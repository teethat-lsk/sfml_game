#pragma once
#include<SFML\Graphics.hpp>
#include<SFML\Audio.hpp>
#include<SFML\Window.hpp>
#include<SFML\Network.hpp>
#include<SFML\System.hpp>

#include<iostream>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include<sstream>
#include<stack>
#include<map>
class HitboxComponent
{
private:
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	float offsetX;
	float offsetY;

public:
	HitboxComponent(sf::Sprite& sprite,float offset_x,float offset_y,float width, float height);
	virtual ~HitboxComponent();

	//Function
	bool checkintersect(const sf::FloatRect& frect);

	void update();
	void render(sf::RenderTarget& target);
	const sf::Vector2f& getPosition() const;
	const sf::FloatRect getGlobalBound() ;
	sf::Vector2f getHbcenter();
	sf::Vector2f getHbrad();
	
	
};

