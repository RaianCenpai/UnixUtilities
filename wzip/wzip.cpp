#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char* argv[]) {
    if(argc == 1) {
        char message[] = "wzip: file1 [file2 ...]\n";
        write(1, message, sizeof(message)-1);
        exit(1);
    } else {
        int count = 1;
        char countChar[1] = "";
        char nextChar[1] = "";
        for(int i = 1; i < argc; i++) {
            int fileDescriptor = open(argv[i], O_RDONLY);
            if(fileDescriptor < 0) {
                char message[] = "wzip: cannot open file\n";
                write(1, message, sizeof(message)-1);
                exit(1);
            }
            
            int eof = 0;

            read(fileDescriptor, countChar, 1);
            if(countChar[0] != nextChar[0]) {
                count = 1;
            } else {
                count++;
            }

            
            while(eof != 1) {
                
                int BytesRead = read(fileDescriptor, nextChar, 1);
                if(BytesRead == 0) {
                    eof = 1;
                    break;
                }
                

                if(countChar[0] == nextChar[0]) {
                    count++;
                } else {
                    write(1, &count, 4);
                    write(1, countChar, 1);
                    countChar[0] = nextChar[0];
                    count = 1;
                }
                
            }
            

            close(fileDescriptor);
        }
        write(1, &count, 4);
        write(1, countChar, 1);
    
    }
    exit(0);
}