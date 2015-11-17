Imports Microsoft.Office.Interop
Imports Microsoft.Office.Interop.Access
Imports Microsoft.Office.Interop.Access.Dao
Imports System.IO

Class AccessJudgeSimple
    Private score As Integer
    Private ansBase As Database
    Private ansStructStrList() As String
    Private ansTablePrimarykeyList() As String
    Private ansRelationshipList() As String
    Private log As String

    Sub New(ByVal ans As Database)
        ansBase = ans
        ansStructStrList = getTableStructScore(ansBase, False)
        ansTablePrimarykeyList = getTablePrimarykeyScore(ansBase, False)
        ansRelationshipList = getTableRelationshipScore(ansBase, False)
    End Sub

    '目前Access检查的点为表结构、主键、表间关系、查询。目前把每个检查点设置为25
    '修改记录：
    '   1.增加归一化分数处理
    Public Function getScore(ByVal stuBase As Database)
        score = 0
        log = ""
        getTableStructScore(stuBase, True) 'bool 为false时为初始化答案，返回List，不计算得分
        getTablePrimarykeyScore(stuBase, True)
        getTableRelationshipScore(stuBase, True)
        getQueryScore(stuBase)
        writeLog(log, stuBase.Name.Substring(stuBase.Name.LastIndexOf("\") + 1), score)
        Return score
    End Function

    Function writeLog(ByVal content As String, ByVal fileName As String, ByVal score As Integer)
        Try
            Dim path As String = "d://AccessLog.txt"
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

    '计算表结构得分 flag=true 表明是学生文档 需要计算分数 不需要返回
    '修改记录：
    '   1.增加归一化分数处理
    Function getTableStructScore(ByVal stuBase As Database, ByVal flag As Boolean)
        Dim table As TableDef
        Dim structStr As String = ""
        Dim structStrList() As String
        Dim tableNameList() As String = getUserTableList(stuBase)
        Dim cxOfPoint As Integer = 0 '表数目
        Dim cxOfPointRight As Integer = 0 '正确的表数目
        cxOfPoint = tableNameList.Length
        For Each tableName In tableNameList
            table = stuBase.TableDefs(tableName)
            structStr = structStr & table.Fields.Count & " "
            For i = 0 To table.Fields.Count - 1
                structStr = structStr & table.Fields(i).Name & ","
            Next
            structStr = structStr & ";"
        Next
        structStr = structStr.Substring(0, structStr.Length - 1)
        structStrList = structStr.Split(";")

        If flag Then
            For Each ansStructItem In ansStructStrList
                For Each stuStructItem In structStrList
                    If ansStructItem = stuStructItem Then
                        'score = score + 1
                        cxOfPointRight = cxOfPointRight + 1
                        Exit For
                    End If
                Next
            Next
            log = log & "表数目为：" & cxOfPoint & " 其中正确结构数目为：" & cxOfPointRight & vbCrLf
            log = log & "该考点分值为：25 " & "计 " & 25 * (cxOfPointRight / cxOfPoint) & vbCrLf
            score = score + 25 * (cxOfPointRight / cxOfPoint)
            Return Nothing
        End If
        Return structStrList
    End Function

    '计算主键得分 flag=true 表明是学生文档 需要计算分数 不需要返回
    '修改记录：
    '   1.增加归一化分数处理
    Function getTablePrimarykeyScore(ByVal stuBase As Database, ByVal flag As Boolean)
        Dim table As TableDef
        Dim allPrimarykeyStr As String = ""
        Dim primarykeyStrList() As String
        Dim tableNameList() As String = getUserTableList(stuBase)
        Dim cxOfPoint As Integer = 0 '表数目
        Dim cxOfPointRight As Integer = 0 '正确的主键数目
        cxOfPoint = tableNameList.Length

        For Each tableName In tableNameList
            table = stuBase.TableDefs(tableName)
            For i = 1 To table.Indexes.Count '主键都是索引，可以通过索引的primary判别
                If table.Indexes(i - 1).Primary.ToString = True Then
                    For j = 0 To table.Indexes(i - 1).Fields.Count - 1
                        allPrimarykeyStr = allPrimarykeyStr & table.Indexes(i - 1).Fields(j).Name & " "
                    Next
                    Exit For
                End If
            Next
            allPrimarykeyStr = allPrimarykeyStr & ","
        Next
        allPrimarykeyStr = allPrimarykeyStr.Substring(0, allPrimarykeyStr.Length - 1)
        primarykeyStrList = allPrimarykeyStr.Split(",")
        If flag Then
            For Each ansPrimarykey In ansTablePrimarykeyList
                For Each stuKey In primarykeyStrList
                    If ansPrimarykey = stuKey Then
                        'score = score + 1
                        cxOfPointRight = cxOfPointRight + 1
                        Exit For
                    End If
                Next
            Next
            log = log & "表数目为：" & cxOfPoint & " 其中正确主键数目为：" & cxOfPointRight & vbCrLf
            log = log & "该考点分值为：25 " & "计 " & 25 * (cxOfPointRight / cxOfPoint) & vbCrLf
            score = score + 25 * (cxOfPointRight / cxOfPoint)
            Return Nothing
        End If
        Return primarykeyStrList
    End Function

    '计算表间关系得分 flag=true 表明是学生文档 需要计算分数 不需要返回
    '修改记录：
    '   1.增加归一化分数处理
    Function getTableRelationshipScore(ByVal stuBase As Database, ByVal flag As Boolean)
        Dim relation As Relation
        Dim allRelation As String = ""
        Dim relationList() As String
        Dim cxOfPoint As Integer = 0 '表关系数
        Dim cxOfPointRight As Integer = 0 '正确的表关系数
        cxOfPoint = stuBase.Relations.Count - 1

        For i = 1 To stuBase.Relations.Count - 1
            relation = stuBase.Relations(i)
            allRelation = allRelation & relation.Name & " "
            For j = 0 To relation.Fields.Count - 1
                allRelation = allRelation & relation.Fields(j).Name & " " & relation.Fields(j).ForeignName
            Next
            allRelation = allRelation & ","
        Next
        allRelation = allRelation.Substring(0, allRelation.Length - 1)
        relationList = allRelation.Split(",")
        If flag Then
            For Each ansRelation In ansRelationshipList
                For Each stuRelation In relationList
                    If ansRelation = stuRelation Then
                        ' score = score + 1
                        cxOfPointRight = cxOfPointRight + 1
                        Exit For
                    End If
                Next
            Next
            log = log & "表间关系数目为：" & cxOfPoint & " 其中正确关系数目为：" & cxOfPointRight & vbCrLf
            log = log & "该考点分值为：25 " & "计 " & 25 * (cxOfPointRight / cxOfPoint) & vbCrLf
            score = score + 25 * (cxOfPointRight / cxOfPoint)
            Return Nothing
        End If
        Return relationList
    End Function

    '计算查询得分
    '修改记录：
    '   1.增加归一化分数处理
    Function getQueryScore(ByVal db2 As Database)
        Dim qAnswerArr() As String = dbQeryToArray(ansBase)
        Dim qStuArr() As String = dbQeryToArray(db2)
        Dim resultOfAnswerQuery() As String = queryToAccess(qAnswerArr, ansBase)  '将老师的查询去查询 db1 ，返回的结果， 如N条记录，则下表为0-n-1 长度不用减去1
        Dim resultOfStuQuery() As String = queryToAccess(qStuArr, ansBase) '将学生的查询语句作用于标准答案，得到结果
        Dim cxOfPoint As Integer = 0 '查询数
        Dim cxOfPointRight As Integer = 0 '正确的查询数
        cxOfPoint = ansBase.QueryDefs.Count
        '比较两个查询结果，如果老师的查询结果能在学生的查询结果里面找到，算学生正确！
        For i = 0 To ansBase.QueryDefs.Count - 1
            cxOfPointRight = cxOfPointRight + checkIsInArray(resultOfAnswerQuery(i), resultOfStuQuery)
        Next
        ' MsgBox("考点个数为：" & ansBase.QueryDefs.Count & "最后分数是：" & mark)
        log = log & "查询数为：" & cxOfPoint & " 其中正确查询数目为：" & cxOfPointRight & vbCrLf
        log = log & "该考点分值为：25 " & "计 " & 25 * (cxOfPointRight / cxOfPoint) & vbCrLf
        score = score + 25 * (cxOfPointRight / cxOfPoint)
        Return Nothing
    End Function

    '把一个数据库的所有查询，并执行， 把结果形成一个字符串数组
    Function queryToAccess(ByVal queries() As String, ByRef db As Database)
        Dim numOfQuery As Integer = queries.Length - 1
        Dim results(numOfQuery) As String

        Dim rs As Recordset
        For i = 0 To numOfQuery - 1
            Dim q As String = queries(i)
            q = q.ToLower()

            If q.Contains("update") Then
                '  MsgBox("语句为：" & q & "退出")
                results(i) = "更新操作" '如果是删除或者更改， 设为空
                Continue For
            End If

            If q.Contains("delete") Then
                ' MsgBox("语句为：" & q & "退出")
                results(i) = "delete" '如果是删除或者更改， 设为空
                Continue For
            End If

            '  MsgBox("查询语句为：" & q)

            rs = db.OpenRecordset(q, , , )
            rs.MoveLast() '得到所有的记录数

            Dim rowOfResult As Integer = rs.RecordCount
            Dim colOfResult As Integer = rs.Fields.Count
            Dim r(rowOfResult, colOfResult) As String

            rs.MoveFirst() '调到第一条
            ' MsgBox("查询结果的记录数为：" & rowOfResult)

            For j = 1 To rowOfResult
                For k = 1 To colOfResult
                    On Error Resume Next
                    r(j - 1, k - 1) = rs.Fields(k - 1).Value
                Next
                rs.MoveNext()
            Next

            Dim t As String = i + 1 & ":"
            For o = 0 To rowOfResult - 1
                For p = 0 To colOfResult - 1
                    t = t & r(o, p) & ","
                Next
                t = t & vbCrLf
            Next
            results(i) = t
        Next

        For m = 0 To results.Length - 2
            ' MsgBox(results(m))
        Next
        Return results
    End Function

    Function checkIsInArray(ByVal s As String, ByRef str() As String)
        For i = 0 To str.Length - 1
            If s = str(i) Then
                str(i) = ""
                Return 1
            End If
        Next
        Return 0
    End Function

    '得到该Access 的所有查询
    Function dbQeryToArray(ByVal db As Database)
        Dim qcount As Integer = db.QueryDefs.Count
        Dim queryArray(qcount) As String
        For i = 0 To qcount - 1
            Dim s As String = db.QueryDefs(i).SQL.ToString
            queryArray(i) = s
        Next
        Return queryArray
    End Function


    '找到所有用户表
    Function getUserTableList(ByVal stuBase As Database)
        Dim allUserTableName As String = ""
        Dim allUserTableNameList() As String
        For Each table In stuBase.TableDefs
            If table.Name.ToString.StartsWith("MSys") Then
                Continue For
            End If
            allUserTableName = allUserTableName & table.Name & ","
        Next
        allUserTableName = allUserTableName.Substring(0, allUserTableName.Length - 1)
        allUserTableNameList = allUserTableName.Split(",")
        Return allUserTableNameList
    End Function

End Class

Public Class AccessCheckSimple
    Public Shared accessDocCx As Integer = 0

    Public Function getAccessScore(ByVal ansPath As String, ByVal stuPath As String)
        Dim appAccess As New Access.Application
        Dim db As Database
        Dim stuDb As Database
        appAccess = CreateObject("Access.Application")
        appAccess.Visible = False
        appAccess.UserControl = False '不提示用于保存数据

        Dim path As String = ansPath
        Dim stuP As String = stuPath
        appAccess.OpenCurrentDatabase(path, False)
        appAccess.Visible = False
        db = appAccess.CurrentDb
        appAccess.CloseCurrentDatabase()
        Dim acJudge As AccessJudgeSimple = New AccessJudgeSimple(db)

        If (stuP.EndsWith(".accdb")) Then '单文档情形
            appAccess.OpenCurrentDatabase(stuP, False)
            appAccess.Visible = False
            stuDb = appAccess.CurrentDb
            appAccess.CloseCurrentDatabase()
            MsgBox("文档 " + stuDb.Name + " 得分为： " + acJudge.getScore(stuDb).ToString() + vbCrLf + "判题日志详见D://accessLog.txt")
            stuDb.Close()
            ' appAccess.CloseCurrentDatabase()
        Else
            Dim pattern As String = "*.accdb"
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
                appAccess.OpenCurrentDatabase(file.FullName, False)
                appAccess.Visible = False
                stuDb = appAccess.CurrentDb
                acJudge.getScore(stuDb)
                stuDb.Close()
                appAccess.CloseCurrentDatabase()
                accessDocCx = accessDocCx + 1
            Next
            Dim timeEnd As Date = Now
            strDisp += "判题日志详见D:\accessLog.txt"
            strDisp += vbCrLf
            strDisp += "判卷数: "
            strDisp += accessDocCx.ToString()
            strDisp += " -- 用时："
            strDisp += DateDiff(DateInterval.Second, timeBegin, timeEnd).ToString()
            strDisp += "s"
            MsgBox(strDisp)
        End If
        db.Close()
        '  appAccess.CloseCurrentDatabase()

        appAccess.Visible = False

        ' appAccess.Quit()
        Dim generation As Integer = New Integer
        generation = System.GC.GetGeneration(appAccess)
        System.GC.Collect(generation, GCCollectionMode.Forced)

        Return Nothing
    End Function
End Class
