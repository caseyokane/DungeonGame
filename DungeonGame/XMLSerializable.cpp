#include "XMLSerializable.h"

using namespace std;

void XMLSerializable::dumpObject()
{
	//Dumps content to console (using cout)
	//**Make sure objects read  are correct
	//**Provide name of the class
	//Call dumpObjectData()
}

void XMLSerializable::dumpObjectData()
{
	//Dumps only the private member values to  the console
	//**Should call the version in their immediate base class to make sure that all data in inheritance chain gets output
}

void XMLSerializable::writeFragment(ostream & output)
{
	//Writes object as XML fragment to given stream
	//Provide the tags for class itself
	//Call writeDataAsFragment(sream);
}

void XMLSerializable::writeDataAsFragment(ostream & output)
{
	//writes  member variables of object as an XMLfragment to stream
	//**How is this different from previous method?**
	//Called in base class to ensure that data is output without reduntant code
}

void XMLSerializable::setElementData(string sElementName, string sValue)
{
	//Called during the deserialization process in order to read through data
	//Should be overriden in all calsses and call it's base class to ensure that all calsses get a shot at trying to store the data
}

