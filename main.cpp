#include<SFML/Graphics.hpp>
#include<iostream>
#include<vector>

#include "board.h"
#include "pieces.h"
using namespace std;
void main() {
	int windowSize = 800;
	sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "Chess", sf::Style::Close | sf::Style::Resize);

	vector<sf::Texture*> vec;
	// PAWNS
	sf::Texture bp; bp.loadFromFile("pieces/bp.png");
	for (int i = 0; i < 8; i++) {
		sf::Texture* dummy = &bp;
		vec.push_back(dummy);
	}
	sf::Texture wp; wp.loadFromFile("pieces/wp.png");
	for (int i = 0; i < 8; i++) {
		sf::Texture* dummy = &wp;
		vec.push_back(dummy);
	}
	// ROOKS
	sf::Texture br; br.loadFromFile("pieces/br.png");
	for (int i = 0; i < 2; i++) {
		sf::Texture* dummy = &br;
		vec.push_back(dummy);
	}
	sf::Texture wr; wr.loadFromFile("pieces/wr.png");
	for (int i = 0; i < 2; i++) {
		sf::Texture* dummy = &wr;
		vec.push_back(dummy);
	}
	// KNIGHTS
	sf::Texture bg;
	bg.loadFromFile("pieces/bg.png");
	for (int i = 0; i < 2; i++) {
		sf::Texture* dummy = &bg;
		vec.push_back(dummy);
	}
	sf::Texture wg; wg.loadFromFile("pieces/wg.png");
	for (int i = 0; i < 2; i++) {
		sf::Texture* dummy = &wg;
		vec.push_back(dummy);
	}
	// BISHOPS
	sf::Texture bb; bb.loadFromFile("pieces/bb.png");
	for (int i = 0; i < 2; i++) {
		sf::Texture* dummy = &bb;
		vec.push_back(dummy);
	}
	sf::Texture wb; wb.loadFromFile("pieces/wb.png");
	for (int i = 0; i < 2; i++) {
		sf::Texture* dummy = &wb;
		vec.push_back(dummy);
	}
	// QUEENS
	sf::Texture bq; bq.loadFromFile("pieces/bq.png");
	sf::Texture* dummy = &bq;
	vec.push_back(dummy);

	sf::Texture wq; wq.loadFromFile("pieces/wq.png");
	dummy = &wq;
	vec.push_back(dummy);

	//KINGS
	sf::Texture bk; bk.loadFromFile("pieces/bk.png");
	dummy = &bk;
	vec.push_back(dummy);

	sf::Texture wk; wk.loadFromFile("pieces/wk.png");
	dummy = &wk;
	vec.push_back(dummy);
	
	// BOARD
	sf::Texture boardTexture;
	boardTexture.loadFromFile("board.png");
	
	pieces pc(&boardTexture,vec, windowSize);
	while (window.isOpen()) {
		sf::Event e;
		while (window.pollEvent(e)) {
			if (e.type == e.Closed) {
				window.close();
			}
		}
		window.clear();
		pc.move(window);
	}
}
