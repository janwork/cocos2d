#include "Poke.h"
#include "GameScene.h"
#include "AppMacros.h"

USING_NS_CC;

Poke* Poke::create(PokeInfo info, bool  isSmall)
{
	Poke * sprite = new (std::nothrow) Poke();

	if (sprite && sprite->init(info, isSmall))
	{
		sprite->autorelease();
		return sprite;
	}

	CC_SAFE_DELETE(sprite);
	
	return nullptr;
}

char * poke_text[] = {
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"10",
	"J",
	"Q",
	"K",
	"A",
	"2",
	"w",
	"W",
};

bool Poke::init(PokeInfo info, bool isSmall)
{
	if (!Sprite::init())
	{
		return false;
	}

	_info = info;


	if (isSmall)
	{
		auto cardFront = Label::createWithSystemFont(poke_text[_info._num], "arial", 24);

		this->addChild(cardFront);

		_size = cardFront->getContentSize();
	}
	else
	{
		auto cardFront = Sprite::createWithSpriteFrameName("b/bg.png");
		this->addChild(cardFront);
		_size = cardFront->getContentSize();

		if (_info._num == PokeNum::NUM_XW)
		{
			auto cardNum = Sprite::createWithSpriteFrameName("b/smalltag_4.png");
			cardNum->setPosition(-50, 10);
			this->addChild(cardNum);

			auto cardTag = Sprite::createWithSpriteFrameName("b/bigtag_6.png");
			cardTag->setPosition(20, -30);
			this->addChild(cardTag);
		}
		else if (_info._num == PokeNum::NUM_DW)
		{
			auto cardNum = Sprite::createWithSpriteFrameName("b/smalltag_5.png");
			cardNum->setPosition(-50, 10);
			this->addChild(cardNum);

			auto cardTag = Sprite::createWithSpriteFrameName("b/bigtag_6.png");
			cardTag->setPosition(20, -30);
			this->addChild(cardTag);
		}
		else
		{
			unsigned int num = 0;

			if (_info._num == NUM_A)
			{
				num = 0;
			}
			else if (_info._num == NUM_2)
			{
				num = 1;
			}
			else
			{
				num = _info._num + 2;
			}


			char strTag[256];

			sprintf(strTag, "b/bigtag_%d.png", _info._tag);

			auto cardSmallTag = Sprite::createWithSpriteFrameName(strTag);
			cardSmallTag->setScale(0.5);
			cardSmallTag->setPosition(-50, 20);
			this->addChild(cardSmallTag);

			if (_info._tag == HEITAO || _info._tag == MEIHUA)
			{

				char strNum[256];
				sprintf(strNum, "b/black_%d.png", num);
				CCLOG("<janlog> 1111 %s", strNum);
				auto cardNum = Sprite::createWithSpriteFrameName(strNum);
				cardNum->setPosition(-50, 70);
				this->addChild(cardNum);
			}
			else
			{

				char strNum[256];
				sprintf(strNum, "b/red_%d.png", num);
				CCLOG("<janlog> 222 %s", strNum);
				auto cardNum = Sprite::createWithSpriteFrameName(strNum);
				cardNum->setPosition(-50, 70);
				this->addChild(cardNum);
			}


			auto cardTag = Sprite::createWithSpriteFrameName(strTag);
			cardTag->setPosition(20, -30);
			this->addChild(cardTag);
		}
	}

	_isSelected = false;

	return true;
}

void Poke::SetTouchEnabled()
{
	auto touchListener = EventListenerTouchOneByOne::create();

	touchListener->setSwallowTouches(true);

	touchListener->onTouchBegan = CC_CALLBACK_2(Poke::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(Poke::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(Poke::onTouchEnded, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(Poke::onTouchCancelled, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

}

Rect Poke::getRect()
{
	return Rect(-_size.width / 2, -_size.height / 2, _size.width, _size.height);
}

bool Poke::onTouchBegan(Touch * touch, Event * event)
{
	if (getRect().containsPoint(convertTouchToNodeSpaceAR(touch)))
	{
		click();

		return true;
	}

	return false;

}

void Poke::onTouchMoved(Touch * touch, Event * event)
{

}

void Poke::onTouchCancelled(Touch * touch, Event * event)
{

}

void Poke::onTouchEnded(Touch * touch, Event * event)
{

}

void Poke::click()
{
	Array* arr = _gameMain->getArrPlayerOut();

	if (_isSelected)
	{
		setPosition(_position.x, _position.y - 20);
		arr->removeObject(this);
	}
	else
	{
		setPosition(_position.x, _position.y + 20);
		arr->addObject(this);
	}

	_isSelected = !_isSelected;

}

void Poke::unSelect()
{
	Array * arr = _gameMain->getArrPlayerOut();

	if (_isSelected)
	{
		setPosition(_position.x, _position.y - 20);
		arr->removeObject(this);
	}

	_isSelected = false;

}

void Poke::Select()
{
	Array* arr = _gameMain->getArrPlayerOut();

	if (!_isSelected)
	{
		setPosition(_position.x, _position.y + 20);
		arr->addObject(this);
	}

	_isSelected = true;
}