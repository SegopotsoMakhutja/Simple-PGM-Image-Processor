/**
 * 
 * Driver file stubs
 * Author: Segopotso Makhutja
 * Date: April 2019
 * 
 */

#include "Image.hpp"
#include <iostream>

#ifndef DRIVER_H
#define DRIVER_H

using namespace std;

#define STUB(operation) void operation() { cout<<"complete: "<<#operation<<endl; }

STUB(add);
STUB(subtract);
STUB(invertImage);
STUB(mask);
STUB(threshold);
// extra credit, not requirement.
STUB(filter)

#endif