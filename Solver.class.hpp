#ifndef __SOLVER_CLASS_HPP
# define __SOLVER_CLASS_HPP

#include <iostream>
#include <bitset>
#include "Rubik.class.hpp"
#include <list>

// edge's cubies (2) [12]: UR UF UL UB DR DF DL DB FR FL BR BL
// corner's cubies (3) [8]: UFR UFL UBR UBL  DFR DFL DBR DBL

class Solver
{
private:
    Rubik _base;
    const Rubik _solution;
    uint16_t _threshold;

    std::list<Rubik> _position;
    std::list<Rubik>::iterator it;

public:
    Solver(Rubik cube);
    ~Solver();
    void solve();
    int sumManhattanDistance(Rubik cube);
};

Solver::Solver(Rubik cube)
{
    _base = cube;
    Rubik _solution;
    _threshold = _base.getCost() + _base.getWeight(); // 0 + Sum Manhattan
}

Solver::~Solver()
{
     // Rubik begin = _position.begin();
	// Rubik state = begin->second;

    // Si elem == solution {print Solution}
    // Si elem.threshold > previous.threshold
        // Add elem to list
        // Si threshold = min.newThreshold
    // Sinon ça dégage
    _position.push_front(_base);
    while (_position.size() > 0){ // Tant qu'on a pas de solution
        it = _position.begin(); //it pointeur sur l'objet donc -> pour l'objet
        if (it->verif_soluce(_solution)){ //Sinon juste if weight == 0
            std::cout << "Solution Trouvé." << std::endl;
            exit(0);
        }

        // it->print_cube();

        _position.erase(it);
    }
}

void Solver::solve(){

}

# endif