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




// #СОЗДАТЬ (ДФ)
// >	(ДФ) пустое
VirtualFolder* TreeFiles_create ()
{
	VirtualFolder* folder = new VirtualFolder;
	folder->properties_string["Name"] = "TF";
	folder->parent = NULL;
	folder->level = -1;
	return folder;
}












VirtualFolder__file* TreeFiles_find_file (VirtualFolder* VF_dad_folder, std::string address)
{
	replace(address, "\\", "/");


	std::string s_file_name = TreeFiles_add__separation_file(address);
	vector <string> v_folders_of_address = TreeFiles_add__separation_folder(address);
	std::string s_address_of_current_folder = Implode (v_folders_of_address, "/") + "/";
	VirtualFolder* VF_current_folder = TreeFiles_find_folder(VF_dad_folder, s_address_of_current_folder);

	return  TreeFiles_add__find_dota_file(s_file_name, VF_current_folder);
}












// #ПОИСК НАЛИЧИЯ КАТАЛОГА
// <	местоназначение каталога
// >	(ДФ ред)
VirtualFolder* TreeFiles_find_folder (VirtualFolder* VF_dad_folder, std::string address) //? вернуть объект файл
{
	replace(address, "\\", "/");


	std::string s_file_name = TreeFiles_add__separation_file(address);
	vector <string> v_folders_of_address = TreeFiles_add__separation_folder(address);



	VirtualFolder* VF_save_dota_folder;
	int result_find = 0;
	for (auto s_folder_of_address : v_folders_of_address)
	{
		VF_save_dota_folder = TreeFiles_add__find_dota_folder(VF_dad_folder, s_folder_of_address);
		if (VF_save_dota_folder == NULL)
		{
			result_find = 0;
			break; //прерываем поиск, ибо промежуточный элемент отсутсвует
		}
		else
		{
			result_find = 1;
			VF_dad_folder = VF_save_dota_folder; //подготавливаем папку для слудущей итерации ли возврата, как результата
		}
	}


	if (!result_find)
	{
		return NULL;
	}
	else if (s_file_name == "")
	{
		return VF_save_dota_folder;
	}
	else
	{ //<!--~
		vector < VirtualFolder__file* >::iterator Iter_files;
		for (Iter_files = VF_save_dota_folder->files.begin(); Iter_files != VF_save_dota_folder->files.end(); Iter_files++)
		{
			cout << (*Iter_files)->properties_string["Name"] << endl;
		}
	}
}












// #ДОБАВИТЬ ОБЪЕКТ
// <	местоназначение каталога
// >	(ДФ ред)
void TreeFiles_add (VirtualFolder* VF_dad_folder, std::string address)
{
	replace(address, "\\", "/");



	std::string s_file_name = TreeFiles_add__separation_file(address);
	vector <string> v_folders_of_address = TreeFiles_add__separation_folder(address);
	int level = 0;


	VirtualFolder* VF_save_dota_folder;
	for (auto s_folder_of_address : v_folders_of_address)
	{
		VirtualFolder* VF_save_dota_folder = TreeFiles_add__find_dota_folder(VF_dad_folder, s_folder_of_address);
		if (VF_save_dota_folder == NULL)
		{
			VirtualFolder* VF_new_folder = TreeFiles_add__create_new_local_VF(VF_dad_folder, s_folder_of_address, level); //Создаем новую папку, записывая в нее свойства
			VF_dad_folder->v_child_folders.emplace_back(VF_new_folder); //Добавляем ее в вектор дочерних папок

			VF_save_dota_folder = TreeFiles_add__end_vector_of_VF(VF_dad_folder); //Указываем на последний добавленный элемент
		}

		VF_dad_folder = VF_save_dota_folder;
		level++;
	}

	if ((s_file_name != "") && (TreeFiles_add__find_dota_file(s_file_name, VF_dad_folder) == NULL))
		TreeFiles_add__file_add(s_file_name, VF_dad_folder);
}
VirtualFolder__file* TreeFiles_add__find_dota_file (std::string s_file_name, VirtualFolder* VF_folder)
{ //<!--~ поиск не работает
	vector < VirtualFolder__file* >::iterator Iter_files;
	VirtualFolder__file* VFF_dota_file = NULL;
	int isset_dota_file = 0;
	for (Iter_files = VF_folder->files.begin(); Iter_files != VF_folder->files.end(); Iter_files++)
	{
		if (std_string_compare(s_file_name, (*Iter_files)->properties_string["Name"]) == 0)
		{
			isset_dota_file = 1;
			VFF_dota_file = *Iter_files;
			break; //файл найден, Поиск окончен
		}
	}

	return VFF_dota_file;
}
void TreeFiles_add__file_add (std::string s_file_name, VirtualFolder* VF_folder)
{
	VirtualFolder__file* new_file = new VirtualFolder__file;
	new_file->properties_string["Name"] = s_file_name;
	VF_folder->files.push_back(new_file);
}

VirtualFolder* TreeFiles_add__end_vector_of_VF (VirtualFolder* VF_dad_folder)
{
	vector < VirtualFolder* >::iterator VFITER_save_dota_folder = VF_dad_folder->v_child_folders.end();
	VFITER_save_dota_folder--;
	return *VFITER_save_dota_folder;
}
VirtualFolder* TreeFiles_add__create_new_local_VF (VirtualFolder* VF_dad_folder, std::string s_folder_of_address, int level)
{
	VirtualFolder* VF_new_folder = new VirtualFolder; //Создаем дочернюю папку и ЗАДАЕМ ЕЁ СВОЙСВА
	VF_new_folder->properties_string["Name"] = s_folder_of_address;
	VF_new_folder->parent = VF_dad_folder;
	VF_new_folder->level = level;

	return VF_new_folder;
}
VirtualFolder* TreeFiles_add__find_dota_folder (VirtualFolder* VF_dad_folder, std::string s_address_folder)
{
	VirtualFolder* VF_save_dota_folder = NULL;
	int isset_folder_in_TF = 0;
	int ttest = 0;
	for (auto VF_dota_folder : VF_dad_folder->v_child_folders)
	{
		if (std_string_compare(s_address_folder, VF_dota_folder->properties_string["Name"]) == 0)
		{ //Погружаемся, если нашлась дочерняя папка с подходящим названием
			isset_folder_in_TF = 1;
			VF_save_dota_folder = VF_dota_folder;
			break;
		}
	}
	return VF_save_dota_folder;
}
std::string TreeFiles_add__separation_file (std::string address)
{
	std::string s_file_name = "";
	vector <string> v_folders_of_address;

	if (address[address.size() - 1] != '/') //если нам передали файл (просто папки оканчиваются на '/')
	{
		v_folders_of_address = Explode(address, '/');
		vector <string>::iterator temp_itertat = v_folders_of_address.end(); //Извлекаем имя файла полного пути
		s_file_name = *(temp_itertat - 1);
		v_folders_of_address.erase(temp_itertat - 1); //удаляем последний элемент
	}

	return s_file_name;
}
vector <string> TreeFiles_add__separation_folder (std::string address)
{
	vector <string> v_folders_of_address;
	v_folders_of_address = Explode(address, '/');

	if (address[address.size() - 1] != '/') //если нам передали файл (просто папки оканчиваются на '/')
	{
		vector <string>::iterator temp_itertat = v_folders_of_address.end(); //Извлекаем имя файла полного пути
		v_folders_of_address.erase(temp_itertat - 1); //удаляем последний элемент
	}

	return v_folders_of_address;
}












// #ПРОВЕРИТЬ НАЛИЧИЕ СВОЙСТВА
int TreeFiles_isset_folder_property_string (VirtualFolder* TF, std::string title)
{
	return (TF->properties_string).find(title) != (TF->properties_string).end();
}
int TreeFiles_isset_folder_property_int (VirtualFolder* TF, std::string title)
{
	return (TF->properties_int).find(title) != (TF->properties_int).end();
}
// #ИЗМЕНИТЬ СВОЙСТВО string
void TreeFiles_change_folder_property_string (VirtualFolder* TF, std::string title, std::string property)
{
	if (TF != NULL)
		TF->properties_string[title] = property;
}
// #ИЗМЕНИТЬ СВОЙСТВО int
void TreeFiles_change_folder_property_int (VirtualFolder* TF, std::string title, int property)
{
	if (TF != NULL)
		TF->properties_int[title] = property;
}
// #ПОЛУЧИТЬ СВОЙСТВО string
std::string TreeFiles_get_folder_property_string (VirtualFolder* TF, std::string title)
{
	return TF->properties_string[title];
}
// #ПОЛУЧИТЬ СВОЙСТВО int
int TreeFiles_get_folder_property_int (VirtualFolder* TF, std::string title)
{
	return TF->properties_int[title];
}











// #ПРОВЕРИТЬ НАЛИЧИЕ СВОЙСТВА
int TreeFiles_isset_file_property_string (VirtualFolder__file* TF, std::string title)
{
	return (TF->properties_string).find(title) != (TF->properties_string).end();
}
int TreeFiles_isset_file_property_int (VirtualFolder__file* TF, std::string title)
{
	return (TF->properties_int).find(title) != (TF->properties_int).end();
}
// #ИЗМЕНИТЬ СВОЙСТВО string
void TreeFiles_change_file_property_string (VirtualFolder__file* TF, std::string title, std::string property)
{
	if (TF != NULL)
		TF->properties_string[title] = property;
}
// #ИЗМЕНИТЬ СВОЙСТВО int
void TreeFiles_change_file_property_int (VirtualFolder__file* TF, std::string title, int property)
{
	if (TF != NULL)
		TF->properties_int[title] = property;
}
// #ПОЛУЧИТЬ СВОЙСТВО string
std::string TreeFiles_get_file_property_string (VirtualFolder__file* TF, std::string title)
{
	return TF->properties_string[title];
}
// #ПОЛУЧИТЬ СВОЙСТВО int
int TreeFiles_get_file_property_int (VirtualFolder__file* TF, std::string title)
{
	return TF->properties_int[title];
}












// #ПОЛУЧИТЬ АДРЕСС ОБЪЕКТА
std::string TreeFiles_get_address_of_folder (VirtualFolder* VF_current_folder)
{
	std::string s_address = "";
	while (true)
	{
		if ((VF_current_folder->parent == NULL) || (VF_current_folder == NULL))
			break;

		s_address = VF_current_folder->properties_string["Name"] + "/" + s_address;

		if (VF_current_folder->level <= 0)
			break;

		VF_current_folder = VF_current_folder->parent;
	}

	return s_address;
}












// #УДАЛИТЬ (с дочерними каталогами)
// <	местонахождение каталога
// >	(ДФ ред)
// ::	удаляемый каталог не найден
void TreeFiles_delete (VirtualFolder* TF, std::string address)
{ //<!--~ настоящий код ниже закомментен
/*	while (true)
	{
		VF_folder = TreeFiles_delete__passage(VF_folder);
		if (VF_folder == NULL)
			break;
		else
		{
			TreeFiles_delete__delete_node(VF_parent);
		}
	}*/


	set<string> mandatory_properties; //Свойства которые не выводятся в описании файла
	mandatory_properties.insert("Name");
	VirtualFolder* VF_current_folder;
	while (true)
	{
		VF_current_folder = TreeFiles_delete__passage(TF);
		if (VF_current_folder == NULL)
			break;
		else
		{
			string tabulation = "";
			for (int i = 0; i < TreeFiles_pass__properties_level(TF, "visualization"); ++i)
				tabulation += "	";

			TreeFiles_visuale__print_folder(VF_current_folder, mandatory_properties, tabulation); //Печатаем свойства папки и вложенные файлы
			TreeFiles_visuale__print_files(VF_current_folder, mandatory_properties, tabulation);
		}
	}
}












VirtualFolder* TreeFiles_delete__passage(VirtualFolder* TF)
{
	VirtualFolder* VF_current_folder;
	if (TF->GLobal_position["visualization"].folder == NULL)
	{
		VF_current_folder = TF;
		if (TF != VF_current_folder)
			(TF->GLobal_position["visualization"].folder)->parent->position["visualization"] = -1;
			TF->GLobal_position["visualization"].level = -1;
	}
	else
	{
		VF_current_folder = TF->GLobal_position["visualization"].folder;
		if (TF != VF_current_folder)
			(TF->GLobal_position["visualization"].folder)->parent->position["visualization"]++;
	}
	int* level = &(TF->GLobal_position["visualization"].level);


	VF_current_folder = TreeFiles_delete__correct_pointer(VF_current_folder, &(*level));
	if (VF_current_folder == NULL)
		return NULL; //Визуализация окончена
	else
	{
		TF->GLobal_position["visualization"].folder = VF_current_folder;
		return VF_current_folder;
	}
}
VirtualFolder* TreeFiles_delete__correct_pointer (VirtualFolder* VF_current_folder, int* level)
{
	VirtualFolder* VF_diving = TreeFiles_pass__diving(VF_current_folder, "visualization"); //погружаемся
	if (VF_diving != NULL)
	{
		VF_current_folder = VF_diving;
		(*level)++;
		return VF_current_folder;
	}


	VirtualFolder* VF_next = TreeFiles_pass__next_equal_folder(VF_current_folder, (*level), "visualization"); //Получаем указатель на следующую папку
	if (VF_next != NULL)
	{
		VF_current_folder = VF_next;
		return VF_current_folder;
	}


	VirtualFolder* VF_surfacing = TreeFiles_pass__surfacing(VF_current_folder, &(*level), "visualization"); //всплываем
	if ((VF_surfacing != NULL) && (*level) > 0)
	{
		(*level)--;
		VF_current_folder = TreeFiles_pass__next_equal_folder(VF_surfacing, (*level), "visualization");
		return VF_current_folder;
	}
	else
		return NULL;
}
void TreeFiles_delete__delete_node (VirtualFolder* VF_node)
{

}












// #КОПИРОВАТЬ
// <	местонахождение каталога
// <	местоназначение каталога
// >	(ДФ ред)
// ::	входящий каталог не найден
// 	исходящий каталог не найден











// #ПРОГУЛКА ПО ФАЙЛАМ ПАПКИ
VirtualFolder__file* TreeFiles_pass_files (VirtualFolder* VF_current_folder, std::string label)
{//<~
	VirtualFolder__file* VFF_result_find = NULL;
	vector < VirtualFolder__file* >::iterator Iter_files;
	int i = 0;
	for (Iter_files = VF_current_folder->files.begin(); Iter_files != VF_current_folder->files.end(); Iter_files++)
	{
		if (i == VF_current_folder->position_file[label])
		{
			VFF_result_find = (*Iter_files);
			break;
		}
		i++;
	}

	VF_current_folder->position_file[label]++;
	return VFF_result_find;
}
void TreeFiles_pass_files_on_start (VirtualFolder* VF_current_folder, std::string label)
{
	VF_current_folder->position_file[label] = 0;
}











// #ПРОГУЛКА ПО СТРУКТУРЕ (это проход по всем файлам, не важно как они вложены в папки)
// <	(ДФ ред)
// >	(каждый раз выдается файл на обработку)
// ::	конец каталога
VirtualFolder* TreeFiles_pass (VirtualFolder* TF, std::string label) //<!--~ произойдет ошибка сегментации, если на вход дать не верхушку дерева
{
	VirtualFolder* VF_current_folder;
	if ((TF->GLobal_position[label]).folder == NULL)
	{
		VF_current_folder = TF;
		if (TF != VF_current_folder)
		{
			(TF->GLobal_position[label].folder)->parent->position[label] = -1;
			TF->GLobal_position[label].level = -1;
		}
	}
	else
	{
		VF_current_folder = TF->GLobal_position[label].folder;
		if (TF != VF_current_folder)
			(TF->GLobal_position[label].folder)->parent->position[label]++;
	}
	int* level = &(TF->GLobal_position[label].level);




	VF_current_folder = TreeFiles_pass__correct_pointer(VF_current_folder, &(*level), label);
	if (VF_current_folder == NULL)
		return NULL; //Визуализация окончена
	else
	{
		TF->GLobal_position[label].folder = VF_current_folder;
		return VF_current_folder;
	}
}
int TreeFiles_pass__properties_level (VirtualFolder* TF, std::string label)
{
	return TF->GLobal_position[label].level;
}
VirtualFolder* TreeFiles_pass__correct_pointer (VirtualFolder* VF_current_folder, int* level, std::string label)
{
	VirtualFolder* VF_diving = TreeFiles_pass__diving(VF_current_folder, label); //погружаемся
	if (VF_diving != NULL)
	{
		VF_current_folder = VF_diving;
		(*level)++;
		return VF_current_folder;
	}


	VirtualFolder* VF_next = TreeFiles_pass__next_equal_folder(VF_current_folder, (*level), label); //Получаем указатель на следующую папку
	if (VF_next != NULL)
	{
		VF_current_folder = VF_next;
		return VF_current_folder;
	}


	VirtualFolder* VF_surfacing = TreeFiles_pass__surfacing(VF_current_folder, &(*level), label); //всплываем
	if ((VF_surfacing != NULL) && (*level) > 0)
	{
		(*level)--;
		VF_current_folder = TreeFiles_pass__next_equal_folder(VF_surfacing, (*level), label);
		return VF_current_folder;
	}
	else
		return NULL;
}
VirtualFolder* TreeFiles_pass__diving (VirtualFolder* VF_current_folder, std::string label)
{
	if (VF_current_folder == NULL)
		return NULL;

	VirtualFolder* VF_save_dota_folder = NULL;
	int i = 0;

	for (auto VF_find_dota_folder : VF_current_folder->v_child_folders) //Перебираем дочерние папки
	{
		if (i == VF_current_folder->position[label]) //Если дошли до необработанной дочерней папки
		{
			VF_save_dota_folder = VF_find_dota_folder;
			break; //Поиск окончен
		}
		i++;
	}



	return VF_save_dota_folder;
}
VirtualFolder* TreeFiles_pass__next_equal_folder (VirtualFolder* VF_current_folder, int level, std::string label)
{
	return TreeFiles_pass__diving(VF_current_folder->parent, label);
}

VirtualFolder* TreeFiles_pass__surfacing (VirtualFolder* VF_current_folder, int* level, std::string label)
{
	if (VF_current_folder == NULL)
		return NULL;
	VirtualFolder* VF_parent = VF_current_folder->parent;
	// level--;
	while (true)
	{
		if (((*level) < 1) || (VF_parent == NULL) || (VF_parent->parent == NULL)) //?
		{
			VF_parent = NULL; //Конец визуализации
			break;
		}


		if (VF_parent->parent->position[label] >= VF_parent->parent->v_child_folders.size()) //Если количество обработанных элементов на уровне этого объекта больше или равно количеству элементов
		{
			VF_parent = VF_parent->parent; //Всплываем
			(*level)--;
		}
		else
			break; //Необработанный родитель уже найден, поиск окончен


		if (((*level) < 1) || (VF_parent == NULL) || (VF_parent->parent == NULL)) //?
		{
			VF_parent = NULL; //Конец визуализации
			break;
		}
	}
	return VF_parent;
}












//-------------ОТЛАДОЧНЫЕ-------------------------
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












// #ВИЗУАЛИЗАЦИЯ КАТАЛОГА
// <	(ДФ)
// <	адрес каталога
// >	в консоли выводится дерево файлов
// ::	
void TreeFiles_visuale (VirtualFolder* TF)
{
	set<string> mandatory_properties; //Свойства которые не выводятся в описании файла
	mandatory_properties.insert("Name");
	VirtualFolder* VF_current_folder;
	while (true)
	{
		VF_current_folder = TreeFiles_pass(TF, "visualization");
		if (VF_current_folder == NULL)
			break;
		else
		{
			string tabulation = "";
			for (int i = 0; i < TreeFiles_pass__properties_level(TF, "visualization"); ++i)
				tabulation += "	";

			TreeFiles_visuale__print_folder(VF_current_folder, mandatory_properties, tabulation); //Печатаем свойства папки и вложенные файлы
			TreeFiles_visuale__print_files(VF_current_folder, mandatory_properties, tabulation);
		}
	}
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
	vector < VirtualFolder__file* >::iterator Iter_files;
	for (Iter_files = VF_current_folder->files.begin(); Iter_files != VF_current_folder->files.end(); Iter_files++)
	{
		cout << tabulation << "	|-- " << (*Iter_files)->properties_string["Name"] << "	";

		TreeFiles_visuale__print_property_files__string(VF_current_folder, tabulation, mandatory_properties, *Iter_files);
		TreeFiles_visuale__print_property_files__int(VF_current_folder, tabulation, mandatory_properties, *Iter_files);

		cout << endl;
	}
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
void TreeFiles_visuale__print_property_files__string (VirtualFolder* folder, std::string tabulation, set<string> mandatory_properties, VirtualFolder__file* VFF_file)
{
	map<string, string>::const_iterator itr_string;

	for (itr_string = (VFF_file->properties_string).begin(); itr_string != (VFF_file->properties_string).end(); ++itr_string)
	{
		if (mandatory_properties.find((*itr_string).first) == mandatory_properties.end()) //Печатаем свойство, если его нет в исключениях
			cout << " [" << (*itr_string).first << ": " << (*itr_string).second << "]";
	}
}
void TreeFiles_visuale__print_property_files__int (VirtualFolder* folder, std::string tabulation, set<string> mandatory_properties, VirtualFolder__file* VFF_file)
{
	map<string, int>::const_iterator itr_int;

	for (itr_int = (VFF_file->properties_int).begin(); itr_int != (VFF_file->properties_int).end(); ++itr_int)
	{
		if (mandatory_properties.find((*itr_int).first) == mandatory_properties.end()) //Печатаем свойство, если его нет в исключениях
			cout << " [" << (*itr_int).first << ": " << (*itr_int).second << "]";
	}
}