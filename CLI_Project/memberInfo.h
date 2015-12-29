#pragma once
#include <cstring>
using namespace std;
namespace ManagementSystemV5 {

#pragma once
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public class Birthday
	{
	public:
		int year;
		int month;
		int day;
	};
	public class SchoolMember
	{
	public:
		void setId(char* id)
		{
			strcpy(this->id, id);
		}
		char* getId()
		{
			return id;
		}
		void setName(char* name)
		{
			strcpy(this->name, name);
		}

		char* getName()
		{
			return name;
		}
		void setSex(int sex)
		{
			this->sex = sex;
		}
		int getSex()
		{
			return sex;
		}
		void getBirthday(int &y, int &m, int &d)
		{
			y = birthday.year;
			m = birthday.month;
			d = birthday.day;
		}
		void setBirthday(int y, int m, int d)
		{
			this->birthday.year = y;
			this->birthday.month = m;
			this->birthday.day = d;
		}
		char* getPicpath()
		{
			return this->picPath;
		}
		void setPicpath(char* path)
		{
			strcpy(this->picPath, path);
		}
		char* getIdNumber()
		{
			return this->idNumber;
		}
		void setIdNumber(char* idNum)
		{
			strcpy(this->idNumber, idNum);
		}
		bool getIsTalent()
		{
			return isTalent;
		}
		void setIsTalent(bool talent)
		{
			this->isTalent = talent;
		}
		char* getExtraInfo()
		{
			return this->extraInfo;
		}
		void setExtraInfo(char* info)
		{
			strcpy(this->extraInfo, info);
		}

	private:
		char id[20];
		char name[20];
		int sex;
		Birthday birthday;
		char picPath[50];
		char idNumber[50];
		bool isTalent;
		char extraInfo[100];
	};

	public ref class LoginInfo
	{
	public:
		LoginInfo(String ^id, int type,String ^name, String ^passwd)
		{
			this->id = id;
			this->type = type;
			this->name = name;
			this->passwd = passwd;
		}
		String^ getId()
		{
			return this->id;
		}
		String^ getName()
		{
			return this->name;
		}
		int getType()
		{
			return this->type;
		}
	private:
		String^ id;
		String^ name;
		String^ passwd;
		int type;
	};
}