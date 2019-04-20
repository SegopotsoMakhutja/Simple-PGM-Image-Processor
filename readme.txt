/**
* ReadMe file
* Author : Segopotso Makhutja 
* March 2019
*/
	
- there are 5 files and a 2 folders in the tarball
- MRI folder and a .git repo [ctrl + h  if hidden].
- raw image files are in the basefolder MRI.
- volimage.h is the header file with method declarations
- volimage.cpp is the implementation file which contains all the method bodies/implementations
- volimage_driver.cpp is the driver file which has the main method/entry function.

compilation:
	-in terminal extract tarball
	-cd into root folder/directory of extracted tarball
	-run make
run:
	-in terminal "make run" for default programme without operations.
	- ./volimage <imageBase> [-d i j output_filename] [-x i output_filename] [-g i output_filename]
	- each flag must be run separately in different instances.
clean:
	- make clean deletes all binary files that were compiled.

**CAUTIONS:
	- make sure images are in folders within the programme directory
	- the name of the folder containing the images must be the same as the prefixes of the images
