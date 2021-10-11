#pragma once
#include<vector>

#include<SFML\Graphics.hpp>
#include<SFML\Audio.hpp>
#include<SFML\Window.hpp>
#include<SFML\System.hpp>

#include<iostream>
#include<cstdlib>
#include<ctime>
#include<sstream>

enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };

class Button
{
private:
	sf::RectangleShape buttonShape;
	sf::Font* font;
	sf::Text text;
	unsigned short buttonState;
	
	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

	sf::Color textIdleColor;
	sf::Color textHoverColor;
	sf::Color textActiveColor;


protected:


public:
	Button(float x,float y,float width,float height,sf::Font* font,std::string text,
		unsigned textSize,sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
		sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color);
	~Button();

	const bool isPressed() const;

	void update(const sf::Vector2i& mousePos);
	void render(sf::RenderTarget& target);
	
};

