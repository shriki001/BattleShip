
#include "Language.h"
#include <fstream>
#include <codecvt>

Language::Language(std::string file)
{
	std::wifstream fin(file);
	fin.imbue(std::locale(fin.getloc(),
		new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
	std::wstring str;
	for (; getline(fin, str); )
		m_language.emplace_back(std::move(str));
	fin.close();
}

std::wstring Language::getString(int index)
{
	try 
	{
		return m_language.at(index);
	}
	catch(std::exception&)
	{
		puts("cant get string");
		exit(EXIT_FAILURE);
	}
}

size_t Language::getDicSize()
{
	return m_language.size();
}