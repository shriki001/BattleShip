#pragma once
#include "ME_Editor.h"

class Editor3D : public Editor
{
public:
	Editor3D() = default;
	void ShowButton(const sf::Vector2f &currPos, sf::RenderWindow & app, const bool);
};