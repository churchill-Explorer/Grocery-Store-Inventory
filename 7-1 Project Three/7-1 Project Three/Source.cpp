#include <Python.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

/*
Description:
	This function will return a string of the user input.
Example:
	string x = getInput();
Return:
	Returns string
*/
string getInput() {
	string userInput;
	bool breakLoop;

	//I choice a do while statement so it can recieve input before understanding if it need to executed again.
	do
	{
		//This try statement ensures that if the input is invalid it will still process and attempt again.
		try
		{
			cout << endl << "Enter an item: " << endl;
			cin >> userInput;
			breakLoop = true;
		}
		catch (const std::exception&)
		{
			cout << "That input wasn't quite right..." << endl;
			breakLoop = false;
		}

		//We're clearning and ignoring to ensure that if a non numeric value is entered for op1 or op2 that the cin buffer is flushed to prevent a infinit loop
		//or unintentional exit of the program.
		cin.clear();
		cin.ignore(10000, '\n');

	} while (!breakLoop);

	return userInput;
}

/*
Description:
	This function will return a menu selection as long as it's win the range of 1 and the number you pass it.
Example:
	getInput(3);
Return:
	Returns int 1 to maxChoice
*/
int getInput(int maxChoice) {
	//This function will recieve input from 1-maxChoice and if it's outside of parameter it will attempt again.
	int userInput;

	//I choice a do while statement so it can recieve input before understanding if it need to executed again.
	do
	{
		//This try statement ensures that if the input is invalid it will still process and attempt again.
		try
		{
			cin >> userInput;
		}
		catch (const std::exception&)
		{
			userInput = -1;
		}

		//We're clearning and ignoring to ensure that if a non numeric value is entered for op1 or op2 that the cin buffer is flushed to prevent a infinit loop
		//or unintentional exit of the program.
		cin.clear();
		cin.ignore(10000, '\n');

	} while (userInput > maxChoice || userInput < 1);

	return userInput;
}

/*
Description:
	prints the options for the main menu
Example:
	printMenu();
Return:
	Returns Nothing.
*/
void printMenu() {
	cout << "1. List of all items purchased in a given day" << endl;
	cout << "2. Specific item purchase count in a given day" << endl;
	cout << "3. All items purchased histogram in a given day" << endl;
	cout << "4. Exit" << endl << endl;
}

/*
Description:
	This is function will return the string of histogram token length
Example:
	Only one param which is the length of the token. i.e. getHistogramToken(3);
Return:
	Returns string of token length. i.e. a token of 3 is "***".
*/
string getHistogramToken(int tokenLength) {
	
	//Generate tempstring that we can append too.
	string tempString = "";

	//Loop that appends to the tempString
	for (int i = 0; i < tokenLength; i++)
	{
		//Append to string using +=
		tempString += "*";
	}

	//Return token
	return tempString;
}

/*
Description:
	This is function will output the contents of a Dat file in a histogram
Example:
	Only one param which is the Dat file path. i.e. histogramDatFile("this.dat");
Return:
	Returns nothing. This is a void function.
*/
void histogramDatFile(string filePathDat) {
	
	//These are start up local variables.
	ifstream datFile;
	string token;
	string item;

	//Open per file name of project.
	datFile.open(filePathDat, ifstream::in);

	//Checks to ensure that the file is open
	if (!datFile.is_open()) {
		cout << "Could not open file." << endl;
		cout << "Ensure file is located in proper directory." << endl;
		cout << "i.e. The dat is located in \\7-1 Project Three\\7-1 Project Three" << endl;
	}

	//Checks to ensure that the file is not empty
	if (datFile.fail())
	{
		cout << "File was not read successfully." << endl;
	}

	//Print Header
	cout << endl << "Histogram:" << endl;
	//Loop for printing output
	do
	{
		//Gets the line from the file.
		getline(datFile, token);
		item = token.substr(0, token.find("|"));
		token.erase(0, token.find("|") + 1);

		//This if statement will check to see if the line is empty or not.
		if (token.length() > 0)
		{
			cout << item << " " << getHistogramToken(stoi(token)) << endl;
		}
		//This is checking to ensure that the end of the file is reached.
	} while (!datFile.eof());

	//Console Cleanup
	cout << endl << endl;
	datFile.close();
	return;
}

/*
Description:
	This is the main function loop that will run and control the flow of the main program.
Example:
	Main function loop call with no params.
Return:
	Returns Nothing.
*/
void mainMenu() {
	
	//Setting userInput to -1 so it can make the switch case without terminating the program.
	int userInput = -1;

	//Cannot be declared in switch case because it throws an error.
	const string filePath = "CS210_Project_Three_Input_File.txt";
	string tempString;
	string tempStringTwo;

	do
	{
		//Prints menu around each loop iteration.
		printMenu();

		//Returns the menu selection validated input.
		userInput = getInput(4);

		switch (userInput)
		{
		case 1:
			callIntFunc("printItemsPurchasedInDay", filePath);
			break;
		case 2:
			tempString = getInput();
			tempStringTwo = filePath + "|" + tempString;
			cout << endl;
			cout << tempString << ": " << callIntFunc("getSpecificItemPurchaseCount", tempStringTwo) << endl << endl;
			break;
		case 3:
			callIntFunc("createFreqDat", filePath);
			histogramDatFile("frequency.dat");
			break;
		default:
			break;
		}

	} while (userInput != 4);
}

int main()
{
	mainMenu();

	return -1;
}