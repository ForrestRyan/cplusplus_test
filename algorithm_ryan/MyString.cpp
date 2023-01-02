#include "MyString.h"

ostream& endl(ostream& out) // manipulator
{
    out.put('\n');
    out.flush();
    return out;
}


// ostream& ostream::operator<<(ostream& (*func)(ostream& ))
// {
//     return (*func)(*this);
// }

MyString getString(const char* str)
{
    MyString tmp(str); //default constructor
    return tmp; // move constructor
}

int main()
{
    cout << "hello world" << endl; //endl: '\n' and flush   // endl is an OBJECT? Build-in data type or function? Answer is function!

    MyString mystr_mv0("MOVE_0_TEST"); // default constructor
    MyString mystr_mv1("MOVE_1_TEST"); // default constructor
    MyString mystr("DEFAULT_TEST"); // default constructor

    MyString mystr1(mystr); // copy constructor 
    MyString mystr4 = mystr; // copy constructor 
    // MyString mystr2(getString("hello world")); // include move constructor, but due to compile optimization, we cant see the process
    MyString mystr3 = std::move(mystr_mv1); // move constructor

    mystr4 = mystr; //copy assignement
    mystr4 = static_cast<MyString&&>(mystr_mv0); //move assignment

    cout << mystr1 << mystr3 << mystr4;

#if 0
    cout << endl;
    cin>>mystr4;
    cout << mystr4;
#endif

    char element = 'T';
    char* iter = mystr.find<char*, char>(mystr.m_data, mystr.m_data+ strlen(mystr.m_data), element);
    if(*iter != '\0')
        cout << "MyString::find: the element " << *iter  << " is found" << endl << endl;
    else
        cout << "MyString::find: the element " << *iter  << " is not found! please check it." << endl << endl;

    return 0;
}
