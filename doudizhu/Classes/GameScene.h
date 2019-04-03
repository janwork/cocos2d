#ifndef __SCENE_GAME_H__
#define __SCENE_GAME_H__

#include "cocos2d.h"
#include "Player.h"
#include "BottomCardZone.h"

USING_NS_CC;

class GameScene : public Layer {
public :
	static Scene* createScene();

	virtual bool init();

	void menuBackCallback(Ref* pSender);
	void menuReadyCallback(Ref* pSender);
	void menuRestartCallback(Ref* pSender);
	void menuQiangCallback(Ref* pSender);
	void menuBuQiangCallback(Ref* pSender);
	void menuTiShiCallback(Ref* pSender);
	void menuBuChuCallback(Ref* pSender);
	void menuChuPaiCallback(Ref* pSender);

	void callbackChuPai2(Node * node);
	void callbackChuPai3(Node * node);

	void callbackQiangDiZhu2(Node* node);
	void callbackQiangDiZhu3(Node* node);

	void callbackJieSuan(Node * node);

	void update(float dt);

	void OutCard(float dt);

	void faPai();

	void callbackFaPai(Node* node);

	void FaDiPai(Player* player);

	void gameover(int winID);

	void jiesuan(int winID);

	void setChuPaiMenuEnabled(bool isChuPai, bool isBuChu);

	void initCards();

	Array* getArrPlayerOut() { return  _arrPlayerOut; }

	CREATE_FUNC(GameScene);

public:
	Player* _player1;
	Player* _player2;
	Player* _player3;

protected:

	std::vector<PokeInfo> _vecDiPai;

	BottomCardZone* _bottomCardZone;

	Menu* _menuBack;
	Menu* _menuChuPai;
	Menu* _menuQiangDiZhu;
	Menu* _menuReady;


	int _state;
	bool _gameover;
	bool _begin;

	std::vector<PokeInfo> _pokeInfo;

	Array* _arrPlayerOut;

};


#endif