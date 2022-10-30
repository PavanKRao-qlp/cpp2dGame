
#include <iostream>
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp";
#include "mini/ini.h"
#include <memory>

void printConfig(mINI::INIStructure& configData);
int main()
{
	/*b2Vec2 gravity(0.0f, -10.0f);
	b2World world(gravity);
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 10.0f);

	b2Body* groundBody = world.CreateBody(&groundBodyDef);
	groundBody->CreateFixture(&groundBox, 0.0f);

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 4.0f);
	b2Body* body = world.CreateBody(&bodyDef);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	body->CreateFixture(&fixtureDef);
	float timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	for (int32 i = 0; i < 60; ++i)
	{
		world.Step(timeStep, velocityIterations, positionIterations);
		b2Vec2 position = body->GetPosition();
		float angle = body->GetAngle();
		printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
	}*/

	sf::Clock cl;
	mINI::INIFile configFile("assets/config/launch.ini");
	mINI::INIStructure configData;
	if (configFile.read(configData))
	{
	//	printConfig(configData);		
	}
	else
	{
		std::cerr << "Failed to read launch config!";
		return 1;
	}

	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}


	std::cout<<"Hello CMake.";
	return 0;
}


void printConfig(mINI::INIStructure& configData)
{
	std::cout << "-----------------------------------\n";
	for (auto const& it : configData)
	{
		auto const& section = it.first;
		auto const& collection = it.second;
		std::cout << "[" << section << "]" << std::endl;
		for (auto const& it2 : collection)
		{
			auto const& key = it2.first;
			auto const& value = it2.second;
			std::cout << key << "=" << value << std::endl;
		}
	}
	std::cout << "-----------------------------------\n";
}
