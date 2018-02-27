// based on https://people.csail.mit.edu/albert/bluez-intro/
// with modifications from https://raspberrypi.stackexchange.com/questions/55850/rpi-bluetooth-headless-communication-with-android-phone-no-pairing

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

using namespace std;

int main(int argc, char **argv)
{
	// this program will accept any bluetooth connection and print out the data sent
    struct sockaddr_rc loc_addr = { 0 }, rem_addr = { 0 };
    char buf[1024] = { 0 };
    int s, client, bytes_read;
    socklen_t opt = sizeof(rem_addr);
    char pi_addr[18] = "B8:27:EB:EB:F6:E1";
    
    // activate automatic bluetooth pairing through command line
    // not super safe, but will do for now
    // maybe look at implementing this in a script using bluetoothctl (https://stackoverflow.com/questions/34709583/bluetoothctl-set-passkey)
    system("sudo hciconfig hci0 piscan");

    // allocate socket
    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    // bind socket to port 1 of the first available 
    // local bluetooth adapter
    loc_addr.rc_family = AF_BLUETOOTH;
    str2ba(pi_addr, &loc_addr.rc_bdaddr);
    loc_addr.rc_channel = (uint8_t) 1;
    bind(s, (struct sockaddr *)&loc_addr, sizeof(loc_addr));

    // put socket into listening mode
    listen(s, 1);

    // accept one connection
    client = accept(s, (struct sockaddr *)&rem_addr, &opt);

    ba2str( &rem_addr.rc_bdaddr, buf );
    fprintf(stderr, "Accepted connection from %s\n", buf);
    memset(buf, 0, sizeof(buf));

    // read in any character coming from the device
    while(true){
        bytes_read = read(client, buf, sizeof(buf));
        if( bytes_read > 0 ) {
            cout << "Received: " << buf << "\n";
            memset(buf, 0, sizeof(buf));
        }
    

    }

  

}
