/*
Interface that works with Pascal Pons Connect4 Solver. Intended to communicate with Riddles.io Connect4(four in a row) Engine.
The Solver only needs to be passed the position which it evaluates and returns a score. The position is encoded in the form of the
order the columns have been played in so far. Therefore In order to chose the best possible move, one needs to take the current position
and add a potential column as if the move was played. One then needs to do that for all playable columns and chose the one with the best score.
*/
#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "solver.hpp"
#include <string>
#include <sstream>
#include <vector>

using namespace GameSolver::Connect4;

class Settings {

	int bot_id;
	int rond;//round
	int score;
	int max_score;
	std::string position = "";
	std::string columns = "4536271";//Will be used when evaluating possible next moves.
	std::vector<std::string> field;
public:
	Settings();
	Solver solver;
	void run();
	/*
	Returns where the enemy bot made its move. In the case where we're the first player
	at the beggining of the game it returns an empty string.
	*/
	std::string get_new_pos(std::vector<std::string> &update_field_vector);
	/*
	updates the internal field as well as returns a string of the column.
	*/
	std::string update_pos(int &pos);
	/*
	Returns the best move using Pascal Pons Connect4 solver.
	*/
	int make_move();
	/*
	Returns a vector version of game field.
	*/
	std::vector<std::string> split(const std::string &s, char delim);

	/*
	Simply returns an int version of a passed char.
	*/
	int ctoi(char &col);

	//unsigned long long getTimeMicrosec();
};

#endif // !SETTINGS_HPP