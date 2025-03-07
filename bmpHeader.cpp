#include <stdint.h>

/*
    ╔════════════════════════════╗
    ║       header format        ║▓▒░
    ╠════════════════╦═══════════╣▓▒░
    ║     NAME       ║  SIZE     ║▓▒░
    ╠════════════════╬═══════════╣▓▒░
    ║ header field   ║  2 Bytes  ║▓▒░
    ╠════════════════╬═══════════╣▓▒░
    ║    File Size   ║  4 Bytes  ║▓▒░
    ╠════════════════╬═══════════╣▓▒░
    ║   Reserved     ║  2 Bytes  ║▓▒░
    ╠════════════════╬═══════════╣▓▒░
    ║   Reserved     ║  2 Bytes  ║▓▒░
    ╠════════════════╬═══════════╣▓▒░
    ║     Offset     ║  4 Bytes  ║▓▒░
    ║ Start of array ║           ║▓▒░
    ╚════════════════╩═══════════╝▓▒░
      ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░
       ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
*/


struct bmpHeader{

    ///////////////////////////////////////////
    //  Header information
    ///////////////////////////////////////
    uint8_t   firstLetter;
    uint8_t   secondLetter;
    uint32_t  fileSize;
    uint32_t  reservedMem;
    uint32_t  offset;
};
