/**
 * 
 * Image Operations implementation file
 * Author: Segopotso Makhutja
 * Date: April 2019
 * 
 */

#include "Image.hpp"
#include "Matrix.hpp"
#include "Ops.hpp"
#include <iostream>
#include <sstream>

using namespace std;
using namespace MKHSEG001;

void Ops::add(string image1, string image2, string outImg)
{
    cout << "performing add operation on \"" << image1 << "\" & \"" << image2 << "\" "<< endl;

    Image img_1 = Image(image1);
    Image img_2 = Image(image2);
    Image out = img_1 + img_2;
    out.store(outImg);

    cout << "Add operation performed on \"" << image1 << "\" & \"" << image2 << "\" "<< endl;
    cout << "View output in \"" << outImg << "\" " << endl;
}

void subtract(string image1, string image2, string outImg)
{
    cout << "performing subtract operation on \"" << image1 << "\" & \"" << image2 << "\" "<< endl;
    
    Image img_1 = Image(image1);
    Image img_2 = Image(image2);
    Image out = img_1 - img_2;
    out.store(outImg);

    cout << "Subtract operation performed on \"" << image1 << "\" & \"" << image2 << "\" "<< endl;
    cout << "output saved in \"" << outImg << "\" " << endl;
}

void invert(string image1, string outImg)
{
    cout << "performing invert operation on \"" << image1 << "\" " << endl;

    Image in(image1);
    Image out = !in;
    out.store(outImg);

    cout << "Invert operation performed on \"" << image1 << "\" " << endl;
    cout << "View output in \"" << outImg << "\" " << endl;
}

void mask(string image1, string image2, string outImg)
{

}

void threshold(string image1, int threshold, string outImg)
{

}

// extra credit, not requirement
void filter(string image, string filterName, string outImg)
{

}

void Ops::printUsage()
{
    cout << "command line formats are as follows:\n" << endl;
    cout << "-a[add] <image1> <image2> <output image>" << endl;
    cout << "-s[subtract] <image1> <image2> <output image>" << endl;
    cout << "-i[invert] <image> <output image>" << endl;
    cout << "-l[mask] <image1> <image2> <output image>" << endl;
    cout << "-t[threshold] <image> <threshold value> <output image>" << endl;
}