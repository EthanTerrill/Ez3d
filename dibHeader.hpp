
#include <iostream>
#include <unistd.h>

#include <cassert>
#include <vector>

#include <fstream>
#include <string>
#include <unistd.h>
#include <math.h>

#include <sstream>





enum DIB_HEADER_TYPE
{
    UNDEFINED,
    BITMAPCOREHEADER,
    OS22XBITMAPHEADER,
    BITMAPINFOHEADER,
    BITMAPV2INFOHEADER,
    BITMAPV3INFOHEADER,
    BITMAPV4INFOHEADER,
    BITMAPV5INFOHEADER

};


class dibHeader{


private:
    ///////////////////////////////////////////
    //  Header All formats
    ///////////////////////////////////////

    DIB_HEADER_TYPE type;
    uint32_t headerSize;

    int width;
    int height;



    void loadBitmapCoreHeader(std::ifstream& file){

        uint16_t width16;
        uint16_t height16;
        uint16_t numColorPlanes16;
        uint16_t bitsPerPixel16;
        

        file.read((char*)&width16,          sizeof(uint16_t));
        file.read((char*)&height16,         sizeof(uint16_t));
        file.read((char*)&numColorPlanes16, sizeof(uint16_t));
        file.read((char*)&bitsPerPixel16,   sizeof(uint16_t));

        width  = (int)width16;
        height = (int)height16;


    }

    void loadBitmapInfoHeader(std::ifstream& file){

        uint32_t width32;
        uint32_t height32;
        uint16_t numColorPlanes16;
        uint16_t bitsPerPixel16;
        uint32_t compressionMethod16;   //default 0
        uint32_t imageSize32;
        uint32_t horizontalRes32;
        uint32_t verticalRes32;
        uint32_t numColors32;           // default 0
        uint32_t numImportantColors;    // default 0







        

        file.read((char*)&width32,              sizeof(uint32_t));
        file.read((char*)&height32,             sizeof(uint32_t));
        file.read((char*)&numColorPlanes16,     sizeof(uint16_t));
        file.read((char*)&bitsPerPixel16,       sizeof(uint16_t));
        file.read((char*)&compressionMethod16,  sizeof(uint16_t)); //default 0
        file.read((char*)&imageSize32,          sizeof(uint32_t));
        file.read((char*)&horizontalRes32,      sizeof(uint32_t));
        file.read((char*)&verticalRes32,        sizeof(uint32_t));
        file.read((char*)&numColors32,          sizeof(uint32_t)); // default 0
        file.read((char*)&numImportantColors,   sizeof(uint32_t)); // default 0

        width  = (int)width32;
        height = (int)height32;
        
    }

public:




    ///////////////////////////////////////////
    //  Header All formats
    ///////////////////////////////////////

    dibHeader(){

    }
    
    dibHeader(std::ifstream& file) {

        assert(file.is_open());

        file.read((char*)&headerSize, sizeof(uint32_t));

        switch(headerSize){
            case 12:

                type = BITMAPCOREHEADER;
                loadBitmapCoreHeader(file);


            break;
            case 64:

                type = OS22XBITMAPHEADER;
            break;
            case 16:
                type = OS22XBITMAPHEADER;
            break;
            case 40:

                type = BITMAPINFOHEADER;
                loadBitmapInfoHeader(file);

            break;
            case 52:

                type = BITMAPV2INFOHEADER;
            break;
            case 56:

                type = BITMAPV3INFOHEADER;
            break;
            case 108:

                type = BITMAPV4INFOHEADER;
            break;
            case 124:

                type = BITMAPV5INFOHEADER;
            break;
            default:
            type = UNDEFINED;
            break;




        }
        std::cout << "size is:" << (headerSize) << "\n";
        std::cout << "width is: "  << width << "\n";
        std::cout << "height is: " << height << "\n";



    }

    int getWidth(){

        return width;
    }
    int getHeight(){
        return height;
    }
    
    int getDibSize(){
        return headerSize;
    }






};
