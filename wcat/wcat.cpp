#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char* argv[]) {
    if(argc == 1) {
        exit(0);
    }
    for(int i = 1; i < argc; i++) {
        int fileDescriptor = open(argv[i], O_RDONLY);
        if(fileDescriptor < 0) {
            char message[24] = "wcat: cannot open file\n";
            write(1, message, sizeof(message)-1);
            exit(1);
        }
        int bytesRead = 1;
        while(bytesRead > 0) {
            char buf[128];
            bytesRead = read(fileDescriptor, buf, 128);
            write(1, buf, bytesRead);
        }
        
        close(fileDescriptor);
    }
    exit(0);
}