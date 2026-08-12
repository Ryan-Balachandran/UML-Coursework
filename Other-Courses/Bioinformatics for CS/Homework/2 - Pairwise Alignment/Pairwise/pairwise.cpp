#include <iostream>
#include <string>

#include "pairwise.hpp"

using namespace std;

//S(i,j) = {+2 match, -1 mismatch}
//gap = -2g

void globalAlign(string sequence1, string sequence2)
{
    static const int match = 20;
    static const int mismatch = -3;
    static const int gap = -10;
    
    int seq1Length = sequence1.length();
    int seq2Length = sequence2.length();
    
    cout << endl;
    cout << "Sequence 1: " << sequence1 << endl;
    cout << "Sequence 2: " << sequence2 << endl;
    cout << endl;
    cout << "Sequence 1 length: " << seq1Length << endl;
    cout << "Sequence 2 length: " << seq2Length << endl;
    cout << endl;
    cout << "MATCH SCORE IS: " << match << endl;
    cout << "MISMATCH SCORE IS: " << mismatch << endl;
    cout << "GAP PENALTY IS: " << gap << endl;
    cout << endl;

    
    // Initialize matrix
    int matrix[seq1Length + 1][seq2Length + 1];
    
    for(int i = 0; i <= seq1Length; i++)
    {
        for(int j = 0; j <= seq2Length; j++)
        {
            matrix[i][j] = 0;
        }
    }
    
    // Initial gap penalties
    for(int i = 1; i <= seq1Length; i++)
    {
        matrix[i][0] = matrix[i-1][0] + gap;
    }
    
    for(int j = 1; j <= seq2Length; j++)
    {
        matrix[0][j] = matrix[0][j-1] + gap;
    }
    
    
    // DRAW MATRIX -------------------------------
    cout << "\t";
    for(int j = 0; j <= seq2Length; j++)
    {
        cout << j << "\t";
    }
    cout << endl;
    
    cout << "\t";
    cout << "-";
    cout << "\t";
    for(int j = 0; j <= seq2Length; j++)
    {
        cout << sequence2[j] << "\t";
    }
    cout << endl;
    
    for(int i = 0; i <= seq1Length; i++)
    {
        if(i == 0)
        {
            cout << i << "  " << "-" << "\t";
        }
        else
        {
            cout << i << "  " << sequence1[i-1] << "\t";
        }
    
        for(int j = 0; j <= seq2Length; j++)
        {
            cout << "[" << matrix[i][j] << "]" << "\t";
        }
        
        cout << endl;
    }
     
     cout << endl << endl;
    // DRAW MATRIX -------------------------------

    
    // fill in the rest of the matrix based on penalties
    for(int i = 1; i <= seq1Length; i++)
    {
        for(int j = 1; j <= seq2Length; j++)
        {
            int diagonal_score = 0;
            
            if(sequence1[i-1] == sequence2[j-1])
            {
                diagonal_score = matrix[i-1][j-1] + match;
            }
            else
            {
                diagonal_score = matrix[i-1][j-1] + mismatch;
            }
            
            int gapLeft = matrix[i][j-1] + gap;
            int gapRight = matrix[i-1][j] + gap;
            
            matrix[i][j] = max({gapLeft, gapRight, diagonal_score});
        }
    }
    
    // DRAW MATRIX -------------------------------
    cout << "\t";
    for(int j = 0; j <= seq2Length; j++)
    {
        cout << j << "\t";
    }
    cout << endl;
    
    cout << "\t";
    cout << "-";
    cout << "\t";
    for(int j = 0; j <= seq2Length; j++)
    {
        cout << sequence2[j] << "\t";
    }
    cout << endl;
    
    for(int i = 0; i <= seq1Length; i++)
    {
        if(i == 0)
        {
            cout << i << "  " << "-" << "\t";
        }
        else
        {
            cout << i << "  " << sequence1[i-1] << "\t";
        }
    
        for(int j = 0; j <= seq2Length; j++)
        {
            cout << "[" << matrix[i][j] << "]" << "\t";
        }
        
        cout << endl;
    }
     
     cout << endl << endl;
    // DRAW MATRIX -------------------------------
    
    // Traceback matrix to find global alignment
    char seq1Trace[seq1Length];
    char seq2Trace[seq2Length];
    
    for(int c1 = 0; c1 <= seq1Length; c1++)
    {
        seq1Trace[c1] = sequence1[c1];
    }
    
    for(int c2 = 0; c2 <= seq2Length; c2++)
    {
        seq2Trace[c2] = sequence2[c2];
    }
    
    string alignment1, alignment2;
    
    int M = seq1Length;
    int N = seq2Length;
    
    while(M > 0 && N > 0)
    {
        int diagScore;
        
        // match
        if(sequence2[N-1] == sequence1[M-1])
        {
            diagScore = match;
        }
        //mismatch
        else
        {
            diagScore = mismatch;
        }
        
        if(M > 0 && N > 0 && matrix[M][N] == matrix[M-1][N-1] + diagScore)
        {
            alignment1 = seq2Trace[N-1] + alignment1;
            alignment2 = seq1Trace[M-1] + alignment2;
            M -= 1;
            N -= 1;
        }
        else if(N > 0 && matrix [M][N] == matrix[M][N-1] + gap)
        {
            alignment1 = seq2Trace[N-1] + alignment1;
            alignment2 = "-" + alignment2;
            N -= 1;
        }
        else
        {
            alignment1 = "-" + alignment1;
            alignment2 = seq1Trace[M-1] + alignment2;
            M -= 1;
        }
    }
    
    cout << endl << "OPTIMAL SCORE: " << matrix[seq1Length][seq2Length] << endl;
    
    cout << endl << alignment2 << endl << alignment1 << endl << endl;
}
