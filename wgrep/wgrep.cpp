#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>


int main(int argc, char* argv[]) {
    if(argc == 1) {
        char message[] = "wgrep: searchterm [file ...]\n";
        write(1, message, sizeof(message)-1);
        exit(1);
    } else if(argc == 2) {
        int eof = 0;
        while(eof != 1) {
            std::string currentLine = "";
            char currentChar[1] = "";
            int BytesRead = 0;
            while(currentChar[0] != '\n') {
                int ByteRead = read(STDIN_FILENO, currentChar, 1);
                if(ByteRead == 0) {
                    eof = 1;
                    break;
                } else {
                    BytesRead += ByteRead;
                }
                currentLine.append(currentChar);
            }

            std::size_t found = currentLine.find(argv[1]);
            if(found!=std::string::npos) {
                write(1, currentLine.c_str(), BytesRead);
            }
            
        }
        exit(0);
    } else {
        for(int i = 2; i < argc; i++) {
            int fileDescriptor = open(argv[i], O_RDONLY);
            if(fileDescriptor < 0) {
                char message[] = "wgrep: cannot open file\n";
                write(1, message, sizeof(message)-1);
                exit(1);
            }
            int eof = 0;
            while(eof != 1) {
                std::string currentLine;
                char currentChar[1] = "";
                int BytesRead = 0;
                while(currentChar[0] != '\n') {
                    int ByteRead = read(fileDescriptor, currentChar, 1);
                    if(ByteRead == 0) {
                        eof = 1;
                        break;
                    } else {
                        BytesRead += ByteRead;
                    }
                    currentLine.append(currentChar);
                }
                
                std::size_t found = currentLine.find(argv[1]);
                if(found!=std::string::npos) {
                    write(1, currentLine.c_str(), BytesRead);
                }
                
            }
            close(fileDescriptor);
        }
    
    }
    exit(0);
}