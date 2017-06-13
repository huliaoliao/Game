#include "HolderPlayer.h"

#include "CountDownController.h"
#include "GameRule.h"
#include "HolderPlayerInstance.h"
#include "OutPokers.h"
#include "Util.h"

HolderPlayer::HolderPlayer()
{
	init();
}

bool HolderPlayer::init()
{
	//_lastOutPokers = nullptr;

	if (initContent() == false)
	{
		return false;
	}

	return true;
}

bool HolderPlayer::initContent()
{
	//ע�����ֶ���Ҵ�����������Ƶ���Ϣ
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(HolderPlayer::addPokerWaitForOutCallback, this),
		ADD_POKER_IN_HOLDER_POKERSWAITFOROUT,
		nullptr);

	//ע�����ֶ���Ҵ�������ɾ���Ƶ���Ϣ
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(HolderPlayer::deletePokerWaitForOutCallback, this),
		DELETE_POKER_IN_HOLDER_POKERSWAITFOROUT,
		nullptr);

	//ע���ֶ���ҳ��Ƶ���Ϣ
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(HolderPlayer::holderOutPokersCallback, this),
		HOLDER_OUTPOKERS,
		nullptr);

	//ע����ʾ��ť������ֶ������Ҫ������Ӧ����Ϣ
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(HolderPlayer::clickHintBtnCallback, this),
		CLICK_HINT_BTN,
		nullptr);

	return true;
}


void HolderPlayer::displayPokers()
{
// 	cocos2d::Vector<Poker*> pokers;
// 	for (int i = 0; i < _holdPokers.size(); ++i)
// 	{
// 		pokers.pushBack(&_holdPokers[i]);
// 	}

	cocos2d::NotificationCenter::getInstance()->postNotification(
		DISPLAY_HOLDER_POKERS, (cocos2d::Ref*)(&_holdPokers));
}

void HolderPlayer::callLandlord()
{
	//��ʾ�е�����ť
	cocos2d::NotificationCenter::getInstance()->postNotification(DISPLAY_CALL_LANDLORD_BTN, nullptr);
}

void HolderPlayer::outPokers(OutPokers* lastOutPokers_)
{
	CountDownController::getInstance()->startCountDown(this);
	//_pokersWaitForOut.clear();
	this->_lastOutPokers = lastOutPokers_;

	//��ȡ��ʾ���ƣ�ȷʵ��ʾ��ť�Ƿ�ɰ����Լ�"û�д�ù��ϼҵ���"�Ƿ���ʾ
	this->_hintPokers = searchOutPokers(lastOutPokers_);
	//���ڿ��Դ�ù��ϼҵ���
	if (_hintPokers.size() != 0)
	{
		//����ʾ��ť�ɰ�
		cocos2d::NotificationCenter::getInstance()->postNotification(HINT_BTN_ENABLED,
			nullptr);
	}
	else
	{
		//��ʾ"û�д�ù��ϼҵ���"
		cocos2d::NotificationCenter::getInstance()->postNotification(SHOW_PASSHINT,
			nullptr);
	}

	//������һ�ִ������
	cocos2d::NotificationCenter::getInstance()->postNotification(DESTROY_LAST_HOLDER_OUTPOKERS, nullptr);
	//��ʾ������ذ�ť
	cocos2d::NotificationCenter::getInstance()->postNotification(DISPLAY_HOLDER_OUTPOKERS_BTNS, nullptr);
}

void HolderPlayer::outPokersCallback()
{
	//��PokerLayer��ʵ�ָ��ӷ��㣬���ﲻ���κδ�������Ϊһ���ӿڱ���
}

bool HolderPlayer::isPokerWaitForOutCanOut()
{
	auto pokersType = GameRule::getInstance()->analysePokersType(_pokersWaitForOut);
	if (pokersType == NONE)
	{
		return false;
	}

	std::vector<Poker> pokers;
	//�����һ�����ǿյģ��ֶ����Ϊ��һ�ֵ�һ�������ߣ�,������һ����Ҳ���ֶ���ҵ�
	if (_lastOutPokers == nullptr || _lastOutPokers->getPokerOwner() == this)
	{
		return true;
	}
	else
	{
		return GameRule::getInstance()->canOutPokers(_pokersWaitForOut, *_lastOutPokers);
	}
}

void HolderPlayer::checkOutPokerBtnEnabled()
{
	//�жϵ�ǰѡ������Ƿ���Գ��������������ư�ť�Ƿ�ɰ���
	//������ԣ�������Ϣ����ư�ť���԰�
	if (isPokerWaitForOutCanOut())
	{
		cocos2d::NotificationCenter::getInstance()->postNotification(
			OUTPOKERS_BTN_ENABLED, nullptr);
	}
	else
	{
		cocos2d::NotificationCenter::getInstance()->postNotification(
			OUTPOKERS_BTN_DISABLED, nullptr);
	}
}

void HolderPlayer::deletePokerWaitForOutCallback(cocos2d::Ref* sender_)
{
	auto poker = dynamic_cast<Poker*>(sender_);
	if (poker == nullptr)
	{
		CCASSERT(poker != nullptr, "sender_ is nullptr");
		return;
	}
	for (auto iter = _pokersWaitForOut.begin(); iter != _pokersWaitForOut.end();)
	{
		bool isEqual = *iter == *poker;
		if (isEqual)
		{
			iter = _pokersWaitForOut.erase(iter);
		}
		else
		{
			++iter;
		}
	}
	//ɾ���Ʋ���Ҫ��������

	//�жϵ�ǰѡ������Ƿ���Գ��������������ư�ť�Ƿ�ɰ���
	//������ԣ�������Ϣ����ư�ť���԰�
	if (isPokerWaitForOutCanOut())
	{
		cocos2d::NotificationCenter::getInstance()->postNotification(
			OUTPOKERS_BTN_ENABLED, nullptr);
	}
	else
	{
		cocos2d::NotificationCenter::getInstance()->postNotification(
			OUTPOKERS_BTN_DISABLED, nullptr);
	}
}

void HolderPlayer::addPokerWaitForOutCallback(cocos2d::Ref* sender_)
{
	auto poker = dynamic_cast<Poker*>(sender_);
	if (poker == nullptr)
	{
		CCASSERT(poker != nullptr, "sender_ is nullptr!");
		return;
	}
	_pokersWaitForOut.push_back(*poker);
	util::PokerUtil::sort(_pokersWaitForOut);

	//�жϵ�ǰѡ������Ƿ���Գ��������������ư�ť�Ƿ�ɰ���
	//������ԣ�������Ϣ����ư�ť���԰�
	if (isPokerWaitForOutCanOut())
	{
		cocos2d::NotificationCenter::getInstance()->postNotification(
			OUTPOKERS_BTN_ENABLED, nullptr);
	}
	else
	{
		cocos2d::NotificationCenter::getInstance()->postNotification(
			OUTPOKERS_BTN_DISABLED, nullptr);
	}
}

void HolderPlayer::holderOutPokersCallback(cocos2d::Ref*)
{
	_outedPokers = _pokersWaitForOut;
	//��������Ʋ�Ϊ�գ�������һ����
	if (_pokersWaitForOut.size() != 0)
	{
		auto lastOutPokers = createLastOutPokers(_outedPokers);
		cocos2d::NotificationCenter::getInstance()->postNotification(UPDATE_LAST_OUTPOKERS,
			(cocos2d::Ref*)(lastOutPokers));
	}

	//����������Ϣ���ݵĴ�����ƣ���һ����ҵ���һ���ƣ�
// 	_outedPokersForPost.clear();
// 	for (int i = 0; i < _outedPokers.size(); ++i)
// 	{
// 		_outedPokersForPost.pushBack(&_outedPokers.at(i));
// 	}

	//�ڳ��е�����ɾ��Ҫ������
	for (int i = 0; i < _outedPokers.size(); ++i)
	{
		for (auto iter = _holdPokers.begin(); iter != _holdPokers.end();)
		{
			if (*iter == _outedPokers[i])
			{
				iter = _holdPokers.erase(iter);
				break;
			}
			else
			{
				iter++;
			}
		}
	}

	//����������Ϣ���ݵ���ҳ��е���
// 	_holderPokerForPost.clear();
// 	for (int i = 0; i < _holdPokers.size(); ++i)
// 	{
// 		_holderPokerForPost.pushBack(&_holdPokers.at(i));
// 	}

	//׼�����������
	_pokersWaitForOut.clear();
	//�þ���ʾ�������
	_hintPokers.clear();

// 	//��ʾ�ֶ���ҳ�����
	cocos2d::NotificationCenter::getInstance()->postNotification(DISPLAY_HOLDER_OUTPOKERS,
		reinterpret_cast<cocos2d::Ref*>(&_outedPokers));
	//�����ֶ���ҳ��е���
	cocos2d::NotificationCenter::getInstance()->postNotification(DISPLAY_HOLDER_POKERS,
		reinterpret_cast<cocos2d::Ref*>(&_holdPokers));
	//���³���˳��
	cocos2d::NotificationCenter::getInstance()->postNotification(UPDATE_OUT_ORDER, nullptr);
}

std::vector<Poker> HolderPlayer::searchOutPokers(OutPokers* lastOutPokers_)
{
	std::vector<Poker> result;

	//�����һ�������Լ���
	if (lastOutPokers_ == nullptr || lastOutPokers_->getPokerOwner() == this ||
		lastOutPokers_->getPokersType() == NONE)
	{
		result = GameRule::getInstance()->searchProperPokers(_holdPokers);
	}
	else
	{
		result = GameRule::getInstance()->calcPokersWithTypeInSplit(
			_holdPokers, lastOutPokers_->getPokersType(), &lastOutPokers_->getLowestPoker(),
			lastOutPokers_->getTotalLen());

		if (result.size() == 0) //����Ҳ�����Ӧ���ƣ�����ը��
		{
			result = GameRule::getInstance()->calcPokersWithTypeInSplit(_holdPokers, BOMB);
			if (result.size() == 0)//����Ҳ�����ͨ��ը��������ը
			{
				result = GameRule::getInstance()->calcPokersWithTypeInSplit(_holdPokers, KINGBOMB);
			}
		}
	}

	return result;
}

void HolderPlayer::clickHintBtnCallback(cocos2d::Ref*)
{
	cocos2d::NotificationCenter::getInstance()->postNotification(MAKE_HINT_POKERS_SELECTED,
		(cocos2d::Ref*)(&_hintPokers));
}
