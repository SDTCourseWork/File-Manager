#pragma once /* Защита от двойного подключения заголовочного файла */
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <vector>
#include <string>
#include <map>

#include "bicycle.h"

vector<string> Split (string str, char delimetr)
{
	vector<string> list_string;
	istringstream f(str);
	string s;
	while (getline(f, s, delimetr))
	{
		list_string.push_back(s);
	}
	return list_string;
}
void replace(std::string& str, const std::string& from, const std::string& to) {
	while (true)
	{
		size_t start_pos = str.find(from);
		if (start_pos == std::string::npos)
			break;
		str.replace(start_pos, from.length(), to);
	}
}







// template<class CharT, class Traits, class Alloc>
// int basic_string<CharT, Traits, Alloc>::compare(const std::basic_string& str) const noexcept
// {
//     size_type lhs_sz = size();
//     size_type rhs_sz = str.size();
//     int result = traits_type::compare(data(), str.data(), std::min(lhs_sz, rhs_sz));
//     if (result != 0)
//         return result;
//     if (lhs_sz < rhs_sz)
//         return -1;
//     if (lhs_sz > rhs_sz)
//         return 1;
//     return 0;
// }