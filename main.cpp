#include "Quain.h"


void get_quain_method();

int main() {
    get_quain_method();
    return  0;
}

void get_quain_method() {
    Quain quain;
    quain.method( PDNF, std::vector<std::string>{ "ABCD", "ABcD", "ABcd", "AbCd", "AbcD", "Abcd", "aBCD", "aBCd", "aBcD"});
    quain.method( PDNF, std::vector<std::string>{ "ABCD", "ABCd", "ABcD", "ABcd", "AbCD", "Abcd", "aBCD", "aBCd", "aBcD"});
    quain.method( PDNF, std::vector<std::string>{ "ABCD", "ABCd", "ABcd", "AbCD", "AbCd", "AbcD", "Abcd", "aBCD", "aBCd", "aBcD"});
    quain.method( PDNF, std::vector<std::string>{ "ABCD", "ABcD", "ABcd", "AbCd", "AbcD", "aBCD", "aBCd"});
    quain.method( PDNF, std::vector<std::string>{ "ABCD", "ABcD", "AbcD", "aBCD", "aBcD"});
    quain.method( PDNF, std::vector<std::string>{ "ABCD", "AbCD", "AbCd", "AbcD", "aBCD", "aBCd", "aBcD"});
    quain.method( PDNF, std::vector<std::string>{ "ABcD", "ABcd", "AbCD", "AbCd", "AbcD", "aBCD", "aBCd"}); 
    std::cout << std::setfill('=') << std::setw(120) << " "  << std::endl;
    std::cout << "Готовая таблица для tex" << std::endl;
    std::cout << std::setfill('=') << std::setw(120) << " " << std::endl;
    std::cout << std::setfill(' ');
    quain.method( PDNF, std::vector<std::string>{ "ABCD", "ABcD", "ABcd", "AbCd", "AbcD", "Abcd", "aBCD", "aBCd", "aBcD"}, true, "a");
    quain.method( PDNF, std::vector<std::string>{ "ABCD", "ABCd", "ABcD", "ABcd", "AbCD", "Abcd", "aBCD", "aBCd", "aBcD"}, true, "b");
    quain.method( PDNF, std::vector<std::string>{ "ABCD", "ABCd", "ABcd", "AbCD", "AbCd", "AbcD", "Abcd", "aBCD", "aBCd", "aBcD"}, true, "c");
    quain.method( PDNF, std::vector<std::string>{ "ABCD", "ABcD", "ABcd", "AbCd", "AbcD", "aBCD", "aBCd"}, true, "d");
    quain.method( PDNF, std::vector<std::string>{ "ABCD", "ABcD", "AbcD", "aBCD", "aBcD"}, true, "e");
    quain.method( PDNF, std::vector<std::string>{ "ABCD", "AbCD", "AbCd", "AbcD", "aBCD", "aBCd", "aBcD"}, true, "f");
    quain.method( PDNF, std::vector<std::string>{ "ABcD", "ABcd", "AbCD", "AbCd", "AbcD", "aBCD", "aBCd"}, true, "g");
    std::cout << std::setfill('=') << std::setw(120) << " " << std::endl;
    std::cout << std::setfill('=') << std::setw(120) << " " << std::endl;
    std::cout << std::setfill('=') << std::setw(120) << " " << std::endl;
    std::cout << std::setfill(' ');
    quain.method( PCNF, std::vector<std::string>{ "abcD", "aBcd"});
    quain.method( PCNF, std::vector<std::string>{ "aBcD", "aBCd"});
    quain.method( PCNF, std::vector<std::string>{ "abCd"});
    quain.method( PCNF, std::vector<std::string>{ "abcD", "aBcd", "aBCD", "AbCd"});
    quain.method( PCNF, std::vector<std::string>{ "abcD", "abCD", "aBcd", "aBcD", "aBCD" , "AbcD"});
    quain.method( PCNF, std::vector<std::string>{ "abcD", "abCd", "abCD", "aBCD"});
    quain.method( PCNF, std::vector<std::string>{ "abcd", "abcD", "aBCD", "AbCd"});
    std::cout << std::setfill('=') << std::setw(120) << " "  << std::endl;
    std::cout << "Готовая таблица для tex" << std::endl;
    std::cout << std::setfill('=') << std::setw(120) << " " << std::endl;
    std::cout << std::setfill(' ');
    quain.method( PCNF, std::vector<std::string>{ "abcD", "aBcd"}, true, "a");
    quain.method( PCNF, std::vector<std::string>{ "aBcD", "aBCd"}, true, "b");
    quain.method( PCNF, std::vector<std::string>{ "abCd"}, true, "c");
    quain.method( PCNF, std::vector<std::string>{ "abcD", "aBcd", "aBCD", "AbCd"}, true, "d");
    quain.method( PCNF, std::vector<std::string>{ "abcD", "abCD", "aBcd", "aBcD", "aBCD" , "AbcD"}, true, "e");
    quain.method( PCNF, std::vector<std::string>{ "abcD", "abCd", "abCD", "aBCD"}, true, "f");
    quain.method( PCNF, std::vector<std::string>{ "abcd", "abcD", "aBCD", "AbCd"}, true, "g");
}


