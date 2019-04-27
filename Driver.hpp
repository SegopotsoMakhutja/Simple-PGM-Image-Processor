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

#define STUB(method) void method() { std::cout<<"To-Do: "<<#method<<endl; }

STUB(add);
STUB(subtract);
STUB(invertImage);
STUB(mask);
STUB(threshold);
// extra credit, not requirement.
STUB(filter)

#endif