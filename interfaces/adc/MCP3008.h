
#ifndef MCP3008_H
#define MCP3008_H

// init device and read 10 bit channel data 

class MCP3008 
{

    int spi_channel, fd;

public:

    MCP3008(int spi_channel = 0, int clk_speed = 1000000);
    int getFileDescriptor();
    int readChannel(int analog_channel, int channel_config = 8);
};

#endif