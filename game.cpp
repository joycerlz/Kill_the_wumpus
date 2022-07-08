/* @file: game.cpp
   Implementation file for class Game

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

#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "game.h"
#include "room.h"

using namespace std;

// Constructors and constructor helpers
Game::Game(int numB, int numP, int numT) : numArrows(2) {
   srand(time(NULL));
   loadRooms(numT);
   loadBatsPits(numB, numP);
   curr = 0;
}

// Helper: initialize room number and neighbors for each room members
// Set the wumpus at a random room
void Game::loadRooms(int t) {
   for (int i = 0; i < 20; i++) {
      rooms[i].setRoomNumberNeighbor(i);
   }

   int temp = getRandomIn20();
   rooms[temp].setWumpus(true);
   rooms[temp].setWumpusT(t);

   cout << "Wumpus originnally set at room " << temp << endl;
}

// Helper: set bats and pits at random rooms based on user input
void Game::loadBatsPits(int numB, int numP) {
   int bTemp = numB;
   int pTemp = numP;

   while (bTemp > 0) {
      int temp = getRandomIn20();

      if (rooms[temp].hasBats()) {  //if the room already has bats, skip
         continue;    
      }

      rooms[temp].setBats(true);
      bTemp--;
   }

    while (pTemp > 0) {
      int temp = getRandomIn20();

      if (rooms[temp].hasPits()) {  //if the room already has bats, skip
         continue;    
      }

      rooms[temp].setPits(true);
      pTemp--;
   }

   // for debugging
   for (int i = 0; i < 20; i++) {
      if (rooms[i].hasBats()) 
         cout << "room " <<i<<" has bats"<<endl;
   }

   for (int i = 0; i < 20; i++) {
      if (rooms[i].hasPits()) 
         cout << "room " <<i<<" has PIts"<<endl;
   }
}

// ---------------------Public functions---------------------
// Main method for the game, each call is a turn
// Chceks if the player still have arrows;
// prompts them to enter choice and takes them to the room
void Game::conversation() {
   if (numArrows == 0) {
      cout << "You have used up all your arrows. You are dead." << endl;
      return;
   }
   
   update();

   if (rooms[curr].hasBats()) {
      fly(curr);
      return;
   }

   if (rooms[curr].hasPits()) {
      cout << "You have fallen into a pit. You are dead." << endl;
      return;
   }

   if (rooms[curr].hasWumpus()) {
      if (wumpus()) return;
   }

   cout << "You are in room " << curr << endl;

   outputFeelings();

   const int* neighbors = rooms[curr].getNeighborList();
   cout << "You may go to Room " << neighbors[0];
   cout << ", Room " << neighbors[1];
   cout << ", Room " << neighbors[2] << endl;

   int choice;
   bool is20 = false;
   cout << "Enter choice: ";
   cin >> choice;

   while (!validNeighbor(choice)) {  //check if the user enters a valid input
      if (choice == 20) {
         shoot();
         is20 = true;
         break;
      }

      cout << "Invalid input, please try again." << endl;
      cin >> choice;
   }
   cout << endl;
   
   if (!is20) moveTo(choice);
}

// Moves the player to another room
void Game::moveTo(int roomNumber) {
   curr = roomNumber;
   conversation();
}

// Shoots an arrow to player's choice
// If the player shoots the wumpus, they win and the game ends
void Game::shoot() {
   numArrows--;
   const int* neighbors = rooms[curr].getNeighborList();

   cout << "What direction do you want to shoot your arrow?" << endl;
   cout << "Enter room number: ";

   int choice;
   cin >> choice;

   if (!(validNeighbor(choice))) {   
      cout << "You entered a non-adjacent room, the arrow is lost." << endl;
      conversation();
      return;
   }

   if (rooms[choice].hasWumpus())
      cout << "You have killed the Wumpus. You Win." << endl;
   else {
      cout << "Wumpus is not in the room." << endl;
      conversation();
   }
}

// The player is taken to another room (selected at random) by the bats
void Game::fly(int& c) {
   int steps = (rooms[c].getBatHealth() % 3) + 1;
   rooms[c].setBatHealth(1);

   for (int i = steps; i > 0; i--) {
      const int* neighbors = rooms[c].getNeighborList();
      int rand = getRandomIn3();

      c = neighbors[rand];
   }

   cout << "A giant bat picks you up and drops you in room " << c <<endl;
   conversation();
}

// Decides if the wumpus eats the player
// returns true if the wumpus eats the player
bool Game::wumpus() {
   int tiredness = rooms[curr].getWumpusT();

   int temp = getRandomIn(tiredness);
   
   if (tiredness == 0 || temp == 0) {
      cout << "The wumpus eats you. You are dead." << endl;
      return true;
   }
   else {
      temp = getRandomIn20();
      rooms[curr].setWumpus(false);
      rooms[temp].setWumpus(true);
      rooms[temp].setWumpusT(tiredness);
      cout << "The wumpus has moved to room " << temp << endl;
      return false;
   }
}

// ---------------------Private functions---------------------
// Prints out hint massage to player about adjacent room conditions
void Game::outputFeelings() {
   const int* neighbors = rooms[curr].getNeighborList();

   // to avoid extra outputs
   bool outputBat = false;
   bool outputPit = false;

   for (int i = 0; i < 3; i++) {
      if (rooms[neighbors[i]].hasBats() && !(outputBat)) {
         cout << "   You hear the wings of a bat fluttering." << endl;
         outputBat = true;
      }

      if (rooms[neighbors[i]].hasPits() && !(outputPit)) {
         cout << "   You feel a cold draft." << endl;
         outputPit = true;
      }

      if (rooms[neighbors[i]].hasWumpus())
         cout << "   You smell a Wumpus nearby." << endl;
   }
}

// For each turn, update bat's health and wumpus's tiredness
void Game::update() {
   for (int i = 0; i < 20; i++) {
      if (rooms[i].hasBats()) {
         rooms[i].setBatHealth(rooms[i].getBatHealth() + 1);
      }

      if (rooms[i].hasWumpus()) {
         rooms[i].setWumpusT(rooms[i].getWumpusT() - 1);
      }
   }
}

// Check if the user enters an adjacent neighbor
bool Game::validNeighbor(int n) {
   const int* neighbors = rooms[curr].getNeighborList();

   for (int i = 0; i < 3; i++) {
      if (n == neighbors[i]) return true;
   }

   return false;
}

// Generate random numbers in different ranges
int Game::getRandomIn20() {
   return rand() % 19 + 1;  // to ensure it's not 0 (leaving room 0 clear)
}

int Game::getRandomIn3() {
   return rand() % 3;
}

int Game::getRandomIn(int n) {
   return rand() % (n + 1);
}