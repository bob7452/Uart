#ifndef IO_OPERATION
#define IO_OPERATION

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/asio.hpp>
#include <error.h>
#include <boost/asio/io_service.hpp>
#include <stdexcept>
#include <boost/filesystem.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/core/scoped_enum.hpp>

class File_IO{

    private:
        bool debug = false;
    public:
        
        /*sync io service*/
        void readFile(std::vector<std::string> & lines , const std::string& filepath);
        void writeFile(const std::string& filepath, const std::vector<std::string>& content);

        /*async io service*/
        void writeFileAsync(const std::string& filepath, const std::vector<std::string>& content, std::function<void(bool)> callback);

        /*sync Binary file*/
        void readBinaryFile(std::vector<char>& buffer, const std::string& filepath);
        void writeBinaryFile(const std::string& filepath, const std::vector<char>& content);



        explicit File_IO(bool debug);
        ~File_IO(void);
};

#endif
