// Examples of name & structural type equivalence in C/C++

#include <iostream>
#include <string>

typedef double myDouble1;

typedef double myDouble2;

typedef struct
{
    int foo;
    double bar;
} struct1;

typedef struct
{
    int foo;
    double bar;
} struct2;


void printStruct (struct1 s)
{
    std::cout << s.foo << ", " << s.bar << std::endl;;
}


int main()
{
    myDouble1 md1 = 1.0;
    myDouble2 md2;
    md2 = md1; // This is OK - structural equivalence used for scalar types!

    struct1 s1;

    s1.foo = 1;
    s1.bar = 3.14159;
    printStruct(s1);

    struct2 s2;

    s2.foo = 1;
    s2.bar = 3.14159;
    printStruct(s2); // This is an error - name equivalence used for structured types!
}
