// Array-pointer equivalence in C/C++

#include <iostream>
#include <string>

int main()
{
  int a[3];

  a[0] = 10;     // normal array index operation
  *(a + 1) = 11; // equivalent pointer arithmetic operation - this is the default way to access an array element
  2[a] = 12;     // but this is also a valid array index operation! x[y] == *(x + y) == y[x]

  std::cout << "a[0] == " << a[0] << ", a[1] == " << a[1] << ", a[2] == " << a[2] << std::endl;
}
