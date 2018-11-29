//
// Created by Ashton Rodriquez on 11/16/18.
//

#ifndef ITERATIVE_FICTION_STORYTOKENIZER_H
#define ITERATIVE_FICTION_STORYTOKENIZER_H

#include <string>
#include <iostream>
#include "passagetokenizer.h"
#include "Display.h"
using namespace std;


class StoryTokenizer{

    public:
        bool hasNextPassage();
        PassageToken nextPassage();
        StoryTokenizer(string sentence);

    private:
        string textSource;
        int location = 0;

};

class PassageToken{

public:
    string getText() const;
    PassageToken(string sentence);

private:
    string passageText;

};

class Passage{
    friend class PassageTokenizer;

private:
    string name;
    vector<Section> sections;
    int ptIndex;

public:
    Passage(PassageToken& pt);
    string getName() const{ return name; };
    vector<Section> getSec(){ return sections; };
};

#endif //ITERATIVE_FICTION_STORYTOKENIZER_H
