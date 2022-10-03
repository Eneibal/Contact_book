#include "Contact.h"

Contact::Contact() = default;

Contact::Contact(int id_, const char* name_,
	const char* midl_name_, const char* adress_con_,
	int number_phone_)
{
	//Варіант 1 // Varian 1
	id = id_;
	name = new char[strlen(name_) + 1] {};
	strcpy(name, name_);
	//короткий варіант 2 // variant 2 short
	midl_name= _strdup(midl_name_);
	adress_con = _strdup(adress_con_);
	number_phone = number_phone_;
}

Contact::Contact(const Contact& obj)//конструктор копіювання // constructor copy
{
	id = obj.id;
	if (obj.name)//спосіб перший // variant 1
	{
		name = new char[strlen(obj.name) + 1] {};
		strcpy(name, obj.name);
	}
	//короткий спосіб
	midl_name = obj.midl_name ? _strdup(obj.midl_name) : nullptr;// короткий спосіб 2 // variant 2 short
	adress_con = obj.adress_con ? _strdup(obj.adress_con) : nullptr;
	number_phone = obj.number_phone;
}

Contact::Contact(Contact&& obj)// конструктор переноса // constructor move
{
	swap(id, obj.id);
	swap(name, obj.name);
	swap(midl_name, obj.midl_name);
	swap(adress_con, obj.adress_con);
	swap(number_phone, obj.number_phone);
}

Contact::~Contact()
{
	delete[]name;
	delete[]midl_name;
	delete[]adress_con;
}

Contact& Contact::operator=(const Contact& obj)
{
	if (this == & obj)
	{
		return *this;
	}
	delete[]name;
	delete[]midl_name;
	delete[]adress_con;
	id = obj.id;
	name = _strdup(obj.name);
	midl_name = _strdup(obj.midl_name);
	adress_con = _strdup(obj.adress_con);
	number_phone = obj.number_phone;
	return *this;
}

Contact& Contact::operator=(Contact&& obj)
{
	if (this == &obj)
	{
		return *this;
	}
	delete[]name;
	delete[]midl_name;
	delete[]adress_con;

	id = obj.id;
	name = obj.name;
	midl_name = obj.midl_name;
	adress_con = obj.adress_con;
	number_phone = obj.number_phone;

	obj.id = 0;
	obj.name = nullptr;
	obj.midl_name = nullptr;
	obj.adress_con = nullptr;
	obj.number_phone = 0;

	return *this;
}

int Contact::get_id() const
{
	return id;
}

const char* Contact::get_name() const
{
	return name;
}

const char* Contact::get_midl_name() const
{
	return midl_name;
}

const char* Contact::get_adress() const
{
	return adress_con;
}

int Contact::get_number_phone() const
{
	return number_phone;
}

void Contact::set_id(int id_)
{
	id = id_;
}

void Contact::set_name(const char* name_)
{
	delete[]name;//варіант 1 // variant 1
	name = _strdup(name_);

	//strcpy(name, name_);// перезапитати як правильно //варіант 2 // variant 2 short
}

void Contact::set_midl_name(const char* midl_name_)
{
	delete[]midl_name;
	midl_name = _strdup(midl_name_);
}

void Contact::set_adress(const char* adress_con_)
{
	delete[]adress_con;
	adress_con = _strdup(adress_con_);
}

void Contact::set_number_phone(int number_phone_)
{
	number_phone = number_phone_;
}

void Contact::Fill_contacts()
{
	delete[]name;
	delete[]midl_name;
	delete[]adress_con;

	char buf[500];
	cout << "Enter id -> " << endl;
	cin >> id;
	cin.ignore();

	cout << "Enter name ->" << endl;
	cin.getline(buf, 500);
	name = new char[strlen(buf) + 1] {};
	strcpy(name, buf);

	cout << "Enter midl name - > " << endl;
	cin.getline(buf, 500);
	midl_name = _strdup(buf);

	cout << "Enter adress -> " << endl;
	cin.getline(buf,500	);
	adress_con = _strdup(buf);

	cout << "Enter number phone" << endl;
	cin >> number_phone;
	//cin.ignore(); ?????
}

void Contact::print_contact() const
{
	cout << "~~~~~~ Contact info ~~~~~~" << endl;
	cout << "Id - " << (id ? id :0) << endl;
	cout << "Name -> " << (name ? name : "Noname") << endl;
	cout << "Midl name -> " << (midl_name ? midl_name: "Noname") << endl;
	cout << "Adres -> " << (adress_con ? adress_con: "Unknow") << endl;
	cout << "Number phone -> " << (number_phone? number_phone : 0) << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}

void Contact::save_data_bin(fstream& fs) const
{
	fs.write((char*)&id, sizeof(int));

	int len = strlen(name) + 1;
	fs.write((char*)&len, sizeof(int));
	fs.write(name, sizeof(char) * len);

	len = strlen(midl_name) + 1;
	fs.write((char*)&len, sizeof(int));
	fs.write(midl_name, sizeof(char) * len);

	len = strlen(adress_con) + 1;
	fs.write((char*)&len, sizeof(int));
	fs.write(adress_con, sizeof(char) * len);

	fs.write((char*)&number_phone, sizeof(int));
}

void Contact::load_data_bin(fstream& fs)
{
	delete[]name;
	delete[]midl_name;
	delete[]adress_con;

	int len = 0;

	fs.read((char*)&id, sizeof(int));

	fs.read((char*)&len, sizeof(int));
	name = new char[len];
	fs.read(name, sizeof(char) * len);

	fs.read((char*)&len, sizeof(int));
	midl_name = new char[len];
	fs.read(midl_name, sizeof(char) * len);

	fs.read((char*)&len, sizeof(int));
	adress_con = new char[len];
	fs.read(adress_con, sizeof(char) * len);

	fs.read((char*)&number_phone, sizeof(int));
}

ostream& operator<<(ostream& os, const Contact& obj)
{
	os << obj.id << ", " << 
		obj.name << ", " <<
		obj.midl_name << ", " << 
		obj.adress_con << ", " << 
		obj.number_phone;
	return os;
}

iostream& operator>>(iostream& is, Contact& obj)
{
	string buf;
	getline(is, buf);
	obj.id = stoi(buf);

	getline(is, buf, ',');
	strcpy(obj.name, buf.c_str());
	
	getline(is, buf, ',');
	strcpy(obj.midl_name, buf.c_str());

	getline(is, buf, ',');
	strcpy(obj.adress_con, buf.c_str());

	getline(is, buf);
	obj.number_phone = stoi(buf);

	return is;
	
}
