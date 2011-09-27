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

#include "projectile.h"
#include "../mineserver.h"
#include "../map.h"

bool ItemProjectile::affectedItem(int item) const
{
  switch (item)
  {
  case ITEM_SNOWBALL:
  case ITEM_EGG:
  case ITEM_BOW:
    return true;
  }
  return false;
}

void ItemProjectile::onRightClick(User* user, Item* item)
{
  int8_t projID = 0;
  switch (item->getType())
  {
  case ITEM_SNOWBALL:
    projID = OBJECT_PROJECTILE_SNOWBALL;
    break;
  case ITEM_EGG:
    projID = OBJECT_PROJECTILE_EGG;
    break;
  case ITEM_BOW:
    projID = OBJECT_PROJECTILE_ARROW;
    break;
  }

  if(projID != 0)
  {
    if(projID == OBJECT_PROJECTILE_ARROW) // Bow and Arrow
    {
      //TODO: make the below inventory magic numbers into constants
      bool foundArrow = false;
      // Hotbar
      for( int i = 36; i < 45; i++ )
      {
        if( user->inv[i].getType() == ITEM_ARROW )
        {
          foundArrow = true;
          user->inv[i].decCount();
          i = 45;
        }
      }
      //Inventory
      if(foundArrow == false)
      {
        for(int i = 9; i < 36; i++)
        {
          if( user->inv[i].getType() == ITEM_ARROW )
          {
            foundArrow = true;
            user->inv[i].decCount();
            i = 36;
          }
        }
      }
      if(!foundArrow)
        return;
      Mineserver::get()->map(user->pos.map)->sendProjectileSpawn(user, projID);
    }
    else
    {
      item->decCount();
      Mineserver::get()->map(user->pos.map)->sendProjectileSpawn(user, projID);
    }
  }
}