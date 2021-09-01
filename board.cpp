#include "board.h"

board::board(sf::Texture * boardTexture,float size) {
	Board.setSize(sf::Vector2f(size,size));
	size /= 2.0f;
	Board.setOrigin(size, size);
	Board.setPosition(size, size);
	Board.setTexture(boardTexture);
}