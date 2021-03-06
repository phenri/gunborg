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
 * eval.h
 *
 *  Created on: Jan 18, 2014
 *      Author: Torbjörn Nilsson
 */

#ifndef EVAL_H_
#define EVAL_H_

#include "board.h"

static const int DOUBLED_PAWN_PENALTY = 10;
static const int ISOLATED_PAWN_PENALTY = 5;
static const int PROTECTED_PAWN_BONUS = 2;
static const int PASSED_PAWN_BONUS = 35;
static const int OPEN_FILE_BONUS = 15;
static const int SEMI_OPEN_FILE_BONUS = 7;

// the value of a white pawn at all squares
static const int WHITE_PAWN_SQUARE_TABLE[] = {
		// A1
		100, 100, 100, 100, 100, 100, 100, 100, // H1
		100, 100, 100, 100, 100, 100, 100, 100,
		101, 103, 104, 107, 107, 104, 103, 101,
		102, 105, 106, 111, 111, 106, 105, 102,
		103, 107, 109, 112, 112, 109, 107, 103,
		105, 109, 111, 113, 113, 111, 109, 105,
		107, 111, 113, 113,	113, 113, 111, 107,
  /*A8*/100, 100, 100, 100, 100, 100, 100, 100 // H8
		};

// the value of a black pawn at all squares
static const int BLACK_PAWN_SQUARE_TABLE[] = {
		// A1
		100, 100, 100, 100, 100, 100, 100, 100, // H1
		107, 111, 113, 113, 113, 113, 111, 107,
		105, 109, 111, 113, 113, 111, 109, 105,
		103, 107, 109, 112, 112, 109, 107, 103,
		102, 105, 106, 111, 111, 106, 105, 102,
		101, 103, 104, 107, 107, 104, 103, 101,
		100, 100, 100, 100, 100, 100, 100, 100,
  /*A8*/100, 100, 100, 100, 100, 100, 100, 100 // H8
		};

// affect elo negative right now, test again when retrying last move at alpha/beta fail is implemented
static const int KNIGHT_SQUARE_TABLE[] = {
		290, 295, 295, 295, 295, 295, 295, 290,
		295, 300, 300, 300, 300, 300, 300, 295,
		295, 300, 309, 309, 309, 309, 300, 295,
		295, 300, 309, 312, 312, 309, 300, 295,
		295, 300, 309, 312, 312, 309, 300, 295,
		295, 300, 309, 309, 309, 309, 300, 295,
		295, 300, 300, 300, 300, 300, 300, 295,
		290, 295, 295, 295, 295, 295, 295, 290, };

static const int BISHOP_SQUARE_TABLE[] = {
		275, 295, 295, 295, 295, 295, 295, 275,
		295, 300, 300, 300, 300, 306, 300, 295,
		295, 300, 300, 300, 300, 300, 300, 295,
		295, 300, 300, 300, 300, 300, 300, 295,
		295, 300, 300, 300, 300, 300, 300, 295,
		295, 300, 300, 300, 300, 300, 300, 295,
		295, 300, 300, 300, 300, 300, 300, 295,
		275, 295, 295, 295, 295, 295, 295, 275, };

static const int WHITE_ROOK_SQUARE_TABLE[] = {
		// A1
		500, 500, 500, 510, 510, 500, 500, 500,
		500, 500, 500, 500, 500, 500, 500, 500,
		500, 500, 500, 500, 500, 500, 500, 500,
		500, 500, 500, 500, 500, 500, 500, 500,
		500, 500, 500, 500, 500, 500, 500, 500,
		500, 500, 500, 500, 500, 500, 500, 500,
		515, 515, 515, 515, 515, 515, 515, 515,
		500, 500, 500, 500, 500, 500, 500, 500, }; //H8

static const int BLACK_ROOK_SQUARE_TABLE[] = {
		// A1
		500, 500, 500, 500, 500, 500, 500, 500,
		515, 515, 515, 515, 515, 515, 515, 515,
		500, 500, 500, 500, 500, 500, 500, 500,
		500, 500, 500, 500, 500, 500, 500, 500,
		500, 500, 500, 500, 500, 500, 500, 500,
		500, 500, 500, 500, 500, 500, 500, 500,
		500, 500, 500, 500, 500, 500, 500, 500,
		500, 500, 500, 510, 510, 500, 500, 500, }; //H8

static const int KING_SQUARE_TABLE_ENDGAME[] = {
		9980, 9990, 9990, 9990, 9990, 9990, 9990, 9980,
		9990, 9995, 9995, 9995, 9995, 9995, 9995, 9990,
		9995, 10000, 10000, 10005, 10005, 10000, 10000, 9995,
		9995, 10005, 10005, 10010, 10010, 10005, 10005, 9995,
		9995, 10005, 10005, 10010, 10010, 10005, 10005, 9995,
		9995, 10000, 10000, 10005, 10005, 10000, 10000, 9995,
		9990, 9995, 9995, 9995, 9995, 9995, 9995, 9990,
		9980, 9990, 9990, 9990, 9990, 9990, 9990, 9980
};

int evaluate(const Board& board);

#endif /* EVAL_H_ */
