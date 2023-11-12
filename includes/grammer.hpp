#ifndef GRAMMER
#define GRAMMER

#include <sstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include "io.hpp"

class Grammer{
    
    private:
        std::string path ="";
        bool debug = false;
        std::unordered_map<int,std::string> string_map = {}; 
        std::unordered_map<int,std::vector<char>>  hex_map = {}; 
        void split_word(std::string line,std::string pattern);
        int  header2int(const std::string & line);
        void storebytes(const std::string & line, std::vector<char> & buffer);

    public:        
        explicit Grammer(const std::string& path,bool debug);
        ~Grammer();
        
        int initialize_grammer(void);
};

#endif
