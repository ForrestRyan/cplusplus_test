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
    cout << "hello world" << endl; //endl: '\n' and flush
    // endl is an OBJECT? Build-in data type or function? Answer is function!

    MyString mystr0("hello"); // default constructor
    MyString mystr1(mystr0); // copy constructor 
    MyString mystr2 = mystr0; // copy constructor 
    mystr2 = mystr0; //copy assignement
    MyString mystr3(getString("hello world")); // include move constructor, but due to compile optimization, we cant see the process
    MyString mystr4 = std::move(mystr0); // move constructor
    cout << mystr1 << mystr2 << mystr3 << mystr4;

    cout << endl;
    cin>>mystr4;
    cout << mystr4;
    return 0;
}
