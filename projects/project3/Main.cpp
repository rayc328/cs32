#include "Board.h"
#include "Side.h"
#include "Player.h"
#include "Game.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
	/*HumanPlayer hp("Marge");
	BadPlayer bp("Homer");
	Board b(3, 8);
	Game g(b, &bp, &hp);
	g.play();*/

	SmartPlayer bruh("SOUTH AI");
	SmartPlayer bp("NORTH AI");
	Board b(6, 4);
	Game g(b, &bp, &bruh);
	g.play();
}