#include "../includes/grammer.hpp"

Grammer::Grammer(const std::string& path, bool debug) : path(path) , debug(debug){
    std::cout << "create grammer path : " << path << std::endl;
    std::cout << "Debug Mode" << debug << std::endl;
}

Grammer::~Grammer(){
}

int Grammer::initialize_grammer(void){    
    return 0;
}
