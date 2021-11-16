#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include "SIM.h"

using namespace std;

int main(int argc, char *argv[])
{

    int ret;
    char buf[5];
    int s, n, fd;
    struct sockaddr_in p;
    struct hostent *h;
    char *str = argv[1];                        // take slave test file parameter from the terminal

    h = gethostbyname("127.0.0.1");             // connect to master at local host
   
    bzero(&p, sizeof(p));
    p.sin_family = AF_INET;
    p.sin_addr.s_addr = htonl(INADDR_ANY);
    p.sin_addr.s_addr = ((struct in_addr *)(h->h_addr))->s_addr;
    p.sin_port = htons(8080);

    s = socket(AF_INET, SOCK_STREAM, 0);        
    connect(s, (struct sockaddr *)&p, sizeof(p));
    n = write(s, str, strlen(str));             // send the requested file name to the master 
    //printf(n);

    int idx = 0;
    n = read(s, buf, 5);                        // wait for master to respond

    if (n > 0)                                  // if the master responds with anything              
    {
        fd = open(str, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);  // open new txt file to receive
        do
        {
        
            idx += n;
            fflush(stdout);
            write(fd, buf, n);                  // write received instructions to the txt file
            n = read(s, buf, 5);
        } while (n > 0);

        cout << "File received successfully!" << endl;
        close(fd);
        close(s);

        SIM cpu;                  // initialize simulator class
        cpu.process(string(str)); // process preferred instructions text file
        remove(str);
    }
    else
    {
        cout << "Master says: file doesn't exist" << endl;
    }

    return 0;
}