#include <iostream> //содержимым файла «iostream.h», который находится в стандартной библиотеке языка и отвечает за ввод и вывод данных на экран.
#include <cstdlib> //подключает стандартную библиотеку языка С. Это подключение необходимо для работы функции system.
#include <string>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <map>
#include <time.h>
// #include <algorithm>
#include <set>
#include <cstring>
using namespace std; //указывает на то, что мы используем по умолчанию пространство имен с названием «std»

#include "function/bicycle.cpp"
#include "function/ftree_files_infrastructure.cpp"
#include "function/infrastructure.cpp"


int main()
{

cout << "DEMONSTRATION: Explode" << endl;

/*
Explode - это функция которую я в интренете нашел и прекрасно использую,
 она находится в документе function/bicycle.cpp
 */
std::string str1 = "a/b/c/d/";
/*                                        V разделитель нужно передавать обязательно как char, то есть в одинарных ковычках*/
vector <string> vec_str = Explode (str1, '/');



cout << endl << endl << endl << endl << endl << endl;
cout << "DEMONSTRATION:  for on Iter" << endl;
/*
пример перебора всех элементов вектора
Iter_string - это УКАЗАТЕЛЬ НА ТЕКУЩИЙ ЭЛЕМЕНТ ВЕКТОРА
*/
vector < string >::iterator Iter_string;
int i = 0;
for (Iter_string = vec_str.begin(); Iter_string != vec_str.end(); Iter_string++)
{
	cout << "elem number " << i << " -> " << *Iter_string << endl;
	i++;
}


cout << endl << endl << endl << endl << endl << endl;
cout << "DEMONSTRATION:  for on auto" << endl;
/*
можно сделать еще круче, проще, нагляднее
Здесь Iter_current_string является строкой, а не указателем
*/
i = 0;
for (auto Iter_current_string : vec_str)
{
	cout << "elem number " << i << " -> " << Iter_current_string << endl;
	i++;
}




cout << endl << endl << endl << endl << endl << endl;
cout << "DEMONSTRATION:  Implode" << endl;
/*
Implode собирает вектор из строк в строку
*/
/*                         V      делитель здесь передается, как строка std::string, то есть в двойных кавычках*/
cout << Implode (vec_str, "/") << endl;


cout << endl << endl << endl << endl << endl << endl;
cout << "DEMONSTRATION:  Implode_invert" << endl;
cout << Implode_invert (vec_str, "/") << endl;



cout << endl << endl << endl << endl << endl << endl;
cout << "DEMONSTRATION:  replace" << endl;
std::string address_test = "address\\b/c    \"     ";
/*
\ - при помощи этого символа идет экранирование, можно кавычку двойную внутри двойных кавычек вывести
\\ или этот же символ
\" вот так вот кавычку
*/
replace(address_test, "\\", "/"); //ЭТА ФУНКЦИЯ РЕДАКТИРУЕТ СТРОКУ, А НЕ ВОЗВРАЩАЕТ НОВУЮ, тип void
cout << address_test << endl;




cout << endl << endl << endl << endl << endl << endl;
cout << "DEMONSTRATION:  std_string_compare" << endl;

/*
std_string_compare сравнивает две строки, возрвращемый тип int
	если строка 1 равна строке 2, то выдает 0
	если строка 1 больше строки 2, то выдает 1   ('a' < 'b')
	если строка 1 меньше строки 2, то выдает -1  ('z' > 'a')
*/

std::string compare_str1 = "abc";
std::string compare_str2 = "bbc";
std::string compare_str3 = "bbc";
std::string compare_str4 = "zbc";
cout	<< "1-2 " << std_string_compare(compare_str1, compare_str2) <<	"	1 < 2"	<< endl
		<< "2-3 " << std_string_compare(compare_str2, compare_str3)	<<	"	2 == 3"	<< endl
		<< "3-4 " << std_string_compare(compare_str3, compare_str4)	<<	"	3 < 4"	<< endl
		<< "4-1 " << std_string_compare(compare_str4, compare_str1)	<<	"	4 > 1"	<< endl;





cout << endl << endl << endl << endl << endl << endl;
cout << "DEMONSTRATION:  create_rand_string" << endl;
srand(time(NULL)); //Меняем базу, внутри функции это не делается, это нужно, чтобы каждый раз числа были рандомные
cout << create_rand_string(5) << endl;













/*
	map<string, int>::const_iterator itr_int;

	for (itr_int = (VFF_file->properties_int).begin(); itr_int != (VFF_file->properties_int).end(); ++itr_int)
	{
		if (mandatory_properties.find((*itr_int).first) == mandatory_properties.end()) //Печатаем свойство, если его нет в исключениях
			cout << " [" << (*itr_int).first << ": " << (*itr_int).second << "]";
	}
*/

	return 0;
}