#include "SectionToken.h"
#include <iostream>
using namespace std;
//


SectionToken::SectionToken(string& section)
{
	sectionText = section;
}

string SectionToken::getText() const{

	return string();
}



Command::Command()
{
	text = "";
	type = NULLT;
}

//Command Class Functions
Command::Command(SectionToken& st)//constructor
{
	text = st.getText();
	type = NULLT;
}

string Command::getText() const
{
	return text;
}

command_t Command::getType() const
{
	return type;
}




Link::Link(SectionToken & stok){//Working on LINK class ***************//

	type = LINK;
	location = 0;
	if (stok.getText().find("-&gt;", location) != string::npos)

	{

		location = stok.getText().find("-&gt;", location);
		text = stok.getText().substr(2, location-2);

		location += 5;

		sectionName = stok.getText().substr(location, stok.getText().length() - location - 2);

	}

	else {

		text = stok.getText().substr(2, stok.getText().length() - 4);

		sectionName = text;

	}
}

string Link::getPassageName() const
{
	return sectionName;
}

Text::Text(SectionToken& stok){
	type = TEXT;
}

Goto::Goto(SectionToken& stok){
	type = GOTO;
	location = stok.getText().find("&quot;") + 6;
	sectionName = stok.getText().substr(location, stok.getText().find("&quot;", location) - location);
}

string Goto::getPassageName() const
{
	return sectionName;
}

Set::Set(SectionToken & stok)
{
	type = SET;
	location = stok.getText().find("$") + 1;
	text = stok.getText().substr(location, stok.getText().find(" to ", location) - location);

	location = stok.getText().find(" to ", location) + 4;
	if (stok.getText().substr(location, 4) == "true") {
		setBool = true;
	}

	else {
		setBool = false;
	}
}

bool Set::getBool() const
{
	return setBool;
}

If::If(SectionToken & stok)
{
	type = IF;
	location = stok.getText().find("$") + 1;
	text = stok.getText().substr(location, stok.getText().find(" is ", location) - location);

	location = stok.getText().find(" is ", location) + 4;
	if (stok.getText().substr(location, 4) == "true") {
		checkSet = true;
	}
	else {
		checkSet = false;
	}
}

bool If::getSetValue() const
{
	return checkSet;
}

Elseif::Elseif(SectionToken & stok)
{
	type = ELSEIF;
	location = stok.getText().find("$") + 1;
	text = stok.getText().substr(location, stok.getText().find(" is ", location) - location);

	location = stok.getText().find(" is ", location) + 4;
	if (stok.getText().substr(location, 4) == "true") {
		checkSet = true;
	}
	else {
		checkSet = false;
	}
}

bool Elseif::getSetValue() const
{
	return checkSet;
}

Else::Else(SectionToken & stok)
{
	type = ELSE;
}
