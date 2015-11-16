Imports Microsoft.Office.Interop.Excel
Imports Microsoft.Office.Interop
Imports System.IO

Class ExcelJudge
    Private score As Integer
    Private pointCellsLevelList() As String '为了提高效率,只在initPointList进行考点字符串计算
    Private pointSheetLevelList() As String
    Private pointCellsLevelOffset As String '维持一个偏移量，标识某个sheet里Cellslevel考点数
    Private ConstPointListForPrint() As String 'VB不知道怎么动态往数组里添加元素，自己写个字符串解析好了
    Private xlsAnsDoc As Excel.Workbook '构造方法里初始化
    Private sheetOffsetRow As Integer
    Private sheetOffsetCol As Integer
    Private log As String   '记录对每个文档评分的细节 每个文档调用getScore方法算法 在里面重置
    Private logPoint As String

    Sub New(ByVal ans As Excel.Workbook, ByVal path As String) '构造函数，使用标准答案
        xlsAnsDoc = ans
        initPointList(IO.File.ReadAllText(path))
        ConstPointListForPrint = {"合并单元格", "字体大小", "字体颜色", "字体名称", "下划线", "字形设置", "行高", "列宽", "背景颜色", "对齐方式", "数据格式", "公式", "边框", "筛选", "排序", "页眉", "页脚", "图表", "纸张方向", "纸张大小", "工作表名", "页边距"}
    End Sub

    Public Function initPointList(ByVal pointList As String)
        Dim strSheetAll As String = ""
        Dim strCellsAll As String = ""
        Dim strSheet As String = ""
        Dim strCells As String = ""
        Dim posCellEnd As Integer = 0
        Dim posSheetEnd As Integer = 0
        Do While pointList.Contains(">")
            posSheetEnd = pointList.IndexOf(">")
            strSheet = pointList.Substring(0, posSheetEnd - 2) '换行占2个字节
            pointList = pointList.Substring(posSheetEnd + 3)
            posCellEnd = strSheet.IndexOf("<")
            strCells = strSheet.Substring(0, posCellEnd)
            strCellsAll = strCellsAll & strCells
            pointCellsLevelOffset = pointCellsLevelOffset & strCells.Split(vbCrLf).Length - 1 & ","
            strSheet = strSheet.Substring(posCellEnd + 3)
            strSheetAll = strSheetAll & strSheet & "|"
        Loop
        strCellsAll = strCellsAll.Replace(vbCrLf, "|")
        strSheetAll = strSheetAll.Substring(0, strSheetAll.Length - 1)
        strCellsAll = strCellsAll.Substring(0, strCellsAll.Length - 1)
        pointSheetLevelList = strSheetAll.Split("|")
        pointCellsLevelList = strCellsAll.Split("|")
        Return Nothing
    End Function

    '判断合并单元格
    Function getMergeAreasAddr(ByVal r As Range, ByVal flag As Boolean)
        Dim rangeStr As String = r.MergeArea.Address
        rangeStr = rangeStr.Replace("$", "")
        'Normalization Range
        If flag Then
            rangeStr = normalizationRange(rangeStr)
        End If
        Return rangeStr
    End Function

    '字体大小
    Function getFontSize(ByVal r As Range)
        Return r.Font.Size
    End Function

    '字体颜色
    Function getFontColor(ByVal r As Range)
        Return r.Font.Color
    End Function

    '字体名称
    Function getFontName(ByVal r As Range)
        Return r.Font.Name
    End Function

    '下划线
    Function getUnderlineStyle(ByVal r As Range)
        Return r.Font.Underline.ToString
    End Function

    '字形设置
    Function getRangeFontBI(ByVal r As Range)
        Dim isBI As String = ""
        isBI = isBI & r.Font.Bold.ToString & ","
        isBI = isBI & r.Font.Italic.ToString.ToString
        Return isBI
    End Function

    '行高
    Function getRowHeight(ByVal r As Range)
        Return r.RowHeight
    End Function

    '列宽
    Function getColumnWidth(ByVal r As Range)
        Return r.ColumnWidth
    End Function

    '背景颜色
    Function getRangeBGColor(ByVal r As Range)
        Return r.Interior.Color.ToString
    End Function

    '选择区域的对齐方式
    Function getRangeAlignment(ByVal s As Range)
        Dim align As String = ""
        align = align & s.HorizontalAlignment.ToString & ","
        align = align & s.VerticalAlignment.ToString
        Return align
    End Function

    '数据格式 
    Function getRangeNumberFormat(ByVal r As Range)
        For Each c In r '找到范围内第一个数值
            If IsNumeric(c.Value) Then
                Return c.NumberFormat.ToString()
            End If
        Next
        Return "未知"
    End Function

    '公式
    '修改记录：
    '   1.有些公式可能直接是 =A1+A2的情形
    '   2.多个单元格应用公式的情形增加了遍历，虽然我觉得没必要
    Function getRangeFormula(ByVal ra As Range, ByVal flag As Boolean)
        Dim formulaAll As String = ""
        Dim formulaSrc As String = ""
        Dim formulaRange As String = ""
        For Each r In ra
            formulaSrc = ""
            formulaRange = ""
            formulaSrc = r.Formula.ToString
            Dim posLeftBracket As Integer = formulaSrc.IndexOf("(")

            If posLeftBracket <> -1 Then
                formulaRange = formulaSrc.Substring(posLeftBracket + 1, formulaSrc.Length - posLeftBracket - 2)
                formulaSrc = formulaSrc.Substring(0, posLeftBracket)
                'Return "没有公式" 有些公式可能直接是 =A1+A2的情形
            End If
            'Normalization Range
            If flag Then
                formulaRange = normalizationRange(formulaRange)
            End If
            formulaSrc = formulaSrc & " " & formulaRange
            formulaAll = formulaAll & formulaSrc & ";"
        Next

        Return formulaAll
    End Function

    '单元格边框
    Enum BorderStyle
        xlEdgeTop = 1
        xlEdgeBottom
        xlEdgeRight
        xlEdgeRightLeft
        xlInsideVertical
        xlInsideHorizontal
    End Enum

    '获得所选区域的边框样式 
    Function getRangeBorderStyle(ByVal r As Range)
        Dim border As String = ""
        For i = 1 To 6
            border = border & r.Borders(i).LineStyle & "==="
            border = border & r.Borders(i).Color.ToString & "==="
            border = border & r.Borders(i).Weight
        Next
        Return border
    End Function

    '过滤考点 考虑到单元格并没有记录应用在他们上面的过滤公式等 这里简单的比较结果
    '过滤考点 传入的Range一般应是：过滤行时为 过滤列所以数据单元格
    Function getFilterRes(ByVal r As Range)
        Dim resStr As String = ""
        For Each c In r
            If c.Rows.Hidden Then
                resStr = resStr & "不可见行" & ","
            Else
                resStr = resStr & c.Value & ","
            End If
        Next
        Return resStr
    End Function

    '排序考点 考虑到单元格并没有记录应用在他们上面的排序公式等 这里简单的比较结果
    '排序一般是升序或者降序 比较规律
    Function getSortRes(ByVal r As Range)
        Dim cx As Integer = 0 '计数器
        Dim previousValue As Integer = 0

        For Each c In r
            If cx = 0 AndAlso IsNumeric(c.Value) Then
                cx = cx + 1
                previousValue = c.Value
            ElseIf IsNumeric(c.Value) Then
                If c.Value < previousValue Then
                    Return "降序"
                ElseIf c.Value > previousValue Then
                    Return "升序"
                End If
            End If
        Next
        Return "未知"
    End Function


    '得到页眉 只有文字内容，在左、中间、右，对其方式可以获取到;都找到设置页眉页脚的点了，肯定会设置其他属性了
    Function getHeaderInfo(ByVal xlsSheet As Excel.Worksheet)
        Dim headerInfo As String
        headerInfo = xlsSheet.PageSetup.CenterHeader.ToString & ","
        headerInfo = headerInfo & xlsSheet.PageSetup.LeftHeader.ToString & ","
        headerInfo = headerInfo & xlsSheet.PageSetup.RightHeader.ToString & ","
        Return xlsSheet.PageSetup.CenterHeader.ToString
    End Function

    '页脚
    Function getFooterInfo(ByVal xlsSheet As Excel.Worksheet)
        Dim footerInfo As String
        footerInfo = xlsSheet.PageSetup.CenterFooter.ToString & ","
        footerInfo = footerInfo & xlsSheet.PageSetup.LeftFooter.ToString & ","
        footerInfo = footerInfo & xlsSheet.PageSetup.RightFooter.ToString & ","
        Return xlsSheet.PageSetup.CenterHeader.ToString
    End Function

    '纸张方向
    Function getPageDirection(ByVal xlsSheet As Excel.Worksheet)
        Return xlsSheet.PageSetup.Orientation.ToString
    End Function

    '纸张大小
    Function getPageSize(ByVal xlsSheet As Excel.Worksheet)
        Return xlsSheet.PageSetup.PaperSize.ToString
    End Function

    '工作表名称
    Function getSheetName(ByVal xlsSheet As Excel.Worksheet)
        Return xlsSheet.Name
    End Function

    '页边距
    Function getSheetMargin(ByVal xlsSheet As Excel.Worksheet)
        Dim marginStr As String = ""
        marginStr = marginStr & xlsSheet.PageSetup.TopMargin & ","
        marginStr = marginStr & xlsSheet.PageSetup.BottomMargin & ","
        marginStr = marginStr & xlsSheet.PageSetup.LeftMargin & ","
        marginStr = marginStr & xlsSheet.PageSetup.RightMargin & ","
        Return marginStr
    End Function

    '图表主要考察类型和数据源 以后的工作要把数据源不设置为绝对路径 以及 处理考虑多列少列的情形
    '修改记录：
    '   1.图表考点增加对标题属性的检查
    '   2.增加对图例的检查 注：图例只能检查到数目、字体等，不能直接得到数据源即图例名称，也没找到坐标轴属性的读取方法，只有设置、
    Function getChartStyle(ByVal xlsSheet As Excel.Worksheet, ByVal flag As Boolean) 'flag表面是不是AnsDoc
        If xlsSheet.ChartObjects.Count < 1 Then
            Return "没有图表"
        End If
        Dim c As Chart = xlsSheet.ChartObjects(1).Chart
        Dim dataSrcStr As String = ""
        Dim style As String = ""
        Dim posLeftBracket As Integer = 0
        style = c.ChartType.ToString & vbCrLf

        For i = 1 To c.SeriesCollection.Count
            dataSrcStr = c.SeriesCollection(i).Formula
            posLeftBracket = dataSrcStr.IndexOf("(") + 1
            dataSrcStr = dataSrcStr.Substring(posLeftBracket, dataSrcStr.Length - posLeftBracket - 3)
            dataSrcStr = dataSrcStr.Replace("$", "")
            dataSrcStr = dataSrcStr.Replace(xlsSheet.Name & "!", "")
            'Normalization Range
            If flag Then '只有学生文档才需要标准化输出
                dataSrcStr = normalizationRange(dataSrcStr)
            End If
            dataSrcStr = dataSrcStr & vbCrLf
            style = style & dataSrcStr
        Next
        If c.HasTitle Then
            style = style & "-title info " & c.ChartTitle.Text & c.ChartTitle.Font.Name.ToString & " " & c.ChartTitle.Font.Size.ToString & vbCrLf
        Else
            style = style & "-title info " & "没有标题" & vbCrLf
        End If
        If c.HasLegend Then
            style = style & "-Legend info " & c.Legend.LegendEntries.Count & vbCrLf
        Else
            style = style & "-legend info " & "没有图例信息" & vbCrLf
        End If
        'Dim s As Series = c.SeriesCollection(1)
        ' ch = ch & c.Legend.Font.Size.ToString & c.Legend.Font.Name.ToString '获取系列组的字体
        'ch = ch & c.ChartTitle.Font.Name.ToString & c.ChartTitle.Font.Size.ToString '获取标题的字体
        ' ch = ch & c.PlotArea.Border.LineStyle.ToString()
        Return style
    End Function

    '处理偏移，使偏移的range正常化
    Function normalizationRange(ByVal rangeStr As String)
        Dim rStr As String = ""
        Dim strTemp As String = ""
        Dim numtemp As Integer = 0
        Dim raStrList() As String = rangeStr.Split(",")
        For i = 0 To raStrList.Length - 1
            For j = 0 To raStrList(i).Length - 1
                If Asc(raStrList(i)(j)) >= Asc("A") AndAlso Asc(raStrList(i)(j)) <= Asc("Z") Then
                    strTemp = strTemp & Chr(Asc(raStrList(i)(j)) - sheetOffsetCol)
                ElseIf raStrList(i)(j) = ":" Then
                    strTemp = strTemp & ":"
                ElseIf Asc(raStrList(i)(j)) >= Asc("0") AndAlso Asc(raStrList(i)(j)) <= Asc("9") Then
                    numtemp = 0
                    Do While j < raStrList(i).Length AndAlso Asc(raStrList(i)(j)) >= Asc("0") AndAlso Asc(raStrList(i)(j)) <= Asc("9")
                        numtemp = numtemp * 10 + Asc(raStrList(i)(j)) - Asc("0")
                        j = j + 1
                    Loop
                    j = j - 1
                    numtemp = numtemp - sheetOffsetRow
                    strTemp = strTemp & numtemp
                End If
            Next
            rStr = rStr & strTemp & ","
            strTemp = ""
        Next
        Return rStr.Substring(0, rStr.Length - 1)
    End Function

    Public Function handleMapCellsLevel(ByVal cmd As Integer, ByVal r As Range, ByVal flag As Boolean)
        Select Case cmd
            Case 1
                Return getMergeAreasAddr(r, flag)
            Case 2
                Return getFontSize(r)
            Case 3
                Return getFontColor(r)
            Case 4
                Return getFontName(r)
            Case 5
                Return getUnderlineStyle(r)
            Case 6
                Return getRangeFontBI(r)
            Case 7
                Return getRowHeight(r)
            Case 8
                Return getColumnWidth(r)
            Case 9
                Return getRangeBGColor(r)
            Case 10
                Return getRangeAlignment(r)
            Case 11
                Return getRangeNumberFormat(r)
            Case 12
                Return getRangeFormula(r, flag)
            Case 13
                Return getRangeBorderStyle(r)
            Case 14
                Return getFilterRes(r)
            Case 15
                Return getSortRes(r)
            Case Else
                Return Nothing
        End Select
    End Function

    Public Function handleMapSheetsLevel(ByVal cmd As Integer, ByVal xlsSheet As Excel.Worksheet, ByVal flag As Boolean)
        Select Case cmd
            Case 1
                Return getHeaderInfo(xlsSheet)
            Case 2
                Return getFooterInfo(xlsSheet)
            Case 3
                Return getChartStyle(xlsSheet, flag)
            Case 4
                Return getPageDirection(xlsSheet)
            Case 5
                Return getPageSize(xlsSheet)
            Case 6
                Return getSheetName(xlsSheet)
            Case 7
                Return getSheetMargin(xlsSheet)
            Case Else
                Return Nothing
        End Select
    End Function

    Function writeLog(ByVal content As String, ByVal fileName As String, ByVal score As Integer)
        Try
            Dim path As String = "d://excelLog.txt"
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

    Public Function getScore(ByVal stu As Excel.Workbook)

        sheetOffsetCol = 0
        sheetOffsetRow = 0
        score = 0
        log = "" '重置对文档的评分细节日志
        logPoint = ""

        Dim cellPoingCx As Integer = 15 '单元格考点测试时取5个，Sheet级别考点取3个
        Dim sheetPointCx As Integer = 7
        Dim posRange As Integer = 0
        Dim offSet As Integer = 0
        Dim offSetSum As Integer = 0 '各sheet累计的Cell考点数
        Dim rangeStr As String = ""
        Dim cellStr As String = ""
        Dim ra As Range
        Dim cxOfPoint As Integer = 0
        Dim cxOfPointRight As Integer = 0
        Dim scoreOfPointNow As Integer = 0
        Dim strScoreOfPoint As String = ""
        For i = 0 To (pointCellsLevelOffset.Length / 2) - 1 '.length即为sheet数目，即对每个sheet,pointCellsLevelOffset存了每个sheet的单元格考点数，

            '处理偏移 ，学生可能建立表的位置和要求或答案不同,用这个来规范偏移
            sheetOffsetRow = xlsAnsDoc.Worksheets(i + 1).UsedRange.End(XlDirection.xlToRight).row
            sheetOffsetCol = xlsAnsDoc.Worksheets(i + 1).UsedRange.End(XlDirection.xlDown).Column
            sheetOffsetRow = stu.Worksheets(i + 1).UsedRange.End(XlDirection.xlToRight).row - sheetOffsetRow
            sheetOffsetCol = stu.Worksheets(i + 1).UsedRange.End(XlDirection.xlDown).Column - sheetOffsetCol

            If sheetOffsetRow <> 0 Or sheetOffsetCol <> 0 Then
                'MsgBox("异常！将偏移：row=" & sheetOffsetRow & " col=" & sheetOffsetCol)
                log = log & "异常！将偏移：row=" & sheetOffsetRow & " col=" & sheetOffsetCol
            Else
                ' MsgBox("一切正常,没有偏移")
                log = log & "一切正常,没有偏移"
            End If
            'sheet级各考点
            strScoreOfPoint = pointSheetLevelList(i).Substring(pointSheetLevelList(i).IndexOf("*") + 1)
            strScoreOfPoint = strScoreOfPoint.Replace("@", "")
            scoreOfPointNow = Integer.Parse(strScoreOfPoint)

            cxOfPoint = 0
            cxOfPointRight = 0
            For t = 0 To pointSheetLevelList(i).IndexOf("*") ' *号后面为不是属性检查点了
                If pointSheetLevelList(i)(t) = "1" Then
                    cxOfPoint = cxOfPoint + 1
                    'MsgBox("考察： " & ConstPointListForPrint(cellPoingCx + t / 2) & " ans = " & handleMapSheetsLevel(t / 2 + 1, xlsAnsDoc.Worksheets(i + 1), False) & "stu = " & handleMapSheetsLevel(t / 2 + 1, stu.Worksheets(i + 1), True))
                    '   MsgBox(handleMapSheetsLevel(t / 2 + 1, stu.Worksheets(i + 1)))
                    log = log & "考察： " & ConstPointListForPrint(cellPoingCx + t / 2) & vbCrLf & "其中 ans = " & handleMapSheetsLevel(t / 2 + 1, xlsAnsDoc.Worksheets(i + 1), False) & vbCrLf & "stu = " & handleMapSheetsLevel(t / 2 + 1, stu.Worksheets(i + 1), True) & vbCrLf
                    logPoint = logPoint & xlsAnsDoc.Worksheets(i + 1).Name & "考察： " & ConstPointListForPrint(cellPoingCx + t / 2) & "  "
                    If handleMapSheetsLevel(t / 2 + 1, xlsAnsDoc.Worksheets(i + 1), False) = handleMapSheetsLevel(t / 2 + 1, stu.Worksheets(i + 1), True) Then
                        logPoint = logPoint & "正确" & vbCrLf
                        cxOfPointRight = cxOfPointRight + 1
                    Else
                        logPoint = logPoint & "错误" & vbCrLf
                    End If
                End If
            Next
            If cxOfPoint = 0 Then
                logPoint = logPoint & "该考点为空!!!" & vbCrLf
            Else
                logPoint = logPoint & "该sheet级别考点检查属性数目： " & cxOfPoint & "其中，正确属性数目为： " & cxOfPointRight & vbCrLf
                logPoint = logPoint & "该考点分值为： " & scoreOfPointNow & ",计 " & scoreOfPointNow * (cxOfPointRight / cxOfPoint) & " 分" & vbCrLf
                score = score + scoreOfPointNow * (cxOfPointRight / cxOfPoint)
            End If


            '某个sheet的,各Cells考点
            offSet = Integer.Parse(pointCellsLevelOffset(i * 2))
            For j = 0 To offSet - 1
                cellStr = pointCellsLevelList(offSetSum + j)
                posRange = cellStr.IndexOf("]")
                rangeStr = cellStr.Substring(1, posRange - 1)
                cellStr = cellStr.Substring(posRange + 2)
                strScoreOfPoint = cellStr.Substring(cellStr.IndexOf("*") + 1)
                strScoreOfPoint = strScoreOfPoint.Replace("@", "")
                scoreOfPointNow = Integer.Parse(strScoreOfPoint)
                cxOfPoint = 0
                cxOfPointRight = 0
                For k = 0 To cellStr.IndexOf("*") - 1
                    If cellStr(k) = "1" Then
                        ' MsgBox("range:" & rangeStr & "考察:" & ConstPointListForPrint(k / 2))
                        cxOfPoint = cxOfPoint + 1
                        ra = stu.Worksheets(i + 1).Range(rangeStr)
                        ra = ra.Offset(sheetOffsetRow, sheetOffsetCol)
                        ' MsgBox(handleMapCellsLevel(k / 2 + 1, ra))
                        ' MsgBox("ans = " & handleMapCellsLevel(k / 2 + 1, xlsAnsDoc.Worksheets(i + 1).Range(rangeStr), False) & " stu = " & handleMapCellsLevel(k / 2 + 1, ra, True))
                        log = log & "[" & rangeStr & "]" & "考察:" & ConstPointListForPrint(k / 2) & vbCrLf
                        log = log & "其中 ans = " & handleMapCellsLevel(k / 2 + 1, xlsAnsDoc.Worksheets(i + 1).Range(rangeStr), False) & " stu = " & handleMapCellsLevel(k / 2 + 1, ra, True) & vbCrLf
                        logPoint = logPoint & "[" & rangeStr & "]" & "考察:" & ConstPointListForPrint(k / 2) & "  "
                        If handleMapCellsLevel(k / 2 + 1, xlsAnsDoc.Worksheets(i + 1).Range(rangeStr), False) = handleMapCellsLevel(k / 2 + 1, ra, True) Then
                            logPoint = logPoint & "正确" & vbCrLf
                            cxOfPointRight = cxOfPointRight + 1
                        Else
                            logPoint = logPoint & "错误" & vbCrLf
                        End If
                    End If
                Next
                If cxOfPoint = 0 Then
                    logPoint = logPoint & "该考点为空!!!" & vbCrLf
                Else
                    logPoint = logPoint & "该cells级别考点检查属性数目： " & cxOfPoint & "其中，正确属性数目为： " & cxOfPointRight & vbCrLf
                    logPoint = logPoint & "该考点分值为： " & scoreOfPointNow & ",计 " & scoreOfPointNow * (cxOfPointRight / cxOfPoint) & " 分" & vbCrLf
                    score = score + scoreOfPointNow * (cxOfPointRight / cxOfPoint)
                End If
            Next
            offSetSum = offSetSum + offSet
        Next
        logPoint = logPoint & vbCrLf & "下面是该文档评分细节" & vbCrLf & vbCrLf
        log = logPoint & log
        writeLog(log, stu.Name, score)
        Return score
    End Function

End Class

Public Class ExcelCheck
    Public Shared excelDocCx As Integer = 0

    Public Function getExcelScore(ByVal ansPath As String, ByVal stuPath As String)
        Dim xlsApp As Excel.Application = CreateObject("Excel.Application")
        xlsApp.Visible = False
        Dim xlsExcel As Excel.Workbook
        Dim xlsStu As Excel.Workbook
        Dim xlsAnsPath As String = ansPath
        Dim xlsAnsPointPath As String = ansPath.Replace(".xlsx", ".txt")
        Dim xlsStuPath As String = stuPath

        '初始化答案文档
        xlsExcel = xlsApp.Workbooks.Open(xlsAnsPath)
        Dim xlsJudge As ExcelJudge = New ExcelJudge(xlsExcel, xlsAnsPointPath)

        If (xlsStuPath.EndsWith(".xlsx")) Then '单文档情形
            xlsStu = xlsApp.Workbooks.Open(xlsStuPath)
            MsgBox("文档 " + xlsStu.Name + " 得分为： " + xlsJudge.getScore(xlsStu).ToString() + vbCrLf + "判题日志详见D://excelLog.txt")
            xlsStu.Close()
        Else                                '目录情形
            Dim pattern As String = "*.xlsx"
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
                xlsStu = xlsApp.Workbooks.Open(file.FullName)
                xlsJudge.getScore(xlsStu)
                xlsStu.Close()
                excelDocCx = excelDocCx + 1
            Next
            Dim timeEnd As Date = Now
            strDisp += "判题日志详见D:\excelLog.txt"
            strDisp += vbCrLf
            strDisp += "判卷数: "
            strDisp += excelDocCx.ToString()
            strDisp += " -- 用时："
            strDisp += DateDiff(DateInterval.Second, timeBegin, timeEnd).ToString()
            strDisp += "s"
            MsgBox(strDisp)
        End If
        xlsExcel.Close()
        xlsApp.Quit()
        Return Nothing
    End Function
End Class
