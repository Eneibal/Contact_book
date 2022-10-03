#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class Contact
{
	int id = 0;
	char* name = nullptr;
	char* midl_name = nullptr;
	char* adress_con = nullptr;
	int number_phone = 0;
public:
	Contact();
	Contact(int id_, const char* name_, const char* midl_name_,
		const char* adress_con_, int number_phone_);
	Contact(const Contact& obj);//конструктор копіювання //constryctor copy
	Contact(Contact&& obj);// конструктор переноса//constructor move
	~Contact();
	Contact& operator=(const Contact& obj);
	Contact& operator=(Contact&& obj);
	friend ostream& operator<<(ostream& os, const Contact& obj);
	friend iostream& operator>>(iostream& is, Contact& obj);
	//get
	int get_id()const;
	const char* get_name()const;
	const char* get_midl_name()const;
	const char* get_adress()const;
	int get_number_phone()const;
	//set
	void set_id(int id_);
	void set_name(const char* name_);
	void set_midl_name(const char* midl_name_);
	void set_adress(const char* adress_con_);
	void set_number_phone(int number_phone_);
	//function
	void Fill_contacts();
	void print_contact()const;
	void save_data_bin(fstream& fs)const;
	void load_data_bin(fstream& fs);
};
