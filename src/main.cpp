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

	VirtualFolder *test = TreeFiles_create();
	TreeFiles_add(test, "1a/");
	TreeFiles_add(test, "1a/2a/");
	TreeFiles_add(test, "1b/");
	// TreeFiles_add(test, "1a/2a/");
	// TreeFiles_add(test, "1a/2a/3a/");
	// TreeFiles_add(test, "1a/2a/3a/");

	// TreeFiles_add(test, "1a/2a/3b/");
	TreeFiles_visuale(test);	















	// if (TreeFiles_find_folder(test, "asd\\fd/ono.jpt") != NULL)
	// 	cout << "+" << endl;
	// else
	// 	cout << "-" << endl;
	// delete test;

	// string str = "adfasdf;asdfsdf;asdf";
	// vector<string> v;
	// v = Split(str, ';');
	// vector < string >::iterator it_int; //объявляю итератор it
	// for (it_int = v.begin(); it_int != v.end(); it_int++)
	// {
	// 	cout << (*it_int) << endl;
	// }




	return 0;
}