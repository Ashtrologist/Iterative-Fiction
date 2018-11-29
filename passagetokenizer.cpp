///
// Created by Ashton Rodriquez on 11/16/18.
//

#include "passagetokenizer.h"
#include <string>
#include <iostream>
using namespace std;

PassageTokenizer::PassageTokenizer(string sentence) {
    text = text + sentence;
    currLocation = text.find(">") + 1;
}


string SectionToken::getText() const {
    return sectionText;
}


//Is there an error here? WHy am I getting an endless loop
bool PassageTokenizer::hasNextSection() {

    if (text.find("(set:", currLocation) != string::npos) {
        return true;
    }

    else if (text.find("(go-to:", currLocation) != string::npos) {
        return true;
    }

    else if (text.find("(if:", currLocation) != string::npos) {
        return true;
    }

    else if (text.find("(else-if:", currLocation) != string::npos) {
        return true;
    }

    else if (text.find("(else:", currLocation) != string::npos) {
        return true;
    }
    else if (text.find("[[", currLocation) != string::npos) {
        return true;
    }
    else if (text.substr(currLocation, 1) != "<") {
        return true;
    }
    else {
        return false;
    }
}

SectionToken PassageTokenizer::nextSection() {
	int tempLocation;
	command_t command;

	if ((text.substr(currLocation, 1) != "(") && (text.substr(currLocation, 1) != "[")) {
        command = TEXT;
        tempLocation = currLocation;

        if ((text.find("(", currLocation) == string::npos) && (text.find("[", currLocation) == string::npos)) {
            currLocation = text.find("<", currLocation);
        }
        else if (text.find("(", currLocation) < text.find("[", currLocation)) {
            currLocation = text.find("(", currLocation);
        }
        else {
            currLocation = text.find("[", currLocation);
        }
    }
    else if (text.substr(currLocation, 5) == "(set:") {
        command = SET;
        tempLocation = text.find("(set:", currLocation);
        currLocation = text.find(")", tempLocation) + 1;
    }
    else if (text.substr(currLocation, 7) == "(go-to:") {
        command = GOTO;
        tempLocation = text.find("(go-to:", currLocation);
        currLocation = text.find(")", tempLocation) + 1;
    }
    else if (text.substr(currLocation, 4) == "(if:") {
        command = IF;
        tempLocation = text.find("(if:", currLocation);
        currLocation = text.find(")", tempLocation) + 1;
    }
    else if (text.substr(currLocation, 9) == "(else-if:") {
        command = ELSEIF;
        tempLocation = text.find("(else-if:", currLocation);
        currLocation = text.find(")", tempLocation) + 1;
    }
    else if (text.substr(currLocation, 6) == "(else:") {
        command = ELSE;
        tempLocation = text.find("(else:", currLocation);
        currLocation = text.find(")", tempLocation) + 1;
    }
    else if (text.substr(currLocation, 2) == "[[") {
        command = LINK;
        tempLocation = text.find("[[", currLocation);
        currLocation = text.find("]]", tempLocation) + 2;
    }
        //(text.find("(else:", currLocation) < text.find("]", currLocation) && text.find("else:", currLocation) != string::npos)
    else {
        command = BLOCK;
        tempLocation = currLocation;
        while(text.find("[[", currLocation) != string::npos && text.find("[[", currLocation) < text.find("]", currLocation)){
            currLocation = text.find("]]", currLocation) + 2;
            while((text.find("(if:", currLocation) < text.find("]", currLocation) && text.find("(if:", currLocation) != string::npos) || (text.find("(else-if:", currLocation) < text.find("]", currLocation) && text.find("else-if:", currLocation) != string::npos) || (text.find("(else:", currLocation) < text.find("]", currLocation) && text.find("else:", currLocation) != string::npos)){
                currLocation = text.find("]", currLocation) + 1;
            }
        }
        while((text.find("(if:", currLocation) < text.find("]", currLocation) && text.find("(if:", currLocation) != string::npos) || (text.find("(else-if:", currLocation) < text.find("]", currLocation) && text.find("else-if:", currLocation) != string::npos) || (text.find("(else:", currLocation) < text.find("]", currLocation) && text.find("else:", currLocation) != string::npos)){
            currLocation = text.find("]", currLocation) + 1;
            while(text.find("[[", currLocation) != string::npos && text.find("[[", currLocation) < text.find("]", currLocation)){
                currLocation = text.find("]]", currLocation) + 2;
            }
        }
        currLocation = text.find("]", currLocation) + 1;
    }

	//I dont know what text should be instead
    SectionToken stok(text.substr(tempLocation, currLocation - tempLocation), command);
    return stok;
}

SectionToken::SectionToken(string& section)
{
	sectionText = section;
}



Command::Command()
{
	text = "";
	type = NULLT;
}

//Command Class Functions
Command::Command(SectionToken& st)//constructor
{
	text = st.getText();
	type = NULLT;
}

string Command::getText() const
{
	return text;
}

command_t Command::getType() const
{
	return type;
}




Link::Link(SectionToken & stok) {//Working on LINK class ***************//

	type = LINK;
	location = 0;
	if (stok.getText().find("-&gt;", location) != string::npos)

	{

		location = stok.getText().find("-&gt;", location);
		text = stok.getText().substr(2, location - 2);

		location += 5;

		sectionName = stok.getText().substr(location, stok.getText().length() - location - 2);

	}

	else {

		text = stok.getText().substr(2, stok.getText().length() - 4);

		sectionName = text;

	}
}

string Link::getPassageName() const
{
	return sectionName;
}

Text::Text(SectionToken& stok) {
	type = TEXT;
}

Goto::Goto(SectionToken& stok) {
	type = GOTO;
	location = stok.getText().find("&quot;") + 6;
	sectionName = stok.getText().substr(location, stok.getText().find("&quot;", location) - location);
}

string Goto::getPassageName() const
{
	return sectionName;
}

Set::Set(SectionToken & stok)
{
	type = SET;
	location = stok.getText().find("$") + 1;
	text = stok.getText().substr(location, stok.getText().find(" to ", location) - location);

	location = stok.getText().find(" to ", location) + 4;
	if (stok.getText().substr(location, 4) == "true") {
		setBool = true;
	}

	else {
		setBool = false;
	}
}

bool Set::getBool() const
{
	return setBool;
}

If::If(SectionToken & stok)
{
	type = IF;
	location = stok.getText().find("$") + 1;
	text = stok.getText().substr(location, stok.getText().find(" is ", location) - location);

	location = stok.getText().find(" is ", location) + 4;
	if (stok.getText().substr(location, 4) == "true") {
		checkSet = true;
	}
	else {
		checkSet = false;
	}
}

bool If::getSetValue() const
{
	return checkSet;
}

Elseif::Elseif(SectionToken & stok)
{
	type = ELSEIF;
	location = stok.getText().find("$") + 1;
	text = stok.getText().substr(location, stok.getText().find(" is ", location) - location);

	location = stok.getText().find(" is ", location) + 4;
	if (stok.getText().substr(location, 4) == "true") {
		checkSet = true;
	}
	else {
		checkSet = false;
	}
}

bool Elseif::getSetValue() const
{
	return checkSet;
}

Else::Else(SectionToken & stok)
{
	type = ELSE;
}

BlockTokenizer::BlockTokenizer()
{
}

bool BlockTokenizer::hasNextSection(Block & block)
{
	if (bl.getText().find("(set:", bl.blIndex) != string::npos) {
		return true;
	}
	else if (bl.getText().find("(go-to:", bl.blIndex) != string::npos) {
		return true;
	}
	else if (bl.getText().find("(if:", bl.blIndex) != string::npos) {
		return true;
	}
	else if (bl.getText().find("(else-if:", bl.blIndex) != string::npos) {
		return true;
	}
	else if (bl.getText().find("(else:", bl.blIndex) != string::npos) {
		return true;
	}
	else if (bl.getText().find("[[", bl.blIndex) != string::npos) {
		return true;
	}
	else if (bl.getText().substr(bl.blIndex, 1) != "]") {
		return true;
	}
	else {
		return false;
	}
}

void BlockTokenizer::nextSection(Block& block)
{
	int sectionBeginning;
	string stokenText;

	while (bl.getText().substr(bl.blIndex, 1) == "\n")
	{
		bl.blIndex++;



		//test to see if the next section is a Text Section.
		if ((bl.getText().substr(bl.blIndex, 1) != "(") && (bl.getText().substr(bl.blIndex, 1) != "["))
		{
			sectionBeginning = bl.blIndex;


			if ((bl.getText().find("(", bl.blIndex) == string::npos) && (bl.getText().find("[", bl.blIndex) == string::npos))
			{
				bl.blIndex = bl.getText().find("]", bl.blIndex);
			}
			else if (bl.getText().find("(", bl.blIndex) < bl.getText().find("[", bl.blIndex))
			{
				bl.blIndex = bl.getText().find("(", bl.blIndex);
			}
			else
			{
				bl.blIndex = bl.getText().find("[", bl.blIndex);
			}
			stokenText = bl.getText().substr(sectionBeginning, bl.blIndex - sectionBeginning);
			SectionToken stok(stokenText);
			Text text(stok);
			bl.addSection(text);
		}
		else if (bl.getText().substr(bl.blIndex, 3) == "[[[")
		{
			int counter = 1;
			sectionBeginning = bl.blIndex;
			bl.blIndex++;
			while (counter != 0) {
				if (bl.getText().at(bl.blIndex) == '[') {
					counter++;
				}
				if (bl.getText().at(bl.blIndex) == ']') {
					counter--;
				}
				bl.blIndex++;
			}
			stokenText = bl.getText().substr(sectionBeginning, bl.blIndex - sectionBeginning);
			SectionToken stok(stokenText);
			Block block(stok);
			bl.addSection(block);
		}
		else if (bl.getText().substr(bl.blIndex, 5) == "(set:")
		{
			sectionBeginning = bl.getText().find("(set:", bl.blIndex);
			bl.blIndex = bl.getText().find(")", sectionBeginning) + 1;
			stokenText = bl.getText().substr(sectionBeginning, bl.blIndex - sectionBeginning);
			SectionToken stok(stokenText);
			Set set(stok);
			bl.addSection(set);
		}
		else if (bl.getText().substr(bl.blIndex, 7) == "(go-to:")
		{
			sectionBeginning = bl.getText().find("(go-to:", bl.blIndex);
			bl.blIndex = bl.getText().find(")", sectionBeginning) + 1;
			stokenText = bl.getText().substr(sectionBeginning, bl.blIndex - sectionBeginning);
			SectionToken stok(stokenText);
			Goto go_to(stok);
			bl.addSection(go_to);
		}
		else if (bl.getText().substr(bl.blIndex, 4) == "(if:")
		{
			sectionBeginning = bl.getText().find("(if:", bl.blIndex);
			bl.blIndex = bl.getText().find(")", sectionBeginning) + 1;
			stokenText = bl.getText().substr(sectionBeginning, bl.blIndex - sectionBeginning);
			SectionToken stok(stokenText);
			If ifSec(stok);
			bl.addSection(ifSec);
		}
		else if (bl.getText().substr(bl.blIndex, 9) == "(else-if:")
		{
			sectionBeginning = bl.getText().find("(else-if:", bl.blIndex);
			bl.blIndex = bl.getText().find(")", sectionBeginning) + 1;
			stokenText = bl.getText().substr(sectionBeginning, bl.blIndex - sectionBeginning);
			SectionToken stok(stokenText);
			Elseif elseif(stok);
			bl.addSection(elseif);
		}
		else if (bl.getText().substr(bl.blIndex, 6) == "(else:")
		{
			sectionBeginning = bl.getText().find("(else:", bl.blIndex);
			bl.blIndex = bl.getText().find(")", sectionBeginning) + 1;
			stokenText = bl.getText().substr(sectionBeginning, bl.blIndex - sectionBeginning);
			SectionToken stok(stokenText);
			Else el(stok);
			bl.addSection(el);
		}
		else if (bl.getText().substr(bl.blIndex, 2) == "[[")
		{
			sectionBeginning = bl.getText().find("[[", bl.blIndex);
			bl.blIndex = bl.getText().find("]]", sectionBeginning) + 2;
			stokenText = bl.getText().substr(sectionBeginning, bl.blIndex - sectionBeginning);
			SectionToken stok(stokenText);
			Link link(stok);
			bl.addSection(link);
		}
		else
		{
			int counter = 1;
			sectionBeginning = bl.blIndex;
			bl.blIndex++;
			while (counter != 0)
			{
				if (bl.getText().at(bl.blIndex) == '[')
				{
					counter++;
				}
				if (bl.getText().at(bl.blIndex) == ']')
				{
					counter--;
				}
				bl.blIndex++;
			}
			stokenText = bl.getText().substr(sectionBeginning, bl.blIndex - sectionBeginning);
			SectionToken stok(stokenText);
			Block block(stok);
			bl.addSection(block);
		}
	}
}

Block::Block(SectionToken& stok)
{
	type = BLOCK;
	blIndex = 2;
	BlockTokenizer btkzr;

	while (btkzr.hasNextSection(*this))
	{
		btkzr.nextSection(*this);
	}
}

void Block::startBlock(unordered_map<string, bool>& variables, vector<pair<string, string>>& listOfLinks, int gotoIndex, bool & gotoExists, string & passName)
{
	bool ifElseIfElse = true;

	if (gotoExists == false)
	{
		for (int i = 0; i < blockSections.size(); i++)
		{
			if (blockSections.at(i).getType() == GOTO)
			{
				gotoIndex = i;
				gotoExists = true;
				passName = blockSections.at(i).getPassName();
				break;
			}
			else
			{
				gotoIndex = blockSections.at(i).getType();
			}
		}
	}

	for (int i = 0; i < gotoIndex; i++)
	{
		type_t currentType = blockSections.at(i).getType();
		string currentText = blockSections.at(i).getText();

		if (currentType == SET)
		{
			bool value = blockSections.at(i).getValue();
			variables[currentText] = value;
		}
		else if (currentType == TEXT)
		{
			cout << currentText << endl;
		}
		else if (currentType == LINK)
		{
			if (gotoExists == false)
			{
				passName = blockSections.at(i).getPassName();

				cout << "\"" + currentText + "\"" << endl;
				listOfLinks.push_back(make_pair(currentText, passName));
			}
		}
		else if(currentType == IF)
		{
			if (blockSections.at(i).getValueToCheck() == variables[currentText])
			{
				ifElseIfElse = false;
			}
			else
			{
				i++;
			}
		}
		else if (currentType == ELSEIF)
		{
			if (blockSections.at(i).getValueToCheck() == variables[currentText] && ifElseIfElse == true)
			{
				ifElseIfElse = false;
			}
			else
			{
				i++;
			}
		}
		else if (currentType == ELSE)
		{
			if (ifElseIfElse == false)
			{
				i++;
			}
		}
		else
		{
			blockSections.at(i).startBlock(variables, listOfLinks, gotoIndex, gotoExists, passName);
		}
	}
}



void Block::addSection(SectionToken * blockSect) const
{
	blockSections.push_back(blockSect);
}
