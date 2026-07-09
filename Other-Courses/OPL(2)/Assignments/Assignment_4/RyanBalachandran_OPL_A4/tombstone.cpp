#include <iostream>
#include <stdlib.h>
#include "tombstones.h"     // Header file for your Pointer class (tombstones implementation)
using namespace std;

class testclass
{
public:
    int a;
    float b;
    testclass(int x, float y) : a(x), b(y) {}
};

void error(const char *text)
{
    cout << "ERROR: " << text << endl;
    exit(-1);
}

// Driver program for the Pointer class (tombstones implementation)
int main()
{
    cout << "***************************************************" << endl;
    Pointer<int> ptr(new int(12));      // bootstrap constructor
    Pointer<int> tmp((int*)NULL);       // default constructor
    Pointer<int> bar = tmp;             // assignment operator

    if (ptr == 0)
    {
        cout << "ERROR 1: ";
        error("ptr should not be null!");
    }

    if (bar != 0)
    {
        cout << "ERROR 2: ";
        error("bar should be null!");
    }

    bar = new int(12);
    if (ptr == bar)
    {
        cout << "ERROR 3: ";
        error("ptr and bar should refer to distinct objects!");
    }

    if (*ptr != *bar)
    {
        cout << "ERROR 4: ";
        error("*ptr and *bar should have the same value!");
    }

    cout << "*ptr == " << *ptr << ", *bar == " << *bar << " (both should be 12)\n";

    free(ptr);
    free(bar);
    cout << "free is OK" << endl;
    cout << "***************************************************" << endl << endl;




    cout << "***************************************************" << endl;
    Pointer<int> valCheck;        // default constructor
    valCheck = new int(12);       // assignment operator
    Pointer<int> copy(valCheck);  // copy constructor

    if (copy == 0)
    {
        cout << "ERROR 5: ";
        error("copy should not be null!");
    }

    if (*copy != 12)
    {
        cout << "ERROR 6: ";
        error("copy is the wrong value!");
    }

    if (valCheck != copy)
    {
        cout << "ERROR 7: ";
        error("valcheck and copy should refer to the same object!");
    }

    if (*valCheck != *copy)
    {
        cout << "ERROR 8: ";
        error("*valcheck and *copy are supposed to have the same value!");
    }

    *valCheck = 15;
    if (*copy != 15)
    {
        cout << "ERROR 9: ";
        error("valcheck and copy should still match here!");
    }

    Pointer<testclass> tc(new testclass(14, 3.14159));
    cout << "tc->a == " << tc->a << ", tc->b == " << tc->b << " (should be 14 and 3.14159)\n\n";

    cout << "About to use the free() friend function - beware of SEGFAULTs...\n";
    cout << "***************************************************" << endl << endl;

    free(valCheck);
    free(copy);
    cout << "Free is OK" << endl;
    cout << "***************************************************" << endl << endl;




    cout << "***************************************************" << endl;
    Pointer<int> freeSegfaultTest;
    free(freeSegfaultTest);         // should be null pointer
    cout << "free() did not cause a SEGFAULT (which is good)!\n\n";

    cout << "About to dereference the freed Pointer...\n"
    << "(this should cause an error message about a dangling pointer\n"
    << "or memory leak, and terminate this driver program!)\n\n";

    int i = *freeSegfaultTest; // should cause a dangling pointer error message
    // and terminate this driver program
    cout << "***************************************************" << endl;

    cout << "ERROR 10: Tests complete, but dangling pointer was NOT detected!" << endl;
    return 0;
}
