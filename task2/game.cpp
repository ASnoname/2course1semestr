#include "game.hpp"

using namespace life;

	Game::Game():m(3),n(2),k(3),countIteration(10){

		queue.emplace_back();
	}

	void Game::load(std::string namefile){

		std::fstream input(namefile, std::ios::in);

		int index = -1;

		std::string x_file;
		std::string y_file;

		std::string m_file;
		std::string n_file;
		std::string k_file;

		std::string currentLine;

		while(getline(input, currentLine,'\n')){

			index = currentLine.find("FIELD",0);
			if (index != -1){
				index += strlen("FIELD");

				while(currentLine[index] == ' ') index++;

				while(currentLine[index] != ' '){

					x_file += currentLine[index];
					index++;
				}

				while(currentLine[index] == ' ') index++;

				while((currentLine[index] != ' ') && (currentLine[index] != '#') && (currentLine[index] != '\n')){

					x_file += currentLine[index];
					index++;
				}

				(queue.end()-1)->x_ = stoi(x_file); 
				(queue.end()-1)->y_ = stoi(y_file);
			}

			index = currentLine.find("RULES",0);
			if (index != -1){
				index += strlen("RULES");

				while(currentLine[index] == ' ') index++;

				while(currentLine[index] != ' '){

					m_file += currentLine[index];
					index++;
				}

				while(currentLine[index] == ' ') index++;

				while(currentLine[index] != ' '){

					n_file += currentLine[index];
					index++;
				}

				while(currentLine[index] == ' ') index++;

				while((currentLine[index] != ' ') && (currentLine[index] != '#') && (currentLine[index] != '\n')){

					k_file += currentLine[index];
					index++;
				}

				m = stoi(m_file); 
				n = stoi(n_file);
				k = stoi(k_file);
			}

		}

		input.close();

		std::fstream input2(namefile, std::ios::in);

		while (getline(input2, currentLine,'\n')){

			index = currentLine.find("SET",0);
			if (index != -1){
				index += strlen("SET"); 

				std::string setX;		
				std::string setY;

				while(currentLine[index] == ' ') index++;

				while(currentLine[index] != ' '){

					setX += currentLine[index];
					index++;
				}

				while(currentLine[index] == ' ') index++;

				while((currentLine[index] != ' ') && (currentLine[index] != '#') && (currentLine[index] != '\n')){

					setY += currentLine[index];
					index++;
				}

				bool a = true;

				if ((stoi(setX) >= (queue.end()-1)->x_) || (stoi(setY) >= (queue.end()-1)->y_))
					a = false;

				if (a)
					(queue.end()-1)->set(stoi(setX), stoi(setY));
			}
		}

		input2.close();
	}

	void Game::save(std::string namefile){

		std::fstream output (namefile,std::ios::out);

		if ((m != 3) || (n != 2) || (k != 3))
			output << "RULES " << m << " " << n << " " << k << '\n';

		if ((queue.end()-1)->x_ != 10 || (queue.end()-1)->y_ != 10)
			output << "FIELD " << (queue.end()-1)->x_ << " " << (queue.end()-1)->y_ << '\n';

		for (int i = 0; i < (queue.end()-1)->y_; ++i) 
			for (int j = 0; j < (queue.end()-1)->x_; ++j)
				if ((queue.end()-1)->array[(queue.end()-1)->x_*i+j] == aliveCell)
					output << "SET" << ' ' << j << ' ' << i << '\n';
		output.close();				
	}

	std::string helperForfindcmd(std::string in, int index){

		while(in[index] == ' ') index++;

		std::string name;
		while((in[index] != ' ') && (in[index] != '#') && (in[index] != '\n')){

			name += in[index];
			index++;
		}
		return name;
	}

	std::string findcmd(std::string in, std::string cmd){

		int index = -1;

		index = in.find(cmd,0);
		if (index != -1){

			index += cmd.length();
			return helperForfindcmd(in,index);
		}
		return ".";
	}

	Game::Game(std::string in):m(3),n(2),k(3),countIteration(10){ 

		queue.emplace_back();

		int m_cmd = -1; 
		int n_cmd = -1; 
		int k_cmd = -1; 
		int x_cmd = -1; 
		int y_cmd = -1; 

		std::string smth;
		int index;

		smth = findcmd(in,"--input");
		if (smth != ".")
			load(smth);

		smth = findcmd(in,"-if");
		if (smth != ".")
			load(smth);

		smth = findcmd(in,"--output");
		if (smth != ".")
			save(smth);

		smth = findcmd(in,"-o");
		if (smth != ".")
			save(smth);

		smth = findcmd(in,"--iterations");
		if (smth != ".")
			countIteration = stoi(smth);

		smth = findcmd(in,"-ic");
		if (smth != ".")
			countIteration = stoi(smth);

		index = in.find("--field",0);
		if (index != -1){

			index += strlen("--field");

			while(in[index] == ' ') index++;

			std::string name;
			while((in[index] != ' ') && (in[index] != '#') && (in[index] != '\n')){

				name += in[index];
				index++;
			}
			x_cmd = stoi(name);
			y_cmd = stoi(helperForfindcmd(in,index));
		}	

		index = in.find("-f",0);
		if (index != -1){

			index += strlen("-f");

			while(in[index] == ' ') index++;

			std::string name;
			while((in[index] != ' ') && (in[index] != '#') && (in[index] != '\n')){

				name += in[index];
				index++;
			}
			x_cmd = stoi(name);
			y_cmd = stoi(helperForfindcmd(in,index));
		}	

		smth = findcmd(in,"-m");
		if (smth != ".")
			m_cmd = stoi(smth);

		smth = findcmd(in,"-n");
		if (smth != ".")
			n_cmd = stoi(smth);

		smth = findcmd(in,"-k");
		if (smth != ".")
			k_cmd = stoi(smth);

		if (m_cmd != -1)
			m = m_cmd;

		if (n_cmd != -1)
			n = n_cmd;

		if (k_cmd != -1)
			k = k_cmd;

		if (x_cmd != -1)
		{
			(queue.end()-1)->x_ = x_cmd;
			(queue.end()-1)->y_ = y_cmd;
		}

		step(countIteration);
		show();
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