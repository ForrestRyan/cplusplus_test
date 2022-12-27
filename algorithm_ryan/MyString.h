#include <iostream>
#include <cstring>
using namespace std;

class MyString
{
public:
    explicit MyString(const char* str)
    {
        cout << "constructor is called." << endl;
        if(nullptr == str)
            str = "";

        m_str = new char[strlen(str) + 1];
        strcpy_s(m_str, strlen(str)+1, str);
    }

    MyString(const MyString& str)
    {
        m_str = new char[strlen(str.m_str) + 1];
        strcpy_s(m_str, strlen(str.m_str)+1, str.m_str);
    }

    MyString& operator=(const MyString& str)
    {
        if(this == &str)
            return *this;
        
        m_str = new char[strlen(str.m_str) + 1];
        strcpy_s(m_str, strlen(str.m_str)+1, str.m_str);

        return *this;
    }

    ~MyString()
    {
        if(m_str != nullptr)
        {
            delete []m_str;
            m_str = nullptr;
        }
    }

    friend ostream& operator<<(ostream& out, const MyString& str)
    {
        out << "MyString is output: " << str.m_str << endl;
        return out;
    }

    friend istream& operator>>(istream& in, const MyString& str)
    {
        cout << "MyString is waiting for input from keyboard: ";
        in >> str.m_str;
        return in;
    }



private:
    char* m_str;
};