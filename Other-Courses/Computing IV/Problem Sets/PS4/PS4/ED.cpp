/*
 Name: Ryan Balachandran
 Computing IV
 Professor: Yelena Rykalova
 Due Date: 3/25/19
 Problem Set 4
 */

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <string>

#include "ED.hpp"

using namespace sf;
using namespace std;

ED::~ED()
{
    cout << "----------DESTRUCTOR----------" << endl;
    
    for (int i = 0; i < N; i++)
    {
        delete[] matrix[i];
    }
    
    delete[] matrix;
}

ED::ED(string string1, string string2)
{
    X = string1 + "-";
    Y = string2 + "-";
    
    cout << "String X: " << X << endl;
    cout << "String Y: " << Y << endl;
    
    N = X.size();
    M = Y.size();
    
    cout << "Size of string X: " << N << endl;
    cout << "Size of string Y: " << M << endl;
    
    N = N+1;
    M = M+1;
    
    cout << "Matrix is: " << N << "x" << M << endl << endl;
    
    // create matrix
    matrix = new int*[N];
    
    for (int i = 0; i < N; i++)
    {
        matrix[i] = new int[M];
    }
    
    // fill matrix
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            matrix[i][j] = 0;
        }
    }
    
    // default penalty
    for (int i = N-1; i >= 0 ; i--)
    {
        matrix[i][M-1] = (((N-1)-i)*2);
    }
    
    for (int j = M-1; j >= 0; j--)
    {
        matrix[N-1][j] = (((M-1)-j)*2);
    }
    
    // draw_matrix();
}

int ED::penalty(char a, char b)
{ 
    if (a == b)
        return 0;
    else
        return 1;
}

int ED::min(int a, int b, int c)
{
    if (a < b && a < c)
        return a;
    else if(b < a && b < c)
        return b;
    else
        return c;
}

int ED::OptDistance()
{
    // fill matrix to get edit distance
    for (int i = M-2; i >= 0; i--)
    {
        for (int j = N-2; j >= 0; j--)
        {
            if (!(penalty(X[j], Y[i])))
                matrix[j][i] = matrix[j+1][i+1];
            else
                matrix[j][i] = min(matrix[j+1][i+1]+1, matrix[j+1][i]+2, matrix[j][i+1]+2);
        }
    }
    
    return matrix[0][0];
}

string ED::Alignment()
{
    string result;
    
    int i = 0;
    int j = 0;
    
    while (!(i == N-1 || j == M-1))
    {
        if (!(penalty(X[i], Y[j])))
        {
            result = result + X[i] + Y[j] + '0';
            i += 1;
            j += 1;
        }
        else if (matrix[i][j] == (matrix[i+1][j]+2))
        {
            result = result + X[i] + "-" + '2';
            i += 1;
        }
        else if (matrix[i][j] == (matrix[i][j+1]+2))
        {
            result = result + "-" + Y[j] + '2';
            j += 1;
        }
        else
        {
            result = result + X[i] + Y[j] + '1';
            i += 1;
            j += 1;
        }
    }
    
    result.pop_back();
    result.pop_back();
    result.pop_back();
    
    draw_matrix();
    
    return result;
}

void ED::draw_matrix()
{
    cout << "\t";
    for (int i = 0; i < M; i++)
    {
        cout << " " << i << "\t";
    }
    cout << endl;
    
    cout << "\t";
    for (int i = 0; i < M; i++)
    {
        cout << " " << Y[i] << "\t";
    }
    cout << endl;
    
    for (int i = 0; i < N; i++)
    {
        cout << i << "   " << X[i] << "\t";
        
        for (int j = 0; j < M; j++)
        {
            cout << "[" << matrix[i][j] << "]" << "\t";
        }
        
        cout << endl;
    }
}
