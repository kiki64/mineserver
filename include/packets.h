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

#ifndef _PACKETS_H
#define _PACKETS_H

#include <vector>
#include <deque>
#include <string>
#include <cstring>
#include <iterator>
#include <stdint.h>

#define PACKET_NEED_MORE_DATA -3
#define PACKET_DOES_NOT_EXIST -2
#define PACKET_VARIABLE_LEN   -1
#define PACKET_OK             0

#ifndef M_PI
#define M_PI 3.141592653589793238462643
#endif

class PacketHandler;
class User;

//Packet names
enum
{
  //Client to server
  PACKET_KEEP_ALIVE                = 0x00,
  PACKET_LOGIN_REQUEST             = 0x01,
  PACKET_HANDSHAKE                 = 0x02,
  PACKET_CHAT_MESSAGE              = 0x03,
  PACKET_ENTITY_EQUIPMENT          = 0x05,
  PACKET_USE_ENTITY                = 0x07,
  PACKET_RESPAWN                   = 0x09,
  PACKET_PLAYER                    = 0x0a,
  PACKET_PLAYER_POSITION           = 0x0b,
  PACKET_PLAYER_LOOK               = 0x0c,
  PACKET_PLAYER_POSITION_AND_LOOK  = 0x0d,
  PACKET_PLAYER_DIGGING            = 0x0e,
  PACKET_PLAYER_BLOCK_PLACEMENT    = 0x0f,
  PACKET_HOLDING_CHANGE            = 0x10,
  PACKET_ANIMATION                 = 0x12,
  PACKET_ENTITY_CROUCH             = 0x13,
  PACKET_INVENTORY_CLOSE           = 0x65,
  PACKET_INVENTORY_CHANGE          = 0x66,
  PACKET_SET_SLOT                  = 0x67,
  PACKET_INVENTORY                 = 0x68,
  PACKET_SIGN                      = 0x82,
  PACKET_TAB_COMPLETE              = 0xcb,
  PACKET_CLIENT_INFO               = 0xcc,
  PACKET_CLIENT_STATUS             = 0xcd,
  PACKET_PLUGIN_MESSAGE            = 0xfa,
  PACKET_ENCRYPTION_RESPONSE       = 0xFC,
  PACKET_DISCONNECT                = 0xff,
  //Server to client
  PACKET_LOGIN_RESPONSE            = 0x01,
  PACKET_TIME_UPDATE               = 0x04,
  PACKET_SPAWN_POSITION            = 0x06,
  PACKET_UPDATE_HEALTH             = 0x08,
  PACKET_ADD_TO_INVENTORY          = 0x11,
  PACKET_NAMED_ENTITY_SPAWN        = 0x14,
  PACKET_PICKUP_SPAWN              = 0x15,
  PACKET_COLLECT_ITEM              = 0x16,
  PACKET_ADD_OBJECT                = 0x17,
  PACKET_MOB_SPAWN                 = 0x18,
  PACKET_ENTITY_VELOCITY           = 0x1c,
  PACKET_DESTROY_ENTITY            = 0x1d,
  PACKET_ENTITY                    = 0x1e,
  PACKET_ENTITY_RELATIVE_MOVE      = 0x1f,
  PACKET_ENTITY_LOOK               = 0x20,
  PACKET_ENTITY_LOOK_RELATIVE_MOVE = 0x21,
  PACKET_ENTITY_TELEPORT           = 0x22,
  PACKET_ENTITY_HEAD_LOOK          = 0x23,
  PACKET_ENTITY_STATUS             = 0x26,
  PACKET_ATTACH_ENTITY             = 0x27,
  PACKET_ENTITY_METADATA           = 0x28,
  PACKET_REMOVE_ENTITY_EFFECT      = 0x2a,
  //PACKET_PRE_CHUNK                 = 0x32,
  PACKET_MAP_CHUNK                 = 0x33,
  PACKET_MULTI_BLOCK_CHANGE        = 0x34,
  PACKET_BLOCK_CHANGE              = 0x35,
  PACKET_BLOCK_ACTION              = 0x36,
  PACKET_NAMED_SOUND_EFFECT        = 0x3E,
  PACKET_GAMESTATE                 = 0x46,
  PACKET_OPEN_WINDOW               = 0x64,
  PACKET_PROGRESS_BAR              = 0x69,
  PACKET_TRANSACTION               = 0x6a,
  PACKET_PLAYER_LIST_ITEM          = 0xc9,
  //PACKET_COMPLEX_ENTITIES          = 0x3b,
  PACKET_PING                      = 0xFE,
  PACKET_ENCRYPTION_REQUEST        = 0xFD,
  PACKET_KICK                      = 0xff,

  /// two-way
  PACKET_CREATIVE_INVENTORY        = 0x6b,
  PACKET_PLAYER_ABILITIES          = 0xca,
  // TODO unhandled packets
  PACKET_THUNDERBOLT = 0x47,
  PACKET_INCREMENT_STATISTICS = 0xC8
};

class Packet
{
  // A deque has random-access iterators, so we can track the read position in an integer.
  typedef std::deque<uint8_t> BufferVector;

public:
  BufferVector m_readBuffer;
  BufferVector m_writeBuffer;
  size_t m_readPos;
  bool m_isValid;

public:
  Packet()
    :
    m_readBuffer(),
    m_writeBuffer(),
    m_readPos(0),
    m_isValid(true) 
  {
  }

  inline uint8_t firstwrite() const { return m_writeBuffer.front(); }

  inline bool haveData(int requiredBytes)
  {
    return m_isValid = m_isValid && (m_readPos + requiredBytes <= m_readBuffer.size());
  }

  inline operator bool() const
  {
    return m_isValid;
  }

  inline void reset()
  {
    m_readPos = 0;
    m_isValid = true;
  }

  inline void addToRead(const uint8_t* const data, const size_t len)
  {
    m_readBuffer.insert(m_readBuffer.end(), data, data + len);
    m_isValid = true;
  }

  inline void addToWrite(const Packet& p)
  {
    m_writeBuffer.insert(m_writeBuffer.end(), p.m_writeBuffer.begin(), p.m_writeBuffer.end());
  }

  inline void addToWrite(const uint8_t* const buffer, const size_t len)
  {
    m_writeBuffer.insert(m_writeBuffer.end(), buffer, buffer + len);
  }

  inline void removePacket()
  {
    m_readBuffer.erase(m_readBuffer.begin(), m_readBuffer.begin() + m_readPos);
    m_readPos = 0;
  }

  Packet& operator<<(int8_t val);
  Packet& operator>>(int8_t& val);
  Packet& operator<<(int16_t val);
  Packet& operator>>(int16_t& val);
  Packet& operator<<(int32_t val);
  Packet& operator>>(int32_t& val);
  Packet& operator<<(int64_t val);
  Packet& operator>>(int64_t& val);
  Packet& operator<<(float val);
  Packet& operator>>(float& val);
  Packet& operator<<(double val);
  Packet& operator>>(double& val);

  // convert to wstring and call that operator
  Packet& operator<<(const std::string& str);
  Packet& operator>>(std::string& str);

  void writeString(const std::string& str);
  std::string readString();

  Packet& operator<<(const Packet& other);

  inline void getData(uint8_t* buf, size_t count)
  {
    if (haveData(count))
    {
      std::copy(m_readBuffer.begin() + m_readPos, m_readBuffer.begin() + m_readPos + count, buf);
      m_readPos += count;
    }
  }

  inline bool getWriteEmpty() const
  {
    return m_writeBuffer.empty();
  }

  inline void getWriteData(std::vector<char>& buf) const
  {
    buf.clear();
    buf.resize(m_writeBuffer.size(), 0);
    std::copy(m_writeBuffer.begin(), m_writeBuffer.end(), buf.begin());
  }

  inline void clearWrite(size_t count)
  {
    BufferVector::iterator it = m_writeBuffer.begin();
    std::advance(it, count);
    m_writeBuffer.erase(m_writeBuffer.begin(), it);
  }
};


struct Packets
{
  typedef int (*handler_function)(User*);

  int len;
  handler_function function;

  Packets(int newlen = PACKET_DOES_NOT_EXIST)
    : len(newlen)
  {
  }

  Packets(int newlen, handler_function newfunction)
    : len(newlen), function(newfunction)
  {
  }

  Packets(const Packets & other)
    : len(other.len), function(other.function)
  {
  }
};

struct packet_login_request
{
  int version;
  std::string Username;
  std::string Password;
  int64_t map_seed;
  uint8_t dimension;
};

struct packet_player_position
{
  double x;
  double y;
  double stance;
  double z;
  char onground;
};

struct packet_player_look
{
  float yaw;
  float pitch;
  char onground;
};

struct packet_player_position_and_look
{
  double x;
  double y;
  double stance;
  double z;
  float yaw;
  float pitch;
  char onground;
};

class PacketHandler
{
public:
  void init();

  // Information of all the packets
  // around 2kB of memory
  Packets packets[256];

  // The packet functions
  static int keep_alive(User* user);
  static int login_request(User* user);
  static int handshake(User* user);
  static int chat_message(User* user);
  static int player(User* user);
  static int player_position(User* user);
  static int player_look(User* user);
  static int player_position_and_look(User* user);
  static int player_digging(User* user);
  static int player_block_placement(User* user);
  static int holding_change(User* user);
  static int arm_animation(User* user);
  static int pickup_spawn(User* user);
  static int disconnect(User* user);
  static int use_entity(User* user);
  static int respawn(User* user);
  static int change_sign(User* user);
  static int inventory_transaction(User* user);
  static int tab_complete(User* user);
  static int encryption_response(User* user);
  static int plugin_message(User* user);

  static int client_info(User* user);
  static int client_status(User* user);

  static int creative_inventory(User* user);
  static int player_abilities(User* user);

  static int inventory_change(User* user);
  static int inventory_close(User* user);
  static int destroy_entity(User* user);

  static int entity_crouch(User* user);

  static int unhandledPacket(User* user);

  static int ping(User* user);


  static int block_change(User* user);

};

#endif
