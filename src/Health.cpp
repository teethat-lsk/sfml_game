#include "Health.h"

void Health::initializeTexture()
{
	if (!this->hpbar.loadFromFile("Resources/Images/hpbar.png"))
	{
		std::cout << "FAIL LOADING HP_BAR" << std::endl;
	}
}

Health::Health(float hp,float barWidth,float barHeight,sf::Vector2f scale)
	
{
	initializeTexture();
	this->barWidth = barWidth;
	this->barHeight = barHeight;
	
	this->maxHp = hp;
	this->currentHp = hp;
	this->blackBar.setSize(sf::Vector2f(this->barWidth,this->barHeight));
	this->blackBar.setFillColor(sf::Color::Black);
	this->redBar.setSize(sf::Vector2f(this->barWidth, this->barHeight));
	this->redBar.setFillColor(sf::Color::Red); 
	this->hpBar.setTexture(this->hpbar);
	this->hpBar.setScale(scale);

}

void Health::update(float HPx,float HPy,float BarX,float BarY)                                                                                                                                                                                            
{
	this->blackBar.setPosition(BarX,BarY);
	this->redBar.setPosition(BarX, BarY);
	this->hpBar.setPosition(HPx,HPy);
	if(this->currentHp>0)
	this->redBar.setSize(sf::Vector2f((this->currentHp/this->maxHp)*this->barWidth,this->barHeight));
	
}

void Health::render(sf::RenderTarget& target)
{
	
	target.draw(this->blackBar);
	target.draw(this->redBar);
	target.draw(this->hpBar);
}
void Health::damage(int damage)
{

	this->currentHp -= damage;
	if (this->currentHp > this->maxHp)
	{
		this->currentHp = this->maxHp;

	}
	
}


float Health::getHealth()
{
	return this->currentHp;
}
Health::~Health()
{
}
