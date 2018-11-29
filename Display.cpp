//
// Created by Ashton Rodriquez on 11/16/18.
//

#include "Display.h"
#include "passagetokenizer.h"
#include "storytokenizer.h"
#include <fstream>
#include <iostream>
#include <string>

void Display::startProgram(string textFile) const {

//The purpose of this part of the function is to open a file and read in the text
    fstream myFile;
    string textInput, name;

    myFile.open(textFile);

    if(myFile.is_open()){
        getline(myFile, textInput);
        while (myFile && textInput != "</html"){
            cout << textInput << endl; //Remember to move
            getline(myFile, textInput);
        }
    }

    myFile.close();

    Display story (textInput);
    int pass = 0;

    StoryTokenizer stoken;

    while(stoken.hasNextPassage(story))
    {
        stoken.nextPassage(story);
        name = story.getPassages().at(pass).getName();
        story.addLookup(name, pass);
        pass++;

    }

    story.startPassage(0);
}


Display::Display(string textFile) {

    displayText = textFile;
}

void Display::addLookup(string &name, int &index) {
    lookUpPassage[name] = index;
}

void Display::addVariable(string &varName, bool &value) {
    variables[varName] = value;
}

bool Display::getVarVal(string &varName) const {
    return variables.at(varName);
}

bool Display::lookup(string &passName) const {
    return lookUpPassage.find(passName) -> second;
}

void Display::startPassage(int index) {
    bool ifElseIfElse = true;
    bool gotoExists = false;
    int j, chosen;
    string passName;

    listOfLinks.clear();

    for(int i = 0; i < passages.at(index).getSec().size(); i++)
    {
        if(passages.at(index).getSec().at(i).getType() == GOTO)
        {
            j = i;
            gotoExists = true;
            passName = passages.at(index).getSec().at(i).getPassName();
            break;
        }
    }

    if(gotoExists == false)
    {
        j = passages.at(index).getSec().size();
    }

    for(int i = 0; i < j; i++)
    {
        type_t currentType = passages.at(index).getSec().at(i).getType();
        string currentText = passages.at(index).getSec().at(i).getText();

        if(currentType == SET)
        {
            bool value = passages.at(index).getSec().at(i).getValue();
            addVariable(currentText, value);
        }
        else if(currentType == TEXT)
        {
            cout << currentText << endl;
        }
        else if(currentType == LINK)
        {
            if(gotoExists == false)
            {
                passName = passages.at(index).getSec().at(i).getPassName();
                cout << "\"" + currentText + "\"" << endl;
                listOfLinks.push_back(make_pair(currentText, passName));
            }
        }
        else if(currentType == IF)
        {
            if(passages.at(index).getSec().at(i).getValueToCheck() == getVarVal(currentText))
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
            if(passages.at(index).getSec().at(i).getValueToCheck() == getVarVal(currentText) && ifElseIfElse == true)
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
            passages.at(index).getSec().at(i).startBlock(variables, listOfLinks, j, gotoExists, passName);
        }

    }

    if(listOfLinks.size() > 0)
    {
        for(int i = 0; i < listOfLinks.size(); i++)
        {
            cout << (i + 1) << ". " << listOfLinks.at(i).first << endl;
        }

        cin >> chosen;
        chosen--;
        passName = listOfLinks.at(chosen).second;

    }

    chosen = lookup(passName);

    startPassage(chosen);
}



