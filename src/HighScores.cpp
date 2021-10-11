#include "HighScores.h"

void HighScores::saveScore(std::string name,unsigned long score)
{
	std::string nameReader[6];
	unsigned long scoreReader[6];
	std::fstream myFile;
	myFile.open("Config/score.txt",std::ios::in);
	std::string input;
	std::string tempstring;
	long tempint,p=1;
	vector<pair<long, string>> listScoreA;
	while (std::getline(myFile,input))
	{
		//std::cout << "Read : " << input.length() << std::endl;
		for (int i = 0; i < input.length(); i++)
		{
			if (input[i] != ' ')
			{
				//std::cout << input[i];
				tempstring += input[i];
			}
			else
			{
				tempstring[i] = '\0';
				tempint = 0;
				p = 1;
				for (int j = input.length() - 1; j >= i + 1; j--)
				{
					tempint += (input[j] - '0') * p;
					p *= 10;
				}
				//std::cout << tempstring << " -- " << tempint << std::endl;
				listScoreA.push_back(make_pair(tempint, tempstring));
				tempstring.clear();
				break;
			}
		}
	}
	myFile.close();

	for (int i = 0; i < 5; i++)
	{
		//std::cout << listScoreA[i].second << " " << listScoreA[i].first << std::endl;
	}
	listScoreA.push_back(std::make_pair(score, std::string(name)));
	std::sort(listScoreA.begin(), listScoreA.end());
	myFile.open("Config/score.txt", std::ios::out);
	for (int i = 5; i >= 1; i--)
	{
		myFile << listScoreA[i].second << " " << listScoreA[i].first << std::endl;
	}
	myFile.close();
	std::cout << "Complete" << std::endl;
	/*scorefile.open("Config/score.txt");
	
	if (this->scorefile.is_open())
	{
		std::cout << " open score file" << std::endl;


		for (int i = 0; i < 5; i++)
		{
			if (scorefile.is_open())
			{

				scorefile >> nameReader[i] >> scoreReader[i];

			}

		}
	}
	else
	{
		std::cout << "fail open score file" << std::endl;
	}
	scorefile.close();

	nameReader[5] = name;
	scoreReader[5] = score;

	for (int i = 0; i < 6;i++) {
		for (int j = 0; j < 6;j++) 
		{
			if (scoreReader[j] > scoreReader[i])
			{
			
				long tempScore = scoreReader[i];
				scoreReader[i] = scoreReader[j];
				scoreReader[j] = tempScore;

				std::string tempName = nameReader[i];
				nameReader[i] = nameReader[j];
				nameReader[j] = tempName;
			}
		}
	}
	std::ofstream writer;
	writer.open("Config/score.txt");

	if (writer.is_open())
	{
		writer << nameReader[0] << " " << scoreReader[0] << std::endl;;
		writer << nameReader[1] << " " << scoreReader[1] << std::endl;;
		writer << nameReader[2] << " " << scoreReader[2] << std::endl;;
		writer << nameReader[3] << " " << scoreReader[3] << std::endl;;
		writer << nameReader[4] << " " << scoreReader[4] << std::endl;;

	}
	writer.close();
	*/

}

void HighScores::renderButton(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target); //render() from button.cpp ==> buttonShape.draw and text.draw
	}

}

void HighScores::initializeButton()
{
	this->buttons["BACK"] = new Button(static_cast<float>(window->getSize().x/2-150), 800.f, 300.f, 100.f,
		&this->font, "BACK", 30,
		sf::Color::Transparent, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color::Black, sf::Color::Black);
}

void HighScores::textModify()
{
	this->nameText[0].setFont(this->font);
	this->nameText[0].setFillColor(sf::Color::Red);
	this->nameText[0].setCharacterSize(30);
	//this->nameText[0].setPosition(500,200);
	this->nameText[0].setPosition(700, 200);
	//this->nameText[0].setPosition(static_cast<float>(window->getPosition().x+window->getSize().x/4),static_cast<float>(window->getPosition().y+window->getSize().y+200));
	this->scoreText[0].setFont(this->font);
	this->scoreText[0].setFillColor(sf::Color::Red);
	this->scoreText[0].setCharacterSize(30);
	//this->nameText[0].setPosition(static_cast<float>(window->getPosition().x + (window->getSize().x / 4)*3), static_cast<float>(window->getPosition().y + window->getSize().y + 200));
	/*this->scoreText[0].setPosition(900, 200);*/
	this->scoreText[0].setPosition(1100, 200);

	this->nameText[1].setFont(this->font);
	this->nameText[1].setFillColor(sf::Color::Blue);
	this->nameText[1].setCharacterSize(30);
	/*this->nameText[1].setPosition(500, 250);*/
	this->nameText[1].setPosition(700, 300);
	this->scoreText[1].setFont(this->font);
	this->scoreText[1].setFillColor(sf::Color::Blue);
	this->scoreText[1].setCharacterSize(30);
	/*this->scoreText[1].setPosition(900, 250);*/
	this->scoreText[1].setPosition(1100, 300);

	this->nameText[2].setFont(this->font);
	this->nameText[2].setFillColor(sf::Color::Yellow);
	this->nameText[2].setCharacterSize(30);
	/*this->nameText[2].setPosition(500, 300);*/
	this->nameText[2].setPosition(700, 400);
	this->scoreText[2].setFont(this->font);
	this->scoreText[2].setFillColor(sf::Color::Yellow);
	this->scoreText[2].setCharacterSize(30);
	//this->scoreText[2].setPosition(900, 300);
	this->scoreText[2].setPosition(1100, 400);

	this->nameText[3].setFont(this->font);
	this->nameText[3].setFillColor(sf::Color::Cyan);
	this->nameText[3].setCharacterSize(30);
	//this->nameText[3].setPosition(500, 350);
	this->nameText[3].setPosition(700, 500);
	this->scoreText[3].setFont(this->font);
	this->scoreText[3].setFillColor(sf::Color::Cyan);
	this->scoreText[3].setCharacterSize(30);
	//this->scoreText[3].setPosition(900, 350);
	this->scoreText[3].setPosition(1100, 500);


	this->nameText[4].setFont(this->font);
	this->nameText[4].setFillColor(sf::Color::Green);
	this->nameText[4].setCharacterSize(30);
	//this->nameText[4].setPosition(500, 400);
	this->nameText[4].setPosition(700, 600);
	this->scoreText[4].setFont(this->font);
	this->scoreText[4].setFillColor(sf::Color::Green);
	this->scoreText[4].setCharacterSize(30);
	//this->scoreText[4].setPosition(900, 400);
	this->scoreText[4].setPosition(1100, 600);

	

	
}

void HighScores::initializeKeybinds()
{
}

void HighScores::updateButton()
{
	for (auto& it : this->buttons) // if there is any iterator remain in the buttons
	{
		it.second->update(this->mousePosWindow); //update() from button.cpp ==> update color of button and button states
	}
	//Start Game
	if (this->buttons["BACK"]->isPressed())
	{
		this->endState();
	}
	
}




HighScores::HighScores(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->backGround.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));
	if (!this->backgroundTexture.loadFromFile("Resources/Images/menu.png"))
		std::cout << "Fail to load background";
	this->backGround.setTexture(&this->backgroundTexture);

	
	this->font.loadFromFile("Font/Cream Peach.ttf");
	textModify();
	initializeButton();
	
	//cout << &this->listScoreA << endl;

}

HighScores::~HighScores()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void HighScores::updateInput(const float& deltaTime)
{
}

void HighScores::update(const float& deltaTime)
{
	std::fstream showScoreBoard;
	showScoreBoard.open("Config/score.txt");
	if (showScoreBoard.is_open())
	{
		std::string name[6];
		std::string score[6];

		showScoreBoard >> name[0] >> score[0];
		showScoreBoard >> name[1] >> score[1];
		showScoreBoard >> name[2] >> score[2];
		showScoreBoard >> name[3] >> score[3];
		showScoreBoard >> name[4] >> score[4];

		this->nameText[0].setString(name[0]);
		this->nameText[1].setString(name[1]);
		this->nameText[2].setString(name[2]);
		this->nameText[3].setString(name[3]);
		this->nameText[4].setString(name[4]);

		this->scoreText[0].setString(score[0]);
		this->scoreText[1].setString(score[1]);
		this->scoreText[2].setString(score[2]);
		this->scoreText[3].setString(score[3]);
		this->scoreText[4].setString(score[4]);
	}
	showScoreBoard.close();

	this->updateMousePosition();
	this->updateButton();

}

void HighScores::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->backGround);
	
	for (int i = 0; i < 5; i++)
	{
		target->draw(this->nameText[i]);
		target->draw(this->scoreText[i]);
	}
	this->renderButton(*target);
	
	

	
	
}
