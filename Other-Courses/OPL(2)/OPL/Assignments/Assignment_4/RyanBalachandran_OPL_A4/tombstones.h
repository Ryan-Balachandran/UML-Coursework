#ifndef tombstones_h
#define tombstones_h

#include <iostream>
#include <stdlib.h>
using namespace std;

void DR_error()
{
    cout << "########################################" << endl;
    cout << "# ERROR: Dangling Reference Exception! #" << endl;
    cout << "########################################" << endl;

    exit(-1);
}

void ML_error()
{
    cout << "##########################" << endl;
    cout << "# Memory Leak Exception! #" << endl;
    cout << "##########################" << endl;

    exit(-1);
}


// Class to represent a tombstone
template <class T> class Tombstone
{
public:
    int reference_count;    // reference counting for the Tombstone
    T* value;               // pointer of value to actual address
    bool rip;               // boolean to check whether the tombstone is still in use or not

    Tombstone<T>()          // Default Constructor to initialize tombstone
    {
        cout << "Tombstone default constructor" << endl << endl;

        reference_count = 0;
        value = NULL;
        rip = false;
    }

    Tombstone<T>(T* ptr)    // Bootstrapping Constructor
    {
        cout << "Tombstone bootstrapping constructor" << endl << endl;

        reference_count = 1;
        value = ptr;
        rip = false;
    }
};


// Pointer Class
template <class T>
class Pointer
{
public:
    Tombstone <T> *ptr;     // initialized a pointer to the tombstone

    // Default Constructor; constructs NULL pointer
    Pointer<T>()
    {
        cout << "Default Pointer Constructor" << endl;
        ptr = new Tombstone<T>();
        ptr->rip = true;    // not in use when initialized
    }

    // Copy Constructor
    Pointer<T>(Pointer<T>& object)
    {
        cout << "Copy Pointer Constructor" << endl;

        // object is a reference of Pointer<T>
        if(object.ptr->rip)
        {
            cout << "DR Error in copy constructor" << endl;
            DR_error();     // if tombstone of object is not in use, that means we are accessing a dangling reference
        }

        ptr = object.ptr;
        ptr->reference_count++;
    }

    // Bootstrapping Constructor; value constructor
    Pointer<T>(T* object)
    {
        cout << "Bootstrapping Pointer Constructor" << endl;

        // argument should always be a call to new
        ptr = new Tombstone<T>(object);
    }

    // Destructor
    ~Pointer<T>()
    {
        cout << "Pointer Destructor" << endl;

        ptr->reference_count--;  // only delete one pointer

        if(ptr->reference_count == 0 && !ptr->rip)
        {
            cout << "ML Error in pointer destructor" << endl;
            ML_error();     // if the reference counting is 0 and rip is false, that means we have a memory leak exception
        }

        ptr = NULL;
    }

    // Dereferencing
    T& operator*() const
    {
        // cout << "Dereferencing: ";

        if(ptr->reference_count == 0)
        {
            cout << "ML Error in Dereferencing" << endl;
            ML_error();     // usually when reference counting reaches to 0, we are going to run into memory leak excetion
        }
        else if(ptr->rip == true)
        {
            cout << "DR Error in Dereferencing" << endl;
            DR_error();     // if rip is true, then it's a dangling reference exception
        }

        return *(ptr->value);   // otherwise return the actual value
    }

    // Field Dereferencing
    T* operator->() const
    {
        // cout << "Field Dereferencing: ";

        if(ptr->reference_count == 0)
        {
            cout << "ML Error in Field Dereferencing" << endl;
            ML_error();     // usually when reference counting reaches to 0, we are going to run into memory leak excetion
        }
        else if(ptr->rip == true)
        {
            cout << "DR Error in Field Dereferencing" << endl;
            DR_error();     // if rip is true, then it's a dangling reference exception
        }

        return ptr->value;      // otherwise return the pointer to the object
    }

    // Assignment
    Pointer<T>& operator=(const Pointer<T>& object)
    {
        cout << "Assignment operator" << endl << endl;

        ptr->reference_count--;

        if(ptr->reference_count == 0)
        {
            cout << "ML Error in assignment" << endl;
            ML_error();
        }

        ptr = object.ptr;
        ptr->reference_count++;

        if(ptr->rip)
        {
            cout << "DR Error in assignment" << endl;
            DR_error();     // if rip is true, then it's a dangling reference exception
        }

        return *this;
    }

    friend void free(Pointer<T>& object)     // delete pointed-at object
    {
        cout << "Freeing Pointer" << endl;

        if(object.ptr->rip)
        {
            cout << "DR Error in freeing pointer" << endl;
            DR_error();     // if rip is true, then it's a dangling reference exception
        }

        delete object.ptr->value;   //delete the pointer to the object
        object.ptr->rip = true;     // set this tombstone to rip
        object.ptr->value = NULL;
    }
        // This is essentially the inverse of the new inside the call to
        // the bootstrapping constructor. It should delete the pointed-to
        // object (which should in turn call its destructor).

    // equality comparisons:
    bool operator==(const Pointer<T>& object) const
    {
        // cout << "Equality comparison: ==" << endl << endl;
        if(ptr->rip || (object.ptr->rip))
        {
            cout << "DR Error in == comparison" << endl;
            DR_error();     // if any of them are rip, its a dangling reference
        }

        return ptr->value == (object.ptr->value);
    }

    bool operator!=(const Pointer<T>& object) const
    {
        // cout << "Equality comparison: !=" << endl << endl;
        if(ptr->rip || (object.ptr->rip))
        {
            cout << "DR Error in != comparison" << endl;
            DR_error();     // if any of them are rip, its a dangling reference
        }

        return ptr->value != (object.ptr->value);
    }

    // true iff Pointer is null and int is zero
    bool operator==(const int n) const
    {
        // cout << "Equality comparison: ==" << endl << endl;
        return ptr->value == NULL && n == 0;
    }

    // false iff Pointer is null and int is zero
    bool operator!=(const int n) const
    {
        // cout << "Equality comparison: !=" << endl << endl;
        return !(ptr->value == NULL && n == 0);
    }
};


template <class T>
bool operator==(const int n, const Pointer<T>& t)
{
    // cout << "Equality comparison: ==" << endl << endl;
    return t == n;

}


template <class T>
bool operator!=(const int n, const Pointer<T>& t)
{
    // cout << "Equality comparison: !=" << endl << endl;
    return t != n;
}

#endif /* tombstones_h */
