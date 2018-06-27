/*
    Name: Alexander Gonzales
    Build: 1.0
    Date: Dec 13, 2017
    Class: CSC 310
    Instructor: Lori Nicholson
    Project: Final Project
    Description: This project deals with a 4x4 game board. Players can put no two letters or numbers in
    the same vertical or horizontal on a grid
*/

#include <iostream>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <cctype>
#include <cstring>
#include <time.h>
#include <ctime>
#include <random>
#include <algorithm>

using namespace std;

//the starting words
const string startWords[5] = {"boyz", "back", "yous", "rint", "grin"};

class Board
{
private:

    // storing board as one dimensional array.
    // indexing is 4y + x
    string workingBoard[16] = {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "};
    string answerBoard[16];
    string startWord;

    string getAnswerRow(int rowNumber)
    {
        string result;
        for (int i = 0; i < 4; ++i)
        {
            result += getAnswerValue(i,rowNumber);
        }
        return result;
    }

    string getAnswerColumn(int colNumber)
    {
        string result;
        for (int i = 0; i < 4; ++i)
        {
            result += getAnswerValue(colNumber,i);
        }
        return result;
    }
    //sets answer value for the game board
    bool setAnswerValue(int x, int y, char value)
    {
        answerBoard[4 * y + x] = value;
        return true;
    }
    //gets answer value for game board
    string getAnswerValue(int x, int y)
    {
        return answerBoard[4 * y + x];
    }
    //checks if it has the answer value in that part of the board
    bool hasAnswerValue(int x, int y)
    {
        return !(" " == getAnswerValue(x, y));
    }
    //generates the answer board
    void generateAnswerBoard()
    {
        // copy working board to answer board
        for (int i = 0; i < 16; ++i)
        {
            answerBoard[i] = workingBoard[i];
        }
        for (int x = 0; x < 4; x++)
        {
            for(int y = 0; y < 4; y++)
            {
                if (!hasAnswerValue(x, y))
                {
                    string matchString = string(startWord);
                    string col = getAnswerColumn(x);
                    string row = getAnswerRow(y);
                    for(int index = 0; index < 4; index++)
                    {
                        char cVal = col.at(index);
                        if (matchString.find(cVal) != string::npos)
                        {
                            matchString.erase (matchString.find(cVal), 1);
                        }
                        char rVal = row.at(index);
                        if (rVal != cVal)
                        {
                            if (matchString.find(rVal) != string::npos)
                            {
                                matchString.erase (matchString.find(rVal), 1);
                            }
                        }
                    }
                    setAnswerValue(x, y, matchString.at(0));
                }
            }
        }
    }
    //displays board
    void display(string board[16])
    {
        cout << endl;
        cout << "Game Board: \n"
             << "   0   1   2   3\n"
             << "0 [" << board[0] << "] " << "[" << board[1] << "] " <<  "["
             << board[2] << "] " << "[" << board[3] << "] " << "\n"
             << "1 [" << board[4] << "] " << "[" << board[5] << "] " <<  "["
             << board[6] << "] " << "[" << board[7] << "] " << "\n"
             << "2 [" << board[8] << "] " << "[" << board[9] << "] " <<  "["
             << board[10] << "] " << "[" << board[11] << "] " << "\n"
             << "3 [" << board[12] << "] " << "[" << board[13] << "] " <<  "["
             << board[14] << "] " << "[" << board[15] << "] " << "\n";
    }

public:

    Board()
    {
        srand(time(0));
        // random to determine if vertical or horizontal
        bool isHorizontal = (rand() % 2) == 1? true: false;
        // determine start index, 0-3, of start word on x or y axis
        int startIndex = rand() % 4;
        startWord = startWords[rand() % 5];

        // if horizontal, then start word populates row
        // if vertical then start word populates column
        // init array

        if (isHorizontal)
        {
            // if horizontal, the x changes
            for (int i = 0; i < 4; ++i)
            {
                setValue(i, startIndex, startWord.at(i));
            }
        }
        else
        {
            // if vertical, the y changes
            for (int i = 0; i < 4; ++i)
            {
                setValue(startIndex, i, startWord.at(i));
            }
        }
        generateAnswerBoard();
    }

    bool setValue(int x, int y, char value)
    {
        workingBoard[4 * y + x] = value;
        return true;
    }

    string getValue(int x, int y)
    {
        return workingBoard[4 * y + x];
    }

    bool hasValue(int x, int y)
    {
        return !(" " == getValue(x, y));
    }

    bool isBoardValid()
    {
        for (int i = 0; i < 16; i++)
        {
            if (answerBoard[i] != workingBoard[i])
            {
                return false;
            }
        }
        return true;
    }

    bool isValidInput(char input)
    {
        return (startWord.find(input) != string::npos);
    }

    void displayBoard()
    {
        display(workingBoard);
    }

    void displayAnswerBoard()
    {
        display(answerBoard);
    }
};

int main()
{
    Board aBoard = Board();

    int loc1;
    int loc2;
    char ansLet;
    cout << "This is a number game on a 4x4 board \n";
    cout << "Rules: no two letters or numbers can lie in \nthe same vertical / horizontal or diagonal.\n\n";
    char numL = 'Y';

    srand(time(0));

    cout << endl;
    while (numL != 'N')
    {
        //displays board and asks user to input where they want to put the letters
        aBoard.displayBoard();
        cout << "Input location of where you want the letters: (example: 1 3)";
        cin >> loc1 >> loc2;
        cout << endl;
        //error thrown if int is not entered, clears cin and makes your re-enter an int
        while(cin.fail())
        {
            cout << "Error input integer values: " << endl;
            cin.clear();
            cin.ignore(256,'\n');
            cin >> loc1 >> loc2;
        }
        //checks if they have put in numbers that are too big for the board locations
        while (loc1 >= 4 || loc2 >= 4)
        {
            cout << "input a valid number: ";
            cin >> loc1 >> loc2;
            cout << endl;
            //error thrown if int is not entered, clears cin and makes your re-enter an int
            while(cin.fail())
            {
                cout << "Error input integer values: " << endl;
                cin.clear();
                cin.ignore(256,'\n');
                cin >> loc1 >> loc2;
            }
        }
        //checks if the numbers are too small for the game board
        while (loc1 <= -1 || loc2 <= -1)
        {
            cout << "input a valid number: ";
            cin >> loc1 >> loc2;
            cout << endl;
            //error thrown if int is not entered, clears cin and makes your re-enter an int
            while(cin.fail())
            {
                cout << "Error input integer values: " << endl;
                cin.clear();
                cin.ignore(256,'\n');
                cin >> loc1 >> loc2;
            }
        }
        while (aBoard.hasValue(loc1, loc2))
        {
            cout << "that position already has a value. please enter again: ";
            cin >> loc1 >> loc2;
            cout << endl;
            //error thrown if int is not entered, clears cin and makes your re-enter an int
            while(cin.fail())
            {
                cout << "Error input integer values: " << endl;
                cin.clear();
                cin.ignore(256,'\n');
                cin >> loc1 >> loc2;
            }
        }
        cout << "Input the letter you want to put in this location: ";
        cin >> ansLet;
        while (!aBoard.isValidInput(ansLet))
        {
            cout << "that is not a valid input letter for this board. Re-enter the letter again: ";
            cin >> ansLet;
        }
        aBoard.setValue(loc1, loc2, ansLet);

        cout << "continue playing y/n: ";
        cin >> numL;
        numL = toupper(numL);

        while (numL != 'Y' && numL != 'N')
        {
            cout << "\nPlease enter a valid character: ";
            cin >> numL;
            numL = toupper(numL);
        }
    }
    cout << "Do you want to check your board against the answer y/n:";
    cin >> numL;
    numL = toupper(numL);
    while (numL != 'Y' && numL != 'N')
    {
        cout << "\nPlease enter a valid character: ";
        cin >> numL;
        numL = toupper(numL);
    }
    if (numL == 'Y')
    {
        if (aBoard.isBoardValid())
        {
            cout << "Your board was correct! Good job!" << endl;
        }
        else
        {
            cout << "Your board was not correct!" << endl << "The answer board is: " << endl;
            aBoard.displayAnswerBoard();
        }
    }

    return 0;
}
