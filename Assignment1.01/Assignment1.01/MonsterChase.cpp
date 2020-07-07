
#include "SFML/Graphics.hpp"

#include "../DarkNinjaEngine/HeaderFiles/Engine/DarkNinjaEngine.h"
#include <stdio.h>
#include "SmartPointer.h"
#include "../nlohmann/json.hpp"
#include "../DarkNinjaEngine/HeaderFiles/Engine/Utility/Helper.h"


#include <fstream>
#include <iostream>
#include <cassert>
#include "Shared/LoadFileToBuffer.h"
#include "Math/Mat4.h"


LRESULT CALLBACK onEvent(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		// Quit when we close the main window
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}

	default:
		break;
	}

	return DefWindowProc(handle, message, wParam, lParam);
}

void AddToList(std::vector<Entity*> *List, Entity* I_Entity);
void PlayerBulletHitCheck( int &Out_score);
void SpawnEnemy(std::vector<Entity*>* Out_List,float CurrentTime);
void EnemyHitCheck(std::vector<Entity*>* Out_List, bool &GameControl);

//List for storing Bullets;
std::vector<Entity*> _BulletCloneListPlayer;
//List for storing enemies;
std::vector<Entity*> _EnemyList;

INT WINAPI wWinMain(HINSTANCE instance, HINSTANCE, LPWSTR, int)
{
	std::ostringstream osstr,gameoverstr;
	sf::Font font;
	if (!font.loadFromFile("data/sansation.ttf"))
		return EXIT_FAILURE;
	sf::Clock clock;
	sf::Text hudText;
	hudText.setFont(font);
	hudText.setCharacterSize(14);
	hudText.setFillColor(sf::Color::White);
	hudText.setOutlineColor(sf::Color::Black);
	hudText.setOutlineThickness(2.0f);
	hudText.setPosition(5.0f, 5.0f);

	sf::Text gameOverText;
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(14);
	gameOverText.setFillColor(sf::Color::Red);
	gameOverText.setOutlineColor(sf::Color::Black);
	gameOverText.setOutlineThickness(2.0f);
	gameOverText.setPosition(300,500);
	
	sf::RenderWindow window(sf::VideoMode(800, 1000), "Space Shooter");
	Engine::Init(&window);
	int score=0;
	bool EndGame = false;

	//Entity test("test");
	
	Entity* player = EntityManagerMain.FindGameObjectByTag("Player");
	if(player)
	{
		player->SetGameObjectTag("Player");
	}
	else
	{
		std::cout << "Player is missing";
		system("pause");
	}


	


	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
			{

				Engine::ShutDown();
				window.close();
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Space && EndGame == false)
				{
					static float i = clock.getElapsedTime().asSeconds();
					if (clock.getElapsedTime().asSeconds() > i + 0)
					{

						PrintToOutput("pressed");
						Entity* Temp = Engine::Instantiate("data\\Bullet.json");
						vector3D::vector3D spawnloction = vector3D::vector3D(player->GetComponent<Position>()->getPosition());
						Temp->GetComponent<Position>()->setPosition(vector3D::vector3D(spawnloction.x + 50, spawnloction.y - 50, spawnloction.z));
						//Tag the bullets;
						Temp->SetGameObjectTag("PlayerBullet");
						//Bullet Speed
						Temp->GetComponent<RigidBody2D>()->setVelocity(vector3D::vector3D::Up() * 5);
						//Auto Destroys after 5 Seconds
						Temp->Destroy(5);
						AddToList(&_BulletCloneListPlayer, Temp);
						i = clock.getElapsedTime().asSeconds();
					}


				}

			}
		}

		// clear the window with black color

		window.clear(sf::Color::Black);


		if(!EndGame)
	{

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			player->GetComponent<RigidBody2D>()->AddForce(vector3D::vector3D::Down());
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{

			player->GetComponent<RigidBody2D>()->AddForce(vector3D::vector3D::Up());
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			player->GetComponent<RigidBody2D>()->AddForce(vector3D::vector3D::Left());
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			player->GetComponent<RigidBody2D>()->AddForce(vector3D::vector3D::Right());
		}
	}
		window.clear();
	
		
		
		osstr.str("");
		osstr << "Score: "  << score;
		hudText.setString(osstr.str());
		Engine::Run();
		window.draw(hudText);


		if(!EndGame)
		{

			PlayerBulletHitCheck(score);

			SpawnEnemy(&_EnemyList, clock.getElapsedTime().asSeconds());


			EnemyHitCheck(&_EnemyList, EndGame);
		}
		else
		{
			gameoverstr.str("");
			gameoverstr << "GameOver!!!!";
			gameOverText.setString(gameoverstr.str());
			gameOverText.setScale(3, 3);
			window.draw(gameOverText);
		}


		// end the current frame
		window.display();


	}

}



void AddToList(std::vector<Entity*> *List, Entity* I_Entity)
{
	List->push_back(I_Entity);
	
	
}

void PlayerBulletHitCheck(int &Out_score)
{

	for (int i=0; i < _BulletCloneListPlayer.size();i++)
	{

		if (_BulletCloneListPlayer[i]->GetComponent<BoxCollider>()->GetOtherEntity())
		{
			if (_BulletCloneListPlayer[i]->GetComponent<BoxCollider>()->GetOtherEntity()->GetGameObjectTag() == "smallEnemy")
			{
				Out_score++;
				_BulletCloneListPlayer[i]->GetComponent<BoxCollider>()->GetOtherEntity()->Destroy();
				_BulletCloneListPlayer[i]->Destroy();
				_BulletCloneListPlayer.erase(_BulletCloneListPlayer.begin() + i);
			}

		}



	}
	
	
	
			
	
}

void SpawnEnemy(std::vector<Entity*>* Out_List,float CurrentTime)
{

	static float i = CurrentTime;
	if(Out_List->size() ==0)
	{
		Entity* Temp = Engine::Instantiate("data\\Enemy.json");
		Temp->SetGameObjectTag("smallEnemy");
		vector3D::vector3D spawnloction = vector3D::vector3D(Temp->GetComponent<Position>()->getPosition());
		Temp->GetComponent<Position>()->setPosition(vector3D::vector3D(spawnloction.x + rand() % 100, spawnloction.y, spawnloction.z));
		Temp->GetComponent<RigidBody2D>()->setDrag(0);
		Temp->GetComponent<RigidBody2D>()->setVelocity(vector3D::vector3D::Down());
		Temp->Destroy(10);
		Out_List->push_back(Temp);
	}
	if (CurrentTime > i + 2 )
	{

		Entity* Temp = Engine::Instantiate("data\\Enemy.json");
		Temp->SetGameObjectTag("smallEnemy");
		vector3D::vector3D spawnloction = vector3D::vector3D(Temp->GetComponent<Position>()->getPosition());
		Temp->GetComponent<Position>()->setPosition(vector3D::vector3D(spawnloction.x + (rand()%300 - 300), spawnloction.y , spawnloction.z));
		Temp->GetComponent<RigidBody2D>()->setDrag(0);
		Temp->GetComponent<RigidBody2D>()->setVelocity(vector3D::vector3D::Down());
		Temp->Destroy(10);
		Out_List->push_back(Temp);
		i = CurrentTime;
	}
}

void EnemyHitCheck(std::vector<Entity*>* Out_List,bool& GameControl)
{

	for (auto& element : *Out_List)
	{
	
		if (element->GetComponent<BoxCollider>()->GetOtherEntity())
		{
			if (element->GetComponent<BoxCollider>()->GetOtherEntity()->GetGameObjectTag() == "Player")
			{
				//system("PAUSE");
				//element->GetComponent<BoxCollider>()->GetOtherEntity()->Destroy();
				GameControl = true;

			}
		}



	}

}



#ifdef glib
int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{




	// IMPORTANT: first we need to initialize GLib
	GLib::Initialize(i_hInstance, i_nCmdShow, "MonsterChase", -1, 1000, 1000);



	{
		////Engine::CreateGameObjects();
		//EntityManager EntityManagerMain;

		//Engine::vector4D row0(
		//	1, 2, 3, 4
		//);
		//Engine::vector4D row1(
		//	5,6,7,8
		//);
		//Engine::vector4D row2(
		//	9,10,11,12
		//);
		//Engine::vector4D row3(
		//	13,14,15,16
		//);
		//
		//Engine::Maths::mat4 sample(
		//		 row0,
		//		 row1,
		//		 row2,
		//		 row3


		//);
		//Engine::Maths::mat4 sample1(
		//	row0*10,
		//	row1*10,
		//	row2*10,
		//	row3*10


		//);
		//

		//sample.multiply(sample1);
	}








	Engine::Init();

	bool bQuit = false;


	float timeTest = Engine::Time::CalculateTime();



	Entity* player = EntityManagerMain.FindGameObjectByTag("Joe");
	if (player != nullptr)
	{
		//PrintToOutput("Player found" <<player->GetComponent<RigidBody2D>()->getMass());

	}
	else
	{
		PrintToOutput("Player not found");
	}
	Entity* EnemyTest = EntityManagerMain.FindGameObjectByTag("Enemy1");
	if (EnemyTest == nullptr)
	{


		PrintToOutput("Error");

	}



	do
	{

		GLib::Service(bQuit);
		bQuit = Engine::Input::QuitRequested();


		if (Engine::Input::GetKey(87))
		{
			static int i = 0;
			i++;
			PrintToOutput(i);
			if (player)
				player->GetComponent<RigidBody2D>()->AddForce(vector3D::vector3D::Up() * 5);
			if (EnemyTest != nullptr)
			{

				EnemyTest->IsActive(true);

			}
		}


		if (Engine::Input::GetKeyDown(71))
		{
			if (EnemyTest != nullptr)
			{

				EnemyTest->IsActive(false);

			}
		}
		if (Engine::Input::GetKey(69))
		{
			static int i = 0;

			if (i == 0)
			{
				Entity* NewEnemy = Engine::Instantiate("data\\Enemy.json");


				NewEnemy->AttachComponent(new BoxCollider());
			}
			i++;


		}






		/*if(Engine::Input::GetKey(69))
		{
			static int i = 0;

			if(i==0)
			{
				Entity* NewEnemy = Engine::Instantiate("data\\Enemy.json");


				NewEnemy->AttachComponent(new BoxCollider());
			}
			i++;


		}*/
		if (Engine::Input::GetKey(70))
		{
			if (player)
				player->GetComponent<Position>()->addRotation(0.001);
		}


		if (Engine::Input::GetKey(83))
		{
			if (player)
				player->GetComponent<RigidBody2D>()->AddForce(vector3D::vector3D::Down() * 5);


		}
		if (Engine::Input::GetKey(68))
		{
			/*location.x += 1;
			player->GetComponent<Position>()->setPosition(location);*/
			if (player)
				player->GetComponent<RigidBody2D>()->AddForce(vector3D::vector3D::Right() * 5);
		}
		if (Engine::Input::GetKey(65))
		{
			if (player)
				player->GetComponent<RigidBody2D>()->AddForce(vector3D::vector3D::Left() * 5);
		}

		if (!bQuit)
		{
			Engine::Run();
		}
	} while (bQuit == false);

	PrintToOutput("hello");






#if defined _DEBUG
	_CrtDumpMemoryLeaks();
#endif // _DEBUG
}
//	while (1)
//	{
//
//		//Add the input here
//		Engine::Run();
//	
//		Entity* EnemyTest = EntityManagerMain.FindGameObjectByTag("Enemy1");
//		if (EnemyTest != nullptr)
//		{
//			
//		
//			
//		}
//		else
//		{
//			PrintToOutput("Error");
//		}
//		Entity* player = EntityManagerMain.FindGameObjectByTag("Joe");
//		if (player != nullptr)
//		{
//			//PrintToOutput("Player found");
//			if (player->GetComponent<BoxCollider>())
//			{
//
//			}
//			else
//			{
//
//				player->AttachComponent(new BoxCollider());
//			}
//
//		}
//		else
//		{
//			PrintToOutput("Player not found");
//		}
//		
//		bool bQuit = false;
//		bool test = Engine::Input::QuitRequested();
//
//	
//		float timeTest = Engine::Time::CalculateTime();
//		// IMPORTANT: We need to let GLib do it's thing.
//	
//		GLib::Service(bQuit);
//		test = Engine::Input::QuitRequested();
//		int keypressed = Engine::Input::KeyPressed();
//
//		//E Key
//
//		
//		
//		if(Engine::Input::GetKey(69))
//		{
//			static int i = 0;
//			
//			if(i==0)
//			{
//				Entity* NewEnemy = Engine::Instantiate("data\\Enemy.json");
//				
//				
//				NewEnemy->AttachComponent(new BoxCollider());
//			}
//			i++;
//			
//			
//		}
//		if (Engine::Input::GetKey(70))
//		{
//			if (player)
//				player->GetComponent<Position>()->addRotation(0.001);
//		}
//		if (Engine::Input::GetKey(87))
//		{
//			
//			if(player)
//				player->GetComponent<RigidBody2D>()->AddForce(vector3D::vector3D::Up());
//		}
//		
//		if(Engine::Input::GetKey(83))
//		{
//			if (player)
//			player->GetComponent<RigidBody2D>()->AddForce(vector3D::vector3D::Down() );
//	
//			
//		}
//		if (Engine::Input::GetKey(68))
//		{
//			/*location.x += 1;
//			player->GetComponent<Position>()->setPosition(location);*/
//			if (player)
//			player->GetComponent<RigidBody2D>()->AddForce(vector3D::vector3D::Right());
//		}
//		if (Engine::Input::GetKey(65))
//		{
//			if (player)
//			player->GetComponent<RigidBody2D>()->AddForce(vector3D::vector3D::Left());
//		}
//		if(keypressed ==0)
//		{
//			if (player)
//			player->GetComponent<RigidBody2D>()->AddForce(vector3D::vector3D::Zero());
//		}
//		//
//		if (test)
//		{
//			Engine::ShutDown();
//			PrintToOutput("Shuting Down");
//			GLib::Shutdown();
//			break;
//		}
//
//		
//	}
//
//	
//#if defined _DEBUG
//	_CrtDumpMemoryLeaks();
//#endif // _DEBUG

#endif 




