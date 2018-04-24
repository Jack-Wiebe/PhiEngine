#include "InputManager.h"

InputManager::InputManager()
{
}

void InputManager::Update(sf::RenderWindow* _mainWindow, GameObject* _user, GameObject* _user2, sf::Clock* clock)
{

	//std::cout << "Update" << std::endl;

	sf::Event m_event;
	while (_mainWindow->pollEvent(m_event)) {
		//std::cout << "POLL" << std::endl;
		PhysicsComponent* phyComp = _user->GetComponent<PhysicsComponent>();
		PhysicsComponent* phyComp2 = _user2->GetComponent<PhysicsComponent>();
		if (m_event.type == sf::Event::KeyPressed)
		{
	#pragma region player 1
			//std::cout << "KEY PRESSED" << std::endl;
			if (m_event.key.code == sf::Keyboard::Q)
			{
				
				
				_user->GetTransform()->SetRotation(_user->GetTransform()->GetRotation() + -10 * clock->getElapsedTime().asSeconds());
				

			}
			if(m_event.key.code == sf::Keyboard::E)
			{


				_user->GetTransform()->SetRotation(_user->GetTransform()->GetRotation() + 10 * clock->getElapsedTime().asSeconds());


			}
			if (m_event.key.code == sf::Keyboard::D)
			{
				//std::cout << "Right" << std::endl;
				 //phyComp = NULL;
			//	PhysicsComponent* phyComp = _user->GetComponent<PhysicsComponent>();
				if (phyComp != nullptr) {
					//phyComp->currentVelocity = sf::Vector2f(0, 0);
					phyComp->AddForc(sf::Vector2f(1000, 0));
				}
				//_user->GetTransform()->SetRotation(_user->GetTransform()->GetRotation() + 10 * clock->getElapsedTime().asSeconds());
				//_user->GetTransform()->SetPosition(_user->GetTransform()->GetPosition() + sf::Vector2f(5,0));

			}
			if (m_event.key.code == sf::Keyboard::A)
			{
				//std::cout << "Left" << std::endl;
			//	PhysicsComponent* phyComp = _user->GetComponent<PhysicsComponent>();
				if (phyComp != nullptr) {
					//phyComp->currentVelocity = sf::Vector2f(0, 0);
					phyComp->AddForc(sf::Vector2f(-1000, 0));
				}
				//_user->GetTransform()->SetRotation(_user->GetTransform()->GetRotation() + -10 * clock->getElapsedTime().asSeconds());
				//_user->GetTransform()->SetPosition(_user->GetTransform()->GetPosition() + sf::Vector2f(-5, 0));

			}
			if (m_event.key.code == sf::Keyboard::W)
			{
				std::cout << "Up" << std::endl;
				//PhysicsComponent* phyComp = _user->GetComponent<PhysicsComponent>();
				if (phyComp != nullptr) {
					
					phyComp->AddForc(sf::Vector2f(0, -1000));
				}
				//_user->GetTransform()->SetPosition(_user->GetTransform()->GetPosition() + sf::Vector2f(0, -5));

			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				std::cout << "Down" << std::endl;
				if (phyComp != nullptr) {
					
					phyComp->AddForc(sf::Vector2f(0, 1000));
				}
				//_user->GetTransform()->SetPosition(_user->GetTransform()->GetPosition() + sf::Vector2f(0, 5 )*clock->getElapsedTime().asSeconds());


			}
			//phyComp->currentVelocity = sf::Vector2f(0, 0);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{

				
				phyComp->Stop();

			}
#pragma endregion

#pragma region player 2
				//std::cout << "KEY PRESSED" << std::endl;
				if (m_event.key.code == sf::Keyboard::Q)
				{


					_user2->GetTransform()->SetRotation(_user2->GetTransform()->GetRotation() + -10 * clock->getElapsedTime().asSeconds());


				}
			if (m_event.key.code == sf::Keyboard::E)
			{


				_user2->GetTransform()->SetRotation(_user2->GetTransform()->GetRotation() + 10 * clock->getElapsedTime().asSeconds());


			}
			if (m_event.key.code == sf::Keyboard::Right)
			{
				//std::cout << "Right" << std::endl;
				//phyComp = NULL;
				//	PhysicsComponent* phyComp = _user->GetComponent<PhysicsComponent>();
				if (phyComp2!= nullptr) {
					//phyComp->currentVelocity = sf::Vector2f(0, 0);
					phyComp2->AddForc(sf::Vector2f(1000, 0));
				}
				//_user->GetTransform()->SetRotation(_user->GetTransform()->GetRotation() + 10 * clock->getElapsedTime().asSeconds());
				//_user->GetTransform()->SetPosition(_user->GetTransform()->GetPosition() + sf::Vector2f(5,0));

			}
			if (m_event.key.code == sf::Keyboard::Left)
			{
				//std::cout << "Left" << std::endl;
				//	PhysicsComponent* phyComp = _user->GetComponent<PhysicsComponent>();
				if (phyComp2 != nullptr) {
					//phyComp->currentVelocity = sf::Vector2f(0, 0);
					phyComp2->AddForc(sf::Vector2f(-1000, 0));
				}
				//_user->GetTransform()->SetRotation(_user->GetTransform()->GetRotation() + -10 * clock->getElapsedTime().asSeconds());
				//_user->GetTransform()->SetPosition(_user->GetTransform()->GetPosition() + sf::Vector2f(-5, 0));

			}
			if (m_event.key.code == sf::Keyboard::Up)
			{
				std::cout << "Up" << std::endl;
				//PhysicsComponent* phyComp = _user->GetComponent<PhysicsComponent>();
				if (phyComp2 != nullptr) {

					phyComp2->AddForc(sf::Vector2f(0, -1000));
				}
				//_user->GetTransform()->SetPosition(_user->GetTransform()->GetPosition() + sf::Vector2f(0, -5));

			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				std::cout << "Down" << std::endl;
				if (phyComp2 != nullptr) {

					phyComp2->AddForc(sf::Vector2f(0, 1000));
				}
				//_user->GetTransform()->SetPosition(_user->GetTransform()->GetPosition() + sf::Vector2f(0, 5 )*clock->getElapsedTime().asSeconds());


			}
			//phyComp->currentVelocity = sf::Vector2f(0, 0);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
			{


				phyComp2->Stop();

			}
#pragma endregion
			if (m_event.key.code == sf::Keyboard::P)
			{
				system("pause");

			}
			if (m_event.key.code == sf::Keyboard::Escape)
			{

				_mainWindow->close();
				exit(EXIT_SUCCESS);
			}
		}
		//std::cout << "exit" << std::endl;
	}
}

