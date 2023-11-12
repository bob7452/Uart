#include "../includes/io.hpp"

File_IO::File_IO(bool debug): debug(debug){
    std::cout << "Enable Debug Mode" << debug << std::endl;
}

File_IO::~File_IO(){
}

std::vector<std::string> File_IO::readFile(const std::string& filepath){
    boost::asio::io_service ioService;
    boost::asio::io_service::work work(ioService); 
    
    std::vector<std::string> lines;

    ioService.post([&]() {
        std::ifstream inputFile(filepath);
        if (inputFile.is_open()) {
            std::string line;
            
            while (getline(inputFile, line))
                lines.push_back(line);
            
            inputFile.close();
        } 
        else{
            std::cerr << "Unable to open file: " << filepath << std::endl;
            throw std::runtime_error("Unable to open file for reading : "+ filepath);
        }
    });

    // stuck, until service done.
    ioService.run();
    return lines; 
}

void File_IO::writeFile(const std::string& filepath, const std::vector<std::string>& content) {
    boost::asio::io_service ioService;
    boost::asio::io_service::work work(ioService);

    int writeResult = 0;

    ioService.post([&]() {
        std::ofstream outputFile(filepath);
        if (outputFile.is_open()) {
            for (const auto& line : content)
                outputFile << line << std::endl;
            outputFile.close();
        } 
        else{
            std::cerr << "Unable to open file for writing: " << filepath << std::endl;
            throw std::runtime_error("Unable to open file for writing : "+filepath);
        }
    });

    // stuck, until service done.
    ioService.run();
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

std::vector<char> File_IO::readBinaryFile(const std::string& filepath){
    std::ifstream inputFile(filepath, std::ios::binary);

    if (!inputFile.is_open()) {
        throw std::runtime_error("Error opening binary file: " + filepath);
    }

    inputFile.seekg(0, std::ios::end);
    std::streamsize fileSize = inputFile.tellg();
    inputFile.seekg(0, std::ios::beg);

    std::vector<char> buffer(fileSize);
    inputFile.read(buffer.data(), fileSize);

    inputFile.close();

    return buffer;
}

void File_IO::writeBinaryFile(const std::string& filepath, const std::vector<char>& content) {
    std::ofstream outputFile(filepath, std::ios::binary);

    if (!outputFile.is_open()) {
        throw std::runtime_error("Error opening binary file for writing: " + filepath);
    }
    outputFile.write(content.data(), content.size());
    
    outputFile.close();
}

