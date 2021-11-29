#ifndef __RUBIK_CLASS_HPP
# define __RUBIK_CLASS_HPP

#include <iostream>
#include <bitset>

// edge's cubies [12][2]: UR UF UL UB DR DF DL DB FR FL BR BL
// corner's cubies [8][3]: UFR UFL UBR UBL  DFR DFL DBR DBL

class Rubik
{
private:
    uint32_t _front;
    uint32_t _back;
    uint32_t _up;
    uint32_t _down;
    uint32_t _left;
    uint32_t _right;

    uint16_t    _cost;
	uint16_t    _weight;
    void	_calculateWeight( void );
    int _edge[12];
    int _corner[8];

public:
    Rubik();
    Rubik(const Rubik *parent);
    ~Rubik();
    void up();
    void down();

    void left();
    void right();

    void front();
    void back();
    void print_cube();
    void move_cube(char move, int nb);
    void scramble(std::string list_move);
    uint16_t    getCost(void) const;
    uint16_t    getWeight(void) const;
    int verif_soluce(const Rubik soluce);
    void count_edge();
    void count_corner();
};

// 0001 rouge
// 0011 orange
// 0111 jaune
// 1111 vert
// 0010 bleu
// 0110 blanc
Rubik::Rubik()
{
    _front = 0b00010001000100010001000100010001;
    _back = 0b00110011001100110011001100110011;
    _up = 0b01110111011101110111011101110111;
    _down = 0b11111111111111111111111111111111;
    _left = 0b00100010001000100010001000100010;
    _right = 0b01100110011001100110011001100110;

    _cost = 0;
    count_edge();
    count_corner();
}

Rubik::Rubik(const Rubik * parent)
{
    _front = parent->_front;
    _back = parent->_back;
    _up = parent->_up;
    _down = parent->_down;
    _left = parent->_left;
    _right = parent->_right;

    _cost = parent->_cost + 1;
    count_edge();
    count_corner();
}

Rubik::~Rubik()
{
}

void Rubik::up(){
    //Face Down, Rien
    // Face Up, Barrel Rool
    _up = (((_up & 0XF000F000) >> 8) | ((_up & 0X0F000000) >> 12) | ((_up & 0X00F00000) >> 20) | ((_up & 0X000F000F) << 8) | ((_up & 0X000000F0) << 12) | ((_up & 0X00000F00) << 20));

    // Save bits [31,20]
    uint32_t mask = 0XFFF00000;
    uint32_t front_save = (_front & mask);
    uint32_t left_save = (_left & mask);
    uint32_t back_save = (_back & mask);
    uint32_t right_save = (_right & mask);

    _front = (right_save | (_front & ~mask));
    _left = (front_save | (_left & ~mask));
    _back = (left_save | (_back & ~mask));
    _right = (back_save | (_right & ~mask));
}

void Rubik::down(){
    _down = (((_down & 0XF000F000) >> 8) | ((_down & 0X0F000000) >> 12) | ((_down & 0X00F00000) >> 20) | ((_down & 0X000F000F) << 8) | ((_down & 0X000000F0) << 12) | ((_down & 0X00000F00) << 20));

    uint32_t mask = 0X00000FFF;
    uint32_t front_save = (_front & mask);
    uint32_t left_save = (_left & mask);
    uint32_t back_save = (_back & mask);
    uint32_t right_save = (_right & mask);

    _front = (left_save | (_front & ~mask));
    _left = (back_save | (_left & ~mask));
    _back = (right_save | (_back & ~mask));
    _right = (front_save | (_right & ~mask));
}

void Rubik::left(){
    _left = (((_left & 0XF000F000) >> 8) | ((_left & 0X0F000000) >> 12) | ((_left & 0X00F00000) >> 20) | ((_left & 0X000F000F) << 8) | ((_left & 0X000000F0) << 12) | ((_left & 0X00000F00) << 20));

    uint32_t mask = 0XF00F0F00;
    uint32_t front_save = (_front & mask);
    uint32_t up_save = (_up & mask);
    uint32_t back_save = (_back & mask);
    uint32_t down_save = (_down & mask);

    _front = (up_save | (_front & ~mask));
    _up = (back_save | (_up & ~mask));
    _back = (down_save | (_back & ~mask));
    _down = (front_save | (_down & ~mask));
}

void Rubik::right(){
    _right = (((_right & 0XF000F000) >> 8) | ((_right & 0X0F000000) >> 12) | ((_right & 0X00F00000) >> 20) | ((_right & 0X000F000F) << 8) | ((_right & 0X000000F0) << 12) | ((_right & 0X00000F00) << 20));

    uint32_t mask = 0X00F0F00F;
    uint32_t front_save = (_front & mask);
    uint32_t up_save = (_up & mask);
    uint32_t back_save = (_back & mask);
    uint32_t down_save = (_down & mask);

    _front = (down_save | (_front & ~mask));
    _up = (front_save | (_up & ~mask));
    _back = (up_save | (_back & ~mask));
    _down = (back_save | (_down & ~mask));
}

void Rubik::front(){
    _front = (((_front & 0XF000F000) >> 8) | ((_front & 0X0F000000) >> 12) | ((_front & 0X00F00000) >> 20) | ((_front & 0X000F000F) << 8) | ((_front & 0X000000F0) << 12) | ((_front & 0X00000F00) << 20));

    uint32_t mask = 0XF00F0F00;
    uint32_t left_save = (_left & mask);
    uint32_t up_save = (_up & mask);
    uint32_t right_save = (_right & mask);
    uint32_t down_save = (_down & mask);

    _up = (left_save | (_up & ~mask));
    // std::bitset<32> d(left_save | (_up & ~mask)); std::cout << d << std::endl;
    _right = (up_save | (_right & ~mask));
    _down= (right_save | (_down & ~mask));
    _left = (down_save | (_left & ~mask));
}

void Rubik::back(){
    _back = (((_back & 0XF000F000) >> 8) | ((_back & 0X0F000000) >> 12) | ((_back & 0X00F00000) >> 20) | ((_back & 0X000F000F) << 8) | ((_back & 0X000000F0) << 12) | ((_back & 0X00000F00) << 20));

    uint32_t mask = 0X00F0F00F;
    uint32_t left_save = (_left & mask);
    uint32_t up_save = (_up & mask);
    uint32_t right_save = (_right & mask);
    uint32_t down_save = (_down & mask);

    _up = (right_save | (_up & ~mask));
    _right = (down_save | (_right & ~mask));
    _down= (left_save | (_down & ~mask));
    _left = (up_save | (_left & ~mask));
}

void Rubik::print_cube(){
    std::bitset<32> u(_up); std::cout << u << std::endl;
    std::bitset<32> f(_front); std::cout << f << std::endl;
    std::bitset<32> r(_right); std::cout << r << std::endl;
    std::bitset<32> b(_back); std::cout << b << std::endl;
    std::bitset<32> l(_left); std::cout << l << std::endl;
    std::bitset<32> d(_down); std::cout << d << std::endl << std::endl;
}

void Rubik::move_cube(char move, int nb){
    switch (move){
        case 'U':
            for (int i=0; i < nb; i++)
                up();
            break;
        case 'D':
            for (int i=0; i < nb; i++)
                down();
            break;
        case 'F':
            for (int i=0; i < nb; i++)
                front();
            break;
        case 'B':
            for (int i=0; i < nb; i++)
                back();
            break;
        case 'L':
            for (int i=0; i < nb; i++)
                left();
            break;
        case 'R':
            for (int i=0; i < nb; i++)
                right();
            break;
        default :
            break ;
    }
}

void Rubik::scramble(std::string list_move){
    int nb;
    for(int i = 0; list_move[i]; i++){
        nb = 1;
        if (list_move[i] == '2' || list_move[i] == '\'')
            i++;
        if (list_move[i + 1] == '2')
            nb = 2;
        else if (list_move[i + 1] == '\'')
            nb = 3;
        move_cube(list_move[i], nb);
    }
}

int Rubik::verif_soluce(const Rubik soluce){ // & | ^| et check si == 0
    int verif;

    if (_front != soluce._front)
        verif++;
    if (_back != soluce._back)
        verif++;
    if (_left != soluce._left)
        verif++;
    if (_right != soluce._right)
        verif++;
    if (_up != soluce._up)
        verif++;
    if (_down != soluce._down)
        verif++;
    if(verif == 0)
        return 1;
    return 0;
}

uint16_t    Rubik::getCost( void ) const {
	return ( _cost ); // Cost Parent + 1
}

// int Rubik::sumManhattanDistanceEdge/Corner(){
//     int sum = 0;
//     for (int i = 0; i < 6; i++){

//     }
//     return sum;
// }

uint16_t    Rubik::getWeight( void ) const {
    int sum = 0;
    for (int i = 0; i < 6; i++){

    }
	return ( _weight ); // Sum Manhattan Max Edge/Corner
}

void Rubik::count_edge(){ // edge's cubies [12][2]: UR UF UL UB DR DF DL DB FR FL BR BL
    _edge[0] = (_up & 0X0000F000) + (_right & 0X0F000000);
    _edge[1] = (_up & 0X000000F0) + (_front & 0X0F000000);
    _edge[2] = (_up & 0X000F0000) + (_left & 0X0F000000);
    _edge[3] = (_up & 0X0F000000) + (_back & 0X0F000000);

    _edge[4] = (_down & 0X0000F000) + (_right & 0X000000F0);
    _edge[5] = (_down & 0X0F000000) + (_front & 0X000000F0);
    _edge[6] = (_down & 0X000F0000) + (_left & 0X000000F0);
    _edge[7] = (_down & 0X000000F0) + (_back & 0X000000F0);
    
    _edge[8] = (_front & 0X0000F000) + (_right & 0X000F0000);
    _edge[9] = (_front & 0X000F0000) + (_left & 0X0000F000);
    _edge[10] = (_back & 0X000F0000) + (_right & 0X0000F000);
    _edge[11] = (_back & 0X0000F000) + (_left & 0X000F0000);
}

void Rubik::count_corner(){ // corner's cubies [8][3]: UFR UFL UBR UBL  DFR DFL DBR DBL
    _corner[0] = (_up & 0X0000000F) + (_front & 0X00F00000) + (_right & 0XF0000000);
    _corner[1] = (_up & 0X00000F00) + (_front & 0XF0000000) + (_left & 0X00F00000);
    _corner[2] = (_up & 0X00F00000) + (_back & 0XF0000000) + (_right & 0X00F00000);
    _corner[3] = (_up & 0XF0000F00) + (_back & 0X00F00000) + (_left & 0XF0000000);
    _corner[4] = (_down & 0X00F00000) + (_front & 0X0000000F) + (_right & 0X00000F00);
    _corner[5] = (_down & 0XF0000000) + (_front & 0X00000F00) + (_left & 0X0000000F);
    _corner[6] = (_down & 0X0000000F) + (_back & 0X00000F00) + (_right & 0X0000000F);
    _corner[7] = (_down & 0X00000F00) + (_back & 0X0000000F) + (_left & 0X00000F00);
}

# endif