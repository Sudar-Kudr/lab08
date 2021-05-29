/*!
	\file
	\brief Заголовочный файл print.hpp
	Декларация
*/
#include <string>
#include <fstream>
#include <iostream>

/*!
Функция вывода (1)
\param[in] text стринговая переменная, для записи текста
\param[in] out оператор вывода
*/
void print(const std::string& text, std::ostream& out = std::cout);
/*!
Функция вывода (2)
\param[in] text стринговая переменная, для записи текста
\param[in] out оператор вывода из файла
*/
void print(const std::string& text, std::ofstream& out);