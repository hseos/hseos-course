#include <iostream>

using namespace std;

int f(int &&a)
{
    cout << __PRETTY_FUNCTION__ << endl;
}

int f(int &a)
{
    cout << __PRETTY_FUNCTION__ << endl;
}

int f(const int &a)
{
    cout << __PRETTY_FUNCTION__ << endl;
}

int main()
{
    f(6);
    const int x = 10;
    f(x);
    int y = 10;
    f(y);
}
