#include "pieces.h"
pieces::pieces(sf::Texture* boardTexture,vector<sf::Texture*>textures,float size) {
	//setting up Board
	Board.setSize(sf::Vector2f(size, size));
	size /= 2.0f;
	Board.setOrigin(size, size);
	Board.setPosition(size, size);
	Board.setTexture(boardTexture);
	size *= 2.0f;

	aspct = size/8.0f;
	turn = 1;	//White - 1   Black - 2
	pieceColor.resize(8);
	// pieceColors
	// 0-none  1-white  2-black
	// White - c    Black - C
	for (int i = 0; i < 8; i++) {
		pieceColor[i].resize(8,0);
	}
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 8; i++) {
			if (j < 2)
				pieceColor[j][i] = 2;
			else
				pieceColor[4 + j][i] = 1;
		}
	}
	whites = {8,9,10,11,12,13,14,15,18,19,22,23,26,27,29,31};
	blacks = {0,1,2,3,4,5,6,7,16,17,20,21,24,25,28,30};
	//show();
	sf::RectangleShape dum;
	dum.setSize(sf::Vector2f(aspct, aspct));
	// PAWNS
	for (int i = 0; i < 8; i++) {
		dum.setTexture(textures[i]);
		dum.setPosition((float)i * aspct, aspct);
		piecePosition.push_back(dum.getPosition());
		Pieces.push_back({ dum,'P'});
	}
	for (int i = 0; i < 8; i++) {
		dum.setTexture(textures[i + 8]);
		dum.setPosition((float)i * aspct, 6.0f * aspct);
		piecePosition.push_back(dum.getPosition());
		Pieces.push_back({dum, 'p'});
	}
	// ROOKS
	for (int i = 0; i < 2; i++) {
		dum.setTexture(textures[i + 16]);
		dum.setPosition((float)i * 7.0f* aspct, 0.0f);
		piecePosition.push_back(dum.getPosition());
		Pieces.push_back({ dum,'R' });
	}
	for (int i = 0; i < 2; i++) {
		dum.setTexture(textures[i + 18]);
		dum.setPosition((float)i * 7.0f* aspct, 7.0f * aspct);
		piecePosition.push_back(dum.getPosition());
		Pieces.push_back({ dum,'r' });
	}
	// KNIGHTS
	for (int i = 0; i < 2; i++) {
		dum.setTexture(textures[i + 20]);
		dum.setPosition((float)i * 5.0f*aspct + aspct, 0.0f);
		piecePosition.push_back(dum.getPosition());
		Pieces.push_back({ dum,'G' });
	}
	for (int i = 0; i < 2; i++) {
		dum.setTexture(textures[i + 22]);
		dum.setPosition((float)i * 5.0f * aspct + aspct, 7.0f* aspct);
		piecePosition.push_back(dum.getPosition());
		Pieces.push_back({ dum,'g' });
	}
	// BISHOPS
	for (int i = 0; i < 2; i++) {
		dum.setTexture(textures[i + 24]);
		dum.setPosition((float)i * 3.0f* aspct + 2.0f* aspct, 0.0f);
		piecePosition.push_back(dum.getPosition());
		Pieces.push_back({ dum,'B' });
	}
	for (int i = 0; i < 2; i++) {
		dum.setTexture(textures[i + 26]);
		dum.setPosition((float)i * 3.0f*aspct + 2.0f* aspct, 7.0f * aspct);
		piecePosition.push_back(dum.getPosition());
		Pieces.push_back({ dum,'b' });
	}
	// QUEENS
	dum.setTexture(textures[28]);
	dum.setPosition(3.0f* aspct, 0.0f);
	piecePosition.push_back(dum.getPosition());
	Pieces.push_back({ dum,'Q' });

	dum.setTexture(textures[29]);
	dum.setPosition(3.0f* aspct, 7.0f* aspct);
	piecePosition.push_back(dum.getPosition());
	Pieces.push_back({ dum,'q' });
	
	//KINGS
	dum.setTexture(textures[30]);
	dum.setPosition(4.0f* aspct, 0.0f);
	piecePosition.push_back(dum.getPosition());
	Pieces.push_back({ dum,'K' });
	
	dum.setTexture(textures[31]);
	dum.setPosition(4.0f* aspct, 7.0f* aspct);
	piecePosition.push_back(dum.getPosition());
	Pieces.push_back({ dum,'k' });
}
//checks if two players are at same position and then kills the one who is below 
void pieces::update(int indx) {
	for (int i = 0; i < 32; i++) {
		if (piecePosition[indx] == piecePosition[i] && i != indx) {
			piecePosition[i].x = -aspct;
			piecePosition[i].y = -aspct;
			Pieces[i].first.setPosition(-aspct, -aspct);
		}
	}
}

void pieces::show()
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++)
			if (!pieceColor[i][j]) cout << ". ";
			else
				cout << pieceColor[i][j] << " ";
		cout << "\n";
	}
}

// ************************** MOVE *********************************

void pieces::move(sf::RenderWindow& window) {
	int cnt = 1;
	int indx=-1;
	bool flg = true;
	//if (check()) Draw(window);
	check(3);
	while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		sf::Vector2i position = sf::Mouse::getPosition(window);
		position.x = position.x - position.x % (int)aspct;
		position.y = position.y - position.y % (int)aspct;
		//exception handling : if screen is zoomed and the mouse position goes out of bounds  
		if ((position.x > 720 || position.y > 720) && (position.x < 0 || position.y < 0)) flg = false;
		if (!flg) break;
		if (cnt) {
			//finding if where mouse is pointing there is a piece or its blank
			indx = pieceColor[position.y / aspct][position.x/aspct];
			//error found: when we click on blank indx becomes 0 and in next line it breaks off with the same value
			if (!indx) { indx=-1;  break; } //if the square is blank then break;
			if (indx != turn) { indx=-1; break; }//if the chosen piece's turn is'nt right then break
			//finding the chosen pieces index in the array
			for (int i = 0; i < 32; i++) {
				if (position.x == piecePosition[i].x && position.y == piecePosition[i].y) {
					indx = i;
					break;
				}
			}//index found
			//window.draw(Pieces[32 - turn].first);
			if (Pieces[indx].first.getOutlineColor() != sf::Color::Red) {
				Pieces[indx].first.setOutlineThickness(3);
				Pieces[indx].first.setOutlineColor(sf::Color::Yellow);
			}
			Draw(window);
		}
		//now comes the moving part
		Pieces[indx].first.setPosition(position.x,position.y);
		cnt = 0;
	}
	//now the piece is moved halfly
	//we are gonna check if its a valid move or not
	if (indx >= 0&&flg) {
		//cout << indx << "\n";
		sf::Vector2f from = piecePosition[indx];
		sf::Vector2f to = Pieces[indx].first.getPosition();
		//VALID
		//if the square we moved to is blank
		if (pieceColor[to.y / aspct][to.x / aspct] == 0) {
			if (canMove(indx, to, from)) {
				int d = pieceColor[from.y / aspct][from.x / aspct];
				pieceColor[from.y / aspct][from.x / aspct] = 0;
				pieceColor[to.y / aspct][to.x / aspct] = d;
				
				// if after moving this piece there is check to the king then nullify the move
				if (check(turn)) {
					pieceColor[from.y / aspct][from.x / aspct] = d;
					pieceColor[to.y / aspct][to.x / aspct] = 0;
					goto lbl;
				}
				//else move fully.
				turn = 3 - turn;//Change the turns
				piecePosition[indx] = to;
				cout << "\n"; show();
			}
			else goto lbl;
		}
		//VALID
		//if the square we moved to is of opposite color
		else if (pieceColor[to.y / aspct][to.x / aspct] == 3-pieceColor[from.y / aspct][from.x / aspct]) {
			if (canMove(indx, to, from)) {
				int d = pieceColor[from.y / aspct][from.x / aspct];
				int x = pieceColor[to.y / aspct][to.x / aspct];
				pieceColor[from.y / aspct][from.x / aspct] = 0;
				pieceColor[to.y / aspct][to.x / aspct] = d;

				int k;
				for (int i = 0; i < 32; i++) if (piecePosition[i] == to && i != indx) k = i;
				sf::Vector2f dum = piecePosition[k];
				Pieces[k].first.setPosition(-aspct, -aspct);

				// if after moving this piece there is check to the king then nullify the move
				if (check(turn)) {
					pieceColor[from.y / aspct][from.x / aspct] = d;
					pieceColor[to.y / aspct][to.x / aspct] = x;
					Pieces[k].first.setPosition(dum.x, dum.y);
					goto lbl;
				}

				//else move fully.
				turn = 3 - turn;//Change the turns
				piecePosition[indx] = to;
				//update the color array
				//if their has been killing then move the killed player out of sight
				update(indx);
				cout << "\n"; show();
			}
			else goto lbl;
		}
		//NOT VALID
		//if we try to kill the same kind then nullify the move
		else if (pieceColor[to.y / aspct][to.x / aspct] == pieceColor[from.y / aspct][from.x / aspct]) {
			//revert the position of the piece
			Pieces[indx].first.setPosition(from.x, from.y);
		}
		//NOT VALID
		//in all other cases nullify the move
		else {
			lbl:
			//revert the position of the piece
			Pieces[indx].first.setPosition(from.x, from.y);
		}
		Pieces[indx].first.setOutlineThickness(0);
	}
	Draw(window);
}
void pieces:: Draw(sf::RenderWindow& window) {
	window.draw(Board);
	for (int i = 0; i < 32; i++) {
		window.draw(Pieces[i].first);
	}
	window.display();
}

// ************************** CAN MOVE *********************************

bool pieces::canMove(int indx, sf::Vector2f to, sf::Vector2f from)
{
	//if (1) return true;
	//PAWNS
	if (Pieces[indx].second == 'p' || Pieces[indx].second == 'P') {
		//the can be moving linear 
		if (to.x - from.x == 0) {
			//the Pawn can move linear if he is'nt killing
			if (pieceColor[to.y / aspct][to.x / aspct]) return false;
			//Pawns can only move two or one square
			if (abs(to.y - from.y) / aspct == 1) {
				//if its a black Pawn it should move down
				if (Pieces[indx].second == 'p' && to.y < from.y) return true;
				//if its a white Pawn it should move up
				else if (Pieces[indx].second == 'P' && to.y > from.y) return true;
			}
			//the Pawn can only move two squares if it has'nt moved yet only  
			else if (abs(to.y - from.y) / aspct == 2) {
				//the Pawn can Move only if there is nothing in between 
				if (obstruction(to, from)) return false;
				//if (pieceColor[(to.y + from.y) / (aspct * 2)][(to.x + from.x) / (aspct * 2)]) return false;
				if (from.y == aspct || from.y == aspct * 6) return true;
			}
		}
		//the can be moving diagonally
		else if(abs(to.x-from.x)/aspct==1){
			//the pawn can only move one move diagonally
			if (abs(to.y - from.y) / aspct == 1) {
				//the Pawn can only move diagonal if he is killing something
				if (pieceColor[to.y/aspct][to.x/aspct]) {
					//if its a black Pawn it should move down
					if (Pieces[indx].second == 'p' && to.y < from.y) return true;
					//if its a white Pawn it should move up
					else if (Pieces[indx].second == 'P' && to.y > from.y) return true;
				}
			}
		}
	}//*********
	//ROOKS
	if (Pieces[indx].second == 'r' || Pieces[indx].second == 'R') {
		// the rook can move only vertically or horizontally
		if (to.x == from.x || to.y == from.y) {
			// the rook an move only if their is no obstruction in between
			if (obstruction(to, from)) return false;
			else return true;
		}
	}//*********
	//KNIGHTS
	if (Pieces[indx].second == 'g' || Pieces[indx].second == 'G') {
		sf::Vector2f dif;
		dif.x = abs(to.x - from.x) / aspct;
		dif.y = abs(to.y - from.y) / aspct;
		//the knights 2.5 squares
		if ((dif.x == 2 && dif.y == 1) || (dif.x == 1 && dif.y == 2)) return true;
	}//*********
	//BISHOP
	if (Pieces[indx].second == 'b' || Pieces[indx].second == 'B') {
		if (abs(to.x - from.x) == abs(to.y - from.y)) {
			if (obstruction(to, from)) return false;
			else return true;
		}
	}//*********
	//QUEEN
	if (Pieces[indx].second == 'q' || Pieces[indx].second == 'Q') {
		//the queen can move linear
		if (to.x == from.x || to.y == from.y) {
			if (obstruction(to,from)) return false;
			else return true;
		}
		//or she can move diagonally
		if (abs(to.x - from.x) == abs(to.y - from.y)) {
			if (obstruction(to, from)) return false;
			else return true;
		}
	}//*********
	//KING
	if (Pieces[indx].second == 'k' || Pieces[indx].second == 'K') {
		if (abs(to.x - from.x)/aspct <= 1 && abs(to.y - from.y)/aspct <=1) return true;
	}//*********
	return false;
}

// ************************** OBSTRUCTION *********************************

bool pieces::obstruction(sf::Vector2f to, sf::Vector2f from) {
	sf::Vector2f dif,trvl;
	dif.x = abs(to.x - from.x)/aspct;
	dif.y = abs(to.y - from.y)/aspct;
	trvl = from;
	//if its a knight moving then obstruction dont matter
	//if ((dif.x == 2 && dif.y == 1) || (dif.x == 1 && dif.y == 2)) return false;

	//we just want the direction of movement
	if (dif.x) dif.x /= ((to.x - from.x)/aspct);
	if (dif.y) dif.y /= ((to.y - from.y)/aspct);
	//dif.x *= -1;
	//dif.y *= -1;
	bool flg = true;
	//return false;
	//cout << trvl.x/aspct << " " << trvl.y/aspct<<"\n";
	while (trvl.x != to.x || trvl.y != to.y) {
		if (trvl.x > 720 || trvl.y > 720) break;
		if (trvl.x < 0 || trvl.y < 0) break;
		//cout << trvl.x / aspct << " " << trvl.y / aspct << "\n";
		if (trvl.y == from.y && trvl.x == from.x);
		else if (pieceColor[trvl.y / aspct][trvl.x / aspct]) return true;
		trvl.x += (dif.x) * aspct;
		trvl.y += (dif.y) * aspct;
	}
	return false;
}

// ************************** CHECK *********************************

bool pieces::check(int t)
{	//white's turn it is
	bool fflg = false;
	if (t==1||t==3) {
		//31 is white king
		sf::Vector2f to = Pieces[31].first.getPosition();
		if(to.x == -80.0f) return false;
		for (int i = 0; i < 16; i++) {
			sf::Vector2f from = Pieces[blacks[i]].first.getPosition();
			if (canMove(blacks[i], to, from)) {
				//cout <<"Check by" << Pieces[blacks[i]].second<<"\n";
				Pieces[31].first.setOutlineColor(sf::Color::Red);
				fflg = true;
				break;
			}
		}
	}
	if (fflg) Pieces[31].first.setOutlineThickness(4);
	else     Pieces[31].first.setOutlineThickness(0);
	bool sflg = false;
	//black's turn
	if(t==2||t==3) {
		//30 is white king
		sf::Vector2f to = Pieces[30].first.getPosition();
		if (to.x == -80.0f) return false;
		for (int i = 0; i < 16; i++) {
			sf::Vector2f from = Pieces[whites[i]].first.getPosition();
			if (canMove(whites[i], to, from)) {
				//cout <<"Check by" << Pieces[blacks[i]].second<<"\n";
				Pieces[30].first.setOutlineColor(sf::Color::Red);
				sflg = true;
				break;
			}
		}
		if (sflg) Pieces[30].first.setOutlineThickness(4);
		else     Pieces[30].first.setOutlineThickness(0);
	}
	if (turn==3&&(sflg|fflg)) return true;
	if (turn == 1 && fflg) return true;
	if (turn == 2 && sflg ) return true;
	return false;
}
