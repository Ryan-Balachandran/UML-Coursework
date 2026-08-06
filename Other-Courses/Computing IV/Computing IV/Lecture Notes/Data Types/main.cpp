#include <iostream>
#include<string>
#include <vector>
using namespace std;

// Constants in the global or namespace scope (if not declared extern)
// have internal linkage

//The const keyword specifies that a variable's value is constant and
// tells the compiler to prevent the programmer from modifying it.
const double x = 3.2;

namespace A
{
    const double x = 5.0;
}

double fx() {return x;}
double fy() {return A::x;}

void f(const std::string& name, const int& x)
{
    std::cout << name << x << std::endl;
}

class Date
{
public:
    Date()
    {
        month = 0;
        day = 0;
        year = 0;
    }
    
    Date(int mn, int dy, int yr);
    int getMonth() const;     // A read-only function
    void setMonth(int mn);   // A write function; can't be const
    
private:
    int month;
    int day;
    int year;
};

Date::Date(int mn, int dy, int yr)
{
    this->month = mn;
    this->year = yr;
    this->day = dy;
}
int Date::getMonth() const
{
    return month;        // Doesn't modify anything
}
void Date::setMonth(int mn)
{
    month = mn;          // Modifies data member
}

//--------STATIC-----------------------

//static variables keep their values and are not destroyed even after they go out of scope
int generateID()
{
    static int s_id = 0;
    return ++s_id;
}


// Static member variables
// only single copy of the variable creates for all objects

// Static constants defined in class scope have external linkage,
// which means there should be one module where they are fully defined

class AA
{
public:
    static int s_value;
    static const double c;
    //static member function to access private statis members
    // Static member functions have no *this pointer
    static int getValue() { return a_value; } // inline implementation
    
private:
    static int a_value;
};

class B
{
public:
    static const double d;
};

int AA::s_value = 0;

const double AA::c = 1000.0;
const double B::d = AA::c;
const double div2 = B::d / 10.0;
int AA::a_value = 1;

//------------ constexpr  -----------------------//
//compile-time implementations of the Fibonacci sequence
constexpr unsigned fibonacci(unsigned i)
{
    return (i <= 1u) ? i : (fibonacci(i - 1) + fibonacci(i - 2));
}

class Point
{
    int x;
    int y;
public:
    constexpr Point(int ix, int iy) : x{ ix }, y{ iy } {}
    constexpr int getX() const { return x; }
    constexpr int getY() const { return y; }
};

std::string nonsense(char input)
{
    switch (input)
    {
        case "foobar"[(sizeof(void*) == 4) ? 0 : 1]:
            return "beef";
        default:
            return "lettuce";
    }
}

template <typename Any>
auto switch_(Any& a)
{
    return [&a](auto ...cases_)
    {
        auto cases = hana::make_tuple(cases_...);
        // ...
    };
}

class complex
{
    int a, b;
public:
    complex()
    {        }
    complex(int k)
    {
        a = k;
        b = 0;
    }
    void setdata(int x, int y)
    {
        a = x;
        b = y;
    }
    void showdata()
    {
        cout << "a:" << endl << a << endl << "b:" << b<<endl;
    }
};

int main(int argc, char** argv) {
    // -------- WIDE CHAR -------------//
    
    cout << "---------------Wide character--------------\n";
    wchar_t w = L'A';
    cout << "Wide character value:: " << w << endl;
    cout << "Size of the wide char is:: " << sizeof(w) << endl;
    //-----------------------------
    complex c1;
    int d = 5;//Basic data type
    c1 = d; //parametized constructer called(value of Basic type is assigned to class type
    c1.showdata();
    // --------AUTO ------------------------//
    
    auto i = 10; // i is int
    auto s = "hello world"; // s is char const*
    cout << s << endl;
    auto ss = "hello world"s; // ss is std::string
    cout << ss << endl;
    std::vector<double> vec;
    vec = { 2, 4, 6, 8, 10 };
    auto iter = vec.cbegin(); // iter is std::vector<double>::const_iterator
    
    // ------CONSTANT: -------------
    // variable
    
    const int ii = 5;
    // cannot do the next - error!
    // i = 10;
    // i++;
    
    const int maxarray = 255;
    char store_char[maxarray];
    
    // pointer
    char a = 'a';
    char ma = 'm';
    char *mybuf = &a;
    char *yourbuf = &ma;
    cout << "  *mybuf=" << *mybuf << "  &mybuf=" << &mybuf << endl;
    char *const aptr = mybuf;
    *aptr = 'b';   // OK
    cout << "  *mybuf=" << *mybuf << "   *aptr=" << *aptr << endl;
    // aptr = yourbuf;   // C3892  ERROR!!- pointer should be declare as a const
    //-----------------------------
    Date MyDate(7, 4, 1998);
    const Date BirthDate(1, 18, 1953);
    MyDate.setMonth(4);    // Okay
    cout << "month=" << BirthDate.getMonth() << endl;    // Okay
    
    // BirthDate.setMonth(4); // C2662 Error
    
    
    f("x: ", fx());
    f("myname: ", fx());
    f("y: ", fy());
    f("x: ", x);
    f("y: ", A::x);
    
    //-----------STATIC---------------
    // variable
    
    std::cout << generateID() << '\n';   //pints: 1
    std::cout << generateID() << '\n';   //pints: 2
    std::cout << generateID() << '\n';   //pints: 3
    // Static member variables
    AA first;
    AA second;
    first.s_value = 2;
    std::cout << "first.s_value =" << first.s_value << '\n';     //first.s_value =2
    std::cout << "second.s_value =" << second.s_value << '\n';  //second.s_value = 2
    
    std::cout << "AA::c =" << AA::c << std::endl;
    std::cout << "B::d =" << B::d << std::endl;
    std::cout << "div2 =" << div2 << std::endl;
    //std::cout << "AA::a_value ="<< AA::a_value<< std::endl;  // cannot access it is private
    std::cout << "AA::a_value =" << AA::getValue() << std::endl;  //Because static member functions
    // are not attached to a particular object,
    // they can be called directly by using the class name and the scope resolution operator
    
    //---------------------------------------------
    //----------------------------------------------
    
    char int_values[fibonacci(6)] = {};       //OK, 6 is a compile time constant
    std::cout << sizeof(int_values) << '\n';  //8
    
    std::cout << fibonacci(argc) << '\n';     //OK, run time calculation
    //std::cout << sizeof(std::array<char, fibonacci(argc)>) << '\n'; //ERROR
    //`argc` is not a compile time constant, neither is `fibonacci(argc)`
    
    constexpr Point p{ 22, 11 };
    constexpr int py = p.getY();
    double darr[py]{};
    
    std::cout << nonsense(4) << endl;
    std::cout << nonsense(0) << endl;
    
    //-------------AUTO -----------//
    std::vector<bool> vec1(10, 0);
    
    auto x = vec1[2];
    
    bool y = vec1[2];
    std::cout << "AUTO\n";
    std::cout << typeid(x).name() << "\n";
    std::cout << "x = " << x << endl;
    std::cout << typeid(y).name() << "\n\n";
    std::cout << "y = " << y << endl;
    return 0;
}
