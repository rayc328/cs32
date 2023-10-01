#ifndef GAME_H
#define GAME_H

#include <iostream>

using namespace std; 

class Arena;

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nRabbits);
    ~Game();

    // Mutators
    void play();

private:
    Arena* m_arena;

    // Helper functions
    string takePlayerTurn();
};

int computeDanger(const Arena& a, int r, int c);
bool recommendMove(const Arena& a, int r, int c, int& bestDir); //auxillary function only used by Game object 
bool decodeDirection(char ch, int& dir); 

#endif 