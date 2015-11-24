#include <iostream>
#include <signal.h>
#include <stdlib.h>

using namespace std;

void fpehnd(int s)
{
    cerr << "division by 0" << endl;
    exit(1);
}

int main()
{
    signal(SIGFPE, fpehnd);
    int a, b;
    cin >> a >> b;
    cout << a / b << endl;
}
