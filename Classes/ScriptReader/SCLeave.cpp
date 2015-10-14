#include "SCLeave.h"
#include "CharactorManager.h"

ScriptReader::SCLeave::SCLeave(ScriptReader* reader, std::string &name)
	:cName(name)
{
	this->reader = reader;
	this->type = ScriptCommandType::Leave;
}


ScriptReader::SCLeave::~SCLeave()
{
}

void ScriptReader::SCLeave::execute(cocos2d::Node* stage)
{
	auto cha = CM->getCharactor(cName);
	if (cha->faceSprite)
	{
		cha->faceSprite->runAction(Sequence::createWithTwoActions(FadeOut::create(1.0f), CallFunc::create([=]()
		{
			if (reader->charNumber == 1)
			{
				reader->chars[2] = nullptr;
			}
			else
				if (reader->charNumber == 2)
				{
					switch (cha->currentPosition)
					{
					case PositionType::LEFT_CENTER:
					{
						reader->chars[1] = nullptr;
						reader->chars[3]->moveTo(PositionType::CENTER);
						reader->chars[2] = reader->chars[3];
						reader->chars[3] = nullptr; 
						break;
					}
					case PositionType::RIGHT_CENTER:
					{
						reader->chars[3] = nullptr;
						reader->chars[1]->moveTo(PositionType::CENTER);
						reader->chars[2] = reader->chars[1];
						reader->chars[1] = nullptr;
						break;
					}
					default:
					{
						break;
					}
					}
				}
				else
					if (reader->charNumber == 3)
					{
						switch (cha->currentPosition)
						{
						case PositionType::LEFT:
						{
							reader->chars[0] = nullptr;
							reader->chars[2]->moveTo(PositionType::LEFT_CENTER);
							reader->chars[1] = reader->chars[2];
							reader->chars[2] = nullptr;
							reader->chars[4]->moveTo(PositionType::RIGHT_CENTER);
							reader->chars[3] = reader->chars[4];
							reader->chars[4] = nullptr;
							break;
						}
						case PositionType::CENTER:
						{
							reader->chars[2] = nullptr;
							reader->chars[0]->moveTo(PositionType::LEFT_CENTER);
							reader->chars[1] = reader->chars[0];
							reader->chars[0] = nullptr;
							reader->chars[4]->moveTo(PositionType::RIGHT_CENTER);
							reader->chars[3] = reader->chars[4];
							reader->chars[4] = nullptr;
							break;
						}
						case PositionType::RIGHT:
						{
							reader->chars[4] = nullptr;
							reader->chars[0]->moveTo(PositionType::LEFT_CENTER);
							reader->chars[1] = reader->chars[0];
							reader->chars[0] = nullptr;
							reader->chars[2]->moveTo(PositionType::RIGHT_CENTER);
							reader->chars[3] = reader->chars[2];
							reader->chars[2] = nullptr;
							break;
						}
						default:
						{
							break;
						}
						}

					}
			/*
			cha->faceSprite->runAction
			(
			Sequence::createWithTwoActions
			(
			MoveBy::create(0.2f, Vec2(cha->positionIsLeft ? -400 : 400, 0)),
			CallFunc::create
			(
			[=]()
			{

			cha->leave();
			reader->charNumber--;

			reader->nextScript();
			}
			)
			)
			);
			*/
			cha->leave();
			reader->charNumber--;
			reader->nextScript();
		}
		)
			)
			);
	}
}
