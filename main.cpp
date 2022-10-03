#include <iostream>
#include"Book.h"
#include"Contact.h"
void Check_save_contact_bin()
{
    Contact a(23, "Vasy", "Pypkin", "Kyiv23", 435342), b;
    //cout << a << endl;
    b = a;
    //cout << b << endl;
    string bin_file = "contact.bin";

    fstream fs(bin_file, ios::out | ios::binary);
    if (fs.is_open())
    {
        a.save_data_bin(fs);
        fs.close();
    }
}
void Check_load_contact_bin()
{
    string bin_file = "contact.bin";
    Contact c(24, "Gor", "Foot", "Dubai", 42523), g;
    //cout << c << endl;
    fstream fs_1(bin_file, ios::in | ios::binary);
    if (fs_1.is_open())
    {
        g.load_data_bin(fs_1);
        fs_1.close();
    }
    //test
    //cout << c << endl;
    //cout << g << endl;
    //swap(c, g);
    //cout << g << endl;
}
void Check_save_book_Add()
{
    Book a("My book person");
    a.add_contact();
    a.add_contact(24, "Gor", "Foot", "Dubai", 42523);
    a.add_contact(646, "Vana", "Pypkin", "Nort", 3443);
    a.add_contact(245, "Fotman", "Gor", "Stranghold", 245232);
    //test
    //a.print();
    //a.del_contact_id(1);//++
    //a.print();
    string bin_fill_Bok = "Book.bin";//save
    fstream fs(bin_fill_Bok, ios::out | ios::binary);
    if (fs.is_open())
    {
        a.save_data_bin(fs);
        fs.close();
    }
}
void Check_Load_Book()
{
    string bin_fill_Bok = "Book.bin";
    Book b("New Book");
    //b.print();
    fstream fs_1(bin_fill_Bok, ios::in | ios::binary);//load
    if (fs_1.is_open())
    {
        b.load_data_bin(fs_1);
        fs_1.close();
    }
    //cout << "New BOOk Load data" << endl;
    b.print();
}
void Check_save_txt()
{
    string txt_f = "book_txt.txt";
    Book a_txt("Txt_Book");
    a_txt.add_contact(24, "Gor", "Foot", "Dubai", 42523);
    a_txt.add_contact(646, "Vana", "Pypkin", "Nort", 3443);
    a_txt.add_contact(245, "Fotman", "Gor", "Stranghold", 245232);
    fstream fs(txt_f, ios::out);
    if (fs.is_open())
    {
        fs << a_txt << endl;
        fs.close();
    }    
}
void Check_load_txt()
{
    Book c;
    string txt_f = "book_txt.txt";
    fstream fs_1(txt_f, ios::in);
    if (fs_1.is_open())
    {
        fs_1 >> c;
        fs_1.close();
    }
    //c.print();
}
void Check_save_csv()
{
    Book a("MyBook");
    a.add_contact(23, "Georgi", "Afro", "Kriv_Rig", 29395868);
    a.add_contact(4, "Tom", "Tomson", "UAS", 233415);
    a.add_contact(5, "Jer", "Jeroo", "Muvuk", 256734);
    //a.print();
    fstream fs;
    fs.open("txt.csv", ios::out);
    if (fs.is_open())
    {
        a.save_data_csv(fs);
        fs.close();
    }    
}
void Check_load_csv()
{
    fstream fs;
    Book c;
    fs.open("txt.csv", ios::in);
    if (fs.is_open())
    {
        c.load_data_csv(fs);
        fs.close();
    }    
    //c.print();
}
void Check_save_txt2()
{
    Book a("MyBook_txt2");
    a.add_contact(2423, "Georgghi", "Akfro", "Kriv_Rig", 29395868);
    a.add_contact(5254, "Tomss", "Tomumson", "USA", 233415);
    a.add_contact(566, "Jerew", "Jeroo", "Muvuk", 256734);
    fstream fs;
    fs.open("my_book_txt2.txt", ios::out);
    if (fs.is_open())
    {
        a.save_data_txt(fs);
        fs.close();
    }
    //a.print();   
}
void Check_load_txt2()
{
    fstream fs;
    Book c;
    fs.open("my_book_txt2.txt", ios::in);
    if (fs.is_open())
    {
        c.load_data_txt(fs);
        fs.close();
    }
    //c.print();
}
int main()
{
    //Check_save_contact_bin();
    //Check_load_contact_bin();
    //Check_save_book_Add();
    //Check_Load_Book();
    //Check_save_txt();
    //Check_load_txt();
    //Check_save_csv();
    //Check_load_csv();
    //Check_save_txt2();
    //Check_load_txt2();
}
