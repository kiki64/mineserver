/*
   Copyright (c) 2011, The Mineserver Project
   All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
  * Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
  * Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
  * Neither the name of the The Mineserver Project nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _ENTITIES_ARROW_H
#define _ENTITIES_ARROW_H

#include "../../../include/constants.h"
#include "../../../include/user.h"
#include "../entity.h"


class EntityArrow: public Entity
{
public:
  EntityArrow();
  EntityArrow(User* user, int8_t ID);

  void update();
  //bool hasTimedout() { return timeStationary >= projectileTimeout;}
  bool isInFlight() { return inFlight; }
  bool canBeRetrieved() { return true; } //pickedup

  //Setters
  void setProjectileID( int8_t temp ){ projID = temp; }
  void setUser(int32_t whoShotArrow){owner = whoShotArrow;}
  void setInFlight( bool temp ){inFlight = temp;}

  //Getters
  int8_t getProjectileID(){return projID;}
  int32_t getUser(){return owner;}
  int getTicksInFlight(){return ticksInFlight;}
  int getTicksStationary(){return ticksStationary;}

  //Increment ticks
  void incrementTicksInFlight(){ ++ticksInFlight;}
  void incrementTicksStationary(){ ++ticksStationary;}


private:
  int8_t projID;

  float intialHeight;
  int16_t intialVelocity;
  float intialPitch;
  float intialYaw;
  float totalHorizontalDistance;
  
  int displacementX;
  int displacementY;
  int ticksInFlight; //Ticks projectile was in flight - Needed?
  int ticksStationary; // Ticks projectile wasn't moving
  bool inFlight;

  static const int projectileTimeout = 60000; // one minute, milliseconds
  int32_t owner; // EID / UID of thing that shot this arrow.


  //On collision with a mob or another player deals damage, stays stuck in person.
  //inFlight() to see if it is moving, check for colisions.
  //If arrow is shot by player they can retrieve their arrows under certian conditions.
};

#endif