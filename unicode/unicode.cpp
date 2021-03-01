#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <bitset>
#include <locale>
#include <clocale>
#include <codecvt>
#include <map>
#pragma execution_character_set("utf-8")

std::string utf(std::string bin, int dec) {
    std::stringstream result;
    if (dec >= 0 && dec <= 127) {
        std::bitset <8> bits(bin);
        result << std::hex << bits.to_ulong();
    }
    else if (dec >= 128 && dec <= 2047) {
        std::bitset <16> bits(bin);
        result << std::hex << bits.to_ulong();
    }
    else if (dec >= 2048 && dec <= 65535) {
        std::bitset <24> bits(bin);
        result << std::hex << bits.to_ulong();
    }
    else {
        std::bitset <32> bits(bin);
        result << std::hex << bits.to_ulong();
    }
    return result.str();
}

std::string decToBin(int n) {
    std::string binNum;
    int i = 0;
    while (n > 0)
    {
        int num = n % 2;
        binNum.insert(0, std::to_string(num));
        n = n / 2;
        i++;
    }
    return binNum;
}

std::string bytes(int decimal) {
    std::string binary;
    if (decimal >= 0 && decimal <= 127) {
        binary = decToBin(decimal);
        while (binary.length() < 8) {
            binary.insert(0, "0");
        }
    }
    else if (decimal >= 128 && decimal <= 2047) {
        binary = "110xxxxx10xxxxxx";
        std::string binary1 = decToBin(decimal);
        int index = binary1.length() - 1;
        for (int i = binary.size(); i >= 0; i--) {
            if (binary[i] == 'x') {
                if (index >= 0) {
                    binary[i] = binary1[index];
                    index--;
                }
                else {
                    binary[i] = '0';
                }
            }
        }
    }
    else if (decimal >= 2048 && decimal <= 65535) {
        binary = "1110xxxx10xxxxxx10xxxxxx";
        std::string binary1 = decToBin(decimal);
        int index = binary1.length()-1;
        for (int i = binary.size(); i >= 0; i--) {
            if (binary[i] == 'x') {
                if (index >= 0) {
                    binary[i] = binary1[index];
                    index--;
                }
                else {
                    binary[i] = '0';
                }
            }
        }
    }
    else {
        binary = "11110xxx10xxxxxx10xxxxxx10xxxxxx";
        std::string binary1 = decToBin(decimal);
        int index = binary1.length() - 1;
        for (int i = binary.size(); i >= 0; i--) {
            if (binary[i] == 'x') {
                if (index >= 0) {
                    binary[i] = binary1[index];
                    index--;
                }
                else {
                    binary[i] = '0';
                }
            }
        }
    }
    return binary;
}

void converter() {
    int dec;
    const std::locale utf8_locale = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>());
    std::stringstream unic;
    std::cout << "Enter the decimal character value: ";
    std::cin >> dec;
    std::cout << std::endl << "Check '1dalisRez.txt' file";
    std::string unicode, binary, utf8 = utf(bytes(dec), dec);
    std::ofstream fout("1dalisRez.txt");
    fout << "Decimal value: " << dec<<std::endl;
    unic << std::hex << std::setfill('0')<<std::setw(4)<<dec;
    unic >> unicode;
    wchar_t symbol = strtol(unicode.c_str(), NULL, 16);
    fout << "Unicode value: U+" << unicode<<std::endl;
    fout << "Byte value: " << bytes(dec) << std::endl;
    fout << "Utf-8: " << utf8 << std::endl;
    fout.close();
    std::wofstream fout1("1dalisRez.txt", std::ios::app);
    fout1.imbue(utf8_locale);
    fout1 << "Character: " << symbol << std::endl;
    fout1.close();
}

void part2() {
    std::wstring eilute;
    std::string unicode;
    std::stringstream unic;
    int decimal;
    const std::locale utf8_locale = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>());
    std::ifstream table("cp437.txt");
    std::map<int, std::string> lentele;
    int table_input=666;
    std::map<int, std::string>::iterator j;
    while (!table.eof()) {
        table >> table_input;
        std::string hex;
        table >> hex;
        lentele[table_input] = hex;
    }
    table.close();
    std::wifstream fin("lilpartoftext.txt");
    std::wofstream fout("2dalisRez.txt");
    bool isFound = false;
    while (!fin.eof()) {
        std::getline(fin, eilute);
        for (int i = 0; i < eilute.size(); i++) {
            decimal = (int)eilute[i];
            unic << std::hex << std::setfill('0') << std::setw(4) << decimal;
            unic >> unicode;
            if (decimal > 127 && decimal < 256) {
                for (auto j=lentele.begin(); j!=lentele.end(); j++) {
                    if (j->first == decimal) {
                        unicode = j->second;
                        isFound = true;
                        break;
                    }
                }
                if (isFound) {
                    int newDec = stoi(unicode, 0, 16);
                    std::string bin = decToBin(newDec);
                    std::string utf8 = utf(bin, newDec);
                    wchar_t galutinis = strtol(utf8.c_str(), NULL, 16);
                    fout.imbue(utf8_locale);
                    fout << galutinis;
                }
                isFound = false;
            }
            else
            {
                fout << eilute[i];
            }
        }
        fout << std::endl;
    }
    fout.close();
    fin.close();
    std::cout << "Check '2dalisRez.txt' file" << std::endl;
}

int main()
{
    //setlocale(LC_ALL, "");
    int part;
    std::cout << "This is unicode/utf-8 converter" << std::endl;
    std::cout << "[1-2]?";
    std::cin >> part;
    if (part == 1) {
        converter();
    }
    else if (part == 2) {
        part2();
    }
}