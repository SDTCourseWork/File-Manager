#pragma once /* Защита от двойного подключения заголовочного файла */
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>


vector<string> Split (string str, char delimetr);
int std_string_compare (std::string str1, std::string str2);
// void replace(std::string& str, const std::string& from, const std::string& to);