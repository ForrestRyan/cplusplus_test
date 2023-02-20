#include <iostream>
#include <cstring>
#include <cstdint>
#include <string>
#include <cmath>

bool isChineseChar(const char* utf8Str, int pos, unsigned int charLen) {
    // Check if the byte is a valid UTF-8 lead byte
    if ((utf8Str[pos] & 0x80) == 0) return false;

    // Check if the character is Chinese
    int code = 0;
    for (int len = 1; len < charLen; ++len) {
        code = (code << 6) | (utf8Str[pos + len] & 0x3F);
    }
    unsigned int high = std::pow(2, (8-charLen)) - 1;
    code |= (utf8Str[pos] & high) << (6 * (charLen - 1));
    return (code >= 0x4E00 && code <= 0x9FFF || code >= 0x3400 && code <= 0x4DBF);
}

std::string insertBlank(const std::string& utf8Str) {
    std::string result;
    int len = utf8Str.length();

    for (int pos = 0; pos < len;) {
        int charLen = 0;
        if ((utf8Str[pos] & 0x80) == 0) {
            charLen = 1;
        } else if ((utf8Str[pos] & 0xE0) == 0xC0) {
            charLen = 2;
        } else if ((utf8Str[pos] & 0xF0) == 0xE0) {
            charLen = 3;
        } else if ((utf8Str[pos] & 0xF8) == 0xF0) {
            charLen = 4;
        }

        if (isChineseChar(utf8Str.c_str(), pos, charLen)) {
            result += " " + utf8Str.substr(pos, charLen) + " ";
        }
        else {
            result += utf8Str.at(pos);
        }

        pos += charLen;
        // std::cout << "result: " << result << std::endl;
    }
    auto first = result.find_first_not_of(" ");
    auto last = result.find_last_not_of(" ");
    return result.substr(first, last-first+1);
}

int main() {
    std::string utf8Str = "我暫時操作唔到hello車內空氣123循環功能 肯德hello基颐123堤港店 朝阳区   ";
    std::cout << insertBlank(utf8Str) << std::endl;
    return 0;
}
