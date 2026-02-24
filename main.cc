#include <drogon/drogon.h>
#include "LDClient.h"

#include <cstring>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <boost/algorithm/string.hpp>

using namespace drogon;

int main(int argc, char *argv[])
{
    std::filesystem::path file_path{".env"};
    if (std::filesystem::exists(file_path)) {
        std::ifstream file(file_path);
        if (!file.is_open()) {
            std::cerr << "Error: Unable to open file " << file_path << std::endl;
            return 1;
        }

        std::string line;
        while (std::getline(file, line)) {
            boost::trim(line);
            if (line.empty()) {
                continue;
            }
            if (line.starts_with("#")) {
                continue;
            }
            if (line.find('=') > 0) {
                std::string key = line.substr(0, line.find('='));
                std::string value = line.substr(line.find('=') + 1);
                if (setenv(key.c_str(), value.c_str(), 1) != 0) {
                    std::cerr << "Error: Unable to set an environment variable from the .env file." << std::endl;
                    return 1;
                }
            }
        }

        file.close();
    } else {
        std::cout << "Error: The .env file does not exist." << std::endl;
        return 1;
    }

    std::ofstream MyFile("./static/js/keys.js");
    MyFile << "const clientKey = \"" << std::getenv("LD_CLIENT_KEY") << "\";";
    MyFile.close();

    LDClient *ldclient = LDClient::getInstance();

    app().addListener("0.0.0.0", 3000);
    // Use executable directory as document root (static/ is copied there by CMake)
    std::string exeDir = std::filesystem::path(argv[0]).parent_path().string();
    app().setDocumentRoot(exeDir.empty() ? "./" : exeDir + "/");
    app().run();
    return 0;
}
