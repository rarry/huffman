#ifndef CRC_H_INCLUDED
#define CRC_H_INCLUDED

#define SIZECRC 4
#define degreegen 32
#define BUFSIZE 128

unsigned char * calculateCrc(char *fileName);

void printCrcToFile(FILE *fp, unsigned char * crc);

void createCrcFile(char * fileName, int crcSizeInBytes, unsigned char crc[]);

void appendCrcToFile(char * outputWithCrc, int crcSizeInBytes, unsigned char crc[]);

unsigned char * calulateRest(char *fileName);

#endif // CRC_H_INCLUDED
