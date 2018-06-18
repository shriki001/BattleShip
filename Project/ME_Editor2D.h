#pragma once
#include "ME_Editor.h"


class Editor2D : public Editor
{
public:
	Editor2D() = default;
	void ShowButton(const sf::Vector2f &currPos, sf::RenderWindow & app, const bool);
};