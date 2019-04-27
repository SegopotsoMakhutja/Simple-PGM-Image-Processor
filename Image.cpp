/**
 * 
 * Image Operations implementation file
 * Author: Segopotso Makhutja
 * Date: April 2019
 * 
 */

#include "Matrix.hpp"
#include "Image.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <memory>

#define u_char unsigned char

using namespace MKHSEG001;
using namespace std;

/* <-------- end special memeber functions --------> */
Image::Image(string imgName)
{
    load(imgName);
}

Image::Image(int w, int h, u_char* imageData)
{
    width = w;
    height = h;
    size = width * height;
    imgData.reset(imageData);
}

Image::~Image()
{
    width = 0;
    height = 0;
    imgData = nullptr;
}

Image::Image(const Image& otherImg)
{
    width = otherImg.width;
    height = otherImg.height;
    size = width * height;
    int i = 0;
    
    u_char* imageData  = new u_char[size];
    
    while(i<size)
    {
        imageData[i] = otherImg.imgData[i];
        i++;
    }

    imgData.reset(imageData);
}

Image::Image(Image&& otherImg)
{
    width = otherImg.width;
    height = otherImg.height;
    size = width * height;
    int i = 0;

    u_char* imageData  = new u_char[size];

    while(i<size)
    {
        imageData[i] = otherImg.imgData[i];
        i++;
    }

    imgData.reset(imageData);
    // clean up
    otherImg.height = 0;
    otherImg.width = 0;
    otherImg.size = 0;
    otherImg.imgData = nullptr;
}

Image& Image::operator = (const Image& otherImg)
{
    if(this == &otherImg)
    {
        return *this;
    }
    else
    {
        if(imgData != nullptr){ imgData = nullptr; }

        width = otherImg.width;
        height  = otherImg.height;
        size = width * height;
        int i = 0;

        u_char* imageData  = new u_char[size];

        while(i<size)
        {
            imageData[i] = otherImg.imgData[i];
            i++;
        }
        
        imgData.reset(imageData);
    }
    return *this;
}

Image& Image::operator = (Image&& otherImg)
{
    if(this == &otherImg)
    {
        return *this;
    }
    else
    {
        if (imgData != nullptr){ imgData = nullptr; }

        width = otherImg.width;
        height = otherImg.height;
        size = width * height;
        int i = 0;

        u_char* imageData  = new u_char[size];

        while(i<size)
        {
            imageData[i] = otherImg.imgData[i];
            i++;
        }

        imgData.reset(imageData);
        // clean up
        otherImg.height = 0;
        otherImg.width = 0;
        otherImg.size = 0;
        otherImg.imgData = nullptr;    
    }
    return *this;
}
/* <-------- end of special memeber functions --------> */

/* <-------- start of Iterator nav --------> */
Image::Iterator Image::begin() const
{
    return  Iterator(&(imgData.get()[0]));
}

Image::Iterator Image::end() const
{
    return  Iterator(&(imgData.get()[size]));
}
/* <-------- end of Iterator nav --------> */

/* <-------- start of operator overloading --------> */
Image Image::operator + (const Image& otherImg)
{
    checkDimensions(this, otherImg);

    Image img(*this);

    Image::Iterator begin = img.begin();
    Image::Iterator end = img.end();
    Image::Iterator altBegin = otherImg.begin();
    Image::Iterator altEnd = otherImg.end();

    while(begin != end)
    {
        int res = *begin + *altBegin;
        if(res > 255) { res = 255; }

        *begin = res;

        ++begin;
        ++altBegin;
    }

    return img;
}

Image Image::operator - (const Image& otherImg)
{
    checkDimensions(this, otherImg);

    Image img(*this);

    Image::Iterator end = img.end();
    Image::Iterator begin = img.begin();
    Image::Iterator altBegin = otherImg.begin();

    while(begin != end)
    {
        int res = *begin - *altBegin;

        if(res < 0) { res = 0; }

        *begin = res;

        ++begin;
        ++altBegin;
    }

    return img;
}

Image Image::operator * (int threshold)
{

    Image img(*this);

    Image::Iterator begin = img.begin();
    Image::Iterator end = img.end();

    //for(Image::Iterator i = begin; i != end; ++i)
    while(begin != end)
    {
        if(*begin > threshold) { *begin = 255; }
        else { *begin = 0; }
        ++begin;
    }

    return img;
}

Image Image::operator / (const Image& otherImg)
{
    checkDimensions(this, otherImg);

    Image img(*this);
    
    Image::Iterator end = img.end();
    Image::Iterator begin = img.begin();
    Image::Iterator altBegin = otherImg.begin();
    
    while(begin != end)
    {
        if(*altBegin != 255) { *begin = 0; }

        ++begin;
        ++altBegin;
    }

    return img;
}

Image Image::operator ! ()
{
    Image imgArr(*this);

    Image::Iterator begin = imgArr.begin();
    Image::Iterator end = imgArr.end();

    while(begin != end)
    {
        *begin = 255 - *begin;
        ++begin;
    }

    return imgArr;
}

Image Image::operator % (Matrix& matrix)
{
    Image img(*this);
    int dimension = matrix.N;
    u_char* dataArr = new u_char[size]; // filtered image array
    
    for(int i = 0; i < height; i++)
    {
        for(int k = 0; k < width; k++)
        {
            int flow = 0;
            for(int yVec = 0; yVec < dimension; yVec++)
            {
                for(int xVec = 0; xVec < dimension; xVec++)
                {
                    int y = (i - dimension/2 + yVec + height) % height;
                    int x = (k - dimension/2 + xVec + width) % width;
                
                    float filterValue = matrix.valPtr[(yVec*dimension) + xVec];
                    float  imageValue = imgData[(y * width) + x];
                
                    float result =  imageValue * filterValue;

                    flow+=result;
                }
            }
            
            if(flow < 0) 
            {
                cout << "clamped" <<endl; 
                flow = 0; 
            }

            if(flow > 255) 
            {
                cout << "clamped" <<endl; 
                flow = 255; 
            }

            dataArr[(i*width) + k] = flow;
        }
    }
    
    img.setImgData(dataArr);
    
    return img;
}

bool Image::operator == (const Image& otherImg)
{
    bool eq = true;

    if(width != otherImg.getWidth()) { eq = false; }
    if(height != otherImg.getHeight()) { eq = false; } 
    if(size != otherImg.getSize()) { eq = false; }

    for(int i = 0; i < size; i++)
    {
        if(imgData[i] != otherImg.imgData[i])
        {
            eq = false;
            break;
        }
    }

    return eq;
}
/* <-------- end of operator overloading --------> */

/* <------------------------ start I/O overloads  ------------------------> */
ofstream& operator << (ofstream& os, const Image& img)
{
    if(!os)
    {
        cout << "\nError opening file." << endl;
        exit(0);
    }
    else
    {
        int row = img.getWidth(), col = img.getHeight();
        Image::Iterator begin = img.begin(), end = img.end();
        u_char pixel;

        os << "P5" << endl;
        os << col << " " << row << endl;
        os << 255 << "\n" << endl;

        /*
        while(begin != end)
        {
            ++begin;
            pixel = *begin;
            os.write((char*)& pixel,1);
        } */
        
        for(Image::Iterator iter = img.begin() ; iter != img.end() ; ++iter)
        {
            pixel  = *iter;
            os.write((char*)&pixel,1);
        }
        return os; // comment out
    }
}

ifstream& operator >> (ifstream& in,  Image& img)
{
    if(in)
    {
        string line = "EMPTY";

        while(line != "255")
        {
            if(line == "255") { cout << "Line 255" << endl; }
            cout << ">> Line = " << line << endl;

            if(line.at(0) != 'P' && line.at(0) != '#' && line != "EMPTY")
            {
                cout << "Line = " << line << endl;
                stringstream ss;
                ss << line;
                int w, h;

                ss >> h >> ws >> w >> ws;

                img.setHeight(h);
                img.setWidth(w);
                break;
            }
            getline(in, line);
        }

        img.setSize(img.getWidth() * img.getHeight());

        u_char* imageData = new u_char[img.getSize()];

        in.read((char*)imageData, img.getSize());

        img.setImgData(imageData);
        cout << "file read succesfully" <<endl;
        return in; // comment line out
    }
    else
    {
        cout << "Error opening file" << endl;
        exit(0);
    }
}
/* <------------------------ end I/O overloads  ------------------------> */

/* <------------------------ start file I/O ops  ------------------------> */
// Loads image data from file
void Image::load(string file)
{
    ifstream infile(file, ios::in | ios::binary);

    if(!infile)
    {
        cout << "Error opening. " << file << endl;
        exit(0);
    }

    string line = "EMPTY";

    if(infile.is_open())
    {
        while(line != "255")
        {
            if(line.at(0) != '#' && line.at(0) != 'P' && line != "EMPTY")
            {
                stringstream ss;
                ss << line;
                ss >> height >> ws >> width >> ws;
                break;
            }
            getline(infile, line);
        }

        getline(infile, line);
        size = width * height;
        u_char* imageData = new u_char[width * height];

        infile.read((char*)imageData, size);

        imgData.reset(imageData);

        infile.close();
    }
    else
    {
        cout << "Unable to open file." << endl;
    }
}

void Image::store(string outputImg)
{
    ofstream outFile(outputImg, ios::out|ios::binary);

    if(!outFile)
    {
        cout << "Error opening "<< outputImg << endl;
        exit(0);
    }

    unsigned char pixel;

    if(outFile.is_open())
    {
        outFile << "P5" << endl;
        outFile << width << " " << height << endl;
        outFile << "255" << endl;

        for(Image::Iterator iter = this->begin() ; iter != this->end() ; ++iter)
        {
            pixel  = *iter;
            outFile.write((char*)&pixel,1);
        }

        outFile.close();

        cout << "File saved successfully. " << endl;
    }
    else
    {
        cout << "Unable to open file." << endl;
    }
}
/* <------------------------ end file I/O ops  ------------------------> */

/* <-------- Check that two images have the same dimensions --------> */
void Image::checkDimensions(Image* img_1, const Image& img_2)
{
    if(img_1->width != img_2.width || img_1->height != img_2.height)
    {
        cout << "Images provided have different dimensions. Operations cannot be performed on the images." << endl;
        exit(0);
    }
}

/* <--------------------- Getters and setters ---------------------> */
int Image::getWidth() const
{
    return width;
}

int Image::getHeight() const
{
    return height;
}

int Image::getSize() const
{
    return size;
}

void Image::setWidth(int w)
{
    width = w;
}

void Image::setHeight(int h)
{
    height = h;
}

void Image::setSize(int n)
{
    size = n;
}

void Image::setImgData(u_char * d)
{
    imgData.reset(d);
}

u_char * Image::getImgData()
{
    return imgData.get();
}
/* <--------------------- end of Getters and setters ---------------------> */

/********************************************************************** 
 *                                                                  ***
 *                   Iterator helper class methods                  ***
 *                                                                  ***
 **********************************************************************/

/* <-------- start of Iterator special members --------> */
Image::Iterator::Iterator(u_char *p): i_ptr(p){}

Image::Iterator::~Iterator() { i_ptr = nullptr; }

Image::Iterator::Iterator(const Iterator& other)
{
    i_ptr = other.i_ptr;
}

Image::Iterator::Iterator(Iterator&& otherImg)
{
    i_ptr = otherImg.i_ptr;
    otherImg.i_ptr = nullptr;
}

Image::Iterator&  Image::Iterator::operator = (const Iterator& other)
{
    if(this != &other) { i_ptr = other.i_ptr; }
    return *this;
}

Image::Iterator&  Image::Iterator::operator = (Iterator&& other)
{
    if(this != &other) { i_ptr = other.i_ptr; }

    other.i_ptr = nullptr;
    return *this;
}
/* <-------- end of Iterator special members --------> */

/* <-------- start of Iterator operator overloading --------> */
Image::Iterator&  Image::Iterator::operator += (int num)
{
    i_ptr = i_ptr + num;
    return *this;
}

bool Image::Iterator::operator != ( const Iterator& otherIterator)
{
    return (i_ptr != otherIterator.i_ptr);
}

const Image::Iterator& Image::Iterator::operator ++ ()
{
    ++i_ptr;
    return *this;
}

const Image::Iterator& Image::Iterator::operator -- ()
{
    i_ptr--;
    return *this;
}

u_char& Image::Iterator::operator * ()
{
    return *i_ptr;
}
/* <-------- end of Iterator operator overloading --------> */