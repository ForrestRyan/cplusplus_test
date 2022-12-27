#include "MyString.h"

int main()
{
    MyString mystr("hello world");
    cout << mystr;

    cout << endl;
    cin>>mystr;
    cout << mystr;
    return 0;
}