#include <iostream>
#include <cstring>
#include <cstdint>
#include <string>
#include <algorithm>
#include <locale>
#include <codecvt>
#include <vector>

bool hasChinese(const std::string& text, std::vector<size_t>& poses) {
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> cv;
    std::u32string utf32 = cv.from_bytes(text);
    size_t pose = 0;
    bool bInclude = false;

    poses.clear();
    for (char32_t code_point : utf32) {
        if ((code_point >= 0x4e00 && code_point <= 0x9fff) || (code_point >= 0x3400 && code_point <= 0x4DBF)) {
            poses.push_back(pose);
            bInclude = true;
        }
        pose++;
    }

    return bInclude;
}

size_t getChineseText(const std::string& strInput, std::string& subText, size_t pos)
{
    size_t charLen = 0;
    if ((strInput[pos] & 0x80) == 0) {
        return 1;
    } else if ((strInput[pos] & 0xE0) == 0xC0) {
        charLen = 2;
    } else if ((strInput[pos] & 0xF0) == 0xE0) {
        charLen = 3;
    } else if ((strInput[pos] & 0xF8) == 0xF0) {
        charLen = 4;
    }

    if(pos + charLen < strInput.size())
    {
        subText = strInput.substr(pos, charLen);
    }
    else {
        charLen = strInput.size() - pos;
        subText = strInput.substr(pos);
    }

    return charLen;
}

std::string splitChineseWords(const std::string& dynContent, std::vector<size_t>&& poses)
{
    std::string result = "";
    size_t prePose = 0;
    size_t offset = 0;
    std::for_each(poses.cbegin(),poses.cend(), [&](size_t pose) {
        if(offset == 0 &&  pose != 0) {
            result += dynContent.substr(0, pose) + " ";
        }
        else if(pose - prePose > 1) {
            result += dynContent.substr(prePose+offset+1, pose-prePose-1) + " ";
        }

        std::string subContent = "";
        size_t charLen = getChineseText(dynContent, subContent, pose+offset);
        result += subContent + " ";
        offset += charLen-1;
        prePose = pose;
    });

    std::cout << "prePose + offset: " << prePose + offset << "dynContent.size(): " << dynContent.size() << std::endl;
    if(prePose + offset + 1 < dynContent.size()) {
        result += dynContent.substr(prePose + offset);
    }

    std::cout << "before: " << result.size() << std::endl;
    result.erase(result.find_last_not_of(" ")+1);
    result.erase(0, result.find_first_not_of(" "));
    std::cout << "after: " << result.size() << std::endl;

    return result;
}

int main() {
    std::string utf8Str = "我暫時操作唔到hello車內空氣123循環功能 肯德hello基颐123堤港店 朝阳区   ";
    std::vector<size_t> poses;
    if(hasChinese(utf8Str, poses)) {
        std::cout << splitChineseWords(utf8Str, std::move(poses)) << std::endl;
    }
    
    if(hasChinese(utf8Str, poses)) {
        std::cout << splitChineseWords(utf8Str, std::move(poses)) << std::endl;
    }
    return 0;
}