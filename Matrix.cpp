/**
 * 
 * Matrix implementation file
 * Author: Segopotso Makhutja
 * Date: April 2019
 * 
 */

#include "Image.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace MKHSEG001;

Matrix::Matrix(std::string file)
{ 
    loadVals(file);
}

Matrix::~Matrix()
{
    N = 0;
    valPtr = nullptr;
}

void Matrix::loadVals(std::string file)
{
    ifstream infile(file);
    
    if(!infile)
    {
        cout << "Error opening " << file << endl;
        exit(0);
    }
    
    std::string line;
    float inValues; // float values being read from the file
    
    if(infile.is_open())
    {
        getline(infile, line);
        // A string stream for the vals
        std::stringstream ss;
        ss << line;
        ss >> N;
        valPtr = new float[N*N];
        
        int i = 0;
        while(i<N*N)
        {
            ss>>inValues;
            valPtr[i]=inValues;
            i++;
        }

        infile.close();
    }
    else
    {
        cout << "Error opening " << file << endl;
    }
}
