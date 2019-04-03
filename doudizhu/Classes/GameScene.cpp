#include "GameScene.h"
#include "Player.h"
#include "MenuScene.h"


USING_NS_CC;
using namespace CocosDenshion;

struct PlayerInfo
{
	std::string _name;
	int			_score;
};

struct RunTimeData
{
	RunTimeData(){
		_isReady = false;
	}


	bool  _isReady;
	PlayerInfo _playerinfo1;
	PlayerInfo _playerinfo2;
	PlayerInfo _playerinfo3;

};


RunTimeData s_runtimeData;


Scene * GameScene::createScene(){
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);

	return scene;
}

bool  GameScene::init(){

	if (!Layer::init()){
		return false;
	}





	return true;

}

void GameScene::initCards(){

}

static int index_fapai = 0;


void GameScene::faPai(){
}

void GameScene::callbackFaPai(Node *node){

}

void GameScene::FaDiPai(Player* player){

}

void GameScene::menuBackCallback(Ref* pSender){

}

void GameScene::menuReadyCallback(Ref* pSender){

}

void GameScene::menuRestartCallback(Ref* pSender){

}

void GameScene::menuQiangCallback(Ref* pSender){

}

void GameScene::menuBuQiangCallback(Ref* pSender){

}

void GameScene::callbackQiangDiZhu2(Node *node){

}

void GameScene::callbackQiangDiZhu3(Node* node){

}

void GameScene::menuTiShiCallback(Ref* pSender){

}

void GameScene::menuBuChuCallback(Ref* pSender){

}

void GameScene::menuChuPaiCallback(Ref* pSender){

}

void GameScene::callbackChuPai2(Node * node){

}

void GameScene::callbackChuPai3(Node * node){

}

void GameScene::update(float dt){

}

void GameScene::OutCard(float dt){

}

void GameScene::gameover(int winID){

}

void GameScene::jiesuan(int winID){

}

void GameScene::callbackJieSuan(Node *node){

}