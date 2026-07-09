// Example of exception handling
#include <iostream>
#include <string>
#include <exception>

using namespace std;

class MyException : public exception
{
public:
    MyException() : _message("MyException") {}
    MyException(string message) : _message(message) {}
    virtual const char* what() const noexcept override
    { return _message.c_str(); }
    
private:
    string _message;
};

void d(void)
{
    cout << "d(): Called\n";
    
    bool throwException = true; // change to true to throw the exception
    
    if (throwException)
    {
        cout << "d(): Throwing MyException\n";
        throw MyException("MyException from d()");
    }
    
    cout << "d(): Returning\n";
}


void c(void)
{
    cout << "c(): Calling d()\n";
    d();
    cout << "c(): Returning\n";
}


void b(void)
{
    cout << "b(): Calling c()\n";
    c();
    cout << "b(): Returning\n";
}


void a(void)
{
    try
    {
        cout << "a(): Calling b()\n";
        b();
        cout << "a(): Completed try block\n";
    }
    catch (MyException& e)
    {
        cout << "a(): Caught " << e.what() << endl;
    }
    
    cout << "a(): Returning\n";
}


int main()
{
    cout << "main(): Calling a()\n";
    a();
    cout << "main(): Returning\n";
    
    return 0;
}
