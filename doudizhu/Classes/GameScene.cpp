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


	// ²¥·ÅÒôÀÖ
	SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/MusicEx_Normal.ogg", true);


	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	//±³¾°

	auto spr_bg = Sprite::create("bg_table.jpg");
	spr_bg->setPosition(Vec2(visibleSize.width / 2,visibleSize.height /2 ));
	addChild(spr_bg);


	auto spr_flag = Sprite::create("d_flag.png");
	spr_flag->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 100));
	addChild(spr_flag);

	auto itemBack = customMenuItem("item_back.png", "item_back.png", CC_CALLBACK_1(GameScene::menuBackCallback, this));
	itemBack->setPosition(visibleSize.width / 2 + 200, visibleSize.height - 50);


	_menuBack = Menu::create(itemBack,NULL);
	_menuBack->setPosition(Director::getInstance()->getVisibleOrigin());
	this->addChild(_menuBack, 1);


	auto itemReady = customMenuItem("item_zhunbei.png", "item_zhunbei.png", CC_CALLBACK_1(GameScene::menuReadyCallback, this));
	_menuReady = Menu::create(itemReady, NULL);
	this->addChild(_menuReady, 1);


	auto itemQiang = customMenuItem("item_qiangdizhu.png", "item_qiangdizhu.png", CC_CALLBACK_1(GameScene::menuQiangCallback, this));
	itemQiang->setPosition(-80, - 50);
	auto itemBuQiang = customMenuItem("item_buqiang.png", "item_buqiang.png", CC_CALLBACK_1(GameScene::menuBuQiangCallback, this));
	itemBuQiang->setPosition(80, -50);

	_menuQiangDiZhu = Menu::create(itemQiang, itemBuQiang, NULL);
	this->addChild(_menuQiangDiZhu, 1);

	auto itemBuChu = customMenuItem("item_buchu.png", "item_buchu.png", CC_CALLBACK_1(GameScene::menuBuChuCallback, this));
	itemBuChu->setPosition(50, -50);

	auto itemChuPai = customMenuItem("item_chupai.png", "item_chupai.png", CC_CALLBACK_1(GameScene::menuChuPaiCallback, this));
	itemChuPai->setPosition(250, -50);


	auto itemTiShi = customMenuItem("item_tishi.png", "item_tishi.png", CC_CALLBACK_1(GameScene::menuTiShiCallback, this));
	itemTiShi->setPosition(-150, -50);

	_menuChuPai = Menu::create();
	_menuChuPai->addChild(itemBuChu);
	_menuChuPai->addChild(itemChuPai);
	_menuChuPai->addChild(itemTiShi);
	this->addChild(_menuChuPai, 1);


	_menuChuPai->setVisible(false);


	srand(time(0));

	auto name_list = FileUtils::getInstance()->getValueMapFromFile("strings.xml").at("name_list").asValueVector();

	if (!s_runtimeData._isReady)
	{
		int name_index_1 = rand() % name_list.size();
		int name_index_2 = rand() % name_list.size();
		int name_index_3 = rand() % name_list.size();



		while (name_index_2 == name_index_1)
		{
			name_index_2 = rand() % name_list.size();
		}

		while (name_index_2 == name_index_1 || name_index_3 == name_index_1)
		{
			name_index_3 = rand() % name_list.size();
		}

		s_runtimeData._playerinfo1._name = name_list[name_index_1].asString();
		s_runtimeData._playerinfo1._score = 5000;

		s_runtimeData._playerinfo2._name = name_list[name_index_3].asString();
		s_runtimeData._playerinfo2._score = 5000;

		s_runtimeData._playerinfo3._name = name_list[name_index_2].asString();
		s_runtimeData._playerinfo3._score = 5000;


		s_runtimeData._isReady = true;
	}


	_player1 = Player::create(s_runtimeData._playerinfo1._name, s_runtimeData._playerinfo1._score, true);
	_player1->setPosition(70, 300);
	this->addChild(_player1);

	_player2 = Player::create(s_runtimeData._playerinfo2._name, s_runtimeData._playerinfo2._score, false);
	_player2->setPosition(1000, 600);
	this->addChild(_player2);

	_player3 = Player::create(s_runtimeData._playerinfo3._name, s_runtimeData._playerinfo3._score, false);
	_player3->setPosition(70, 600);
	this->addChild(_player3);

	_bottomCardZone = BottomCardZone::create();
	_bottomCardZone->setPosition(600, 610);
	this->addChild(_bottomCardZone, 1);

	initCards();

	_arrPlayerOut = Array::create();
	_arrPlayerOut->retain();

	_state = 1;
	_gameover = false;
	_begin = false;


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