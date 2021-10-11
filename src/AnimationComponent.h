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
class AnimationComponent
{
private: 
	class Animation {

	
	public: 

		sf::Sprite& sprite;
		sf::Texture& textureSheet;
		float animationTimer;
		float timer;
		int width;
		int height;
		bool done;
		sf::IntRect startRect;
		sf::IntRect endRect; 
		sf::IntRect currentRect;

		
		

		Animation(sf::Sprite& sprite, sf::Texture& texture_sheet,
			float animationTimer, 
			int start_x,int start_y,int end_x,int end_y,int width,int height)
			:sprite(sprite),textureSheet(texture_sheet),animationTimer(animationTimer),width(width),height(height),timer(0.f),done(false)
		{
			this->startRect = sf::IntRect(start_x*width, start_y*height, width, height);
			this->endRect = sf::IntRect(end_x * width, end_y * height, width, height);

			this->currentRect = this->startRect;
			 
			this->sprite.setTexture(this->textureSheet, true);
			this->sprite.setTextureRect(this->startRect);

		}
		
		//Accesors
		const bool& isDone() const
		{
			return this->done;
		}
		
		//Function
		const bool& play(const float& deltaTime) {
			
			//Update Timer
			this->done = false;
			this->timer += 100.f * deltaTime;
			//std::cout << this->timer << std::endl;
			//std::cout << deltaTime << std::endl;
			if (this->timer >= animationTimer)
			{
				//reset Timer
				this->timer = 0.f;

				if (this->currentRect != this->endRect)//Animate
				{
					this->currentRect.left += this->width;
				}
				else//Reset
				{
					this->currentRect.left = this->startRect.left;
					this->done = true;
				}
				this->sprite.setTextureRect(this->currentRect);

			}
			return this->done;
		}

		const bool& play(const float& deltaTime,float percentage) {
			this-> done = false;
			//Update Timer
			if (percentage < 0.5f)
			{
				percentage = 0.5f;
			}
			this->timer +=(percentage)* 100.f * deltaTime;
			if (this->timer >= animationTimer)
			{
				//reset Timer
				this->timer = 0.f;

				if (this->currentRect != this->endRect)//Animate
				{
					this->currentRect.left += this->width;
				}
				else//Reset
				{
					this->currentRect.left = this->startRect.left;
					this->done = true;
				}
				this->sprite.setTextureRect(this->currentRect);

			}
			return this->done;
		}
		
		void reset()
		{
			this->timer = animationTimer;
			this->currentRect.left = this->startRect.left;

		}


	};

	sf::Sprite& sprite;
	sf::Texture& textureSheet;
	std::map<std::string, Animation*> animations;
	Animation* lastAnimation;
	Animation* priorityAnimation;
	

protected:

public:
	AnimationComponent(sf::Sprite& sprite , sf::Texture& texture_sheet);
	virtual ~AnimationComponent();

	//Accessor
	const bool& isDone(const std::string key);

	//Functions
	void addAnimation(const std::string key, 
						float animationTimer,
						int start_x, int start_y, int end_x, int end_y, int width, int height);


	const bool& play(const std::string key, const float& deltaTime,/*sf::Sound sound,*/const bool priority=false); // update animation
	const bool& play(const std::string key, const float& deltaTime,const float& modifier,const float& modifier_max,/*sf::Sound sound,*/const bool priority=false);
};

