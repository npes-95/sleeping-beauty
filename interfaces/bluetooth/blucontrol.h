#ifndef BLU_H
#define BLU_H

// init bluetooth and read incoming characters
// future work: send data to connected device

class BLU 
{

    int s, client, bytes_read;
    char buf[1024] = { 0 };
    // change this so it can get address for any pi
    char pi_addr[18] = "B8:27:EB:EB:F6:E1";
    struct sockaddr_rc loc_addr = { 0 }, rem_addr = { 0 };

public:

    BLU();
    int dataAvailable();
    int getData();
};

#endif