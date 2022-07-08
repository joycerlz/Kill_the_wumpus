/* @file: game.h
   Header file for class Game

   CSS342 - Spring22
   Professor John Chenault
   Joyce Lee

   This is the main class for the game.
   Holds an array of "rooms" which might have wumpus, bats and pits inside
   The player moves around the rooms with 2 arrows
   If the player enters a room with bats, the bats fly them to another room
   If the player enters a room with pits, they die and lose the game
   If the player enters a room with wumpus, 
   the wumpus might eat them, and in this case they die and lose the game.
   Or the wumpus might wander to another room
   The player has the choice to shoot aroows to adjacent rooms
   If they shoot the wumpus, they win the game
   If they used up all their arrows, they lose the game
*/

#ifndef GAME_H
#define GAME_H

#include "room.h"

class Game {
   public:
      Game(int numB, int numP, int numT);

      void conversation();
      void moveTo(int roomNumber);
      
      void fly(int&);
      bool wumpus();

      void shoot();

   private:
      int curr;  // current room number
      Room rooms[20];
      int numArrows;

      void loadRooms(int t);
      void loadBatsPits(int numB, int numP);

      bool validNeighbor(int n);
      
      void update();
      void outputFeelings();

      int getRandomIn20();
      int getRandomIn3();
      int getRandomIn(int n);
};
#endif