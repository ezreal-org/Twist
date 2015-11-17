Imports Microsoft.Office.Interop
Imports Microsoft.Office.Interop.Word
Imports System.IO

Class CommAttr
    Private doc As Document
    Sub New(ByVal d As Document)
        doc = d
    End Sub

    Function getPicAroundStyle() '约定一个题目只有一个图形
        If doc.Shapes.Count > 0 Then
            Return doc.Shapes.Item(1).WrapFormat.Type.ToString
        Else
            Return "没有图片"
        End If
    End Function
    Function getPicDistance()
        Dim distanceStr As String
        If doc.Shapes.Count > 0 Then
            distanceStr = doc.Shapes.Item(1).WrapFormat.DistanceBottom.ToString & ","
            distanceStr = distanceStr + doc.Shapes.Item(1).WrapFormat.DistanceLeft.ToString & ","
            distanceStr = distanceStr + doc.Shapes.Item(1).WrapFormat.DistanceRight.ToString & ","
            distanceStr = distanceStr + doc.Shapes.Item(1).WrapFormat.DistanceTop.ToString & ","
            Return distanceStr
        Else
            Return "没有图片"
        End If

    End Function

    Function handleMap(ByVal i As Integer)
        Select Case i
            Case 1
                Return getPicAroundStyle()
            Case 2
                Return getPicDistance()
            Case 4
                Return getPicAroundStyle()
            Case Else
                Return Nothing
        End Select
    End Function

End Class

Class Para
    Private p As Paragraph
    Sub New(ByVal para As Paragraph)
        p = para
    End Sub

    Function getFontSize() As String
        Return p.Range.Font.Size.ToString
    End Function

    Function getFontFace() As String
        Return p.Range.Font.NameFarEast
    End Function

    Function getFontColor() As String
        Return p.Range.Font.ColorIndex.ToString
    End Function

    Function getFontOtherChara() As String
        Dim ctr As String
        ctr = p.Range.Font.Bold.ToString
        ctr = ctr & "," & p.Range.Font.Italic.ToString
        Return ctr
    End Function

    Function getUnderline() As String
        Dim underL As String
        underL = p.Range.Underline.ToString
        Return (underL)
    End Function

    Function getCharaSpacing() As String
        Return p.Range.Font.Spacing.ToString
    End Function

    '公式段，简单的检查公式内容
    Function getFormula() As String
        Return p.Range.Text
    End Function

    Function getShadingStyle() As String  '阴影效果，测试结果不好
        Dim styleD As String
        styleD = p.Range.Shading.ForegroundPatternColor.ToString
        styleD = styleD & "," & p.Range.Shading.BackgroundPatternColor.ToString
        styleD = styleD & "," & p.Range.Shading.Texture.ToString
        styleD = styleD & p.Range.Text
        Return styleD
    End Function

    Function getEmphasismark() As String
        Return p.Range.EmphasisMark.ToString
    End Function

    Function getBgColor() As String
        Return p.Range.HighlightColorIndex.ToString
    End Function


    Function getAlignment() As String
        Return p.Alignment.ToString
    End Function

    Function getFrontAndAfterDistOfPara() As String '段前段后距离
        Dim dis As String
        dis = p.SpaceAfter.ToString
        dis = dis & p.SpaceBefore.ToString
        dis = dis & p.SpaceAfterAuto.ToString & "," & p.SpaceBeforeAuto.ToString
        Return dis
    End Function

    Function getRAndLIn() As String  '左右缩进
        Dim dis As String
        dis = p.CharacterUnitLeftIndent.ToString & "," & p.CharacterUnitRightIndent.ToString
        Return dis
    End Function

    Function getLineSpace() As String
        Return p.LineSpacingRule.ToString & "," & p.LineSpacing.ToString
    End Function

    Function getFirstLeterDrop() As String
        Return p.DropCap.LinesToDrop.ToString & "," & p.DropCap.DistanceFromText.ToString & "," & p.DropCap.FontName.ToString
    End Function

    Function getBorderStyle() As String
        Dim borderS As String
        borderS = p.Borders(1).LineStyle.ToString & "," & p.Borders(1).LineWidth.ToString & "," & p.Borders(1).Color.ToString
        Return borderS
    End Function

    Function getFenLanStyle() As String
        Dim st As String
        st = p.Range.PageSetup.TextColumns.Count.ToString & "," & p.Range.PageSetup.TextColumns.EvenlySpaced.ToString & "," & p.Range.PageSetup.TextColumns.LineBetween.ToString & "," & p.Range.PageSetup.TextColumns.Spacing.ToString
        Return st
    End Function

    Function handleMap(ByVal i As Integer)
        Select Case i
            Case 1
                Return getFontSize()
            Case 2
                Return getFontFace()
            Case 3
                Return getFontColor()
            Case 4
                Return getFontOtherChara()
            Case 5
                Return getUnderline()
            Case 6
                Return getCharaSpacing()
            Case 7
                Return getShadingStyle()
            Case 8
                Return getEmphasismark()
            Case 9
                Return getBgColor()
            Case 10
                Return getAlignment()
            Case 11
                Return getFrontAndAfterDistOfPara()
            Case 12
                Return getRAndLIn()
            Case 13
                Return getFirstLeterDrop()
            Case 14
                Return getLineSpace()
            Case 15
                Return getBorderStyle()
            Case 16
                Return getFenLanStyle()
            Case Else
                Return Nothing
        End Select
        Return Nothing
    End Function

End Class

Class WordCheckPerDoc
    Private ConstPointListForPrint() As String '所有段落考点名
    Private ConstCommonPointListForPrint() As String '所有通用考点名称
    Private commonPoint As String '通用考点
    Private paraPoint As String '段落考点列表
    Private pointPath As String
    Private answerDoc As Document '答案文档，对每道题判卷只初始化一次
    Private stuDoc As Document  '学生文档
    Private commAttrAns As CommAttr '答案的通用属性，对每道题目只初始化一次
    Private ansParaIndex As Integer '当前匹配答案第几段，对每个学生文档getScore时设置初始值
    Private ansValidParaIndex As Integer '有效的正处理段落下标 getScore里非空段加一
    Private paraScoreList() As Integer '每个考点的分值，在initpointList初始化
    Private flagOfXiaChen As Boolean '是否刚处理完下沉段
    Private flagOfXiaChenRes As Boolean '假如刚处理完下沉段，首字下沉结果怎样
    Private score As Integer
    Private log As String   '记录对每个文档评分的细节 每个文档调用getScore方法算法 在里面重置
    Private logPoint As String

    Sub New(ByVal answer As Document, ByVal path As String) '构造函数，使用标准答案
        answerDoc = answer
        score = 0
        pointPath = path.Replace(".docx", ".txt")        'path
        ConstPointListForPrint = {"字体大小", "字体类型", "字体颜色", "字形设置", "下划线", "字符间距", "阴影样式", "字符强调", "背景颜色", "对齐方式", "段前段后距离", "左右缩进", "首字下沉", "行间距", "边框", "分栏", "背景图片", "标题风格"}
        ConstCommonPointListForPrint = {"艺术字", "表格", "插入图画", "环绕方式", "图文距离"}
        commAttrAns = New CommAttr(answer)
        '从答案列表中获得考点列表！
        initPointList()
    End Sub

    Function initPointList()
        paraPoint = ""
        Dim pointPerPara As Integer = 18
        Dim scoreStr As String = ""
        '既老师给定的段数，并不一定等于真实的段数，下沉，分栏会使段数增加
        Dim actualCountOfPara As Integer = 0
        Dim strTemp As String = ""
        For Each line As String In File.ReadLines(pointPath)
            If line.Substring(0, line.IndexOf("@")) <> "0" Then '空段时老师可能添加了分数为0的段，直接忽略，分数也不加进去
                scoreStr = scoreStr & line.Substring(0, line.IndexOf("@")) & ","
            End If

            line = line.Substring(line.IndexOf("@") + 1)
            If line.Length < pointPerPara * 2 Then
                commonPoint = line
            Else
                actualCountOfPara = actualCountOfPara + 1
                paraPoint = paraPoint & line
            End If
        Next
        Dim scoreList() As String = scoreStr.Split(",")
        ReDim paraScoreList(scoreList.Length - 1)
        For k = 0 To scoreList.Length - 2
            paraScoreList(k) = Integer.Parse(scoreList(k))
        Next
        Dim strRec As String '处理某段时先保存下来那段以前的样子
        Dim i As Integer = 0
        Dim chars() As Char
        Do While i < actualCountOfPara '处理分栏，这里简单约定每段 16号考点为下沉标志
            strRec = paraPoint.Substring(i * pointPerPara * 2, pointPerPara * 2)
            If strRec(30) = "1" Then
                If i = 0 Then
                    paraPoint = paraPoint.Insert((i + 1) * pointPerPara * 2, "0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,")
                    actualCountOfPara = actualCountOfPara + 1
                Else
                    paraPoint = paraPoint.Insert((i + 1) * pointPerPara * 2, "0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,")
                    paraPoint = paraPoint.Insert(i * pointPerPara * 2, "0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,")
                    actualCountOfPara = actualCountOfPara + 2
                    i = i + 1
                End If
            End If
            i = i + 1
        Loop
        i = 0
        Do While i < actualCountOfPara '处理下沉，这里简单约定每段 13号考点为下沉标志
            strRec = paraPoint.Substring(i * pointPerPara * 2, pointPerPara * 2)
            If strRec(24) = "1" Then
                chars = paraPoint.ToCharArray
                chars(i * pointPerPara * 2 + 24) = "0"
                paraPoint = New String(chars)
                paraPoint = paraPoint.Insert(i * pointPerPara * 2, "0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,")
                actualCountOfPara = actualCountOfPara + 1
            End If
            i = i + 1
        Loop
        ' For i = 0 To actualCountOfPara - 1
        'MsgBox(paraPoint.Substring(i * pointPerPara * 2, 36))
        ' Next
        Return (Nothing)
    End Function

    Function selectNextPara(ByVal j As Integer, ByVal sDoc As Document) '当段内多了回车或段间多了回车可以处理异常
        Dim nextParaIndex As Integer = j
        Dim cNextParaIndex As Integer = j + 1

        If sDoc.Paragraphs(j).Range.Text.Length <> answerDoc.Paragraphs(ansParaIndex).Range.Text.Length Then '某段异常，这里明天要改下，应该考虑学生缺段情形
            '  MsgBox("学生第" & j & "段匹配异常") '找一个完全相同的段 或 答案下沉下面的段内容跟学生相差首字
            log = log & "学生第" & j & "段匹配异常" & vbCrLf
            ansParaIndex = ansParaIndex + 1
            Do While ansParaIndex <= answerDoc.Paragraphs.Count
                nextParaIndex = cNextParaIndex 'cNextParaIndex 记录回溯点
                Do While nextParaIndex <= sDoc.Paragraphs.Count '相同的段内容应该一样
                    '   MsgBox(answerDoc.Paragraphs(ansParaIndex).Range.Text & " <>" & sDoc.Paragraphs(nextParaIndex).Range.Text)
                    log = log & answerDoc.Paragraphs(ansParaIndex).Range.Text & "<>" & sDoc.Paragraphs(nextParaIndex).Range.Text & "--" & vbCrLf
                    If answerDoc.Paragraphs(ansParaIndex).Range.Text = sDoc.Paragraphs(nextParaIndex).Range.Text AndAlso answerDoc.Paragraphs(ansParaIndex).Range.Text.Length > 1 Then '分栏生成的空段 占四个字节 这里处理不了
                        Return nextParaIndex
                    End If
                    If answerDoc.Paragraphs(ansParaIndex - 1).Range.Text.Length > 1 AndAlso answerDoc.Paragraphs(ansParaIndex - 1).Range.Text.Length < 3 Then
                        ' MsgBox("学生段丢失首字下沉 尝试匹配以后的内容")
                        log = log & "答案上一段为首字下沉 尝试匹配以后的内容" & vbCrLf
                        flagOfXiaChen = True
                        flagOfXiaChenRes = False
                        If sDoc.Paragraphs(nextParaIndex - 1).Range.Text.Length > 2 AndAlso answerDoc.Paragraphs(ansParaIndex).Range.Text = sDoc.Paragraphs(nextParaIndex - 1).Range.Text.Substring(1) Then
                            log = log & "学生段丢失首字下沉 其他内容匹配" & vbCrLf
                            '  MsgBox(answerDoc.Paragraphs(ansParaIndex).Range.Text & answerDoc.Paragraphs(ansParaIndex).Range.Text.Length & "-" & sDoc.Paragraphs(nextParaIndex - 1).Range.Text.Length)
                            'log = log & answerDoc.Paragraphs(ansParaIndex).Range.Text & answerDoc.Paragraphs(ansParaIndex).Range.Text.Length & "-" & sDoc.Paragraphs(nextParaIndex - 1).Range.Text.Length & vbCrLf
                            Return nextParaIndex - 1
                        End If
                    Else
                        flagOfXiaChen = False
                    End If
                    nextParaIndex = nextParaIndex + 1
                Loop
                For i = 0 To 35 '假如某段丢失 该段的考点都算错 写入日志
                    If i = 24 Then '当为首字下沉时，ansValidParaIndex不会加一，因为它指的分数还是将作用于下面的段
                        Continue For
                    End If
                    If paraPoint(36 * (ansParaIndex - 1) + i) = "1" Then
                        log = log & "学生丢失实际ans第" & ansParaIndex & "段信息" & vbCrLf
                        logPoint = logPoint & "学生丢失实际ans第" & ansParaIndex & "段信息" & vbCrLf
                        ansValidParaIndex = ansValidParaIndex + 1 '丢失非空段时　有效指针也要往下走
                        Exit For
                    End If
                Next
                ansParaIndex = ansParaIndex + 1
            Loop
        Else
            nextParaIndex = nextParaIndex + 1
            Do While nextParaIndex <= sDoc.Paragraphs.Count AndAlso sDoc.Paragraphs(nextParaIndex).Range.Text.Length < 2 '找到下一段不为空的学生段
                nextParaIndex = nextParaIndex + 1
            Loop
            ansParaIndex = ansParaIndex + 1
            Do While ansParaIndex <= answerDoc.Paragraphs.Count AndAlso answerDoc.Paragraphs(ansParaIndex).Range.Text.Length < 2 '找到一个不为空的段
                ansParaIndex = ansParaIndex + 1
            Loop
        End If
        Return nextParaIndex
    End Function

    Function getScore(ByVal sDoc As Document) As Integer '计算每个文档得分
        score = 0
        ansValidParaIndex = 0
        log = "" '重置对文档的评分细节日志
        logPoint = ""
        stuDoc = sDoc
        ansParaIndex = 1
        Dim paraCount = answerDoc.Paragraphs.Count
        'getParaScore
        Dim pIndexOfStu As Integer = 1
        ' Do While (ansParaIndex <= answerDoc.Paragraphs.Count) AndAlso (pIndexOfStu <= sDoc.Paragraphs.Count)
        '不再检查所有段，而是设置了考点的段，一方面减少计算，另一方面，没有设置考点的段，没有pointList，会越界
        '首字下沉和分栏会自动补类似 0,0,0 的靠点，不受影响
        Do While (ansParaIndex <= paraPoint.Length / 36) AndAlso (pIndexOfStu <= sDoc.Paragraphs.Count)
            'MsgBox("ans第" & ansParaIndex & "stu第" & pIndexOfStu)
            log = log & "ans第" & ansParaIndex & "stu第" & pIndexOfStu & vbCrLf
            If pIndexOfStu <= sDoc.Paragraphs.Count Then
                '  MsgBox(answerDoc.Paragraphs(ansParaIndex).Range.Text & "--" & sDoc.Paragraphs(pIndexOfStu).Range.Text)
                log = log & answerDoc.Paragraphs(ansParaIndex).Range.Text & "--" & sDoc.Paragraphs(pIndexOfStu).Range.Text & vbCrLf
                ' MsgBox("计算Ans第" & ansParaIndex & "段 和" & "Stu第" & pIndexOfStu & "段")
                log = log & "计算Ans第" & ansParaIndex & "段 和" & "Stu第" & pIndexOfStu & "段" & vbCrLf
                score = score + getParaScore(pIndexOfStu)
                pIndexOfStu = selectNextPara(pIndexOfStu, stuDoc)
            End If
        Loop

        'getComObjScore
        Dim countOfCommAttr As Integer = commonPoint.Length / 2
        Dim commAttrStu As CommAttr = New CommAttr(sDoc)

        Dim cxOfPoint As Integer = 0
        Dim cxOfRightPoint As Integer = 0

        For j = 0 To countOfCommAttr - 1 '0到所有通用考点数
            If (commonPoint(j * 2) = "1") Then
                cxOfPoint = cxOfPoint + 1
                logPoint = logPoint & ConstCommonPointListForPrint(j)
                If commAttrAns.handleMap(j + 1) = commAttrStu.handleMap(j + 1) Then
                    cxOfRightPoint = cxOfRightPoint + 1
                    log = log & "<该考点答案正确>" & vbCrLf
                    logPoint = logPoint & " -- 正确" & vbCrLf
                Else
                    logPoint = logPoint & " -- 错误" & vbCrLf
                End If
                ' MsgBox("通用考点 考查:" & ConstCommonPointListForPrint(j) & "--其中 ans = " & commAttrAns.handleMap(j + 1) & " stu = " & commAttrStu.handleMap(j + 1))
                log = log & "通用考点 考查:" & ConstCommonPointListForPrint(j) & "--其中 ans = " & commAttrAns.handleMap(j + 1) & " stu = " & commAttrStu.handleMap(j + 1) & vbCrLf
            End If
        Next
        If cxOfPoint > 0 Then
            logPoint = logPoint & "通用考点属性数目：" & cxOfPoint & ", 其中正确属性数目:" & cxOfRightPoint & vbCrLf
            logPoint = logPoint & "通用考点分值为: " & paraScoreList(paraScoreList.Length - 2) & "  计 " & paraScoreList(ansValidParaIndex) * (cxOfRightPoint / cxOfPoint) & vbCrLf
            log = log & "通用考点属性数目：" & cxOfPoint & ", 其中正确属性数目:" & cxOfRightPoint & vbCrLf
            log = log & "通用考点分值为: " & paraScoreList(paraScoreList.Length - 2) & "  计 " & paraScoreList(ansValidParaIndex) * (cxOfRightPoint / cxOfPoint) & vbCrLf
            score = score + paraScoreList(ansValidParaIndex) * (cxOfRightPoint / cxOfPoint)
        End If
        GC.Collect()
        logPoint = logPoint & vbCrLf & "下面是该文档评分细节" & vbCrLf & vbCrLf
        log = logPoint & log
        writeLog(log, sDoc.Name, score)
        Return score
    End Function

    Private Function getParaScore(ByVal pIndexOfStu As Integer) As Integer '因为异常的存在，学生段可能推迟，按答案标准判题
        Dim cxOfPoint As Integer = 0
        Dim cxOfRightPoint As Integer = 0
        Dim pAns As Para = New Para(answerDoc.Paragraphs(ansParaIndex))
        ' Dim countOfPointPerPara As Integer = (paraPoint.Length / 2) / answerDoc.Paragraphs.Count
        Dim countOfPointPerPara As Integer = 18 '假如有些段没有设置考点，那么上面计算的就不准确
        '这里可以加过滤处理，处理误操作问题
        Dim pStu As Para = New Para(stuDoc.Paragraphs(pIndexOfStu))
        For j = 0 To countOfPointPerPara - 1 ' 0到每段考点数
            If paraPoint((countOfPointPerPara * (ansParaIndex - 1) + j) * 2) = "1" Then
                cxOfPoint = cxOfPoint + 1
                logPoint = logPoint & ConstPointListForPrint(j)
                If (pAns.handleMap(j + 1) = pStu.handleMap(j + 1)) Then
                    cxOfRightPoint = cxOfRightPoint + 1
                    log = log & "<该属性答案正确>" & vbCrLf
                    logPoint = logPoint & " -- 正确" & vbCrLf
                Else
                    logPoint = logPoint & " -- 错误" & vbCrLf
                End If
                'MsgBox("考查:" & ConstPointListForPrint(j) & "--其中 ans = " & pAns.handleMap(j + 1) & " stu = " & pStu.handleMap(j + 1) & " " & (pAns.handleMap(j + 1) = pStu.handleMap(j + 1)))
                log = log & "考查:" & ConstPointListForPrint(j) & "--其中 ans = " & pAns.handleMap(j + 1) & " stu = " & pStu.handleMap(j + 1) & " " & (pAns.handleMap(j + 1) = pStu.handleMap(j + 1)) & vbCrLf
            End If
        Next
        '算分时会存在一些问题，分栏和首字下沉会改变原来的段落格式，
        '那么应用在上面的分值设定也是要灵活处理的'
        '分栏只增加了空段，影响不大,首字下沉时，设置一个静态变量存储以前的首字下沉值

        If cxOfPoint > 0 Or flagOfXiaChen Then
            If ansValidParaIndex > paraScoreList.Length - 3 Then
                Return 0
            End If
            If cxOfPoint = 1 AndAlso paraPoint((countOfPointPerPara * (ansParaIndex - 1)) * 2 + 24) = "1" Then '该段是首字下沉
                flagOfXiaChen = True
                If cxOfRightPoint > 0 Then
                    flagOfXiaChenRes = True
                Else
                    flagOfXiaChenRes = False
                End If
                Return 0
            End If

            If flagOfXiaChen Then
                cxOfPoint = cxOfPoint + 1
                If flagOfXiaChenRes Then
                    cxOfRightPoint = cxOfRightPoint + 1
                End If
                flagOfXiaChen = False
                flagOfXiaChenRes = False
            End If
            logPoint = logPoint & "该段考察属性数目：" & cxOfPoint & ", 其中正确属性数目:" & cxOfRightPoint & vbCrLf
            logPoint = logPoint & "该段分值为: " & paraScoreList(ansValidParaIndex) & "  计 " & paraScoreList(ansValidParaIndex) * (cxOfRightPoint / cxOfPoint) & vbCrLf
            log = log & "该段考察属性数目：" & cxOfPoint & ", 其中正确属性数目:" & cxOfRightPoint & vbCrLf
            log = log & "该段分值为: " & paraScoreList(ansValidParaIndex) & "  计 " & paraScoreList(ansValidParaIndex) * (cxOfRightPoint / cxOfPoint) & vbCrLf

            ansValidParaIndex = ansValidParaIndex + 1
            Return paraScoreList(ansValidParaIndex - 1) * (cxOfRightPoint / cxOfPoint)

        End If
        GC.Collect()
        Return 0
    End Function

    Function writeLog(ByVal content As String, ByVal fileName As String, ByVal score As Integer)
        Try
            Dim path As String = "d://wordLog.txt"
            Dim sw As StreamWriter = New StreamWriter(path, True)
            sw.WriteLine("===================================" & fileName & "得分为：" & score & "============================")
            sw.WriteLine(content)
            sw.WriteLine("-------------------------------------------------------------------------------")
            sw.WriteLine("")
            sw.Close()
        Catch ex As Exception
            MsgBox(ex.ToString)
        End Try
        Return Nothing
    End Function

End Class

Public Class wordCheck
    Public Shared wdDocCx As Integer = 0
    '检查一个学生文档的接口
    '以后要增加批量检查学生文档功能，定义word.Application时间较长
    Public Function getWordScore(ByVal pathAns As String, ByVal pathStu As String)
        '答案初始化
        Dim wdApp As New Word.Application
        Dim FileNameAns As String = pathAns
        Dim docAns As Document = wdApp.Documents.Open(FileNameAns, Nothing, False)
        wdApp.ActiveWindow.Visible = False
        Dim wordCheck As WordCheckPerDoc = New WordCheckPerDoc(docAns, FileNameAns)

        Dim docStu2 As Document
        If (pathStu.EndsWith(".docx")) Then '单文档情形
            Dim FileName2 As String = pathStu
            docStu2 = wdApp.Documents.Open(FileName2, Nothing, False)
            wdApp.ActiveWindow.Visible = False
            MsgBox("文档" + docStu2.Name + "得分为:" + wordCheck.getScore(docStu2).ToString() + vbCrLf + "判题日志详见D:\wordLog.txt")
            wdApp.Visible = False
            docStu2.Close()
        Else                                '目录情形
            Dim pattern As String = "*.docx"
            Dim directoryInfo As IO.DirectoryInfo
            Dim fileInfoCollection As IO.FileInfo()
            directoryInfo = New IO.DirectoryInfo(pathStu)
            fileInfoCollection = directoryInfo.GetFiles(pattern)

            '统计阅卷文档数目，阅卷时间
            'wdDocCx将用于dll外部调用，协助动态显示已阅文档数
            Dim timeBegin As Date = Now
            Dim strDisp As String = ""
            For Each file In fileInfoCollection
                If (file.Name.ToString.Contains("~")) Then '损坏的文档
                    Continue For
                End If
                docStu2 = wdApp.Documents.Open(file.FullName, Nothing, False)
                wdApp.ActiveWindow.Visible = False
                wordCheck.getScore(docStu2)
                wdApp.Visible = False
                docStu2.Close()
                wdDocCx = wdDocCx + 1
            Next
            Dim timeEnd As Date = Now
            strDisp += "判题日志详见D:\wordLog.txt"
            strDisp += vbCrLf
            strDisp += "判卷数: "
            strDisp += wdDocCx.ToString()
            strDisp += " -- 用时："
            strDisp += DateDiff(DateInterval.Second, timeBegin, timeEnd).ToString()
            strDisp += "s"
            MsgBox(strDisp)

        End If
        wdApp.Quit()
        Return Nothing
    End Function

End Class

