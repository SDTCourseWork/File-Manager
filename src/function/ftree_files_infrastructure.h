#ifndef FTREE_FILES_INFRASTRUCTURE_H_INCLUDED
#define FTREE_FILES_INFRASTRUCTURE_H_INCLUDED

#pragma once /* Защита от двойного подключения заголовочного файла */
#include <string>
#include <map>
#include <vector>


class VirtualFolder
{
	public:
		VirtualFolder *parent; // *указатель на родительскую папку
		vector < VirtualFolder* > v_child_folders; // *динамический массив с указателями на дочерние папки
		map <string, int> position; // *динамический массив с указателями на описание положения для каждой метки

		map <string, int> properties_int; // *указатель на массив с числовыми свойствами свойствами папки
		map <string, string> properties_string; // *указатель на массив с строковыми свойствами свойствами папки
		vector < map<string, int> > files_int; // *динамический массив с указателями на массивы с числовыми свойствами вложенных файлов
		vector < map<string, string> > files_string; // *динамический массив с указателями на массивы с строковыми свойствами вложенных файлов
};

VirtualFolder* TreeFiles_create ();
VirtualFolder* TreeFiles_find_folder (VirtualFolder* folder, std::string address);

void TreeFiles_add_folder (VirtualFolder* folder, std::string address);
void TreeFiles_visuale (VirtualFolder* folder/*, std::string address*/);

void TreeFiles_visuale__print_property_folder__string (VirtualFolder* folder, std::string tabulation, set<string> mandatory_properties);
void TreeFiles_visuale__print_property_folder__int (VirtualFolder* folder, std::string tabulation, set<string> mandatory_properties);
void TreeFiles_visuale__print_property_files__string (VirtualFolder* folder, std::string tabulation, set<string> mandatory_properties, vector < map<string, string> >::iterator it_str);
void TreeFiles_visuale__print_property_files__int (VirtualFolder* folder, std::string tabulation, set<string> mandatory_properties, vector < map<string, int> >::iterator it_int);


#endif // TEACHER_H_INCLUDED