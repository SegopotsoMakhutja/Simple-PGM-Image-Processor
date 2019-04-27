/**
 * 
 * Driver program
 * Author: Segopotso Makhutja
 * Date: April 2019
 * 
 */

#include "Image.hpp"
#include "Ops.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace MKHSEG001;
using namespace std;

int main(int argc, char* argv[])
{
    string img_1, img_2, outputImg;
    Ops operation;

    if(argc == 1)
    {
        cout << " " << endl;
        cout << "No parameters supplied." << endl;
        operation.printUsage();
        exit(0);
    }
    
    if(argc > 1 && argc < 4)
    {
        cout << "missing some parameters." << endl;
        cout << "see correct usage below:" << endl;
        cout << " " << endl;
        operation.printUsage();
        exit(0);
    }
    if(argc == 4)
    {
        string directive(argv[1]);
        if(directive != "-i")
        {
            cout << "missing some parameters." << endl;
            cout << "see correct usage below:" << endl;
            cout << " " << endl;
            operation.printUsage();
            exit(0);
        }
    }
}