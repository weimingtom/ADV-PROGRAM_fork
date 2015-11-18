#include "SCCharactorSpeak.h"
#include "CharactorManager.h"
#include "GameSystem.h"

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
	/*
	auto cha = CM->getCharactor(cName);	//��ȡ��ɫ
	if (cha)
	{
		bool isNeedShow = false;	//�ж��Ƿ���Ҫ������ʾ��������
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
			PositionType tmpPT = PositionType::EMPTY;

			Sprite *sp = nullptr;
			if (cha->getCharactorFace(face))
				sp = Sprite::create(cha->getCharactorFace(face));
			cha->faceSprite = sp;

			int flag = reader->charNumber; //��ʱ���µ�ǰ��Ļ��������

			if (face.compare("") != 0)
			{
				if (!reader->charNumber)
				{
					reader->charNumber++;
					pChar = &reader->chars[2];
					tmpPT = PositionType::CENTER;
				}
				else
					if (reader->charNumber == 1)
					{
						if (reader->chars[2] == cha)
						{
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
								pChar = &reader->chars[1];
								tmpPT = PositionType::LEFT_CENTER;
							}
							else
								if (reader->chars[3] == cha)
								{
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
									pChar = &reader->chars[2];
									tmpPT = PositionType::CENTER;
								}
						}
						else
						{
							if (reader->chars[0] == cha)
							{
								pChar = &reader->chars[0];
								tmpPT = PositionType::LEFT;
							}
							else
								if (reader->chars[2] == cha)
								{
									pChar = &reader->chars[2];
									tmpPT = PositionType::CENTER;
								}
								else
									if (reader->chars[4] == cha)
									{
										pChar = &reader->chars[4];
										tmpPT = PositionType::RIGHT;
									}
									else
									{
										pChar = &reader->chars[2];
										tmpPT = PositionType::CENTER;
									}
						}
					}


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

				if (flag != reader->charNumber)	//�������ȣ�˵�����������ˣ���GameSystem�м�¼
				{
					GameSystem::getInstance()->getGameSceneInfo().push(cName, face);
				}

				reader->charStage->addChild(sp);
			}
		}
	}
	*/
    auto cha = CM->getCharactor(cName);
	reader->showCharator(cName, face);
	reader->showName(cha->name);
	reader->showText(text);
	cocos2d::log("%s",text.c_str());
}