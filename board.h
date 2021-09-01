#pragma once
#include<SFML/Graphics.hpp>
class board
{
	sf::RectangleShape Board;
public:
	board(sf::Texture* boardTexture,float size);
	void Draw(sf::RenderWindow& window) {	
		window.draw(Board);
	}
};

