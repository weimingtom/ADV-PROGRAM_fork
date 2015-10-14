#include "SCCharactorSpeak.h"
#include "CharactorManager.h"

ScriptReader::SCCharactorSpeak::SCCharactorSpeak(ScriptReader *reader, std::string &name, std::string &text, std::string &face)
	:cName(name)
	, face(face)
	, text(text)
{
	this->reader = reader;
	this->type = ScriptCommandType::CharactorSpeak;
}

ScriptReader::SCCharactorSpeak::~SCCharactorSpeak()
{

}

void ScriptReader::SCCharactorSpeak::execute(cocos2d::Node* stage)
{
	auto cha = CM->getCharactor(cName);	//获取角色
	if (cha)
	{
		bool isNeedShow = false;	//判断是否需要重新显示人物立绘
		if (cha->faceSprite)
		{
			if (cha->currentFace != face)
			{
				cha->leave();
				isNeedShow = true;
			}
		}
		else
		{
			isNeedShow = true;
		}


		
		if (isNeedShow)
		{
			auto pChar = &reader->chars[2];
			//auto pSprite = &reader->centerCharSprite;
			PositionType tmpPT = PositionType::EMPTY;

			Sprite *sp = nullptr;
			if (cha->getCharactorFace(face))
				sp = Sprite::create(cha->getCharactorFace(face));
			cha->faceSprite = sp;
			if (face.compare("") != 0)
			{
				if (!reader->charNumber)
				{
					reader->charNumber++;
					//pSprite = &reader->charSprites[2];
					pChar = &reader->chars[2];
					tmpPT = PositionType::CENTER;
				}
				else
					if (reader->charNumber == 1)
					{
						if (reader->chars[2] == cha)
						{
							//pSprite = &reader->charSprites[2];
							pChar = &reader->chars[2];
							tmpPT = PositionType::CENTER;
						}
						else
						{
							reader->charSprites[1] = reader->charSprites[2];
							reader->chars[2]->moveTo(PositionType::LEFT_CENTER);
							reader->chars[1] = reader->chars[2];
							reader->chars[2] = nullptr;
							reader->charNumber++;
							//pSprite = &reader->charSprites[3];
							pChar = &reader->chars[3];
							tmpPT = PositionType::RIGHT_CENTER;
						}
					}
					else
					{
						if (reader->charNumber == 2)
						{
							if (reader->chars[1] == cha)
							{
								//pSprite = &reader->charSprites[1];
								pChar = &reader->chars[1];
								tmpPT = PositionType::LEFT_CENTER;
							}
							else
								if (reader->chars[3] == cha)
								{
									//pSprite = &reader->charSprites[3];
									pChar = &reader->chars[3];
									tmpPT = PositionType::RIGHT_CENTER;
								}
								else
								{
									reader->charSprites[0] = reader->charSprites[1];
									reader->chars[1]->moveTo(PositionType::LEFT);
									reader->chars[0] = reader->chars[1];
									reader->chars[1] = nullptr;
									reader->charSprites[4] = reader->charSprites[3];
									reader->chars[3]->moveTo(PositionType::RIGHT);
									reader->chars[4] = reader->chars[3];
									reader->chars[3] = nullptr;
									reader->charNumber++;
									//pSprite = &reader->charSprites[2];
									pChar = &reader->chars[2];
									tmpPT = PositionType::CENTER;
								}
						}
						else
						{
							if (reader->chars[0] == cha)
							{
								//pSprite = &reader->charSprites[0];
								pChar = &reader->chars[0];
								tmpPT = PositionType::LEFT;
							}
							else
								if (reader->chars[2] == cha)
								{
									//pSprite = &reader->charSprites[2];
									pChar = &reader->chars[2];
									tmpPT = PositionType::CENTER;
								}
								else
									if (reader->chars[4] == cha)
									{
										//pSprite = &reader->charSprites[4];
										pChar = &reader->chars[4];
										tmpPT = PositionType::RIGHT;
									}
									else
									{
										//pSprite = &reader->charSprites[2];
										pChar = &reader->chars[2];
										tmpPT = PositionType::CENTER;
									}
						}
					}
				/*
				if (reader->leftChar == cha || (reader->nextPositionIsLeft && reader->rightChar != cha))
				{
				cha->positionIsLeft = true;
				reader->nextPositionIsLeft = false;
				}
				else
				{
				pChar = &reader->rightChar;
				pSprite = &reader->rightCharSprite;
				cha->positionIsLeft = false;
				reader->nextPositionIsLeft = true;
				}
				*/


				if (((Charactor*)*pChar))
				{
					((Charactor*)*pChar)->leave();
				}



				cha->currentPosition = tmpPT;
				if (sp)
					*pChar = cha;

				switch (tmpPT)
				{
				case PositionType::LEFT:
				{
					sp->setPositionX(320);
					break;
				}
				case PositionType::LEFT_CENTER:
				{
					sp->setPositionX(427);
					break;
				}
				case PositionType::CENTER:
				{
					sp->setPositionX(640);
					break;
				}
				case PositionType::RIGHT_CENTER:
				{
					sp->setPositionX(853);
					break;
				}
				case PositionType::RIGHT:
				{
					sp->setPositionX(960);
					break;
				}
				default:
				{
					break;
				}
				}

				sp->setAnchorPoint(Vec2(0.5, 0));

				reader->charStage->addChild(sp);
				//pSprite[0]->addChild(sp);
			}
		}
	}
	reader->showName(cha->name);
	reader->showText(text);
	log("%s",text.c_str());
}