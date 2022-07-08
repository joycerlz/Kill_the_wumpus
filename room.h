/* @file: room.h
   Header file for class Room

   CSS342 - Spring22
   Professor John Chenault
   Joyce Lee

   This class represents a room element
   It saves the room's number, neighbors and status
   (whether it has bats/pits/wumpus)
*/

#ifndef ROOM_H
#define ROOM_H

#include "bat.h"
#include "wumpus.h"

class Room {

   public: 
      Room();

      // Initialize rooms
      void setRoomNumberNeighbor(int n);
      void setWumpus(bool b);
      void setBats(bool b);
      void setPits(bool b);

      bool hasBats() const;
      bool hasPits() const;
      bool hasWumpus() const;

      int getRoomNumber() const;
      const int* getNeighborList() const;

      void setBatHealth(int n);
      int getBatHealth();

      void setWumpusT(int t);
      int getWumpusT();

      Room& operator = (const Room& rhs);

   private:
      int roomNumber;
      const int* neighbors;

      Bat theBat;
      Wumpus theWumpus;

      bool bats;
      bool pits;
      bool wumpus;

      const int MAPPING[20][3] = {
         {13, 16, 19},  // 0 (room 20)
         {2, 5, 8},     // 1
         {1, 3, 10},    // 2
         {2, 4, 12},    // 3
         {3, 5, 14},    // 4
         {1, 4, 6},     // 5
         {5, 7, 15},    // 6
         {6, 8, 17},    // 7
         {1, 7, 9},     // 8
         {8, 10, 18},   // 9
         {2, 9, 11},    // 10
         {10, 12, 19},  // 11
         {3, 11, 13},   // 12
         {12, 14, 0},   // 13
         {4, 13, 15},   // 14
         {6, 14, 16},   // 15
         {15, 17, 0},   // 16
         {7, 16, 18},   // 17
         {9, 17, 19},   // 18
         {11, 18, 0}    // 19
      };
};
#endif