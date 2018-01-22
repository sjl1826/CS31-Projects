//  stars.cpp
//
//  Created by Samuel J. Lee on 11/8/17.
//  Copyright © 2017 Samuel J. Lee. All rights reserved.
//
#define _CRT_SECURE_NO_DEPRECATE

#include "utilities.h"
#include <iostream>
#include <cctype>
#include <cstring>

using namespace std;

const char WORDFILENAME[] = "/Users/sjl1826/Desktop/Home/UCLA/CS/words.txt"; //Destination of the word text file with all the words

int runOneRound(const char words[][MAXWORDLEN+1], int nWords, int wordnum); //runs through one round and returns number of tries
bool isWordThere(const char words[][MAXWORDLEN+1], const char guessed[MAXWORDLEN+1], int nWords); //Checks to see if the word is inside the wordfilename array

int main()
{
    const int MAXWORDS = 10000;
    double total = 0; //total tries to take the average
    int minimum = 0; //holds the minimum tries
    int maximum = 0; //holds the maximum tries
    const int MAXWORDLEN = 6; //Maximum length is 6 characters
    char wordList[MAXWORDS][MAXWORDLEN+1];
    int nWords = getWords(wordList, 10000, WORDFILENAME);
    int _RANDOMINTEGER; //Holds the random integer for the position in the array to grab the random word
    int numRounds = 0; //takes in how many runs they want to play
    cout.setf(ios::fixed);
    cout.precision(2); //setting everything to 2 decimal places
    if(nWords<1)
    {
        cout<<"No words were loaded, so I can't play the game."<<endl;
        return -1;
    }
    cout<<"How many rounds do you want to play? ";
    cin>>numRounds;
    cin.ignore(10000, '\n'); //so that it doesn't mess up the getline
    if(numRounds>0) //rounds must be positive
    {
        for(int rounds = 1; rounds<=numRounds; rounds++) //goes through the number of rounds wanted
        {
            _RANDOMINTEGER = randInt(0, nWords-1); //pick out a random integer
            cout<<endl<<"Round "<<rounds<<endl;
            cout<<"The secret word is "<<strlen(wordList[_RANDOMINTEGER])<<" letters long."<<endl;
            int tries = runOneRound(wordList, nWords, _RANDOMINTEGER); //amount of tries
            if(tries != -1)
            {
                if(tries == 1)
                    cout<<"You got it in "<<tries<<" try."<<endl;
                else
                    cout<<"You got it in "<<tries<<" tries."<<endl;
                total += tries;
            }
            else
            {
                cout<<"Invalid words and number of words"<<endl;
                return 0;
            }
            if(rounds == 1)
                minimum = tries; //taking the minimum amount of tries
            else if(tries<minimum)
                minimum = tries;
            
            if(rounds == 1)
                maximum = tries;
            else if(tries>maximum) //taking the maximum amount of tries
                maximum = tries;
            
            cout<<"Average: "<<total/rounds<<", minimum: "<<minimum<<", maximum: "<<maximum<<endl;
        }
    }
    else
    {
    cout<<"The number of rounds must be positive."<<endl;
    return -1;
    }
    
    
}

bool isWordThere(const char words[][MAXWORDLEN+1], const char guessed[100], int nWords)
{
    for(int firstA = 0; firstA<nWords; firstA++)
    {
        if(strcmp(words[firstA], guessed) == 0) //loop through all the words and check if they are equal
            return true;
    }
    return false;
}

int runOneRound(const char words[][MAXWORDLEN+1], int nWords, int wordnum)
{
    
    const int guessLength = 100; // the length amount a guess can hold
    char guess[guessLength]; //guess
    char secretWord[MAXWORDLEN+1]; //holds the secretword
    char holder[MAXWORDLEN+1];
    char holderguess[MAXWORDLEN+1]; //holds the guess word
    strcpy(secretWord, words[wordnum]); //copy the secretword into the cstring secretWord
    int tries = 0; //keeps track of the amount of tries
    int stars = 0;
    int planets = 0;
    int checkLet = 0; //my while loop to keep it in loop unless something is not right
    int goodS = 0;
    int checkLet2 = 0;
    if(nWords<1)
        return -1;
    if(wordnum<0 || wordnum>=nWords)
        return -1;
    
    while(checkLet2 == 0)
    {
        stars = 0; //reset stars, planets, checkLet, goodS to 0
        planets = 0;
        checkLet = 0;
        goodS = 0;
        strcpy(holder, secretWord);
        cout<<"Probe word: ";
        cin.getline(guess, guessLength);
        strcpy(holderguess, guess);
        while(checkLet == 0)
        {
            if(strlen(guess)<4)
            {
                cout<<"Your probe word must be a word of 4 to 6 lower case letters."<<endl;
                checkLet = -1;
                break;
            } //checking if it is between 4 to 6 letters
            if(strlen(guess)>6)
            {
                cout<<"Your probe word must be a word of 4 to 6 lower case letters."<<endl;
                checkLet = -1;
                break;
            }
            for(int check = 0; check<strlen(guess); check++)
            {
                if(isalpha(guess[check]))
                { //check if it is a letter and if it is lowercase
                    if(islower(guess[check]))
                    {
                        goodS++; //increment this variable. If all the letters are good, this variable should equal the length
                        continue;
                    }
                    else
                    {
                        cout<<"Your probe word must be a word of 4 to 6 lower case letters."<<endl;
                        checkLet = -1;
                        break;
                    }
            
                }
                else
                {
                    cout<<"Your probe word must be a word of 4 to 6 lower case letters."<<endl;
                    checkLet = -1;
                    break;
                }
        
            }
            if(checkLet == -1) //if its -1 then it breaks out of the entire loop
            {break;}
            if(!isWordThere(words, guess, nWords))
            {
                cout<<"I don't know that word."<<endl; //checking if the word is inside the array
                checkLet = -1;
                break;
            }
            tries++; //increment tries to keep track of how many tries taken
            for(int sec = 0; sec<strlen(guess); sec++) //loops through the guess and compares it to characters of the secretword
            {
                        for(int d = 0; d<strlen(holder); d++) //do stars first
                        {
                            if(guess[sec] == holder[d]) //if the characters are equal
                            {
                                if(sec == d) //check to see if the position is equal and increment stars
                                    {
                                        stars++;
                                        holder[d] = 'A'; //set that character to an invalid one becuase it cannot be compared to anymore
                                        guess[sec] = 'B';
                                        break;
                                    }
                            }
                        }
            }

            
                for(int plans = 0; plans<strlen(guess); plans++)
                {
                        for(int c = 0; c<strlen(holder); c++) //do planets next
                        {
                            if(guess[plans] == holder[c])
                            {
                               planets++; //if the position is not equal, increment planets
                               holder[c] = 'A';
                                guess[plans] = 'B';
                                break;
                            }
                        }
                }
                
            
            if(goodS == strlen(guess)) //if the length is equal to amount of correct characters, it is good
                checkLet = 1;
        }
        
        strcpy(guess, holderguess);
        if(isWordThere(words, holderguess, nWords) && stars!=strlen(secretWord))
           {
        cout<<"Stars: "<<stars<<", Planets: "<<planets<<endl;
           }
        
        if(stars == strlen(secretWord)) //if the stars is equal to the secretword length, that means that they are all correct and they match
            checkLet2 = 1;
            

    }
    
    return tries;
}
