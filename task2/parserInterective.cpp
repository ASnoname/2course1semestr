#include "parserInterective.hpp"

using namespace life;

	int counterCommandInCurrentLine(std::string command, std::string currentCMD){

		int indexCMD = -1;

		indexCMD = currentCMD.find(command);

		if (indexCMD != -1){

			if (currentCMD.find("reset",indexCMD+3) != -1)
				return -1;

			if (currentCMD.find("set",indexCMD+3) != -1)
				return -1;

			if (currentCMD.find("clear",indexCMD+3) != -1)
				return -1;
				
			if (currentCMD.find("step",indexCMD+3) != -1)
				return -1;
				
			if (currentCMD.find("back",indexCMD+3) != -1)
				return -1;

			if (currentCMD.find("save",indexCMD+3) != -1)
				return -1;

			if (currentCMD.find("load",indexCMD+3) != -1)
				return -1;

			if (currentCMD.find("rules",indexCMD+3) != -1)
				return -1;		

			return 0;						
		}

		return 0;
	}

	InteractiveMode::InteractiveMode(std::string currentCMD){

		int temp = 0;

		while(1){

			if ((counterCommandInCurrentLine("reset",currentCMD) == 0) && (cmdReset(currentCMD) == 0)){
				var_valid = 0; temp = 1; break;
			}

			if ((counterCommandInCurrentLine("set",currentCMD) == 0) && (cmdSet(currentCMD) == 0)){
				var_valid = 0; temp = 1; break;
			}

			if ((counterCommandInCurrentLine("clear",currentCMD) == 0) && (cmdClear(currentCMD) == 0)){
				var_valid = 0; temp = 1; break;
			}		

			if ((counterCommandInCurrentLine("step",currentCMD) == 0) && (cmdStep(currentCMD) == 0)){
				var_valid = 0; temp = 1; break;
			}

			if ((counterCommandInCurrentLine("back",currentCMD) == 0) && (cmdBack(currentCMD) == 0)){
				var_valid = 0; temp = 1; break;
			}

			if ((counterCommandInCurrentLine("save",currentCMD) == 0) && (cmdSave(currentCMD) == 0)){
				var_valid = 0; temp = 1; break;
			}

			if ((counterCommandInCurrentLine("load",currentCMD) == 0) && (cmdLoad(currentCMD) == 0)){
				var_valid = 0; temp = 1; break;
			}

			if ((counterCommandInCurrentLine("rules",currentCMD) == 0) && (cmdRules(currentCMD) == 0)){
				var_valid = 0; temp = 1; break;
			}

			if (temp == 0){

				std::cout << "Error parsing\n";
				var_valid = -1;
				break;
			}
		}						
	}

	int InteractiveMode::valid(){

		return this->var_valid;
	}

	std::string clearOfSpacesLeft(std::string currentCMD, std::string command){

		int index = currentCMD.find(command);
		int i = 0; 

		while ((i < index) && (currentCMD[i] == ' ')) i++;

		if (i != index)
			return "-1";
// std::cout << currentCMD << "\n";
		//currentCMD.substr(index + command.length(), currentCMD.length() - index + command.length());
		std::string a = currentCMD.substr(index + command.length());
// std::cout << a << "\n";
		return a;
	}

	int InteractiveMode::cmdReset(std::string currentCMD){

		std::string newLine = clearOfSpacesLeft(currentCMD, "reset");

		if (newLine == "-1")
			return -1;

		int index = newLine.length();
		int i = 0; 

		while ((i < index) && (newLine[i] == ' ')) i++;

		if (i != index)
			return -1;
		else return 0;
	}

	int parsingArguments(int index, std::string currentLine){
		
		while ((currentLine[index] == 32) && (index != currentLine.length()-1)) index++;
		if ((index == currentLine.length()-1) || (currentLine[index] < '0') || (currentLine[index] > '9'))
			return -1;

		std::string argument;
		while (currentLine[index] > '0' && currentLine[index] < '9'){

			argument += currentLine[index]; // проверить stoi
			index++;
		}

		return 0;
	}

	int helpLoad(std::string firstArgument){

		std::fstream input (firstArgument,std::ios::in);
		if (!input){
			std::cout << "Expected flag <string>, but failed to parse.\n";
			return -1;
		}

		std::string currentLine;
		int countFIELD = 0;
		int indexFIELD = -1;

		int countRULES = 0;
		int indexRULES = -1;

		int indexSET = -1;

		while (getline(input, currentLine,'#')){
			// начало FIELD
			indexFIELD = currentLine.find("FIELD",0);
			if (indexFIELD != -1){
				countFIELD++;
				if (countFIELD > 1) return -1;
				
				indexFIELD += strlen("FIELD");

				if (parsingArguments(indexFIELD, currentLine) == -1) //необходимо чтобы измененный индекс в функции был тем же индексом и тут!
					return -1;

				if(currentLine[indexFIELD] != 32) return -1;  // обязательный пробел между командой и аргументами

				if (parsingArguments(indexFIELD, currentLine) == -1)
					return -1;

				if ((indexFIELD != currentLine.length()-1) && (currentLine[indexFIELD] != ' '))
					return -1;
			}
			// конец FIELD

			// начало RULES
			indexRULES = currentLine.find("RULES",0);
			if (indexRULES != -1){
				countRULES++;
				if (countRULES > 1) return -1;
				
				indexRULES += strlen("RULES");

				if (parsingArguments(indexRULES, currentLine) == -1)
					return -1;

				if(currentLine[indexRULES] != 32) return -1;  // обязательный пробел между командой и аргументами

				if (parsingArguments(indexRULES, currentLine) == -1)
					return -1;

				if(currentLine[indexRULES] != 32) return -1;  // обязательный пробел между командой и аргументами

				if (parsingArguments(indexRULES, currentLine) == -1)
					return -1;

				if ((indexRULES != currentLine.length()-1) && (currentLine[indexRULES] != ' '))
					return -1;
			}
			// конец RULES

			// начало SET

			indexSET = currentLine.find("SET",0);
			if (indexSET != -1){
				
				indexSET += strlen("SET"); 
				if(currentLine[indexSET] != 32) return -1; // обязательный пробел между командой и аргументами

				if (parsingArguments(indexSET, currentLine) == -1)
					return -1;

				if(currentLine[indexSET] != 32) return -1;  // обязательный пробел между командой и аргументами

				if (parsingArguments(indexSET, currentLine) == -1)
					return -1;

				if ((indexSET != currentLine.length()-1) && (currentLine[indexSET] != ' '))
					return -1;
			}			
			// конец SET 			
		}	

		input.close(); //правильно ли я закрываю?

		return 0;
	}

	int forArguments(std::string newLine, int beginIndex, std::string intORstring){

		if (newLine[beginIndex] != ' ')
			return -1;

		int i = 0;
		int index = newLine.length();

		while ((i < index) && (newLine[i] == ' ')) i++;

		if (i == index)
			return -1;

		std::string firstArgument = "";

		while ((newLine[i] != ' ') && (i < index)){

			firstArgument += newLine[i];
			i++;
		}

		if (intORstring == "int")
		{
			try{
				stoi(firstArgument);
			}catch(std::invalid_argument){
				std::cout << "Expected argument <int>, but failed to parse.\n";
				return -1;
			}
		}

		if (intORstring == "stringLOAD")
		{
			if (helpLoad(firstArgument) == -1)
				return -1;
			else if (helpLoad(firstArgument) == 1)
				return 0;
		}

		beginIndex = i;

		return beginIndex;
	}

	int InteractiveMode::cmdSet(std::string currentCMD){

		std::string newLine = clearOfSpacesLeft(currentCMD, "set");

		if (newLine == "-1")
			return -1;

		int beginIndex;

		beginIndex = forArguments(newLine, 0, "int");
		if (beginIndex == -1)
			return -1;

		beginIndex = forArguments(newLine, beginIndex, "int");
		if (beginIndex == -1)
			return -1;

		return 0;
	}

	int InteractiveMode::cmdClear(std::string currentCMD){

		std::string newLine = clearOfSpacesLeft(currentCMD, "clear");

		if (newLine == "-1")
			return -1;

		int beginIndex;

		beginIndex = forArguments(newLine, 0, "int");
		if (beginIndex == -1)
			return -1;

		beginIndex = forArguments(newLine, beginIndex, "int");
		if (beginIndex == -1)
			return -1;

		return 0;
	}

	int InteractiveMode::cmdStep(std::string currentCMD){

		std::string newLine = clearOfSpacesLeft(currentCMD, "step");

		if (newLine == "-1")
			return -1;

		int beginIndex;
		
		beginIndex = forArguments(newLine, 0, "int");
		if (beginIndex == -1)
			return -1;

		return 0;
	}

	int InteractiveMode::cmdBack(std::string currentCMD){

		std::string newLine = clearOfSpacesLeft(currentCMD, "back");

		if (newLine == "-1")
			return -1;

		int index = newLine.length();
		int i = 0; 

		while ((i < index) && (newLine[i] == ' ')) i++;

		if (i != index)
			return -1;
		else return 0;
	}

	int InteractiveMode::cmdSave(std::string currentCMD){

		std::string newLine = clearOfSpacesLeft(currentCMD, "save");

		if (newLine == "-1")
			return -1;

		int beginIndex;
		
		beginIndex = forArguments(newLine, 0, "string");
		if (beginIndex == -1)
			return -1;

		return 0;
	}

	int InteractiveMode::cmdLoad(std::string currentCMD){

		std::string newLine = clearOfSpacesLeft(currentCMD, "save");

		if (newLine == "-1")
			return -1;

		int beginIndex;
		
		beginIndex = forArguments(newLine, 0, "stringLOAD");
		if (beginIndex == -1)
			return -1;

		return 0;
	}

	int InteractiveMode::cmdRules(std::string currentCMD){

		std::string newLine = clearOfSpacesLeft(currentCMD, "rules");

		if (newLine == "-1")
			return -1;

		int beginIndex;
		
		beginIndex = forArguments(newLine, 0, "int"); 
		if (beginIndex == -1)
			return -1;

		beginIndex = forArguments(newLine, beginIndex, "int");
		if (beginIndex == -1)
			return -1;

		beginIndex = forArguments(newLine, beginIndex, "int");
		if (beginIndex == -1)
			return -1;

		return 0;
	}
