#include <iostream>

using namespace std;

int main()
{
    int a = 10;

    int &ra = a;            // lvalue reference
    const int &cra = a;     // const lvalue reference

    //int && rra = a;
    int &&rra = 10;
    int &&rrb = move(a);

    rrb += 10;

    const int &val = 10;
}
