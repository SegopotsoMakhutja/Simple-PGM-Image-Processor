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

// Assignment operator
Image& Image::operator = (const Image& otherImage)
{

    if(this == &otherImage)
    {
        return *this;
    }
    else
    {
        if(data != nullptr)
        {
            data = nullptr;
        }

        width = otherImage.width;
        height  = otherImage.height;

        size = width * height;

        u_char* imageData = new u_char[width*height];

        for(int i = 0; i < size; i++)
        {
            imageData[i] = otherImage.data[i];
        }

        data.reset(imageData);
    }

    return *this;
}

// Move assignment operator
Image& Image::operator = (Image&& otherImage)
{
    if(this == &otherImage)
    {
        return *this;
    }
    else
    {
        if (data != nullptr)
        {
            data = nullptr;
        }

        width = otherImage.width;
        height = otherImage.height;

        size = width * height;

        u_char* imageData = new u_char[width*height];

        for(int i = 0; i < size; i++)
        {
            imageData[i] = otherImage.data[i];
        }

        data.reset(imageData);

        otherImage.width = 0;
        otherImage.height = 0;
        otherImage.size = 0;
        otherImage.data = nullptr;
    }

    return *this;
}
 
/* <-------- Check that two images have the same dimensions --------> */
void Image::checkDimensions(Image* one, const Image& two)
{
    if(one->height != two.height || one->width != two.width)
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
