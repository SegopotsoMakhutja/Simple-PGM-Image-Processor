#include "Image.h"
#include <iostream>

#ifndef DRIVER_H
#define DRIVER_H

#define STUB(method) void method() {std::cout<<"Todo: "<<#method<<"\n";}

STUB(invertImage);
STUB(mask);
STUB(subtract);
STUB(add);
STUB(threshold);
STUB(filter)

#endif