#include "Quain.h"


void get_quain_method() {
    Quain quain;
    quain.method( PCNF, std::vector<std::string>{ "Abcd", "ABcd", "abCd", "AbCd", "ABCd", "AbcD"});
#if 0
    quain.method( PDNF, std::vector<std::string>{ "ABCD", "ABcD", "ABcd", "AbCd", "AbcD", "Abcd", "aBCD", "aBCd", "aBcD"});
    quain.method( PDNF, std::vector<std::string>{ "ABCD", "ABCd", "ABcD", "ABcd", "AbCD", "Abcd", "aBCD", "aBCd", "aBcD"});
    quain.method( PDNF, std::vector<std::string>{ "ABCD", "ABCd", "ABcd", "AbCD", "AbCd", "AbcD", "Abcd", "aBCD", "aBCd", "aBcD"});
    quain.method( PDNF, std::vector<std::string>{ "ABCD", "ABcD", "ABcd", "AbCd", "AbcD", "aBCD", "aBCd"});
    quain.method( PDNF, std::vector<std::string>{ "ABCD", "ABcD", "AbcD", "aBCD", "aBcD"});
    quain.method( PDNF, std::vector<std::string>{ "ABCD", "AbCD", "AbCd", "AbcD", "aBCD", "aBCd", "aBcD"});
    quain.method( PDNF, std::vector<std::string>{ "ABcD", "ABcd", "AbCD", "AbCd", "AbcD", "aBCD", "aBCd"});
//
    quain.method(std::vector<std::string>{ "ABCD", "ABcD", "ABcd", "AbCd", "AbcD", "Abcd", "aBCD", "aBCd", "aBcD"}, true, "a");
    quain.method(std::vector<std::string>{ "ABCD", "ABCd", "ABcD", "ABcd", "AbCD", "Abcd", "aBCD", "aBCd", "aBcD"}, true, "b");
    quain.method(std::vector<std::string>{ "ABCD", "ABCd", "ABcd", "AbCD", "AbCd", "AbcD", "Abcd", "aBCD", "aBCd", "aBcD"}, true, "c");
    quain.method(std::vector<std::string>{ "ABCD", "ABcD", "ABcd", "AbCd", "AbcD", "aBCD", "aBCd"}, true, "d");
    quain.method(std::vector<std::string>{ "ABCD", "ABcD", "AbcD", "aBCD", "aBcD"}, true, "e");
    quain.method(std::vector<std::string>{ "ABCD", "AbCD", "AbCd", "AbcD", "aBCD", "aBCd", "aBcD"}, true, "f");
    quain.method(std::vector<std::string>{ "ABcD", "ABcd", "AbCD", "AbCd", "AbcD", "aBCD", "aBCd"}, true, "g");
#endif
}

int main() {
    get_quain_method();
    return  0;
}
