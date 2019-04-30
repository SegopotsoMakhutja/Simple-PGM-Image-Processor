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


