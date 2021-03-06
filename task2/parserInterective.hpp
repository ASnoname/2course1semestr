#ifndef LIFE2
#define LIFE2

#include <cstring>
#include <string>
#include <fstream>
#include <iostream>

namespace life {

	class InteractiveMode {

		public:

			InteractiveMode(std::string);
			bool is_valid();

		private:

			int cmdReset(std::string);
			int cmdSet(std::string);
			int cmdClear(std::string);
			int cmdStep(std::string);
			int cmdBack(std::string);
			int cmdSave(std::string);
			int cmdLoad(std::string);
			int cmdRules(std::string);

			bool var_valid;
	};
	
};	

#endif 
