
#include "dibHeader.cpp"
#include "bmpHeader.cpp"

class bitmap{


  /*

    ╔════════════════════════════════════════╗
    ║         .bmp format                    ║▓▒░
    ╠════════════════╦════════════╦══════════╣▓▒░
    ║     NAME       ║   NEEDED   ║ SIZE     ║▓▒░
    ╠════════════════╬════════════╬══════════╣▓▒░
    ║    header      ║    yes     ║ 14 Bytes ║▓▒░
    ╠════════════════╬════════════╬══════════╣▓▒░
    ║       DIB      ║    yes     ║  varies  ║▓▒░
    ╠════════════════╬════════════╬══════════╣▓▒░
    ║   Extra bit    ║     no     ║ 12-16    ║▓▒░
    ║     masks      ║            ║ Bytes    ║▓▒░
    ╠════════════════╬════════════╬══════════╣▓▒░
    ║   Color Table  ║ Only>8bits ║ varies   ║▓▒░
    ╠════════════════╬════════════╬══════════╣▓▒░
    ║      GAP 1     ║    no      ║ varies   ║▓▒░
    ╠════════════════╬════════════╬══════════╣▓▒░
    ║   Pixel Array  ║    yes     ║ varies   ║▓▒░
    ╠════════════════╬════════════╬══════════╣▓▒░
    ║      GAP 2     ║    no      ║ varies   ║▓▒░
    ╠════════════════╬════════════╬══════════╣▓▒░
    ║   ICC color    ║    no      ║ varies   ║▓▒░
    ║      GAP 1     ║            ║          ║▓▒░
    ╚════════════════╩════════════╩══════════╝▓▒░
      ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░
       ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░

  */

private:
  

  char* bytes;


  ///////////////////////////////////////////
  //  Header information
  ///////////////////////////////////////
  bmpHeader header;
  dibHeader dib;



  std::string DIBHeaderType;


  std::string fileName;

  bool isGoodHeaderField(){

    if
    (
      (header.firstLetter == 'B' && header.secondLetter =='M') ||
      (header.firstLetter == 'B' && header.secondLetter =='A') ||
      (header.firstLetter == 'C' && header.secondLetter =='I') ||
      (header.firstLetter == 'C' && header.secondLetter =='P') ||
      (header.firstLetter == 'I' && header.secondLetter =='C') ||
      (header.firstLetter == 'P' && header.secondLetter =='T')
    )
    {
      return true;
    }
    else{
      return false;
    }

  }


  void inline readHeader(std::ifstream& file){

    file.read((char*)&header.firstLetter, sizeof(uint8_t));
    file.read((char*)&header.secondLetter, sizeof(uint8_t));

    if(!isGoodHeaderField()){
      throw("Error corrupted .bmp file");
    }

    file.read((char*)&header.fileSize, sizeof(uint32_t));
    file.read((char*)&header.reservedMem, sizeof(uint32_t));
    file.read((char*)&header.offset, sizeof(uint32_t));

    


  }

public:


  bitmap(std::string fileName)
  {
    this->fileName = fileName;


    std::ifstream file(fileName, std::ios::binary);

    if(!file.is_open()){

      throw("Error: could not find bmp file");
    }

    readHeader(file);

    dib = dibHeader(file);

    unsigned int byteSize = 3 * getWidth() * getheight();
    bytes = new char[byteSize];

    int currentPos = 14 + dib.getDibSize();
    uint8_t trash = 0;

    while(currentPos <  header.offset + 2){

      file.read((char*)&trash, sizeof(uint8_t));
      currentPos++;


    }


    file.read(bytes, byteSize);




    file.close();



  }


  int getWidth(){
    return dib.getWidth();
  }
  int getheight(){
    return dib.getHeight();
  }
  unsigned char* getBytes(){

    return (unsigned char*)bytes;
  }












};
