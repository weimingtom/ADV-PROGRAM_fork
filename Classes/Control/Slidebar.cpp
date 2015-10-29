#include "Slidebar.h"


Slidebar::Slidebar(Sprite* backgroundSprite, Sprite* pointSprite)
{
	_background = backgroundSprite;
	this->addChild(_background);
	_point = pointSprite;
	this->addChild(_point);
	_maxValue = 100;
	_minValue = 0;
	_targetValue = nullptr;
}


Slidebar::~Slidebar()
{
}

Slidebar* Slidebar::createSlidebar(std::string backgroundFile, std::string pointFile)
{
	auto tmpBackgroundSprite = Sprite::create(backgroundFile);
	auto tmpPointSprite = Sprite::create(pointFile);
	if (tmpBackgroundSprite && tmpPointSprite)
	{
		auto tmpSliderbar = new Slidebar(tmpBackgroundSprite, tmpPointSprite);
		return tmpSliderbar;
	}
	else
	{
		if (!tmpBackgroundSprite) log("Sliderbar background file (%s) not found.", backgroundFile.c_str());
		if (!tmpPointSprite) log("Sliderbar point file (%s) not found.", pointFile.c_str());
		return nullptr;
	}
}

EventListenerTouchOneByOne* Slidebar::createControlEvent()
{

}