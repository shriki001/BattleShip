#pragma once
#include "ImageMenuButton.h"


class OptionButton :public MenuButton
{
public:
	OptionButton(const sf::Text & ButtonNameTxt,const sf::Vector2f& position);
	void addOption(const sf::Text& newOptionTxt);
	void render(sf::RenderWindow& window) const;
	void update(sf::RenderWindow & window);
	sf::FloatRect getGlobalBounds() const;
	void setName(const sf::Text& newText, int offsetOption = 0);
	void choose() override;
	void unchoose() override;
	int getChooseButton();
	void reset();
	void setCurrentOpt(int);

private:
	sf::Text m_NameText;
	std::shared_ptr<ImageMenuButton> m_fowardButton;
	std::shared_ptr<ImageMenuButton> m_backwardButton;
	std::vector<sf::Text> m_options;
	short m_currentOption;
	sf::Vector2f m_position;
	short m_chooseButton = -1;

};