
#include "Board.h"
#include <fstream>

Board::Board(const std::string file)
{
	std::ifstream m_inputFile;
	try
	{
		m_inputFile.open(file, std::ios_base::binary);
		if (!m_inputFile.is_open())
			throw std::runtime_error("Cannot open file");
	}
	catch (std::exception&)
	{
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < M_ROW; i++)
	{
		for (int j = 0; j < 2*M_COL; j++)
			m_board[i][j] = m_inputFile.get();
		m_inputFile.get();
		m_inputFile.get();
	}
	m_inputFile.close();
}

std::pair<char, int> Board::show(int x, int y)
{
	return std::make_pair(m_board[y][x * 2], m_board[y][x * 2 + 1] - '0');
}