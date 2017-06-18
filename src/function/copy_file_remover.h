#ifndef COPY_FILE_REMOVER_H_INCLUDED
#define COPY_FILE_REMOVER_H_INCLUDED

#pragma once /* Защита от двойного подключения заголовочного файла */
#include <iostream> //содержимым файла «iostream.h», который находится в стандартной библиотеке языка и отвечает за ввод и вывод данных на экран.
#include <cstdlib> //подключает стандартную библиотеку языка С. Это подключение необходимо для работы функции system.
#include <string>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <map>
// #include <algorithm>
#include <set>
#include <cstring>
#include <time.h>
using namespace std; //указывает на то, что мы используем по умолчанию пространство имен с названием «std»

string GetMD5HashFromFile(string fileName);
#endif