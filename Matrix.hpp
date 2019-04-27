/**
 * 
 * Matrix H file
 * Author: Segopotso Makhutja
 * Date: April 2019
 * 
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#ifndef MATRIX_H
#define MATRIX_H

using namespace std;
namespace MKHSEG001
{
    class Matrix
    {
        public:
            int N;
            float* valPtr;
            
            Matrix(string file);
            ~Matrix();

            void loadVals(string file);
    };
} // namespace MKHSEG001

#endif
