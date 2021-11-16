#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include "reader.h"
#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

/*
this write function fetches the instructions requested by the slave and 
puts them together in a separate text file.
*/
void write(vector<Instruction> &inst_mem, string locs)
{
    ofstream myfile("temp.txt");
    int index;
    if (myfile.is_open())
    {
        for (int i = 0; i < locs.length(); i++)
        {
            index = int(locs[i]) - 48;

            myfile << inst_mem[index].getcontent() << endl;
            ;
        }
        myfile.close();
    }
    else
        cout << "Unable to open file";
}

int main(int argc, char *argv[])
{
    string test_num;
    cout << "Which test would you like to work on? ";
    cin >> test_num;
    test_num += "/";
    cout << endl;

    vector<Instruction> inst_mem;
    file_reader reader(test_num + "master.txt"); // reading master instruction memory
    cout << "Begin reading master instructions...." << endl;
    cout << endl;
    inst_mem = reader.instruction_mem();
    cout << endl;

    struct sockaddr_in p; // sockets for TCP communication
    struct sockaddr_in q;
    int z, s, t, x, n, size, b = sizeof(q);
    char buf[23];
    int fd;
    s = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&p, sizeof(p));
    p.sin_family = AF_INET;
    p.sin_addr.s_addr = INADDR_ANY;
    p.sin_port = htons(8080);
    bind(s, (struct sockaddr *)&p, sizeof(p));
    listen(s, 13);

    while (1) // while (1) to make the master run forever
    {
        t = accept(s, (struct sockaddr *)&q, (socklen_t *)&b); // wait for any slave to make a request
        n = read(t, buf, 23);
        buf[n] = 0;
        printf("Received request from a slave for %s: \n", buf);

        char *newArray = new char[test_num.size() + strlen(buf) + 1];
        strcpy(newArray, test_num.c_str());
        strcat(newArray, buf);
        FILE *myfilee;
        if (myfilee = fopen(newArray, "r")) // check if the requested file actually exists
        {
            fclose(myfilee);

            cout << "Fetching instructions at requested locations...." << endl;
            string line;
            string str;
            ifstream myfile(newArray);
            while (getline(myfile, line)) // read the file to find requested instructions locations
            {
                line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());

                str += line;
            }

            write(inst_mem, str);               // fetch the instructions at these locations
            fd = open("temp.txt", O_RDONLY); // temp.txt includes requested instructions
            z = lseek(fd, 0, SEEK_END);
            lseek(fd, 0, SEEK_SET);
            x = 0;
            cout << "Now sending..." << endl;
            do
            {
                n = read(fd, buf, 23); // read each instruction then send sequentially
                write(t, buf, n);
                x += n;
            } while (x < z);

            printf("%d/%d sent successfully\n", x, z);
            cout << endl;
            myfile.close();
            remove("temp.txt");
            close(fd);
            close(t);
        }
        else // if the file doesn't exist, send -1
        {
            cout << "This file doesn't exist!" << endl;

            fd = open(newArray, O_RDONLY);
            z = lseek(fd, 0, SEEK_END);
            lseek(fd, 0, SEEK_SET);
            x = 0;
            do
            {
                n = read(fd, buf, 23);
                write(t, buf, n);
                x += n;
            } while (x < z);

            close(fd);
            close(t);
            cout << endl;
        }
    }

    return 0;
}
