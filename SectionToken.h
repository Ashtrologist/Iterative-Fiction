#ifndef ITERATIVE_FICTION_SECTIONTOKEN_H
#define ITERATIVE_FICTION_SECTIONTOKEN_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum command_t {NULLT, LINK, GOTO, SET, IF, ELSEIF, ELSE, BLOCK, TEXT };

class SectionToken
{
protected:
	string sectionText;

public:
	string getText() const;
	SectionToken(string& section);
};


//SUPERCLASS
class Command{
protected:
	string text;
	command_t type;
	int location;

public:
	Command();
	Command(SectionToken& st);
	string getText() const;
	command_t getType() const;
};

//**********SUBCLASSES************//
class Link : public Command
{
private:
    string sectionName;
public:
    Link(SectionToken& stok);
    string getPassageName() const;
};

class Block : public Command
{
private:
    vector<SectionToken*> blockSections;
    int blockIndex;
public:
    Block(SectionToken& stok);
    void addSection(SectionToken* blockSect) const;
};

class Text : public Command
{
public:
    Text(SectionToken& stok);
};

class Goto : public Command
{
private:
    string sectionName;
public:
    Goto(SectionToken& stok);
    string getPassageName() const;
};

class Set : public Command
{
private:
    bool setBool;
public:
    Set(SectionToken& stok);
    bool getBool() const;
};

class If : public Command
{
private:
    bool checkSet;
public:
    If(SectionToken& stok);
    bool getSetValue() const;
};

class Elseif : public Command
{
private:
    bool checkSet;
public:
    Elseif(SectionToken& stok);
    bool getSetValue() const;
};

class Else : public Command
{
public:
    Else(SectionToken& stok);
};

class BlockTokenizer
{
public:
    BlockTokenizer();
    bool hasNextSection(Block& block);
    void nextSection(Block& block);
};
#endif