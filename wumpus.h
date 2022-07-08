/* @file: wumpus.h
   Header file for class Wumpus

   CSS342 - Spring22
   Professor John Chenault
   Joyce Lee

   This class is for the wumpus
   It has the tiredness variable
*/

#ifndef WUMPUS_H
#define WUMPUS_H

class Wumpus {
   public:
      Wumpus();

      int getTiredness();
      void setTiredness(int t);

   private:
      int tiredness;
};
#endif