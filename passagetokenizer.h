//
// Created by Ashton Rodriquez on 11/16/18.
//

#ifndef ITERATIVE_FICTION_PASSAGETOKENIZER_H
#define ITERATIVE_FICTION_PASSAGETOKENIZER_H

#include <string>
#include <iostream>
using namespace std;

enum command_t {LINK, GOTO, SET, IF, ELSEIF, ELSE, BLOCK, TEXT};


class SectionToken{
public:
    SectionToken(string sentence, command_t type);
    string getText() const;
    command_t getType() const;

private:
    command_t sectionType;
    string sectionText;
};

class PassageTokenizer {
public:
    bool hasNextSection();
    SectionToken nextSection();
    PassageTokenizer(string sentence);

private:
    string text = "";
    int currLocation;
};


#endif //ITERATIVE_FICTION_PASSAGETOKENIZER_H
