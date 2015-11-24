#pragma once
#include <cstring>
using namespace std;
public class SchoolMember
{
public:
	void setName(char* name)
	{
		strcpy(this->name, name);
	}
	void setAge(int age)
	{
		this->age = age;
	}
	void setSex(int sex)
	{
		this->sex = sex;
	}
	void setCity(char *city)
	{
		strcpy(this->homeCity, city);
	}
	void setId(char* id)
	{
		strcpy(this->id, id);
	}
	char* getName()
	{
		return name;
	}
	char* getCity()
	{
		return homeCity;
	}
	char* getId()
	{
		return id;
	}
	int getAge()
	{
		return age;
	}
	int getSex()
	{
		return sex;
	}
private:
	char id[20];
	char name[20];
	int sex;
	int age;
	char homeCity[20];
};