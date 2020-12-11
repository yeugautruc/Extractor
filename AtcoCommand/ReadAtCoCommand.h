#pragma once
#include "FileName.h"
#include "AtcoCommand.h"
#include "Ocurrence.h"
#include "DynCommandArray.h"
#include "DynAtcoCommandArray.h"
#include "DynOcurrenceArray.h"
#include "UltilType.h"

using namespace std;

class ReadAtCoCommand
{

public:
	/* Methods to use
---------------------------*/

	// Read text file method
	string readTextFile(string url)
	{
		string output, line;
		ifstream myfile(url);
		if (myfile.is_open())
		{
			while (getline(myfile, line))
			{
				output += line + "\n";
			}
			myfile.close();
		}
		else
			cout << "Unable to open test file ";

		return output;
	}

	// Count word from string into a map
	void wordsCount(const string &str, map<string, int> &wordsMap)
	{
		int count = 1;
		istringstream wordStream(str);
		string word;
		while (wordStream >> word)
		{
			pair<map<string, int>::iterator, bool> returnValue;
			returnValue = wordsMap.insert(pair<string, int>(word, count));
			if (returnValue.second == false)
			{
				++returnValue.first->second;
			}
		}
	};
	void commandsCount(const string &str, map<string, int> &wordsMap)
	{
		if (str.length() > 3)
		{
			int count = 1;
			pair<map<string, int>::iterator, bool> returnValue;
			returnValue = wordsMap.insert(pair<string, int>(str, count));
			if (returnValue.second == false)
			{
				++returnValue.first->second;
			}
		}
	};

	// Resize dynamic array type Atcocommand
	void resizeAtcoCommand(AtcoCommand *&inputArray, int &oldSize, int &newSize)
	{
		AtcoCommand *temp = new AtcoCommand[oldSize];
		for (int i = 0; i < oldSize; i++)
		{
			temp[i] = inputArray[i];
		}
		delete[] inputArray;

		inputArray = new AtcoCommand[newSize];
		for (int i = 0; i < oldSize; i++)
		{
			inputArray[i] = temp[i];
		}
		delete[] temp;
	};

	// Resize dynamic array type Occurence
	void resizeOcurrence(Ocurrence *&inputArray, int &oldSize, int &newSize)
	{
		Ocurrence *temp = new Ocurrence[oldSize];
		for (int i = 0; i < oldSize; i++)
		{
			temp[i] = inputArray[i];
		}
		delete[] inputArray;

		inputArray = new Ocurrence[newSize];
		for (int i = 0; i < oldSize; i++)
		{
			inputArray[i] = temp[i];
		}
		delete[] temp;
	};

	// Init atcoCommand array with value and size
	void initAtcoCommand(AtcoCommand *&a, string wert, int size)
	{
		a = new AtcoCommand[size];
		for (int i = 0; i < size; i++)
		{
			AtcoCommand atcoCommand = AtcoCommand("2019-02-15__11-32-48-00:", wert, "ABP61 INIT_RESPONSE");
			a[i] = atcoCommand;
		}
	};

	// Init atcoCommand array with value
	void initAtcoCommand(AtcoCommand *&a, string wert)
	{
		for (int i = 0; i < 50; i++)
		{
			AtcoCommand atcoCommand = AtcoCommand("2019-02-15__11-32-48-00:", wert, "ABP61 INIT_RESPONSE");
			a[i] = atcoCommand;
		}
	};

	// Init occurence array with value and size
	void initOcurrence(Ocurrence *&a, string wert, int size)
	{
		a = new Ocurrence[size];
		for (int i = 0; i < size; i++)
		{
			Ocurrence ocurrence = Ocurrence(wert, 1);
			a[i] = ocurrence;
		}
	};

	// Init occurence array with value
	void initOcurrence(Ocurrence *&a, string wert)
	{
		for (int i = 0; i < 50; i++)
		{
			Ocurrence ocurrence = Ocurrence(wert, 1);
			a[i] = ocurrence;
		}
	};

	// Main method to read text file and input to main type (AtcoCommand Array and Occurence Array)
	void readFileGetOutput(string url, UltilType &output)
	{
		map<string, int> wordsMap;
		map<string, int> commandsMap;
		DynAtcoCommandArray atcoCommands;
		atcoCommands = DynAtcoCommandArray(1);

		string line, fileName, wordSequence, commands;
		ifstream file(url);
		if (file.is_open())
		{
			while (file.good())
			{
				getline(file, line);
				if (line.find(":") != -1)
				{
					if (wordSequence.length() != 0)
					{
						// Finish last read AtcoCommand
						AtcoCommand atcoCommand = AtcoCommand(fileName, wordSequence, commands);
						atcoCommands.add(atcoCommand);
						commands = "";
					}
					fileName = line;
					getline(file, line);
					wordSequence = line;
				}
				else
				{
					commands += line + "\n ";
				}
			}

			// Last AtcoCommand is read
			AtcoCommand atcoCommand = AtcoCommand(fileName, wordSequence, commands);
			atcoCommands.add(atcoCommand);

			file.close();

			// Count words sequence and commands into map
			for (int i = 0; i < atcoCommands.getSize(); i++)
			{
				wordsCount(atcoCommands.getElementArray(i).getWordSequence(), wordsMap);
				for (int k = 0; k < atcoCommands.getElementArray(i).getSizeCommands(); k++)
				{
					// save only expected command type (main commands) into commandsMap (use to print out later)
					commandsCount(atcoCommands.getElementArray(i).getElementFromCommandArray(k).getMainCommands(), commandsMap);
				}
			}

			// Input data in to AtcoCommand Dynamic Array and Occurence Dynamic Array
			output = UltilType(atcoCommands, wordsMap, commandsMap, url);
		}
	};
	/* End methods to use
---------------------------*/

	/* All test methods above:
existsTest									check if able to acces file
dateTimeSplitMethodTest						check if split method works
topOcurrencesTest							check if get top occurence method works
resizeOccurencesTest						check if resize Occurence method works
resizeAtcoCommandTest						check if resize AtcoCommand method works
canReadMoreThanSixCommandTest				check if method able to read more than 6 commands
CopyConstructorDynCommandArrayTest			check if copy constructor of dynCommandArray works
CopyConstructorDynAtcoCommandArrayTest		check if copy constructor of dynAtcoCommandArray works
CopyConstructorDynOcurrenceArrayTest		check if copy constructor of dynOcurrenceArray works
AssignmentOperatorDynCommandArrayTest		check if assignment operator of dynCommandArray works
AssignmentOperatorDynAtcoCommandArrayTest	check if assignment operator of dynAtcoCommandArray works
AssignmentOperatorDynOcurrenceArrayTest		check if assignment operator of dynCommandArray works

---------------------------*/

	bool existsTest(const string &name)
	{
		ifstream myFile(name);
		if (myFile.fail())
		{
			return false;
		}
		cout << "Test file exist                                OK" << endl;
		return true;
	};

	bool dateTimeSplitMethodTest(UltilType input, string testString)
	{
		if (testString.find(input.getDynAtcoCommands().getElementArray(0).getFormattedDateTime().toString().substr(2, input.getDynAtcoCommands().getElementArray(0).getFormattedDateTime().toString().length() - 4)) != -1)
		{
			cout << "Test split                                     OK" << endl;
			return true;
		}
		return false;
	};

	bool topOcurrencesTest(UltilType input, string testString)
	{
		if (testString.find(input.getTopCommands(20)) != -1)
		{
			cout << "Test top occurences method                     OK" << endl;
			return true;
		}
		return false;
	};

	/* Create an AtcoCommand Dynamic Array with old word sequence
Use resize method to resize the dynamic array from 4 to 50
and set all word sequence value of the array to new word squence.
Check if all elements has a new word sequence value.*/
	bool resizeAtcoCommandTest()
	{
		AtcoCommand *a;
		a = new AtcoCommand[1];
		const string wert = "old word sequence";
		const string newWert = "new word sequence";
		int oldSize = 4;
		int newSize = 50;

		initAtcoCommand(a, wert, oldSize);
		resizeAtcoCommand(a, oldSize, newSize);
		initAtcoCommand(a, newWert);

		// Check of dynamic array after resize works
		for (size_t i = 0; i < unsigned(newSize); i++)
		{
			if (a[i].getWordSequence().find(newWert) == -1)
			{
				delete[] a;
				return false;
			}
		}
		delete[] a; // Release memory
		cout << "Test resize AtcoCommand method                 OK" << endl;
		return true;
	};

	/* Create an Occurence Dynamic Array with old value
Use resize method to resize the dynamic array from 4 to 50
and set all value of the array to new value.
Check if all elements has a new value.*/
	bool resizeOcurrenceTest()
	{
		Ocurrence *o;
		o = new Ocurrence[1];
		const string wert = "old value";
		const string newWert = "new value";
		int oldSize = 4;
		int newSize = 50;

		initOcurrence(o, wert, oldSize);
		resizeOcurrence(o, oldSize, newSize);
		initOcurrence(o, newWert);

		// Check of dynamic array after resize works
		for (size_t i = 0; i < unsigned(newSize); i++)
		{
			if (o[i].getValue().find(newWert) == -1)
			{
				delete[] o;
				return false;
			}
		}
		delete[] o; // Release memory
		cout << "Test resize Ocurrence method                   OK" << endl;
		return true;
	};

	/*Read from test Text an AtcoCommand with 7 commands.
Check if more than 6 commands are read*/
	bool CanReadMoreThanSixCommandTest(UltilType input)
	{
		int amountOfCommand = 0;
		for (int i = 0; i < input.getDynAtcoCommands().getElementArray(2).getDynCommands().getSize(); i++)
		{
			if (input.getDynAtcoCommands().getElementArray(2).getDynCommands().getElementArray(i).getCommands().length() > 3)
			{
				amountOfCommand++;
			};
		};
		if (amountOfCommand > 6)
		{
			cout << "Test can read more than 6 commands             OK" << endl;
			return true;
		}
		return false;
	};

	/* Create an dynamic command array d1 with 10 elements.
Use copy constructor, copy d1 to d2.Check if all elements
of d2 is correct copied from d1 and have same size with d1.

I dont want just check test crash when copy constructor not work.
I also need content test (may be copy constructor work,
but copy content is not correct, then crash test make no sense)*/
	bool CopyConstructorDynCommandArrayTest()
	{
		Command cmd = Command("BAW52CV INIT_RESPONSE");

		// Create d1 with 10 elements
		DynCommandArray d1 = DynCommandArray(1);
		for (size_t i = 0; i < 10; i++)
		{
			d1.add(cmd);
		}

		// Copy d2 from d1
		DynCommandArray d2 = d1;

		// Check d2 is coppied
		for (int i = 0; i < 10; i++)
		{
			if (d2.getElementArray(i).getMainCommands().find("INIT_RESPONSE") == -1)
			{
				return false;
			}
		}
		if (d2.getSize() != 11)
		{
			return false;
		}
		cout << "Test copy constructor DynCommandArray          OK" << endl;
		return true;
	};

	/* Create an dynamic atcoCommand array d1 with 10 elements.
Use copy constructor, copy d1 to d2.Check if all elements
of d2 is correct copied from d1 and have same size with d1.

I dont want just check test crash when copy constructor not work.
I also need content test (may be copy constructor work,
but copy content is not correct, then crash test make no sense)*/
	bool CopyConstructorDynAtcoCommandArrayTest()
	{
		AtcoCommand atcCmd = AtcoCommand("2019-02-15__11-32-02-00:", "word sequence", "BAW52CV INIT_RESPONSE");

		// Create d1 with 10 elements
		DynAtcoCommandArray d1 = DynAtcoCommandArray(1);
		for (size_t i = 0; i < 10; i++)
		{
			d1.add(atcCmd);
		}

		// Copy d2 from d1
		DynAtcoCommandArray d2 = d1;

		// Check d2 is coppied
		for (int i = 0; i < 10; i++)
		{
			if (d2.getElementArray(i).getWordSequence().find("word sequence") == -1)
			{
				return false;
			}
		}
		if (d2.getSize() != 11)
		{
			return false;
		}
		cout << "Test copy constructor DynAtcoCommandArray      OK" << endl;
		return true;
	};

	/* Create an dynamic Ocurrence array d1 with 10 elements.
Use copy constructor, copy d1 to d2.Check if all elements
of d2 is correct copied from d1 and have same size with d1.

I dont want just check test crash when copy constructor not work.
I also need content test (may be copy constructor work,
but copy content is not correct, then crash test make no sense)*/
	bool CopyConstructorDynOcurrenceArrayTest()
	{
		Ocurrence ocur = Ocurrence("value", 5);

		// Create d1 with 10 elements
		DynOcurrenceArray d1 = DynOcurrenceArray(1);
		for (size_t i = 0; i < 10; i++)
		{
			d1.add(ocur);
		}

		// Copy d2 from d1
		DynOcurrenceArray d2 = d1;

		// Check d2 is coppied
		for (int i = 0; i < 10; i++)
		{
			if (d2.getElementArray(i).getValue().find("value") == -1)
			{
				return false;
			}
		}
		if (d2.getSize() != 11)
		{
			return false;
		}
		cout << "Test copy constructor DynOcurrenceArray        OK" << endl;
		return true;
	};

	/* Create an dynamic command array d1 with 10 elements.
Create an dynamic command array d2 with 20 elements.
Use assignment operator, assign d1 to d2.Check if all elements
of d2 is correct assigned from d1 and have same size with d1.*/
	bool AssignmentOperatorDynCommandArrayTest()
	{
		// Create d1 with 10 elements
		Command cmd1 = Command("BAW52CV INIT_RESPONSE");
		DynCommandArray d1 = DynCommandArray(1);
		for (size_t i = 0; i < 10; i++)
		{
			d1.add(cmd1);
		}

		// Create d2 with 20 elements, which are difference from d1 elements
		Command cmd2 = Command("NLY785J CORRECTION");
		DynCommandArray d2 = DynCommandArray(1);
		for (size_t i = 0; i < 20; i++)
		{
			d2.add(cmd2);
		}

		// Assign d2 to d1
		d2 = d1;

		// Check if size of d2 is now = size of d1
		// and all elements from d2 is now elements from d1
		if (d2.getSize() != 11)
		{
			return false;
		}
		for (int i = 0; i < d2.getSize() - 1; i++)
		{
			if (d2.getElementArray(i).getMainCommands().find("INIT_RESPONSE") == -1)
			{
				return false;
			};
		}
		cout << "Test assignment operator DynCommandArray       OK" << endl;
		return true;
	};

	/* Create an dynamic AtcoCommand array d1 with 10 elements.
Create an dynamic atcoCommand array d2 with 20 elements.
Use assignment operator, assign d1 to d2.Check if all elements
of d2 is correct assigned from d1 and have same size with d1.*/
	bool AssignmentOperatorDynAtcoCommandArrayTest()
	{
		// Create d1 with 10 elements
		AtcoCommand atcCmd1 = AtcoCommand("2019-02-15__11-32-02-00:", "word sequence", "BAW52CV INIT_RESPONSE");
		DynAtcoCommandArray d1 = DynAtcoCommandArray(1);
		for (size_t i = 0; i < 10; i++)
		{
			d1.add(atcCmd1);
		}

		// Create d2 with 20 elements, which are difference from d1 elements
		AtcoCommand atcCmd2 = AtcoCommand("2019-02-15__11-32-02-00:", "otherWordSequence", "BAW52CV INIT_RESPONSE");
		DynAtcoCommandArray d2 = DynAtcoCommandArray(1);
		for (size_t i = 0; i < 20; i++)
		{
			d2.add(atcCmd2);
		}

		// Assign d2 to d1
		d2 = d1;

		// Check if size of d2 is now = size of d1
		// and all elements from d2 is now elements from d1
		if (d2.getSize() != 11)
		{
			return false;
		}
		for (int i = 0; i < d2.getSize() - 1; i++)
		{
			if (d2.getElementArray(i).getWordSequence().find("word sequence") == -1)
			{
				return false;
			};
		}
		cout << "Test assignment operator DynAtcoCommandArray   OK" << endl;
		return true;
	};

	/* Create an dynamic Ocurrence array d1 with 10 elements.
Create an dynamic Ocurrence array d2 with 20 elements.
Use assignment operator, assign d1 to d2.Check if all elements
of d2 is correct assigned from d1 and have same size with d1.*/
	bool AssignmentOperatorDynOcurrenceArrayTest()
	{
		// Create d1 with 10 elements
		Ocurrence ocur1 = Ocurrence("value", 2);
		DynOcurrenceArray d1 = DynOcurrenceArray(1);
		for (size_t i = 0; i < 10; i++)
		{
			d1.add(ocur1);
		}

		// Create d2 with 20 elements, which are difference from d1 elements
		Ocurrence ocur2 = Ocurrence("otherValue", 2);
		DynOcurrenceArray d2 = DynOcurrenceArray(1);
		for (size_t i = 0; i < 20; i++)
		{
			d2.add(ocur2);
		}

		// Assign d2 to d1
		d2 = d1;

		// Check if size of d2 is now = size of d1
		// and all elements from d2 is now elements from d1
		if (d2.getSize() != 11)
		{
			return false;
		}
		for (int i = 0; i < d2.getSize() - 1; i++)
		{
			if (d2.getElementArray(i).getValue().find("value") == -1)
			{
				return false;
			};
		}
		cout << "Test assignment operator DynOcurrenceArray     OK" << endl;
		return true;
	};

	// Run all tests
	int runTests(string file)
	{
		UltilType test;
		string testFileURL = "shortTest.txt";
		string testString = readTextFile("testString.txt");

		// Test if testString is read
		if (testString.length() == 0)
		{
			system("Color 04");
			cout << "\nTest fileTest exist: Fail" << endl;
			return 0;
		}

		// Test if main text file exist
		if (!existsTest(file))
		{
			system("Color 04");
			cout << "Test text file exist: Fail" << endl;
			return 0;
		}

		// Test if resize AtcoCommand and Occurence method works
		if (!resizeAtcoCommandTest() || !resizeOcurrenceTest())
		{
			system("Color 04");
			cout << "Test resize method: Fail" << endl;
			return 0;
		}

		// Read test file and input to string to check functional method works
		readFileGetOutput(testFileURL, test);

		// Test if method can read more than 6 commands
		if (!CanReadMoreThanSixCommandTest(test))
		{
			system("Color 04");
			cout << "Test method can read more than 6 commands: Fail" << endl;
			return 0;
		}

		// Test if copy constructor of DynCommandArray works
		if (!CopyConstructorDynCommandArrayTest())
		{
			system("Color 04");
			cout << "Test copy constructor of DynCommandArray : Fail" << endl;
			return 0;
		}

		// Test if copy constructor of DynAtcoCommandArray works
		if (!CopyConstructorDynAtcoCommandArrayTest())
		{
			system("Color 04");
			cout << "Test copy constructor of DynAtcoCommandArray : Fail" << endl;
			return 0;
		}

		// Test if copy constructor of DynCommandArray works
		if (!CopyConstructorDynOcurrenceArrayTest())
		{
			system("Color 04");
			cout << "Test copy constructor of DynOcurrenceArray : Fail" << endl;
			return 0;
		}

		// Test if assignment operator of DynCommandArray works
		if (!AssignmentOperatorDynCommandArrayTest())
		{
			system("Color 04");
			cout << "Test assignment operator of DynCommandArray : Fail" << endl;
			return 0;
		}
		// Test if assignment operator of DynAtcoCommandArray works
		if (!AssignmentOperatorDynAtcoCommandArrayTest())
		{
			system("Color 04");
			cout << "Test assignment operator of DynAtcoCommandArray : Fail" << endl;
			return 0;
		}
		// Test if assignment operator of DynCommandArray works
		if (!AssignmentOperatorDynOcurrenceArrayTest())
		{
			system("Color 04");
			cout << "Test assignment operator of DynOcurrenceArray : Fail" << endl;
			return 0;
		}

		// Test if split method works
		if (!dateTimeSplitMethodTest(test, testString))
		{
			system("Color 04");
			cout << "Test split method: Fail" << endl;
			return 0;
		}

		// Test if read top occurence method work
		if (!topOcurrencesTest(test, testString))
		{
			system("Color 04");
			cout << "Test top Ocurrneces Method: Fail" << endl;
			return 0;
		}

		// Print out result if all test passed.
		system("Color 0A");
		cout << "\n    Cool! All tests passed." << endl;
		return 1;
	};

	// End test methods
	/*________________________________________________________*/

	/*Main method
---------------------------*/
	ReadAtCoCommand(string expect)
	{

		string defaultOpenFile = "./AtcoCommand/longTest.txt";

		// Check if input parameter require test
		if (expect == "--test")
		{
			runTests(defaultOpenFile);
		}
		// Check if input parameter require stress test
		else if (expect == "--stresstest")
		{
			while (1)
			{
				runTests(defaultOpenFile);
			}
		}
		else
		{
			// Read data and print out
			readFileGetOutput(expect, outputAtco);
			// cout << "\n Result:" << endl;
			// output.print();
		}
	}

	UltilType getOutputAtcoCommand()
	{
		return outputAtco;
	}

private:
	UltilType outputAtco;
};