/* @file: wumpus.cpp
   Implementation file for class Wumpus

   CSS342 - Spring22
   Professor John Chenault
   Joyce Lee

   This class is for the wumpus
   It has the tiredness variable
*/

#include "wumpus.h"

Wumpus::Wumpus() {
   tiredness = 0;
}

int Wumpus::getTiredness() {
   return tiredness;
}

void Wumpus::setTiredness(int t) {
   if (t >= 0) tiredness = t;  //tiredness should not be less than 0
}