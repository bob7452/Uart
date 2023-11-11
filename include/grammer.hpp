#ifndef GRAMMER
#define GRAMMER

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <errno.h>

class Grammer{
    
    public:        
        explicit Grammer(std::string path);
        ~Grammer();

    private:
        std::string spec_path;
        std::unordered_map<int,std::string> string_map = {}; 
        std::unordered_map<int,std::vector<int>>  hex_map = {};
};

#endif
