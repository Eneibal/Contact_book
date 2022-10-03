#include "Book.h"

Book::Book() = default;

Book::Book(const char* book_)
{
	name_book = _strdup(book_);
}

Book::Book(const Book& obj)
{
	size_contact = obj.size_contact;
	name_book = obj.name_book ? _strdup(obj.name_book) : nullptr;

	contact_arr = new Contact[size_contact];
	for (int i = 0; i < size_contact; i++)
	{
		contact_arr[i] = obj.contact_arr[i];
	}	
}

Book::Book(Book&& obj)
{
	size_contact = obj.size_contact;
	name_book = obj.name_book ? _strdup(obj.name_book) : nullptr;
	contact_arr = obj.contact_arr;

	obj.size_contact = 0;
	obj.name_book = nullptr;
	obj.contact_arr = nullptr;
}

Book::~Book()
{
	delete[]name_book;
	if (size_contact)
	{
		delete[]contact_arr;
	}
}

int Book::get_size_book() const
{
	return size_contact;
}

const char* Book::get_name_book() const
{
	return name_book;
}

void Book::set_name_book(const char* name_book_)
{
	delete[]name_book;
	name_book = _strdup(name_book_);
}

Book& Book::operator=(const Book& obj)
{
	if (this == & obj)
	{
		return *this;
	}
	if (size_contact)
	{
		delete[]contact_arr;
	}
	name_book = obj.name_book ? _strdup(obj.name_book) : nullptr;
	size_contact = obj.size_contact;

	contact_arr = new Contact[size_contact];
	for (int i = 0; i < size_contact; i++)
	{
		contact_arr[i] = obj.contact_arr[i];
	}
	return *this;
}

Book& Book::operator=(Book&& obj)
{
	if (this == &obj)
	{
		return *this;
	}
	if (size_contact)
	{
		delete[]contact_arr;
	}

	size_contact = obj.size_contact;
	name_book = obj.name_book ? _strdup(obj.name_book) : nullptr;
	contact_arr = obj.contact_arr;

	obj.size_contact = 0;
	obj.name_book = nullptr;
	obj.contact_arr = nullptr;

	return *this;
}

void Book::add_contact()
{
	if (size_contact == 0)
	{
		contact_arr = new Contact[1];
	}
	else
	{
		auto tmp = new Contact[size_contact + 1]{};
		for (int i = 0; i < size_contact; i++)
		{
			tmp[i] = contact_arr[i];
		}
		delete[]contact_arr;
		contact_arr = tmp;
	}
	if (name_book == nullptr)
	{
		// цю перевірку я зробив для того, 
		//що книгу можно створити без name_book 
		//і визвати метод добавити контакта,і якщо 
		//не має назви то при print буде помилка
		cout << "Enter name Book !" << endl;
		char buf[500];
		cin.getline(buf, 500);
		set_name_book(buf);
	}
	contact_arr[size_contact].Fill_contacts();
	size_contact++;
}

void Book::add_contact(int id_, const char* name_, const char* midl_name_, const char* adress_, int number_phone_)
{
	if (size_contact == 0)
	{
		contact_arr = new Contact[1];
	}
	else
	{
		auto tmp = new Contact[size_contact + 1]{};
		for (int i = 0; i < size_contact; i++)
		{
			tmp[i] = contact_arr[i];
		}
		delete[]contact_arr;
		contact_arr = tmp;
	}
	if (name_book == nullptr)
	{
		// цю перевірку я зробив для того, 
		//що книгу можно створити без name_book 
		//і визвати метод добавити контакта,і якщо 
		//не має назви то при print буде помилка
		cout << "Enter name Book !" << endl;
		char buf[500];
		cin.getline(buf, 500);
		set_name_book(buf);
	}
	contact_arr[size_contact].set_id(id_);
	contact_arr[size_contact].set_name(name_);
	contact_arr[size_contact].set_midl_name(midl_name_);
	contact_arr[size_contact].set_adress(adress_);
	contact_arr[size_contact].set_number_phone(number_phone_);
	size_contact++;
}

void Book::del_contact_id(int size_contact_)
{
	if (size_contact == 1)
	{
		delete[]contact_arr;
		size_contact = 0;
		return;
	}
	auto tmp = new Contact[--size_contact]{};
	for (int i = 0,j=0; i < size_contact; i++,j++)
	{
		if (j == size_contact_)
		{
			j++;
		}
		tmp[i] = contact_arr[j];
	}
	delete[]contact_arr;
	contact_arr = tmp;
}

void Book::print() const
{
	cout << "~~~~~~~~ Book ~~~~~~~~" << endl;
	cout << "Name -> " << (name_book ? name_book : "Noname") << endl;
	for (int i = 0; i < size_contact; i++)
	{
		contact_arr[i].print_contact();
	}	
}

void Book::save_data_bin(fstream& fs) const
{
	fs.write((char*)&size_contact, sizeof(int));
	
	int len = strlen(name_book) + 1;
	fs.write((char*)&len, sizeof(int));
	fs.write(name_book, sizeof(char) * len);

	for (int i = 0; i < size_contact; i++)
	{
		//варіант 1 // variant 1 short
		//contact_arr[i].save_data_bin(fs);

		//Варіант 2 // variant 2
		int tmp;
		char* buf;
		int len;		
		//id
		tmp = contact_arr[i].get_id();
		fs.write((char*)&tmp, sizeof(int));
		//name
		buf =_strdup(contact_arr[i].get_name());
		len = strlen(buf)+1;
		fs.write((char*)&len, sizeof(int));
		fs.write(buf,sizeof(char)*len);
		//midl_name
		buf = _strdup(contact_arr[i].get_midl_name());
		len = strlen(buf) + 1;
		fs.write((char*)&len, sizeof(int));
		fs.write(buf, sizeof(char) * len);
		//adress
		buf = _strdup(contact_arr[i].get_adress());
		len = strlen(buf) + 1;
		fs.write((char*)&len, sizeof(int));
		fs.write(buf, sizeof(char) * len);
		//number_phone
		tmp = contact_arr[i].get_number_phone();
		fs.write((char*)&tmp, sizeof(int));

		delete[]buf;
	}
}

void Book::load_data_bin(fstream& fs)
{
	delete[]name_book;
	int len = 0;

	fs.read((char*)&size_contact, sizeof(int));

	fs.read((char*)&len, sizeof(int));
	name_book = new char[len];
	fs.read(name_book, sizeof(char) * len);

	contact_arr = new Contact[size_contact];
	for (int i = 0; i < size_contact; i++)
	{
		////Варіант 1	variant 1
		//contact_arr[i].load_data_bin(fs);
		//Варіант 2 // variant 2
		int tmp;
		char* buf;
		//Id
		fs.read((char*)&tmp, sizeof(int));
		contact_arr[i].set_id(tmp);
		//name
		fs.read((char*)&len, sizeof(int));
		buf = new char[len];
		fs.read(buf, sizeof(char) * len);
		contact_arr[i].set_name(buf);
		//midl_name
		fs.read((char*)&len, sizeof(int));
		buf = new char[len];
		fs.read(buf, sizeof(char) * len);
		contact_arr[i].set_midl_name(buf);
		//addres
		fs.read((char*)&len, sizeof(int));
		buf = new char[len];
		fs.read(buf, sizeof(char) * len);
		contact_arr[i].set_adress(buf);
		//number_pone
		fs.read((char*)&tmp, sizeof(int));
		contact_arr[i].set_number_phone(tmp);

		delete[]buf;
	}
}

void Book::save_data_txt(fstream& os) const
{
	char* buf;
	int tmp = 0;
	os << name_book << ", ";
	os << size_contact << ", " << endl;
	for (int i = 0; i < get_size_book(); i++)
	{
		tmp = contact_arr[i].get_id();
		os << tmp << ", ";

		buf = _strdup(contact_arr[i].get_name());
		os << buf << ", ";

		buf = _strdup(contact_arr[i].get_midl_name());
		os << buf << ", ";

		buf = _strdup(contact_arr[i].get_adress());
		os << buf << ", ";

		tmp = contact_arr[i].get_number_phone();
		os << tmp << ", ";
		os << endl;
	}
}

void Book::load_data_txt(fstream& fs)
{
	string buf;
	getline(fs, buf, ',');
	set_name_book(buf.c_str());

	getline(fs, buf, ',');
	size_contact = stoi(buf);

	contact_arr = new Contact[size_contact];
	for (int i = 0; i < size_contact; i++)
	{
		//id
		getline(fs, buf, ',');
		contact_arr[i].set_id(stoi(buf));
		//name
		getline(fs, buf, ',');
		contact_arr[i].set_name(buf.c_str());
		//midl_name
		getline(fs, buf, ',');
		contact_arr[i].set_midl_name(buf.c_str());
		//adres
		getline(fs, buf, ',');
		contact_arr[i].set_adress(buf.c_str());
		//Numberphone
		getline(fs, buf, ',');
		contact_arr[i].set_number_phone(stoi(buf));
	}
}

void Book::save_data_csv(fstream& os) const
{	
	char* buf;
	int tmp = 0;
	os << name_book << "; ";
	os << size_contact << "; " << endl;
	for (int i = 0; i < get_size_book(); i++)
	{
		tmp = contact_arr[i].get_id();
		os << tmp << "; ";

		buf = _strdup(contact_arr[i].get_name());
		os << buf << "; ";

		buf = _strdup(contact_arr[i].get_midl_name());
		os << buf << "; ";

		buf = _strdup(contact_arr[i].get_adress());
		os << buf << "; ";

		tmp = contact_arr[i].get_number_phone();
		os << tmp << "; ";
		os << endl;
	}
}

void Book::load_data_csv(fstream& fs)
{
	string buf;
	getline(fs, buf, ';');
	set_name_book(buf.c_str());

	getline(fs, buf, ';');
	size_contact = stoi(buf);

	contact_arr = new Contact[size_contact];
	for (int i = 0; i < size_contact; i++)
	{
		//id
		getline(fs, buf, ';');
		contact_arr[i].set_id(stoi(buf));
		//name
		getline(fs, buf, ';');
		contact_arr[i].set_name(buf.c_str());
		//midl_name
		getline(fs, buf, ';');
		contact_arr[i].set_midl_name(buf.c_str());
		//adres
		getline(fs, buf, ';');
		contact_arr[i].set_adress(buf.c_str());
		//Numberphone
		getline(fs, buf, ';');
		contact_arr[i].set_number_phone(stoi(buf));
	}
}

ostream& operator<<(ostream& os, const Book& obj)
{
	char* buf;
	int tmp = 0;
	os << obj.name_book << ", ";
	os << obj.size_contact<<", " << endl;
	for (int i = 0; i < obj.get_size_book(); i++)
	{
		tmp = obj.contact_arr[i].get_id();
		os << tmp << ", ";

		buf = _strdup(obj.contact_arr[i].get_name());
		os << buf << ", ";

		buf = _strdup(obj.contact_arr[i].get_midl_name());
		os << buf << ", ";

		buf = _strdup(obj.contact_arr[i].get_adress());
		os << buf << ", ";

		tmp = obj.contact_arr[i].get_number_phone();
		os << tmp << ", ";
		os << endl;
	}
	//delete[]buf;
	return os;
}

iostream& operator>>(iostream& is, Book& obj)
{
	string buf;
	getline(is, buf, ',');
	obj.set_name_book(buf.c_str());

	getline(is, buf,',');
	obj.size_contact = stoi(buf);

	obj.contact_arr = new Contact[obj.size_contact];
	for (int i = 0; i < obj.size_contact; i++)
	{
		//id
		getline(is, buf, ',');
		obj.contact_arr[i].set_id(stoi(buf));
		//name
		getline(is, buf, ',');
		obj.contact_arr[i].set_name(buf.c_str());
		//midl_name
		getline(is, buf, ',');
		obj.contact_arr[i].set_midl_name(buf.c_str());
		//adres
		getline(is, buf, ',');
		obj.contact_arr[i].set_adress(buf.c_str());
		//Numberphone
		getline(is, buf, ',');
		obj.contact_arr[i].set_number_phone(stoi(buf));
	}
	return is;
}
