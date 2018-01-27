#include "parserAuto.hpp"

using namespace life;

	AutoMode::AutoMode(char** flagsAndArguments, int argc){

		int counterWords = 1;

		while(1){

			if(std::string(flagsAndArguments[counterWords]) == "--input" || std::string(flagsAndArguments[counterWords]) == "-if") 
				counterWords = flagInput(counterWords, flagsAndArguments, argc);
			if((counterWords == -1) || (counterWords == argc)) break;

			if(std::string(flagsAndArguments[counterWords]) == "--output" || std::string(flagsAndArguments[counterWords]) == "-o") 
				counterWords = flagOutput(counterWords, flagsAndArguments, argc);
			if((counterWords == -1) || (counterWords == argc)) break;

			if(std::string(flagsAndArguments[counterWords]) == "--iterations" || std::string(flagsAndArguments[counterWords]) == "-ic") 
				counterWords = flagIterations(counterWords, flagsAndArguments, argc);
			if((counterWords == -1) || (counterWords == argc)) break;

			if(std::string(flagsAndArguments[counterWords]) == "--field" || std::string(flagsAndArguments[counterWords]) == "-f") 
				counterWords = flagField(counterWords, flagsAndArguments, argc);
			if((counterWords == -1) || (counterWords == argc)) break;

			if(std::string(flagsAndArguments[counterWords]) == "--help" || std::string(flagsAndArguments[counterWords]) == "-h") 
				counterWords = flagHelp(counterWords, flagsAndArguments, argc); 
			if((counterWords == -1) || (counterWords == argc)) break;

			if(std::string(flagsAndArguments[counterWords]) == "-m") 
				counterWords = flagM(counterWords, flagsAndArguments, argc);
			if((counterWords == -1) || (counterWords == argc)) break;

			if(std::string(flagsAndArguments[counterWords]) == "-n") 
				counterWords = flagN(counterWords, flagsAndArguments, argc);
			if((counterWords == -1) || (counterWords == argc)) break;

			if(std::string(flagsAndArguments[counterWords]) == "-k") 
				counterWords = flagK(counterWords, flagsAndArguments, argc);
			if((counterWords == -1) || (counterWords == argc)) break;

				if (counterWords == 1)
				{
					std::cout << "Failed to parse command line arguments: use --help or -h to get help\n";
					var_valid = false;
					break;
				}
		}

		if (counterWords == -1){
			std::cout << "Error parsing\n";
			var_valid = false;
		}
		else var_valid = true;
	}

	bool AutoMode::is_valid(){

		return var_valid;
	}

	int parsingArgumentsAuto(int index, std::string currentLine){
		
		while ((currentLine[index] == 32) && (index != currentLine.length()-1)) index++;
		if ((index == currentLine.length()-1) || (currentLine[index] < '0') || (currentLine[index] > '9'))
			return -1;

		std::string argument;
		while (currentLine[index] > '0' && currentLine[index] < '9'){

			argument += currentLine[index];
			index++;
		}

		return 0;
	}


	int AutoMode::flagInput(int counterWords, char* flagsAndArguments[], int argc){

		if (counterWords+1 > argc)
		{
			std::cout << "Expected flag <string>, but failed to parse.\n";
			return -1;
		}

		counterWords++;

		std::fstream input (flagsAndArguments[counterWords],std::ios::in);
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

				if (parsingArgumentsAuto(indexFIELD, currentLine) == -1) //необходимо чтобы измененный индекс в функции был тем же индексом и тут!
					return -1;

				if(currentLine[indexFIELD] != 32) return -1;  // обязательный пробел между командой и аргументами

				if (parsingArgumentsAuto(indexFIELD, currentLine) == -1)
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

				if (parsingArgumentsAuto(indexRULES, currentLine) == -1)
					return -1;

				if(currentLine[indexRULES] != 32) return -1;  // обязательный пробел между командой и аргументами

				if (parsingArgumentsAuto(indexRULES, currentLine) == -1)
					return -1;

				if(currentLine[indexRULES] != 32) return -1;  // обязательный пробел между командой и аргументами

				if (parsingArgumentsAuto(indexRULES, currentLine) == -1)
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

				if (parsingArgumentsAuto(indexSET, currentLine) == -1)
					return -1;

				if(currentLine[indexSET] != 32) return -1;  // обязательный пробел между командой и аргументами

				if (parsingArgumentsAuto(indexSET, currentLine) == -1)
					return -1;

				if ((indexSET != currentLine.length()-1) && (currentLine[indexSET] != ' '))
					return -1;
			}			
			// конец SET 			
		}	

		input.close();

		return ++counterWords;
	}
	
	int AutoMode::flagOutput(int counterWords, char* flagsAndArguments[], int argc){

		if (counterWords+1 > argc)
		{
			std::cout << "Expected flag <string>, but failed to parse.\n";
			return -1;
		}

		counterWords++;

		std::fstream output (flagsAndArguments[counterWords],std::ios::out);
		if (!output){
			std::cout << "Expected flag <string>, but failed to parse.\n";
			return -1;
		}

		output.close();

		return ++counterWords;
	}

	int AutoMode::flagIterations(int counterWords, char* flagsAndArguments[], int argc){

		if (counterWords+2 > argc)
		{
			std::cout << "Expected flag <int>, but failed to parse.\n";
			return -1;
		}

		counterWords++;

		try{
			stoi(std::string(flagsAndArguments[counterWords]));
		}catch(std::invalid_argument){
			std::cout << "Expected flag <int>, but failed to parse.\n";
			return -1;
		}

		return ++counterWords;
	}

	int AutoMode::flagField(int counterWords, char* flagsAndArguments[], int argc){

		if (counterWords+2 > argc)
		{
			std::cout << "Expected flag <int> <int>, but failed to parse.\n";
			return -1;
		}

		counterWords++;

		try{
			stoi(std::string(flagsAndArguments[counterWords]));
		}catch(std::invalid_argument){
			std::cout << "Expected flag <int>, but failed to parse.\n";
			return -1;
		}

		counterWords++;

		try{
			stoi(std::string(flagsAndArguments[counterWords]));
		}catch(std::invalid_argument){
			std::cout << "Expected flag <int>, but failed to parse.\n";
			return -1;
		}

		return ++counterWords;
	}

	void localHelp(int begin, int end){

		std::fstream input ("help",std::ios::in);
		std::string currentLine;
		int i = 1;
			
		while (begin > i){
			getline(input, currentLine);
			i++;
		}

		while (i <= end){
			getline(input, currentLine);
			i++;
			std::cout << currentLine << "\n";
		}

		input.close();
	}

	int AutoMode::flagHelp(int counterWords, char** flagsAndArguments, int argc){

		if (counterWords+1 == argc){
			localHelp(1, 57);

			return ++counterWords;
		}

		++counterWords;

		if(std::string(flagsAndArguments[counterWords]) == "--input" || std::string(flagsAndArguments[counterWords]) == "-if") 
			localHelp(1, 7);

		if(std::string(flagsAndArguments[counterWords]) == "--output" || std::string(flagsAndArguments[counterWords]) == "-o") 
			localHelp(8, 15);

		if(std::string(flagsAndArguments[counterWords]) == "--iterations" || std::string(flagsAndArguments[counterWords]) == "-ic") 
			localHelp(16, 23);

		if(std::string(flagsAndArguments[counterWords]) == "--field" || std::string(flagsAndArguments[counterWords]) == "-f") 
			localHelp(24, 31);

		if(std::string(flagsAndArguments[counterWords]) == "--help" || std::string(flagsAndArguments[counterWords]) == "-h") 
			localHelp(32, 37);

		if(std::string(flagsAndArguments[counterWords]) == "-m") 
			localHelp(38, 44);

		if(std::string(flagsAndArguments[counterWords]) == "-n") 
			localHelp(45, 51);

		if(std::string(flagsAndArguments[counterWords]) == "-k") 
			localHelp(51, 57);

		return ++counterWords;
	}

	int AutoMode::flagM(int counterWords, char* flagsAndArguments[], int argc){

		if (counterWords+1 > argc)
		{
			std::cout << "Expected flag <int>, but failed to parse.\n";
			return -1;
		}

		counterWords++;

		try{
			stoi(std::string(flagsAndArguments[counterWords]));
		}catch(std::invalid_argument){
			std::cout << "Expected flag <int>, but failed to parse.\n";
			return -1;
		}

		return ++counterWords;	
	}

	int AutoMode::flagN(int counterWords, char* flagsAndArguments[], int argc){

		if (counterWords+1 > argc)
		{
			std::cout << "Expected flag <int>, but failed to parse.\n";
			return -1;
		}

		counterWords++;

		try{
			stoi(std::string(flagsAndArguments[counterWords]));
		}catch(std::invalid_argument){
			std::cout << "Expected flag <int>, but failed to parse.\n";
			return -1;
		}

		return ++counterWords;
	}

	int AutoMode::flagK(int counterWords, char* flagsAndArguments[], int argc){

		if (counterWords+1 > argc)
		{
			std::cout << "Expected flag <int>, but failed to parse.\n";
			return -1;
		}

		counterWords++;

		try{
			stoi(std::string(flagsAndArguments[counterWords]));
		}catch(std::invalid_argument){
			std::cout << "Expected flag <int>, but failed to parse.\n";
			return -1;
		}

		return ++counterWords;
	}					