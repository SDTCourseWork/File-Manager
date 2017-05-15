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
		// VirtualFolder* parent;
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
		map <string, int> position_file; // *динамический массив с указателями на описание положения для каждой метки

		map <string, int> properties_int; // *указатель на массив с числовыми свойствами свойствами папки
		map <string, string> properties_string; // *указатель на массив с строковыми свойствами свойствами папки
		int level;


		vector < VirtualFolder__file* > files;
		map < string, VirtualFolder__global_position > GLobal_position;


		
};

VirtualFolder* TreeFiles_create ();
VirtualFolder__file* TreeFiles_find_file (VirtualFolder* VF_dad_folder, std::string address);
VirtualFolder* TreeFiles_find_folder (VirtualFolder* VF_dad_folder, std::string address);



void TreeFiles_add (VirtualFolder* folder, std::string address);
	VirtualFolder__file* TreeFiles_add__find_dota_file (std::string s_file_name, VirtualFolder* VF_folder);
	void TreeFiles_add__file_add(std::string s_file_name, VirtualFolder* VF_folder);
	VirtualFolder* TreeFiles_add__end_vector_of_VF (VirtualFolder* VF_dad_folder);
	VirtualFolder* TreeFiles_add__create_new_local_VF (VirtualFolder* VF_dad_folder, std::string s_folder_of_address, int level);
	VirtualFolder* TreeFiles_add__find_dota_folder (VirtualFolder* VF_dad_folder, std::string s_folder_of_address);
	std::string TreeFiles_add__separation_file (std::string address);
	vector <string> TreeFiles_add__separation_folder (std::string address);



int TreeFiles_isset_folder_property_string (VirtualFolder* TF, std::string title);
int TreeFiles_isset_folder_property_int (VirtualFolder* TF, std::string title);
void TreeFiles_change_folder_property_string (VirtualFolder* TF, std::string title, std::string property);
void TreeFiles_change_folder_property_int (VirtualFolder* TF, std::string title, int property);
std::string TreeFiles_get_folder_property_string (VirtualFolder* TF, std::string title);
int TreeFiles_get_folder_property_int (VirtualFolder* TF, std::string title);



int TreeFiles_isset_file_property_string (VirtualFolder__file* TF, std::string title);
int TreeFiles_isset_file_property_int (VirtualFolder__file* TF, std::string title);
void TreeFiles_change_file_property_string (VirtualFolder__file* TF, std::string title, std::string property);
void TreeFiles_change_file_property_int (VirtualFolder__file* TF, std::string title, int property);
std::string TreeFiles_get_file_property_string (VirtualFolder__file* TF, std::string title);
int TreeFiles_get_file_property_int (VirtualFolder__file* TF, std::string title);



std::string TreeFiles_get_address_of_folder (VirtualFolder* VF_current_folder);


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



VirtualFolder__file* TreeFiles_pass_files (VirtualFolder* VF_current_folder, std::string label);



VirtualFolder* TreeFiles_pass (VirtualFolder* folder, std::string label, std::string address = "");
	int TreeFiles_pass__properties_level (VirtualFolder* TF, std::string label);

	VirtualFolder* TreeFiles_pass__correct_pointer (VirtualFolder* VF_current_folder, int* level, std::string label);

	int TreeFiles_pass__isset_dota_folder (VirtualFolder* VF_current_folder, int level, std::string label);
	VirtualFolder* TreeFiles_pass__diving (VirtualFolder* VF_current_folder, std::string label);
	int TreeFiles_pass__isset_equal_folder (VirtualFolder* VF_current_folder, int level, std::string label);
	VirtualFolder* TreeFiles_pass__next_equal_folder(VirtualFolder* VF_current_folder, int level, std::string label);
	int TreeFiles_pass__isset_parent_folder(VirtualFolder* VF_current_folder, int level, std::string label);
	VirtualFolder* TreeFiles_pass__surfacing(VirtualFolder* VF_current_folder, int* level, std::string label);



void TESTING_PRINT_ALL_DOTA_FOLDER (VirtualFolder* VF_current_folder, int level);

#endif // TEACHER_H_INCLUDED