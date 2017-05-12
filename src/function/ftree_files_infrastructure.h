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



void TreeFiles_add (VirtualFolder* folder, std::string address);
	VirtualFolder* TreeFiles_add__end_vector_of_VF (VirtualFolder* VF_dad_folder);
	VirtualFolder* TreeFiles_add__create_new_local_VF (VirtualFolder* VF_dad_folder, std::string s_folder_of_address);
	VirtualFolder* TreeFiles_add__find_dota_folder (VirtualFolder* VF_dad_folder, std::string s_folder_of_address);
	std::string TreeFiles_add__separation_file (std::string address);
	vector <string> TreeFiles_add__separation_folder (std::string address);




void TreeFiles_visuale (VirtualFolder* folder/*, std::string address*/);

	void TESTING_PRINT_ALL_DOTA_FOLDER (VirtualFolder* VF_current_folder, int level);


	int TreeFiles_visuale__isset_dota_folder (VirtualFolder* VF_current_folder, int level);
	VirtualFolder* TreeFiles_visuale__diving (VirtualFolder* VF_current_folder);
	int TreeFiles_visuale__isset_equal_folder (VirtualFolder* VF_current_folder, int level);
	VirtualFolder* TreeFiles_visuale__next_equal_folder(VirtualFolder* VF_current_folder, int level);
	void TreeFiles_visuale__print_folder(VirtualFolder* VF_current_folder, set<string> mandatory_properties, string tabulation);
	void TreeFiles_visuale__print_files(VirtualFolder* VF_current_folder, set<string> mandatory_properties, string tabulation);
		void TreeFiles_visuale__print_property_folder__string (VirtualFolder* folder, std::string tabulation, set<string> mandatory_properties);
		void TreeFiles_visuale__print_property_folder__int (VirtualFolder* folder, std::string tabulation, set<string> mandatory_properties);
		void TreeFiles_visuale__print_property_files__string (VirtualFolder* folder, std::string tabulation, set<string> mandatory_properties, vector < map<string, string> >::iterator it_str);
		void TreeFiles_visuale__print_property_files__int (VirtualFolder* folder, std::string tabulation, set<string> mandatory_properties, vector < map<string, int> >::iterator it_int);
	int TreeFiles_visuale__isset_parent_folder(VirtualFolder* VF_current_folder, int level);
	VirtualFolder* TreeFiles_visuale__surfacing(VirtualFolder* VF_current_folder, int* level);




#endif // TEACHER_H_INCLUDED