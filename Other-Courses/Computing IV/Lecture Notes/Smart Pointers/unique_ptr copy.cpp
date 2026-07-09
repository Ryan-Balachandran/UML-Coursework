#include <iostream>
#include <memory>
using namespace std;

class Integer
{
public:
    Integer(int i = 0); // Integer default constructor
    ~Integer(); // Integer destructor
    void setInteger(int i); // set Integer value
    int getInteger() const; // return Integer value
private:
    int value;
};
// Integer default constructor
Integer::Integer(int i): value{ i }
{
    cout << "Constructor for Integer " << value << endl;
    }
    
    // Integer destructor
    Integer::~Integer()
    {
        cout << "Destructor for Integer " << value << endl;
    }
    
    // set Integer value
    void Integer::setInteger(int i)
    {
        value = i;
    }
    
    // return Integer value
    int Integer::getInteger() const
    {
        return value;
    }
    
    
    int main()
    {
        // https://www.assignmentexpert.com/blog/catching-memory-allocation-bugs-how-to-use-smart-pointers-in-c/
        
        std::unique_ptr<int> up(new int(45));
        std::cout << "up contains the following data: " << *up << std::endl;
        std::unique_ptr<int> up2(std::move(up));
        std::cout << "up2 contains the following data: " << *up2 << std::endl;
        if (up) {
            
            std::cout << "up now contains the following data: " << *up << std::endl;
        }
        else
        {
            std::cout << "up is empty" << std::endl;
        }
        // output
        // up contains the following data: 45
        // up2 contains the following data : 45
        //    up is empty
        //-----------------------------------------------------------
        cout << "Creating a unique_ptr object that points to an Integer\n";
        
        // "aim" unique_ptr at Integer object
        unique_ptr<Integer> ptrToInteger{ make_unique<Integer>(7) };
        
        cout << "\nUsing the unique_ptr to set the Integer\n";
        ptrToInteger->setInteger(99); // use unique_ptr to set Integer value
        // before C++14: pass the result of "new" directly to unique_ptr's constr
        // C++14 use "make_unique(): allocate memory with "new" then returns
        // unique_ptr to that memory
        
        // use unique_ptr to get Integer value
        cout << "Integer after setInteger: " << (*ptrToInteger).getInteger()
        << "\n\nTerminating program" << endl;
        return 0;
    }
