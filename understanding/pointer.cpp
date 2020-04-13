#include <iostream>
#include <string>

using namespace std;

int change_variable(int *x){
    cout << "x=" << x << ", &x=" << &x << endl;
    // x contains the address of a

    *x += 1;

    cout << "x=" << x << ", &x=" << &x << endl;
    // x still contains the address of a
}

int main() {
  int a = 42;
  cout << "a=" << a << ", &a=" << &a << endl;
  int *p;
  cout << "p=" << p << ", &p=" << &p << endl;

  p = &a;
  cout << "p=" << p << ", &p=" << &p << endl;
  // p contains the address of a

  change_variable(p);

  cout << "p=" << p << ", &p=" << &p << endl;

  cout << "a=" << a << ", &a=" << &a << endl;

  return 0;
}