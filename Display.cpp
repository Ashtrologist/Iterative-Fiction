//
// Created by Ashton Rodriquez on 11/26/18.
//

#include "Display.h"

void Display::startProgram(string textFile) {
// The purpose of this part of the function is to open a file and read in the text
    string input, textInput, name;

    ifstream myFile;
    myFile.open(textFile);

    getline(myFile, textInput);
    while (myFile && textInput != "</html>")
    {
        input = input + textInput + '\n';
        // cout << input;
        getline(myFile, textInput);
    }

    myFile.close();

//This part of the function acts as the interpreter, running the entire code
    Display st(input);
    int count = 0;

    StoryTokenizer storyTok;

    while(storyTok.hasNextPassage(st))
    {
        storyTok.nextPassage(st);
        name = st.getPassages().at(count).getName();
        st.addPassage(name, count);
        count++;
    }

    st.startPassage(0);

}

//Having weird problems running code, moved StoryTokenizer into display file as well

bool StoryTokenizer::hasNextPassage(Display& theStory)
{
    return theStory.displayText.find("<tw-passagedata ", index) != string::npos;
}

void StoryTokenizer::nextPassage(Display& theStory)
{
    int passageBeginning;

    passageBeginning = theStory.displayText.find("<tw-passagedata ", index);
    index = theStory.displayText.find("</tw-passagedata>", passageBeginning) + 17;

    PassageToken ptok(theStory.displayText.substr(passageBeginning, index - passageBeginning));
    Passage p(ptok);

    theStory.passages.push_back(p);
}



Display::Display(string text)
{
    displayText = text;
}



void Display::addPassage(string& name, int& index)
{
    findPassage[name] = index;
}



void Display::addVariable(string& variableName, bool& value)
{
    variables[variableName] = value;
}



bool Display::getVariable(string& variableName) const
{
    return variables.at(variableName);
}



int Display::lookup(string& passName) const
{
    return findPassage.find(passName)->second;
}



void Display::startPassage(int index)
{
    bool ifElseIfElse = true;
    bool gotoExists = false;
    int j;
    int chosen;
    string passageName;

    linkList.clear();

    for(int i = 0; i < passages.at(index).getCommand().size(); i++)
    {
        if(passages.at(index).getCommand().at(i).getType() == GOTO)
        {
            j = i;
            gotoExists = true;
            passageName = passages.at(index).getCommand().at(i).getPassName();
            break;
        }
    }

    if(gotoExists == false)
    {
        j = passages.at(index).getCommand().size();
    }

    for(int i = 0; i < j; i++)
    {
        command_t currentType = passages.at(index).getCommand().at(i).getType();
        string currentText = passages.at(index).getCommand().at(i).getText();

        if(currentType == SET)
        {
            bool value = passages.at(index).getCommand().at(i).getValue();
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
                passageName = passages.at(index).getCommand().at(i).getPassName();
                cout << "\"" + currentText + "\"" << endl;
                linkList.push_back(make_pair(currentText, passageName));
            }
        }
        else if(currentType == IF)
        {
            if(passages.at(index).getCommand().at(i).getValueToCheck() == getVariable(currentText))
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
            if(passages.at(index).getCommand().at(i).getValueToCheck() == getVariable(currentText) && ifElseIfElse == true)
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
            passages.at(index).getCommand().at(i).startBlock(variables, linkList, j, gotoExists, passageName);
        }

    }

    if(linkList.size() > 0)
    {
        for(int i = 0; i < linkList.size(); i++)
        {
            cout << (i + 1) << ". " << linkList.at(i).first << endl;
        }

        cin >> chosen;
        chosen--;
        passageName = linkList.at(chosen).second;

    }

    chosen = lookup(passageName);

    startPassage(chosen);
}

