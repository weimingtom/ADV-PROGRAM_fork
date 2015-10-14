#include "SCSelect.h"


ScriptReader::SCSelect::SCSelect(ScriptReader *reader)
{
	this->reader = reader;
	this->type = ScriptCommandType::Select;
}


ScriptReader::SCSelect::~SCSelect()
{
}

void ScriptReader::SCSelect::addOption(std::string &sign, std::string &text)
{
	options.insert(std::pair<std::string, std::string>(sign, text));
}


void ScriptReader::SCSelect::execute(Node* stage)
{
	reader->isWaitingForSelection = true;

	auto menu = Menu::create();
	int startY = options.size()*(60) / 2;
	int size = options.size();
	log("Select::> optionSize[%d]", options.size());
	for (auto itr = options.begin(); itr != options.end(); itr++)
	{
		auto label = Label::createWithSystemFont(itr->second, "MSYH", 20);
		label->setColor(Color3B::WHITE);
		log("OPTION[%s] SIGN[%s]", itr->second.c_str(), itr->first.c_str());
		auto button = MenuItemLabel::create(label, [=](Ref*)
		{
			reader->jumpToSign((std::string)itr->first);
			menu->removeFromParent();
		});

		menu->addChild(button);
		button->setPosition(0, startY);
		startY -= 60;
	}
	stage->addChild(menu);
}