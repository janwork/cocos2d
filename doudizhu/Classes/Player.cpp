#include "Player.h"
#include "GameScene.h"
#include "AppCommon.h"


Player * Player::create(std::string name, int score, bool isHero)
{
	Player * spr = new(std::nothrow) Player();
	if (spr && spr->init(name, score, isHero)){
		spr->autorelease();
		return spr;
	}

	CC_SAFE_DELETE(spr);
	return nullptr;
}

bool Player::init(std::string name, int score, bool isHero)
{

	if (!Sprite::init())
	{
		return false;
	}

	_isHero = isHero;
	_name = name;
	_score = score;
	_isDiZhu = false;


	_cardsManager = Sprite::create();
	_cardsManager->setPosition(0, -190);
	this->addChild(_cardsManager, 1);


	_labelName = Label::createWithTTF(_name, "fonts/FZCuYuan-M03S.ttf", 18);
	_labelName->setPosition(0, -70);
	this->addChild(_labelName, 1);


	auto huanledou = Sprite::create("icon_dou.png");
	huanledou->setScale(0.5);
	huanledou->setPosition(65, -70);
	this->addChild(huanledou, 0);

	_labelScore = Label::createWithTTF(this->GetScoreString().c_str(), "fonts/FZCuYuan-M03S.ttf", 18);
	_labelScore->setPosition(100, -70);
	this->addChild(_labelScore);


	auto str = FileUtils::getInstance()->getValueMapFromFile("strings.xml").at("tipinfo").asString();

	_labelTipInfo = Label::createWithTTF(str, "fonts/FZCuYuan-M03S.ttf", 18);
	_labelTipInfo->setColor(Color3B(255,255,0));
	_labelTipInfo->setPosition(550, 50);
	this->addChild(_labelTipInfo, 1);
	_labelTipInfo->setVisible(false);

	auto avatorBg = Sprite::create("avator_bg1.png");
	avatorBg->setScale(0.8);
	this->addChild(avatorBg, 0);


	char str_avator_image[255] = { 0 };
	sprintf(str_avator_image, "head/vtouxiang_%02d.png", rand() % 14 + 1);
	auto avator = Sprite::create(str_avator_image);
	this->addChild(avator, 0);


	auto back = Sprite::createWithSpriteFrameName("b/poker_back.png");
	back->setScale(0.3);
	back->setPosition(100, 0);
	this->addChild(back, 1);

	_labelPokeCount = Label::createWithTTF("0", "fonts/FZCuYuan-M03S.ttf", 130);
	_labelPokeCount->setPosition(70, 110);
	back->addChild(_labelPokeCount, 1);


	//³öÅÆÇø

	_exhibitionZone = PokeExhibitionZone::create();

	if (isHero)
	{
		_exhibitionZone->setPosition(500, 130);
	}
	else{
		_exhibitionZone->setPosition(0, -150);
	}

	this->addChild(_exhibitionZone, 1);

	return true;
}

void Player::SetPlayerID(size_t id)
{
	_id = id;
}

size_t Player::GetPlayerID()
{
	return _id;
}

bool Player::IsQiangDiZhu()
{
	return rand() % 2;
}

std::string Player::GetName()
{
	return _name;
}

int Player::GetScore()
{
	return _score;
}

std::string Player::GetScoreString()
{
	char tmp[255] = { 0 };
	sprintf(tmp, "%d", _score);
	return std::string(tmp);
}

void Player::Score(int delta_score)
{
	_score += delta_score;

	_labelScore->setString(this->GetScoreString().c_str());

}

void Player::setDiZhu()
{
	_isDiZhu = true;

	if (_isDiZhu){
		auto lord = Sprite::create("flag_lord.png");
		lord->setPosition(160, 0);
		this->addChild(lord);
	}
}

void Player::FaPai(GameScene * scene, PokeInfo info)
{
	   _vecPokeInfo.push_back(info);

		if (_isHero)
		{
			Poke* card = Poke::create(info, !_isHero);
			_cardsManager->addChild(card, 100 - info._num);
			card->SetTouchEnabled();
			card->setGameMain(scene);
		}

		_cardsManager->sortAllChildren();

		this->updateCards();
}

void Player::ShowTipInfo(bool isFollow, CARD_TYPE cardType, unsigned int count, unsigned int value)
{
	for (int i = 0; i < _cardsManager->getChildren().size(); i++)
	{
		Poke * card = dynamic_cast<Poke*>(_cardsManager->getChildren().at(i));

		if (card != NULL)
		{
			card->unSelect();
		}
	}

		//²éÑ¯

		std::vector<int>& vec = isFollow ? FindFollowCards(cardType, count, value) : FindOutCards();
	
		if (vec.empty())
		{
			_labelTipInfo->setVisible(true);
		}
		else
		{
			_labelTipInfo->setVisible(false);


			for (int j = 0; j < vec.size(); j++)
			{
				for (auto it = _cardsManager->getChildren().begin(); it != _cardsManager->getChildren().end(); it++)
				{
					Poke* card = dynamic_cast<Poke*>(*it);

					if (card != NULL && !card->isSelected() && card->getInfo()._num == vec[j])
					{
						card->Select();
						break;
					}
				}
			}
		}
}

int s_index_sound_buyao = 0;
int s_index_sound_dani = 0;

void Player::ChuPai(GameScene *scene, bool isFollow, CARD_TYPE cardType, unsigned int count, unsigned int value)
{
	clearCards();
	_vecOutCards.clear();

	if (_isHero)
	{
		for (auto it = _cardsManager->getChildren().begin(); it != _cardsManager->getChildren().end(); it++)
		{
			Poke* card = dynamic_cast<Poke*>(*it);
			if (card != NULL && card->isSelected())
			{
				_vecOutCards.push_back(card->getInfo());
			}
		}


		//´ÓÊÖÅÆÖÐÉ¾³ý

		for (int j = 0; j < _vecOutCards.size(); j++)
		{
			for (auto it = _cardsManager->getChildren().begin(); it != _cardsManager->getChildren().end(); it++)
			{

				Poke* card = dynamic_cast<Poke*>(*it);
				if (card != NULL && card->getInfo() == _vecOutCards.at(j))
				{
					_vecPokeInfo.erase(std::find(_vecPokeInfo.begin(), _vecPokeInfo.end(), card->getInfo()));
					_cardsManager->removeChild(card, true);
					break;
				}
			}
		}

	}
	else
	{
		std::vector<int> vec = isFollow ? FindFollowCards(cardType, count, value) : FindOutCards();
		if (vec.empty())
		{
			_exhibitionZone->chuPai(_vecOutCards);
		}
		else
		{
			for (int i=0; i<vec.size(); i++)
			{
				PokeInfo info;
				info._num = (PokeNum)vec[i];
				info._tag = (PokeTag)0;
				_vecOutCards.push_back(info);
			}


			for (int j = 0; j < _vecOutCards.size(); j++)
			{
				for (int i = 0; i != _vecPokeInfo.size(); i++)
				{
					if (_vecOutCards.at(j)._num == _vecPokeInfo.at(i)._num)
					{
						_vecOutCards.at(j)._tag = _vecPokeInfo.at(i)._tag;

						_vecPokeInfo.erase(std::find(_vecPokeInfo.begin(), _vecPokeInfo.end(), _vecOutCards.at(j)));
						break;
					}
				}


				for (auto it = _cardsManager->getChildren().begin(); it != _cardsManager->getChildren().end(); it++)
				{
					Poke* card = dynamic_cast<Poke*>(*it);
					if (card != NULL && card->getInfo()._num == _vecOutCards.at(j)._num)
					{
						_cardsManager->removeChild(card, true);
						break;
					}
				}
			}
		}
	}


	CARDS_DATA vecOutCardsData = PanDuanPaiXing(_vecOutCards);

	if (isFollow)
	{
		if (vecOutCardsData._cards.empty())
		{
			char str_music[255] = { 0 };
			sprintf(str_music, "sound/Man/buyao%d.ogg", s_index_sound_buyao % 4 + 1);
			SimpleAudioEngine::getInstance()->playEffect(str_music);
			s_index_sound_buyao++;
		}
		else
		{
			if (vecOutCardsData._type == BOMB_CARD || vecOutCardsData._type == MISSILE_CARD)
			{
				std::vector<int> vec;
				for (int i = 0; i < _vecOutCards.size(); i++)
				{
					vec.push_back(_vecOutCards[i]._num);
				}
				PlayEffectForCards(vec);
			}
			else
			{
				char str_music[255] = {0};
				sprintf(str_music, "sound/Man/dani%d.ogg", s_index_sound_dani%3 + 1);
				SimpleAudioEngine::getInstance()->playEffect(str_music);
				s_index_sound_dani++;
			}
		}
	}
	else
	{
		std::vector<int> vec;
		for (int i = 0; i < _vecOutCards.size(); i++)
		{
			vec.push_back(_vecOutCards[i]._num);
		}
		PlayEffectForCards(vec);
	}

	_exhibitionZone->chuPai(_vecOutCards);

	updateCards();

	if (_vecPokeInfo.empty())
	{
		scene->gameover(_id);
	}
}


void Player::PlayEffectForCards(std::vector<int> & vec)
{
	CARDS_DATA vecOutCardsData = PanDuanPaiXing(_vecOutCards);

	switch (vecOutCardsData._type)
	{
	case SINGLE_CARD://µ¥ÅÆ	
	{
		char str_music[255] = { 0 };
		sprintf(str_music, "sound/Man/%d.ogg", vec.at(0) + 1);
		SimpleAudioEngine::getInstance()->playEffect(str_music);
	}
	break;
	case DOUBLE_CARD://¶Ô×Ó
	{
		char str_music[255] = { 0 };
		sprintf(str_music, "sound/Man/dui%d.ogg", vec.at(0) + 1);
		SimpleAudioEngine::getInstance()->playEffect(str_music);
	}
	break;
	case THREE_CARD://3²»´ø
	{
		char str_music[255] = { 0 };
		sprintf(str_music, "sound/Man/tuple%d.ogg", vec.at(0) + 1);
		SimpleAudioEngine::getInstance()->playEffect(str_music);
	}
	break;
	case BOMB_CARD://Õ¨µ¯
		SimpleAudioEngine::getInstance()->playEffect("sound/Man/zhadan.ogg");
		break;
	case MISSILE_CARD://»ð¼ý
		SimpleAudioEngine::getInstance()->playEffect("sound/Man/wangzha.ogg");
		break;
	case THREE_ONE_CARD://3´ø1
		SimpleAudioEngine::getInstance()->playEffect("sound/Man/sandaiyi.ogg");
		break;
	case THREE_TWO_CARD://3´ø2
		SimpleAudioEngine::getInstance()->playEffect("sound/Man/sandaiyidui.ogg");
		break;
	case BOMB_TWO_CARD://ËÄ¸ö´ø2ÕÅµ¥ÅÆ
		SimpleAudioEngine::getInstance()->playEffect("sound/Man/sidaier.ogg");
		break;
	case BOME_TWOOO_CARD	://四个�?�?
		SimpleAudioEngine::getInstance()->playEffect("sound/Man/sidailiangdui.ogg");
		break;
	case CONNECT_CARD://Á¬ÅÆ
		SimpleAudioEngine::getInstance()->playEffect("sound/Man/shunzi.ogg");
		break;
	case COMPANY_CARD://Á¬¶Ó
		SimpleAudioEngine::getInstance()->playEffect("sound/Man/liandui.ogg");
		break;
	case AIRCRAFT_CARD://·É»ú²»´ø
		SimpleAudioEngine::getInstance()->playEffect("sound/Man/feiji.ogg");
		break;
	case AIRCRAFT_SINGLE_CARD://·É»ú´øµ¥ÅÆ
		SimpleAudioEngine::getInstance()->playEffect("sound/Man/feiji.ogg");
		break;
	case AIRCRAFT_DOUBLE_CARD://·É»ú´ø¶Ô×Ó
		SimpleAudioEngine::getInstance()->playEffect("sound/Man/feiji.ogg");
		break;
	default:
	{

	}
	break;
	}
}

std::vector<int>& Player::FindOutCards()
{
	_vecFindFollowCards.clear();

	int index_company_card = -1;
	int count_company_card = 0;

	for (int i = 0; i < _allCardGroups.size(); i++)
	{
		if (_allCardGroups[i]._type == COMPANY_CARD && count_company_card < _allCardGroups[i]._cards.size())
		{
			count_company_card = _allCardGroups[i]._cards.size();
			index_company_card = i;
		}
	}

	if (index_company_card != -1)
	{
		return _allCardGroups[index_company_card]._cards;
	}

	int index_connect_card = -1;
	int count_connect_card = 0;

	for (int i = 0; i < _allCardGroups.size(); i++)
	{
		if (_allCardGroups[i]._type == CONNECT_CARD && count_connect_card < _allCardGroups[i]._cards.size())
		{
			count_connect_card = _allCardGroups[i]._cards.size();
			index_connect_card = i;
		}
	}

	if ( index_connect_card != -1)
	{
		return _allCardGroups[index_connect_card]._cards;
	}


	for (int i = 0; i < _allCardGroups.size(); i++)
	{
		if (_allCardGroups[i]._type == THREE_CARD)
		{
			for (int j = 0; j < _allCardGroups.size(); j++)
			{
				if (_allCardGroups[j]._type == SINGLE_CARD)
				{
					_vecFindFollowCards.push_back(_allCardGroups[i]._cards[0]);
					_vecFindFollowCards.push_back(_allCardGroups[i]._cards[0]);
					_vecFindFollowCards.push_back(_allCardGroups[i]._cards[0]);
					_vecFindFollowCards.push_back(_allCardGroups[j]._cards[0]);
					return _vecFindFollowCards;
				}
			}

			return _allCardGroups[i]._cards;
		}
	}

	for (int i = 0; i < _allCardGroups.size(); i++)
	{
		if (_allCardGroups[i]._type == DOUBLE_CARD)
		{
			return _allCardGroups[i]._cards;
		}
	}

	for (int i = 0; i < _allCardGroups.size(); i++)
	{
		if (_allCardGroups[i]._type == SINGLE_CARD)
		{
			return _allCardGroups[i]._cards;
		}
	}

	for (int i = 0; i < _allCardGroups.size(); i++)
	{
		if (_allCardGroups[i]._type == BOMB_CARD)
		{
			return _allCardGroups[i]._cards;
		}
	}


	for (int i = 0; i < _allCardGroups.size(); i++)
	{
		if (_allCardGroups[i]._type == MISSILE_CARD)
		{
			return _allCardGroups[i]._cards;
		}
	}

	std::vector<int> tmp;
	return tmp;
}

std::vector<int>& Player::FindFollowCards(CARD_TYPE cardType, unsigned int count, unsigned int value)
{
	_vecFindFollowCards.clear();

	for (int i = 0; i < _allCardGroups.size(); i++)
	{
		if (_allCardGroups[i]._value <= value){
			continue;
		}

		if (cardType == _allCardGroups[i]._type)
		{
			if (cardType == CONNECT_CARD || cardType == COMPANY_CARD || cardType == AIRCRAFT_CARD)
			{
				if (count == _allCardGroups[i]._cards.size())
				{
					return _allCardGroups[i]._cards;
				}
			}
			else
			{
				return _allCardGroups[i]._cards;
			}
		}
		else
		{
			if (cardType == THREE_ONE_CARD)
			{
				if (_allCardGroups[i]._type == THREE_CARD)
				{
					for (int j = 0; j < _allCardGroups.size(); j++)
					{
						if (_allCardGroups[j]._type == SINGLE_CARD)
						{
							_vecFindFollowCards.push_back(_allCardGroups[i]._cards[0]);
							_vecFindFollowCards.push_back(_allCardGroups[i]._cards[0]);
							_vecFindFollowCards.push_back(_allCardGroups[i]._cards[0]);
							_vecFindFollowCards.push_back(_allCardGroups[j]._cards[0]);
							return _vecFindFollowCards;
	
						}
					}
				}
			}
			else if (cardType == THREE_TWO_CARD)
			{
				if (_allCardGroups[i]._type == THREE_CARD)
				{
					for (int j = 0; j < _allCardGroups.size(); j++)
					{
						if (_allCardGroups[j]._type == DOUBLE_CARD && _allCardGroups[i]._cards[0] != _allCardGroups[j]._cards[0])
						{
							_vecFindFollowCards.push_back(_allCardGroups[i]._cards[0]);
							_vecFindFollowCards.push_back(_allCardGroups[i]._cards[0]);
							_vecFindFollowCards.push_back(_allCardGroups[i]._cards[0]);
							_vecFindFollowCards.push_back(_allCardGroups[j]._cards[0]);
							_vecFindFollowCards.push_back(_allCardGroups[j]._cards[1]);
							return _vecFindFollowCards;
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < _allCardGroups.size(); i++)
	{
		if (_allCardGroups[i]._value <= value){
			continue;
		}

		if (BOMB_CARD == _allCardGroups[i]._type){
			return _allCardGroups[i]._cards;
		}
	}

	for (int i = 0; i < _allCardGroups.size(); i++)
	{
		if (MISSILE_CARD == _allCardGroups[i]._type)
		{
			return _allCardGroups[i]._cards;
		}
	}

	return _vecFindFollowCards;
}

std::vector<PokeInfo> & Player::GetOutCards()
{
	return _vecOutCards;
}

void Player::updateCards()
{
	this->ChaiPai();

	std::stringstream text;

	text << _vecPokeInfo.size();
	_labelPokeCount->setString(text.str());
	

	int count = _cardsManager->getChildren().size();
	int zeroPoint = count / 2;
	for (int i = 0; i < count; i++)
	{
		Poke* card = dynamic_cast<Poke*>(_cardsManager->getChildren().at(i));
		if (card != NULL)
		{
			card->setPosition(550 + (i - zeroPoint) * 50, card->getPosition().y);
		}
	}
}

void Player::clearCards()
{
	_exhibitionZone->removeAllChildrenWithCleanup(true);
}

void Player::BuChu()
{
	_labelTipInfo->setVisible(false);
	clearCards();

	_vecOutCards.clear();

	for (int i = 0; i < _cardsManager->getChildren().size(); i++)
	{
		Poke* card = dynamic_cast<Poke *>(_cardsManager->getChildren().at(i));
		if (card != NULL)
		{
			card->unSelect();
		}
	}
}

void Player::ChaiPai()
{
	// ÅÆÖµ

	//			×îÐ¡ÅÆ»ù´¡Öµ	Ã¿´óÒ»µã¼ÓÒ»
	// µ¥ÕÅ		0	+	1
	// ¶Ô×Ó		20	+	1
	// Èý´ø		40	+	1
	// µ¥Ë³		60	+	1
	// Ë«Ë³		80	+	1
	// Õ¨µ¯		100	+	1
	// »ð¼ý		120

	_allCardGroups.clear();

	std::vector<int> vec_poke;
	for (int i = 0; i < _vecPokeInfo.size(); i++)
	{
		vec_poke.push_back(_vecPokeInfo[i]._num);
	}

	std::sort(vec_poke.begin(), vec_poke.end());

	std::vector<int> card_i;
	std::vector<int> card_ii;
	std::vector<int> card_iii;
	std::vector<int> card_iiii;


	for (int i = 0; i < vec_poke.size(); i++)
	{
		auto itor_find_i = std::find(card_i.begin(), card_i.end(), vec_poke[i]);

		if (itor_find_i != card_i.end())
		{
			auto itor_find_ii = std::find(card_ii.begin(), card_ii.end(), vec_poke[i]);

			if (itor_find_ii != card_ii.end())
			{
				auto itor_find_iii = std::find(card_iii.begin(), card_iii.end(), vec_poke[i]);
				// 找到�?
				if (itor_find_iii != card_iii.end())
				{
					card_iiii.push_back(vec_poke[i]);
				}
				else
				{
					card_iii.push_back(vec_poke[i]);

				}
			}
			else
			{
				card_ii.push_back(vec_poke[i]);
			}
			
		}
		else
		{
			card_i.push_back(vec_poke[i]);
		}
		vec_poke[i];
	}

	std::sort(card_i.begin(), card_i.end());
	std::sort(card_ii.begin(), card_ii.end());
	std::sort(card_iii.begin(), card_iii.end());
	std::sort(card_iiii.begin(), card_iiii.end());

	auto iter_xw = std::find(card_i.begin(), card_i.end(), NUM_XW);
	auto iter_dw = std::find(card_i.begin(), card_i.end(), NUM_DW);

	if (iter_xw != card_i.end() && iter_dw != card_i.end())
	{
		CARDS_DATA temp;

		temp._cards.push_back(NUM_XW);
		temp._cards.push_back(NUM_DW);
		temp._type = MISSILE_CARD;
		temp._value = 120;

		_allCardGroups.push_back(temp);
	}


	for (int i = 0; i < card_iiii.size(); i++)
	{
		CARDS_DATA temp;
		temp._cards.push_back(card_iiii[i]);
		temp._cards.push_back(card_iiii[i]);
		temp._cards.push_back(card_iiii[i]);
		temp._cards.push_back(card_iiii[i]);

		temp._type = BOMB_CARD;
		temp._value = 100 + card_iiii[i];
		_allCardGroups.push_back(temp);


	}

	for (int i = 0; i < card_iii.size(); i++)
	{
		CARDS_DATA temp;
		temp._cards.push_back(card_iii[i]);
		temp._cards.push_back(card_iii[i]);
		temp._cards.push_back(card_iii[i]);
		temp._type = THREE_CARD;
		temp._value = 40 + card_iii[i];

		_allCardGroups.push_back(temp);

	}

	for (int i = 0; i < card_ii.size(); i++)
	{
		CARDS_DATA temp;
		temp._cards.push_back(card_ii[i]);
		temp._cards.push_back(card_ii[i]);
		temp._type = DOUBLE_CARD;
		temp._value = 20 + card_ii[i];

		_allCardGroups.push_back(temp);

	}

	for (int i = 0; i < card_i.size(); i++)
	{
		bool is_in_link = false;
		for (int j = 4; j < card_i.size(); j++)
		{
			if (i + j < card_i.size() && card_i[i + j] - card_i[i] == j && card_i[i + j] <= NUM_A)
			{
				CARDS_DATA temp;
				temp._type = CONNECT_CARD;
				temp._value = 60 + card_i[i];
				for (int k = 0; k <= j; k++)
				{
					temp._cards.push_back(card_i[i + k]);
				}

				_allCardGroups.push_back(temp);

				is_in_link = true;
			}
		}

		CARDS_DATA temp;
		temp._cards.push_back(card_i[i]);
		temp._type = SINGLE_CARD;
		temp._value = 0 + card_i[i];


		_allCardGroups.push_back(temp);
	}

	for (int i = 0; i < card_ii.size(); i++)
	{
		for (int j = 2; j < card_ii.size(); j++)
		{
			if (i + j < card_ii.size() && card_ii[i+j] - card_ii[i] == j && card_ii[i+j] <= NUM_A)
			{
				CARDS_DATA temp;
				temp._type = COMPANY_CARD;
				temp._value = 80 + card_ii[i];
				for (int k = 0; k <= j; k++)
				{
					temp._cards.push_back(card_ii[i + k]);
					temp._cards.push_back(card_ii[i + k]);
				}

				_allCardGroups.push_back(temp);
			}
		}
	}
}

