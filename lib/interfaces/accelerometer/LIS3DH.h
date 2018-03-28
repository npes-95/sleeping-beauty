#ifndef LIS3DH_H
#define LIS3DH_H

// init device and read XYZ 16 bit values
// future work: add functions for settings control

class LIS3DH 
{

    int fd;

public:

    LIS3DH();
    int getFileDescriptor();
    int dataAvailable();
    int readX();
    int readY();
    int readZ();
};

#endif