// stable_sort example
#include <iostream>     // std::cout
#include <algorithm>    // std::stable_sort
#include <vector>       // std::vector

using namespace std;

bool compare_as_ints(double i, double j)
{
    return (int(i)<int(j));
}

ostream& operator<< (ostream& os, vector<double>& v)
{
    for (vector<double>::iterator it = v.begin(); it != v.end(); ++it)
        cout << ' ' << *it;
    cout << '\n';
    
    return os;
}

int main()
{
    double mydoubles[] = { 3.14, 1.41, 2.72, 4.67, 1.73, 1.32, 1.62, 2.58 };
    
    vector<double> myvector;
    
    myvector.assign(mydoubles, mydoubles + 8);
    
    cout << "using default comparison :";
    stable_sort(myvector.begin(), myvector.end());
    cout << myvector;
    
    myvector.assign(mydoubles, mydoubles + 8);
    
    cout << "using 'compare_as_ints' :";
    stable_sort(myvector.begin(), myvector.end(), compare_as_ints);
    cout << myvector;
    
    myvector.assign(mydoubles, mydoubles + 8);
    
    cout << "using inline lambda expression :";
    stable_sort(myvector.begin(), myvector.end(), [](double a, double b) { return int(a) < int(b); });
    cout << myvector;
    
    myvector.assign(mydoubles, mydoubles + 8);
    
    auto descending = [](double a, double b) { return a > b; };
    
    cout << "using named lambda expression 'descending' :";
    stable_sort(myvector.begin(), myvector.end(), descending);
    cout << myvector;
    
    return 0;
}
