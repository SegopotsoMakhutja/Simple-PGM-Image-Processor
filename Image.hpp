/**
 * 
 * Image Operations H file
 * Author: Segopotso Makhutja
 * Date: April 2019
 * 
 */

#include "Matrix.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <memory>

#ifndef IMAGE_H
#define IMAGE_H

using namespace std;
namespace MKHSEG001
{
    class Image
    {
        private:
            unique_ptr<u_char[]> imgData;
            int size, height, width;
        public:
            /** start special memeber functions **/
            ~Image();
            Image(string imgName);
            Image(int w, int h, u_char* imgData);
            Image(const img& otherImg);
            Image(img&& otherImg);
            Image& operator = (const img& otherImg);
            Image& operator = (img&& otherImg);                     
            /** end special memeber functions **/

            /** start operator overloading **/
            Image operator + (const img& otherImg);
            Image operator - (const img& otherImg);
            Image operator / (const img& otherImg);
            Image operator * (int m);
            Image operator ! ();
            Image operator % (MKHSEG001::Matrix& m);
            Image& operator = (const img& otherImg);
            bool operator == (const img& otherImg);
            /** end operator overloading **/
            
            /** start file operations **/
            void store(string outputImg);
            void load(string file);
            /** end file operations **/
            
            /** start image operations **/
            void checkImageDimensions(img* one, const Image& two);
            int getWidth() const;
            int getHeight() const;
            int getSize() const;
            void setWidth(int w);
            void setHeight(int h);
            void setSize(int s);
            void setImgData(u_char * d);
            u_char* getImgData();
            /** end image operations **/
            
            /** start I/O overloads **/
            friend ifstream& operator >> (ifstream& inStream, img1& img2);
            friend ofstream& operator << (ofstream& outStream, const img1& img2);
            /** end I/O overloads **/

            /** start Iterator definition **/
            class Iterator
            {
                private:
                    friend class Image;
                    unsigned char* ptr;
                public:
                    // special members
                    ~Iterator();
                    Iterator(u_char *p);
                    Iterator(const Iterator& other);
                    Iterator (Iterator&& other);
                    Iterator& operator = (Iterator&& other);
                    Iterator& operator = (const Iterator& other);
                    
                    // Operator overloads
                    Iterator&  operator += (int num);
                    bool operator != (const Iterator& other);
                    const Iterator& operator ++();
                    const Iterator& operator --();
                    u_char& operator *();

            };
            Iterator begin(void) const;
            Iterator end(void) const;
    }; 
}// namespace MKHSEG001

#endif 