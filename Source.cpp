#include <Python.h>
#include <iostream>
#include<iomanip>
#include <Windows.h>
#include <cmath>
#include <string>
#include<fstream>

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

void printMenu() {
	cout << endl << "1: List All Items and Quantities Sold" << endl;
	cout << "2: Get Quantity Sold of Specific Item" << endl;
	cout << "3: Display Histogram of Sales" << endl;
	cout << "4: Exit" << endl;
	cout << "Enter your selection as a number 1, 2, 3, or 4." << endl << endl;
}

void displayHistogram() {
	// Open frequency file
	ifstream fin("frequencies.dat");

	if (fin.is_open()) {
		string line;
		string item;
		int qty;

		while (fin.good()) {
			// Read next item name and qty
			fin >> item;
			fin >> qty;

			// Print item name and '*' for size of qty
			cout << item;
			for (int i = 0; i < qty; ++i) {
				cout << '*';
			}
			cout << endl;
		}
	}
}

int main()
{
	int userInput = -1;
	string specItem;

	do {
		// Show menu
		printMenu();

		// Get user selection
		while (!(cin >> userInput)) {
			cout << "Invalid Input" << endl;
			cin.clear();
			cin.ignore(123, '\n');
		}

		switch (userInput) {
			// List all items and quantities
		case 1:
			CallProcedure("listQty");
			break;

			// Get Quantity of Specific Item
		case 2:
			// Get item from user
			cout << "Which item?" << endl;
			cin >> specItem;

			// Return item quasntity
			callIntFunc("getItemQty", specItem);
			break;

			// Display Histogram of Sales
		case 3:
			CallProcedure("getHistogramData");
			displayHistogram();
			break;

			// Exit
		case 4:
			cout << "Goodbye." << endl;
			break;

			// Input validation
		default:
			cout << "Invalid Input" << endl;
		}
	} while (userInput != 4);

	return 0;
}
