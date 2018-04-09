#include "InputManager.h"

InputManager::InputManager()
{
}

void InputManager::Update(sf::RenderWindow* _mainWindow, GameObject* _user)
{
	
	//std::cout << "Update" << std::endl;

	sf::Event m_event;
	while (_mainWindow->pollEvent(m_event)) {
		std::cout << "POLL" << std::endl;
		if (m_event.type == sf::Event::KeyPressed)
		{
			std::cout << "KEY PRESSED" << std::endl;
			if (m_event.key.code == sf::Keyboard::Right)
			{
				std::cout << "Right" << std::endl;
				 //phyComp = NULL;
				PhysicsComponent* phyComp = _user->GetComponent<PhysicsComponent>();
				if (phyComp != nullptr) {
					phyComp->currentVelocity = sf::Vector2f(0, 0);
					phyComp->AddForc(sf::Vector2f(.1, 0));
				}
			}
			if (m_event.key.code == sf::Keyboard::Left)
			{
				std::cout << "Left" << std::endl;
				PhysicsComponent* phyComp = _user->GetComponent<PhysicsComponent>();
				if (phyComp != nullptr) {
					phyComp->currentVelocity = sf::Vector2f(0, 0);
					phyComp->AddForc(sf::Vector2f(-.1, 0));
				}
			}
			if (m_event.key.code == sf::Keyboard::Up)
			{
				std::cout << "Up" << std::endl;
				PhysicsComponent* phyComp = _user->GetComponent<PhysicsComponent>();
				if (phyComp != nullptr) {
					phyComp->currentVelocity = sf::Vector2f(0, 0);
					phyComp->AddForc(sf::Vector2f(0, -.1));
				}
			}
			if (m_event.key.code == sf::Keyboard::Down)
			{
				std::cout << "Down" << std::endl;
				PhysicsComponent* phyComp = _user->GetComponent<PhysicsComponent>();
				if (phyComp != nullptr) {
					phyComp->currentVelocity = sf::Vector2f(0, 0);
					phyComp->AddForc(sf::Vector2f(0, .1));
				}

			}
			if (m_event.key.code == sf::Keyboard::P)
			{
				system("pause");
			}
		}
		std::cout << "exit" << std::endl;
	}
}