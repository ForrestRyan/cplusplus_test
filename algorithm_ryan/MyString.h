#include <iostream>
#include <cstring>
using namespace std;

class MyString
{
public:
    //default constructor: deep copy
    explicit MyString(const char* str)
    {
        cout << "default constructor is called." << endl;
        if(nullptr == str)
            str = "";

        m_str = new char[strlen(str) + 1];
        strcpy_s(m_str, strlen(str)+1, str);
    }

    //copy constructor: deep copy
    MyString(const MyString& str)
    {
        cout << "copy constructor is called." << endl;
        m_str = new char[strlen(str.m_str) + 1];
        strcpy_s(m_str, strlen(str.m_str)+1, str.m_str);
    }

#if 0
    //move constructor: shallow copy
    MyString(MyString&& str)
    {
        cout << "move constructor is called." << endl;
        m_str = str.m_str;
        str.m_str = nullptr;
    }
#endif

    //move constructor: shallow copy
    MyString(MyString&& str)
    :m_str(std::move(str.m_str))
    {
        cout << "move constructor is called." << endl;
    }

    //copy assignment: deep copy
    MyString& operator=(const MyString& str)
    {
        cout << "copy assignment is called." << endl;
        if(this == &str)
            return *this;
        
        m_str = new char[strlen(str.m_str) + 1];
        strcpy_s(m_str, strlen(str.m_str)+1, str.m_str);

        return *this;
    }

    ~MyString()
    {
        cout << "destructor is called." << endl;
        if(m_str != nullptr)
        {
            delete []m_str;
            m_str = nullptr;
        }
    }

    //operator override
    friend ostream& operator<<(ostream& out, const MyString& str)
    {
        out << "MyString is output: " << str.m_str << endl;
        return out;
    }

    //operator override
    friend istream& operator>>(istream& in, const MyString& str)
    {
        cout << "MyString is waiting for input from keyboard: ";
        in >> str.m_str;
        return in;
    }

private:
    char* m_str;
};