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

//#include <iostream>
#include <sstream>
#include <fstream> // Added for MOTD
//#include <string>
#include <deque>
//#include <stdint.h>
//#include <cstdlib>
//#include <ctime>

#include "tr1.h"
#include TR1INCLUDE(unordered_map)
#include TR1INCLUDE(memory)

#define MINESERVER_C_API
#include "plugin_api.h"
#include "commands_vanilla.h"

#define PLUGIN_COMMANDS_VANILLA_VERSION 1.4  // Following the minecraft official version
const std::string PLUGIN_NAME = "commands_vanilla";
const char CHATCMDPREFIX   = '/';
mineserver_pointer_struct* mineserver;

//Helper functions
std::string dtos(double n)
{
  std::ostringstream result;
  result << n;
  return result.str();
}

int roundUpTo(int x, int nearest)
{
  return (((x + (nearest - 1)) / nearest) * nearest );
}

void giveItemsName(std::string userIn, int id, int count, int health)
{
  if (mineserver->inventory.isValidItem(id))
  {
    int itemCount = 1, itemStacks = 1;

    if(count != 1)
    {
      itemCount = count;
      if(itemCount>1024) itemCount=1024;
      // If multiple stacks
      itemStacks = roundUpTo(itemCount, 64) / 64;
      itemCount  -= (itemStacks-1) * 64;
    }
    int amount = 64;
    for(int i = 0; i < itemStacks; i++)
    {
      // if last stack
      if(i == itemStacks - 1)
      {
        amount = itemCount;
      }
      mineserver->user.addItem(userIn.c_str(), id, amount, health);
    }
  }
  else
  {
    mineserver->chat.sendmsgTo(userIn.c_str(),  "Not a valid item");
  }
}

void giveItems(std::string user, std::string command, std::deque<std::string> args)
{
  int itemId = 0;
  int health = 0;
  int count = 1;
  int delimeterIndex = -1;

  //Send items to self
  if ((command == "igive" || command == "i" || command == "item" ) && args.size() >= 1 && args.size() <= 2)
  {
    //See if the item includes metadata
    delimeterIndex = args[0].find(":");
    if( delimeterIndex != -1 )
    {
      itemId = atoi(args[0].substr(0,delimeterIndex).c_str());
      health = atoi(args[0].substr(delimeterIndex + 1).c_str());
    }
    else
      itemId = atoi(args[0].c_str()); //Check if item is a number

    //If item was not a number, search the name from config
    if (itemId == 0)
      itemId = mineserver->config.iData(args[0].substr(0,delimeterIndex).c_str());
    if (args.size() == 2 )
      count = atoi(args[1].c_str());
  }
  //Send items to others.
  else if (args.size() >= 2 && args.size() <= 3)
  {
    user = args[0];

    //See if the item includes metadata
    delimeterIndex = args[1].find(":");
    if( delimeterIndex != -1 )
    {
      itemId = atoi(args[1].substr(0,delimeterIndex).c_str());
      health = atoi(args[1].substr(delimeterIndex + 1).c_str());
    }
    else
      itemId = atoi(args[1].c_str()); //Check if item is a number

    //If item was not a number, search the name from config
    if (itemId == 0)
      itemId = mineserver->config.iData(args[1].substr(0,delimeterIndex).c_str());

    if(args.size()==3)
      count = atoi(args[2].c_str());
  }
  else
  {
    mineserver->chat.sendmsgTo(user.c_str(), std::string("Usage: /" + command + " [player] item [count]").c_str());
  }

  giveItemsName(user, itemId, count, health);
}

void coordinateTeleport(std::string user, std::string command, std::deque<std::string> args)
{
  if(args.size() == 3)
  {
    double x = atof(args[0].c_str());
    double y = atof(args[1].c_str());
    double z = atof(args[2].c_str());
    mineserver->user.teleport(user.c_str(), x, y, z);
  }
  else
  {
    mineserver->chat.sendmsgTo(user.c_str(),"Usage: /ctp x y z");
  }
}

void userTeleport(std::string user, std::string command, std::deque<std::string> args)
{
  if(args.size() == 1)
  {
    std::string tUser = args[0];
    double x,y,z;
    if(mineserver->user.getPosition(tUser.c_str(), &x,&y,&z,NULL,NULL,NULL))
    {
      mineserver->user.teleport(user.c_str(),x,y+2,z);
      mineserver->chat.sendmsgTo(user.c_str(), "Teleported!");
    }
    else
    {
      std::string msg = "User " + args[0] + " not found (see /players)";
      mineserver->chat.sendmsgTo(user.c_str(), msg.c_str());
    }
  }
  else if(args.size() == 2)
  {
    std::string whoUser = args[0];
    std::string toUser  = args[1];

    double x,y,z;
    if(mineserver->user.getPosition(toUser.c_str(), &x,&y,&z,NULL,NULL,NULL))
    {
      mineserver->user.teleport(whoUser.c_str(),x,y+2,z);
      mineserver->chat.sendmsgTo(user.c_str(), "Teleported!");
    }
    else
    {
      std::string msg = "User " + args[0] + " not found (see /players)";
      mineserver->chat.sendmsgTo(user.c_str(), msg.c_str());
    }
  }
  else
  {
    mineserver->chat.sendmsgTo(user.c_str(), "Usage: /tp [player] targetplayer");
  }
}

void playerList(std::string user, std::string command, std::deque<std::string> args)
{
  mineserver->chat.sendUserlist(user.c_str());
}

void save(std::string user, std::string command, std::deque<std::string> args)
{
  mineserver->map.saveWholeMap();
  mineserver->chat.sendmsgTo(user.c_str(),"Saved map!");
}

void time(std::string user, std::string command, std::deque<std::string> args)
{
  if(args.size() == 0)
  {
    std::string msg = "The current server time is " + dtos(mineserver->map.getTime());
    mineserver->chat.sendmsgTo(user.c_str(), msg.c_str());
  }
  else if(args.size() == 1)
  {
    std::string timeValue = args[0];

    // Check for time labels
    if(timeValue == "day" || timeValue == "morning")
    {
      timeValue = "24000";
    }
    else if (timeValue == "dawn")
    {
      timeValue = "22500";
    }
    else if (timeValue == "noon")
    {
      timeValue = "6000";
    }
    else if (timeValue == "dusk")
    {
      timeValue = "12000";
    }
    else if (timeValue == "night" || timeValue == "midnight")
    {
      timeValue = "18000";
    }

    mineserver->map.setTime(atoi(timeValue.c_str()));

    mineserver->chat.sendmsgTo(user.c_str(),"World time changed.");
  }
  else
  {
    mineserver->chat.sendmsgTo(user.c_str(), std::string("Usage: /" + command + " time (time = 0-24000)").c_str());
  }
}

void ban(std::string user, std::string command, std::deque<std::string> args)
{
  return;
}

void unban(std::string user, std::string command, std::deque<std::string> args) 
{
  return;
}



void changeGameMode(std::string user, std::string command, std::deque<std::string> args)
{
    std::string changeUser = user;
    int gamemode = -1;

    if(args.size() >= 1)
    {
      if(args.size() == 2)
        changeUser = args[0];

      if(args[0] == "survival" || atoi(args[0].c_str()) == 0 ) 
        gamemode = 0;
      else if(args[0] == "creative" || atoi(args[0].c_str()) == 1)
        gamemode = 1;
      //else if(args[0] == "adventure" || atoi(args[0].c_str()) == 2)
        //gamemode = 2;

      if(gamemode != -1)
      {
        mineserver->user.setGameMode(changeUser.c_str(), gamemode);
        mineserver->logger.log(LOG_INFO, "plugin.commands", 
          std::string(user + " set " + changeUser + "'s gamemode to " + 
          ( gamemode == 0 ? "survival" : ( gamemode == 1 ? "creative" : "adventure" ) ) + ".").c_str());
      }
      else
        mineserver->chat.sendmsgTo(user.c_str(), "usage: /gamemode [player] < survival: 0 | creative: 1 > " ) ;
    }
    else
      mineserver->chat.sendmsgTo(user.c_str(), "usage: /gamemode [player] < survival: 0 | creative: 1 > " ) ;
}

void kick(std::string user, std::string command, std::deque<std::string> args)
{
  if( args.size() >= 1 )
  {
    std::string reason = "";
    if(args.size() >= 2)
    {
      for( int i = 1; i < args.size(); i++ ) // Get all of reason for kick.
      {
        reason += " " + args[i];
      }
      reason = reason.substr(0,15); // BUG: For some reason when testing >15 for a reason is to much.
    }
    mineserver->user.kick(args[0].c_str(), reason);
    mineserver->logger.log(LOG_INFO, "plugin.commands", std::string(user + " kicked " + args[0] + " Reason:" + reason).c_str());
  }
  else
  {
    mineserver->chat.sendmsgTo(user.c_str(), "usage: /kick <player> [reason]" ) ;
  }
}

void me(std::string user, std::string command, std::deque<std::string> args)
{
  if( args.size() >= 1 )
  {
    std::string message = "";

    for( int i = 0; i < args.size(); i++ ) // Get all of message.
    {
      message += " " + args[i];
    }

    mineserver->chat.sendmsg(std::string("* " + user + message).c_str());
  }
  else
    mineserver->chat.sendmsgTo(user.c_str(), "usage: /me <action>") ;
}

void kill(std::string user, std::string command, std::deque<std::string> args)
{
  std::string tokill = user;
  if( args.size() == 1 )
  {
    tokill = args[0];
  }

  mineserver->user.sethealth(tokill.c_str(), -1000);
}

void tell(std::string user, std::string command, std::deque<std::string> args)
{
  if( args.size() >= 2 )
  {
    std::string message = "";

    for( int i = 1; i < args.size(); i++ ) // Get all of message.
    {
      message += " " + args[i];
    }

    mineserver->chat.sendmsgTo(args[0].c_str(), std::string(user + "> " + message).c_str() );
  }
  else
    mineserver->chat.sendmsgTo(user.c_str(), std::string("usage: /"+command+" <player> <message>").c_str()) ;
}

void whitelist(std::string user, std::string command, std::deque<std::string> args)
{
  std::string whitelistFile = "whitelist.txt";

  if( args.size() >= 1 )
  {
    if( args[0] == "add" )
    {
      if( args.size() == 2 )
      {
        std::string line;
        std::fstream file;
        file.open(whitelistFile.c_str(), std::fstream::in);
        if( file.is_open() )
        {
          while( file.good() )
          {
            getline(file,line);
            if( line.compare( args[1] ) == 0 )
            {
              mineserver->chat.sendmsgTo(user.c_str(), std::string(args[1] + " is already in the whitelist.").c_str());
              return;
            }
          }
          file.close();
        }
      
        file.open(whitelistFile.c_str(), std::fstream::out | std::fstream::app);
        file << args[1] << std::endl;
        mineserver->chat.sendmsgTo(user.c_str(), std::string(args[1] + " was added to the whitelist.").c_str());
      }
      else
        mineserver->chat.sendmsgTo(user.c_str(), std::string("usage: /whitelist add <player>").c_str());
    }
    else if( args[0] == "remove" || args[0] == "delete" )
    {
      if( args.size() == 2 )
      {
        bool found = false;
        std::string tempWhitelist = "tempWhitelist.txt";
        std::string line;

        std::fstream file, tempfile;
        file.open(whitelistFile.c_str(), std::fstream::in);
        tempfile.open(tempWhitelist.c_str(), std::fstream::out | std::fstream::trunc);
        if( file.is_open() && tempfile.is_open() )
        {
          while( file.good() )
          {
            std::getline(file, line);
            if( line.compare( args[1] ) == 0 )
            {
              found = true;
            }
            else if( line.size() >= 1 )
            {
              tempfile << line << std::endl;
            }
          }
          file.close();
          tempfile.close();
        }
        else
        {
          mineserver->chat.sendmsgTo(user.c_str(), "An error occcured while modifing the whitelist.");
          return;
        }

        if( found )
        {  
          //Remove old whitelist.
          if( std::rename(whitelistFile.c_str(), std::string(whitelistFile + "2").c_str()) == 0 )
          {
            if( std::rename(tempWhitelist.c_str(), whitelistFile.c_str()) == 0 )
            {
              if( std::remove(std::string(whitelistFile + "2").c_str()) == 0 )
              {
                mineserver->chat.sendmsgTo(user.c_str(), std::string(args[1] + " was removed from the whitelist.").c_str());
                return;
              }
              else
              {
                mineserver->chat.sendmsgTo(user.c_str(), "An error occcured while modifing the whitelist. Delete1");
                std::remove(tempWhitelist.c_str());
                std::rename(std::string(whitelistFile + "2").c_str(), whitelistFile.c_str());
              }
            }
            else
            {
              mineserver->chat.sendmsgTo(user.c_str(), "An error occcured while modifing the whitelist. Rename2");
              std::rename(std::string(whitelistFile + "2").c_str(), whitelistFile.c_str());
            }
          }
          else
            mineserver->chat.sendmsgTo(user.c_str(), "An error occcured while modifing the whitelist. Rename1");
        }
        else
        {
          std::remove(tempWhitelist.c_str());
          mineserver->chat.sendmsgTo(user.c_str(), std::string(args[1] + " was not found in the whitelist.").c_str());
          return;
        }
      }
      else
        mineserver->chat.sendmsgTo(user.c_str(), std::string("usage: /whitelist remove <player>").c_str());
    }
    else if( args[0] == "list" )
    {
      std::string all;
      std::string line;

      std::fstream file;
      file.open(whitelistFile.c_str(), std::fstream::in);
      if( file.is_open() )
      {
        while( file.good() )
        {
          getline(file,line);
          if( line.substr(0,1) != "#" && line.size() >= 1 )
            all += line + ", ";
        }
        file.close();
      }
      
      //Remove trailing space and comma
      all = all.substr(0, all.length()-2);

      mineserver->chat.sendmsgTo(user.c_str(), all.c_str());
    }
    else if( args[0] == "on" )
    {
      mineserver->chat.sendmsgTo(user.c_str(), "Whitelist is now enabled.");
    }
    else if( args[0] == "off" )
    {
      mineserver->chat.sendmsgTo(user.c_str(), "Whitelist off");
    }
    else if( args[0] == "reload" )
    {
      mineserver->chat.sendmsgTo(user.c_str(), "Whitelist reload");
    }
    else
      mineserver->chat.sendmsgTo(user.c_str(), std::string("usage: /"+command+" [add|remove|list|on|off|reload]").c_str()) ;
  }
  else
    mineserver->chat.sendmsgTo(user.c_str(), std::string("usage: /"+command+" [add|remove|list|on|off|reload]").c_str()) ;
}



PLUGIN_API_EXPORT void CALLCONVERSION commands_vanilla_init(mineserver_pointer_struct* mineserver_temp)
{
  mineserver = mineserver_temp;

  if (mineserver->plugin.getPluginVersion(PLUGIN_NAME.c_str()) > 0)
  {
    mineserver->logger.log(LOG_INFO, std::string("plugin." + PLUGIN_NAME).c_str(), std::string(PLUGIN_NAME + " is already loaded v."+dtos(PLUGIN_COMMANDS_VANILLA_VERSION)).c_str());
    return;
  }
  mineserver->logger.log(LOG_INFO, std::string("plugin." + PLUGIN_NAME).c_str(), std::string("Loaded "+PLUGIN_NAME+"!").c_str());
  mineserver->plugin.setPluginVersion(PLUGIN_NAME.c_str(), PLUGIN_COMMANDS_VANILLA_VERSION);
  //mineserver->plugin.addCallback("PlayerChatCommand", reinterpret_cast<voidF>(chatCommandFunction));
  //mineserver->plugin.addCallback("BlockPlacePre", reinterpret_cast<voidF>(blockPlacePreFunction));
  //mineserver->plugin.addCallback("PlayerDiggingStarted", reinterpret_cast<voidF>(startedDiggingFunction));

  //mineserver->chat.registerCommand(ComPtr(new Command("ban", "<player> [reason]", "Ban a player from playing on this server", ban)));
  //mineserver->chat.registerCommand(ComPtr(new Command("ban-ip", "<ip address> [reason]", "Ban anyone from an ipaddress from playing on this server.", banIp)));
  //mineserver->chat.registerCommand(ComPtr(new Command("banlist", "[ips]", "Show player banned or ips banned.", banList)));
  // Change mineserver->chat.registerCommand(ComPtr(new Command("ctp", "<x> <y> <z>", "Teleport to coordinates (eg. /ctp 100 100 100)", coordinateTeleport))); // Change to tp
  //mineserver->chat.registerCommand(ComPtr(new Command("defaultgamemode", "<survival:0 creative:1 adventure:2>", "Change the default gamemode of the entire server.", changeDefaultGameMode)));
  //mineserver->chat.registerCommand(ComPtr(new Command("deop", "<player>", "Remove this player from the list of ops.", deop)));
  mineserver->chat.registerCommand(ComPtr(new Command(parseCmd("gamemode"), "[player] <survival:0 creative:1 adventure:2>", "Changes your or someone else's gamemode.", changeGameMode)));
  mineserver->chat.registerCommand(ComPtr(new Command(parseCmd("give igive i item"), "[player] <id/alias> [count]", "Gives <player> [count] pieces of <id/alias>. By default [count] = 1", giveItems)));
  /*mineserver->chat.registerCommand(ComPtr(new Command("help ?", "[<commandName>]", "Display this help message.", sendHelp)));*/
  mineserver->chat.registerCommand(ComPtr(new Command(parseCmd("kick"), "<player> [reason]", "Kicks a player from the server.", kick)));
  mineserver->chat.registerCommand(ComPtr(new Command(parseCmd("kill slay"), "[player]", "Kill either you or another player.", kill)));
  mineserver->chat.registerCommand(ComPtr(new Command(parseCmd("list players who names"), "", "Lists online players", playerList)));
  mineserver->chat.registerCommand(ComPtr(new Command(parseCmd("me emote"), "<action>", "Displays your message as an action.", me)));
  //mineserver->chat.registerCommand(ComPtr(new Command("op", "<player>", "Adds player to the list of ops.", op)));
  mineserver->chat.registerCommand(ComPtr(new Command(parseCmd("pardon unban"), "<player>", "Remove the ban of a player from this server.", unban)));
  //mineserver->chat.registerCommand(ComPtr(new Command("pardon-ip unban-ip", "<ip address>", "Remove the ban of an ip address from this server.", unbanIp)));
  /*mineserver->chat.registerCommand(ComPtr(new Command("publish", "", "", publish))); //mineserver is not a local/singleplayer server. /publish not supported.*/
  mineserver->chat.registerCommand(ComPtr(new Command(parseCmd("save-all save"), "", "Manually saves map to disc", save)));
  //mineserver->chat.registerCommand(ComPtr(new Command("save-off", "", "Change save on interval to off", saveOff)));
  //mineserver->chat.registerCommand(ComPtr(new Command("save-on", "", "Change save on interval to on", saveOn)));
  //mineserver->chat.registerCommand(ComPtr(new Command("say broadcast", "<message>", "Broadcast a message to all players (in pink letters)", say)));
  //mineserver->chat.registerCommand(ComPtr(new Command("seed", "", "Displays the world seed", sendSeed)));
  /*mineserver->chat.registerCommand(ComPtr(new Command("stop exit", "", "", stop))); //stop and exit are hard coded into the server.*/
  mineserver->chat.registerCommand(ComPtr(new Command(parseCmd("tell t msg m whisper"), "<player> <message>", "Quitely tell another player something.", tell)));
  mineserver->chat.registerCommand(ComPtr(new Command(parseCmd("time settime gettime"), "<time>", "Sets the world time. (<time> = 0-24000, 0 & 24000 = day, ~15000 = night)", time)));
  //mineserver->chat.registerCommand(ComPtr(new Command("toggledownfall weather", "[off|rain|thunder]", "Toggles the status of the weather.", weather);
  mineserver->chat.registerCommand(ComPtr(new Command(parseCmd("tp"), "<player> [<anotherPlayer>]", "Teleport yourself to <player>'s position or <player> to <anotherPlayer>", userTeleport)));
  mineserver->chat.registerCommand(ComPtr(new Command(parseCmd("whitelist"), "<add|remove|list|on|off|reload>", "Manages the servers whitelist", whitelist)));
  //mineserver->chat.registerCommand(ComPtr(new Command("xp experience", "<amount> <player>", "Add or subtract to a players experience progress. (5000 max per command)", giveExperience)));
}

PLUGIN_API_EXPORT void CALLCONVERSION commands_vanilla_shutdown(void)
{
  if (mineserver->plugin.getPluginVersion(PLUGIN_NAME.c_str()) <= 0)
  {
    mineserver->logger.log(LOG_INFO, std::string("plugin."+PLUGIN_NAME).c_str(), std::string(PLUGIN_NAME+" is not loaded!").c_str());
    return;
  }
}

std::deque<std::string> parseCmd(std::string cmd)
{
  int del;
  std::deque<std::string> temp;

  while(cmd.length() > 0)
  {
    while(cmd[0] == ' ')
    {
      cmd = cmd.substr(1);
    }

    del = cmd.find(' ');

    if(del > -1)
    {
      temp.push_back(cmd.substr(0, del));
      cmd = cmd.substr(del+1);
    }
    else
    {
      temp.push_back(cmd);
      break;
    }
  }

  if(temp.empty())
  {
    temp.push_back("empty");
  }

  return temp;
}