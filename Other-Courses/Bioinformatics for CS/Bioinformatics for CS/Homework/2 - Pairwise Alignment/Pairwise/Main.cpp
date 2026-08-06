#include <iostream>
#include <string>

#include "pairwise.hpp"

using namespace std;

int main()
{
    int choice = 0;
    string filename;
    string sequences[2] = {};
    
    cout << endl;
    cout << "****************************************************" << endl;
    cout << "PAIRWISE ALIGNMENT PROGRAM USING DYNAMIC PROGRAMMING" << endl;
    cout << "****************************************************" << endl;
    
    //Keep running program until the user enters 1
    while(choice != 1)
    {
        cout << "Input file name: ";
        cin >> filename;
        
        string line;
        int count = 0;
        
        ifstream file(filename);
        
        if(file.is_open())
        {
            cout << endl << "Input: " << endl;
            
            while(getline(file, line))
            {
                cout << line << endl;
                sequences[count] = line;
                count++;
            }
            
            file.close();
            
            globalAlign(sequences[0], sequences[1]);
            
            cout << "Would you like to try another file?" << endl << "hit any NUMBER to continue" << endl << "1 to exit" << endl;
            cin >> choice;
        }
        else
        {
            cout << "unable to fine file" << endl;
        }
    }

    return 0;
}
