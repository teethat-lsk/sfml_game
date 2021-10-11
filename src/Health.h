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
class Health
{
private:
	float currentHp ;
	float maxHp;
	sf::Texture hpbar;
	sf::Sprite hpBar;
	
	float barWidth;
	float barHeight;
	sf::Vector2f barPosition;
	void initializeTexture();
	sf::Vector2f spriteScale;
	sf::Sprite healthBar;
	sf::RectangleShape blackBar;
	sf::RectangleShape redBar;
	

public:
	Health(float health,float barWidth, float barHeight,sf::Vector2f scale);
	virtual ~Health();

	void damage(int damage);
	
	void update(float HPx, float HPy, float BarX, float BarY);
	void render(sf::RenderTarget &target);
	float getHealth();
};

