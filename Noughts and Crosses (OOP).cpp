#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>

bool ClaimSquare(std::map<int, unsigned char>& grid, int move, const unsigned char player)
{
    auto validSquare = std::find_if(grid.begin(), grid.end(), [&](auto pair) {
        return pair.first == move;
        });
    if (validSquare != grid.end())
    {
        if (validSquare->second == '-')
        {
            validSquare->second = player;
            return true;
        }
        else
        {
            std::cout << "This square has already been claimed. Choose a different square!" << std::endl;
            return false;
        }
    }
}

void Displaygrid(const std::map<int, unsigned char>& grid)
{

    for (auto const& cell : grid)
    {
        if (cell.first % 3 == 1) {
            std::cout << "\n\n";
        }
        if (cell.second != '-') {
            std::cout << cell.second << "        ";
            
        }
        else
        {
            std::cout << cell.first << "        ";
        }
    }
    std::cout << "\n\n";
}

class Player
{
private:
     std::string m_type;
    unsigned char m_name;
public:
    std::string GetType() { return m_type; }
    Player(unsigned char name, std::string&& type = "Player") :m_name(name),m_type(type) {}
    virtual ~Player() = default;
    virtual unsigned char GetName() { return m_name; }
    virtual int NextMove() = 0;
};

class Human : public Player
{

public:
    Human(unsigned char name) :Player(name, "Human") {}
    virtual int NextMove() override {
        int move;
        std::cout << "Enter a number on the grid (e.g. 1): ";
        std::cin >> move;
        return move;
    }
};

class Robot : public Player
{

public:
    Robot(unsigned char name) :Player(name, "Robot"){}
    virtual int NextMove() override 
    {
        int move;
        std::cout << "Enter a number on the grid (e.g. 1): ";
        std::cin >> move;
        return move;
    }
    
};

class Game
{
private:

    //std::vector<Player*> m_p;
    std::vector<Player*>m_p;
public:
    Game(Player *p1, Player *p2)
    {
        m_p = {
            p1, p2
        };
       
    }
    bool CheckForDraw(std::map<int, unsigned char>& board) {

        if (std::count_if(board.begin(), board.end(), [](auto& cell) {
            return cell.second == '-';
            }) == 0)
        {
            std::cout << "It's a draw!\n";
            return true;
        }
        return false;
    }
    bool CheckForAWinner(std::map<int, unsigned char>& board, const unsigned char key)
    {
        if (board.at(1) == key && board.at(2) == key && board.at(3) == key) {
            std::cout << key << " is the winner" << std::endl;
            return true;
        }
        else if (board.at(4) == key && board.at(5) == key && board.at(6) == key) {
            std::cout << key << " is the winner" << std::endl;
            return true;
        }
        else if (board.at(7) == key && board.at(8) == key && board.at(9) == key) {
            std::cout << key << " is the winner" << std::endl;
            return true;
        }

        else if (board.at(1) == key && board.at(4) == key && board.at(7) == key) {
            std::cout << key << " is the winner" << std::endl;
            return true;
        }
        else if (board.at(2) == key && board.at(5) == key && board.at(8) == key) {
            std::cout << key << " is the winner" << std::endl;
            return true;
        }
        else if (board.at(3) == key && board.at(6) == key && board.at(9) == key) {
            std::cout << key << " is the winner" << std::endl;
            return true;
        }

        else if (board.at(1) == key && board.at(5) == key && board.at(9) == key) {
            std::cout << key << " is the winner" << std::endl;
            return true;
        }
        else if (board.at(7) == key && board.at(5) == key && board.at(3) == key) {
            std::cout << key << " is the winner" << std::endl;
            return true;
        }
        else
        {
            return false;
        }
    }
    void play(std::map<int, unsigned char>&board)
    {
        int currentPlayer = 1;
        do
        {
            int move = 0;
            currentPlayer = (currentPlayer + 1) % 2;
            do
            {
                Displaygrid(board);
                std::cout << m_p.at(currentPlayer)->GetType() << ": " << m_p.at(currentPlayer)->GetName() << " turn: " << std::endl; 
                move = m_p.at(currentPlayer)->NextMove();
                
            }
            while (ClaimSquare(board, move, m_p.at(currentPlayer)->GetName()) == false);
            system("cls");
        } 
        while (CheckForDraw(board) == false && CheckForAWinner(board,m_p.at(currentPlayer)->GetName()) == false);

        Displaygrid(board);
    }
};

int main() {

    
    std::map<int, unsigned char>grid =
    {           
     std::make_pair(1,'-'), 
     std::make_pair(2,'-'), 
     std::make_pair(3,'-'),
     std::make_pair(4,'-'), 
     std::make_pair(5,'-'), 
     std::make_pair(6,'-'),
     std::make_pair(7,'-'), 
     std::make_pair(8,'-'), 
     std::make_pair(9,'-') 
    };
    
    
    Human player('O');
    Human player2('X');

    Robot robot('O');
    Robot robot2('X');

    //Game 1: Human vs Human
    Game HumanVsHuman(&player, &player2);
    HumanVsHuman.play(grid);

    //The robot doesn't work yet. Just treat it as a human. Point is to demonstrate polymorphisim.
    /*Game RobotvsHumanGame(&robot, &robot2);
    RobotvsHumanGame.play(grid);*/
}