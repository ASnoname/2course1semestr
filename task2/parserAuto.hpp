#ifndef LIFE1
#define LIFE1

#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

namespace life{

	class AutoMode {

		public:

			AutoMode(char**, int);
			int validAuto();
			
		private: 

			int flagInput(int, char**, int);
			int flagOutput(int, char**, int);
			int flagIterations(int, char**, int);
			int flagField(int, char**, int);
			int flagHelp(int, char**, int);
			int flagM(int, char**, int);
			int flagN(int, char**, int);
			int flagK(int, char**, int);

			int var_validAuto;
	};
};	

#endif 