#pragma once

#include <vector>
#include <string>

class Language
{
public:
	Language(std::string file);
	std::wstring getString(int);
	size_t getDicSize();
	~Language() = default;

private:
	std::vector<std::wstring> m_language;
};