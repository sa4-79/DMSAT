/*
 * Main.h
 *
 *  Created on: Sep 22, 2012
 *      Author: MacBookPro
 */

#ifndef MAIN_H_
#define MAIN_H_
#include <inttypes.h>
#include <errno.h>

#include <signal.h>
#include <zlib.h>

#include<vector>
#include "../utils/System.h"
#include "../utils/ParseUtils.h"
#include "../utils/Options.h"
#include "Dimacs.h"
#include "Solver.h"
#include <iostream>
#include "../core/SolverTypes.h"
using namespace std;
using namespace Minisat;

//static Solver* solver;
string getPaths(int pathLenght);
void printStats1(Solver& solver);
//void printStats1(Solver& solver);
int mainSolver(int argc, char** argv);
#endif /* MAIN_H_ */
