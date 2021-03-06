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

/*
Here is where we explain what a entity at it's most basic form is.
There will be children of this class that will define more in detail what they are.
Source: (http://www.minecraftwiki.net/wiki/Entity)
*/
#ifndef _ENTITY_H
#define _ENTITY_H

#include "../include/constants.h"

struct entityPosition
{
  int32_t x;
  int32_t y;
  int32_t z;
  size_t map;
  int8_t yaw;
  int8_t pitch;
  int8_t roll;
};
struct velocity
{
  int16_t x;
  int16_t y;
  int16_t z;
};

class Entity 
{
public:
  virtual void update();
  void createEID();
  int32_t getEID();
  void setPosition( int32_t x, int32_t y, int32_t z, size_t map, int8_t yaw, int8_t pitch, int8_t roll);
  void getPosition( int32_t &x, int32_t &y, int32_t &z, size_t &map, int8_t &yaw, int8_t &pitch, int8_t &roll);
  void setVelocity( int16_t x, int16_t y, int16_t z );
  void getVelocity( int16_t &x, int16_t &y, int16_t &z );

protected:
  int32_t EID;
  int8_t type;
  entityPosition pos;
  velocity vel;
  int8_t health;
  bool onFire;

};

#endif