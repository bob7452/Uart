#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "../../includes/io.hpp"
#include <stdio.h>

static void print(const std::string & message){
    std::cout << message << std::endl;
}

static const std::string bin_path = "/home/ponder/Desktop/projects/sample/UartDataBuff_ttyUSB0.bin";
static const std::string rule_path = "/home/ponder/Desktop/projects/sample/LogSetting.txt";

static void test_read_bin(File_IO* & file_io,const std::string & path){
    
    print("start test read bin");

    std::vector<char> bin;
    file_io->readBinaryFile(bin,path);
    
    long long index = 0;
    for(auto &bin_data : bin){
        
        if (index == 32)
            break;
       
        unsigned char data = static_cast<unsigned char>(bin_data);
        printf("0x%02X\n",data);
        index++;
    }
}

static void test_read_file(File_IO* & file_io , const std::string &path){
    
    print("start test read file");

    std::vector<std::string> lines;
    file_io->readFile(lines,rule_path);
  
    unsigned int rows = 0;
    for(auto &line : lines){
    
        if(rows == 64)
            break;

        print(line);
    } 
}


int main(){
    print("start Test File IO");
    
    File_IO * file_io = new File_IO(false);
    
    test_read_bin(file_io,bin_path);
    test_read_file(file_io,rule_path);
    
    delete file_io; 
    file_io = nullptr;   

    return 0;
}
