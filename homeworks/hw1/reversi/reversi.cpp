#include <vector>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <string>
#include "reversi.h"
using namespace std;


void Square::flip()
{
    switch (value_)
    {
    case WHITE:
        value_ = BLACK;
        break;
    case BLACK:
        value_ = WHITE;
        break;
    default:
        break;
    }
}

Square::SquareValue opposite_color(Square::SquareValue value)
{
    switch (value)
    {
    case Square::WHITE:
        return Square::BLACK;
    case Square::BLACK:
        return Square::WHITE;
    default:
        throw invalid_argument("Illegal square value");
    }
}

Square& Square::operator=(SquareValue value){
    //operation overload to change square value
    this->value_ = value;
    return *this;
}

bool Square::operator==(SquareValue value) const{
    //operation overload to compare square value
    if(this->value_ == value){
        return true;
    }
    else{
        return false;
    }
}

bool Square::operator!=(SquareValue value) const{
    //operation overload to compare square values
    if(this->value_ != value){
        return true;
    }
    else {
        return false;
    }
}

std::ostream& operator<<(std::ostream& out, const Square& square){
    //outputs board
    if(square.value_ == Square::FREE){
        out << '-';
    }
    else if (square.value_ == Square::WHITE){
        out << 'W';
    }
    else if(square.value_ == Square::BLACK){
        out << "B";
    }
    return out;
}

//------------
Square& Board::operator()(char row, size_t column)
{
    if (!is_valid_location(row, column))
    {
        throw out_of_range("Bad row index");
    }
    size_t row_index = row_to_index(row);
    return squares_[row_index][column - 1];
}

Square const& Board::operator()(char row, size_t column) const
{
    if (!is_valid_location(row, column))
    {
        throw out_of_range("Bad row index");
    }
    size_t row_index = row_to_index(row);
    return squares_[row_index][column - 1];
}

bool Board::is_legal_and_opposite_color(
    char row, size_t column, Square::SquareValue turn) const
{
    if (is_valid_location(row, column))
    {
        size_t row_index = row_to_index(row);
        return squares_[row_index][column - 1] != Square::FREE && squares_[row_index][column - 1] != turn;
    }
    return false;
}

bool Board::is_legal_and_same_color(
    char row, size_t column, Square::SquareValue turn) const
{
    if (is_valid_location(row, column))
    {
        size_t row_index = row_to_index(row);
        return squares_[row_index][column - 1] == turn;
    }
    return false;
}

bool Board::is_valid_location(char row, size_t column) const
{
    size_t row_index = row_to_index(row);
    return row_index < dimension_ && column - 1 < dimension_;
}


Board::Board(size_t s){
    //alloactes new memory for board-squares
    dimension_ = s;
    squares_ = new Square* [s];

    for (unsigned int i = 0; i < s; i++){
        squares_[i] = new Square[s];
    }
}

//Board Copy Constructor
Board::Board(const Board& b){
    //sets data members
    dimension_ = b.dimension();
    squares_ = new Square* [b.dimension()];
    
    
    //allocates new memory
    for (size_t i = 0; i < b.dimension(); i++){
        squares_[i] = new Square[b.dimension()];
    }
    
    //sets memory to old board
    for (size_t i = 0; i < dimension_; i++){
        for (size_t j = 0; j < dimension_; j++){
            this->squares_[i][j] = b.squares_[i][j];
        }
    }
}

Board::~Board(){
    //deletes memory of squares in boards
    for(unsigned int i = 0; i < dimension_; i++){
        delete [] squares_[i];
    }
    delete [] squares_;
}

std::ostream& operator<<(std::ostream& out, const Board& board){ 
    //wrapper for printin board
    return board.print(out);
}

//---



Checkpoint::Checkpoint(const Board& b, Square::SquareValue turn) :
    board_(b),
    turn_(turn)
{

}

ostream& Board::print(ostream& out) const
{
    out << "  ";
    for (size_t i = 1; i <= dimension_; i++)
    {
        if (i < 10)
        {
            out << " ";
        }
        else
        {
            out << (i / 10);
        }
    }
    out << endl;
    out << "  ";
    for (size_t i = 1; i <= dimension_; i++)
    {
        out << (i % 10);
    }
    out << endl;
    for (size_t i = 0; i < dimension_; i++)
    {
        out << (char)('a' + i) << ':';
        for (size_t k = 0; k < dimension_; k++)
        {
            out << squares_[i][k];
        }
        out << endl;
    }
    return out;
}



void Reversi::prompt() const
{
    cout << board_ << endl;
    cout << (turn_ == Square::BLACK ? "B" : "W");
    cout << " - Enter 'p r/c', 'q', 'c', 'u':" << endl;
}

void Reversi::win_loss_tie_message(size_t white_count, size_t black_count)
{
    cout << board_ << endl;
    if (white_count > black_count)
    {
        cout << "W wins" << endl;
    }
    else if (white_count < black_count)
    {
        cout << "B wins" << endl;
    }
    else
    {
        cout << "Tie" << endl;
    }
    cout << "W=" << white_count << "/B=" << black_count << endl;
}

bool Reversi::is_legal_choice(char row, size_t column, Square::SquareValue turn) const
{
    // Vectors for each cardinal direction
    const size_t direction_count = 8;
    const int direction_row[] =    {-1, -1,  0, +1, +1, +1,  0, -1};
    const int direction_column[] = { 0, -1, -1, -1,  0, +1, +1, +1};

    // Make sure location is free
    if (board_(row, column) != Square::FREE)
    {
        return false;
    }

    // Now check in each directions
    for (size_t d = 0; d < direction_count; d++)
    {
        // Where we're checking
        char cursor_row = row + direction_row[d];
        size_t cursor_column = column + direction_column[d];

        // Move towards the direction while we're on the opposite color
        bool found_opposite = false;
        while (board_.is_legal_and_opposite_color(cursor_row, cursor_column, turn_))
        {
            found_opposite = true;
            cursor_row += direction_row[d];
            cursor_column += direction_column[d];
        }

        // Check if the next thing after is our color
        bool found_same = board_.is_legal_and_same_color(cursor_row, cursor_column, turn_);

        // If this direction is valid, the move is valid, so short circuit and return
        if (found_opposite && found_same) {
            return true;
        }
    }
    return false;
}

bool Reversi::is_game_over() const
{
    for (unsigned char row = 'a'; row < 'a' + board_.dimension(); row++)
    {
        for (size_t column = 1; column <= board_.dimension(); column++)
        {
            if (is_legal_choice(row, column, turn_))
            {
                return false;
            }
        }
    }
    return true;
}

//Write this ---

Reversi::Reversi(size_t size):board_(size){
    turn_ = Square::BLACK;
    
    //sets starting pieces for board
    int cornerInt = size/2;
    char cornerChar = 'a' + (size/2 -1);
    
    board_(cornerChar, cornerInt).value_ = Square::BLACK; //Set to black
    board_(cornerChar + 1, cornerInt + 1).value_ = Square::BLACK;
    board_(cornerChar + 1, cornerInt).value_ = Square::WHITE;
    board_(cornerChar, cornerInt+1).value_ = Square::WHITE;
    
}

void Reversi::play(){    
    //while loop to play as long as legal move exists
    do{
        char input;
        //outs board, prompts and takes input
        prompt();
        cin >> input;
        //if player is playing
        if (input == 'p'){
            char row; int col;
            string s;
            getline(cin, s);
            stringstream ss(s);
            ss >> row >> col;
            
//            if((size_t(row - 97) ) >= board_.dimension() || size_t(col) >= board_.dimension()){
//                continue;
//            }
            
            //if position is legal
            if(is_legal_choice(row, col, turn_)){
                //places peice on board
                board_(row, col).value_ = turn_;
                    
                //dictionary for checking which peices to turn
                const int checkRow[] =    {-1, -1,  0, +1, +1, +1,  0, -1};
                const int checkCol[] = { 0, -1, -1, -1,  0, +1, +1, +1};
                    
                //for loop to change search sides
                for(int i = 0; i < 8; i++){
                    //variable to extend search side
                    int count = 1;
                    //keeps searching till outside parameter, or reaching opposite/free colour
                    while (board_.is_legal_and_opposite_color(char(row + count*checkRow[i]), col + count*checkCol[i], turn_)){
                        count++;  
                    }
                    //if opposite color, traces back and flips color
                    if(board_.is_legal_and_same_color(char(row + count*checkRow[i]), col + count*checkCol[i], turn_)){
                        //traces back
                        while(count != 0 ){
                            //changes color
                            board_(char( row + count*checkRow[i]), col + count*checkCol[i]) = turn_;
                            count--;
                        }
                    }
                }
                //changes color
                turn_ = opposite_color(turn_);
            }
        }        
        //saves checkpoint
        else if (input == 'c'){
            save_checkpoint();
        }
        //undoes to last checkpoint
        else if (input == 'u'){
            undo();
        }
        //quits if anything else is inputted
        else {
            break;
        }
    }while(!is_game_over());
    
    //nested loop to count black and white
    int wcnt = 0, bcnt = 0;
    for (unsigned int i = 0; i < board_.dimension(); i++){
        for (unsigned int j = 0; j < board_.dimension(); j++){
            if(board_(char(i+97), j+1) == Square::BLACK){
                bcnt++;
            }
            else if(board_(char(i+97), j+1) == Square::WHITE){
                wcnt++;
            }
        }
    }
    //outputs message
    win_loss_tie_message(wcnt, bcnt);
}



void Reversi::save_checkpoint(){
    //creates new object and stores in vector
    Checkpoint temp(board_, turn_);
    history_.push_back(temp);
}

void Reversi::undo(){
    if(!history_.empty()){
        for (size_t i = 0; i < history_.back().board_.dimension(); i++){
            for (size_t j = 0; j < history_.back().board_.dimension(); j++){
                board_(char(i+97), j+1) = history_.back().board_(char(i+97), j+1);
            }
        }
        turn_ = history_.back().turn_;
        history_.pop_back();
    }
}




