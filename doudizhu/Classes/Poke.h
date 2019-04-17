#ifndef __POKE_H__
#define __POKE_H__

#include "cocos2d.h"

USING_NS_CC;

// ÅÆÖµ
enum PokeNum
{
	NUM_3 = 0,
	NUM_4,
	NUM_5,
	NUM_6,
	NUM_7,
	NUM_8,
	NUM_9,
	NUM_10,
	NUM_J,
	NUM_Q,
	NUM_K,
	NUM_A,
	NUM_2,
	NUM_XW,
	NUM_DW
};


// »¨É«
enum PokeTag{
	FANGKUAI = 0,
	MEIHUA,
	HONGTAO,
	HEITAO
};


struct PokeInfo
{
	PokeNum _num;
	PokeTag _tag;

	inline bool operator==(const PokeInfo &pi) const
	{
		return (this->_num == pi._num && this->_tag == pi._tag);
	}
};

class GameScene;

class Poke : public Sprite{

public:
	static Poke* create(PokeInfo info, bool isSmall = false);

	virtual bool init(PokeInfo info, bool isSmall = false);

	void SetTouchEnabled();

	bool isSelected() { return _isSelected; };

	void click();

	void unSelect();

	void Select();

	PokeInfo getInfo() { return _info; };

	Rect getRect();

	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);


	CC_SYNTHESIZE(GameScene *, _gameMain, GameMain);


	PokeInfo _info;

protected:

	bool _isSelected;

	Size _size;
};



#endif