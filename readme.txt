/**
* ReadMe file for Assignment 4: Image processing
* Author : Segopotso Makhutja
* [MKHSEG001]
* April 2019
*/

### instructions:
	- extract tarball  
	- cd into root directory

### files in root directory
	- Driver.hpp	: Driver file stubs
	- Driver.cpp	: Driver program, main entry.
	- catch.hpp		: header file for testing framework
	- Test.cpp		: used for unit testing implementation
	- Image.hpp		: header file for image class and iterator
	- Image.cpp		: implementation of image methods defined in the h file
	- Matrix.hpp	: header file for matrix class definitions 
	- Matrix.cpp	: implementation of matrix methods defined in the h file
	- Ops.hpp		: header file for image operations
	- Ops.cpp		: implementation of operation methods defined in the h file
	- Makefile		: make file used for compiling
	- ReadMe.txt	: readme file with instructions and notes
	- *.pgm			: all raw image files upon which operations are performed
	- sample_filters: folder containing all filters [*.fir]

### compilation:
	- in terminal type `make` and enter.

### run:
	- once done compiling
	- in terminal type `make run` it will show you command line args
	- each flag must be run separately in different instances.

### test:
	- `make test` on terminal

clean:
	- make clean deletes all binary files that were compiled.

**CAUTIONS:
	- make sure images are in folders within the programme directory
	- the name of the folder containing the images must be the same as the prefixes of the images
	- to test for the filters, move or copy them from their folder into the working directory.