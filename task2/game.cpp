#include "game.hpp"

using namespace life;

	Life::Life(){

		std::vector<char> array(10*10, '.');
		M(3);
		N(2);
		K(3);
		field(10,10);
	}

	Life::Life(unsigned int x,unsigned int y){
 
		std::vector<char> array(10*10, '.');

		M(3);
		N(2);
		K(3);
		field(x,y);
	}

	void Life::M(int userM){

		this->m = userM;
	}

	void Life::N(int userN){

		this->n = userN;
	}

	void Life::K(int userK){

		this->k = userK;
	}	

	void Life::field(unsigned int userX,unsigned int userY){

		this->x = userX; // кол-во столбцов
		this->y = userY; // кол-во строк
	}
