Imports Microsoft.Office.Interop
Imports Microsoft.Office.Interop.PowerPoint
Imports System.IO

Class PPTJudge
    Private score As Integer
    Private pointList() As String
    Private offSetOfSlidePoint As String
    Private ConstPointListForPrint() As String 'VB不知道怎么动态往数组里添加元素，自己写个字符串解析好了
    Private pptAnsDoc As PowerPoint.Presentation '构造方法里初始化
    Private slideLevelscorePointList() As Integer '纪录每个考点的分值，在initPointList里面设置一次
    Public log As String   '记录对每个文档评分的细节 每个文档调用getScore方法算法 在里面重置
    Private logPoint As String

    Sub New(ByVal ans As PowerPoint.Presentation, ByVal path As String) '构造函数，使用标准答案
        pptAnsDoc = ans
        initPointList(IO.File.ReadAllText(path))
        ConstPointListForPrint = {"文本框字体大小", "文本框字体颜色", "文本框字体名称", "文本框超链接", "文本框动作跳转", "文本框动画", "文本框粗体", "文本框斜体", "文本下划线", "文本框填充颜色", "自选图形字体大小", "自选图形字体颜色", "自选图形字体名称", "自选图形超链接", "自选图形动作跳转", "自选图形动画", "自选图形粗体", "自选图形斜体", "自选图形下划线", "自选图形填充颜色", "自选图形形状", "图表动画", "图片存在", "图片数目", "表格存在", "表格数目", "幻灯片背景", "幻灯片切换动作", "幻灯片模板", "动画高级模式", "文档名称", "文档纸张大小", "文档宽高", "文档起始编号"}
    End Sub

    Public Function initPointList(ByVal plSrc As String)
        Dim pointAll As String = ""
        Dim pointTemp As String = ""
        Dim indexOfFlag As Integer = 0
        Dim strSlideLevelScoreALl As String = ""
        offSetOfSlidePoint = ""
        Do While plSrc.Contains(">")
            indexOfFlag = plSrc.IndexOf(">")
            pointTemp = plSrc.Substring(0, indexOfFlag)
            strSlideLevelScoreALl = strSlideLevelScoreALl & pointTemp.Substring(pointTemp.LastIndexOf(vbCrLf) + 1) & "|"
            offSetOfSlidePoint = offSetOfSlidePoint & pointTemp.Split(vbCrLf).Length - 1 & ","
            pointTemp = pointTemp.Substring(0, pointTemp.LastIndexOf(vbCrLf) + 2) '去掉每个slide级别最后的分数 ，+2是保留那个换行
            pointAll = pointAll & pointTemp
            plSrc = plSrc.Substring(indexOfFlag + 3)
        Loop
        strSlideLevelScoreALl = strSlideLevelScoreALl & plSrc
        pointAll = pointAll.Replace(vbCrLf, "|")
        pointAll = pointAll.Substring(0, pointAll.Length - 1)
        pointList = pointAll.Split("|")
        Dim listTemp() As String = strSlideLevelScoreALl.Split("|")
        ReDim slideLevelscorePointList(listTemp.Length - 1)
        For i = 0 To listTemp.Length - 1
            slideLevelscorePointList(i) = Integer.Parse(listTemp(i))
        Next
        ' For Each xx In pointList
        'MsgBox(xx)
        'Next
        Return Nothing
    End Function

    Function handleMap(ByVal cont As String, ByVal slide As Slide, ByVal index As Integer)
        Select Case index
            Case 1      '1~10文本框
                Return getFontSize(cont, slide)
            Case 2
                Return getFontColor(cont, slide)
            Case 3
                Return getFontName(cont, slide)
            Case 4
                Return getShapeHyperlinkOut(cont, slide)
            Case 5
                Return getShapeHyperlinkIn(cont, slide)
            Case 6
                Return getShapeEntryEffect(cont, slide)
            Case 7
                Return isBold(cont, slide)
            Case 8
                Return isItalic(cont, slide)
            Case 9
                Return isUnderline(cont, slide)
            Case 10
                Return getFillColor(cont, slide)
            Case 11     '11~21 自选图形
                Return getFontSize(cont, slide)
            Case 12
                Return getFontColor(cont, slide)
            Case 13
                Return getFontName(cont, slide)
            Case 14
                Return getShapeHyperlinkOut(cont, slide)
            Case 15
                Return getShapeHyperlinkIn(cont, slide)
            Case 16
                Return getShapeEntryEffect(cont, slide)
            Case 17
                Return isBold(cont, slide)
            Case 18
                Return isItalic(cont, slide)
            Case 19
                Return isUnderline(cont, slide)
            Case 20
                Return getFillColor(cont, slide)
            Case 21
                Return getShapeType(cont, slide)
            Case 22     '22-26 图表
                Return getSlidePictureOrTableAni(slide)
            Case 23
                Return isPictureExist(slide)
            Case 24
                Return getPictureCx(slide)
            Case 25
                Return isTableExist(slide)
            Case 26
                Return getTableCx(slide)
            Case 27     '27-30 slide级别
                Return getSlideBackgroundStyle(slide)
            Case 28
                Return getTransitionEffect(slide)
            Case 29     '幻灯片模板
                Return getLayoutType(slide)
            Case 30
                Return getSlideAniAdvanceMode(slide)
            Case 31     '31-34 文档级别
                Return getPresentationName(slide.Parent)
            Case 32
                Return getSlideSizeType(slide.Parent)
            Case 33
                Return getSlideHeightWidth(slide.Parent)
            Case 34
                Return getFirstSlideNumber(slide.Parent)
            Case Else
                Return Nothing
        End Select
    End Function

    Public Function getScore(ByVal stuDoc As PowerPoint.Presentation)
        score = 0
        log = "" '重置对文档的评分细节日志
        logPoint = ""
        '  log = "创建时间:" & stuDoc.BuiltInDocumentProperties(11).value & " 保存时间:" & stuDoc.BuiltInDocumentProperties(12).value & " 作者:" & stuDoc.BuiltInDocumentProperties(3).value & "<br>"
        '  log = log & "<table  class='gridtable' border=1><tr><th>序号</th><th>考察内容</th><th>参考答案</th><th>学生答案</th><th>对错</th><th>得分</th></tr>"            '重置对文档的评分细节日志

        Dim stuSlidePosNow = 1 '学生文档结构跟答案不一定一致，用selectStuSlideId处理一些缺页多页的异常
        Dim slidePointCxSum = 0
        Dim pointNow As String = ""  '当前处理的考点
        Dim pointStr As String = "" '当前处理的考点内容标识
        Dim firstSlideLevelIndex As Integer = 25
        Dim firstDocLevelIndex As Integer = 29
        Dim cxOfPoint As Integer = 0
        Dim cxOfPointRight As Integer = 0
        Dim indexOfSlideNow As Integer = 0
        Dim pointScore As Integer = 0
        Dim isFirtsEnterSlide As Boolean
        Dim sCheck As String = "", sAns As String = "", sStu As String = "", sScore As String = ""


        For i = 1 To offSetOfSlidePoint.Length / 2 'slide数目
            isFirtsEnterSlide = True
            Dim slidePointcx As Integer = Integer.Parse(offSetOfSlidePoint((i - 1) * 2))

            sCheck = ""
            sAns = ""
            sStu = ""
            sScore = ""

            For j = 1 To slidePointcx '每个slide考点数
                pointNow = pointList(slidePointCxSum + j - 1)
                pointStr = pointNow.Substring(0, pointNow.IndexOf("@"))
                pointNow = pointNow.Remove(0, pointNow.IndexOf("@") + 1)

                cxOfPoint = 0
                cxOfPointRight = 0
                For t = 0 To (pointNow.LastIndexOf(",") - 1) / 2 '每个考点     

                    If j <> slidePointcx AndAlso t > firstSlideLevelIndex Then '不是最后某个slide的最后一个考点不检查slide级别属性
                        ' MsgBox("不是最后某个slide的最后一个考点不检查slide级别属性")
                        Continue For
                    End If
                    If i <> offSetOfSlidePoint.Length / 2 AndAlso t > firstDocLevelIndex Then '不是文档最后一个slide的最后一个考点不检查文档级别属性
                        'MsgBox("不是文档最后一个slide的最后一个考点不检查文档级别属性"
                        Continue For
                    End If

                    If pointNow(t * 2) = "1" Then
                        If pointStr <> "ignore" Then
                            Dim temp As Integer = selectStuSlideId(stuSlidePosNow, pointStr, stuDoc)
                            If temp <> -1 Then
                                stuSlidePosNow = temp
                            End If
                            isFirtsEnterSlide = False
                        Else                                        'isFirtsEnterSlide记录是否是第一次进入该Slide
                            If isFirtsEnterSlide Then               '切换到下一张Slide时，假如第一个考点就没有关键字(ignore)，那学生文档index要+1
                                stuSlidePosNow = stuSlidePosNow + 1 '用selectStuSlideId来定位学生Slide的位置，但切换slide时，要先有存在关键字的考点才行
                                isFirtsEnterSlide = False
                            End If
                        End If
                        ' MsgBox(pointStr & "考察 - " & ConstPointListForPrint(t) & " 其中 ans = " & handleMap(pointStr, stuDoc.Slides(stuSlidePosNow), t + 1))
                        Dim ansStr As String = handleMap(pointStr, pptAnsDoc.Slides(i), t + 1)
                        Dim stuStr As String = handleMap(pointStr, stuDoc.Slides(stuSlidePosNow), t + 1)

                        log = log & "Slide" & i & " " & pointStr & " 考察 - " & ConstPointListForPrint(t) & vbCrLf
                        log = log & " 其中 ans = " & ansStr & vbCrLf
                        log = log & " 其中 stu = " & stuStr & vbCrLf
                        sCheck = sCheck & "#" & ConstPointListForPrint(t)
                        sAns = sAns & "#" & ansStr
                        sStu = sStu & "#" & stuStr

                        logPoint = logPoint & "Slide" & i & " " & pointStr & " 考察 - " & ConstPointListForPrint(t) & "  "
                        cxOfPoint = cxOfPoint + 1
                        If stuStr = ansStr Then
                            cxOfPointRight = cxOfPointRight + 1
                            logPoint = logPoint & "正确" & vbCrLf
                        Else
                            logPoint = logPoint & "错误" & vbCrLf
                        End If
                    End If

                    If t = firstSlideLevelIndex Then '由于所以消息在一起，当处理到达slide级别开始处时，提交slide内部的文本框、图标等考点
                        If cxOfPoint = 0 Then '被除数不能为0
                            logPoint = logPoint & "空白考点!!!" & vbCrLf
                            cxOfPoint = 0
                            cxOfPointRight = 0
                        Else
                            pointScore = Integer.Parse(pointNow.Substring(pointNow.LastIndexOf(",") + 1).Replace("*", ""))
                            logPoint = logPoint & "该考点考察的属性数目为： " & cxOfPoint & "，其中正确属性数目为： " & cxOfPointRight & vbCrLf
                            logPoint = logPoint & "该考点分值为: " & pointScore & " 计 " & pointScore * (cxOfPointRight / cxOfPoint) & "分" & vbCrLf

                            'log = log & "<tr><td >Slide " & i & "</td><td>" & sCheck.Substring(1).Replace("#", "<hr>") & "</td><td>" & sAns.Substring(1).Replace("#", "<hr>") & "</td><td>" & sStu.Substring(1).Replace("#", "<hr>") & "</td><td>" & sScore.Substring(1).Replace("#", "<hr>") & "</td>"
                            '  log = log & "<td>" & pointScore * (cxOfPointRight / cxOfPoint) & "</td></tr>"

                            score = score + pointScore * (cxOfPointRight / cxOfPoint)
                            cxOfPoint = 0
                            cxOfPointRight = 0
                        End If

                    End If
                    If t = firstDocLevelIndex Then '提交slide级别的考点
                        If cxOfPoint = 0 Then
                            logPoint = logPoint & "空白考点!!!" & vbCrLf
                            cxOfPoint = 0
                            cxOfPointRight = 0
                        Else
                            logPoint = logPoint & "Slide级别考点考察的属性数目为： " & cxOfPoint & "，其中正确属性数目为： " & cxOfPointRight & vbCrLf
                            logPoint = logPoint & "该考点分值为: " & slideLevelscorePointList(indexOfSlideNow) & " 计 " & slideLevelscorePointList(indexOfSlideNow) * (cxOfPointRight / cxOfPoint) & "分" & vbCrLf
                            score = score + slideLevelscorePointList(indexOfSlideNow) * (cxOfPointRight / cxOfPoint)

                            '   log = log & "<tr><td >Slide " & i & "</td><td>" & sCheck.Substring(1).Replace("#", "<hr>") & "</td><td>" & sAns.Substring(1).Replace("#", "<hr>") & "</td><td>" & sStu.Substring(1).Replace("#", "<hr>") & "</td><td>" & sScore.Substring(1).Replace("#", "<hr>") & "</td>"
                            '   log = log & "<td>" & slideLevelscorePointList(indexOfSlideNow) * (cxOfPointRight / cxOfPoint) & "</td></tr>"

                            indexOfSlideNow = indexOfSlideNow + 1
                            cxOfPoint = 0
                            cxOfPointRight = 0
                        End If
                    End If
                    If t = (pointNow.LastIndexOf(",") - 1) / 2 Then '提交文档级别的考点
                        If cxOfPoint = 0 Then
                            logPoint = logPoint & "空白考点!!!" & vbCrLf
                            cxOfPoint = 0
                            cxOfPointRight = 0
                        Else
                            logPoint = logPoint & "文档级别考点考察的属性数目为： " & cxOfPoint & "，其中正确属性数目为： " & cxOfPointRight & vbCrLf
                            logPoint = logPoint & "该考点分值为: " & slideLevelscorePointList(indexOfSlideNow) & " 计 " & slideLevelscorePointList(indexOfSlideNow) * (cxOfPointRight / cxOfPoint) & "分" & vbCrLf
                            score = score + slideLevelscorePointList(indexOfSlideNow) * (cxOfPointRight / cxOfPoint)
                            indexOfSlideNow = indexOfSlideNow + 1
                            cxOfPoint = 0
                            cxOfPointRight = 0
                        End If
                    End If
                Next
            Next
            slidePointCxSum = slidePointCxSum + slidePointcx
        Next
        logPoint = logPoint & vbCrLf & "下面是该文档评分细节" & vbCrLf & vbCrLf
        log = logPoint & log
        '  log = log & "</table><br>"
        writeLog(log, stuDoc.Name, score)
        Return score
    End Function

    Function writeLog(ByVal content As String, ByVal fileName As String, ByVal score As Integer)
        Try
            Dim path As String = "d://pptLog.txt"
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


    '通过内容找到对应Shape Index
    Function getShapeIndexByContent(ByVal cont As String, ByVal slide As Slide)
        Dim text As String = ""
        Dim sp As PowerPoint.Shape
        For i = 1 To slide.Shapes.Count
            sp = slide.Shapes(i)
            If sp.HasTextFrame Then
                If sp.TextFrame.TextRange.Text.Contains(cont) Then
                    Return i
                End If
            End If
        Next
        Return -1
    End Function

    Function selectStuSlideId(ByVal constStuSlidePos As Integer, ByVal cont As String, ByVal pStu As Presentation)
        For i = constStuSlidePos To pStu.Slides.Count
            For j = 1 To pStu.Slides(i).Shapes.Count
                If pStu.Slides(i).Shapes(j).HasTextFrame Then
                    If pStu.Slides(i).Shapes(j).TextFrame.TextRange.Text.Contains(cont) Then
                        Return i
                    End If
                End If
            Next
        Next
        Return -1
    End Function

    Function travel(ByVal pAns As Presentation, ByVal pStu As Presentation)
        Dim constStuSlidePos = 1
        For i = 1 To pAns.Slides.Count
            For j = 1 To pAns.Slides(i).Shapes.Count
                Dim content As String = "something"
                'selectSlide
                Dim slideIndex As Integer = selectStuSlideId(constStuSlidePos, content, pStu)
                If slideIndex <> -1 Then
                    constStuSlidePos = slideIndex
                    ' Compare
                End If
            Next
        Next

        Return Nothing
    End Function

    '字体大小
    Function getFontSize(ByVal cont As String, ByVal slide As Slide)
        Dim index As Integer = getShapeIndexByContent(cont, slide)
        If index = -1 Then
            Return -1
        Else
            Return slide.Shapes(index).TextFrame.TextRange.Font.Size
        End If
    End Function

    '字体颜色
    Function getFontColor(ByVal cont As String, ByVal slide As Slide)
        Dim index As Integer = getShapeIndexByContent(cont, slide)
        If index = -1 Then
            Return "未知"
        Else
            Return slide.Shapes(index).TextFrame.TextRange.Font.Color.RGB.ToString
        End If
    End Function

    '字体名称
    Function getFontName(ByVal cont As String, ByVal slide As Slide)
        Dim index As Integer = getShapeIndexByContent(cont, slide)
        If index = -1 Then
            Return "未知"
        Else
            Return slide.Shapes(index).TextFrame.TextRange.Font.NameFarEast
        End If
    End Function

    '粗体
    Function isBold(ByVal cont As String, ByVal slide As Slide)
        Dim index As Integer = getShapeIndexByContent(cont, slide)
        If index = -1 Then
            Return "未知"
        Else
            Return slide.Shapes(index).TextFrame.TextRange.Font.Bold.ToString
        End If
    End Function

    '斜体
    Function isItalic(ByVal cont As String, ByVal slide As Slide)
        Dim index As Integer = getShapeIndexByContent(cont, slide)
        If index = -1 Then
            Return "未知"
        Else
            Return slide.Shapes(index).TextFrame.TextRange.Font.Italic.ToString
        End If
    End Function

    '下划线
    Function isUnderline(ByVal cont As String, ByVal slide As Slide)
        Dim index As Integer = getShapeIndexByContent(cont, slide)
        If index = -1 Then
            Return "未知"
        Else
            Return slide.Shapes(index).TextFrame.TextRange.Font.Underline.ToString
        End If
    End Function

    '填充颜色
    Function getFillColor(ByVal cont As String, ByVal slide As Slide)
        Dim index As Integer = getShapeIndexByContent(cont, slide)
        If index = -1 Then
            Return "未知"
        Else
            Return slide.Shapes(index).Fill.ForeColor.RGB.ToString
        End If
    End Function

    '自选图形形状
    Function getShapeType(ByVal cont As String, ByVal slide As Slide)
        Dim index As Integer = getShapeIndexByContent(cont, slide)
        If index = -1 Then
            Return "未知"
        Else
            Return slide.Shapes(index).AutoShapeType.ToString
        End If
    End Function

    '获得内部跳转地址  '考虑到学生文档的结构和答案不完全一致,超链接等,只检查某个考点就行了
    Function getShapeHyperlinkIn(ByVal cont As String, ByVal s As Slide)
        Dim index As Integer = getShapeIndexByContent(cont, s)

        If index = -1 Then
            Return "未知"
        Else
            Dim action As String = ""
            If s.Shapes(index).TextFrame.TextRange.ActionSettings(1).Hyperlink.SubAddress <> Nothing Then
                Return "存在"
            End If
            If s.Shapes(index).ActionSettings(1).Hyperlink.SubAddress <> Nothing Then
                Return "存在"
            End If
            Return "不存在"
        End If
    End Function

    '获得文本的超链接地址
    Function getShapeHyperlinkOut(ByVal cont As String, ByVal s As Slide)
        Dim index As Integer = getShapeIndexByContent(cont, s)
        If index = -1 Then
            Return "未知"
        Else
            Dim action As String = ""
            If s.Shapes(index).TextFrame.TextRange.ActionSettings(1).Hyperlink.Address <> Nothing Then
                Return "存在"
            End If
            If s.Shapes(index).ActionSettings(1).Hyperlink.Address <> Nothing Then
                Return "存在"
            End If
            Return "不存在"
        End If
    End Function

    '返回一个图形的进入动画
    Function getShapeEntryEffect(ByVal cont As String, ByVal s As Slide)
        Dim index As Integer = getShapeIndexByContent(cont, s)
        If index = -1 Then
            Return "未知"
        End If
        Return s.Shapes(index).AnimationSettings.EntryEffect.ToString()
    End Function

    'Slide级别如下
    '动画高级效果,如前一事件后几秒后自动播放  当前幻灯片的图形
    Function getSlideAniAdvanceMode(ByVal slide As Slide)
        Dim s As PowerPoint.Shape
        For Each s In slide.Shapes
            If s.AnimationSettings.Animate <> Microsoft.Office.Core.MsoTriState.msoFalse Then
                Return s.AnimationSettings.AdvanceMode.ToString & "," & s.AnimationSettings.AdvanceTime
            End If
        Next
        Return "未知"
    End Function

    'Slide的背景格式，只能检测到是否改变，不是很有效
    Function getSlideBackgroundStyle(ByVal slide As Slide)
        Return slide.BackgroundStyle.ToString
    End Function

    '是否存在图片
    Function isPictureExist(ByVal slide As Slide)
        For Each sp In slide.Shapes
            If sp.Type = Microsoft.Office.Core.MsoShapeType.msoPicture Then
                Return True
            End If
        Next
        Return False
    End Function

    '图片数目
    Function getPictureCx(ByVal slide As Slide)
        Dim cx As Integer = 0
        For Each sp In slide.Shapes
            If sp.Type = Microsoft.Office.Core.MsoShapeType.msoPicture Then
                cx = cx + 1
            End If
        Next
        Return cx
    End Function

    '是否存在表格
    Function isTableExist(ByVal slide As Slide)
        For i = 1 To slide.Shapes.Count
            If slide.Shapes(i).HasTable Then
                Return True
            End If
        Next
        Return False
    End Function

    '表格数目
    Function getTableCx(ByVal slide As Slide)
        Dim cx As Integer = 0
        For i = 1 To slide.Shapes.Count
            If slide.Shapes(i).HasTable Then
                cx = cx + 1
            End If
        Next
        Return cx
    End Function

    'slide里图片或表格的动画，图片对象、表格不好区分，它们的动画考察存不存在
    Function getSlidePictureOrTableAni(ByVal s As Slide)
        For i = 1 To s.Shapes.Count
            If s.Shapes(i).HasTable Or s.Shapes(i).Type = Microsoft.Office.Core.MsoShapeType.msoPicture Then
                If s.Shapes(i).AnimationSettings.EntryEffect <> PpEntryEffect.ppEffectCut Then '没有动画就是cut
                    Return "存在动画"
                End If
            End If
        Next
        Return "未知"
    End Function

    '版式
    Function getLayoutType(ByVal s As Slide)
        Return s.Layout.ToString
    End Function

    'Slide 间切换效果集合
    '1 切换效果√
    Function getTransitionEffect(ByVal s As Slide)
        Return s.SlideShowTransition.EntryEffect.ToString
    End Function

    '2切换是否声音√
    Function getTransitionSound(ByVal s As Slide)
        Return s.SlideShowTransition.SoundEffect.Name.ToString
    End Function
    '3 切换速度
    Function getTransitionSpeed(ByVal s As Slide)
        Return s.SlideShowTransition.Speed.ToString
    End Function

    '文档级别如下
    '文档名称
    Function getPresentationName(ByVal p As Presentation)
        Return p.Name
    End Function

    '文档纸张
    Function getSlideSizeType(ByVal p As Presentation)
        Return p.PageSetup.SlideSize.ToString
    End Function

    '文档宽高
    Function getSlideHeightWidth(ByVal p As Presentation)
        Return p.PageSetup.SlideHeight.ToString & "," & p.PageSetup.SlideWidth.ToString
    End Function

    '起始编号
    Function getFirstSlideNumber(ByVal p As Presentation)
        Return p.PageSetup.FirstSlideNumber.ToString
    End Function

End Class

Public Class PptCheck
    Public Shared pptDocCx As Integer = 0

    Public Function getPPTScore(ByVal ansPath As String, ByVal stuPath As String)
        Dim pptApp As PowerPoint.Application
        Dim pptPre As PowerPoint.Presentation
        Dim pptStu As PowerPoint.Presentation
        Dim ansDocPath As String = ansPath
        Dim stuDocPath As String = stuPath
        Dim ansPointPath As String = ansPath.Replace(".pptx", ".txt")

        pptApp = CreateObject("PowerPoint.Application")
        pptPre = pptApp.Presentations.Open(ansDocPath, , , False)
        Dim pptJudge As PPTJudge = New PPTJudge(pptPre, ansPointPath)

        If (stuDocPath.EndsWith(".pptx")) Then '单文档情形
            pptStu = pptApp.Presentations.Open(stuDocPath, , , False)
            MsgBox("文档 " + pptStu.Name + " 得分为： " + pptJudge.getScore(pptStu).ToString() + vbCrLf + "判题日志详见D://pptLog.txt")
            pptStu.Close()
        Else
            Dim pattern As String = "*.pptx"
            Dim directoryInfo As IO.DirectoryInfo
            Dim fileInfoCollection As IO.FileInfo()
            directoryInfo = New IO.DirectoryInfo(stuPath)
            fileInfoCollection = directoryInfo.GetFiles(pattern)

            '统计阅卷文档数目，阅卷时间
            'wdDocCx将用于dll外部调用，协助动态显示已阅文档数
            Dim timeBegin As Date = Now
            Dim strDisp As String = ""
            For Each file In fileInfoCollection
                If (file.Name.ToString.Contains("~")) Then '损坏的文档
                    Continue For
                End If
                pptStu = pptApp.Presentations.Open(file.FullName, , , False)
                pptJudge.getScore(pptStu)
                pptStu.Close()
                pptDocCx = pptDocCx + 1
            Next
            Dim timeEnd As Date = Now
            strDisp += "判题日志详见D:\pptLog.txt"
            strDisp += vbCrLf
            strDisp += "判卷数: "
            strDisp += pptDocCx.ToString()
            strDisp += " -- 用时："
            strDisp += DateDiff(DateInterval.Second, timeBegin, timeEnd).ToString()
            strDisp += "s"
            MsgBox(strDisp)
        End If
        pptPre.Close()
        pptApp.Quit()
        Return Nothing
    End Function

End Class
