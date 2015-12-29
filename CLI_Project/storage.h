#pragma once
#include "memberInfo.h"
#include <fstream>
#include <iostream>
using namespace std;

namespace ManagementSystemV5 {
	using namespace System::Data::Odbc;
	using namespace System::IO;
	public ref class Storage
	{
	private:
		OdbcConnection^ Conn;
		OdbcDataAdapter ^adapter;
		DataSet^ set;

		void dbConnect(String^ sql,String ^tableName)
		{
			Conn = gcnew OdbcConnection("DSN=ManagementSystemV5;UI=root;PWD=tk;");
			adapter = gcnew OdbcDataAdapter(sql, Conn);
			set = gcnew DataSet();
			adapter->Fill(set, tableName);
		}
		DataRow^ getRowById(char* id,String ^tableName)
		{
			DataTable^ table = set->Tables[tableName];
			DataRow^ newRow;
			array<DataColumn^>^ keys = gcnew array<DataColumn^>(2);
			keys[0] = table->Columns["id"];
			table->PrimaryKey = keys;
			string str = id;
			String^ Str = gcnew String(str.c_str());
			try {
				newRow = table->Rows->Find(Str);
			}
			catch (MissingPrimaryKeyException^)
			{
				//MessageBox::Show("没有返回行");
				return nullptr;
			}
			return newRow;
		}
		void persistent(String ^tableName)
		{
			DataSet^ updateSet;
			try
			{
				updateSet = set->GetChanges();
				if (updateSet)
				{
					OdbcCommandBuilder^ b = gcnew OdbcCommandBuilder(adapter);
					adapter->Update(updateSet, tableName);
					set->AcceptChanges();
				}
			}
			catch (Exception^)
			{
				MessageBox::Show("store erro");
			}
		}

	public:
		bool login(int flag,char* name,char* passwd) //不同flag对应不同类型用户登录文件
		{
			char buffer[100];
			char loginInfo[100];
			ifstream input;

			char *path = "C:\\login\\admin.txt";
			if (flag)
				path = "C:\\login\\stu.txt";
			sprintf(loginInfo, "%s|%s", name, passwd);
			input.open(path,ios::in);
			if (!input) { cout << "文件打开失败" << endl; return false; }
			while (!input.eof())
			{
				input.getline(buffer, 100);
				if (!strcmp(loginInfo, buffer))
				{
					input.close();
					return true;
				}
			}
			input.close();
			return false;
		}
		bool updateInfo(int flag, char* name,char* oldpw,char *passwd)
		{
			char buffer[100];
			char newLoginInfo[100];
			char oldLoginInfo[100];
			bool ret = false;
			string strFile = ""; //考虑到文件比较小，修改某一行直接通过文件拼接
			fstream io;

			char *path = "C:\\login\\admin.txt";
			if (flag)
				path = "C:\\login\\stu.txt";
			sprintf(newLoginInfo, "%s|%s", name, passwd);
			sprintf(oldLoginInfo, "%s|%s", name, oldpw);
			io.open(path,ios::in);
			if (!io) { cout << "文件打开失败" << endl; return false; }
			while (!io.eof()) //组建新文件
			{
				io.getline(buffer, 100);
				if (!strcmp(oldLoginInfo, buffer))
				{
					ret = true;
					strFile += newLoginInfo;
					strFile += "\n";
					continue;
				}
				strFile += buffer;
				strFile += "\n";
			}
			io.close();
			io.open(path, ios::out);
			io << strFile.substr(0,strFile.size()-1);//去掉最后的换行
			io.close();
			return ret;
		}

		SchoolMember* readSchoolMemberInfo(char *id)
		{
			SchoolMember*  p1 = new SchoolMember();
			fstream f;
			char path[50];
			sprintf(path, "D:\\stu\\%s.dat", id);
			f.open(path, ios::in | ios::binary);
			f.read((char*)p1, sizeof(SchoolMember));
			f.close();
			return p1;
		}
		void writeSchoolMemberInfo(SchoolMember *p)
		{
			fstream f;
			char path[50];
			sprintf(path, "D:\\stu\\%s %s.dat", p->getId(),p->getName());
			f.open(path, ios::out | ios::binary);
			f.write((char*)p, sizeof(SchoolMember));
			f.close();
		}
		cli::array<String^>^ readAllFileName()
		{
			String^ pattern = "*.dat";
			IO::DirectoryInfo ^directoryInfo = gcnew DirectoryInfo("D://stu//");
			cli::array<FileInfo^>^fileCollection  = directoryInfo->GetFiles(pattern);
			cli::array<String^>^ retString = gcnew cli::array<String^>(fileCollection->Length);
			for (int i = 0; i < fileCollection->Length; i++)
			{
				retString[i] = fileCollection[i]->Name->Substring(0,fileCollection[i]->Name->IndexOf("."));
			}
			return retString;
		}
		LoginInfo^ loginDB( int type,String ^name, String ^passwd) //不同flag对应不同类型用户登录文件
		{														//返回用户ID
			String ^sql = "select * from login";
			dbConnect(sql, "login");
			DataTable^ table = set->Tables["login"];
		    for each(DataRow^ row in table->Rows)
			{
				if (((String^)(row["name"]) == name) && ((String^)(row["passwd"]) == passwd) && (type==(int)(row["type"])))  
				{
					LoginInfo^ thisLogin = gcnew LoginInfo((String^)(row["id"]),(int)(row["type"]), (String^)(row["name"]), (String^)(row["passwd"]));
					return thisLogin;
				}
					
			}
			return nullptr;
		}
		bool updateLoginInfoByIdDB(char *id, char* oldpw, char* passwd)
		{
			String ^sql = "select * from login";
			dbConnect(sql, "login");
			DataTable^ table = set->Tables["login"];
			DataRow^ row;
			DataRow^ newRow = table->NewRow();
			
			row = getRowById(id, "login");
			string temp;
			temp = oldpw;
			String^ strOldPasswd = gcnew String(temp.c_str());
			temp = passwd;
			String^ strNewPasswd = gcnew String(temp.c_str());
			if ((String^)row["passwd"] != strOldPasswd) 
			{
				return false;
			}
			
			newRow["id"] = (String^)row["id"];
			newRow["name"] = (String^)row["name"];
			newRow["type"] = (int)(row["type"]);
			newRow["passwd"] = strNewPasswd;
			row->Delete();	
			table->Rows->Add(newRow);
			persistent("login");
			return true;
		}
		//表结构目前还没有和文件系统结构统一
		SchoolMember* readSchoolMemberInfoDB(char *id)
		{
			dbConnect("select * from schoolmember;", "schoolmember");
			DataRow^ row = getRowById(id,"schoolmember");
			if (row != nullptr)
			{
				SchoolMember* pm1 = new SchoolMember();
				char id[20];
				char name[20];
				int sex;
				Birthday birthday;
				char picPath[50];
				char idNumber[50];
				bool isTalent;
				char extraInfo[100];
				sprintf(id, "%s", (String^)row["id"]);
				sprintf(name, "%s", (String^)row["name"]);
				sprintf(extraInfo, "%s", (String^)row["extraInfo"]);
				sprintf(picPath, "%s", (String^)row["picPath"]);
				sprintf(idNumber, "%s", (String^)row["idNum"]);
				sex = (int)row["sex"];
				birthday.year = (int)row["birthYear"];
				birthday.month = (int)row["birthmonth"];
				birthday.day = (int)row["birthday"];
				isTalent = (int)row["isTalent"];

				pm1->setId(id);
				pm1->setName(name);
				pm1->setExtraInfo(extraInfo);
				pm1->setPicpath(picPath);
				pm1->setIdNumber(idNumber);
				pm1->setSex(sex);
				pm1->setBirthday(birthday.year, birthday.month, birthday.day);
				pm1->setIsTalent(isTalent);

				return pm1;
			}
			return nullptr;
		}
		void writeSchoolMemberInfoDB(SchoolMember *p)
		{
			dbConnect("select * from schoolmember;", "schoolmember");
			DataTable^ table = set->Tables["schoolmember"];
			DataRow^ row;
			DataRow^ newRow = table->NewRow();
			string str;
			str = p->getId();
			newRow["id"] = gcnew String(str.c_str());
			str = p->getName();
			newRow["name"] = gcnew String(str.c_str());
			newRow["sex"] = p->getSex();
			int year, month, day;
			p->getBirthday(year,month,day);
			newRow["birthYear"] = year;
			newRow["birthMonth"] = month;
			newRow["birthDay"] = day;
			newRow["isTalent"] = p->getIsTalent();
			str = p->getPicpath();
			newRow["picPath"] = gcnew String(str.c_str());
			str = p->getExtraInfo();
			newRow["extraInfo"] = gcnew String(str.c_str());
			str = p->getIdNumber();
			newRow["idNum"] = gcnew String(str.c_str());

			row = getRowById(p->getId(),"schoolmember");
			if (row != nullptr) //修改
			{
				row->Delete();	//可以简单的先删除,再添加,也可以直接修改row
			
			}
			table->Rows->Add(newRow);
			persistent("schoolmember");
		}

		array<String^>^ readAllStuSummaryInfo()
		{
			dbConnect("select * from schoolmember", "schoolmember");
			DataTable^ table = set->Tables["schoolmember"];
			cout << table->Rows->Count;
			cli::array<String^>^ retString = gcnew cli::array<String^>(table->Rows->Count);
			int index = 0;
			for each(DataRow^ row in table->Rows)
			{
				retString[index] = (String^)(row["id"]);
				retString[index] += " ";
				retString[index++] += (String^)(row["name"]);
			}
			return retString;
		}
	};
	
}