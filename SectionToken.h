#ifndef ITERATIVE_FICTION_SECTIONTOKEN_H
#define ITERATIVE_FICTION_SECTIONTOKEN_H

#include <iostream>
#include <string>
#include "passagetokenizer.h"
using namespace std;

class SectionToken
{
private:
	string sectionText;
	command_t sectionType;

public:
	string getText();
	command_t getType;
	SectionToken(string, command_t);
};

#endif