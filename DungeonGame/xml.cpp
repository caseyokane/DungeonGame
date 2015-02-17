#include <iostream>
#include <string>
#include <fstream>

using namespace std;



void parseElement(istream & input, string sPrefix)
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
		cout << sPrefix << "Element - " << sElementName << endl;
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


			cout << sPrefix << "Content - " << sContent << endl;

			return;
		}
		else
		{
			parseElement(input, sPrefix + "  ");
		}

	}

}

void parseXML(string sFilename)
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

	
	parseElement(input, "");
	
}

int main(int argc, char * argv[])
{
	cout << "What file should we parse? ";
	string sFilename;
	cin >> sFilename;

	parseXML(sFilename);



	return 0;
}
