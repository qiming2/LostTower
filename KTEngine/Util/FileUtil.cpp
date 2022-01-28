#include <fstream>
#include <sstream>
#include "FileUtil.h"
#include "k_print.h"

std::string FileUtil::readAll(const char* filePath)
{
    std::ifstream in;
    in.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    std::string content;
    try {
        in.open(filePath);
        std::stringstream stream;
        stream << in.rdbuf();
        in.close();
        content = stream.str();
    }
    catch (std::ifstream::failure e) {
        ekp("FILE::READ_FAILED\n FILE: ", __FILE__, " passed in: ", filePath);
    }
    return content;
}
