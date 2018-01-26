#include "game.hpp"

using namespace life;

	Game::Game():m(3),n(2),k(3),countIteration(10){

		queue.emplace_back();
	}

	bool Game::load(std::string namefile){

		std::fstream input(namefile);

		int indexFIELD = -1;
		int indexRULES = -1;
		int indexSET = -1;

		std::string x_file;
		std::string y_file;

		std::string m_file;
		std::string n_file;
		std::string k_file;

		std::string currentLine;

		while(getline(input, currentLine,'#')){

			indexFIELD = currentLine.find("FIELD",0);
			if (indexFIELD != -1){
				indexFIELD += strlen("FIELD");

				while(currentLine[indexFIELD] == ' ') indexFIELD++;

				while(currentLine[indexFIELD] != ' '){

					x_file += currentLine[indexFIELD];
					indexFIELD++;
				}

				while(currentLine[indexFIELD] == ' ') indexFIELD++;

				while((currentLine[indexFIELD] != ' ') && (currentLine[indexFIELD] != '#') && (currentLine[indexFIELD] != '\n')){

					x_file += currentLine[indexFIELD];
					indexFIELD++;
				}

				queue[0].x_ = stoi(x_file); 
				queue[0].y_ = stoi(y_file);
			}

			indexRULES = currentLine.find("RULES",0);
			if (indexRULES != -1){
				indexRULES += strlen("RULES");

				while(currentLine[indexRULES] == ' ') indexRULES++;

				while(currentLine[indexRULES] != ' '){

					m_file += currentLine[indexRULES];
					indexRULES++;
				}

				while(currentLine[indexRULES] == ' ') indexRULES++;

				while(currentLine[indexRULES] != ' '){

					n_file += currentLine[indexRULES];
					indexRULES++;
				}

				while(currentLine[indexRULES] == ' ') indexRULES++;

				while((currentLine[indexRULES] != ' ') && (currentLine[indexRULES] != '#') && (currentLine[indexRULES] != '\n')){

					k_file += currentLine[indexRULES];
					indexRULES++;
				}

				m = stoi(m_file); 
				n = stoi(n_file);
				k = stoi(k_file);
			}

		}

		while (getline(input, currentLine,'#')){
			indexSET = currentLine.find("SET",0);
			if (indexSET != -1){
				indexSET += strlen("SET"); 

				std::string setX;		
				std::string setY;

				while(currentLine[indexSET] == ' ') indexSET++;

				while(currentLine[indexSET] != ' '){

					setX += currentLine[indexSET];
					indexSET++;
				}

				while(currentLine[indexSET] == ' ') indexSET++;

				while((currentLine[indexSET] != ' ') && (currentLine[indexSET] != '#') && (currentLine[indexSET] != '\n')){

					setY += currentLine[indexSET];
					indexSET++;
				}

				if ((stoi(setX) >= queue[0].x_) || (stoi(setY) >= queue[0].y_))
					return false;

				queue[0].set(stoi(setX), stoi(setY));
				return true;
			}
		}

		return true;
	}

	void Game::save(std::string namefile){

		std::fstream output (namefile,std::ios::out);

		if ((m != 3) || (n != 2) || (k != 3))
			output << "RULES " << m << " " << n << " " << k << std::endl;

		if (queue.end()->x_ != 10 || queue.end()->y_ != 10)
			output << "FIELD " << queue.end()->x_ << " " << queue.end()->y_ << std::endl;

		for (int i = 0; i < queue.end()->y_; ++i) // i - y-ая координата
			for (int j = 0; j < queue.end()->x_; ++j)
				if (queue.end()->array[queue.end()->x_*i+j] == aliveCell)
					output << "SET" << j << ' ' << i << std::endl;	
	}

	Game::Game(char** argv, int argc):m(3),n(2),k(3),countIteration(10){

		queue.emplace_back();

		unsigned int m_cmd = -1; 
		unsigned int n_cmd = -1; 
		unsigned int k_cmd = -1; 
		unsigned int x_cmd = -1; 
		unsigned int y_cmd = -1; 
		bool error = true;

		for (int i = 0; i < argc; ++i)
		{
			if ((std::string(argv[i]) == "--input") || (std::string(argv[i]) == "-if"))	
				if(!load(std::string(argv[++i]))) { 
					std::cout << "Error set"; 
					error = true;
					break;
				}	

			if ((std::string(argv[i]) == "--output") || (std::string(argv[i]) == "-o"))
				save(std::string(argv[++i]));

			if ((std::string(argv[i]) == "--iterations") || (std::string(argv[i]) == "-ic"))
				countIteration = stoi(std::string(argv[++i]));					

			if ((std::string(argv[i]) == "--field") || (std::string(argv[i]) == "-f")){

				x_cmd = stoi(std::string(argv[++i]));
				y_cmd = stoi(std::string(argv[++i]));
			}
				
			if (std::string(argv[i]) == "-m")
				m_cmd = stoi(std::string(argv[++i]));

			if (std::string(argv[i]) == "-n")
				n_cmd = stoi(std::string(argv[++i]));

			if (std::string(argv[i]) == "-k")	
				k_cmd = stoi(std::string(argv[++i]));								
		}

		if (m_cmd != -1)
			m = m_cmd;

		if (n_cmd != -1)
			n = n_cmd;

		if (k_cmd != -1)
			k = k_cmd;

		if (x_cmd != -1)
		{
			queue[0].x_ = x_cmd;
			queue[0].y_ = y_cmd;
		}
		if (error == true){
			step(countIteration);
			show();
		}
	}

	void Game::newCommand(std::string currentCmd){

		int index = -1;

		index = currentCmd.find("reset",0);
		if (index != -1)
			(queue.end()-1)->reset();

		index = currentCmd.find("set",0);
		if ((index > 0) && (currentCmd[index-1] == 'e')){}
		else if (index != -1)
		{
			index += strlen("set");

			std::string x_cmd; 
			std::string y_cmd;

			while(currentCmd[index] == ' ') index++;

			while(currentCmd[index] != ' '){

				x_cmd += currentCmd[index];
				index++;
			}

			while(currentCmd[index] == ' ') index++;

			while((currentCmd[index] != ' ') && (currentCmd[index] != '#') && (currentCmd[index] != '\n')){

				y_cmd += currentCmd[index];
				index++;
			}

			(queue.end()-1)->set(stoi(x_cmd), stoi(y_cmd));
		}

		index = currentCmd.find("clear",0);
		if (index != -1)
		{
			index += strlen("clear");

			std::string x_cmd; 
			std::string y_cmd;

			while(currentCmd[index] == ' ') index++;

			while(currentCmd[index] != ' '){

				x_cmd += currentCmd[index];
				index++;
			}

			while(currentCmd[index] == ' ') index++;

			while((currentCmd[index] != ' ') && (currentCmd[index] != '#') && (currentCmd[index] != '\n')){

				y_cmd += currentCmd[index];
				index++;
			}

			(queue.end()-1)->clear(stoi(x_cmd), stoi(y_cmd));
		}

		index = currentCmd.find("step",0);
		if (index != -1){ 
			index += strlen("step");

			std::string count_cmd;

			while(currentCmd[index] == ' ') index++;

			while((currentCmd[index] != ' ') && (currentCmd[index] != '#') && (currentCmd[index] != '\n')){

				count_cmd += currentCmd[index];
				index++;
			}

			countIteration = stoi(count_cmd);

			step(stoi(count_cmd));
		}

		index = currentCmd.find("back",0);
		if (index != -1)
			back();

		index = currentCmd.find("save",0);
		if (index != -1)
		{
			index += strlen("save");

			std::string name_cmd;

			while(currentCmd[index] == ' ') index++;

			while((currentCmd[index] != ' ') && (currentCmd[index] != '#') && (currentCmd[index] != '\n')){

				name_cmd += currentCmd[index];
				index++;
			}

			save(name_cmd);
		}

		index = currentCmd.find("load",0);
		if (index != -1)
		{
			index += strlen("load");

			std::string name_cmd;

			while(currentCmd[index] == ' ') index++;

			while((currentCmd[index] != ' ') && (currentCmd[index] != '#') && (currentCmd[index] != '\n')){

				name_cmd += currentCmd[index];
				index++;
			}

			load(name_cmd);
		}

		index = currentCmd.find("rules",0);
		if (index != -1)
		{
			index += strlen("rules");

			std::string m_cmd;
			std::string n_cmd;
			std::string k_cmd;

			while(currentCmd[index] == ' ') index++;

			while(currentCmd[index] != ' '){

				m_cmd += currentCmd[index];
				index++;
			}

			while(currentCmd[index] == ' ') index++;

			while(currentCmd[index] != ' '){

				n_cmd += currentCmd[index];
				index++;
			}

			while(currentCmd[index] == ' ') index++;

			while((currentCmd[index] != ' ') && (currentCmd[index] != '#') && (currentCmd[index] != '\n')){

				k_cmd += currentCmd[index];
				index++;
			}

			m = stoi(m_cmd);
			n = stoi(n_cmd);
			k = stoi(k_cmd);
		}

		show();
	}	

	void Game::back(){

		if (queue.size() > 1)
			queue.erase(queue.end()-1, queue.end());
		else std::cout << "Раньше команд не было.\n";
	}

	void Game::solver(int i, int j){

		std::vector<int> koo;

		if (i > 0 && j > 0)
			koo = {1,0,-1,0,0,1,1,1,-1,1,0,-1,1,-1,-1,-1};
		if (i == 0 && j > 0)
			koo = {1,0,1,1,1,-1,(queue.end()-1)->y_-1,0,(queue.end()-1)->y_-1,1,(queue.end()-1)->y_-1,-1,0,1,0,-1};
		if (i == (queue.end()-1)->y_-1 && j > 0)
			koo = {-1,0,-1,1,-1,-1,0,1,0,-1,1-((queue.end()-1)->y_-1),0,1-((queue.end()-1)->y_-1),-1,1-((queue.end()-1)->y_-1),1};
		if (i > 0 && j == 0)
			koo = {0,1,0,(queue.end()-1)->x_-1,1,1,1,(queue.end()-1)->x_-1,1,0,-1,1,-1,(queue.end()-1)->x_-1,-1,0};
		if (i > 0 && j == (queue.end()-1)->x_-1)
			koo = {0,-1,0,1-((queue.end()-1)->x_-1),1,-1,1,1-((queue.end()-1)->x_-1),1,0,-1,-1,-1,1-((queue.end()-1)->x_-1),-1,0};
		if (i == 0 && j == 0)
			koo = {0,1,0,(queue.end()-1)->x_-1,1,0,1,1,1,(queue.end()-1)->x_-1,(queue.end()-1)->y_-1,0,(queue.end()-1)->y_-1,1,(queue.end()-1)->y_-1,(queue.end()-1)->x_-1};
		if (i == 0 && j == (queue.end()-1)->x_-1)
			koo = {0,-1,0,1-((queue.end()-1)->x_-1),1,1-((queue.end()-1)->x_-1),1,-1,1,0,(queue.end()-1)->y_-1,1-((queue.end()-1)->x_-1),(queue.end()-1)->y_-1,-1,(queue.end()-1)->y_-1,0};
		if (i == (queue.end()-1)->y_-1 && j == 0)
			koo = {-1,0,-1,1,-1,(queue.end()-1)->x_-1,0,1,0,(queue.end()-1)->x_-1,1-((queue.end()-1)->y_-1),0,1-((queue.end()-1)->y_-1),1,1-((queue.end()-1)->y_-1),(queue.end()-1)->x_-1};
		if (i == (queue.end()-1)->y_-1 && j == (queue.end()-1)->x_-1)
			koo = {-1,0,-1,-1,-1,1-((queue.end()-1)->x_-1),0,-1,0,1-((queue.end()-1)->x_-1),1-((queue.end()-1)->y_-1),0,1-((queue.end()-1)->y_-1),-1,1-((queue.end()-1)->y_-1),1-((queue.end()-1)->x_-1)};

		int temp = 0;
		int temp1 = 0;

		for (int k = 0; k < koo.size(); ++k){ 

			int a = (queue.end()-1)->x_;
			int b = i+koo[k];
			int c = j+koo[k+1];

			if ((queue.end()-1)->array[a*b+c] == diedCell)
			{
				k++; 
				temp1++;
			}

			else if ((queue.end()-1)->array[a*b+c] == diedCell){
				k++; 
				temp++;
			}
		}	

		if (temp1 == m)
			(queue.end()-1)->array[(queue.end()-1)->x_*i+j] = aliveCell;
		if (temp < n) 
			(queue.end()-1)->array[(queue.end()-1)->x_*i+j] = diedCell;
		if (temp > k) 
			(queue.end()-1)->array[(queue.end()-1)->x_*i+j] = diedCell;
	}
	

	void Game::step(unsigned int number){

		for (int p = 0; p < number; ++p)
		{
			int a = (queue.end()-1)->x_;
			int b = (queue.end()-1)->y_;
		 	queue.emplace_back(a,b);
		 	queue.end()-1 = queue.end()-2;

			for (int i = 0; i < b; i++)
				for (int j = 0; j < a; j++)
					solver(i, j);		
		}
	}

	void Game::show(){

		std::cout << queue.size() << std::endl;

		for (int i = 0; i < (queue.end()-1)->y_; ++i)
		{
			for (int j = 0; j < (queue.end()-1)->x_; ++j)
				std::cout << (queue.end()-1)->array[(queue.end()-1)->x_*i+j];

			std::cout << '\n';
		}
	}
