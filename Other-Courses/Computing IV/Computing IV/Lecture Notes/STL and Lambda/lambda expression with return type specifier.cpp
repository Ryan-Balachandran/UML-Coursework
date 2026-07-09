// lambdareturn.cpp -- demonstrate return type specifier in lambda expression

#include <iostream>

using std::cout;
using std::endl;

int f()
{
    return 3.14149;
}

auto g = []() -> int { if (f() >= 3) return 3.14159; else return 0; };

int main()
{
    std::cout << f() << std::endl;
    
    cout << g() << endl;
    
    return 0;
}
