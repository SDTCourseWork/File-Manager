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


int main()
{
	
	// VirtualFolder* test = new VirtualFolder;
	VirtualFolder* test = TreeFiles_create ();
	TreeFiles_add(test, "1a/"); //создается папка 1a
	TreeFiles_add(test, "1a/2a/"); //создается папка 2a внутри папки 1a
	TreeFiles_add(test, "1a/2a/fileone"); //создается файл fileone
	TreeFiles_add(test, "1a/2a/filetwo.jpg");  //создается файл filetwo.jpg
	TreeFiles_add(test, "1c/");

	// TreeFiles_visuale(test); //визуализируем то, что надобавляли, для отладки функция

	VirtualFolder* test_folder = TreeFiles_find_folder(test, "1a/2a/"); //получаем указатель на папку 2a
	VirtualFolder__file* test_file = TreeFiles_find_file(test, "1a/2a/fileone"); //получаем указатель на файл fileone

/*










	cout << "TreeFiles_isset_property_string " << TreeFiles_isset_folder_property_string(test_folder, "Name_tytorial_of_test_folder") << endl; //Проверяем наличие строковое свойства у файла
	cout << "TreeFiles_isset_folder_property_int " << TreeFiles_isset_folder_property_int(test_folder, "Name_tytorial_of_test_folder") << endl; //Проверяем наличие числового свойства у файла
	TreeFiles_change_folder_property_string(test_folder, "Name_tytorial_of_test_folder", "new_name_folder"); //изменяем строковое значение свойства
	TreeFiles_change_folder_property_int(test_folder, "Name_tytorial_of_test_folder", 38); //изменяем числовое значение свойства
	cout << "TreeFiles_get_folder_property_string " << TreeFiles_get_folder_property_string(test_folder, "Name_tytorial_of_test_folder") << endl; //получить строкове свойство
	cout << "TreeFiles_get_folder_property_int " << TreeFiles_get_folder_property_int(test_folder, "Name_tytorial_of_test_folder") << endl; //получить числовое свойство

	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;

	cout << "TreeFiles_isset_property_string " << TreeFiles_isset_file_property_string(test_file, "Name_tytorial_of_test_file") << endl;
	cout << "TreeFiles_isset_file_property_int " << TreeFiles_isset_file_property_int(test_file, "Name_tytorial_of_test_file") << endl;
	TreeFiles_change_file_property_string(test_file, "Name_tytorial_of_test_file", "new_name_file");
	TreeFiles_change_file_property_int(test_file, "Name_tytorial_of_test_file", 53);
	cout << "TreeFiles_get_file_property_string " << TreeFiles_get_file_property_string(test_file, "Name_tytorial_of_test_file") << endl;
	cout << "TreeFiles_get_file_property_int " << TreeFiles_get_file_property_int(test_file, "Name_tytorial_of_test_file") << endl;


*/





	VirtualFolder* VF_folder;
	while (true)
	{
		VF_folder = TreeFiles_pass(test, "metka_primer_proxoda");
		if (VF_folder == NULL)
			break;
		else
		{
			// TreeFiles_get_address_of_folder(VF_folder); //получаем адрес папки по указателю
		}
	}




	while (true)
	{
		VirtualFolder__file* test_file2 = TreeFiles_pass_files (test_folder, "testing"); //получаем указатель на файл
		if (test_file2 == NULL)
			break;
		else
			cout << TreeFiles_get_file_property_string(test_file2, "Name") << endl;
	}
	TreeFiles_pass_files_on_start (test_folder, "testing"); //обнуляем указатель, можно вместо этого просто метку изменить



	return 0;
}