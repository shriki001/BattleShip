#pragma once
#include <array>
#include <string>
#include "settings.h"

class Board
{
public:
	Board(const std::string);
	std::pair<char, int>  show(int ,int);
	~Board() = default;

private:
	std::array<std::array<char ,2*M_COL>, M_ROW> m_board;
};