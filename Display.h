//
// Created by Ashton Rodriquez on 11/16/18.
//

#ifndef ITERATIVE_FICTION_DISPLAY_H
#define ITERATIVE_FICTION_DISPLAY_H

#include "Passage.h"
#include "Command.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

class Display
{

    friend class Command;
    friend class Passage;
    friend class StoryTokenizer;

private:
    string displayText;
    string textFile;
    string textInput;
    vector<Passage> passages;
    vector<pair<string, string>> linkList;
    unordered_map<string, bool> variables;
    unordered_map<string, int> findPassage;

public:
    Display();
    Display(string textFile);
    void addPassage(string& name, int& index);
    void addVariable(string& variableName, bool& value);
    bool getVariable(string& variableName) const;
    int lookup(string& passName) const;
    vector<Passage> getPassages(){ return passages; };
    void startProgram (string textFile);
    void startPassage(int index);
};

class StoryTokenizer{

private:
    int index;

public:
    StoryTokenizer() : index(0) {};
    bool hasNextPassage(Display& theStory);
    void nextPassage(Display& theStory);
};

#endif //ITERATIVE_FICTION_DISPLAY_H
