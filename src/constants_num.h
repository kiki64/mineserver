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

#ifndef _CONSTANTS_NUM_H
#define _CONSTANTS_NUM_H

//
// Mineserver constants
//

//Player digging status
enum
{
  BLOCK_STATUS_STARTED_DIGGING,
  BLOCK_STATUS_DIGGING,
  //BLOCK_STATUS_STOPPED_DIGGING,
  BLOCK_STATUS_BLOCK_BROKEN,
  BLOCK_STATUS_PICKUP_SPAWN = 0x4
};

// Chat colors
#ifdef __cplusplus
#define MC_COLOR_BLACK std::string("§0")
#define MC_COLOR_DARK_BLUE std::string("§1")
#define MC_COLOR_DARK_GREEN std::string("§2")
#define MC_COLOR_DARK_CYAN std::string("§3")
#define MC_COLOR_DARK_RED std::string("§4")
#define MC_COLOR_DARK_MAGENTA std::string("§5")
#define MC_COLOR_DARK_ORANGE std::string("§6")
#define MC_COLOR_GREY std::string("§7")
#define MC_COLOR_DARK_GREY std::string("§8")
#define MC_COLOR_BLUE std::string("§9")
#define MC_COLOR_GREEN std::string("§a")
#define MC_COLOR_CYAN std::string("§b")
#define MC_COLOR_RED std::string("§c")
#define MC_COLOR_MAGENTA std::string("§d")
#define MC_COLOR_YELLOW std::string("§e")
#define MC_COLOR_WHITE std::string("§f")
#else
#define MC_COLOR_BLACK ("§0")
#define MC_COLOR_DARK_BLUE ("§1")
#define MC_COLOR_DARK_GREEN ("§2")
#define MC_COLOR_DARK_CYAN ("§3")
#define MC_COLOR_DARK_RED ("§4")
#define MC_COLOR_DARK_MAGENTA ("§5")
#define MC_COLOR_DARK_ORANGE ("§6")
#define MC_COLOR_GREY ("§7")
#define MC_COLOR_DARK_GREY ("§8")
#define MC_COLOR_BLUE ("§9")
#define MC_COLOR_GREEN ("§a")
#define MC_COLOR_CYAN ("§b")
#define MC_COLOR_RED ("§c")
#define MC_COLOR_MAGENTA ("§d")
#define MC_COLOR_YELLOW ("§e")
#define MC_COLOR_WHITE ("§f")
#endif

// Direction
// Caution! When changing a block the client uses SendDirection for direction - Sept 22 2011
// When sending us a block it uses the Direction below.
enum Direction
{
  BLOCK_BOTTOM, BLOCK_TOP, BLOCK_NORTH, BLOCK_SOUTH, BLOCK_WEST, BLOCK_EAST
};

enum SendDirection 
{
  SEND_BLOCK_BOTTOM, SEND_BLOCK_TOP, SEND_BLOCK_NORTH, SEND_BLOCK_WEST, SEND_BLOCK_EAST, SEND_BLOCK_SOUTH
};

// Blocks
enum Block
{
  BLOCK_AIR, BLOCK_STONE, BLOCK_GRASS, BLOCK_DIRT, BLOCK_COBBLESTONE, BLOCK_PLANK,
  BLOCK_SAPLING, BLOCK_BEDROCK, BLOCK_WATER, BLOCK_STATIONARY_WATER, BLOCK_LAVA,
  BLOCK_STATIONARY_LAVA, BLOCK_SAND, BLOCK_GRAVEL, BLOCK_GOLD_ORE, BLOCK_IRON_ORE,
  BLOCK_COAL_ORE, BLOCK_WOOD, BLOCK_LEAVES, BLOCK_SPONGE, BLOCK_GLASS, BLOCK_LAPIS_ORE,
  BLOCK_LAPIS_BLOCK, BLOCK_DISPENSER, BLOCK_SANDSTONE, BLOCK_NOTE_BLOCK, BLOCK_BED,
  BLOCK_YELLOW_FLOWER = 37, BLOCK_RED_ROSE, BLOCK_BROWN_MUSHROOM, BLOCK_RED_MUSHROOM,
  BLOCK_GOLD_BLOCK, BLOCK_IRON_BLOCK, BLOCK_DOUBLE_STEP, BLOCK_STEP, BLOCK_BRICK,
  BLOCK_TNT, BLOCK_BOOKSHELF, BLOCK_MOSSY_COBBLESTONE, BLOCK_OBSIDIAN, BLOCK_TORCH,
  BLOCK_FIRE, BLOCK_MOB_SPAWNER, BLOCK_WOODEN_STAIRS, BLOCK_CHEST, BLOCK_REDSTONE_WIRE,
  BLOCK_DIAMOND_ORE, BLOCK_DIAMOND_BLOCK, BLOCK_WORKBENCH, BLOCK_CROPS, BLOCK_SOIL,
  BLOCK_FURNACE, BLOCK_BURNING_FURNACE, BLOCK_SIGN_POST, BLOCK_WOODEN_DOOR,
  BLOCK_LADDER, BLOCK_MINECART_TRACKS, BLOCK_COBBLESTONE_STAIRS, BLOCK_WALL_SIGN,
  BLOCK_LEVER, BLOCK_STONE_PRESSURE_PLATE, BLOCK_IRON_DOOR, BLOCK_WOODEN_PRESSURE_PLATE,
  BLOCK_REDSTONE_ORE, BLOCK_GLOWING_REDSTONE_ORE, BLOCK_REDSTONE_TORCH_OFF,
  BLOCK_REDSTONE_TORCH_ON, BLOCK_STONE_BUTTON, BLOCK_SNOW, BLOCK_ICE, BLOCK_SNOW_BLOCK,
  BLOCK_CACTUS, BLOCK_CLAY, BLOCK_REED, BLOCK_JUKEBOX, BLOCK_FENCE, BLOCK_PUMPKIN,
  BLOCK_NETHERSTONE, BLOCK_SLOW_SAND, BLOCK_GLOWSTONE, BLOCK_PORTAL, BLOCK_JACK_O_LANTERN,
  BLOCK_CAKE, BLOCK_REDSTONE_REPEATER_OFF, BLOCK_REDSTONE_REPEATER_ON, BLOCK_LOCKED_CHEST,
  BLOCK_WOOL = 35
};

// Items
enum
{
  ITEM_IRON_SPADE = 256, ITEM_IRON_PICKAXE, ITEM_IRON_AXE, ITEM_FLINT_AND_STEEL, ITEM_APPLE,
  ITEM_BOW, ITEM_ARROW, ITEM_COAL, ITEM_DIAMOND, ITEM_IRON_INGOT, ITEM_GOLD_INGOT, ITEM_IRON_SWORD,
  ITEM_WOODEN_SWORD, ITEM_WOODEN_SPADE, ITEM_WOODEN_PICKAXE, ITEM_WOODEN_AXE, ITEM_STONE_SWORD,
  ITEM_STONE_SPADE, ITEM_STONE_PICKAXE, ITEM_STONE_AXE, ITEM_DIAMOND_SWORD,
  ITEM_DIAMOND_SPADE, ITEM_DIAMOND_PICKAXE, ITEM_DIAMOND_AXE, ITEM_STICK, ITEM_BOWL,
  ITEM_MUSHROOM_SOUP, ITEM_GOLD_SWORD, ITEM_GOLD_SPADE, ITEM_GOLD_PICKAXE, ITEM_GOLD_AXE,
  ITEM_STRING, ITEM_FEATHER, ITEM_GUNPOWDER, ITEM_WOODEN_HOE, ITEM_STONE_HOE,
  ITEM_IRON_HOE, ITEM_DIAMOND_HOE, ITEM_GOLD_HOE, ITEM_SEEDS, ITEM_WHEAT, ITEM_BREAD,
  ITEM_LEATHER_HELMET, ITEM_LEATHER_CHESTPLATE, ITEM_LEATHER_LEGGINGS, ITEM_LEATHER_BOOTS,
  ITEM_CHAINMAIL_HELMET, ITEM_CHAINMAIL_CHESTPLATE, ITEM_CHAINMAIL_LEGGINGS,
  ITEM_CHAINMAIL_BOOTS, ITEM_IRON_HELMET, ITEM_IRON_CHESTPLATE, ITEM_IRON_LEGGINGS,
  ITEM_IRON_BOOTS, ITEM_DIAMOND_HELMET, ITEM_DIAMOND_CHESTPLATE, ITEM_DIAMOND_LEGGINGS,
  ITEM_DIAMOND_BOOTS, ITEM_GOLD_HELMET, ITEM_GOLD_CHESTPLATE, ITEM_GOLD_LEGGINGS,
  ITEM_GOLD_BOOTS, ITEM_FLINT, ITEM_PORK, ITEM_GRILLED_PORK, ITEM_PAINTINGS,
  ITEM_GOLDEN_APPLE, ITEM_SIGN, ITEM_WOODEN_DOOR, ITEM_BUCKET, ITEM_WATER_BUCKET,
  ITEM_LAVA_BUCKET, ITEM_MINECART, ITEM_SADDLE, ITEM_IRON_DOOR, ITEM_REDSTONE,
  ITEM_SNOWBALL, ITEM_BOAT, ITEM_LEATHER, ITEM_MILK_BUCKET, ITEM_CLAY_BRICK,
  ITEM_CLAY_BALLS, ITEM_REED, ITEM_PAPER, ITEM_BOOK, ITEM_SLIME_BALL,
  ITEM_STORAGE_MINECART, ITEM_POWERED_MINECART, ITEM_EGG, ITEM_COMPASS, ITEM_FISHING_ROD,
  ITEM_WATCH, ITEM_GLOWSTONE_DUST, ITEM_RAW_FISH, ITEM_COOKED_FISH, ITEM_DYE,
  ITEM_BONE, ITEM_SUGAR, ITEM_CAKE, ITEM_BED
};

// Records
enum
{
  ITEM_GOLD_RECORD = 2256, ITEM_GREEN_RECORD
};

// Mobs
enum
{
  MOB_CREEPER = 50, MOB_SKELETON, MOB_SPIDER, MOB_GIANT_ZOMBIE, MOB_ZOMBIE,
  MOB_SLIME, MOB_GHAST, MOB_ZOMBIE_PIGMAN
};

// Animals
enum
{
  MOB_PIG = 90, MOB_SHEEP, MOB_COW, MOB_CHICKEN, MOB_SQUID
};

//Instruments (based off http://www.minecraftwiki.net/wiki/Note_Block)

enum
{
  INSTRUMENT_BASS = 1, INSTRUMENT_SNARE, INSTRUMENT_STICK, INSTRUMENT_BASSDRUM, INSTRUMENT_HARP
};

enum
{
  ENTITY_SAND = 21
};

// Animation
enum
{
  ANIMATE_HURT = 2, ANIMATE_DEAD
};

enum
{
  ANIMATE_SWING = 1, ANIMATE_DAMAGE, ANIMATE_LEAVE_BED, ANIMATE_CROUCH = 104, ANIMATE_UNCROUCH
};

enum Dye
{
  DYE_INK_SAC, DYE_RED, DYE_CACTUS_GREEN, DYE_COCOA_BEANS, DYE_LAPIS_LAZULI, DYE_PURPLE, DYE_CYAN,
  DYE_LIGHT_GRAY, DYE_GRAY, DYE_PINK, DYE_LIME, DYE_YELLOW, DYE_LIGHT_BLUE, DYE_MAGENTA, DYE_ORANGE,
  DYE_BONE_MEAL
};
#endif
