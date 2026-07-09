// Example of old-style (deprecated) throw specifier

#include <iostream>

void f1(void) throw(double)  // f1 promises to throw only a double
{
    if(true)
        throw 12.5;
}

int main()
{
    try
    {
        f1();
    }
    catch(int i)
    {
        std::cout << "int value " << i << " was thrown\n";
    }
    catch(double d)
    {
        std::cout << "double value " << d << " was thrown\n";
    }
    catch(...)
    {
        std::cout << "throw was executed\n";
    }
}
