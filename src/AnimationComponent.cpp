#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet)
: sprite(sprite), textureSheet(texture_sheet),lastAnimation(NULL),priorityAnimation(nullptr)
{

}

AnimationComponent::~AnimationComponent()
{
	for (auto &i : this->animations)
	{
		delete i.second;
	}
}

//Accessors
const bool& AnimationComponent::isDone(const std::string key) 
{
	
	return this->animations[key]->isDone();
}

//Function
void AnimationComponent::addAnimation(const std::string key,
							float animationTimer,
							int start_x, int start_y, int end_x, int end_y, int width, int height)
{
	this->animations[key]  = new  Animation(this->sprite, this->textureSheet, animationTimer, start_x, start_y, end_x, end_y, width, height);
}


const bool& AnimationComponent::play(const std::string key,const float& deltaTime,/*sf::Sound sound*/const bool priority)
//normal play() function used for NONE incresing motion speed animation necessary or instant aniamtion  (idle, shiedl , Attack1 2 3)
{
	

	if (this->priorityAnimation) // if priority move occure ==>  just play it
	{
		
		if (this->priorityAnimation == this->animations[key])
		{
			if (lastAnimation != this->animations[key])
			{
				if (this->lastAnimation == NULL)
				{
					this->lastAnimation = this->animations[key];
				}
				else
				{
					this->lastAnimation->reset(); 
					this->lastAnimation = this->animations[key];
				}

			}
			if (this->animations[key]->play(deltaTime)) {
				// Animation::play() also return bool "done" whenever the animation  
				//is done animating play() will return true to this if statement 
				//and set the priorityAnimation pointer to NULL											
			
				this->priorityAnimation = NULL;
			}
		}
	}
	else { // otherwise play animation as usual
		if (priority) // if ther is any  priority animation request to animate ==> set the priorityAnimation to that animation
		{
			this->priorityAnimation = this->animations[key];
		}
		if (lastAnimation != this->animations[key])
		{
			if (this->lastAnimation == NULL)
			{
				this->lastAnimation = this->animations[key];
			}
			else
			{
				this->lastAnimation->reset();
				this->lastAnimation = this->animations[key];
			}

		}

		this->animations[key]->play(deltaTime);
		//this->lastAnimation->play(deltaTime);
	}
	return this->animations[key]->isDone();
}

const bool& AnimationComponent::play(const std::string key, const float& deltaTime, const float& modifier, const float& modifier_max,/*sf::Sound sound,*/ const bool priority)
//unusual play() function used for increasing motion speed animtion necessary (Run Walk Jump(not exactly in the plan))
{
	

	if (this->priorityAnimation) // if priority move occure ==>  just play it
	{
		
		if (this->priorityAnimation == this->animations[key])
		{
			if (lastAnimation != this->animations[key])
			{
				if (this->lastAnimation == NULL)
				{
					this->lastAnimation = this->animations[key];
				}
				else
				{
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];
				}

			}
			if (this->animations[key]->play(deltaTime, abs(modifier / modifier_max)))
				// Animation::play() also return bool "done" whenever the animation  
				//is done animating play() will return true to this if statement										 
				//and set the priorityAnimation pointer to NULL											
			{
				this->priorityAnimation = NULL;
			}
		}
	}
	else { // otherwise play animation as usual
		if (priority) // if ther is any  priority animation request to animate ==> set the priorityAnimation to that animation
		{
			this->priorityAnimation = this->animations[key];
		}
		if (lastAnimation != this->animations[key])
		{
			if (this->lastAnimation == NULL)
			{
				this->lastAnimation = this->animations[key];
			}
			else
			{
				this->lastAnimation->reset();
				this->lastAnimation = this->animations[key];
			}

		}

		this->animations[key]->play(deltaTime, abs(modifier / modifier_max));
		//this->lastAnimation->play(deltaTime, abs(modifier / modifier_max));
	}
	return this->animations[key]->isDone();
}


