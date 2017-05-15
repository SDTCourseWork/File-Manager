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
	
	VirtualFolder* test = new VirtualFolder;
	TreeFiles_add(test, "1a/");
	TreeFiles_add(test, "1a/2a/");
	TreeFiles_add(test, "1a/2a/fileone");
	TreeFiles_add(test, "1a/2a/filetwo");

	TreeFiles_add(test, "1a/2a/");
	TreeFiles_add(test, "1a/2a/3a/4/5/6/7/8/9/");
	TreeFiles_add(test, "1a/2a/3a/adf/asdf/asdf/asdf/asasdfddf/sad/fasdf/asdf");
	TreeFiles_add(test, "1a/2b/3a/");

	TreeFiles_add(test, "1a/2a/3b/");
	TreeFiles_add(test, "1b/");
	TreeFiles_add(test, "1c/");

	VirtualFolder* test_folder = TreeFiles_find_folder(test, "1a/2a/");
	VirtualFolder__file* test_file = TreeFiles_find_file(test, "1a/2a/fileone");

	while (true)
	{
		VirtualFolder__file* test_file2 = TreeFiles_pass_files (test_folder, "testing");
		if (test_file2 == NULL)
			break;
		else
			cout << TreeFiles_get_file_property_string(test_file2, "Name") << endl;
	}
	TreeFiles_pass_files_on_start (test_folder, "testing");

// cout << "TreeFiles_isset_property_string " << TreeFiles_isset_file_property_string(test_file, "Name") << endl;
// cout << "TreeFiles_isset_file_property_int " << TreeFiles_isset_file_property_int(test_file, "Name") << endl;
// TreeFiles_change_file_property_string(test_file, "Name", "name38");
// TreeFiles_change_file_property_int(test_file, "Name", 38);
// cout << "TreeFiles_get_file_property_string " << TreeFiles_get_file_property_string(test_file, "Name") << endl;
// cout << "TreeFiles_get_file_property_int " << TreeFiles_get_file_property_int(test_file, "Name") << endl;



// TreeFiles_visuale  (test);















	// if (TreeFiles_find_folder(test, "asd\\fd/ono.jpt") != NULL)
	// 	cout << "+" << endl;
	// else
	// 	cout << "-" << endl;
	// delete test;

	// string str = "adfasdf;asdfsdf;asdf";
	// vector<string> v;
	// v = Explode(str, ';');
	// vector < string >::iterator it_int; //объявляю итератор it
	// for (it_int = v.begin(); it_int != v.end(); it_int++)
	// {
	// 	cout << (*it_int) << endl;
	// }




	return 0;
}