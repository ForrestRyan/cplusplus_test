#include <iostream>
#include <string>

static const int UTF8_1_BYTE_LEAD = 0x00;
static const int UTF8_2_BYTE_LEAD = 0xC0;
static const int UTF8_3_BYTE_LEAD = 0xE0;
static const int UTF8_4_BYTE_LEAD = 0xF0;
static const int UTF8_MULTI_BYTE_MASK = 0x80;

static const uint32_t SIMPLIFIED_CHINESE_START = 0x4E00;
static const uint32_t SIMPLIFIED_CHINESE_END = 0x9FFF;
static const uint32_t TRADITIONAL_CHINESE_START = 0x3400;
static const uint32_t TRADITIONAL_CHINESE_END = 0x4DBF;

static int splitChineseCharacters(std::string& dccInput)
{
    size_t index = 0;
    std::string result = "";
    char dccChar;
    unsigned int dccInt, codePoint;
    bool bPreChinese = true;

    if (dccInput.size() < 2) {
        return 0;
    }

    while (index < dccInput.size()) {
        dccChar = dccInput.at(index);
        dccInt = static_cast<unsigned int>(dccChar);
        codePoint = 0;
        size_t charLen = 1;
        if ((dccInt & UTF8_MULTI_BYTE_MASK) == UTF8_1_BYTE_LEAD) {
            codePoint = dccInt;
        } else if ((dccInt & 0xE0) == UTF8_2_BYTE_LEAD) {
            charLen = 2;
            codePoint = (dccInt & 0x1F) << 6;
        } else if ((dccInt & 0xF0) == UTF8_3_BYTE_LEAD) {
            charLen = 3;
            codePoint = (dccInt & 0x0F) << 12;
        } else if ((dccInt & 0xF8) == UTF8_4_BYTE_LEAD) {
            charLen = 4;
            codePoint = (dccInt & 0x07) << 18;
        } else {
            // Log::error("DialogEngine", "Error: Invalid UTF-8 string");
            return -1;
        }

        for (size_t i = 1; i < charLen; i++) {
            dccChar = dccInput.at(index + i);
            dccInt = static_cast<unsigned int>(dccChar);
            if ((dccInt & 0xC0) != 0x80) {
                // Log::error("DialogEngine", "Error: Invalid UTF-8 string");
                return -1;
            }
            codePoint |= (dccInt & 0x3F) << (6 * (charLen - 1 - i));
        }

        if ((codePoint >= SIMPLIFIED_CHINESE_START && codePoint <= SIMPLIFIED_CHINESE_END)
            || (codePoint >= TRADITIONAL_CHINESE_START && codePoint <= TRADITIONAL_CHINESE_END)) {
            if(!bPreChinese) {
                result += " ";
            }
            result += dccInput.substr(index, charLen) + " ";
            bPreChinese = true;
        } else {
            result += dccChar;
            bPreChinese = false;
        }
        index += charLen;
    }

    std::cout << "before: " << result.size() << std::endl;
    auto first = result.find_first_not_of(" ");
    auto last = result.find_last_not_of(" ");
    result = result.substr(first, last - first + 1);
    std::swap(dccInput, result);
    std::cout << "after: " << dccInput.size() << std::endl;

    return 0;
}

#include <vector>
#include <algorithm>

void handle(std::vector<std::string>& items)
{
    for_each(items.begin(), items.end(), [](std::string& item){
        splitChineseCharacters(item);
    });

    std::cout << items.at(0) << std::endl;
}
int main()
{
    std::string ddcInput = "我暫時操作唔到hello車內空氣123循環功能 肯德hello基颐123堤港店 朝阳区"; // UTF-8 encoded string
    std::vector<std::string> items;
    items.push_back(ddcInput);
    handle(items);

    return 0;
}
