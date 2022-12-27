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

int main()
{
    cout << "hello world" << endl; //endl: '\n' and flush
    // endl is an OBJECT? Build-in data type or function? Answer is function!


    MyString mystr("hello world");
    cout << mystr;

    cout << endl;
    cin>>mystr;
    cout << mystr;
    return 0;
}
