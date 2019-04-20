/**
 * 
 * Image Operations H file
 * Author: Segopotso Makhutja
 * Date: April 2019
 * 
 */

#include "Image.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#ifndef OPS_H
#define OPS_H

using namespace std;
namespace MKHSEG001
{
    class Ops
    {
    public:

        void add(string image1, string image2, string outImg);

        void subtract(string image1, string image2, string outImg);

        void invert(string image1, string outImg);

        void mask(string image1, string image2, string outImg);

        void threshold(string image1, int threshold, string outImg);

        // extra credit, not requirement
        void filter(string image, string filterName, string outImg);
    };
} // namespace Ops

#endif