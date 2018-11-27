//
// Created by Ashton Rodriquez on 11/16/18.
//

#ifndef ITERATIVE_FICTION_PASSAGETOKENIZER_H
#define ITERATIVE_FICTION_PASSAGETOKENIZER_H

#include <string>
#include <iostream>
#include "display.h"
#include "storytokenizer.h"

using namespace std;

enum command_t {LINK, GOTO, SET, IF, ELSEIF, ELSE, BLOCK, TEXT};


class SectionToken{
public:
    SectionToken(string sentence, command_t type);
    string getText() const;
    command_t getType() const;

protected:
    command_t sectionType;
    string sectionText;
};

class PassageTokenizer {
public:
    bool hasNextSection();
    SectionToken nextSection();
    PassageTokenizer(string sentence);

protected:
    string text = "";
    int currLocation;
};

//class Link : public SectionToken
//{
//private:
//    string passageName;
//public:
//    Link(SectionToken& stok);
//    string getPassageName() const { return passageName; };
//};
//
//class Block : public SectionToken
//{
//private:
//    vector<Section*> blockSections;
//    int blockIndex;
//public:
//    Block(SectionToken& stok);
//    void addSection(Section* blockSect) const;
//};
//
//class Text : public SectionToken
//{
//public:
//    Text(SectionToken& stok);
//};
//
//class Goto : public SectionToken
//{
//private:
//    string passageName;
//public:
//    Goto(SectionToken& stok);
//    string getPassageName() const { return passageName; };
//};
//
//class Set : public SectionToken
//{
//private:
//    bool value;
//public:
//    Set(SectionToken& stok);
//    bool getValue() const { return value;};
//};
//
//class If : public SectionToken
//{
//private:
//    bool valueToCheck;
//public:
//    If(SectionToken& stok);
//    bool getValueToCheck() const { return value; };
//};
//
//class Elseif : public SectionToken
//{
//private:
//    bool valueToCheck;
//public:
//    Elseif(SectionToken& stok);
//    bool getValueToCheck() const { return value; };
//};
//
//class Else : public SectionToken
//{
//public:
//    Else(SectionToken& stok);
//};
//
//class BlockTokenizer
//{
//public:
//    BlockTokenizer();
//    bool hasNextSection(Block& block);
//    void nextSection(Block& block);
//};


#endif //ITERATIVE_FICTION_PASSAGETOKENIZER_H
