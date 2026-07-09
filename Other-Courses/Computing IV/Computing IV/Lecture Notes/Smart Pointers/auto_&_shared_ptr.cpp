#include <iostream> // for std::cout, std::endl
#include <memory>   // for std::auto_ptr
#include <cstdlib> // for EXIT_SUCCESS
#include <vector>

using namespace std;
shared_ptr<int> clone(int p)
{
    // ok: explicitly create a
    // shared_ptr<int> from int*
    return shared_ptr<int>(new int(p));
}
shared_ptr<int> p(new int(42));


// cleanup is automatic
// shared_ptr that can point at a// double
shared_ptr<int> p2(new int(42));// p2 points to an int with value 42

//------- intro to auto_ptr --------------------- //
void Leaky()
{
    int *x = new int(5); // heap allocated
    (*x)++;
    std::cout << *x << std::endl;
}
void NotLeaky()
{
    std::auto_ptr<int> x(new int(5)); // wrapped, heap-allocated
    (*x)++;
    std::cout << *x << std::endl;
}
//------------------- auto_ptr operations -------- //
typedef struct
{
    int a, b;
} IntPair;
//------------------------------------------------//
shared_ptr<int> f(shared_ptr<int> x)
{
    auto p = make_shared<int>(55);
    
    cout << "In function f: *x == " << *x
    << ", x.use_count() == " << x.use_count() << endl << endl;
    
    return p; // makes a copy of p
}

class MyClass
{
public:
    MyClass()
    {
        cout << "Creating MyClass object" << endl;
    }
    
    virtual ~MyClass()
    {
        cout << "Destroying MyClass object" << endl;
    }
    
    void method()
    {
        cout << "Called method of MyClass object" << endl;
    }
};

shared_ptr<MyClass> returnTest()
{
    shared_ptr<MyClass> m(new MyClass);
    m->method();
    return m;
}


int main(void)
{
    // The following two declarations are similar, but not equivalent.
    // See the "Notes" section in the following reference
    // for a discussion of the trade-offs:
    // <https://en.cppreference.com/w/cpp/memory/shared_ptr/make_shared>
    
    //--------- why do use smart ptr ------------------//
    Leaky();
    NotLeaky();
    //------------------- auto_ptr operations -------- //
    auto_ptr<int> x(new int(5));
    // Return a pointer to the pointed-to object.
    int *ptr = x.get();
    // Return a reference to the value of the pointed-to object.
    int val = *x;
    // Access a field or function of a pointed-to object.
    auto_ptr<IntPair> ip(new IntPair);
    ip->a = 100;
    // Reset the auto_ptr with a new heap-allocated object.
    x.reset(new int(1));
    // Release responsibility for freeing the pointed-to object.
    ptr = x.release();
    delete ptr;
    //-----------------------------------------------//
    //-----------------------------------------------//
    std::shared_ptr<int> sp = make_shared<int>(45);
    std::cout << "sp pointer is used " << sp.use_count() << " times" << std::endl;
    std::shared_ptr<int> sp2 = sp;
    std::cout << "Now sp pointer is used " << sp.use_count() << " times" << std::endl;
    //------------------------------------------
    shared_ptr<int> q(new int(21)); // use value constructor
    auto r = make_shared<int>(42);  // use make_shared function
    
    cout << "After declarations:\n";
    cout << "*q == " << *q << ", *r == " << *r << endl;
    cout << "q.use_count() == " << q.use_count()
    << ", r.use_count() == " << r.use_count() << endl << endl;
    
    r = q;
    
    cout << "After assignment r=q:\n";
    cout << "*q == " << *q << ", *r == " << *r << endl;
    cout << "q.use_count() == " << q.use_count()
    << ", r.use_count() == " << r.use_count() << endl << endl;
    
    auto y = f(q); // call-by-value and return-by-value with shared pointers
    
    cout << "After call to function f:\n";
    cout << "*y == " << *y << ", y.use_count() == " << y.use_count() << endl;
    cout << "*q == " << *q << ", *r == " << *r << endl;
    cout << "q.use_count() == " << q.use_count()
    << ", r.use_count() == " << r.use_count() << endl << endl;
    
    // A deleter is a callable object (in this case, a lambda expression)
    // that takes a single parameter which is of the underlying pointer type
    // of the shared pointer.
    auto myDeleter = [](int* x)
    { cout << "Shared pointer is being destroyed! (int value == " << *x << ")\n";
        delete x; };
    
    // Here we use the explicit deleter so that we can see the shared pointer
    // being destroyed!
    // Allocate the underlying pointer using new; destroy using the deleter...
    shared_ptr<int> s(new int(99), myDeleter);
    //-----------------------------------Class --------------//
    shared_ptr<MyClass> m2 = returnTest();
    m2->method();
    MyClass& a = *m2;
    cout << "m2 use_count = " << m2.use_count() << endl;
    shared_ptr<MyClass> m22(m2);
    cout << endl << "After creating m22:" << endl;
    cout << "m2 use_count = " << m2.use_count() << endl;
    cout << "m22 use_count = " << m22.use_count() << endl;
    m2.reset();
    cout << endl << "After reset:" << endl;
    cout << "m2 use_count = " << m2.use_count() << endl;
    cout << "m22 use_count = " << m22.use_count() << endl;
    
    cout << "main() is exiting...\n\n";
    
    return EXIT_SUCCESS;
}

