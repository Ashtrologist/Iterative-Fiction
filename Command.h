//
// Created by Ashton Rodriquez on 11/16/18.
//

#ifndef ITERATIVE_FICTION_COMMAND_H
#define ITERATIVE_FICTION_COMMAND_H

#include <utility>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

enum command_t {NULLT, LINK, SET, GOTO, IF, ELSEIF, ELSE, TEXT, BLOCK};

const string PASSAGE_START_TAG = "<tw-passagedata";
const string PASSAGE_START_TAG_CLOSE = ">";
const string PASSAGE_END_TAG   = "</tw-passagedata>";
const string LINK_START = "[[";
const string LINK_SEPARATOR = "-&gt;";
const string LINK_END   = "]]";
const string GOTO_START = "(go-to:";
const string SET_START = "(set:";
const string IF_START = "(if:";
const string ELSEIF_START = "(else-if:";
const string ELSE_START = "(else:";
const string COMMAND_END = ")";
const string BLOCK_START = "[";
const string BLOCK_END   = "]";
const string PASSAGE_NAME_START = "name=\"";
const string PASSAGE_NAME_END = "\"";
const string GOTO_NAME_START = "&quot;";
const string GOTO_NAME_END = "&quot;";
const string VARIABLE_START = "$";

class SectionToken
{
    friend class Blocks;
protected:
    string sectionText;
public:
    SectionToken(string& s);
    string getText() const { return sectionText; };
};

class Command
{
protected:
    string text;
    command_t type;
    int commandIndex;
public:
    Command(SectionToken& st) : commandIndex(0), text(st.getText()), type(NULLT) {};
    string getText() const { return text; };
    command_t getType() const { return type; };
    virtual string getPassName(){ return text; };
    virtual int getValue(){ return 0; };
    virtual int getValueToCheck(){ return 0; };
    virtual void startBlock(unordered_map<string, bool>& findPassage, vector<pair<string, string>>& linkList, int gotoIndex, bool& gotoExists, string& passName) {};
};

class Link : public Command
{
private:
    string passName;
public:
    Link(SectionToken& stok);
    string getPassName() { return passName; };
};

class Block : public Command
{
    friend class Blocks;
private:
    vector<Command> blockCommands;
    int blIndex = 0;
public:
    Block(SectionToken& stok);
    void addCommand(Command blockSect);
    void startBlock(unordered_map<string, bool>& variables, vector<pair<string, string>>& linkList, int gotoIndex, bool& gotoExists, string& passName);
};

class Text : public Command
{
public:
    Text(SectionToken& stok);
};

class Goto : public Command
{
private:
    string passName;
public:
    Goto(SectionToken& stok);
    string getPassName() const { return passName; };
};

class Set : public Command
{
private:
    bool value;
public:
    Set(SectionToken& stok);
    bool getValue() const { return value;};
};

class If : public Command
{
private:
    bool valueToCheck;
public:
    If(SectionToken& stok);
    bool getValueToCheck() const { return valueToCheck; };
};

class Elseif : public Command
{
private:
    bool valueToCheck;
public:
    Elseif(SectionToken& stok);
    bool getValueToCheck() const { return valueToCheck; };
};

class Else : public Command
{
public:
    Else(SectionToken& stok);
};

class Blocks
{
public:
    Blocks(){};
    bool hasNextSection(Block& bl);
    void nextSection(Block& bl);
};

#endif //ITERATIVE_FICTION_COMMAND_H
