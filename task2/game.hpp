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
			Game(std::string); 
			void newCommand(std::string);

		private:

			std::deque<Field> queue; 

			int m;
			int n;
			int k;

			int countIteration;

			void step(unsigned int);
			void back();
			void save(std::string);
			void load(std::string);
			void solver(int,int);
			void show();
	};

}	

#endif 