#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "../../includes/grammer.hpp"
#include <stdio.h>

static void print(const std::string & message){
    std::cout << message << std::endl;
}

static const std::string rule_path  = "/home/ponder/Desktop/projects/sample/LogSetting.dat";
static const std::string bin_path  = "/home/ponder/Desktop/projects/sample/UartDataBuff_ttyUSB0.bin";


int main(){
    print("start Test Grammer");
    
    Grammer * grammer = new Grammer(rule_path,true);
    grammer->initialize_grammer();

    if(grammer != nullptr) delete grammer , grammer = nullptr; 

    return 0;
}
