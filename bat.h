/* @file: bat.h
   Header file for class Bat

   CSS342 - Spring22
   Professor John Chenault
   Joyce Lee

   This is the class for bats
   It has the health variable
*/

#ifndef BAT_H
#define BAT_H

class Bat {
   public:
      Bat();
      
      void setHealth(int);
      int getHealth();

   private:
      int health;
};
#endif