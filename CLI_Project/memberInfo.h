#pragma once
#include <cstring>
using namespace std;
class Birthday
{
public:
	int year;
	int month;
	int day;
};
class BirthPlace
{
public:
	char province[10];
	char city[10];
};
public class SchoolMember
{
public:	
	void setBirthPlace(char *province,char *city)
	{
		strcpy(this->birthPlace.city, city);
		strcpy(this->birthPlace.province, province);
	}
	void getBirthPlace(char *&provice, char *&city)
	{
		provice = this->birthPlace.province;
		city = this->birthPlace.city;
	}
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
	void setAge(int age)
	{
		this->age = age;
	}
	int getAge()
	{
		return age;
	}
	void setSex(int sex)
	{
		this->sex = sex;
	}
	int getSex()
	{
		return sex;
	}
	void getBirthday(int &y,int &m,int &d)
	{
		y = birthday.year;
		m = birthday.month;
		d = birthday.day;
	}
	void setBirthday(int y,int m,int d)
	{
		this->birthday.year = y;
		this->birthday.month = m;
		this->birthday.day = d;
	}
	int getMajor()
	{
		return major;
	}
	void setMajor(int mj)
	{
		this->major = mj;
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
	int age;
	Birthday birthday;
	BirthPlace birthPlace;
	int major;
	char picPath[50];
	char idNumber[20];
	bool isTalent;
	char extraInfo[100];
};