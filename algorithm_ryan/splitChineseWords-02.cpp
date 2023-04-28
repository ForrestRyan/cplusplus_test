#include <iostream>
#include <string>

static constexpr int UTF8_1_BYTE_LEAD = 0x00;
static constexpr int UTF8_2_BYTE_LEAD = 0xC0;
static constexpr int UTF8_3_BYTE_LEAD = 0xE0;
static constexpr int UTF8_4_BYTE_LEAD = 0xF0;
static constexpr int UTF8_MULTI_BYTE_MASK = 0x80;

static constexpr uint32_t SIMPLIFIED_CHINESE_START = 0x4E00;
static constexpr uint32_t SIMPLIFIED_CHINESE_END = 0x9FFF;
static constexpr uint32_t TRADITIONAL_CHINESE_START = 0x3400;
static constexpr uint32_t TRADITIONAL_CHINESE_END = 0x4DBF;

// You can find the Unicode Standard at the following
// URL:http://www.unicode.org/versions/Unicode13.0.0/
// The specification for the variable-length encoding of UTF-8 can be found in Chapter 3 of the
// Unicode Standard.
// URL:http://www.unicode.org/versions/Unicode13.0.0/ch03.pdf
// Specifically, the section "UTF-8 Encoding Scheme" in that chapter describes how the encoding
// works,including how characters are divided into different numbers of bytes based on their Unicode
// code point values.
std::string splitChineseCharacters(const std::string& input)
{
    if (input.size() < 2) {
        return input;
    }

    size_t index = 0;
    size_t indexOfNonChinese = 0;
    std::string result;
    result.reserve(input.size() * 2);

    auto appendNonChinese = [&input, &index, &indexOfNonChinese, &result]() {
        if (index > indexOfNonChinese) {
            if (!result.empty() && !std::isspace(input[indexOfNonChinese])) {
                // insert whitespace when : 1. not first and 2. not started with whitespace
                result += ' ';
            }
            result += input.substr(indexOfNonChinese, index - indexOfNonChinese);
        };
    };
    while (index < input.size()) {
        char ch = input[index];
        unsigned int chInt = static_cast<unsigned int>(ch);
        unsigned int codePoint = 0;
        size_t charLen = 1;

        if ((chInt & UTF8_MULTI_BYTE_MASK) == UTF8_1_BYTE_LEAD) {
            codePoint = chInt;
        } else if ((chInt & 0xE0) == UTF8_2_BYTE_LEAD) {
            charLen = 2;
            codePoint = (chInt & 0x1F) << 6;
        } else if ((chInt & 0xF0) == UTF8_3_BYTE_LEAD) {
            charLen = 3;
            codePoint = (chInt & 0x0F) << 12;
        } else if ((chInt & 0xF8) == UTF8_4_BYTE_LEAD) {
            charLen = 4;
            codePoint = (chInt & 0x07) << 18;
        } else {
            // Log::error("DialogEngine", "Error: Invalid UTF-8 byte0 : {}", chInt);
            return input;
        }
        if ((index + charLen) > input.size()) {
            // Log::error("DialogEngine", "Error: Invalid UTF-8 string as out of range");
            return input;
        }

        for (size_t i = 1; i < charLen; i++) {
            ch = input[index + i];
            chInt = static_cast<unsigned int>(ch);
            if ((chInt & 0xC0) != 0x80) {
                // Log::error("DialogEngine", "Error: Invalid UTF-8 byte{} : {}", i, chInt);
                return input;
            }
            codePoint |= (chInt & 0x3F) << (6 * (charLen - 1 - i));
        }

        if ((codePoint >= SIMPLIFIED_CHINESE_START && codePoint <= SIMPLIFIED_CHINESE_END)
            || (codePoint >= TRADITIONAL_CHINESE_START && codePoint <= TRADITIONAL_CHINESE_END)) {
            // append the non Chinese first if existed
            appendNonChinese();
            indexOfNonChinese = index + charLen;

            // insert whitespace if needed
            if (!result.empty() && !std::isspace(result.back())) {
                // insert whitespace when : 1. not first and 2. not ended with whitespace
                result += ' ';
            }

            // append the Chinese character
            result += input.substr(index, charLen);
        }
        index += charLen;
    }

    // append the left non Chinese character if existed
    appendNonChinese();
    return result;
}


#include <vector>
#include <algorithm>

void handle(std::vector<std::string>& items)
{
    for_each(items.begin(), items.end(), [](std::string& item){
        std::cout << splitChineseCharacters(item) << std::endl;
    });
}

struct Data
{
    std::string text;
};

struct SystemResponse
{
    std::vector<Data> ttsResponse;
};

using namespace std;

int main()
{
    std::string input1 = "hello你好世界hell world！@#￥%&*（）——+~o·里!@#$$%^&*()~+_？、：:“”''"; // UTF-8 encoded string
    std::string input2 = "我暫時操作唔到hello車內空氣123循環功能 肯德hello基颐123堤港店 朝阳区"; // UTF-8 encoded string
    std::vector<std::string> items;
    items.push_back(input1);
    items.push_back(input2);

    handle(items);

    return 0;
}
