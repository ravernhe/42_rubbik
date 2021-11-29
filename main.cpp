#include "Rubik.class.hpp"
#include "Solver.class.hpp"

void command_parser(std::string commande){
    std::string contains = "FBUDLR'2";
    std::string tmp;

    if (commande.size() > 2048){
        std::cout << "Scramble invalid_1." << std::endl;
        exit(0);
    }
    for(int j= 0; j < commande.size(); ++j) {
            if(commande[j] != ' ')
                tmp += commande[j];
    }
    commande = tmp;

    if (commande[0] == '2' || commande[0] == '\''){
        std::cout << "Scramble invalid_2." << std::endl;
        exit(0);
    }
    for(int i = 0; commande[i]; i++){
        if (contains.find(commande[i]) >= contains.length()){
            std::cout << "Scramble invalid_3." << std::endl;
            exit(0);
        }
    }
    for(int i = 0; commande[i]; i++){
        if (commande[i] == '\'' && (commande[i + 1] == '\'' || commande[i + 1] == '2')){
            std::cout << "Scramble invalid_4." << std::endl;
            exit(0);
        }
        else if (commande[i] == '2' && (commande[i + 1] == '\'' || commande[i + 1] == '2')){
            std::cout << "Scramble invalid_5." << std::endl;
            exit(0);
        }
    }
}

int main(int ac, char ** av) {
    Rubik rubi;
    std::string list_move;

    if (ac != 2){
        std::cout << "Usage : ./a.out \"my_scramble\"" << std::endl;
        return 1;
    }
    list_move = av[1];
    command_parser(list_move);
    rubi.scramble(list_move);

    rubi.print_cube();
    Solver solve(rubi);
    solve.solve();
}