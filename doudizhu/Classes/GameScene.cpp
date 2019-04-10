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


	//// 播放音乐
	SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/MusicEx_Normal.ogg", true);


	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	//背景

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

void GameScene::initCards()
{

	for (int i = 0; i < 13; i++){
		for (int j = 0; j < 4; j++){
			PokeInfo info;
			info._num = (PokeNum)i;
			info._tag = (PokeTag)j;
			_pokeInfo.push_back(info);
		}
	}

	PokeInfo info;
	info._num = (PokeNum)13;
	info._tag = (PokeTag)0;
	_pokeInfo.push_back(info);
	info._num = (PokeNum)14;
	_pokeInfo.push_back(info);


}

static int index_fapai = 0;


void GameScene::faPai(){

	index_fapai = 0;

	srand(time(0));

	std::random_shuffle(_pokeInfo.begin(), _pokeInfo.end());

	auto delay = DelayTime::create(0.04);
	auto callback = CallFuncN::create(CC_CALLBACK_1(GameScene::callbackFaPai, this));
	auto seq = Sequence::createWithTwoActions(delay, callback);
	this->runAction(seq);


	schedule(schedule_selector(GameScene::OutCard), 0.1);
}

void GameScene::callbackFaPai(Node *node)
{

	if (index_fapai < 51)
	{
		if (index_fapai % 3 == 0)
		{

			_player1->FaPai(this, _pokeInfo.at(index_fapai));
		}
		else if (index_fapai % 3 == 1)
		{
			_player2->FaPai(this, _pokeInfo.at(index_fapai));
		}
		else if (index_fapai % 3 == 2)
		{
			_player3->FaPai(this, _pokeInfo.at(index_fapai));
		}

		index_fapai++;
	}

	if (index_fapai < 51)
	{
		auto delay = DelayTime::create(0.04);
		auto callback = CallFuncN::create(CC_CALLBACK_1(GameScene::callbackFaPai, this));
		auto seq = Sequence::createWithTwoActions(delay, callback);
		this->runAction(seq);
	}
	else
	{
		_menuQiangDiZhu->setVisible(true);
	}
}

void GameScene::FaDiPai(Player* player){
	for (int i = index_fapai; i < 54; i++)
	{
		_bottomCardZone->show(_pokeInfo.at(i));
		_vecDiPai.push_back(_pokeInfo.at(i));
	}

	player->setDiZhu();

	for (int i = 0; i < _vecDiPai.size(); i++)
	{
		player->FaPai(this, _vecDiPai[i]);
	}
}

void GameScene::menuBackCallback(Ref* pSender){
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	Director::getInstance()->replaceScene(MenuScene::createScene());
}

void GameScene::menuReadyCallback(Ref* pSender){

	faPai();
	_menuReady->setVisible(false);
}

void GameScene::menuRestartCallback(Ref* pSender)
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	Director::getInstance()->replaceScene(GameScene::createScene());
}

void GameScene::menuQiangCallback(Ref* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("sound/Man/Order.ogg");

	FaDiPai(_player1);
	_menuQiangDiZhu->setVisible(false);
	_menuChuPai->setVisible(true);
}

void GameScene::menuBuQiangCallback(Ref* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("sound/Man/NoOrder.ogg");

	_menuQiangDiZhu->setVisible(false);

	auto delay = DelayTime::create(2);
	auto callback = CallFuncN::create(CC_CALLBACK_1(GameScene::callbackQiangDiZhu2, this));
	auto seq = Sequence::createWithTwoActions(delay, callback);
	this->runAction(seq);
}

void GameScene::callbackQiangDiZhu2(Node *node)
{
	if (_player2->IsQiangDiZhu())
	{
		FaDiPai(_player2);

		if (!_gameover){
			auto delay = DelayTime::create(3);
			auto callback = CallFuncN::create(CC_CALLBACK_1(GameScene::callbackChuPai2, this));
			auto seq = Sequence::createWithTwoActions(delay, callback);

			this->runAction(seq);

			SimpleAudioEngine::getInstance()->playEffect("sound/Man/Rob1.ogg");


			if (!_begin){
				_begin = true;
			}
		}
	}
	else
	{
		SimpleAudioEngine::getInstance()->playEffect("sound/Man/NoRob.ogg");

		auto delay = DelayTime::create(2);
		auto callback = CallFuncN::create(CC_CALLBACK_1(GameScene::callbackQiangDiZhu3, this));
		auto seq = Sequence::createWithTwoActions(delay, callback);

		this->runAction(seq);
	}
}

void GameScene::callbackQiangDiZhu3(Node* node){
	FaDiPai(_player3);

	if (!_gameover)
	{
	auto delay = DelayTime::create(2);
	auto callback = CallFuncN::create(CC_CALLBACK_1(GameScene::callbackChuPai3, this));
	auto seq = Sequence::createWithTwoActions(delay, callback);

	this->runAction(seq);

	SimpleAudioEngine::getInstance()->playEffect("sound/Man/Rob3.ogg");

	if (!_begin)
	{
	_begin = true;
	}
	}
}

void GameScene::menuTiShiCallback(Ref* pSender)
{

	CARDS_DATA card_data = PanDuanPaiXing(_arrPlayerOut);


	auto player3_outcards = _player3->GetOutCards();

	CARDS_DATA player3_card_data = PanDuanPaiXing(player3_outcards);


	if (player3_outcards.empty())
	{
		auto player2_outcards = _player2->GetOutCards();
		CARDS_DATA player2_card_data = PanDuanPaiXing(player2_outcards);

		if (player2_outcards.empty())
		{
			_player1->ShowTipInfo(false, player2_card_data._type, player2_card_data._cards.size(), player2_card_data._value);
		}
		else
		{
			_player1->ShowTipInfo(true, player2_card_data._type, player2_card_data._cards.size(), player2_card_data._value);
		}

	}
	else
	{
		_player1->ShowTipInfo(true, player3_card_data._type, player3_card_data._cards.size(), player3_card_data._value);
	}
}

void GameScene::menuBuChuCallback(Ref* pSender)
{
	_player3->clearCards();
	_player1->BuChu();

	auto delay = DelayTime::create(1);
	auto callback = CallFuncN::create(CC_CALLBACK_1(GameScene::callbackChuPai2,this));
	auto seq = Sequence::createWithTwoActions(delay, callback);

	this->runAction(seq);

	_menuChuPai->setVisible(false);
	SimpleAudioEngine::getInstance()->playEffect("sound/Man/buyao4.ogg");
}

void GameScene::menuChuPaiCallback(Ref* pSender)
{
	if (!_begin)
	{
	_begin = true;
	}

	auto player3_outcards = _player3->GetOutCards();

	CARDS_DATA player3_card_data = PanDuanPaiXing(player3_outcards);


	if (player3_outcards.empty())
	{
	auto player2_outcards = _player2->GetOutCards();
	CARDS_DATA player2_card_data = PanDuanPaiXing(player2_outcards);

	if (player2_outcards.empty())
	{
	_player1->ChuPai(this, false, ERROR_CARD, 0, 1);
	}
	else
	{
	_player1->ChuPai(this, true, player2_card_data._type, player2_outcards.size(), player2_card_data._value);
	}
	}
	else
	{
	_player1->ChuPai(this, true, player3_card_data._type, player3_outcards.size(), player3_card_data._value);
	}

	_arrPlayerOut->removeAllObjects();

	if (!_gameover)
	{
	auto delay = DelayTime::create(1);
	auto callback = CallFuncN::create(CC_CALLBACK_1(GameScene::callbackChuPai2, this));
	auto seq = Sequence::createWithTwoActions(delay, callback);

	this->runAction(seq);
	}

	_menuChuPai->setVisible(false);
}

void GameScene::callbackChuPai2(Node * node)
{
	// 出牌之前，判断上家的牌型
	auto player1_outcards = _player1->GetOutCards();
	CARDS_DATA player1_card_data = PanDuanPaiXing(player1_outcards);

	if (player1_outcards.empty())
	{
		auto player3_outcards = _player3->GetOutCards();
		CARDS_DATA player3_card_data = PanDuanPaiXing(player3_outcards);
		if (player3_outcards.empty())
		{
			_player2->ChuPai(this, false, ERROR_CARD, 0, 1);// 出牌
		}
		else
		{
			_player2->ChuPai(this, true, player3_card_data._type, player3_outcards.size(), player3_card_data._value);// 跟牌
		}
	}
	else
	{
		_player2->ChuPai(this, true, player1_card_data._type, player1_outcards.size(), player1_card_data._value);// 跟牌
	}

	if (!_gameover)
	{
		auto delay = DelayTime::create(1);
		auto callback = CallFuncN::create(CC_CALLBACK_1(GameScene::callbackChuPai3, this));
		auto seq = Sequence::createWithTwoActions(delay, callback);
		this->runAction(seq);
	}
}

void GameScene::callbackChuPai3(Node * node)
{
	// 出牌之前，判断上家的牌型
	auto player2_outcards = _player2->GetOutCards();
	CARDS_DATA player2_card_data = PanDuanPaiXing(player2_outcards);

	if (player2_outcards.empty())
	{
		auto player1_outcards = _player1->GetOutCards();
		CARDS_DATA player1_card_data = PanDuanPaiXing(player1_outcards);
		if (player1_outcards.empty())
		{
			_player3->ChuPai(this, false, ERROR_CARD, 0, 1);// 出牌
		}
		else
		{
			_player3->ChuPai(this, true, player1_card_data._type, player1_outcards.size(), player1_card_data._value);// 跟牌
		}
	}
	else
	{
		_player3->ChuPai(this, true, player2_card_data._type, player2_outcards.size(), player2_card_data._value);// 跟牌
	}

	if (!_gameover)
	{
		_menuChuPai->setVisible(true);
	}
}

void GameScene::update(float dt){

}

void GameScene::setChuPaiMenuEnabled(bool isChuPai, bool isBuChu)
{
	((MenuItemFont *)_menuChuPai->getChildByTag(1))->setEnabled(isChuPai);
	((MenuItemFont *)_menuChuPai->getChildByTag(0))->setCascadeColorEnabled(isBuChu);
}

void GameScene::OutCard(float dt){


	if (_state == 1)
	{


		if (!_begin)
		{
			CARDS_DATA card_data = PanDuanPaiXing(_arrPlayerOut);
			setChuPaiMenuEnabled(card_data._type != ERROR_CARD, false);
		}
		else
		{
			CARDS_DATA card_data = PanDuanPaiXing(_arrPlayerOut);

			auto player3_outcards = _player3->GetOutCards();
			CARDS_DATA player3_card_data = PanDuanPaiXing(player3_outcards);

			if (player3_outcards.empty())
			{
				auto player2_outcards = _player2->GetOutCards();
				CARDS_DATA player2_card_data = PanDuanPaiXing(player2_outcards);

				if (player2_outcards.empty())
				{
					setChuPaiMenuEnabled(card_data._type != ERROR_CARD, false);
				}
				else
				{
					if (
						(card_data._type == player2_card_data._type && card_data._value > player2_card_data._value) ||
						(card_data._type != player2_card_data._type && player2_card_data._type != MISSILE_CARD &&
						(card_data._type == BOMB_CARD || card_data._type == MISSILE_CARD) && card_data._value > player2_card_data._value))
					{
						setChuPaiMenuEnabled(true, true);
					}
					else
					{
						setChuPaiMenuEnabled(false, true);
					}
				}
			}
			else
			{

				if (
					(card_data._type == player3_card_data._type && card_data._value > player3_card_data._value) ||
					(card_data._type != player3_card_data._type && player3_card_data._type != MISSILE_CARD &&
					(card_data._type == BOMB_CARD || card_data._type == MISSILE_CARD) && card_data._value > player3_card_data._value))
				{
					setChuPaiMenuEnabled(true, true);
				}
				else
				{
					setChuPaiMenuEnabled(false, true);
				}
			}

		}
	}
}

void GameScene::gameover(int winID)
{
	_gameover = true;

	unschedule(schedule_selector(GameScene::OutCard));

	_menuChuPai->setVisible(false);
	_menuQiangDiZhu->setVisible(false);
	_menuReady->setVisible(false);

	jiesuan(winID);
}

int player1_delta_score = 0;
int player2_delta_score = 0;
int player3_delta_score = 0;
bool isPlayerWin = false;


void GameScene::jiesuan(int winID)
{
	int base_score = 100;

	player1_delta_score = 0;
	player2_delta_score = 0;
	player3_delta_score = 0;

	if (winID == 1)
	{
		isPlayerWin = true;

		if (_player1->getIsDiZhu())
		{
			player1_delta_score = base_score * 2;
			player2_delta_score = base_score * -1;
			player3_delta_score = base_score * -1;
		}
		else if (_player2->getIsDiZhu())
		{
			player1_delta_score = base_score * 1;
			player2_delta_score = base_score * -2;
			player3_delta_score = base_score * 1;
		}
		else
		{
			player1_delta_score = base_score * 1;
			player2_delta_score = base_score * 1;
			player3_delta_score = base_score * -2;
		}
	}
	else if (winID == 2)
	{
		isPlayerWin = false;

		if (_player1->getIsDiZhu())
		{
			player1_delta_score = base_score * -2;
			player2_delta_score = base_score * 1;
			player3_delta_score = base_score * 1;
		}
		else if (_player2->getIsDiZhu())
		{
			player1_delta_score = base_score * -1;
			player2_delta_score = base_score * 2;
			player3_delta_score = base_score * -1;
		}
		else
		{
			player1_delta_score = base_score * 1;
			player2_delta_score = base_score * 1;
			player3_delta_score = base_score * -2;
		}
	}
	else
	{
		isPlayerWin = false;

		if (_player1->getIsDiZhu())
		{
			player1_delta_score = base_score * -2;
			player2_delta_score = base_score * 1;
			player3_delta_score = base_score * 1;
		}
		else if (_player2->getIsDiZhu())
		{
			player1_delta_score = base_score * 1;
			player2_delta_score = base_score *  -2;
			player3_delta_score = base_score * 1;
		}
		else
		{
			player1_delta_score = base_score * -1;
			player2_delta_score = base_score * -1;
			player3_delta_score = base_score * 2;
		}
	}


	_player1->Score(player1_delta_score);
	_player2->Score(player2_delta_score);
	_player3->Score(player3_delta_score);

	s_runtimeData._playerinfo1._score = _player1->GetScore();
	s_runtimeData._playerinfo2._score = _player2->GetScore();
	s_runtimeData._playerinfo3._score = _player3->GetScore();

	auto delay = DelayTime::create(1);
	auto callback = CallFuncN::create(CC_CALLBACK_1(GameScene::callbackJieSuan, this));
	auto seq = Sequence::createWithTwoActions(delay, callback);

	this->runAction(seq);



}

void GameScene::callbackJieSuan(Node *node){

	_menuBack->setEnabled(false);
	_menuChuPai->setEnabled(false);
	_menuQiangDiZhu->setEnabled(false);
	_menuReady->setEnabled(false);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	SimpleAudioEngine::getInstance()->playEffect(isPlayerWin ? "sound/MusicEx_Win.ogg" : "sound/MusicEx_Lose.ogg");

	auto bg = Sprite::create(isPlayerWin ? "gameover/ddz_diploma_win_big_bg.jpg" : "gameover/ddz_diploma_lose_big_bg.jpg");

	bg->setScale(1.4);
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(bg, 1000);


	auto jiesuanBg = Sprite::create("gameover/bg_small.png");
	jiesuanBg->setPosition(Vec2(visibleSize.width * 2/3, visibleSize.height /2));
	this->addChild(jiesuanBg, 1001);

	auto tiaofu = Sprite::create(isPlayerWin ? "gameover/gameresult_win_tiaofu.png" : "gameover/gameresult_lose_tiaofu.png");
	tiaofu->setPosition(Vec2(350 , 400 ));
	jiesuanBg->addChild(tiaofu, 0);

	auto shengli = Sprite::createWithSpriteFrameName(isPlayerWin ? "ddz_result_base_word_win.png" : "ddz_result_base_word_lose.png");
	shengli->setPosition(Vec2(350 , 430 ));
	jiesuanBg->addChild(shengli, 0);

	auto player = Sprite::create(
		isPlayerWin ?
		(_player1->getIsDiZhu() ? "gameover/owner1_win.png" : "gameover/farmer1_win.png")
		:
		(_player1->getIsDiZhu() ? "gameover/owner1_lose.png" : "gameover/farmer1_lose.png"));
	player->setPosition(Vec2(-200 , 200));
	jiesuanBg->addChild(player, 0);

	auto label_name = Label::createWithTTF(FileUtils::getInstance()->getValueMapFromFile("strings.xml").at("name").asString(), "fonts/FZCuYuan-M03S.ttf", 24);
	label_name->setColor(Color3B(255, 0, 0));
	label_name->setPosition(Vec2(150 , 300 ));
	jiesuanBg->addChild(label_name, 1);

	// 地主标志
	auto dizhu_flag = Sprite::createWithSpriteFrameName("ddz_result_base_dizhu_flag.png");
	dizhu_flag->setPosition(Vec2(90 , _player1->getIsDiZhu() ? 250  : (_player2->getIsDiZhu() ? 200  : (_player3->getIsDiZhu() ? 150  : 0))));
	jiesuanBg->addChild(dizhu_flag, 0);

	auto label_name_player1 = Label::createWithTTF(_player1->GetName().c_str(), "fonts/FZCuYuan-M03S.ttf", 24 );
	label_name_player1->setColor(Color3B(255, 0, 0));
	label_name_player1->setPosition(Vec2(150 , 250 ));
	jiesuanBg->addChild(label_name_player1, 1);

	auto label_name_player2 = Label::createWithTTF(_player2->GetName().c_str(), "fonts/FZCuYuan-M03S.ttf", 24 );
	label_name_player2->setColor(Color3B(255, 0, 0));
	label_name_player2->setPosition(Vec2(150 , 200 ));
	jiesuanBg->addChild(label_name_player2, 1);

	auto label_name_player3 = Label::createWithTTF(_player3->GetName().c_str(), "fonts/FZCuYuan-M03S.ttf", 24 );
	label_name_player3->setColor(Color3B(255, 0, 0));
	label_name_player3->setPosition(Vec2(150 , 150 ));
	jiesuanBg->addChild(label_name_player3, 1);

	// 欢乐豆

	auto label_huanledou = Label::createWithTTF(FileUtils::getInstance()->getValueMapFromFile("strings.xml").at("score").asString(), "fonts/FZCuYuan-M03S.ttf", 24 );
	label_huanledou->setColor(Color3B(255, 0, 0));
	label_huanledou->setPosition(Vec2(350 , 300 ));
	jiesuanBg->addChild(label_huanledou, 1);

	auto label_huanledou_player1 = Label::createWithTTF(_player1->GetScoreString().c_str(), "fonts/FZCuYuan-M03S.ttf", 24 );
	label_huanledou_player1->setColor(Color3B(255, 0, 0));
	label_huanledou_player1->setPosition(Vec2(350 , 250 ));
	jiesuanBg->addChild(label_huanledou_player1, 1);

	auto label_huanledou_player2 = Label::createWithTTF(_player2->GetScoreString().c_str(), "fonts/FZCuYuan-M03S.ttf", 24 );
	label_huanledou_player2->setColor(Color3B(255, 0, 0));
	label_huanledou_player2->setPosition(Vec2(350 , 200 ));
	jiesuanBg->addChild(label_huanledou_player2, 1);

	auto label_huanledou_player3 = Label::createWithTTF(_player3->GetScoreString().c_str(), "fonts/FZCuYuan-M03S.ttf", 24 );
	label_huanledou_player3->setColor(Color3B(255, 0, 0));
	label_huanledou_player3->setPosition(Vec2(350 , 150 ));
	jiesuanBg->addChild(label_huanledou_player3, 1);

	// 分数加减
	char str_score_delta_player1[255] = { 0 };
	char str_score_delta_player2[255] = { 0 };
	char str_score_delta_player3[255] = { 0 };

	sprintf(str_score_delta_player1, "%+d", player1_delta_score);
	sprintf(str_score_delta_player2, "%+d", player2_delta_score);
	sprintf(str_score_delta_player3, "%+d", player3_delta_score);

	auto label_huanledou_d_player1 = Label::createWithTTF(str_score_delta_player1, "fonts/FZCuYuan-M03S.ttf", 24 );
	label_huanledou_d_player1->setColor(Color3B(255, 0, 0));
	label_huanledou_d_player1->setPosition(Vec2(480, 250 ));
	jiesuanBg->addChild(label_huanledou_d_player1, 1);

	auto label_huanledou_d_player2 = Label::createWithTTF(str_score_delta_player2, "fonts/FZCuYuan-M03S.ttf", 24 );
	label_huanledou_d_player2->setColor(Color3B(255, 0, 0));
	label_huanledou_d_player2->setPosition(Vec2(480 , 200 ));
	jiesuanBg->addChild(label_huanledou_d_player2, 1);

	auto label_huanledou_d_player3 = Label::createWithTTF(str_score_delta_player3, "fonts/FZCuYuan-M03S.ttf", 24 );
	label_huanledou_d_player3->setColor(Color3B(255, 0, 0));
	label_huanledou_d_player3->setPosition(Vec2(480 , 150 ));
	jiesuanBg->addChild(label_huanledou_d_player3, 1);

	// 重开菜单

	auto itemRestart = customMenuItemWithSpriteFrameName("ddzsingle_maplvl_btn_restart.png", "ddzsingle_maplvl_btn_restart.png", CC_CALLBACK_1(GameScene::menuRestartCallback, this));
	itemRestart->setPosition(200 , -150 );
	auto menuRestart = Menu::create(itemRestart, NULL);
	this->addChild(menuRestart, 1002);


}