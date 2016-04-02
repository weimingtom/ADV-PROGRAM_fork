#include "CharLabel.h"

USING_NS_CC;

CharLabel::CharLabel()
	: _pos(0)
	, _defaultDelayTime(0.04f)
	, _fadeTime(0.5f)
	, _lineHeight(0)
	, _charLabel(nullptr)
	, _x(0)
	, _y(0)
	, _defaultFontSize(20)
	, _showFinishCallback(nullptr)
	, _defaultFontColor(Color3B::BLACK)
    , _isRunning(false)
{
}


CharLabel::~CharLabel()
{
}

CharLabel* CharLabel::create(std::string text, int fontSize, std::function<void()> callback)
{
	CharLabel* ret = new CharLabel();
	if (ret && ret->init(text, fontSize))
	{
		ret->_showFinishCallback = callback;
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool CharLabel::init(std::string &text, int fontSize)
{
	_text = text;
	_defaultFontSize = fontSize;
	showNextChar();
	return true;
}

void CharLabel::setString(std::string &text)
{
	Node::removeAllChildren();
    //removeAllChildren();
	_charLabel = nullptr;
	_text = text;
	_pos = 0;
	_x = 0;
	_y = 0;
    _isRunning = true;
	showNextChar();
}

void CharLabel::finishShow()
{
	removeAllChildren();
	_charLabel = Label::createWithSystemFont(_text, "Î¢ÈíÑÅºÚ", _defaultFontSize);
	_charLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	_charLabel->setColor(_defaultFontColor);

	Node::addChild(_charLabel);
    _isRunning = false;
	if (_showFinishCallback)
	{
		_showFinishCallback();
	}
}

void CharLabel::showNextChar()
{
	if ( _text[_text.length() - 1] == 13 || _pos >= (int)_text.length())
	{
        _isRunning = false;
		if (_showFinishCallback)
		{
			auto eventSprite = Sprite::create();
			addChild(eventSprite);
			eventSprite->runAction
				(
				Sequence::create
				(
				DelayTime::create(_fadeTime),
				CallFunc::create(_showFinishCallback),
				nullptr
				)
				);
		}
		return;
	}

	auto charString = getNextChar(_text, _pos);

	if (_charLabel && _lineHeight < _charLabel->getContentSize().height)
	{
		_lineHeight = _charLabel->getContentSize().height;
	}

	while (charString.compare("\n") == 0)
	{
		_y -= _lineHeight;
		_x = 0;
		_pos += charString.length();
		charString = getNextChar(_text, _pos);
	}

	auto tmpLabel = Label::createWithSystemFont(charString, "Î¢ÈíÑÅºÚ", _defaultFontSize);
	tmpLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	Node::addChild(tmpLabel);
	tmpLabel->setColor(_defaultFontColor);

	_pos += charString.length();
	//tmpLabel->setOpacity(0);
	tmpLabel->setPosition(_x, _y);
	_x += tmpLabel->getContentSize().width;
	tmpLabel->runAction(Sequence::createWithTwoActions(DelayTime::create(_defaultDelayTime), CallFunc::create(CC_CALLBACK_0(CharLabel::showNextChar, this))));
	_charLabel = tmpLabel;
}

std::string CharLabel::getNextChar(std::string &src, int pos)
{
	if (src.length() < 1)
	{
		return std::string("");
	}

	int len = 0;
	char c = src[pos];

	if (c >= 0 && c <= 127)
	{
		len++;
	}
	else if (c < 0 && c >= -32)
	{
		len += 3;
	}
	else if (c < 0 && c >= -64)
	{
		len += 2;
	}
	else if (c < 0)
	{
		len += 1;
	}
	std::string subString = src.substr(pos, len);
	return subString;
}