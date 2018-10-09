#include "settings.hpp"
#include <iostream>

using namespace std;


Settings::Settings() : solver() {
	string field = ".,.,.,.,.,.,.,.,.,.,.,.,.,.,.,.,.,.,.,.,.,.,.,.,.,.,.,.,.,.,.,.,.,.,.,.,.,.,.,.,.,.";
	this->field = split(field, ',');
}

void Settings::run() {
	string line;
	while (getline(cin, line)) {
		vector<string> command = split(line, ' ');
		//Note: not all settings communicated by the engine are parsed.
		if (command[0] == "settings" && command[1] == "your_botid") {
			this->bot_id = stoi(command[2]);
			this->max_score = 1;
		}
		else if (command[0] == "update" && command[1] == "game" && command[2] == "round") {
			this->rond = stoi(command[3]);
			}
		else if (command[0] == "update" && command[1] == "game" && command[2] == "field") {
			vector<string> tempField = split(command[3], ',');
			this->position += get_new_pos(tempField);	//this returns where the enemy bot made its move
														//and updates the current field position
		    field = tempField;//updates the internal field
		}
		else if (command[0] == "action" && command[1] == "move") {
		    //unsigned long long start_time = getTimeMicrosec(); //uncoment if want to evaluate the time taken.
			int best_move = make_move();
			this->position += update_pos(best_move);
			//unsigned long long end_time = getTimeMicrosec();
		    //cerr << "time taken: "<< (end_time-start_time)<<endl;
			cout << "place_disc " << best_move << endl;
		}
	}
}

/*
Returns where the enemy bot made its move. In the case where we're the first player
at the beggining of the game it returns an empty string.
*/
string Settings::get_new_pos(vector<string> &update_field_vector) {

	for (int i = 0; i < update_field_vector.size(); i++) {
		if (this->field[i] != update_field_vector[i]) {
			return to_string(((i % 7) + 1)); //returns the column as a string
		}
	}
	return "";//runs when both fields are equal. 
			  //Happens at the begginning if we are first player.
}

/*
updates the internal field as well as returns a string of the column.
*/
string Settings::update_pos(int &pos) {
	for (int i = (42+(pos-7)); i >= 0; i -= 7) {
		if (this->field[i] == ".") {
			this->field[i] = to_string(this->bot_id);
			return to_string(pos+1);
		}
	}
}

int Settings::make_move() {
	string poss_move;
	int best_move;
	int score;
	char col;
	unsigned int eval;
	poss_move = this->position;
	if (this->bot_id == 0 && this->rond < 4) {
		return 3;
	}
	else if (this->bot_id == 1 && this->rond < 3) {
		return 3;
	}
	poss_move.append("4");
	for (int i = 0; i < 7; i++) {
		poss_move.back() = this->columns[i];//will change the position as if the col in columns[i] was played.
		Position *P = new Position();
		eval = P->play(poss_move);

		if (eval == poss_move.size()){
			//means it is a legal move
		    solver.reset();
		    score = solver.solve(*P, false);
		    delete P;

            if (this->max_score <= score) {
		        this->max_score = score;
			    col = poss_move.back();
			}
		}
		else if (eval == 8){//means it is winning move
		    col = poss_move.back();
		    best_move = ctoi(col);
		    return (best_move-1);
            
		}
	}
	best_move = ctoi(col); //char converted to int
	return (best_move - 1);
}

/*
Returns a vector version of game field.
*/
vector<string> Settings::split(const string &s, char delim) {
	vector<string> elems;
	stringstream ss(s);
	string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

int Settings::ctoi(char &col){
    if (col == '1'){
        return 1;
    }
    else if (col == '2'){
        return 2;
    }
    else if (col == '3'){
        return 3;
    }
    else if (col == '4'){
        return 4;
    }
    else if (col == '5'){
        return 5;
    }
    else if (col == '6'){
        return 6;
    }
    else if (col == '7'){
        return 7;
    }
}
/*
unsigned long long Settings::getTimeMicrosec() {
	timeval NOW;
	gettimeofday(&NOW, NULL);
	return NOW.tv_sec * 1000000LL + NOW.tv_usec;
}
*/