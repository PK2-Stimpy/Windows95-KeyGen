#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <string.h>
#include <Windows.h>
#include <vector>
#include "Header.h"
#define MAX_KEYS 10000

int KEYS_TO_GENERATE = 10;

namespace std {
    BOOL isdigit(const std::string& str) {
        std::string::const_iterator it = str.begin();
        while (it != str.end() && std::isdigit(*it)) ++it;
        return !str.empty() && it == str.end();
    }
    inline int rand(int start, int end) {
        return rand() % (end-start) + start;
    }
    int stoi(char c) {
        if (c == '0') return 0;
        if (c == '1') return 1;
        if (c == '2') return 2;
        if (c == '3') return 3;
        if (c == '4') return 4;
        if (c == '5') return 5;
        if (c == '6') return 6;
        if (c == '7') return 7;
        if (c == '8') return 8;
        if (c == '9') return 9;
        return -1;
    }
    int isDivisibleBy7(int num)
    {
        if (num < 0)
            return isDivisibleBy7(-num);
        if (num == 0 || num == 7)
            return 1;
        if (num < 10)
            return 0;
        return isDivisibleBy7(num / 10 - 2 *
            (num - num / 10 * 10));
    }
    int rand(int digits) {
        std::string V_cS = "";
        for (int i = 0; i < digits; i++)
            V_cS += std::to_string(std::rand(1, 10));
        return std::stoi(V_cS);
    }
}

int main()
{
    system("cls");
    std::cout << "Welcome to this Windows95 KeyGen.\nType what type of keys do you want to generate(normal,oem):";
    std::string input;
    std::getline(std::cin,input);
    std::transform(input.begin(), input.end(), input.begin(), [](unsigned char c) {return std::tolower(c); });
    
    if (input.find("normal") != std::string::npos)
        normal();
    else if(input.find("oem") != std::string::npos)
        oem();
    else
        main();
}
#define VALID_KEY       1
#define INVALID_KEY     0
#define INVALID_CHAR   -1
#define INVALID_LENGTH -2
#define MS_CD_KEY_LENGTH  11 /* XXX-0123456                          */
#define OEM_CD_KEY_LENGTH 23 /* XXXXX-OEM-0123456-XXXXX              */
#define REAL_KEY_LENGTH    7
#define REAL_MS_OFFSET     4
#define REAL_OEM_OFFSET   10
std::string __VALIDATION_STATE_STRING(char c) {
    if (c == VALID_KEY) return "VALID_KEY";
    if (c == INVALID_KEY) return "INVALID_KEY";
    if (c == INVALID_CHAR) return "INVALID_CHAR";
    if (c == INVALID_LENGTH) return "INVALID_LENGTH";
    return "INVALID_VALIDATION_STATE";
}
namespace normalKeyGenUtil {
    BOOL checkPattern(int patternType, int pattern) {
        if (patternType == 1)
            return 1;
        const char* patternC = std::to_string(pattern).c_str();
        int CHECK_SUM = 0;
        for (int i = 0; i <= std::strlen(patternC); i++) {
            char c = patternC[i];
            int cI = std::stoi(c);
            if (cI != -1)
                CHECK_SUM += cI;
        }
        if (std::isDivisibleBy7(CHECK_SUM))
            return 1;
        return 0;
    }
    char ValidateCDKey(char* szKey)
    {
        unsigned long ulCheckSum = 0L;
        int iStrLength;
        int i = 0;

        iStrLength = strlen(szKey);
        if (iStrLength != MS_CD_KEY_LENGTH && iStrLength != OEM_CD_KEY_LENGTH)
            return INVALID_LENGTH;
        szKey += iStrLength == MS_CD_KEY_LENGTH ? REAL_MS_OFFSET :
            REAL_OEM_OFFSET;

        while (i < REAL_KEY_LENGTH)
        {
            if (isdigit(*szKey))
            {
                ulCheckSum += ((int)*szKey - 48);
            }
            else
                return INVALID_CHAR;

            szKey++;
            i++;

        }

        if (!(ulCheckSum % 7))
            return VALID_KEY;

        return INVALID_KEY;
    }
}
int normal() {
    system("cls");
    std::vector<int> __V_KEY2;
    std::vector<std::string> __V_KEY;
    std::string strQ = (std::string)"How much keys do you want to generate? (" + std::to_string(KEYS_TO_GENERATE) + (std::string)")? ";
    std::cout << strQ;
    std::string input;
    std::getline(std::cin,input);
    if (std::isdigit(input)) {
        if (std::stoi(input) <= MAX_KEYS)
            KEYS_TO_GENERATE = std::stoi(input);
        else
            KEYS_TO_GENERATE = MAX_KEYS;
    }
    std::cout << std::string("\nGenerating " + std::to_string(KEYS_TO_GENERATE) + " keys...") << std::endl;
    for (int i = 0; i < KEYS_TO_GENERATE; i++) {
        int KEY_1 = std::rand(100,999);
        while(!normalKeyGenUtil::checkPattern(1,KEY_1)) KEY_1 = std::rand(100, 999);
        std::cout << "KEY_1 -> Ok!" << std::endl;
        int KEY_2 = std::rand(7);
        while (!normalKeyGenUtil::checkPattern(1, KEY_2) && !std::count(__V_KEY2.begin(), __V_KEY2.end(), KEY_2)) { 
            std::cout << "KEY_2___CHECK_1 -> Fail, " + std::to_string(KEY_2) << std::endl;
            KEY_2 = std::rand(7);
        }
        std::cout << "KEY_2___CHECK_1 -> Ok!" << std::endl;
        __V_KEY2.push_back(KEY_2);
        std::string GEN_KEY = std::string(std::to_string(KEY_1) + "-" + std::to_string(KEY_2));
        char check2 = normalKeyGenUtil::ValidateCDKey((char*)GEN_KEY.c_str());
        while (check2 != VALID_KEY && !std::count(__V_KEY.begin(),__V_KEY.end(), GEN_KEY)) {
            std::cout << "KEY_2___CHECK_2 -> Fail, " + GEN_KEY + "  <" + __VALIDATION_STATE_STRING(check2) + ">" << std::endl;
            KEY_1 = std::rand(3);
            KEY_2 = std::rand(7);
            GEN_KEY = std::string(std::to_string(KEY_1) + "-" + std::to_string(KEY_2));
            check2 = normalKeyGenUtil::ValidateCDKey((char*)GEN_KEY.c_str());
        }
        std::cout << "KEY_2___CHECK_2 -> Ok!" << std::endl << std::endl;
        __V_KEY.push_back(GEN_KEY);
        std::cout << GEN_KEY << std::endl;
    }
    std::cout << "\n\n\nDone!\nKeys:\n";
    for (int i = 0; i < __V_KEY.size(); i++) {
        std::cout << "[Key " + std::to_string(i+1) + "]  " + __V_KEY[i] << std::endl;
    }
    std::cout << std::endl;
    __V_KEY2.clear();
    __V_KEY.clear();
    system("pause");
    main();
    return 0;
}
std::string genOem(int KEY_1_1, int KEY_1_2, int KEY_2_2, int KEY_3) {
    std::string _KEY_1_1(std::to_string(KEY_1_1).substr(1, 3)),
        _KEY_1_2(std::to_string(KEY_1_2));
    if (std::to_string(KEY_1_2).length() == 3)
        _KEY_1_2 = _KEY_1_2.substr(1, 2);
    std::string _KEY_2_1 = "0",
        _KEY_2_2 = std::to_string(KEY_2_2);

    std::string _KEY_1 = _KEY_1_1 + _KEY_1_2,
                _KEY_2 = _KEY_2_1 + _KEY_2_2,
                _KEY_3 = std::to_string(KEY_3);

    std::string _KEY = _KEY_1 + "-OEM-" + _KEY_2 + "-" + _KEY_3;
    std::cout << "__OEM_FIXER -> GenOem[" + _KEY_1_1 + "," + _KEY_1_2 + "," + _KEY_2_1 + "," + _KEY_2_2 + "," + _KEY_3 + "] -> " + _KEY << std::endl;
    return _KEY;
}
void regenOemSeed(int &KEY_1_1, int &KEY_1_2, int &KEY_2_2, int &KEY_3) {
    KEY_1_1 = std::rand(1001, 1367);
    KEY_1_2 = std::rand(95, 103);
    KEY_2_2 = std::rand(6);
    KEY_3 = std::rand(5);
}
int oem() {
    system("cls");
    int KEY_1_1, KEY_1_2, KEY_2_2, KEY_3;
    std::vector<std::string> __V_KEY;
    std::string strQ = (std::string)"How much keys do you want to generate? (" + std::to_string(KEYS_TO_GENERATE) + (std::string)")? ";
    std::cout << strQ;
    std::string input;
    std::getline(std::cin, input);
    if (std::isdigit(input)) {
        if (std::stoi(input) <= MAX_KEYS)
            KEYS_TO_GENERATE = std::stoi(input);
        else
            KEYS_TO_GENERATE = MAX_KEYS;
    }
    std::cout << std::string("\nGenerating " + std::to_string(KEYS_TO_GENERATE) + " keys...") << std::endl;
    for (int i = 0; i < KEYS_TO_GENERATE; i++) {
        regenOemSeed(KEY_1_1, KEY_1_2, KEY_2_2, KEY_3);
        std::string _KEY = genOem(KEY_1_1, KEY_1_2, KEY_2_2, KEY_3);
        char check = normalKeyGenUtil::ValidateCDKey((char*)_KEY.c_str());
        while (check != VALID_KEY && !std::count(__V_KEY.begin(), __V_KEY.end(), _KEY)) {
            std::cout << "__CHECK_KEY -> " + __VALIDATION_STATE_STRING(check) << std::endl;
            regenOemSeed(KEY_1_1, KEY_1_2, KEY_2_2, KEY_3);
            _KEY = genOem(KEY_1_1, KEY_1_2, KEY_2_2, KEY_3);
            check = normalKeyGenUtil::ValidateCDKey((char*)_KEY.c_str());
        }
        std::cout << "__CHECK_KEY -> Done key " + std::to_string(i + 1) + "! <" + __VALIDATION_STATE_STRING(check) + ">\n" << std::endl;
        __V_KEY.push_back(_KEY);
    }
    std::cout << "\n\nDone! Keys: \n" << std::endl;
    for (int i = 0; i < __V_KEY.size(); i++) {
        std::cout << "[Key " + std::to_string(i + 1) + "]  " + __V_KEY[i] << std::endl;
    }
    std::cout << std::endl;
    __V_KEY.clear();
    system("pause");
    main();
    return 0;
}
