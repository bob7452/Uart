#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "../../includes/io.hpp"
#include <stdio.h>

static void print(const std::string & message){
    std::cout << message << std::endl;
}

static const std::string path = "/home/ponder/Desktop/projects/sample/UartDataBuff_ttyUSB0.bin";

int main(){
    print("start Test File IO");
    
    File_IO * file_io = new File_IO(false);
    
    
    std::vector<char> bin;
    bin = file_io->readBinaryFile(path);

    long long index = 0;
    for(auto &bin_data : bin){
        
        if (index == 32)
            break;
       
        unsigned char data = static_cast<unsigned char>(bin_data);
        printf("0x%02X\n",data);
        index++;
    }

    delete file_io; 
    file_io = nullptr;   

    return 0;
}
