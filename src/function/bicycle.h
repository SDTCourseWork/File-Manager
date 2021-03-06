#pragma once /* Защита от двойного подключения заголовочного файла */
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>


vector<string> Explode (string str, char delimetr);
std::string Implode (std::vector<string> v_strings, std::string delimetr);
std::string Implode_invert (std::vector<string> v_strings, std::string delimetr);
int std_string_compare (std::string str1, std::string str2);
std::string create_rand_string (int length);