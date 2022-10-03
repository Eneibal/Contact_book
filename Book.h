#pragma once
#include"Contact.h"
class Book
{
	int size_contact = 0;
	char* name_book = nullptr;
	Contact* contact_arr = nullptr;
public:
	Book();
	Book(const char* book_);
	Book(const Book& obj);
	Book(Book&& obj);
	~Book();
	//get
	int get_size_book()const;
	const char* get_name_book()const;
	//set
	void set_name_book(const char* name_book_);
	//operator
	Book& operator=(const Book& obj);
	Book& operator=(Book&& obj);

	friend ostream& operator<<(ostream& os, const Book& obj);
	friend iostream& operator>>(iostream& is, Book& obj);
	// function
	void add_contact();
	void add_contact(int id_, const char* name_, const char* midl_name_, const char* adress_, int number_phone_);
	void del_contact_id(int size_contact_);
	void print()const;

	void save_data_bin(fstream& os)const;
	void load_data_bin(fstream& fs);

	void save_data_txt(fstream& os)const;
	void load_data_txt(fstream& fs);

	void save_data_csv(fstream& fs)const;
	void load_data_csv(fstream& fs);
};
