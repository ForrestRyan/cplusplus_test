#include <iostream>
#include <cstring>
using namespace std;

class MyString
{
public:
    MyString()
    : m_data(nullptr)
    {

    }

    //default constructor: deep copy
    explicit MyString(const char* str)
    {
        cout << "default constructor is called." << " str: " << str << endl;
        if(nullptr == str)
            str = "";

        size_t len = strlen(str);
        m_data = new char[len + 1];
        // strcpy_s(m_data, strlen(str)+1, str);
        // strcpy(m_data, str);
        memcpy(m_data, str, len);
        m_data[len+1] = '\0';
    }

    //copy constructor: deep copy
    MyString(const MyString& src)
    {
        cout << "copy constructor is called." << " str: " << src.m_data << endl;
        m_data = new char[strlen(src.m_data) + 1];
        strcpy_s(m_data, strlen(src.m_data)+1, src.m_data);
    }

#if 0
    //move constructor: shallow copy
    MyString(MyString&& src)
    {
        cout << "move constructor is called." << endl;
        m_data = src.m_data;
        src.m_data = nullptr;
    }
#endif

    //move constructor: shallow copy
    MyString(MyString&& src)
    :m_data(std::move(src.m_data))
    {
        cout << "move constructor is called." << " str: " << src << endl;
    }

    //copy assignment: deep copy
    MyString& operator=(const MyString& src)
    {
        cout << "copy assignment is called." << " str: " << src << endl;
        if(this == &src) // if both objects are the same, return directly
            return *this;

        if(m_data) // if current data is not empty, clear it first.
        {
            delete m_data;
            m_data = nullptr;
        }
        
        m_data = new char[strlen(src.m_data) + 1];
        strcpy_s(m_data, strlen(src.m_data)+1, src.m_data);

        return *this;
    }

    //copy assignment: shallow copy
    MyString& operator=(MyString&& src)
    {
        cout << "move assignment is called." << " str: " << src << endl;
        if(this == &src)
            return *this;
        
        if(m_data)
        {
            delete m_data;
            m_data == nullptr;
        }

        m_data = src.m_data;
        src.m_data = nullptr;

        return *this;
    }

    ~MyString()
    {
        cout << "destructor is called." << " str: " << m_data << endl;
        if(m_data != nullptr)
        {
            delete []m_data;
            m_data = nullptr;
        }
    }

    //operator override
    friend ostream& operator<<(ostream& out, const MyString& src)
    {
        out << "MyString is output: " << src.m_data << endl;
        return out;
    }

    //operator override
    friend istream& operator>>(istream& in, const MyString& src)
    {
        cout << "MyString is waiting for input from keyboard: ";
        in >> src.m_data;
        return in;
    }

    bool operator<(const MyString& rhs)
    {
        if(rhs.m_data == "")
            return false;
        
        return std::string(this->m_data) < std::string(rhs.m_data);
    }
    
    template<typename InputIterator, typename T>
    InputIterator find(InputIterator first, InputIterator last, const T& value)
    {
        while (first != last && *first != value)
            ++first;
        
        return first;
    }

public:
    char* m_data;
};