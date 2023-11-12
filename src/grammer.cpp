#include "../includes/grammer.hpp"
#include <cstddef>
#include <cstdio>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

Grammer::Grammer(const std::string& path, bool debug) : path(path) , debug(debug){
    std::cout << "create grammer path : " << path << std::endl;
    
    if (debug)
        std::cout << "Enable Debug Mode" << debug << std::endl;
}

Grammer::~Grammer(){
}

void Grammer::showMap(){
    std::cout << "Show Map " << std::endl;

    for (auto& n : this->string_map){
        std::cout << "key_header : " << n.first << std::endl;
        std::cout << "words : " <<  n.second << std::endl;
        
        for(auto byte : this->hex_map[n.first])
            std::cout << "bytes : " << byte <<std::endl;

    }
}

int Grammer::header2int(const std::string & line){
    std::string origin = line;
    origin.erase(std::remove(origin.begin(),origin.end(),' '),origin.end());
    
    unsigned long header;
    std::istringstream(origin) >> std::hex >> header;

    if(this->debug)
        std::cout << "Debug Header " << header << std::endl;

    return header;
}

void Grammer::getbytes(const std::string& line, std::vector<char>& buffer){
    
    for(auto &chars : line){
        if (isspace(chars))
            continue;
        if(this->debug)
            std::cout << "Debug Bytes " << chars << std::endl;
        buffer.push_back(chars);
    }   
}

void Grammer::split_word(std::string line,std::string pattern, std::vector<std::string> & buffer){
    std::size_t left  = line.find(pattern);
    std::size_t right = line.rfind(pattern);

    if (left == std::string::npos || right == std::string::npos)
        return;

    int wordlens = right - left -1;
    int lens     = line.size();

    std::string header = line.substr(0,left);
    std::string word   = line.substr(left+1,wordlens);
    std::string bytes  = line.substr(right+1,lens - right);
    
    if (this->debug){
        std::cout << "Debug " << header << std::endl;
        std::cout << "Debug " << word   << std::endl;
        std::cout << "Debug " << bytes  << std::endl;
    }

    buffer.push_back(header);
    buffer.push_back(word);
    buffer.push_back(bytes);
}

int Grammer::initialize_grammer(void){
    
    int result = 0;

    File_IO* file_io = new File_IO(this->debug);
    std::vector<std::string> lines;
   
    try{
        file_io->readFile(lines,this->path);
    }
    catch (const std::runtime_error& e){
        std::cerr << e.what();
        result =  EIO; 
        goto Error_Handle;
    } 

    for(auto &line : lines){
        std::vector<std::string> split_words;
        this->split_word(line,",",split_words);
        
        if(!split_words.empty()){
            unsigned long key_header = this->header2int(split_words[0]);
            std::vector<char> bytes;
            this->getbytes(split_words[2],bytes);
            this->hex_map.insert({key_header,bytes});
            this->string_map.insert({key_header,split_words[1]});
        }
    }

    if(this->debug)
        this->showMap();    

    Error_Handle:
        if(file_io != nullptr) delete file_io, file_io = nullptr; 
        return result;
}
