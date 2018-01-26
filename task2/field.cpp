#include "field.hpp"
#include "game.hpp"

using namespace life;

	Field::Field():x_(10),y_(10){

   		for (int i = 0; i < x_*y_; ++i)
   			array.push_back(diedCell);
	}

	Field::Field(unsigned int x, unsigned int y): x_(x), y_(y) {
 
		for (int i = 0; i < x_*y_; ++i)
   			array.push_back(diedCell);
	}

	void Field::set(unsigned int x, unsigned int y){

		if ((x >= x_) || (y >= y_)) Field::reset();

		array[x_*y+x] = aliveCell;
	}

	void Field::clear(unsigned int x, unsigned int y){

		if ((x >= x_) || (y >= y_)) Field::reset();

		array[x_*y+x] = diedCell;
	}

	void Field::reset(){

		std::fill(array.begin(), array.end(), diedCell);
	}