#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <functional>
#include <vector>

#include "XMLSerializable.h"
#include "Entity.h"
#include "Item.h"
#include "Character.h"
#include "Consumable.h"
#include "Creature.h"
#include "Equipment.h"
#include "Armor.h"
#include "Weapon.h"
#include "Player.h"


using namespace std;

 
XMLSerializable* buildObject(string sName)
{
	map<string,function<XMLSerializable*()>> mapConstructor;


	mapConstructor["Entity"] = []() {return new Item; };
	mapConstructor["Item"] = []() {return new Item; };
	mapConstructor["Character"] = []() {return new Character; };
	mapConstructor["Consumable"] = []() {return new Consumable; };
	mapConstructor["Creature"] =[]() {return new Creature; };
	mapConstructor["Equipment"] = []() {return new Equipment; };
	mapConstructor["Armor"] = []() {return new Armor; };
	mapConstructor["Weapon"] = []() {return new Weapon; };
	mapConstructor["Player"] = []() {return new Player; };


	function<XMLSerializable*()> pFunction = mapConstructor[sName];

	XMLSerializable * pObject = NULL;

	if(pFunction == NULL)
	{
		cout << "Class not found " << endl;
	}

	else
	{
		cout << "Class found! Building  object." << endl;
		pObject = pFunction();


		if(pObject != NULL)
		{
			cout << "Object built!" << endl;
		}
		else
		{
			cout << "Could not build  object..."  << endl;
		}
	}


	return pObject;

}
void parseElement(istream & input, string sPrefix, XMLSerializable * pObject, vector<XMLSerializable*> & vpObjects)
{
	string sElementName;
	getline(input, sElementName, '>');

	if( sElementName.back() == '/' )
	{
		cout << sPrefix << "Empty element: " << sElementName << endl;
		return;
	}
	else
	{
		cout << sPrefix << " Element - " << sElementName << endl;
		cout << "Try to construct " << sElementName << " here." << endl;

		XMLSerializable *  tempObject = buildObject(sElementName);
		if(tempObject != NULL)
		{
			pObject = tempObject;
			vpObjects.push_back(pObject);
		}
	}

	string sContent = "";


	while( true )
	{

		char c = input.get();

		while( c != '<' )
		{
			if( c != '\n' )
				sContent.push_back(c);

			c = input.get();
		}

		if( input.peek() == '/' )
		{
			input.get();
			string sEndElement;
			getline(input, sEndElement, '>');

			if( sEndElement != sElementName )
				cout << "Bad XML found" << endl;

			if( pObject != NULL)
			{
				pObject->setElementData(sElementName, sContent);
			}
			cout << sPrefix << " : " << sElementName << " : "  << sContent << endl;

			return;
		}
		else
		{
			parseElement(input, sPrefix + " > " + sElementName, pObject, vpObjects);
		}

	}

}

void parseXML(string sFilename, vector<XMLSerializable*> & vpObjects)
{
	ifstream input;
	input.open(sFilename);

	while( input.get() != '?' );
	while( input.get() != '?' );

	if( input.get() != '>' )
	{
		cout << "Bad XML detected" << endl;
		return;
	}

	while( input.get() != '<' );


	parseElement(input, "> ", NULL, vpObjects);

}

int main(int argc, char * argv[])
{
	cout << "What XML file would like you to parse? ";
	string sFilename;
	cin >> sFilename;

	cout << endl;

	vector<XMLSerializable*> vpObjects;

	parseXML(sFilename, vpObjects);

	cout << endl;

	for(auto ctr = vpObjects.begin();
		ctr !=  vpObjects.end();
		ctr++)
	{
		(*ctr)->dumpObject();
	}



	cout << "Your output file was saved as output.xml";
	string sOutFile = "output.xml";
	ofstream output;
	output.open(sOutFile);

	output << "<?xml version=\"1.0\" encoding = \"utf-8\"?>"
		<< endl
		<< "<World>"
		<< endl;

	for(auto it = vpObjects.begin();
		it != vpObjects.end();
		it++)
	{
		(*it)->writeFragment(output);
	}

	output << "</World>" << endl;



	return 0;
}
