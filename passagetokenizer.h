//
// Created by Ashton Rodriquez on 11/16/18.
//.

#ifndef ITERATIVE_FICTION_PASSAGETOKENIZER_H
#define ITERATIVE_FICTION_PASSAGETOKENIZER_H

#include <string>
#include <iostream>
#include "Display.h"
#include "storytokenizer.h"

using namespace std;

enum command_t { NULLT, LINK, GOTO, SET, IF, ELSEIF, ELSE, BLOCK, TEXT };

class SectionToken
{
protected:
	string sectionText;

public:
	string getText() const;
	SectionToken(string& section);
};


//SUPERCLASS
class Command {
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

//I dont understand what this is supposed to do
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

//I dont understand what this is supposed to do
class BlockTokenizer
{
public:
	BlockTokenizer();
	bool hasNextSection(Block& block);
	void nextSection(Block& block);
};//
#endif //ITERATIVE_FICTION_PASSAGETOKENIZER_H

enum command_t { NULLT, LINK, GOTO, SET, IF, ELSEIF, ELSE, BLOCK, TEXT };

class SectionToken
{
protected:
	string sectionText;

public:
	string getText() const;
	SectionToken(string& section);
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
//SUPERCLASS
class Command {
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