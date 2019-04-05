#pragma once
#ifndef __APPCOMMON_H__
#define __APPCOMMON_H__

#include "cocos2d.h"
#include "Player.h"
USING_NS_CC;

MenuItemSprite * customMenuItem(const std::string & normalImage, const std::string &disabledImage, const ccMenuCallback & callback);
MenuItemSprite * customMenuItemWithSpriteFrameName(const std::string & normalImage, const std::string & disabledImage, const ccMenuCallback & callback);

bool isContinuous(Array* vecPoke);
bool isContinuous(std::vector<int>& vec);


bool isLessTwo(Array* vecPoke);
bool isLessTwo(std::vector<int>& vec);


CARDS_DATA PanDuanPaiXing(Array* cards);
CARDS_DATA PanDuanPaiXing(std::vector<PokeInfo> & cards);
CARDS_DATA PanDuanPaiXing(std::vector<int>& cards);


#endif // !__APPCOMMON_H__


