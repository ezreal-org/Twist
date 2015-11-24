#pragma once
#include "memberInfo.h"
#include <fstream>
#include <iostream>
using namespace std;

namespace ManagementSystemV5 {
	using namespace System::Data::Odbc;

	public ref class Storage
	{
	private:
		OdbcConnection^ Conn;
		OdbcDataAdapter ^adapter;
		DataSet^ set;
	public:
		SchoolMember* readSchoolMemberInfo(char *id)
		{
			SchoolMember*  p1 = new SchoolMember();
			fstream f;
			char path[50];
			sprintf(path, "D:\\%s.dat", id);
			f.open(path, ios::in | ios::binary);
			f.read((char*)p1, sizeof(SchoolMember));
			f.close();
			return p1;
		}
		void writeSchoolMemberInfo(SchoolMember *p)
		{
			fstream f;
			char path[50];
			sprintf(path, "D:\\%s.dat", p->getId());
			f.open(path, ios::out | ios::binary);
			f.write((char*)p, sizeof(SchoolMember));
			f.close();
		}
		void dbConnect()
		{
			Conn = gcnew OdbcConnection("DSN=ManagementSystemV5;UI=root;PWD=tk;");
			String^ sql = "select* from schoolmember;";
			adapter = gcnew OdbcDataAdapter(sql, Conn);
			set = gcnew DataSet();
			adapter->Fill(set, "schoolmember");
		}
		DataRow^ getRowById(char* id)
		{
			DataTable^ table = set->Tables["schoolmember"];
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
				MessageBox::Show("没有返回行");
				return nullptr;
			}
			return newRow;
		}
		void persistent()
		{
			DataSet^ updateSet;
			try
			{
				updateSet = set->GetChanges();
				if (updateSet)
				{
					OdbcCommandBuilder^ b = gcnew OdbcCommandBuilder(adapter);
					adapter->Update(updateSet, "schoolmember");
					set->AcceptChanges();
				}
			}
			catch (Exception^)
			{
				MessageBox::Show("store erro");
			}
		}
		SchoolMember* readSchoolMemberInfoDB(char *id)
		{
			dbConnect();
			DataRow^ row = getRowById(id);
			MessageBox::Show(row["id"] + " " + row["name"]);
			return nullptr;
		}
		void writeSchoolMemberInfoDB(SchoolMember *p)
		{
			dbConnect();
			DataTable^ table = set->Tables["schoolmember"];
			DataRow^ row;
			DataRow^ newRow = table->NewRow();
			string str;
			str = p->getId();
			newRow["id"] = gcnew String(str.c_str());
			str = p->getName();
			newRow["name"] = gcnew String(str.c_str());
			newRow["sex"] = p->getSex();
			newRow["age"] = p->getAge();
			str = p->getCity();
			newRow["homeCity"] = gcnew String(str.c_str());
			row = getRowById(p->getId());
			if (row != nullptr) //修改
			{
				row->Delete();	//简单的先删除
				table->Rows->Add(newRow); //再添加
			}
			else //加入
			{
				table->Rows->Add(newRow);
			}
			persistent();
		}
	};
}