/* @file: room.cpp
   Implementation file for class Room

   CSS342 - Spring22
   Professor John Chenault
   Joyce Lee

   This class represents a room element
   It saves the room's number, neighbors and status
   (whether it has bats/pits/wumpus)
*/

#include "room.h"

// Constructor
// Initialize the variables which will be replaced later
Room::Room() {
   roomNumber = 0;
   wumpus = false;
   bats = false;
   pits = false;

   theBat = Bat();
}

// ---------------------Public functions---------------------
// Setters
void Room::setRoomNumberNeighbor(int n) {
   roomNumber = n;
   neighbors = MAPPING[n];
}

void Room::setWumpus(bool b) {
   wumpus = b;
}

void Room::setBats(bool b) {
   bats = b;
   theBat.setHealth(0);
}

void Room::setPits(bool b) {
   pits = b;
}

// Getters
int Room::getRoomNumber() const {
   return roomNumber;
}

const int* Room::getNeighborList() const {
   return neighbors;
}

bool Room::hasBats() const {
   return bats;
}

bool Room::hasPits() const {
   return pits;
}

bool Room::hasWumpus() const {
   return wumpus;
}

// Setters/getters for room members
void Room::setBatHealth(int n) {
   theBat.setHealth(n);
}

int Room::getBatHealth() {
   return theBat.getHealth();
}

void Room::setWumpusT(int t) {
   theWumpus.setTiredness(t);
}

int Room::getWumpusT() {
   return theWumpus.getTiredness();
}

Room& Room::operator = (const Room& rhs) {
   this -> roomNumber = rhs.getRoomNumber();
   this -> neighbors = rhs.getNeighborList();

   return *this;
}