#pragma once /* Защита от двойного подключения заголовочного файла */
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <time.h>

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
			sum_string = *string_of_vector;
		i++;
	}

	return sum_string;
}
std::string Implode_invert (std::vector<string> v_strings, std::string delimetr)
{
	int i = 0;
	vector<string>::iterator string_of_vector;
	std::string sum_string = "";
	for (string_of_vector = v_strings.begin(); string_of_vector != v_strings.end(); ++string_of_vector)
	{
		if (i > 0)
			sum_string = *string_of_vector + delimetr + sum_string;
		else
			sum_string = *string_of_vector;
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

std::string create_rand_string (int length) {
	string  s = "";
	for(int i = 0; i < length; ++i)
		s += 'a' + rand() % 26;

	return s;
}