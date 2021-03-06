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

#include <sstream>
#include "logger.h"

#include "mineserver.h"
#include "map.h"

#include "stair.h"


void BlockStair::onStartedDigging(User* user, int8_t status, int32_t x, int16_t y, int32_t z, int map, int8_t direction)
{

}

void BlockStair::onDigging(User* user, int8_t status, int32_t x, int16_t y, int32_t z, int map, int8_t direction)
{

}

void BlockStair::onStoppedDigging(User* user, int8_t status, int32_t x, int16_t y, int32_t z, int map, int8_t direction)
{

}

bool BlockStair::onBroken(User* user, int8_t status, int32_t x, int16_t y, int32_t z, int map, int8_t direction)
{
  uint8_t block, meta;
  ServerInstance->map(map)->getBlock(x, y, z, &block, &meta);

  ServerInstance->map(map)->setBlock(x, y, z, BLOCK_AIR, 0);
  ServerInstance->map(map)->sendBlockChange(x, y, z, BLOCK_AIR, 0);

  this->spawnBlockItem(x, y, z, map, block, 0);
  return false;
}

void BlockStair::onNeighbourBroken(User* user, int16_t oldblock, int32_t x, int16_t y, int32_t z, int map, int8_t direction)
{
  /* TODO: add code to align stairs? */
}

bool BlockStair::onPlace(User* user, int16_t newblock, int32_t x, int16_t y, int32_t z, int map, int8_t direction, int8_t posx, int8_t posy, int8_t posz)
{
  uint8_t oldblock;
  uint8_t oldmeta;

  if (!ServerInstance->map(map)->getBlock(x, y, z, &oldblock, &oldmeta))
  {
    revertBlock(user, x, y, z, map);
    return true;
  }

  /* Check block below allows blocks placed on top */
  if (!this->isBlockStackable(oldblock))
  {
    revertBlock(user, x, y, z, map);
    return true;
  }

  /* move the x,y,z coords dependent upon placement direction */
  if (!this->translateDirection(&x, &y, &z, map, direction))
  {
    revertBlock(user, x, y, z, map);
    return true;
  }

  if (this->isUserOnBlock(x, y, z, map))
  {
    revertBlock(user, x, y, z, map);
    return true;
  }

  if (!this->isBlockEmpty(x, y, z, map))
  {
    revertBlock(user, x, y, z, map);
    return true;
  }

  int8_t relative_direction = user->relativeToBlock(x, y, z);

  switch(relative_direction)
  {
    case RELATIVE_SOUTH: relative_direction = 2;
      break;
    case RELATIVE_WEST: relative_direction = 1;
      break;
    case RELATIVE_NORTH: relative_direction = 3;
      break;
    case RELATIVE_EAST: relative_direction = 0;
  }

  //set upside down stair
  if( (direction != BLOCK_TOP && posy >= (int8_t)8) || direction == BLOCK_BOTTOM )
    relative_direction ^= 4;

  ServerInstance->map(map)->setBlock(x, y, z, char(newblock), char(relative_direction));
  ServerInstance->map(map)->sendBlockChange(x, y, z, char(newblock), char(relative_direction));

  return false;
}

void BlockStair::onNeighbourPlace(User* user, int16_t newblock, int32_t x, int16_t y, int32_t z, int map, int8_t direction)
{
  /* Align neighbour to this stair */
}

void BlockStair::onReplace(User* user, int16_t newblock, int32_t x, int16_t y, int32_t z, int map, int8_t direction)
{
}
