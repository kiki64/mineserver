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

#include "../entity.h"
#include "arrow.h"


EntityArrow::EntityArrow()
{
  createEID();
}

// Skeletons can shoot arrows also, they are not users
// This will have to be fixed.
EntityArrow::EntityArrow(User* user, int8_t ID)
{
  createEID();
  setProjectileID(ID);

  //Intials used for calculations
  intialHeight = user->pos.y;
  intialPitch = user->pos.pitch;
  totalHorizontalDistance = 0;
  intialVelocity = 9000;

  setUser(user->UID);
  inFlight = true;
  ticksInFlight = 0;

  //
  // Below is for position and velocity
  //
  double tempx = ( user->pos.x * 32 );
  double tempy = ( user->pos.y + 1.5f ) * 32;
  double tempz = ( user->pos.z * 32 );
  int distFromUser = 50; // 32 is one whole block away, 50 seems to work while walking

  //userYaw makes the player's yaw between 0-359
  float userYaw = ((int)user->pos.yaw % 360) + (user->pos.yaw - (int)user->pos.yaw);
  if( user->pos.yaw < 0 )
  {
    userYaw += 360;
  }

  if( user->pos.pitch < 0 )
  {
    tempy = ( distFromUser * abs(sin(user->pos.pitch / 90.f))) + (user->pos.y + 1.5f) * 32;
  }
  else if ( user->pos.pitch > 0 )
  {
    tempy = -( distFromUser * abs(sin(user->pos.pitch / 90.f))) + (user->pos.y + 1.5f) * 32;
  }

  if( userYaw != 0 && userYaw != 180 )
  {
    tempx = ( ( -distFromUser * sin(user->pos.yaw * (M_PI / 180.0f) ) ) * cos( user->pos.pitch * (M_PI / 180.0f) ) ) + (user->pos.x * 32);
  }
  if( userYaw != 90 && userYaw != 270 )
  {
    tempz = ( ( distFromUser * cos(user->pos.yaw * (M_PI / 180.0f) ) ) * cos( user->pos.pitch * (M_PI / 180.0f) ) ) + (user->pos.z * 32);
  }

  //vec pos = vec((int)tempx, (int)tempy, (int)tempz);
  setPosition((int)tempx, (int)tempy, (int)tempz, user->pos.map, user->pos.yaw, user->pos.pitch, 0);
  //std::cout << "tempz: " << tempz << ", " << tempz / 32 << std::endl;

  //The 9000 and 14000 are based off of trial and error.  Not calculated to exactly mimic notchian projectile.
  // 9000 might = 1.125 m/s
  // 14000 might = 1.75 m/s
  const int horizontalVelocity = 1.125 * 8000;
  const int verticalVelocity = 1.75 * 8000;

  // Add ability to set velocity based on projectile type
  setVelocity((int)(sin(-(user->pos.yaw / 360.f) * 2.f * M_PI) * cos(user->pos.pitch * (M_PI / 180.0f)) * horizontalVelocity),
              (int)(sinf(-(user->pos.pitch / 90.f)) * verticalVelocity),
              (int)(cos(-(user->pos.yaw / 360.f) * 2.f * M_PI) * cos(user->pos.pitch * (M_PI / 180.0f)) * horizontalVelocity));
}

// TODO: The below code doesn't work correctly. I am not good at physics.
// http://en.wikipedia.org/wiki/Trajectory_of_a_projectile
void EntityArrow::update()
{
  const float gravityConstant = -9.81;

  std::cout << /*"Distance: " << (9000.f / 2700) * ticksInFlight <<*/ "ticks: " << ticksInFlight;
  //std::cout << /*" cos(pitch): " << (int)cos(pos.pitch * (M_PI / 180) ) <<*/ " Displacement in x: " << (int)((9000.f / 540) * cos(pos.pitch * (M_PI / 180.f))) * ((float)getTicksInFlight() / 5.0F) << " Displacement in y: " << (((14000.f / 650) * sin(pos.pitch * (M_PI / 180.f))) * ((float)getTicksInFlight() / 5.0F)) - (0.5 * gravityConstant * pow(((float)getTicksInFlight() / 5.0F),2)) << std::endl;

  if(ticksInFlight == 1)
  {
    //Will be constant as the projectile flys
    displacementX = (int)((9000.f / 540) * cos(pos.pitch * (M_PI / 180.f))) * (ticksInFlight / 5.0F);
  }

  displacementY = (((14000.f / 650) * sin(pos.pitch * (M_PI / 180.f))) * (ticksInFlight / 5.0F)) - (0.5 * gravityConstant * pow((ticksInFlight / 5.0F),2));

  //Just do z+ for now

  pos.z = pos.z + ( displacementX * 32 );
  pos.y = intialHeight - displacementY;

  std::cout << " posX: " << (pos.x / 32 ) << " posY: " << pos.y << " posZ: " << (pos.z / 32) << std::endl;
}

