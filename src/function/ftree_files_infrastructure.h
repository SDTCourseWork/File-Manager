#ifndef FTREE_FILES_INFRASTRUCTURE_H_INCLUDED
#define FTREE_FILES_INFRASTRUCTURE_H_INCLUDED

#pragma once /* Защита от двойного подключения заголовочного файла */
#include <string>
#include <map>
#include <vector>



class VirtualFolder__file
{
	public:
		map<string, int> properties_int; // *числовыми свойствами вложенных файлов
		map<string, string> properties_string; // *строковыми свойствами вложенных файлов
};
class VirtualFolder
{
	public:
		class VirtualFolder__global_position
		{
			public:
				VirtualFolder* folder;
				int file;
				int level;
		};



		VirtualFolder *parent; // *указатель на родительскую папку
		vector < VirtualFolder* > v_child_folders; // *динамический массив с указателями на дочерние папки
		map <string, int> position; // *динамический массив с указателями на описание положения для каждой метки

		map <string, int> properties_int; // *указатель на массив с числовыми свойствами свойствами папки
		map <string, string> properties_string; // *указатель на массив с строковыми свойствами свойствами папки

		vector < VirtualFolder__file* > files;
		map < string, VirtualFolder__global_position > GLobal_position;


		
};

VirtualFolder* TreeFiles_create ();
VirtualFolder* TreeFiles_find_folder (VirtualFolder* folder, std::string address);



void TreeFiles_add (VirtualFolder* folder, std::string address);
	void TreeFiles_add__file_add(std::string s_file_name, VirtualFolder* VF_folder);
	VirtualFolder* TreeFiles_add__end_vector_of_VF (VirtualFolder* VF_dad_folder);
	VirtualFolder* TreeFiles_add__create_new_local_VF (VirtualFolder* VF_dad_folder, std::string s_folder_of_address);
	VirtualFolder* TreeFiles_add__find_dota_folder (VirtualFolder* VF_dad_folder, std::string s_folder_of_address);
	std::string TreeFiles_add__separation_file (std::string address);
	vector <string> TreeFiles_add__separation_folder (std::string address);



void TreeFiles_delete (VirtualFolder* VF_folder, std::string address);
VirtualFolder* TreeFiles_delete__passage(VirtualFolder* VF_current_folder);
VirtualFolder* TreeFiles_delete__correct_pointer (VirtualFolder* VF_current_folder, int *level);
void TreeFiles_delete__delete_node (VirtualFolder* VF_node);





void TreeFiles_visuale (VirtualFolder* TF);
	void TreeFiles_visuale__print_folder(VirtualFolder* VF_current_folder, set<string> mandatory_properties, string tabulation);
	void TreeFiles_visuale__print_files(VirtualFolder* VF_current_folder, set<string> mandatory_properties, string tabulation);
		void TreeFiles_visuale__print_property_folder__string (VirtualFolder* folder, std::string tabulation, set<string> mandatory_properties);
		void TreeFiles_visuale__print_property_folder__int (VirtualFolder* folder, std::string tabulation, set<string> mandatory_properties);
		void TreeFiles_visuale__print_property_files__string (VirtualFolder* folder, std::string tabulation, set<string> mandatory_properties, VirtualFolder__file* VFF_file);
		void TreeFiles_visuale__print_property_files__int (VirtualFolder* folder, std::string tabulation, set<string> mandatory_properties, VirtualFolder__file* VFF_file);

VirtualFolder* TreeFiles_pass (VirtualFolder* folder/*, std::string address*/);
	int TreeFiles_pass__properties_level (VirtualFolder* TF);

	VirtualFolder* TreeFiles_pass__CORRECT_POINTER (VirtualFolder* VF_current_folder, int* level);

	int TreeFiles_pass__isset_dota_folder (VirtualFolder* VF_current_folder, int level);
	VirtualFolder* TreeFiles_pass__diving (VirtualFolder* VF_current_folder);
	int TreeFiles_pass__isset_equal_folder (VirtualFolder* VF_current_folder, int level);
	VirtualFolder* TreeFiles_pass__next_equal_folder(VirtualFolder* VF_current_folder, int level);
	int TreeFiles_pass__isset_parent_folder(VirtualFolder* VF_current_folder, int level);
	VirtualFolder* TreeFiles_pass__surfacing(VirtualFolder* VF_current_folder, int* level);



void TESTING_PRINT_ALL_DOTA_FOLDER (VirtualFolder* VF_current_folder, int level);

#endif // TEACHER_H_INCLUDED