#pragma once
#include "Menu.h" 


class OptionsMenu : public Menu
{
public:
	OptionsMenu(const sf::Vector2u& windowSize = { 1000,1000 });
	void update(sf::RenderWindow & window);
	void draw(sf::RenderWindow& window);
	int isChoosen() const override;
	int isOnButton(sf::RenderWindow & window) const;
	void choose(int x) override;
	void unchoose() override;
	int handleMenuEvents(sf::Event &e);
	void setNames() override;
	void reset();
	static std::string getName() { return strName; }
	static void setName(std::string name) { strName = name; }

	void syncOptionName();

private:
	static sf::Texture bg;
	static sf::Font font;
	static sf::Text name;
	static std::string strName;
};