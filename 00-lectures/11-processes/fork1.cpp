#include <iostream>
#include <unistd.h>

using namespace std;

int main(void)
{
  int pid;
  cout << "Hello, \n" ;;
  if ((pid = fork()) < 0) {
    cerr << "Err" << endl;
    return 1;
  } else if (!pid) {
    cout << "son" << endl;
  } else {
    cout << "parent" << endl;
  }
  return 0;
}
