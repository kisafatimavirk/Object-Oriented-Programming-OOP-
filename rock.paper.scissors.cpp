// rock paper scissor game
#include <iostream>
#include <cstdlib> //random
#include <ctime>
#include <windows.h>  // for emojis
using namespace std;

// ANSI color code list
#define RED     "\033[31m"  // errors
#define PASTEL_RED     "\033[38;2;255;179;186m"  // lose
#define PASTEL_GREEN   "\033[38;2;186;255;201m"  // win
#define PASTEL_YELLOW  "\033[38;2;255;255;186m"  // rounds
#define PASTEL_BLUE    "\033[38;2;186;225;255m"  // score
#define PASTEL_PURPLE  "\033[38;2;224;187;255m"  // main heading
#define PASTEL_PINK      "\033[38;2;255;192;203m"
#define BLACK   "\033[30m"
#define PASTEL_MINT      "\033[38;2;170;240;209m"
#define RESET          "\033[0m"

#define BG_PASTEL_ORANGE   "\033[48;2;255;223;186m"

// Player class

class Player  // abstract class
{
    string name;
    int score;

// getname
// addscore
// resetscore
// getscore
// move - override

public:
    Player(string n)  // constructor
    {
        name = n;
        score = 0;
    }

    string getName()
    {
        return name;
    }

    int getScore()
    {
        return score;
    }

    int resetScore()
    {
        score = 0;
        return score;
    }    

    int addScore()
    {
        return score++;

    }

    virtual string choice() = 0;  // pure virtual function

    
};

class HumanPlayer : public Player
{
public:
    HumanPlayer(string n) : Player(n)  // constructor
    { 
    }

    string choice() override
    {
        string choice;

        while (true)
        {
            cout << "Please enter choice (Rock ✊ / Paper ✋ / Scissor ✌ ): ";
            cin >> choice;

            if (choice != "Rock" && choice != "Paper" && choice != "Scissor")
            {
                cout << RED <<"\nInvalid choice. Try again.\n" << RESET;
            }
            else
            {
                break;
            }
        }
        return choice; 
    }

};

class ComputerPlayer : public Player  // itself is an abstract class
{
public:
    ComputerPlayer(string n) : Player(n)
    {
    }

    virtual string choice(string lastChoice) = 0;

    string choice() override 
    {
        return "Rock";
    }

};

class EasyComputer : public ComputerPlayer  // first level - always Rock
{
public:
    EasyComputer() : ComputerPlayer("Easy Computer")
    {
    }


    string choice(string lastchoice) override
    {
        return "Rock";
    }

};

class MediumComputer : public ComputerPlayer  // randomly generates output
{
public:
    MediumComputer() : ComputerPlayer("Medium Computer")  // constructor
    {
    }

    string choice(string lastchoice) override
    {
        int r = rand() % 3;

        if (r == 0) 
        {
            return "Rock";
        }

        else if (r == 1)
        {
            return "Paper";
        }

        return "Scissor";

    }
};

class HardComputer : public ComputerPlayer  // generates output based on previous output og human
{
public:
    HardComputer() : ComputerPlayer("Hard Computer")  // constructor
    {
    }

    string choice(string lastchoice) override
    {
        if (lastchoice == " ")  // first checking there is no recent choice avaiable
        {
            int r = rand() % 3;  // randomly geerate output - 1, 2 or 3

            if (r == 0)
            {
                lastchoice = "Rock";
            }
            else if (r == 1)
            {
                lastchoice = "Paper";
            }
            else
            {
                lastchoice = "Scissor";
            }
        }

        if (lastchoice == "Rock")
        {
            return "Paper";
        }
        if (lastchoice == "Paper")
        {
            return "Scissor";
        }
        if (lastchoice == "Scissor")
        {
            return "Rock";
        }
        return "Rock";
    }
};

class Game
{
    HumanPlayer human;
    ComputerPlayer *computer;  // polymorphism

public:
    int powerUps = 1;  // global

    Game(string playerName) : human(playerName)  // composition - member initialiser list
    {
        computer = nullptr;
    }

    int selectWinner(string humanMove, string computerMove)
    {
        if (humanMove == computerMove) // draw case
        {
            return 0;
        }

        if (((humanMove == "Rock") && (computerMove == "Scissor")) || ((humanMove == "Paper") && (computerMove == "Rock")) || 
        ((humanMove == "Scissor") && (computerMove == "Paper")))
        {

            return 1;  // human wins
        } 

        return -1;  // computer wins
    }

// new modification - power up method

    void askForPowerUp()
    {
        bool powerUpActive;

        cout << "Do you want to use your power up? (Yes (1) /No (0)): ";
        cin >> powerUpActive;

        if (powerUpActive == 1)
        {
            cout << "✨ POWER-UP ACTIVATED! ✨" << endl;
        }

        else if(powerUpActive == 0)
        {
            cout << "No power-up used in this round." << endl;
        }

        else
        {
            cout << "Invalid choice!" << endl;
        }

    }


    void selectLevel()
    {
        int choice;
        cout << BG_PASTEL_ORANGE;
        cout << BLACK;
        cout << "\n====================================================\n";
        cout << "         ROCK ✊ PAPER ✋ SCISSOR ✌- 3 LEVELS       " << endl;
        cout << "====================================================\n";
        cout << RESET;
        cout << endl;

        cout << "1️⃣  Easy" << endl;
        cout << "2️⃣  Medium" << endl;
        cout << "3️⃣  Hard" << endl;
        cout << endl;

        cout << "Choose level: ";
        cin >> choice;

        // call powerUp here



        switch (choice)
        {
            case 1:  // human chooses easy level to play
                cout << "Level 1: Easy." << endl;
                computer = new EasyComputer();
                powerUps = 1;
                break;
            case 2:
                cout << "Level 2: Medium." << endl;
                computer = new MediumComputer();
                powerUps = 1;
                break;
            case 3:
                cout << "Level 3: Hard." << endl;
                computer = new HardComputer();
                powerUps = 1;
                break;
            default: 
                cout << RED <<"Invalid choice. Selecting Easy level.\n" << RESET;
                computer = new EasyComputer();
        }
    }

    void play()
    {
        human.resetScore();
        computer -> resetScore();

        string previousMove = " ";

        for (int round = 1; round <= 3; round++)
        {
            cout << "Power-ups available: " << powerUps << endl;

            cout << endl;
            cout << PASTEL_PURPLE;
            cout << "==ROUND " << round << "==\n";
            cout << RESET;
            cout << endl;
            
            if(powerUps != 0)
            {
                askForPowerUp();  // call
            }


            string HMove = human.choice();
            string CMove = computer -> choice(previousMove);

            cout << PASTEL_MINT;
            cout << "Your move: " << HMove << endl;
            cout << "Computer move: " << CMove << endl;
            cout << RESET;

            int result = selectWinner(HMove, CMove);

            if (result == 1)
            {
                cout << endl;
                cout << PASTEL_GREEN <<"🎉 YOU WIN! 🎉\n" << RESET;
                cout << endl;

                cout << "💥 POWER_UP BONUS! +2 points instead of 1! 💥" << endl;
                human.addScore();  
                human.addScore();

                if (powerUps != 0)
                {
                    powerUps--;
                }
            }

            else if (result == -1)
            {
                cout << endl;
                cout << PASTEL_RED <<"🎉 COMPUTER WINS! 🎉\n" << RESET;
                cout << endl;

                cout << "😭 Power-up wasted! No bonus points. 😭" << endl;
                if (powerUps != 0)
                {
                    powerUps--;
                }

                computer -> addScore();
            }

            else
            {
                cout << endl;
                cout << PASTEL_YELLOW;
                cout << "GAME DRAW!" << endl;
                cout << RESET;

                cout << "😭 Power-up wasted! No bonus points. 😭" << endl;
                if (powerUps != 0)
                {
                    powerUps--;
                }
            }
            cout << endl;
            cout << PASTEL_BLUE;
            cout << "==SCORE==" << endl;
            cout << "Your score:  " << human.getScore() << endl;
            cout << "Computer's score: " << computer->getScore() << endl;
            cout << RESET;

            cout << "Power-ups remaining: " << powerUps << endl;

            previousMove = HMove;
        }

        cout << endl;
        cout << PASTEL_PURPLE <<"==FINAL RESULT:==" << RESET <<endl;
        cout << endl;
        if ((human.getScore()) > computer -> getScore())
        {
            cout << PASTEL_GREEN<<"🏆 YOU WIN THE MATCH! 🏆\n" << RESET;
        }

        else if ((human.getScore()) < computer -> getScore())
        {
            cout << PASTEL_RED <<"YOU LOSE 😞\n" << RESET;
        }

        else
        {
            cout << PASTEL_YELLOW;
            cout << "GAME DRAW! " << endl;
            cout << RESET;
        }
    }

    ~Game()  // destructor
    {
        delete computer;
    }
};

int main()
{
    SetConsoleOutputCP(CP_UTF8);  // for emojis

    srand(time(0));  // to start the random values generation from 0

    string playerName;
    cout << "Your name: ";
    getline(cin, playerName);

    string playAgain;

    Game game(playerName);

    do
    {
        game.selectLevel();
        game.play();

        cout << "Play again? (Yes/No) ";
        cin >> playAgain;
    } while (playAgain == "Yes");

    cout << endl;
    cout << PASTEL_PINK;
    cout << "=== Thanks for playing 😊 ==="<< endl;
    cout << RESET;
    return 0;
    
}