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

#include "entity.h"
#include "../mineserver.h"

void Entity::update()
{

}

void Entity::createEID()
{
  EID = Mineserver::get()->generateEID();
}

int32_t Entity::getEID()
{
  return EID;
}

void Entity::setPosition( int32_t x, int32_t y, int32_t z, size_t map, int8_t yaw, int8_t pitch, int8_t roll)
{
  pos.x = x;
  pos.y = y;
  pos.z = z;
  pos.map = map;
  pos.yaw = yaw;
  pos.pitch = pitch;
  pos.roll = roll;
}

void Entity::getPosition( int32_t &x, int32_t &y, int32_t &z, size_t &map, int8_t &yaw, int8_t &pitch, int8_t &roll)
{
  x = pos.x;
  y = pos.y;
  z = pos.z;
  map = pos.map;
  yaw = pos.yaw;
  pitch = pos.pitch;
  roll = pos.roll;
}

void Entity::setVelocity( int16_t x, int16_t y, int16_t z )
{
  vel.x = x;
  vel.y = y;
  vel.z = z;
}

void Entity::getVelocity( int16_t &x, int16_t &y, int16_t &z )
{
  x = vel.x;
  y = vel.z;
  z = vel.z;
}