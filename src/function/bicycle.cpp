#pragma once /* Защита от двойного подключения заголовочного файла */
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <vector>
#include <string>
#include <map>

#include "bicycle.h"

// #Разделяет строку по символу-разделителю в вектор
vector<string> Explode (string str, char delimetr)
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
// Соединяет вектор в строку, добавляя между ними строку-разделитель
/*std::string Implode_invert (std::vector<string> v_strings, std::string delimetr)
{
	std::vector<string>::iterator string_of_vector;
	std::string sum_string = "";
	for (string_of_vector = v_strings.begin(); string_of_vector != v_strings.end(); ++string_of_vector)
	{
		sum_string = string_of_vector + delimetr + sum_string;
	}

	return sum_string;
}*/
std::string Implode (vector<string> v_strings, std::string delimetr)
{
	int i = 0;
	vector<string>::iterator string_of_vector;
	std::string sum_string = "";
	for (string_of_vector = v_strings.begin(); string_of_vector != v_strings.end(); ++string_of_vector)
	{
		if (i > 0)
			sum_string = sum_string + delimetr + *string_of_vector;
		else
			sum_string = sum_string + *string_of_vector;
		i++;
	}

	return sum_string;
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




int std_string_compare (std::string str1, std::string str2)
{
	if (str1.size() > str2.size())
	{
		return 1;
	}
	else if (str1.size() < str2.size())
	{
		return -1;
	}
	else if (str1.size() == str2.size())
	{
		int str_length = str1.size();
		int inequality = 0;
		int a_B_b = 0;
		int b_B_a = 0;
		for (int i = 0; i < str_length; ++i)
		{
			a_B_b = str1[i] > str2[i];
			b_B_a = str1[i] < str2[i];

			if (!((a_B_b == 0) && (b_B_a == 0)))
			{
				inequality = 1;
				break;
			}
		}
		if (inequality)
		{
			if (a_B_b)
				return 1;
			else
				return -1;
		}
		else
			return 0;
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