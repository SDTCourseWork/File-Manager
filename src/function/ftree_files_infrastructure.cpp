#pragma once /* Защита от двойного подключения заголовочного файла */
#include <iostream> //содержимым файла «iostream.h», который находится в стандартной библиотеке языка и отвечает за ввод и вывод данных на экран.
#include <cstdlib> //подключает стандартную библиотеку языка С. Это подключение необходимо для работы функции system.
#include <string>
#include <vector>
#include <set>
#include <cstring>
using namespace std; //указывает на то, что мы используем по умолчанию пространство имен с названием «std»

#include "bicycle.cpp"
#include "ftree_files_infrastructure.h"


//##ДОБАВИТЬ
//##ОПИСАТЬ ОБЪЕКТ
//##ПОЛУЧИТЬ ОПИСАНИЕ ОБЪЕКТА
//##УДАЛИТЬ
//##КОПИРОВАТЬ

// #СОЗДАТЬ (ДФ)
// >	(ДФ) пустое
VirtualFolder* TreeFiles_create ()
{
	VirtualFolder* temp = new VirtualFolder;

	return temp;
}

// #ПОИСК НАЛИЧИЯ КАТАЛОГА
// <	местоназначение каталога
// >	(ДФ ред)
VirtualFolder* TreeFiles_find_folder (VirtualFolder* folder, std::string address)
{
	address.replace(address.begin(), address.end(), '\\', '/');


	vector <string> v_folders_of_address;
	v_folders_of_address = Split(address, '/');


	// vector <string>::iterator temp_itertat = v_folders_of_address.end(); //Извлекаем имя файла полного пути
	// string s_file_name = *(temp_itertat - 1);
	// v_folders_of_address.erase(temp_itertat - 1); //удаляем последний элемент


	int isset_folder_in_TF = 0;
	VirtualFolder* VF_save_dota_folder;
	for (auto s_address_folder : v_folders_of_address)
	{
		isset_folder_in_TF = 0;
		for (auto VF_dota_folder : folder->v_child_folders)
		{
			if (s_address_folder.find(VF_dota_folder->properties_string["Name"]) != std::string::npos)
			{ //Погружаемся, если нашлась дочерняя папка с подходящим названием
				isset_folder_in_TF = 1;
				VF_save_dota_folder = VF_dota_folder;
				break;
			}
		}

		if (isset_folder_in_TF)
			folder = VF_save_dota_folder;
		else
			break; //ломаем поиск адреса, если хотя-бы одно звено отсутствует
	}
	if (isset_folder_in_TF)
		return VF_save_dota_folder;
	else
		return NULL;
}

// #КАРТА СВОЙСТВ ФАЙЛА
// <	местоназначение каталога
// >	(ДФ ред)
// map<string, value> map; TreeFiles_find_folder (VirtualFolder* folder, std::string address)


// #ДОБАВИТЬ КАТАЛОГ
// <	местоназначение каталога
// >	(ДФ ред)
void TreeFiles_add_folder (VirtualFolder* VF_dad_folder, std::string address)
{
	replace(address, "\\", "/");


	vector <string> v_folders_of_address;
	v_folders_of_address = Split(address, '/');

	// vector <string>::iterator temp_itertat = v_folders_of_address.end(); //Извлекаем имя файла полного пути
	// string s_file_name = *(temp_itertat - 1);
	// v_folders_of_address.erase(temp_itertat - 1); //удаляем последний элемент


	int isset_folder_in_TF = 0;
	VirtualFolder* VF_save_dota_folder;
	for (auto s_address_folder : v_folders_of_address)
	{
		isset_folder_in_TF = 0;
		for (auto VF_dota_folder : VF_dad_folder->v_child_folders)
		{
			if (s_address_folder.find(VF_dota_folder->properties_string["Name"]) != std::string::npos)
			{ //Погружаемся, если нашлась дочерняя папка с подходящим названием
				isset_folder_in_TF = 1;
				VF_save_dota_folder = VF_dota_folder;
				break;
			}
		}

		if (!isset_folder_in_TF)
		{
			VirtualFolder* VF_new_folder = new VirtualFolder; //Создаем дочернюю папку и ЗАДАЕМ ЕЁ СВОЙСВА
			VF_new_folder->properties_string["Name"] = s_address_folder;
			VF_new_folder->parent = VF_dad_folder;

			VF_dad_folder->v_child_folders.emplace_back(VF_new_folder); //Добавляем ее в вектор дочерних папок


			vector < VirtualFolder* >::iterator VFITER_save_dota_folder = VF_dad_folder->v_child_folders.end(); //Указываем на последний добавленный элемент
			VFITER_save_dota_folder--;
			// cout << (*VFITER_save_dota_folder)->properties_string["Name"] << endl;
			 VF_save_dota_folder = *VFITER_save_dota_folder;
		}
		VF_dad_folder = VF_save_dota_folder;
	}
}

// #ДОБАВИТЬ СВОЙСТВО КАТАЛОГУ
// <	(ДФ)
// <	адрес папки

// #УДАЛИТЬ КАТАЛОГ (с дочерними каталогами)
// <	местонахождение каталога
// >	(ДФ ред)
// ::	удаляемы каталог не найден

// #ПЕРЕМЕСТИТЬ КАТАЛОГ
// <	местонахождение каталога
// <	местоназначение каталога
// >	(ДФ ред)
// ::	входящий каталог не найден
// 	исходящий каталог не найден

// #ПРОГУЛКА ПО СТРУКТУРЕ (это проход по всем файлам, не важно как они вложены в папки)
// <	(ДФ ред)
// >	(каждый раз выдается файл на обработку)
// ::	конец каталога

// #ВИЗУАЛИЗАЦИЯ КАТАЛОГА
// <	(ДФ)
// <	адрес каталога
// >	в консоли выводится дерево файлов
// ::	
void TreeFiles_visuale (VirtualFolder* folder/*, std::string address*/)
{
	set<string> mandatory_properties; //Свойства которые не выводятся в описании файла
	mandatory_properties.insert("Name");




	folder = folder->v_child_folders




	int position = 0;
	int level = 0;
	std::string tabulation;
	while (true)
	{
		tabulation = "";

		for (int i = 0; i < level; ++i)
			tabulation += "	";

		//Печатаем текущую папку и ее свойства
		cout << tabulation << "'-- " << folder->properties_string["Name"];
		TreeFiles_visuale__print_property_folder__string(folder, tabulation, mandatory_properties);
		TreeFiles_visuale__print_property_folder__int(folder, tabulation, mandatory_properties);
		cout << endl;


		folder->parent->position["visualization"]++;


		
		//Печатаем файлы и их свойства
/*		vector < map<string, string> >::iterator it_str;
		vector < map<string, int> >::iterator it_int;
		it_int = folder->files_int.begin();
		it_str = folder->files_string.begin();
		while (true)
		{
			if (!((it_int != folder->files_int.end()) 
				|| (it_str != folder->files_string.end()))) //если хотя бы один из циклов может работать - работаем
				break; //если ни один из полуциклов не работает, то ломаем цикл

			cout << tabulation << "	|-- " << (*it_str)["Name"] << "	";

			if (it_str != folder->files_string.end()) //Печатаем все текстовые свойства, если полуцикл работает
				TreeFiles_visuale__print_property_files__string(folder, tabulation, mandatory_properties, it_str);
			if (it_int != folder->files_int.end()) //Печатаем все целочисленные свойства, если полуцикл работает
				TreeFiles_visuale__print_property_files__int(folder, tabulation, mandatory_properties, it_int);

			cout << endl;

			it_int++;
			it_str++;
		}*/






		int i = 0;
		int isset_dota_folder_in_TF = 0;
		for (auto VF_find_dota_folder : folder->v_child_folders) //если есть дочерняя папка, то погружаемся
		{
			// cout << "dota: " << VF_find_dota_folder->properties_string["Name"] << " "
			// 	<< "i: " << i << endl;

			position = folder->parent->position["visualization"];

			if (i == position) //Если дошли до необработанной папки
			{
				folder = VF_find_dota_folder;
				isset_dota_folder_in_TF = 1;
				level++;
				break; //Визуализация окончена
			}
			i++;
		}
		if (!isset_dota_folder_in_TF) //Если не нашлась дочерняя папка - всплываем
		{
			level--;
			if (level < 0)
				break;
			folder = folder->parent;
		}
	}
	//если мы обработали последнюю папку родительского каталога, то всплываем (но не выше переданного каталога)
}
// void TreeFiles_visuale (VirtualFolder* folder/*, std::string address*/)
void TreeFiles_visuale__print_property_folder__string (VirtualFolder* folder, std::string tabulation, set<string> mandatory_properties)
{
	map<string, string>::const_iterator itr_string;
	vector < map<string, string> >::iterator it_str;
	for (itr_string = (folder->properties_string).begin(); itr_string != (folder->properties_string).end(); ++itr_string)
	{
		if (mandatory_properties.find((*itr_string).first) == mandatory_properties.end()) //Печатаем свойство, если его нет в исключениях
			cout << " [" << (*itr_string).first << ": " << (*itr_string).second << "]";
	}
}
void TreeFiles_visuale__print_property_folder__int (VirtualFolder* folder, std::string tabulation, set<string> mandatory_properties)
{
	map<string, int>::const_iterator itr_int;
	vector < map<string, int> >::iterator it_int;
	for (itr_int = (folder->properties_int).begin(); itr_int != (folder->properties_int).end(); ++itr_int)
	{
		if (mandatory_properties.find((*itr_int).first) == mandatory_properties.end()) //Печатаем свойство, если его нет в исключениях
			cout << " [" << (*itr_int).first << ": " << (*itr_int).second << "]";
	}
}
void TreeFiles_visuale__print_property_files__string (VirtualFolder* folder, std::string tabulation, set<string> mandatory_properties, vector < map<string, string> >::iterator it_str)
{
	map<string, string>::const_iterator itr_string;

	for (itr_string = (*it_str).begin(); itr_string != (*it_str).end(); ++itr_string)
	{
		if (mandatory_properties.find((*itr_string).first) == mandatory_properties.end()) //Печатаем свойство, если его нет в исключениях
			cout << " [" << (*itr_string).first << ": " << (*itr_string).second << "]";
	}
}
void TreeFiles_visuale__print_property_files__int (VirtualFolder* folder, std::string tabulation, set<string> mandatory_properties, vector < map<string, int> >::iterator it_int)
{
	map<string, int>::const_iterator itr_int;

	for (itr_int = (*it_int).begin(); itr_int != (*it_int).end(); ++itr_int)
	{
		if (mandatory_properties.find((*itr_int).first) == mandatory_properties.end()) //Печатаем свойство, если его нет в исключениях
			cout << " [" << (*itr_int).first << ": " << (*itr_int).second << "]";
	}
}