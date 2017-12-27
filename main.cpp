#include <iostream>
#include <fstream>
#include <string>
#include <streambuf>

#include <tgbot/bot.h>

using namespace tgbot;

std::string readToken(std::string file) {
    std::ifstream tokf(file);
    std::string token;
    tokf.seekg(0, std::ios::end);
    token.reserve(tokf.tellg());
    tokf.seekg(0, std::ios::beg);
    token.assign(
        (std::istreambuf_iterator<char>(tokf)),
         std::istreambuf_iterator<char>()
    );
    tokf.close();
    return token;
}

int main() {
    try {
        Bot bot(readToken("data/token"));
    } catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
