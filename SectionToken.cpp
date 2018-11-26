#include "SectionToken.h"
#include <iostream>
using namespace std;



SectionToken::SectionToken(string sentence, command_t type)
{
	sectionText = sentence;
	sectionType = type;
}

string SectionToken::getText() const{

	return string();
}

command_t SectionToken::getType() const{
	return command_t();
}
