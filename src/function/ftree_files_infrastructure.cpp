#pragma once /* Защита от двойного подключения заголовочного файла */
#include <iostream> //содержимым файла «iostream.h», который находится в стандартной библиотеке языка и отвечает за ввод и вывод данных на экран.
#include <cstdlib> //подключает стандартную библиотеку языка С. Это подключение необходимо для работы функции system.
#include <string>
#include <vector>
#include <typeinfo>
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
void TreeFiles_add (VirtualFolder* VF_dad_folder, std::string address)
{
	replace(address, "\\", "/");



	std::string s_file_name = TreeFiles_add__separation_file(address);
	vector <string> v_folders_of_address = TreeFiles_add__separation_folder(address);



	int isset_folder_in_TF = 0;
	VirtualFolder* VF_save_dota_folder;
	int iteration = 0;
	for (auto s_folder_of_address : v_folders_of_address)
	{
		VirtualFolder* VF_save_dota_folder = TreeFiles_add__find_dota_folder(VF_dad_folder, s_folder_of_address);
		// cout << (VF_save_dota_folder == NULL) << endl; //L
		if (VF_save_dota_folder == NULL)
		{
			VirtualFolder* VF_new_folder = TreeFiles_add__create_new_local_VF(VF_dad_folder, s_folder_of_address); //Создаем новую папку, записывая в нее свойства
			VF_dad_folder->v_child_folders.emplace_back(VF_new_folder); //Добавляем ее в вектор дочерних папок

			VF_save_dota_folder = TreeFiles_add__end_vector_of_VF(VF_dad_folder); //Указываем на последний добавленный элемент
		}

		// cout << "iteration : " << iteration << endl; //L
		// TESTING_PRINT_ALL_DOTA_FOLDER(VF_dad_folder, 5);
		VF_dad_folder = VF_save_dota_folder;
	}
}
VirtualFolder* TreeFiles_add__end_vector_of_VF (VirtualFolder* VF_dad_folder)
{
	vector < VirtualFolder* >::iterator VFITER_save_dota_folder = VF_dad_folder->v_child_folders.end();
	VFITER_save_dota_folder--;
	return *VFITER_save_dota_folder;
}
VirtualFolder* TreeFiles_add__create_new_local_VF (VirtualFolder* VF_dad_folder, std::string s_folder_of_address)
{
	VirtualFolder* VF_new_folder = new VirtualFolder; //Создаем дочернюю папку и ЗАДАЕМ ЕЁ СВОЙСВА
	VF_new_folder->properties_string["Name"] = s_folder_of_address;
	VF_new_folder->parent = VF_dad_folder;

	return VF_new_folder;
}
VirtualFolder* TreeFiles_add__find_dota_folder (VirtualFolder* VF_dad_folder, std::string s_address_folder)
{
	VirtualFolder* VF_save_dota_folder = NULL;
	int isset_folder_in_TF = 0;
	int ttest = 0;
	for (auto VF_dota_folder : VF_dad_folder->v_child_folders)
	{
		ttest = s_address_folder.compare(VF_dota_folder->properties_string["Name"]) != std::string::npos;
		// cout << "in_compare: " << s_address_folder << "   <====>     " << VF_dota_folder->properties_string["Name"] << " result " << ttest << endl; //L
		if (ttest == 0)
		{ //Погружаемся, если нашлась дочерняя папка с подходящим названием
			// cout << "popal cuda" << endl; //L
			isset_folder_in_TF = 1;
			VF_save_dota_folder = VF_dota_folder;
			break;
		}
	}
	// cout << "ravno_null " << (VF_save_dota_folder == NULL) << endl; //L

	return VF_save_dota_folder;
}
std::string TreeFiles_add__separation_file (std::string address)
{
	std::string s_file_name = "";
	vector <string> v_folders_of_address;

	if (address[address.size() - 1] != '/') //если нам передали файл (просто папки оканчиваются на '/')
	{
		v_folders_of_address = Split(address, '/');
		vector <string>::iterator temp_itertat = v_folders_of_address.end(); //Извлекаем имя файла полного пути
		s_file_name = *(temp_itertat - 1);
		v_folders_of_address.erase(temp_itertat - 1); //удаляем последний элемент
	}

	return s_file_name;
}
vector <string> TreeFiles_add__separation_folder (std::string address)
{
	vector <string> v_folders_of_address;
	v_folders_of_address = Split(address, '/');

	if (address[address.size() - 1] != '/') //если нам передали файл (просто папки оканчиваются на '/')
	{
		vector <string>::iterator temp_itertat = v_folders_of_address.end(); //Извлекаем имя файла полного пути
		v_folders_of_address.erase(temp_itertat - 1); //удаляем последний элемент
	}

	return v_folders_of_address;
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
void TreeFiles_visuale (VirtualFolder* VF_current_folder/*, std::string address*/)
{
	set<string> mandatory_properties; //Свойства которые не выводятся в описании файла
	mandatory_properties.insert("Name");


	VF_current_folder = TreeFiles_visuale__diving(VF_current_folder); //Первое погружение для того, чтобы не печатать пустой элемент


	int level = 0;
	string tabulation;
	while (true)
	{
		tabulation = "";

		for (int i = 0; i < level; ++i)
			tabulation += "	";


		cout << " test_on_NULL  " << (VF_current_folder == NULL) << endl;

		if (VF_current_folder != NULL)
		{
			TreeFiles_visuale__print_folder(VF_current_folder, mandatory_properties, tabulation); //Печатаем свойства папки и вложенные файлы
			TreeFiles_visuale__print_files(VF_current_folder, mandatory_properties, tabulation);
			VF_current_folder->parent->position["visualization"]++;
		}


		if (TreeFiles_visuale__isset_dota_folder(VF_current_folder, level)) //Если есть дочерняя папка для печати
		{
			VF_current_folder = TreeFiles_visuale__diving(VF_current_folder); //погружаемся
			cout << "bil on diving " << (VF_current_folder == NULL) << endl;
			level++;
		}
		else if (TreeFiles_visuale__isset_equal_folder(VF_current_folder, level)) //Иначе Если есть папка на этом уровне для печати
		{
			VF_current_folder = TreeFiles_visuale__next_equal_folder(VF_current_folder, level); //Получаем указатель на следующую папку
		}
		else if (/*TreeFiles_visuale__isset_parent_folder(VF_current_folder, level)*/ true)	//Иначе если есть куда всплывать
		{
			int visualization_ending = 0;
			while (true)
			{
				VF_current_folder = TreeFiles_visuale__surfacing(VF_current_folder, level); //всплываем
				level--;


				VF_current_folder = TreeFiles_visuale__next_equal_folder(VF_current_folder, level); //Получаем указатель на следующую папку
				if (VF_current_folder != NULL) //Если нашли необработанную папку
				{
					break;
				}
				if (level <= 1) //если больше всплыват некуда, то прекращаем визуализацию
				{
					visualization_ending = 1;
					break;
				}
			}
			if (visualization_ending)
				break;
		}
		else
		{
			break; //Визуализация окончена
		}
	}
}
void TESTING_PRINT_ALL_DOTA_FOLDER (VirtualFolder* VF_current_folder, int level)
{
	VirtualFolder* VF_save_dota_folder = NULL;
	int i = 0;
	cout << "count: " << VF_current_folder->v_child_folders.size() << endl;
	for (auto VF_find_dota_folder : VF_current_folder->v_child_folders) //Перебираем дочерние папки
	{
		string fod = VF_find_dota_folder->properties_string["Name"];
		cout << VF_current_folder->properties_string["Name"] << " >>>> " << i << "   :   " << fod << endl;
		i++;
	}
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
}
int TreeFiles_visuale__isset_dota_folder (VirtualFolder* VF_current_folder, int level)
{

	if (TreeFiles_visuale__diving(VF_current_folder) == NULL)
		return 0;
	else
		return 1;
}
VirtualFolder* TreeFiles_visuale__diving (VirtualFolder* VF_current_folder)
{//****он возможно не может возвращать дальше 1-ого элемента
	VirtualFolder* VF_save_dota_folder = NULL;
	int i = 0;
	for (auto VF_find_dota_folder : VF_current_folder->v_child_folders) //Перебираем дочерние папки
	{
		// cout << VF_find_dota_folder->properties_string["Name"] << " i " << i << " position " << VF_current_folder->position["visualization"] << endl;
		if (i == VF_current_folder->position["visualization"]) //Если дошли до необработанной дочерней папки
		{
			VF_save_dota_folder = VF_find_dota_folder;
			break; //Поиск окончен
		}
		i++;
	}



	return VF_save_dota_folder;
}
int TreeFiles_visuale__isset_equal_folder (VirtualFolder* VF_current_folder, int level)
{
	if (level == 0) //Нету равных папок для 0-ого уровня
		return 0;


	return TreeFiles_visuale__isset_dota_folder(VF_current_folder->parent, level);
}
VirtualFolder* TreeFiles_visuale__next_equal_folder (VirtualFolder* VF_current_folder, int level)
{
	VirtualFolder* test = TreeFiles_visuale__diving(VF_current_folder->parent);



	return test;
}
void TreeFiles_visuale__print_folder (VirtualFolder* VF_current_folder, set<string> mandatory_properties, string tabulation)
{ //Печатаем текущую папку и ее свойства
		cout << tabulation << "'-- " << VF_current_folder->properties_string["Name"];
		TreeFiles_visuale__print_property_folder__string(VF_current_folder, tabulation, mandatory_properties);
		TreeFiles_visuale__print_property_folder__int(VF_current_folder, tabulation, mandatory_properties);
		cout << endl;
}
void TreeFiles_visuale__print_files (VirtualFolder* VF_current_folder, set<string> mandatory_properties, string tabulation)
{ //Печатаем файлы и их свойства
	vector < map<string, string> >::iterator it_str;
	vector < map<string, int> >::iterator it_int;
	it_int = VF_current_folder->files_int.begin();
	it_str = VF_current_folder->files_string.begin();


	while (true)
	{
		if (!((it_int != VF_current_folder->files_int.end()) 
			|| (it_str != VF_current_folder->files_string.end()))) //если хотя бы один из циклов может работать - работаем
			break; //если ни один из полуциклов не работает, то ломаем цикл

		cout << tabulation << "	|-- " << (*it_str)["Name"] << "	";

		if (it_str != VF_current_folder->files_string.end()) //Печатаем все текстовые свойства, если полуцикл работает
			TreeFiles_visuale__print_property_files__string(VF_current_folder, tabulation, mandatory_properties, it_str);
		if (it_int != VF_current_folder->files_int.end()) //Печатаем все целочисленные свойства, если полуцикл работает
			TreeFiles_visuale__print_property_files__int(VF_current_folder, tabulation, mandatory_properties, it_int);

		cout << endl;

		it_int++;
		it_str++;
	}
}
int TreeFiles_visuale__isset_parent_folder (VirtualFolder* VF_current_folder, int level)
{
	if (level <= 1)
		return 0; //первому уровню незачем всплывать

	VirtualFolder* VF_testing = TreeFiles_visuale__surfacing(VF_current_folder, level);

	return !(VF_testing == NULL);
}
VirtualFolder* TreeFiles_visuale__surfacing (VirtualFolder* VF_current_folder, int level)
{
	if (level <= 1)
		return NULL; //первому уровню незачем всплывать


	return VF_current_folder->parent;

}



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