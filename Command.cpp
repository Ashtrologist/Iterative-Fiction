//
// Created by Ashton Rodriquez on 11/16/18.
//

#include "Command.h"

SectionToken::SectionToken(string& s)
{
    sectionText = s;
}

Link::Link(SectionToken& stok) : Command(stok)
{
    type = LINK;
    if(stok.getText().find(LINK_SEPARATOR, commandIndex) != string::npos)
    {
        commandIndex = stok.getText().find(LINK_SEPARATOR, commandIndex) + 5;
        text = stok.getText().substr(2, commandIndex - 2);
        commandIndex += 5;
        passName = stok.getText().substr(commandIndex, stok.getText().length() - commandIndex - 2);
    }
    else{
        text = stok.getText().substr(2, stok.getText().length() - 4);
        passName = text;
    }
}

Text::Text(SectionToken& stok) : Command(stok)
{
    type = TEXT;
}

Goto::Goto(SectionToken& stok) : Command(stok)
{
    commandIndex = stok.getText().find(GOTO_NAME_START, commandIndex) + 6;
    type = GOTO;
    passName = stok.getText().substr(commandIndex, stok.getText().find(GOTO_NAME_END, commandIndex) - commandIndex);
}

Set::Set(SectionToken& stok) : Command(stok)
{
    commandIndex = stok.getText().find(VARIABLE_START) + 1;
    type = SET;
    text = stok.getText().substr(commandIndex, stok.getText().find(" to ", commandIndex) - commandIndex);

    commandIndex = stok.getText().find(" to ", commandIndex) + 4;
    if(stok.getText().substr(commandIndex, 4) == "true"){
        value = true;
    }
    else{
        value = false;
    }
}

If::If(SectionToken& stok) : Command(stok)
{
    commandIndex = stok.getText().find("$") + 1;
    type = IF;
    text = stok.getText().substr(commandIndex, stok.getText().find(" is ", commandIndex) - commandIndex);

    commandIndex = stok.getText().find(" is ", commandIndex) + 4;
    if(stok.getText().substr(commandIndex, 4) == "true"){
        valueToCheck = true;
    }
    else{
        valueToCheck = false;
    }
}

Elseif::Elseif(SectionToken& stok) : Command(stok)
{
    commandIndex = stok.getText().find("$") + 1;
    type = ELSEIF;
    text = stok.getText().substr(commandIndex, stok.getText().find(" is ", commandIndex) - commandIndex);

    commandIndex = stok.getText().find(" is ", commandIndex) + 4;
    if(stok.getText().substr(commandIndex, 4) == "true"){
        valueToCheck = true;
    }
    else{
        valueToCheck = false;
    }
}

Else::Else(SectionToken& stok) : Command(stok)
{
    type = ELSE;
}

bool Blocks::hasNextSection(Block& bl)
{
    if (bl.getText().find("(set:", bl.blIndex) != string::npos) {
        return true;
    }
    else if (bl.getText().find(GOTO_START, bl.blIndex) != string::npos) {
        return true;
    }
    else if (bl.getText().find(IF_START, bl.blIndex) != string::npos) {
        return true;
    }
    else if (bl.getText().find(ELSEIF_START, bl.blIndex) != string::npos) {
        return true;
    }
    else if (bl.getText().find(ELSE_START, bl.blIndex) != string::npos) {
        return true;
    }
    else if (bl.getText().find(LINK_START, bl.blIndex) != string::npos) {
        return true;
    }
    else if (bl.getText().substr(bl.blIndex, 1) != "]") {
        return true;
    }
    else {
        return false;
    }
}

void Blocks::nextSection(Block& bl)
{
    int sectionBeginning;
    string stokenText;

    while(bl.getText().substr(bl.blIndex, 1) == "\n")
    {
        bl.blIndex++;
    }

    //test to see if the next section is a Text Section.
    if ((bl.getText().substr(bl.blIndex, 1) != "(") && (bl.getText().substr(bl.blIndex, 1) != BLOCK_START))
    {
        sectionBeginning = bl.blIndex;

        if ((bl.getText().find("(", bl.blIndex) == string::npos) && (bl.getText().find(BLOCK_START, bl.blIndex) == string::npos))
        {
            bl.blIndex = bl.getText().find("]", bl.blIndex);
        }
        else if (bl.getText().find("(", bl.blIndex) < bl.getText().find(BLOCK_START, bl.blIndex))
        {
            bl.blIndex = bl.getText().find("(", bl.blIndex);
        }
        else
        {
            bl.blIndex = bl.getText().find(BLOCK_START, bl.blIndex);
        }
        stokenText = bl.getText().substr(sectionBeginning, bl.blIndex - sectionBeginning);
        SectionToken stok(stokenText);
        Text text(stok);
        bl.addCommand(text);
    }
    else if(bl.getText().substr(bl.blIndex, 3) == "[[[")
    {
        int counter = 1;
        sectionBeginning = bl.blIndex;
        bl.blIndex++;
        while(counter != 0){
            if(bl.getText().at(bl.blIndex) == '['){
                counter++;
            }
            if(bl.getText().at(bl.blIndex) == ']'){
                counter--;
            }
            bl.blIndex++;
        }
        stokenText = bl.getText().substr(sectionBeginning, bl.blIndex - sectionBeginning);
        SectionToken stok(stokenText);
        Block block(stok);
        bl.addCommand(block);
    }
    else if (bl.getText().substr(bl.blIndex, 5) == "(set:")
    {
        sectionBeginning = bl.getText().find("(set:", bl.blIndex);
        bl.blIndex = bl.getText().find(COMMAND_END, sectionBeginning) + 1;
        stokenText = bl.getText().substr(sectionBeginning, bl.blIndex - sectionBeginning);
        SectionToken stok(stokenText);
        Set set(stok);
        bl.addCommand(set);
    }
    else if (bl.getText().substr(bl.blIndex, 7) == GOTO_START)
    {
        sectionBeginning = bl.getText().find(GOTO_START, bl.blIndex);
        bl.blIndex = bl.getText().find(COMMAND_END, sectionBeginning) + 1;
        stokenText = bl.getText().substr(sectionBeginning, bl.blIndex - sectionBeginning);
        SectionToken stok(stokenText);
        Goto go_to(stok);
        bl.addCommand(go_to);
    }
    else if (bl.getText().substr(bl.blIndex, 4) == IF_START)
    {
        sectionBeginning = bl.getText().find(IF_START, bl.blIndex);
        bl.blIndex = bl.getText().find(COMMAND_END, sectionBeginning) + 1;
        stokenText = bl.getText().substr(sectionBeginning, bl.blIndex - sectionBeginning);
        SectionToken stok(stokenText);
        If ifSec(stok);
        bl.addCommand(ifSec);
    }
    else if (bl.getText().substr(bl.blIndex, 9) == ELSEIF_START)
    {
        sectionBeginning = bl.getText().find(ELSEIF_START, bl.blIndex);
        bl.blIndex = bl.getText().find(COMMAND_END, sectionBeginning) + 1;
        stokenText = bl.getText().substr(sectionBeginning, bl.blIndex - sectionBeginning);
        SectionToken stok(stokenText);
        Elseif elseif(stok);
        bl.addCommand(elseif);
    }
    else if (bl.getText().substr(bl.blIndex, 6) == ELSE_START)
    {
        sectionBeginning = bl.getText().find(ELSE_START, bl.blIndex);
        bl.blIndex = bl.getText().find(COMMAND_END, sectionBeginning) + 1;
        stokenText = bl.getText().substr(sectionBeginning, bl.blIndex - sectionBeginning);
        SectionToken stok(stokenText);
        Else el(stok);
        bl.addCommand(el);
    }
    else if (bl.getText().substr(bl.blIndex, 2) == LINK_START)
    {
        sectionBeginning = bl.getText().find(LINK_START, bl.blIndex);
        bl.blIndex = bl.getText().find(LINK_END, sectionBeginning) + 2;
        stokenText = bl.getText().substr(sectionBeginning, bl.blIndex - sectionBeginning);
        SectionToken stok(stokenText);
        Link link(stok);
        bl.addCommand(link);
    }
    else
    {
        int counter = 1;
        sectionBeginning = bl.blIndex;
        bl.blIndex++;
        while(counter != 0)
        {
            if(bl.getText().at(bl.blIndex) == '[')
            {
                counter++;
            }
            if(bl.getText().at(bl.blIndex) == ']')
            {
                counter--;
            }
            bl.blIndex++;
        }
        stokenText = bl.getText().substr(sectionBeginning, bl.blIndex - sectionBeginning);
        SectionToken stok(stokenText);
        Block block(stok);
        bl.addCommand(block);
    }
}

Block::Block(SectionToken& stok) : Command(stok)
{
    type = BLOCK;
    blIndex = 2;
    Blocks btkzr;

    while(btkzr.hasNextSection(*this))
    {
        btkzr.nextSection(*this);
    }
}

void Block::addCommand(Command blockSect)
{
    blockCommands.push_back(blockSect);
}

void Block::startBlock(unordered_map<string, bool>& variables, vector<pair<string, string>>& linkList, int gotoIndex, bool& gotoExists, string& passName)
{
    bool ifElseIfElse = true;

    if(gotoExists == false)
    {
        for(int i = 0; i < blockCommands.size(); i++)
        {
            if(blockCommands.at(i).getType() == GOTO)
            {
                gotoIndex = i;
                gotoExists = true;
                passName = blockCommands.at(i).getPassName();
                break;
            }
            else
            {
                gotoIndex = blockCommands.at(i).getType();
            }
        }
    }

    for(int i = 0; i < gotoIndex; i++)
    {
        command_t currentType = blockCommands.at(i).getType();
        string currentText = blockCommands.at(i).getText();

        if(currentType == SET)
        {
            bool value = blockCommands.at(i).getValue();
            variables[currentText] = value;
        }
        else if(currentType == TEXT)
        {
            cout << currentText << endl; // @suppress("Invalid overload")
        }
        else if(currentType == LINK)
        {
            if(gotoExists == false)
            {
                passName = blockCommands.at(i).getPassName();

                cout << "\"" + currentText + "\"" << endl; // @suppress("Invalid overload")
                linkList.push_back(make_pair(currentText, passName));
            }
        }
        else if(currentType == IF)
        {
            if(blockCommands.at(i).getValueToCheck() == variables[currentText])
            {
                ifElseIfElse = false;
            }
            else
            {
                i++;
            }
        }
        else if(currentType == ELSEIF)
        {
            if(blockCommands.at(i).getValueToCheck() == variables[currentText] && ifElseIfElse == true)
            {
                ifElseIfElse = false;
            }
            else
            {
                i++;
            }
        }
        else if(currentType == ELSE)
        {
            if(ifElseIfElse == false)
            {
                i++;
            }
        }
        else
        {
            blockCommands.at(i).startBlock(variables, linkList, gotoIndex, gotoExists, passName);
        }
    }
}
