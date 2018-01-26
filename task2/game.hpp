#ifndef LIFE4
#define LIFE4

#include <deque>
#include <fstream>
#include <string>
#include "field.hpp"
#include <iostream>

namespace life{

	class Game{

		public:
		
			Game();
			Game(char**,int); 
			void newCommand(std::string);

		private:

			std::deque<Field> queue; 

			unsigned int m;
			unsigned int n;
			unsigned int k;

			unsigned int countIteration;

			void step(unsigned int);
			void back();
			void save(std::string);
			bool load(std::string);
			void solver(int,int);
			void show();
	};

}	

#endif 