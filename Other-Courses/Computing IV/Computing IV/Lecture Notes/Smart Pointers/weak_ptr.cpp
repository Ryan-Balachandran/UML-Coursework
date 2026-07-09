#include <iostream> // for std::cout, std::endl
#include <memory>   // for std::auto_ptr
using namespace std;

class Thing
{
public:
    void defrangulate();
};

class Parent;
class Child;

class Child
{
private:
    weak_ptr<Parent> pParent;
public:
    Child(shared_ptr<Parent> parent) : pParent(parent) {}
};

class Parent
{
private:
    shared_ptr<Child> pChild;
public:
    Parent()
    {
        pChild = shared_ptr<Child>(new Child(shared_ptr<Parent>(this)));
    }
};
//https://en.cppreference.com/w/cpp/memory/weak_ptr/lock
void observe(std::weak_ptr<int> weak)
{
    if (auto observe = weak.lock())
    {
        std::cout << "\tobserve() able to lock weak_ptr<>, value=" << *observe << "\n";
    }
    else
    {
        std::cout << "\tobserve() unable to lock weak_ptr<>\n";
    }
}
//--------------------------------------------------
//http://www.modernescpp.com/index.php/std-weak-ptr
struct Son;
struct Daughter;

struct Mother
{
    ~Mother()
    {
        std::cout << "Mother gone" << std::endl;
    }
    void setSon(const std::shared_ptr<Son> s)
    {
        mySon = s;
    }
    void setDaughter(const std::shared_ptr<Daughter> d)
    {
        myDaughter = d;
    }
    std::shared_ptr<const Son> mySon;
    std::weak_ptr<const Daughter> myDaughter;
};

struct Son
{
    Son(std::shared_ptr<Mother> m) :myMother(m) {}
    ~Son()
    {
        std::cout << "Son gone" << std::endl;
    }
    std::shared_ptr<const Mother> myMother;
};

struct Daughter
{
    Daughter(std::shared_ptr<Mother> m) :myMother(m) {}
    ~Daughter()
    {
        std::cout << "Daughter gone" << std::endl;
    }
    std::shared_ptr<const Mother> myMother;
};


int main()
{
    // init weak pointers
    shared_ptr<Thing> sp(new Thing);
    weak_ptr<Thing> wp1(sp); // construct wp1 from a shared_ptr
    weak_ptr<Thing> wp2; // an empty weak_ptr - points to nothing
    wp2 = sp; // wp2 now points to the new Thing
    weak_ptr<Thing> wp3(wp2); // construct wp3 from a weak_ptr
    weak_ptr<Thing> wp4;
    wp4 = wp2; // wp4 now points to the new Thing.
    //----------------------------------------------------------//
    // empty definition
    std::shared_ptr<int> sptr;
    
    // takes ownership of pointer
    sptr.reset(new int);
    *sptr = 10;
    
    // get pointer to data without taking ownership
    std::weak_ptr<int> weak1 = sptr;
    
    // deletes managed object, acquires new pointer
    sptr.reset(new int);
    *sptr = 5;
    
    // get pointer to new data without taking ownership
    std::weak_ptr<int> weak2 = sptr;
    
    // weak1 is expired!
    if (auto tmp = weak1.lock())    // lock() Creates a new std::shared_ptr that shares
        // ownership of the managed object
        std::cout << *tmp << '\n';
    else
        std::cout << "weak1 is expired\n";
    
    // weak2 points to new data (5)
    if (auto tmp = weak2.lock())
        std::cout << *tmp << '\n';
    else
        std::cout << "weak2 is expired\n";
    
    //https://en.cppreference.com/w/cpp/memory/weak_ptr/lock
    
    std::weak_ptr<int> weak;
    std::cout << "weak_ptr<> not yet initialized\n";
    observe(weak);
    
    {
        auto shared = std::make_shared<int>(42);
        weak = shared;
        std::cout << "weak_ptr<> initialized with shared_ptr.\n";
        observe(weak);
    }
    
    std::cout << "shared_ptr<> has been destructed due to scope exit.\n";
    observe(weak);
    //  cycle
    std::cout << std::endl;
    {
        std::shared_ptr<Mother> mother = std::shared_ptr<Mother>(new Mother);
        std::shared_ptr<Son> son = std::shared_ptr<Son>(new Son(mother));
        std::shared_ptr<Daughter> daughter = std::shared_ptr<Daughter>(new Daughter(mother));
        mother->setSon(son);
        mother->setDaughter(daughter);
    }
    std::cout << std::endl;
    
    return 0;
}
