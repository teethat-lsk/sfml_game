#pragma once
#include "Enemy.h"



class Skeleton :
	public Enemy
{
private:
	
	
	void initializeVariables() ;
	bool attack;
	sf::SoundBuffer attackbuffer;
	sf::Sound attacksound;
	

	//void updateMovement();
	//void getPlayerPosition();

public:
	Skeleton(float speed,float hp,float x, float y, sf::Texture& texture_sheet);
	virtual ~Skeleton();

	void stopmoving();
	 void updateAnimation(const float& deltaTime) ;
	 void Attack(const float& deltaTime);
	 void update(const float& deltaTime) ;
	 const sf::Vector2f getPosition();
	 const sf::Vector2f& getHitboxPosition() const;
	 const sf::FloatRect getHitboxGlobalBound() const;
	
	 float getHealth();
	// void render(sf::RenderTarget& target);
	// void set_pt(Player*);
};

