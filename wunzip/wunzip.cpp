#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>


int main(int argc, char* argv[]) {
    if(argc == 1) {
        char message[] = "wunzip: file1 [file2 ...]\n";
        write(1, message, sizeof(message)-1);
        exit(1);
    } else {
        for(int i = 1; i < argc; i++) {
            int fileDescriptor = open(argv[i], O_RDONLY);
            if(fileDescriptor < 0) {
                char message[] = "wzip: cannot open file\n";
                write(1, message, sizeof(message)-1);
                exit(1);
            }
            int eof = 0;

            while(eof != 1) {
                int nextValue;
                char nextChar;
                int BytesRead = read(fileDescriptor, &nextValue, 4);
                if(BytesRead == 0) {
                    eof = 1;
                    break;
                }

                read(fileDescriptor, &nextChar, 1);

                for(int i = 0; i < nextValue; i++) {
                    write(1, &nextChar, 1);
                }
            }
            

            close(fileDescriptor);
        }
    
    }
    exit(0);
}