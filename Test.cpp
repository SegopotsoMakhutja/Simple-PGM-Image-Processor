/**
 * 
 * unit testing
 * Author: Segopotso Makhutja
 * Date: April 2019
 * 
 */

#define u_char unsigned char
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Image.hpp"
#include "Matrix.hpp"
#include "Ops.hpp"

using namespace std;
using namespace MKHSEG001;

TEST_CASE("Testing Copy Constructor")
{
    Image img("shrek_rectangular.pgm");

    u_char* data = img.getImgData();
    int w = img.getWidth();
    int h = img.getHeight();
    int s = img.getSize();

    Image img_2(img);

    REQUIRE(img_2.getWidth() == w);
    REQUIRE(img_2.getHeight() == h);
    REQUIRE(img_2.getSize() == s);
    REQUIRE(img_2.getImgData() != nullptr);

    REQUIRE((img == img_2) == true);
}

TEST_CASE("Testing Copy Assignment Operator")
{
    Image img("shrek_rectangular.pgm");

    u_char* data = img.getImgData();
    int w = img.getWidth();
    int h = img.getHeight();
    int s = img.getSize();

    Image img_2(img);

    REQUIRE(img_2.getWidth() == w);
    REQUIRE(img_2.getHeight() == h);
    REQUIRE(img_2.getSize() == s);
    REQUIRE(img_2.getImgData() != nullptr);

    REQUIRE((img == img_2) == true);
}

TEST_CASE("Testing Move Constructor")
{
    Image img("Lenna_standard.pgm");

    u_char* data = img.getImgData();
    int w = img.getWidth();
    int h = img.getHeight();
    int s = img.getSize();
    
    Image img_2 = move(img);

    REQUIRE(img.getWidth() == 0);
    REQUIRE(img.getHeight() == 0);
    REQUIRE(img.getSize() == 0);
    REQUIRE(img.getImgData() == nullptr);

    REQUIRE(img_2.getWidth() == w);
    REQUIRE(img_2.getHeight() == h);
    REQUIRE(img_2.getSize() == s);
    REQUIRE(img_2.getImgData() != nullptr);

    REQUIRE((img == img_2) == false);
}

TEST_CASE("Testing Move Assignment Operator")
{
    Image img("Lenna_standard.pgm");
    Image img_2("Lenna_hat_mask.pgm");

    u_char* data = img.getImgData();
    int w = img.getWidth();
    int h = img.getHeight();
    int s = img.getSize();

    Image otherImg = img + img_2;

    REQUIRE(otherImg.getWidth() == w);
    REQUIRE(otherImg.getHeight() == h);
    REQUIRE(otherImg.getSize() == s);
    REQUIRE(otherImg.getImgData() != nullptr);
}

TEST_CASE("Testing Iterator")
{
    Image img("Lenna_standard.pgm");
    Image::Iterator iter = img.begin();
    REQUIRE(*iter == img.getImgData()[0]);
    ++iter;
    REQUIRE(*iter == img.getImgData()[1]);
    ++iter;
    REQUIRE(*iter == img.getImgData()[2]);
    --iter;
    REQUIRE(*iter == img.getImgData()[1]);
    --iter;
    REQUIRE(*iter == img.getImgData()[0]);
    REQUIRE(iter != img.end());
}

TEST_CASE("Thresholding Test")
{
    Image img("Lenna_standard.pgm");
    Image img_2 = img * 128;
    int size = img.getSize();
    int i = 0;
    bool pass = true;

    while (i<size)
    {
        int value = (int)img.getImgData()[i];
        if(img.getImgData()[i] > 128)
        {
            value = 255;
        }
        else
        {
            value = 0;
        }

        if(img_2.getImgData()[i] != value)
        {
            pass = false;
            cout << "Thresholding Fail" << endl;
            break;
        }
        i++;
    }
    REQUIRE(pass == true);
}

TEST_CASE("Inverting test")
{
    Image img("Lenna_standard.pgm");
    Image img_2 = !img;
    bool pass = true;

    for(int i = 0; i < img.getSize(); i++)
    {
        int val = 255 - (int)img.getImgData()[i];

        if(img_2.getImgData()[i] != val)
        {
            pass = false;
            cout << "Invert test not passed" << endl;
            break;
        }
    }
    REQUIRE(pass == true);
}

TEST_CASE("Add Operation Test")
{
    Image img("Lenna_standard.pgm");
    Image img_2("Lenna_hat_mask.pgm");
    Image res_img = img + img_2;
    
    bool pass = true;
    
    int size = img.getSize();
    
    u_char* data = img.getImgData();
    u_char* data_2 = img_2.getImgData();
    
    for(int i = 0; i < size; i++)
    {
        int sum = data[i] + data_2[i];
        if(sum > 255)
        {
            sum = 255;
        }
        if(res_img.getImgData()[i] > 255)
        {
            pass = false;
            cout << "Clamping Failed." << endl;
            break;
        }
        else
        {
            if(res_img.getImgData()[i] != sum)
            {
                pass = false;
                break;
            }
        }
    }
    REQUIRE(pass == true);
}

TEST_CASE("Subtract Operation Test")
{
    Image img("Lenna_standard.pgm");
    Image img_2("Lenna_hat_mask.pgm");
    Image res_img = img - img_2;
    
    bool pass = true;
    
    int size = img.getSize();
    
    u_char* data = img.getImgData();
    u_char* data_2 = img_2.getImgData();
    u_char* data_3 = res_img.getImgData();
    
    for(int i = 0; i < size; i++)
    {
        int diff = data[i] - data_2[i];

        if(diff < 0)
        {
            diff = 0;
        }

        if(data_3[i] < 0)
        {
            pass = false;
            cout << "Clamping Failed" << endl;
            break;
        }
        else
        {
            if(res_img.getImgData()[i] != diff)
            {
                pass = false;
                break;
            }
        }
    }
    REQUIRE(pass == true);
}


