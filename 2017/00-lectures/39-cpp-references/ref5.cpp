#include <iostream>
#include <utility>

using namespace std;
void f(int a, double &&b)
{
    cout << __PRETTY_FUNCTION__ << endl;
}

void f(int a, double &b)
{
    cout << __PRETTY_FUNCTION__ << endl;
}

void f(int a, const double &b)
{
    cout << __PRETTY_FUNCTION__ << endl;
}

void f(int &&a)
{
    cout << __PRETTY_FUNCTION__ << endl;
}

void f(int &a)
{
    cout << __PRETTY_FUNCTION__ << endl;
}

void f(const int &a)
{
    cout << __PRETTY_FUNCTION__ << endl;
}

template<typename ...T>
void g(T && ... p)
{
    f(forward<T>(p)...);
}

template <typename C, typename ...T>
void fff(C && c, T && ... p)
{
    c(forward<T>(p)...);
}

int main()
{
    double x = 1.0;
    const double y = 2.0;

    f(10, 3.3);
    f(12, x);
    f(14, y);

    int a = 10;
    const int b = 11;
    f(a);
    f(b);
    f(100);

    g(10, 3.3);
    g(12, x);
    g(14, y);
    g(a);
    g(b);
    g(100);
    
    fff<void (int, double &&)>(f, 10, 15.0);
   
}
