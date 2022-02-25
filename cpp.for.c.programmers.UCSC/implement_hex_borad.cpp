//implement hex board game
#include <iostream>
#include <vector>
#include <random>

using namespace std;

class Cell;
class HexBoard;
class Player;

//define color
enum class Color {RED, BLUE};

//define a cell
class Cell{
    private:
        int coord_x, coord_y;
        char player_type;                    //'X' or 'O', represents two different player_types
        vector<Cell *> edge{};          //the cells connected to this cell, corner will have 2 or 3, edge will have 4, inner cell will have 6
    public:
        Cell(char, int, int);
        void set_player_type(char);
        char get_player_type();
        friend HexBoard;
};

Cell::Cell(char _player_type, int x, int y): player_type(_player_type), coord_x(x), coord_y(y) { }

void Cell::set_player_type(char _player_type){
    player_type = _player_type;
}

char Cell::get_player_type(){
    return player_type;
}

class HexBoard{
    private:
        unsigned int size;                      //board size
        vector<vector<Cell>> board;
    public:
        HexBoard(unsigned int);
        unsigned int get_size();
        friend ostream & operator<<(ostream &, HexBoard & );    //show borad 
        bool has_path_to_opposite(int, int, char);
        friend Player;
};

HexBoard::HexBoard(unsigned int _size): size(_size){
    if(size == 1){
        cout << "size can not be 1!!!" << endl;
        return;
    }
    //initialize cells
    for(int i=0; i<size; ++i){
        vector<Cell> _temp;
        for(int j=0; j<size; ++j){
            _temp.push_back(Cell('.', i, j));
        }
        board.push_back(_temp);
    }
    //initialize all edges for every cell
    for(int i=0; i<size; ++i){
        for(int j=0; j<size; ++j){
            if(i == 0){
                if(j == 0){
                    board[i][j].edge.push_back(&board[i][j+1]);
                    board[i][j].edge.push_back(&board[i+1][j]);
                }
                else if(j == size-1){
                    board[i][j].edge.push_back(&board[i][j-1]);
                    board[i][j].edge.push_back(&board[i+1][j-1]);
                    board[i][j].edge.push_back(&board[i+1][j]);
                }
                else{
                    board[i][j].edge.push_back(&board[i][j-1]);
                    board[i][j].edge.push_back(&board[i+1][j-1]);
                    board[i][j].edge.push_back(&board[i+1][j]);
                    board[i][j].edge.push_back(&board[i][j+1]);
                }
            }
            else if(i == size-1){
                if(j == 0){
                    board[i][j].edge.push_back(&board[i-1][j]);
                    board[i][j].edge.push_back(&board[i-1][j+1]);
                    board[i][j].edge.push_back(&board[i][j+1]);
                }
                else if(j == size-1){
                    board[i][j].edge.push_back(&board[i][j-1]);
                    board[i][j].edge.push_back(&board[i-1][j]);
                }
                else{
                    board[i][j].edge.push_back(&board[i][j+1]);
                    board[i][j].edge.push_back(&board[i-1][j+1]);
                    board[i][j].edge.push_back(&board[i-1][j]);
                    board[i][j].edge.push_back(&board[i][j-1]);
                }
            }
            else{
                if(j == 0){
                    board[i][j].edge.push_back(&board[i+1][j]);
                    board[i][j].edge.push_back(&board[i][j+1]);
                    board[i][j].edge.push_back(&board[i-1][j+1]);
                    board[i][j].edge.push_back(&board[i-1][j]);
                }
                else if(j == size-1){
                    board[i][j].edge.push_back(&board[i-1][j]);
                    board[i][j].edge.push_back(&board[i][j-1]);
                    board[i][j].edge.push_back(&board[i+1][j-1]);
                    board[i][j].edge.push_back(&board[i+1][j]);
                }
                else{
                    board[i][j].edge.push_back(&board[i][j-1]);
                    board[i][j].edge.push_back(&board[i+1][j-1]);
                    board[i][j].edge.push_back(&board[i+1][j]);
                    board[i][j].edge.push_back(&board[i][j+1]);
                    board[i][j].edge.push_back(&board[i-1][j+1]);
                    board[i][j].edge.push_back(&board[i-1][j]);
                }
            }
        }
    }
}

unsigned int HexBoard::get_size(){
    return size;
}

//show board
ostream & operator<<(ostream & out, HexBoard & hexboard){
    for(int i=0; i<hexboard.size; ++i){
        for(int k=0; k<2*i; ++k){
            out << " ";
        }
        for(int j=0; j<hexboard.size; ++j){
            if(j!=hexboard.size-1)
                out << hexboard.board[i][j].get_player_type() << " - ";
            else
                out << hexboard.board[i][j].get_player_type();
        }
        out << endl;
        for(int k=0; k<2*i; ++k){
            out << " ";
        }
        if(i!=hexboard.size-1){
            for(int k=0; k<hexboard.size; ++k){
                if(k!=hexboard.size-1)
                    out << " \\ /";
                else    
                    out << " \\";
            }
            out << endl;
        }
    }

    return out;
}

//test if there's a path from a border to opposite border
bool HexBoard::has_path_to_opposite(int cell_row, int cell_column, char _type){
    static vector<bool> visited(size*size, false);
    char type = _type;
    bool re_value = false;
    vector<bool> results(board[cell_row][cell_column].edge.size(), false);
    // tag
    visited[cell_row*size+cell_column] = true;
    if(board[cell_row][cell_column].get_player_type() == _type)
        for(int i=0; i<results.size(); ++i){
            Cell * neighbor = board[cell_row][cell_column].edge[i];
            if(neighbor->get_player_type() != type || visited[neighbor->coord_x*size+neighbor->coord_y])
                results[i] = false;
            else if((type == 'X' && neighbor->coord_x == size-1) || (type == 'O' && neighbor->coord_y == size-1)){
                results[i] = true;
                break;
            }
            else{
                //recursion
                results[i] = has_path_to_opposite(neighbor->coord_x, neighbor->coord_y, _type);
                if(results[i])
                    break;
            }
        }
    else{
        re_value = false;
    }
    for(auto result: results){
        re_value = re_value || result;
    }
    // cancle tag
    visited[cell_row*size+cell_column] = false;
    return re_value;
}

class Player{
    private:
        HexBoard * hexborad;
        char type;
        Color color;
    public:
        Player(HexBoard *, char, Color);
        bool move(int, int);
        bool is_win();
};

Player::Player(HexBoard * _hexboard, char _type, Color _color): hexborad(_hexboard), type(_type), color(_color) {}

bool Player::move(int row, int column){
    if(hexborad->board[row][column].get_player_type() == '.'){
        hexborad->board[row][column].set_player_type(type);
        return true;
    }
    else{
        return false;
    }
}

bool Player::is_win(){
    switch (color){
        case Color::RED:{
            for(int i=0; i<hexborad->size; ++i){
                if(hexborad->has_path_to_opposite(0, i, type))
                    return true;
            }
            break;
        }
        case Color::BLUE:{
            for(int i=0; i<hexborad->size; ++i){
                if(hexborad->has_path_to_opposite(i, 0, type))
                    return true;
            }
            break;
        }
    }
    return false;
}

int main(){
    HexBoard b(11);                 //create a hexborad
    Player red(&b, 'X', Color::RED), blue(&b, 'O', Color::BLUE);        //create 2 players
    cout << b << endl;      //show empty board
    default_random_engine dre;      //generator
    uniform_int_distribution<unsigned int> coord(0, b.get_size()-1);    //coordinate range
    unsigned int i = 0, size = b.get_size() * b.get_size(); 
    while(i < size){
        if(i<size){
            while(!(blue.move(coord(dre), coord(dre))));
            cout << "round " << i+1 << endl << b << endl;
            if(blue.is_win()){
                cout << "blue win" << endl;
                break;
            }
            ++i;
        }
        if(i<size){
            while(!(red.move(coord(dre), coord(dre))));
            cout << "round " << i+1 << endl <<  b << endl;
            if(red.is_win()){
                cout << "red win" << endl;
                break;
            }
            ++i;
        }
    }
    // result is red win!!!
    return 0;
}
