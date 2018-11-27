#ifndef ITERATIVE_FICTION_SECTIONTOKEN_H
#define ITERATIVE_FICTION_SECTIONTOKEN_H

#include <iostream>
#include <string>
using namespace std;

enum command_t { LINK, GOTO, SET, IF, ELSEIF, ELSE, BLOCK, TEXT };

class SectionToken
{
private:
	string sectionText;
	command_t sectionType;

public:
	string getText() const;
	command_t getType() const;
	SectionToken(string sentence, command_t type);
};

#endif