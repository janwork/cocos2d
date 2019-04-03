#ifndef __BOTTOM_CARD_ZONE_H__
#define __BOTTOM_CARD_ZONE_H__

#include "cocos2d.h"
#include "Poke.h"

USING_NS_CC;

class BottomCardZone : Sprite{
public:

	static BottomCardZone * create();

	virtual bool init();

	void show(PokeInfo cardInfo);
};

#endif
