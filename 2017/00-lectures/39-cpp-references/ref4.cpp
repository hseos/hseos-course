#include <iostream>
#include <utility>

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

// perfect forwarding
template<typename T>
int g(T && val)
{
    cout << __PRETTY_FUNCTION__ << endl;
    f(forward<T>(val));
}

template<typename C, typename T>
int fff(C z, T && t)
{
    z(forward<T>(t));
}

int main()
{
    f(6);
    const int x = 10;
    f(x);
    int y = 10;
    f(y);

    g(6);
    g(x);
    g(y);

    fff<int (int &&), int>(f, 6);
    //fff(g, x);
    //fff(f, y);
}
