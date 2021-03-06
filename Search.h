/*
 * Gunborg - UCI chess engine
 * Copyright (C) 2013-2014 Torbjörn Nilsson
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Search.h
 *
 *  Created on: Jan 11, 2014
 *      Author: Torbjörn Nilsson
 */

#ifndef SEARCH_H_
#define SEARCH_H_

#include "board.h"
#include "Cache.h"
#include <atomic>
#include <chrono>
#include <string>

namespace gunborg {

class Search {

private:
	std::chrono::high_resolution_clock clock;
	std::chrono::high_resolution_clock::time_point start;
	std::string best_move;
	int node_count;
	int quiescence_node_count;
	int total_generated_moves;

	int alphaBeta(bool white_turn, int depth, int alpha, int beta, Board& board, Transposition *tt, bool null_move_in_branch, Move (&killers)[32][2], int (&history)[64][64], int ply);
	int capture_quiescence_eval_search(bool white_turn, int alpha, int beta, Board& board);

	bool time_to_stop();

public:
	Search();
	std::atomic_bool should_run;
	int max_think_time_ms;

	void search_best_move(const Board& board, const bool white_turn, list history);

	virtual ~Search();
};

} /* namespace gunborg */
#endif /* SEARCH_H_ */
