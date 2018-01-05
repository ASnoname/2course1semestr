#ifndef LIFE3
#define LIFE3

#include <vector>

namespace life{

	class Life{

	public:

		Life();
		Life(unsigned int,unsigned int);

		void M(int);
		void N(int);
		void K(int);

	private:	

		void field(unsigned int,unsigned int);

		std::vector<char> array;

		int m;
		int n;
		int k;
		unsigned int x;
		unsigned int y;
	};

};

#endif 