#include "../includes/io.hpp"
#include <vector>

File_IO::File_IO(bool debug): debug(debug){
    if(debug)
        std::cout << "Enable Debug Mode" << std::endl;
}

File_IO::~File_IO(){
}

void File_IO::readFile(std::vector<std::string> & lines, const std::string& filepath){
    std::ifstream inputFile(filepath);
    if (!inputFile.is_open()) {
        std::cerr << "Unable to open file: " << filepath << std::endl;
        throw std::runtime_error("Unable to open file for reading: " + filepath);
    }

    std::string line;
    while (getline(inputFile, line)) {
        if (this->debug)
            std::cout << "Debug " << line << std::endl;
        lines.emplace_back(line);
    }

    inputFile.close();
}

void File_IO::writeFile(const std::string& filepath, const std::vector<std::string>& content) {
    std::ofstream outputFile(filepath);
    if (outputFile.is_open()) {
        for (const auto& line : content) {
            outputFile << line << std::endl;
        }
        outputFile.close();
    } else {
        std::cerr << "Unable to open file for writing: " << filepath << std::endl;
        throw std::runtime_error("Unable to open file for writing: " + filepath);
    }
}

void File_IO::writeFileAsync(const std::string& filepath, const std::vector<std::string>& content, std::function<void(bool)> callback){
    boost::asio::io_service ioService;
    
    std::ofstream outputFile(filepath);
    if (!outputFile.is_open()) {
        std::cerr << "Unable to open file for writing: " << filepath << std::endl;
        callback(false);
        return;
    }

    boost::asio::spawn(ioService, [&](boost::asio::yield_context yield) {
        try {
            for (const auto& line : content) {
                outputFile << line << std::endl;
            }
            outputFile.close();
            callback(true);
        } catch (const std::exception& e) {
            std::cerr << "Error writing to file: " << e.what() << std::endl;
            callback(false);
        }
    });

    ioService.run();
}

void File_IO::readBinaryFile(std::vector<char>& buffer, const std::string& filepath){
    std::ifstream inputFile(filepath, std::ios::binary);

    if (!inputFile.is_open()) {
        throw std::runtime_error("Error opening binary file: " + filepath);
    }

    const std::streamsize chunkSize = 4096; 

    while (true) {
        std::vector<char> chunk(chunkSize);
        inputFile.read(chunk.data(), chunkSize);

        if(this->debug)
            std::cout << "Debug Mode read bin file" << std::endl;

        if (inputFile.gcount() <= 0) {
            break;
        }

        buffer.insert(buffer.end(), chunk.begin(), chunk.begin() + inputFile.gcount());
    }

    inputFile.close();
}

void File_IO::writeBinaryFile(const std::string& filepath, const std::vector<char>& content) {
    std::ofstream outputFile(filepath, std::ios::binary);

    if (!outputFile.is_open()) {
        throw std::runtime_error("Error opening binary file for writing: " + filepath);
    }
    outputFile.write(content.data(), content.size());
    
    outputFile.close();
}

