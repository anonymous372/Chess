#pragma once
#include<SFML/Graphics.hpp>
#include<vector>
#include<iostream>
#include<Windows.h>
using namespace std;
class pieces
{
	float aspct;
	int turn;
	sf::RectangleShape Board;
	vector<vector<int>> pieceColor;
	vector<sf::Vector2f> piecePosition;
	vector<pair<sf::RectangleShape,char>> Pieces;
	vector<int> whites;
	vector<int> blacks;
public:
	pieces(sf::Texture* boardTexture,vector<sf::Texture *>textures,float size);
	void Draw(sf::RenderWindow& window);
	void move(sf::RenderWindow& window);
	void update(int);
	void show();
	bool canMove(int,sf::Vector2f,sf::Vector2f);
	bool obstruction(sf::Vector2f, sf::Vector2f);
	bool check(int);
};

