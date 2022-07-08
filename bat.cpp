/* @file: bat.cpp
   Implementation file for class Bat

   CSS342 - Spring22
   Professor John Chenault
   Joyce Lee

   This is the class for bats
   It has the health variable
*/

#include "bat.h"

Bat::Bat() {
   health = -1;
}

void Bat::setHealth(int h){
   health = h;
}

int Bat::getHealth() {
   return health;
}