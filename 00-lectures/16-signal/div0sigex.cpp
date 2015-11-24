#include <iostream>
#include <signal.h>
#include <stdlib.h>
#include <stdexcept>

using namespace std;

void fpehnd(int s)
{
    cerr << "division by 0" << endl;
    throw runtime_error("division by 0");
}

int main()
{
    signal(SIGFPE, fpehnd);
    while (1) {
        try {
            int a, b;
            cin >> a >> b;
            cout << a / b << endl;
        } catch (const runtime_error &e) {
            signal(SIGFPE, fpehnd);
            cerr << "exception caught: " << e.what() << endl;
        }
    }
}
