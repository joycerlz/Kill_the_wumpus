/* @file: testDriver.cpp
   Test Driver for homework05 - Wumpus

   CSS342 - Spring22
   Professor John Chenault
   Joyce Lee

   Driver class for the wumpus game.
*/

#include <iostream>
#include "game.h"
#include "room.h"

using namespace std;

int main(int argc, char** argv) {
   if (argc != 4) {
      cout << "Incorrect number of parameters." << endl;
      cout << "Provide <NumBats>, <NumPits>, <Wumpus Tiredness>." << endl;

      return -1;
   }

   int bat = stoi(argv[1]);
   int pit = stoi(argv[2]);
   int wump = stoi(argv[3]);

   if (bat < 0 || pit < 0 || wump < 0) {
      cout << "Invalid input, make sure all arguments are greater than 0." << endl;

      return -1;
   }

   if (bat > 19 || pit > 19) {
      cout << "Invalid input, Bats or Pits may not be greater than 19." << endl;

      return -1;
   }

   // cout << "first: " << stoi(argv[1]) << endl;
   // cout << "second: " << stoi(argv[2]) << endl;
   // cout << "third: " << stoi(argv[3]) << endl;

   Game g(bat, pit, wump);
   g.conversation();

   return 0;
}