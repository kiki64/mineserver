/*
   Copyright (c) 2012, The Mineserver Project
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

#include <map>
#include <ctime>

#include "constants.h"
#include "random.h"

std::map<uint8_t, DropPtr> BLOCKDROPS;

// Get the number of items to drop for items that aren't constant
enum {
    RAND_DROP_LAPIS, RAND_DROP_TALL_GRASS, RAND_DROP_HUGE_MUSHROOM, RAND_DROP_REDSTONE,
    RAND_DROP_GLOWSTONE, RAND_DROP_MELON, RAND_DROP_CARROT, RAND_DROP_POTATOES
};
int getDistribution( int type )
{
    srand(time(NULL));
    switch( type )
    {
        case RAND_DROP_LAPIS: return rand() % 8 + 4; // (4-8)
        case RAND_DROP_TALL_GRASS: return rand() % 1; // (0-1)
        case RAND_DROP_HUGE_MUSHROOM: return rand() % 2; // (0-2)
        case RAND_DROP_REDSTONE: return rand() % 5 + 4; // (4-5)
        case RAND_DROP_GLOWSTONE: return rand() % 4 + 2; // (2-4)
        case RAND_DROP_MELON: return rand() % 7 + 3; // (3-7)
        case RAND_DROP_CARROT: return rand() % 4 + 1; // (1-4)
        case RAND_DROP_POTATOES: return rand() % 4 + 1; // (1-4)
        default : return 0;
    }
}

const unsigned int SERVER_CONSOLE_UID = -1;

const std::string VERSION = "0.1.18 (Alpha)";

const int PROTOCOL_VERSION = 39;

const char COMMENTPREFIX  = '#';

// Configuration
const std::string CONFIG_FILE = "config.cfg";

// PID file
const std::string PID_FILE = "mineserver.pid";

//allocate 1 MB for chunk files
const int ALLOCATE_NBTFILE = 1048576;

const int kMaxChatMessageLength = 119;

void initConstants()
{
  // Block drops (10000 = 100%)

  // Sort by block id number and leave white space every 20
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_STONE, DropPtr(new Drop(BLOCK_COBBLESTONE, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_GRASS, DropPtr(new Drop(BLOCK_DIRT, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_DIRT, DropPtr(new Drop(BLOCK_DIRT, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_COBBLESTONE, DropPtr(new Drop(BLOCK_COBBLESTONE, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_PLANK, DropPtr(new Drop(BLOCK_PLANK, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_SAPLING, DropPtr(new Drop(BLOCK_SAPLING, 10000, 1))));
  //BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_BEDROCK, DropPtr( new Drop(BLOCK_BEDROCK, 10000, 1))));
  //BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_WATER, DropPtr( new Drop(BLOCK_WATER, 10000, 1))));
  //BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_STATIONARY_WATER, DropPtr( new Drop(BLOCK_STATIONARY_WATER, 10000, 1))));
  //BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_LAVA, DropPtr( new Drop(BLOCK_LAVA, 10000, 1))));
  //BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_STATIONARY_LAVA, DropPtr( new Drop(BLOCK_STATIONARY_LAVA, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_SAND, DropPtr(new Drop(BLOCK_SAND, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_GRAVEL, DropPtr(new Drop(ITEM_FLINT, 850, 1, 0, DropPtr(new Drop(BLOCK_GRAVEL, 10000, 1))))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_GOLD_ORE, DropPtr(new Drop(BLOCK_GOLD_ORE, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_IRON_ORE, DropPtr(new Drop(BLOCK_IRON_ORE, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_COAL_ORE, DropPtr(new Drop(ITEM_COAL, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_WOOD, DropPtr(new Drop(BLOCK_WOOD, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_LEAVES, DropPtr(new Drop(BLOCK_SAPLING, 1200, 1))));
  //BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_SPONGE, DropPtr( new Drop(BLOCK_SPONGE, 10000, 1))));
  //BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_GLASS, DropPtr( new Drop(BLOCK_GLASS, 10000, 1))));

  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_LAPIS_ORE, DropPtr(new Drop(ITEM_DYE, 10000, getDistribution(RAND_DROP_LAPIS), DYE_LAPIS_LAZULI))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_LAPIS_BLOCK, DropPtr(new Drop(BLOCK_LAPIS_BLOCK, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_DISPENSER, DropPtr( new Drop(BLOCK_DISPENSER, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_SANDSTONE, DropPtr( new Drop(BLOCK_SANDSTONE, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_NOTE_BLOCK, DropPtr( new Drop(BLOCK_NOTE_BLOCK, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_BED, DropPtr( new Drop(ITEM_BED, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_POWERED_RAIL, DropPtr( new Drop(BLOCK_POWERED_RAIL, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_DETECTOR_RAIL, DropPtr( new Drop(BLOCK_DETECTOR_RAIL, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_STICKY_PISTON, DropPtr( new Drop(BLOCK_STICKY_PISTON, 10000, 1))));
  //BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_COBWEB, DropPtr( new Drop(BLOCK_COBWEB, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_TALL_GRASS, DropPtr( new Drop(BLOCK_CROPS, 10000, getDistribution(RAND_DROP_TALL_GRASS)))));
  //BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_DEAD_BUSH, DropPtr( new Drop(BLOCK_DEAD_BUSH, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_PISTON, DropPtr( new Drop(BLOCK_PISTON, 10000, 1))));
  //BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_PISTON_EXTENSION, DropPtr( new Drop(BLOCK_PISTON_EXTENSION, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_WOOL, DropPtr( new Drop(BLOCK_WOOL, 10000, 1))));
  //BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_PISTON_MOVING, DropPtr( new Drop(BLOCK_PISTON_MOVING, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_YELLOW_FLOWER, DropPtr( new Drop(BLOCK_YELLOW_FLOWER, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_RED_ROSE, DropPtr( new Drop(BLOCK_RED_ROSE, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_BROWN_MUSHROOM, DropPtr( new Drop(BLOCK_BROWN_MUSHROOM, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_RED_MUSHROOM, DropPtr( new Drop(BLOCK_RED_MUSHROOM, 10000, 1))));

  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_GOLD_BLOCK, DropPtr( new Drop(BLOCK_GOLD_BLOCK, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_IRON_BLOCK, DropPtr( new Drop(BLOCK_IRON_BLOCK, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_DOUBLE_STEP, DropPtr(new Drop(BLOCK_STEP, 10000, 2))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_STEP, DropPtr( new Drop(BLOCK_STEP, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_BRICK, DropPtr( new Drop(BLOCK_BRICK, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_TNT, DropPtr( new Drop(BLOCK_TNT, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_BOOKSHELF, DropPtr( new Drop(ITEM_BOOK, 10000, 3))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_MOSSY_COBBLESTONE, DropPtr( new Drop(BLOCK_MOSSY_COBBLESTONE, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_OBSIDIAN, DropPtr( new Drop(BLOCK_OBSIDIAN, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_TORCH, DropPtr( new Drop(BLOCK_TORCH, 10000, 1))));
  //BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_FIRE, DropPtr( new Drop(BLOCK_FIRE, 10000, 1))));
  //BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_MOB_SPAWNER, DropPtr( new Drop(BLOCK_MOB_SPAWNER, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_WOODEN_STAIRS, DropPtr( new Drop(BLOCK_WOODEN_STAIRS, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_CHEST, DropPtr( new Drop(BLOCK_CHEST, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_REDSTONE_WIRE, DropPtr( new Drop(ITEM_REDSTONE, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_DIAMOND_ORE, DropPtr( new Drop(ITEM_DIAMOND, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_DIAMOND_BLOCK, DropPtr( new Drop(BLOCK_DIAMOND_BLOCK, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_WORKBENCH, DropPtr( new Drop(BLOCK_WORKBENCH, 10000, 1))));
  //BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_CROPS, DropPtr( new Drop(BLOCK_CROPS, 10000, 1)))); // Can only get seeds from fully grown wheat
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_SOIL, DropPtr( new Drop(BLOCK_DIRT, 10000, 1))));

  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_FURNACE, DropPtr( new Drop(BLOCK_FURNACE, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_BURNING_FURNACE, DropPtr( new Drop(BLOCK_FURNACE, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_SIGN_POST, DropPtr( new Drop(ITEM_SIGN, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_WOODEN_DOOR, DropPtr( new Drop(ITEM_WOODEN_DOOR, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_LADDER, DropPtr( new Drop(BLOCK_LADDER, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_MINECART_TRACKS, DropPtr( new Drop(BLOCK_MINECART_TRACKS, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_COBBLESTONE_STAIRS, DropPtr( new Drop(BLOCK_COBBLESTONE_STAIRS, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_WALL_SIGN, DropPtr( new Drop(ITEM_SIGN, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_LEVER, DropPtr( new Drop(BLOCK_LEVER, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_STONE_PRESSURE_PLATE, DropPtr( new Drop(BLOCK_STONE_PRESSURE_PLATE, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_IRON_DOOR, DropPtr( new Drop(ITEM_IRON_DOOR, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_WOODEN_PRESSURE_PLATE, DropPtr( new Drop(BLOCK_WOODEN_PRESSURE_PLATE, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_REDSTONE_ORE, DropPtr( new Drop(ITEM_REDSTONE, 10000, getDistribution(RAND_DROP_REDSTONE)))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_GLOWING_REDSTONE_ORE, DropPtr( new Drop(ITEM_REDSTONE, 10000, getDistribution(RAND_DROP_REDSTONE)))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_REDSTONE_TORCH_OFF, DropPtr( new Drop(BLOCK_REDSTONE_TORCH_ON, 10000, 1)))); 
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_REDSTONE_TORCH_ON, DropPtr( new Drop(BLOCK_REDSTONE_TORCH_ON, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_STONE_BUTTON, DropPtr( new Drop(BLOCK_STONE_BUTTON, 10000, 1))));
  //BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_SNOW, DropPtr(new Drop(ITEM_SNOWBALL, 10000, 1)))); // TODO: Must be with a shovel to get snowball.
  //BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_ICE, DropPtr( new Drop(BLOCK_ICE, 10000, 1))));

  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_SNOW_BLOCK, DropPtr(new Drop(ITEM_SNOWBALL, 10000, 4))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_CACTUS, DropPtr( new Drop(BLOCK_CACTUS, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_CLAY, DropPtr(new Drop(ITEM_CLAY_BALLS, 10000, 4))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_REED, DropPtr( new Drop(ITEM_REED, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_JUKEBOX, DropPtr( new Drop(BLOCK_JUKEBOX, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_FENCE, DropPtr( new Drop(BLOCK_FENCE, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_PUMPKIN, DropPtr( new Drop(BLOCK_PUMPKIN, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_NETHERRACK, DropPtr( new Drop(BLOCK_NETHERRACK, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_SOUL_SAND, DropPtr( new Drop(BLOCK_SOUL_SAND, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_GLOWSTONE, DropPtr( new Drop(ITEM_GLOWSTONE_DUST, 10000, getDistribution(RAND_DROP_GLOWSTONE)))));
  //BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_PORTAL, DropPtr( new Drop(BLOCK_PORTAL, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_JACK_O_LANTERN, DropPtr( new Drop(BLOCK_JACK_O_LANTERN, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_CAKE, DropPtr( new Drop(BLOCK_CAKE, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_REDSTONE_REPEATER_OFF, DropPtr( new Drop(BLOCK_REDSTONE_REPEATER_OFF, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_REDSTONE_REPEATER_ON, DropPtr( new Drop(BLOCK_REDSTONE_REPEATER_OFF, 10000, 1))));
  //BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_LOCKED_CHEST, DropPtr( new Drop(BLOCK_LOCKED_CHEST, 10000, 1)))); // No longer in the game.
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_TRAPDOOR, DropPtr( new Drop(BLOCK_TRAPDOOR, 10000, 1))));
  //BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_MONSTER_EGG, DropPtr( new Drop(BLOCK_MONSTER_EGG, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_STONE_BRICKS, DropPtr( new Drop(BLOCK_STONE_BRICKS, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_HUGE_BROWN_MUSHROOM, DropPtr( new Drop(BLOCK_BROWN_MUSHROOM, 10000, getDistribution(RAND_DROP_HUGE_MUSHROOM)))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_HUGE_RED_MUSHROOM, DropPtr( new Drop(BLOCK_RED_MUSHROOM, 10000, getDistribution(RAND_DROP_HUGE_MUSHROOM)))));

  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_IRON_BARS, DropPtr( new Drop(BLOCK_IRON_BARS, 10000, 1))));
  //BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_GLASS_PANE, DropPtr( new Drop(BLOCK_GLASS_PANE, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_MELON, DropPtr( new Drop(BLOCK_MELON, 10000, getDistribution(RAND_DROP_MELON)))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_PUMPKIN_STEM, DropPtr( new Drop(BLOCK_PUMPKIN_STEM, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_MELON_STEM, DropPtr( new Drop(BLOCK_MELON_STEM, 10000, 1))));
  //BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_VINES, DropPtr( new Drop(BLOCK_VINES, 10000, 1)))); // Need a shears to collect
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_FENCE_GATE, DropPtr( new Drop(BLOCK_FENCE_GATE, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_BRICK_STAIRS, DropPtr( new Drop(BLOCK_BRICK_STAIRS, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_STONE_BRICK_STAIRS, DropPtr( new Drop(BLOCK_STONE_BRICK_STAIRS, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_MYCELIUM, DropPtr( new Drop(BLOCK_MYCELIUM, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_LILY_PAD, DropPtr( new Drop(BLOCK_LILY_PAD, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_NETHER_BRICK, DropPtr( new Drop(BLOCK_NETHER_BRICK, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_NETHER_BRICK_FENCE, DropPtr( new Drop(BLOCK_NETHER_BRICK_FENCE, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_NETHER_BRICK_STAIRS, DropPtr( new Drop(BLOCK_NETHER_BRICK_STAIRS, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_NETHER_WART, DropPtr( new Drop(ITEM_NETHER_WART, 10000, 1)))); // Depends of the stage of the plant.  Stage 1-3 = 1 Stage 4 = 2-4
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_ENCHANTMENT_TABLE, DropPtr( new Drop(BLOCK_ENCHANTMENT_TABLE, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_BREWING_STAND, DropPtr( new Drop(BLOCK_BREWING_STAND, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_CAULDRON, DropPtr( new Drop(BLOCK_CAULDRON, 10000, 1))));
  //BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_END_PORTAL, DropPtr( new Drop(BLOCK_END_PORTAL, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_END_PORTAL_FRAME, DropPtr( new Drop(BLOCK_END_PORTAL_FRAME, 10000, 1))));

  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_END_PORTAL_STONE, DropPtr( new Drop(BLOCK_END_PORTAL_STONE, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_DRAGON_EGG, DropPtr( new Drop(BLOCK_DRAGON_EGG, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_REDSTONE_LAMP_OFF, DropPtr( new Drop(BLOCK_REDSTONE_LAMP_OFF, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_REDSTONE_LAMP_ON, DropPtr( new Drop(BLOCK_REDSTONE_LAMP_OFF, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_WOODEN_DOUBLE_SLAB, DropPtr( new Drop(BLOCK_WOODEN_SLAB, 10000, 2))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_WOODEN_SLAB, DropPtr( new Drop(BLOCK_WOODEN_SLAB, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_COCOA_PLANT, DropPtr( new Drop(ITEM_DYE, 10000, 1, DYE_COCOA_BEANS)))); // Depends on the stage of the plant.  Stage 1-2 = 1 Stage 3 = 3
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_SANDSTONE_STAIRS, DropPtr( new Drop(BLOCK_SANDSTONE_STAIRS, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_EMERALD_ORE, DropPtr( new Drop(BLOCK_EMERALD_ORE, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_ENDER_CHEST, DropPtr( new Drop(BLOCK_ENDER_CHEST, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_TRIPWIRE_HOOK, DropPtr( new Drop(BLOCK_TRIPWIRE_HOOK, 10000, 1))));
  //BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_TRIPWIRE, DropPtr( new Drop(BLOCK_TRIPWIRE, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_EMERALD_BLOCK, DropPtr( new Drop(BLOCK_EMERALD_BLOCK, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_SPRUCE_WOOD_STAIRS, DropPtr( new Drop(BLOCK_SPRUCE_WOOD_STAIRS, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_BIRCH_WOOD_STAIRS, DropPtr( new Drop(BLOCK_BIRCH_WOOD_STAIRS, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_JUNGLE_WOOD_STAIRS, DropPtr( new Drop(BLOCK_JUNGLE_WOOD_STAIRS, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_COMMAND_BLOCK, DropPtr( new Drop(BLOCK_COMMAND_BLOCK, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_BEACON_BLOCK, DropPtr( new Drop(BLOCK_BEACON_BLOCK, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_COBBLESTONE_WALL, DropPtr( new Drop(BLOCK_COBBLESTONE_WALL, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_FLOWER_POT, DropPtr( new Drop(ITEM_FLOWER_POT, 10000, 1))));

  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_CARROT, DropPtr( new Drop(ITEM_CARROT, 10000, getDistribution(RAND_DROP_CARROT)))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_POTATOES, DropPtr( new Drop(ITEM_POTATO, 10000, getDistribution(RAND_DROP_POTATOES))))); // Can also drop an additional poisonous potato - 2% chance
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_WOODEN_BUTTON, DropPtr( new Drop(BLOCK_WOODEN_BUTTON, 10000, 1))));
  BLOCKDROPS.insert(std::pair<uint8_t, DropPtr>(BLOCK_HEAD, DropPtr( new Drop(ITEM_HEAD, 10000, 1))));
}

void Drop::getDrop(int16_t& item, uint8_t& count, uint8_t& meta)
{
  Drop *cur = this;
  while (cur)
  {
    if (cur->probability >= uniformUINT(0, 9999))
    {
      item = cur->item_id;
      count = cur->count;
      if (cur->meta != -1)
        meta = (uint8_t)cur->meta;
      return;
    }
    else
    {
      cur = cur->alt_drop.get();
    }
  }
  count = 0;
}
