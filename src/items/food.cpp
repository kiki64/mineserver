#include "food.h"
#include "../packets.h"

bool ItemFood::affectedItem(int item) const
{
  switch (item)
  {
  case ITEM_GOLDEN_APPLE:
  case ITEM_MUSHROOM_SOUP:
  case ITEM_PORK:
  case ITEM_GRILLED_PORK:
  case ITEM_BREAD:
  case ITEM_COOKED_FISH:
  case ITEM_RAW_FISH:
  case ITEM_APPLE:
  case ITEM_MELON:
  case ITEM_ROTTEN_FLESH:
  case ITEM_RAW_CHICKEN:
  case ITEM_COOKED_CHICKEN:
  case ITEM_COOKIE:
  case ITEM_CAKE:
  case ITEM_RAW_BEEF:
  case ITEM_STEAK:
    return true;
  }
  return false;
}

void ItemFood::onRightClick(User* user, Item* item)
{
  float foodpoints = 0;
  float chanceOfFoodPosioning = 0.0;
  switch (item->getType())
  {
  case ITEM_GOLDEN_APPLE:
    foodpoints = 5;
    break;
  case ITEM_MUSHROOM_SOUP:
    foodpoints = 4;
    break;
  case ITEM_GRILLED_PORK:
    foodpoints = 4;
    break;
  case ITEM_PORK:
    foodpoints = 1.5;
    break;
  case ITEM_BREAD:
    foodpoints = 2.5;
    break;
  case ITEM_COOKED_FISH:
    foodpoints = 2.5;
    break;
  case ITEM_RAW_FISH:
    foodpoints = 1;
    break;
  case ITEM_APPLE:
    foodpoints = 2;
    break;
  case ITEM_MELON:
    foodpoints = 1;
    break;
  case ITEM_ROTTEN_FLESH:
    foodpoints = 2;
    chanceOfFoodPosioning = 0.80;
    break;
  case ITEM_RAW_CHICKEN:
    foodpoints = 1;
    chanceOfFoodPosioning = 0.30;
    break;
  case ITEM_COOKED_CHICKEN:
    foodpoints = 3;
    break;
  case ITEM_COOKIE:
    foodpoints = 0.5;
    break;
  case ITEM_CAKE:
    foodpoints = 2;
    break;
  case ITEM_RAW_BEEF:
    foodpoints = 1.5;
    break;
  case ITEM_STEAK:
    foodpoints = 4;
    break;
  }
  //int newhealth = user->health + foodpoints;
  //if (newhealth > 20)
  //{
  //  newhealth = 20;
  //}
  //user->sethealth(newhealth);
  item->setType(-1);  // Some food is stackable, find out how many are in stack then decide what to do.
}

