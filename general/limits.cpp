/*
Show limits
 */
#include <climits>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
int main()
{
    cout << "type:char" << endl;
    cout << "bit:" << CHAR_BIT << endl;
    cout << "size:" << sizeof(char) << " byte" << endl;
    cout << "max:" << CHAR_MAX << endl;
    cout << "min:" << CHAR_MIN << endl
         << endl;
    cout << "type:signed char" << endl;
    cout << "size:" << sizeof(signed char) << " byte" << endl;
    cout << "max:" << SCHAR_MAX << endl;
    cout << "min:" << SCHAR_MIN << endl
         << endl;
    cout << "type:unsigned char" << endl;
    cout << "size:" << sizeof(unsigned char) << " byte" << endl;
    cout << "max:" << UCHAR_MAX << endl
         << endl;
    cout << "type:short" << endl;
    cout << "size:" << sizeof(short) << " byte" << endl;
    cout << "max:" << SHRT_MAX << endl;
    cout << "min:" << SHRT_MIN << endl
         << endl;
    cout << "type:unsigned short" << endl;
    cout << "size:" << sizeof(unsigned short) << " byte" << endl;
    cout << "max:" << USHRT_MAX << endl
         << endl;
    cout << "type:int" << endl;
    cout << "size:" << sizeof(int) << " byte" << endl;
    cout << "max:" << INT_MAX << endl;
    cout << "min:" << INT_MIN << endl
         << endl;
    cout << "type:unsigned int" << endl;
    cout << "size:" << sizeof(unsigned int) << " byte" << endl;
    cout << "max:" << UINT_MAX << endl
         << endl;
    cout << "type:long" << endl;
    cout << "size:" << sizeof(long) << " byte" << endl;
    cout << "max:" << LONG_MAX << endl;
    cout << "min:" << LONG_MIN << endl
         << endl;
    cout << "type:unsigned long" << endl;
    cout << "size:" << sizeof(unsigned long) << " byte" << endl;
    cout << "max:" << ULONG_MAX << endl
         << endl;
    cout << "type:long long" << endl;
    cout << "size:" << sizeof(long long) << " byte" << endl;
    cout << "max:" << LLONG_MAX << endl;
    cout << "min:" << LLONG_MIN << endl
         << endl;
    cout << "type:unsigned long long" << endl;
    cout << "size:" << sizeof(unsigned long long) << " byte" << endl;
    cout << "max:" << ULLONG_MAX << endl
         << endl;
    cout << "Press Enter to exit" << endl;
    cin.get();
    return 0;
}