#include<SFML/Graphics.hpp>
#include<sstream>
#include<SFML/Audio.hpp>
void updateBranches(int);
using namespace sf;
enum class side{LEFT, RIGHT, NONE};
const int NUM_BRANCHES = 6;
side branchPositions[NUM_BRANCHES];
int main()
{
	VideoMode vm(960,540);
	View view(FloatRect(0, 0, 1920, 1080));
	RenderWindow window(vm, "Timber Game!!");
	window.setView(view);
	//VideoMode vm(1920,1080);
	//RenderWindow window(vm, "Timber!!!", Style::Fullscreen);
	//------------------------------------------------------
	Texture textureBackground;
	textureBackground.loadFromFile("https://github.com/Sahoobarsharani/Timber.cpp/blob/main/folder/background.png");
	Sprite spriteBackground;
	spriteBackground.setTexture(textureBackground);
	spriteBackground.setPosition(0,0);
	//-------------------------------------------------------
	Texture textureTree;
	textureTree.loadFromFile("/home/student/2241016517_C++/gpwc/graphics/tree.png");
	Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	spriteTree.setPosition(810,0);
	//-------------------------------------------------------
	Texture textureCloud1;
	textureCloud1.loadFromFile("/home/student/2241016517_C++/gpwc/graphics/cloud.png");
	Sprite spriteCloud1;
	spriteCloud1.setTexture(textureCloud1);
	spriteCloud1.setPosition(0,0);
	//-------------------------------------------------------
	Texture textureCloud2;
	textureCloud2.loadFromFile("/home/student/2241016517_C++/gpwc/graphics/cloud.png");
	Sprite spriteCloud2;
	spriteCloud2.setTexture(textureCloud2);
	spriteCloud2.setPosition(0,250);
	//-------------------------------------------------------
	Texture textureCloud3;
	textureCloud3.loadFromFile("/home/student/2241016517_C++/gpwc/graphics/cloud.png");
	Sprite spriteCloud3;
	spriteCloud3.setTexture(textureCloud3);
	spriteCloud3.setPosition(0,500);
	//-------------------------------------------------------
	Texture textureBranch;
	textureBranch.loadFromFile("/home/student/2241016517_C++/gpwc/graphics/branch.png");
	Sprite spriteBranch[NUM_BRANCHES];
	for (int i = 0; i < NUM_BRANCHES; i++)
	{
		spriteBranch[i].setTexture(textureBranch);
		spriteBranch[i].setPosition(-2000,-2000);
		spriteBranch[i].setOrigin(220,20);
	}
	//-------------------------------------------------------
	Texture textureBee;
	textureBee.loadFromFile("/home/student/2241016517_C++/gpwc/graphics/bee.png");
	Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	spriteBee.setPosition(8,800);
	//-------------------------------------------------------
	Texture textureAxe;
	textureAxe.loadFromFile("/home/student/2241016517_C++/gpwc/graphics/axe.png");
	Sprite spriteAxe;
	spriteAxe.setTexture(textureAxe);
	spriteAxe.setPosition(700,830);
	const float AXE_POSITION_LEFT = 700;
	const float AXE_POSITION_RIGHT = 1075;
	//-------------------------------------------------------
	Texture textureLog;
	textureLog.loadFromFile("/home/student/2241016517_C++/gpwc/graphics/log.png");
	Sprite spriteLog;
	spriteLog.setTexture(textureLog);
	spriteLog.setPosition(810,720);
	bool logActive = false;
	float logSpeedX = 1000;
	float logSpeedY = -1500; 
	//-------------------------------------------------------
	Texture texturePlayer;
	texturePlayer.loadFromFile("/home/student/2241016517_C++/gpwc/graphics/player.png");
	Sprite spritePlayer;
	spritePlayer.setTexture(texturePlayer);
	spritePlayer.setPosition(580,720);
	side playerSide = side::LEFT;
	//-------------------------------------------------------
	Texture textureRip;
	textureRip.loadFromFile("/home/student/2241016517_C++/gpwc/graphics/rip.png");
	Sprite spriteRip;
	spriteRip.setTexture(textureRip);
	spriteRip.setPosition(600,860);
	//-------------------------------------------------------
	Font font;
	font.loadFromFile("/home/student/2241016517_C++/gpwc/font/KOMIKAP_.ttf");
	Text messageText;
	messageText.setFont(font);
	messageText.setString("Enter to Start!!");
	messageText.setCharacterSize(80);
	messageText.setFillColor(Color::White);
	messageText.setPosition(1920/2,1080/2);
	FloatRect rect = messageText.getLocalBounds();
	messageText.setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
	Text scoreText;
	scoreText.setFont(font);
	scoreText.setString("Score = 0");
	scoreText.setCharacterSize(100);
	scoreText.setFillColor(Color::White);
	scoreText.setPosition(20,20);
	//-------------------------------------------------------
	bool beeActive = false;
	float beeSpeed = 0.0f;
	bool cloud1Active = false;
	float cloud1Speed = 0.0f;
	bool cloud2Active = false;
	float cloud2Speed = 0.0f;
	bool cloud3Active = false;
	float cloud3Speed = 0.0f;
	Clock clock;
	bool paused = true;
	int Score = 0;
	bool acceptInput = false;
	//--------------------------------------------------------
	RectangleShape timeBar;
	float timeBarStartWidth = 400;
	float timeBarHeight = 80;
	timeBar.setSize(Vector2f(timeBarStartWidth,timeBarHeight));
	timeBar.setPosition(1920/2.0-timeBarStartWidth/2.0,980);
	timeBar.setFillColor(Color::Red);
	float timeRemaining = 6.0f;
	float timeBarStartWidthPerSec = timeBarStartWidth/timeRemaining;
	//--------------------------------------------------------
	//updateBranches(1);
	//updateBranches(2);
	//updateBranches(3);
	//updateBranches(4);
	//updateBranches(5);
	//--------------------------------------------------------
	//Game Sounds
	//--------------------------------------------------------
	SoundBuffer deathBuffer;
	deathBuffer.loadFromFile("/home/student/2241016517_C++/sound/death.wav");
	Sound death;
	death.setBuffer(deathBuffer);
	//--------------------------------------------------------
	SoundBuffer chopBuffer;
	chopBuffer.loadFromFile("/home/student/2241016517_C++/sound/chop.wav");
	Sound chop;
	chop.setBuffer(chopBuffer);
	//--------------------------------------------------------
	SoundBuffer ootBuffer;
	ootBuffer.loadFromFile("/home/student/2241016517_C++/sound/out_of_time.wav");
	Sound oot;
	oot.setBuffer(ootBuffer);
	//--------------------------------------------------------
	//Game Loop
	while(window.isOpen())
	{
		//------------------------------------------------
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
			if (event.type == Event::KeyReleased && !paused)
			{
				acceptInput = true;
				spriteAxe.setPosition(2000,spriteAxe.getPosition().y);
			}
		}
		//------------------------------------------------
		if(Keyboard::isKeyPressed(Keyboard::Return))
		{
			paused = false;
			Score = 0;
			timeRemaining = 6.0f;
			for (int i=0; i<NUM_BRANCHES; i++)
			{
				branchPositions[i] = side::NONE;
			}
			spritePlayer.setPosition(580,720);
			spriteRip.setPosition(680,2000);
			acceptInput = true;
		}
		//-------------------------------------------------
		if (acceptInput)
		{
			if(Keyboard::isKeyPressed(Keyboard::Right))
			{
				playerSide = side::RIGHT;
				Score = Score + 1;
				timeRemaining = timeRemaining + 0.15 + 2/Score;
				spriteAxe.setPosition(AXE_POSITION_RIGHT, spriteAxe.getPosition().y);
				spritePlayer.setPosition(1200,720);
				updateBranches(Score);
				spriteLog.setPosition(810,720);
				logSpeedX = -5000;
				logActive = true;
				acceptInput = false;
				chop.play();
			}
			//----------------------------------------
			if(Keyboard::isKeyPressed(Keyboard::Left))
			{
				playerSide = side::LEFT;
				Score = Score + 1;
				timeRemaining = timeRemaining + 0.15 + 2/Score;
				spriteAxe.setPosition(AXE_POSITION_LEFT, spriteAxe.getPosition().y);
				spritePlayer.setPosition(580,720);
				updateBranches(Score);
				spriteLog.setPosition(810,720);
				logSpeedX = 5000;
				logActive = true;
				acceptInput = false;
				chop.play();
			}
		}
		//------------------------------------------------
		if(Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		//------------------------------------------------
		if (!paused)
		{
			Time dt = clock.restart();
			timeRemaining = timeRemaining - dt.asSeconds();
			timeBar.setSize(Vector2f(timeBarStartWidthPerSec * timeRemaining,timeBarHeight));
			if (timeRemaining <= 0.0f)
			{
				paused = true;
				messageText.setString("Game over");
				messageText.setPosition(1920/2,1080/2);
				messageText.setCharacterSize(80);
				messageText.setFillColor(Color::White);
				FloatRect rect = messageText.getLocalBounds();
				messageText.setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
				oot.play();
			
			}
			//------------------------------------------------
			if(!beeActive)
			{
				srand((int)time(0));
				beeSpeed = rand()%200+200;
				srand((int)time(0));
				float height = rand()%1350+500;
				spriteBee.setPosition(2000,height);
				beeActive = true;
			}
			else{
				spriteBee.setPosition(spriteBee.getPosition().x - beeSpeed*dt.asSeconds(),spriteBee.getPosition().y);
				if(spriteBee.getPosition().x < -100)
				{
					beeActive = false;
				}
			}
			//------------------------------------------------
			if(!cloud1Active)
			{
				srand((int)time(0)*10);
				cloud1Speed = rand()%200;
				srand((int)time(0)*10);
				float height = rand()%150;
				spriteCloud1.setPosition(-300,height);
				cloud1Active = true;
			}
			else{
				spriteCloud1.setPosition(spriteCloud1.getPosition().x + cloud1Speed*dt.asSeconds(),spriteCloud1.getPosition().y);
				if(spriteCloud1.getPosition().x > 1920)
				{
					cloud1Active = false;
				}
			}
			//------------------------------------------------
			if(!cloud2Active)
			{
				srand((int)time(0)*20);
				cloud2Speed = rand()%300;
				srand((int)time(0)*20);
				float height = rand()%300-150;
				spriteCloud2.setPosition(-300,height);
				cloud2Active = true;
			}
			else{
				spriteCloud2.setPosition(spriteCloud2.getPosition().x + cloud2Speed*dt.asSeconds(),spriteCloud2.getPosition().y);
				if(spriteCloud2.getPosition().x > 1920)
				{
					cloud2Active = false;
				}
			}
			//------------------------------------------------
			if(!cloud3Active)
			{
				srand((int)time(0)*30);
				cloud3Speed = rand()%400;
				srand((int)time(0)*30);
				float height = rand()%300-150;
				spriteCloud3.setPosition(-200,height);
				cloud3Active = true;
			}
			else{
				spriteCloud3.setPosition(spriteCloud3.getPosition().x + cloud3Speed*dt.asSeconds(),spriteCloud3.getPosition().y);
				if(spriteCloud3.getPosition().x > 1920)
				{
					cloud3Active = false;
				}
			}
			//---------------------------------------------
			//Update score
			std::stringstream ss;
			ss<<"Score = "<<Score;
			scoreText.setString(ss.str());
			//Score = Score + 1;
			//Update Branches
			for (int i=0; i < NUM_BRANCHES; i++)
			{
				float height = i * 150;
				if (branchPositions[i] == side::LEFT)
				{
					spriteBranch[i].setPosition(610,height);
					spriteBranch[i].setRotation(180);
				}
				else if (branchPositions[i] == side::RIGHT)
				{
					spriteBranch[i].setPosition(1330,height);
					spriteBranch[i].setRotation(0);
				}
				else
				{
					spriteBranch[i].setPosition(3000,height);
				}
			}
			//Moving Log
			if (logActive)
			{
				spriteLog.setPosition(spriteLog.getPosition().x + logSpeedX * dt.asSeconds(),spriteLog.getPosition().y + logSpeedY * dt.asSeconds());
				if(spriteLog.getPosition().x > 2000 || spriteLog.getPosition().x < 100)
				{
					logActive = false;
					spriteLog.setPosition(800,600);
				}
			}
			//Handle Player's Death
			if (branchPositions[5] == playerSide)
			{
				paused = true;
				acceptInput = false;
				//hide the player
				spritePlayer.setPosition(2000,720);
				//draw rip
				spriteRip.setPosition(525,760);
				//display the message text
				messageText.setString("SQUISHED!!");
				messageText.setPosition(1920/2,1080/2);
				messageText.setCharacterSize(80);
				messageText.setFillColor(Color::White);
				FloatRect rect = messageText.getLocalBounds();
				messageText.setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
				death.play();
			}
		}
		//---------------------------------------------
		window.clear();
		window.draw(spriteBackground);
		window.draw(spriteCloud1);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3);
		window.draw(spriteTree);
		window.draw(spriteBee);
		if (paused)
		{
			window.draw(messageText);
		}
		window.draw(scoreText);
		window.draw(timeBar);
		for(int i=0;i<NUM_BRANCHES;i++)
		{
     			window.draw(spriteBranch[i]);
     		}
     		window.draw(spriteAxe);
     		window.draw(spriteLog);
     		window.draw(spritePlayer);
     		window.draw(spriteRip);
		window.display();
	}
	return 0;
}
void updateBranches(int seed)
{
	for(int j = NUM_BRANCHES-1;j>0;j--)
	{
		branchPositions[j] = branchPositions[j-1];
		srand((int)time(0)+seed);
		int r = rand()%5;
		switch(r)
		{
			case 0:
				branchPositions[0] = side::LEFT;
				break;
			case 1:
				branchPositions[0] = side::RIGHT;
				break;
			default:
				branchPositions[0] = side::NONE;
		}
	}
}
