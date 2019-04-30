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
        string img_1((string)argv[2]);
        string outputImg((string)argv[3]);

        if(directive != "-i")
        {
            cout << "missing some parameters." << endl;
            cout << "see correct usage below:" << endl;
            cout << " " << endl;
            operation.printUsage();
            exit(0);
        }
        else
        {
            operation.invert(img_1, outputImg);
        }
    }
    
    else if(argc == 5)
    {
        string dir(argv[1]);
        string img_1((string)argv[2]);
        string img_2((string)argv[3]);
        string outputImg((string)argv[4]);

        char directive(*(argv[1]+1)); // extract next char in directive supplied
        switch(directive)
        {
            // add
            case 'a':
            {
                operation.add(img_1,img_2,outputImg);
                break;
            }
            // subtract
            case 's':
            {
                operation.subtract(img_1,img_2,outputImg);
                break;
            }
            // mask
            case 'l':
            {
                operation.mask(img_1,img_2,outputImg);
                break;
            }
            // threshold
            case 't':
            {
                // Convert string to integer
                int threshold;
                stringstream ss;
                string str = (string)argv[3];
                ss << str;
                ss >> threshold;
                
                operation.threshold(img_1,threshold,outputImg);
                break;
            }
            // filter
            case '-f':
            {
                string filter((string)argv[3]);
                operation.filter(img_1,filter,outputImg);
                break;
            }
            // default
            default:
                cout << "invalid directive." << endl;
                operation.printUsage();
                break;
        }
    }
    
    else
    {
        //cout << "eh eh eh what are you doing?? lmaaooo" << endl;
        operation.printUsage();
    }

    return 0; // safe execution
}