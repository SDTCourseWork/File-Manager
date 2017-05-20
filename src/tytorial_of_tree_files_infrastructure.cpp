#include <iostream>
#include <sstream>
#include <typeinfo>
// #include <algorithm>
#include <vector>
#include <string>
#include <map>

using namespace std;

#include "function/bicycle.cpp"
#include "function/ftree_files_infrastructure.cpp"
#include "function/infrastructure.cpp"



int main()
{



cout << endl << endl << endl << endl << endl << endl;
cout << "DEMONSTRATION: create and visualization" << endl;

/*
Создавать дерево файлов обязательно нужно при помощи функции TreeFiles_create().

TreeFiles_add(указатель на дерево файлов, строка в которой передается адрес нового файла, или папки).
При создании папки в конце адреса нужно писать '/' вот такой символ, иначе это будет трактоваться как файл с расширением.
Папки/файлы создаются всегда по указателю на Дерево файлов, а адрес пишется от корня директории.
*/
	VirtualFolder* test = TreeFiles_create();
	TreeFiles_add(test, "1a/"); //создается папка 1a
	TreeFiles_add(test, "1a/2a/3a/"); //создается папка 2a внутри папки 1a
	TreeFiles_add(test, "1a/2a/3b/"); //создается папка 2a внутри папки 1a
	TreeFiles_add(test, "1a/2a/"); //создается папка 2a внутри папки 1a
	TreeFiles_add(test, "1a/2a/fileone"); //создается файл fileone
	TreeFiles_add(test, "1a/2a/filetwo.jpg");  //создается файл filetwo.jpg
	TreeFiles_add(test, "1c/");

	TreeFiles_visuale(test); //визуализируем то, что надобавляли, для отладки функция





cout << endl << endl << endl << endl << endl << endl;
cout << "DEMONSTRATION: delete" << endl;
	TreeFiles_delete(test, "1a/2a/fileone");
	TreeFiles_visuale(test); //визуализируем то, что надобавляли, для отладки функция





cout << endl << endl << endl << endl << endl << endl;
cout << "DEMONSTRATION: properties of folder" << endl;
/*
Функция поиска папки или файла возвращает указатель на файл, по которому можно
	узнать о наличии свойства
	изменить его значение
	получить свойство.
Все свойства делятся на 2 типа: строковые (std::string) и численные (int).
Для каждого типа нужно пользоваться своим типом
                                V   в конце функции просто пишется, я реализовал пока что только два типа, string и int
TreeFiles_change_file_property_int


Добавлять свойства можно сколько угодно с любым называнием, но только на английском.
Для добавления или изменение свойства пользоваться TreeFiles_change_file_property_string. Например:
TreeFiles_change_file_property_int(test_file, "hash", 77777);


(1) На вход подается указатель полуенный функцией TreeFiles_find_folder или TreeFiles_find_file
(2) Имя свойства
(3.1) Новое значение свойства, строка у строковых (тип std::string)
(3.2) Новое значение свойства, число у числовых (тип int в данном случае)
*/
	VirtualFolder* test_folder = TreeFiles_find_folder(test, "1a/2a/"); //получаем указатель на папку 2a
	VirtualFolder__file* test_file = TreeFiles_find_file(test, "1a/2a/fileone"); //получаем указатель на файл fileone

	cout << (test_folder == NULL) << endl;
	cout << "TreeFiles_isset_folder_property_string " 
		<< TreeFiles_isset_folder_property_string(test_folder, "Name_tytorial_of_test_folder") << endl; //Проверяем наличие строковое свойства у файла
	cout << "TreeFiles_isset_folder_property_int " 
		<< TreeFiles_isset_folder_property_int(test_folder, "Name_tytorial_of_test_folder") << endl; //Проверяем наличие числового свойства у файла


/*                                               (1)             (2)                           (3.1)*/
	TreeFiles_change_folder_property_string(test_folder, "Name_tytorial_of_test_folder", "new_name_folder"); //изменяем строковое значение свойства
/*                                             (1)              (2)                  (3.2)*/
	TreeFiles_change_folder_property_int(test_folder, "Name_tytorial_of_test_folder", 38); //изменяем числовое значение свойства


	cout << "TreeFiles_get_folder_property_string " 
		<< TreeFiles_get_folder_property_string(test_folder, "Name_tytorial_of_test_folder") << endl; //получить строкове свойство
	cout << "TreeFiles_get_folder_property_int " 
		<< TreeFiles_get_folder_property_int(test_folder, "Name_tytorial_of_test_folder") << endl; //получить числовое свойство

cout << endl << endl << endl << endl << endl << endl;
cout << "DEMONSTRATION: properties of file" << endl;

	cout << "TreeFiles_isset_file_property_string " 
		<< TreeFiles_isset_file_property_string(test_file, "Name_tytorial_of_test_file") << endl;
	cout << "TreeFiles_isset_file_property_int " 
		<< TreeFiles_isset_file_property_int(test_file, "Name_tytorial_of_test_file") << endl;


	TreeFiles_change_file_property_string(test_file, "Name_tytorial_of_test_file", "new_name_file");
	TreeFiles_change_file_property_int(test_file, "Name_tytorial_of_test_file", 53);


	cout << "TreeFiles_get_file_property_string " 
		<< TreeFiles_get_file_property_string(test_file, "Name_tytorial_of_test_file") << endl;
	cout << "TreeFiles_get_file_property_int " 
		<< TreeFiles_get_file_property_int(test_file, "Name_tytorial_of_test_file") << endl;




cout << endl << endl << endl << endl << endl << endl;
cout << "DEMONSTRATION: proxod po folder" << endl;

/*
Это пример прохда по файлам, функция TreeFiles_pass (от анлийского passage - проход)
возвращает указатель на новый элемент. Проход происходит по меткам, чтобы разные алгоритмы
не конфликтовали. Например в визуализации подается метка "visualization". Метки можно придумать
любые.
Проход происходит в таком же порядке, в каком выводятся элементы при визуализации.
НА ВХОД ОБЯЗАТЕЛЬНО ПОДАВАТЬ УКАЗАТЕЛЬ НА ДЕРЕВО ФАЙЛОВ, ВОЗМОЖНОСТИ ОБХОДА ДЕРЕВА С 
ОПРЕДЕЛЕННОЙ ПАПКИ НЕТУ, НО МОЖНО ПОПРОСИТЬ ДИМУ И ОН ЕГО СДЕЛАЕТ.
*/
	VirtualFolder* VF_folder;
	while (true)
	{
		VF_folder = TreeFiles_pass(test, "metka_primer_proxoda");
		if (VF_folder == NULL)
			break;
		else
		{
			std::string address_scan = TreeFiles_get_address_of_folder(VF_folder); //получаем адрес папки по указателю
			cout << address_scan << " " << TreeFiles_get_folder_property_string(VF_folder, "Name") << endl; //выводим строковое значение свойства по этому указателю (имя в данном случае)
		}
	}


cout << endl << endl << endl << endl << endl << endl;
cout << "DEMONSTRATION: proxod po file" << endl;
/*
Это пример прохода по всем файлам в папке. Проход тоже по меткам.
*/
	while (true)
	{
		VirtualFolder__file* test_file2 = TreeFiles_pass_files (test_folder, "metka_testing"); //получаем указатель на файл
		if (test_file2 == NULL)
			break;
		else
			cout << TreeFiles_get_file_property_string(test_file2, "Name") << endl;
	}
	TreeFiles_pass_files_on_start(test_folder, "metka_testing"); //обнуляем указатель, можно вместо этого просто метку изменить



	return 0;
}