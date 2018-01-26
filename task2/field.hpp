#ifndef LIFE3
#define LIFE3

#include <vector>
#include <algorithm>

namespace life{

    const char diedCell = '.';
    const char aliveCell = '*';

	class Field{

	public:

		Field();
		Field(unsigned int x,unsigned int y);

		void set(unsigned int x, unsigned int y);
		void clear(unsigned int x, unsigned int y);
		void reset();

		std::vector<char> array;

		int x_; 
		int y_; 
	};

};

#endif 