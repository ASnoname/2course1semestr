#include "game.hpp"
#include "parserAuto.hpp"
#include "parserInterective.hpp"

using namespace life;

int main(int argc, char** argv)
{

	std::string in;

	if (argc > 1){
		
	 	AutoMode hello(argv,argc);

		if (!hello.is_valid())
		 	return 0;

		if ((std::string(argv[0]) == "--help") || (std::string(argv[0]) == "-h"))
			return 0;

		for (int i = 1; i < argc; ++i)
			in = in + argv[i] + ' ';

		Game inGame(in);
	}
	else {

		Game inGame;

		while(true){

			getline(std::cin, in);
			if(in == "exit") break;
			InteractiveMode hello2(in);
			if (!hello2.is_valid())
			 	return 0;

			inGame.newCommand(in);
		}	 
	}

	return 0;
}
