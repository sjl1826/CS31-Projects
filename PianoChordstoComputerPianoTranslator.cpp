//
//  keyboard.cpp
//
//  Created by Samuel J. Lee on 10/20/17.
//  Copyright © 2017 Samuel J. Lee. All rights reserved.
//

#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
using namespace std;

char encodeNote(int octave, char noteLetter, char accidentalSign); //translates the notes
bool hasCorrectSyntax(string song); //Checks for correct syntax
bool letterCheck(char cho); //checks if it is a letter
bool isacciSign(char sig); //checks if it is an accidental sign
int encodeSong(string song, string& instructions, int& badBeat);

int main()
{
    assert(hasCorrectSyntax("D5//D/"));
    assert(!hasCorrectSyntax("D5//Z/"));
    assert(!hasCorrectSyntax("adfge"));
    assert(!hasCorrectSyntax("a/g/E#/B/"));
    assert(!hasCorrectSyntax("a#b/g/"));
    assert(!hasCorrectSyntax("a#3/g#4/"));
    assert(hasCorrectSyntax("G/"));
    assert(!hasCorrectSyntax("AAAAAA"));
    assert(hasCorrectSyntax("AAA/G/G/B/AAAAAAAAAAAAAAAA/E/E/E////////G/"));
    assert(!hasCorrectSyntax("A"));
    assert(!hasCorrectSyntax("E#/GBC#"));
    assert(hasCorrectSyntax("B#/"));
    assert(!hasCorrectSyntax("C##/"));
    assert(hasCorrectSyntax("C#B#G#/////"));
    assert(hasCorrectSyntax("G#A/"));
    assert(hasCorrectSyntax("F#3/G1/B1C1A1////G#9/A#2/B3/"));
    assert(hasCorrectSyntax("A4/B1/E9/"));
    assert(!hasCorrectSyntax("C67/B10/"));
    assert(!hasCorrectSyntax("C10"));
    assert(hasCorrectSyntax("C0C0DC0DD/E#FbB#Cb/B#9/"));
    assert(!hasCorrectSyntax("/#/"));
    assert(!hasCorrectSyntax("/3//"));
    assert(!hasCorrectSyntax("/b/"));
    
    string instrs;
    int badb;
    instrs = "xxx"; badb = -999; // so we can detect whether these get changed
    assert(encodeSong("B#1Cb6C6/Cb2/", instrs, badb) == 2  &&  instrs == "xxx"  &&  badb == 2);
    instrs = "xxx"; badb = -999; // so we can detect whether these get changed
    assert(encodeSong("B#1Cb6C6/C/", instrs, badb) == 0  &&  instrs == "[ZOP]G"  &&  badb == -999);
    instrs = "xxx"; badb = -999;
    assert(encodeSong("///", instrs, badb) == 0  &&  instrs == "   "  &&  badb == -999);
    instrs = "xxx"; badb = -999; // so we can detect whether these get changed
    assert(encodeSong("adfge", instrs, badb) == 1  &&  instrs == "xxx"  &&  badb == -999);
    instrs = "xxx"; badb = -999; // so we can detect whether these get changed
    assert(encodeSong("AGCE", instrs, badb) == 1  &&  instrs == "xxx"  &&  badb == -999);
    instrs = "xxx"; badb = -999;
    assert(encodeSong("a/G/", instrs, badb) == 1  &&  instrs == "xxx"  &&  badb == -999);
    instrs = "xxx"; badb = -999; // so we can detect whether these get changed
    assert(encodeSong("A#/G#3/B/", instrs, badb) == 0  &&  instrs == "%9W"  &&  badb == -999);
    instrs = "xxx"; badb = -999; // so we can detect whether these get changed
    assert(encodeSong("", instrs, badb) == 0  &&  instrs == ""  &&  badb == -999);
    instrs = "xxx"; badb = -999;
    assert(encodeSong("////G//", instrs, badb) == 0  &&  instrs == "    L "  &&  badb == -999);
    instrs = "xxx"; badb = -999; // so we can detect whether these get changed
    assert(encodeSong("//A/B#3/G4", instrs, badb) == 1  &&  instrs == "xxx"  &&  badb == -999);
    instrs = "xxx"; badb = -999; // so we can detect whether these get changed
    assert(encodeSong("/#//", instrs, badb) == 1  &&  instrs == "xxx"  &&  badb == -999);
    instrs = "xxx"; badb = -999;
    assert(encodeSong("A7/G#9/C/", instrs, badb) == 2  &&  instrs == "xxx"  &&  badb == 1);
    instrs = "xxx"; badb = -999; // so we can detect whether these get changed
    assert(encodeSong("A2/C#5/BBBBBB/EEE/FF/GGGG/", instrs, badb) == 0  &&  instrs == "N^[WWWWWW][JJJ][KK][LLLL]"  &&  badb == -999);
    instrs = "xxx"; badb = -999; // so we can detect whether these get changed
    assert(encodeSong("A2///B////G6/", instrs, badb) == 2  &&  instrs == "xxx"  &&  badb == 8);
    instrs = "xxx"; badb = -999;
    assert(encodeSong("AGDEF", instrs, badb) == 1  &&  instrs == "xxx"  &&  badb == -999);
    instrs = "xxx"; badb = -999; // so we can detect whether these get changed
    assert(encodeSong("AGDEF/", instrs, badb) == 0  &&  instrs == "[QLHJK]"  &&  badb == -999);
    instrs = "xxx"; badb = -999; // so we can detect whether these get changed
    assert(encodeSong("G3B3DD5//G/A/A3B/C5/B3D5//G//G//CE5//C5/D5/E5/F#5/B3G5//G//G/", instrs, badb) == 0  &&  instrs == "[SFHR] LQ[DW]E[FR] L L [GT] ERT*[FU] L L"  &&  badb == -999);
    instrs = "xxx"; badb = -999;
    assert(encodeSong("DADDA/", instrs, badb) == 0  &&  instrs == "[HQHHQ]"  &&  badb == -999);
    instrs = "xxx"; badb = -999; // so we can detect whether these get changed
    assert(encodeSong("a#3/B4/", instrs, badb) == 1  &&  instrs == "xxx"  &&  badb == -999);
    instrs = "xxx"; badb = -999; // so we can detect whether these get changed
    assert(encodeSong("A10/B14/", instrs, badb) == 1  &&  instrs == "xxx"  &&  badb == -999);
    instrs = "xxx"; badb = -999;
    assert(encodeSong("B4/CCC6/G#4/B#3/A7/", instrs, badb) == 2  &&  instrs == "xxx"  &&  badb == 5);
    instrs = "xxx"; badb = -999; // so we can detect whether these get changed
    assert(encodeSong("//", instrs, badb) == 0  &&  instrs == "  "  &&  badb == -999);
    instrs = "xxx"; badb = -999; // so we can detect whether these get changed
    assert(encodeSong("/", instrs, badb) == 0  &&  instrs == " "  &&  badb == -999);
    instrs = "xxx"; badb = -999;
    assert(encodeSong(" ", instrs, badb) == 1  &&  instrs == "xxx"  &&  badb == -999);
    instrs = "xxx"; badb = -999; // so we can detect whether these get changed
    assert(encodeSong("B#1Cb6C6/Cb2/", instrs, badb) == 2  &&  instrs == "xxx"  &&  badb == 2);
    instrs = "xxx"; badb = -999; // so we can detect whether these get changed
    assert(encodeSong("C3/AA/Cb2/", instrs, badb) == 2  &&  instrs == "xxx"  &&  badb == 3);
    instrs = "xxx"; badb = -999;
    assert(encodeSong("B/C/E/GGG/E/F#/G#/A#///B1/", instrs, badb) == 2  &&  instrs == "xxx"  &&  badb == 11);
    instrs = "xxx"; badb = -999; // so we can detect whether these get changed
    assert(encodeSong("C/C/G/G/A/A/G/", instrs, badb) == 0  &&  instrs == "GGLLQQL"  &&  badb == -999);
    instrs = "xxx"; badb = -999; // so we can detect whether these get changed
    assert(encodeSong("D3/F#3/A3/D4//D3F#3A3D4/", instrs, badb) == 0  &&  instrs == ".8DH [.8DH]"  &&  badb == -999);
    instrs = "xxx"; badb = -999;
    assert(encodeSong("C0C0DC0DD/E#FbB#Cb/B#9/", instrs, badb) == 2  &&  instrs == "xxx"  &&  badb == 1);
    instrs = "xxx"; badb = -999;
    assert(encodeSong("//33/3", instrs, badb) == 1  &&  instrs == "xxx"  &&  badb == -999);
    instrs = "xxx"; badb = -999;
    assert(encodeSong("/////4", instrs, badb) == 1  &&  instrs == "xxx"  &&  badb == -999);
    instrs = "xxx"; badb = -999; // so we can detect whether these get changed
    assert(encodeSong("#/", instrs, badb) == 1  &&  instrs == "xxx"  &&  badb == -999);
    instrs = "xxx"; badb = -999; // so we can detect whether these get changed
    assert(encodeSong("G##/", instrs, badb) == 1  &&  instrs == "xxx"  &&  badb == -999);
    instrs = "xxx"; badb = -999;
    assert(encodeSong("G#3/G8/", instrs, badb) == 2  &&  instrs == "xxx"  &&  badb == 2);
    instrs = "xxx"; badb = -999; // so we can detect whether these get changed
    assert(encodeSong("/*/", instrs, badb) == 1  &&  instrs == "xxx"  &&  badb == -999);
    instrs = "xxx"; badb = -999; // so we can detect whether these get changed
    assert(encodeSong("C66/", instrs, badb) == 1  &&  instrs == "xxx"  &&  badb == -999);
    instrs = "xxx"; badb = -999;
    assert(encodeSong("CBCCCCC//////8C/", instrs, badb) == 1  &&  instrs == "xxx"  &&  badb == -999);
    instrs = "xxx"; badb = -999; // so we can detect whether these get changed
    assert(encodeSong("B/C/DDD/EE/F#5/C6/Cb2/B#1///F#H/", instrs, badb) == 1  &&  instrs == "xxx"  &&  badb == -999);
    instrs = "xxx"; badb = -999; // so we can detect whether these get changed
    assert(encodeSong("b/", instrs, badb) == 1  &&  instrs == "xxx"  &&  badb == -999);
    instrs = "xxx"; badb = -999;
    assert(encodeSong("B/C/E/GGG/E/F#/G#", instrs, badb) == 1  &&  instrs == "xxx"  &&  badb == -999);
    instrs = "xxx"; badb = -999; // so we can detect whether these get changed
    assert(encodeSong("C/C/G/G/A/A/G9/", instrs, badb) == 2  &&  instrs == "xxx"  &&  badb == 7);
    instrs = "xxx"; badb = -999; // so we can detect whether these get changed
    assert(encodeSong("D/A5/6/", instrs, badb) == 1  &&  instrs == "xxx"  &&  badb == -999);
    instrs = "xxx"; badb = -999;
    assert(encodeSong("C4B4A4D4E4F4G9/", instrs, badb) == 2  &&  instrs == "xxx"  &&  badb == 1);
    instrs = "xxx";badb = -999;
    assert(encodeSong("C6/C#6/Db6/D6/D#6/Eb6/E6/E#6/F6/F#6/Gb6/G6/G#6/", instrs, badb) == 2 && badb == 2 && instrs == "xxx");
    instrs = "xxx";badb = -999;
    assert(encodeSong("C#6///", instrs, badb) == 2 && badb == 1 && instrs == "xxx");
    instrs = "xxx";badb = -999;
    assert(encodeSong("Cb2/", instrs, badb) == 2 && badb == 1 && instrs == "xxx");
    instrs = "xxx";badb = -999;
    assert(encodeSong("G3 A5/Bb/", instrs, badb) == 1 && badb == -999 && instrs == "xxx");
    instrs = "xxx";badb = -999;
    assert(encodeSong("", instrs, badb) == 0 && badb == -999 && instrs == "");
    instrs = "xxx";badb = -999;
    assert(encodeSong("ABC//DEF/G0//", instrs, badb) == 2 && badb == 4 && instrs == "xxx");
    instrs = "xxx";badb = -999;
    assert(encodeSong("hello my name is Adam", instrs, badb) == 1 && badb == -999 && instrs == "xxx");
    instrs = "xxx";badb = -999;
    assert(encodeSong("ABC//C#3/Abb5//", instrs, badb) == 1 && badb == -999 && instrs == "xxx");
    instrs = "xxx";badb = -999;
    assert(encodeSong("ABC/ABC/ABC/A55/", instrs, badb) == 1 && badb == -999 && instrs == "xxx");
    instrs = "xxx";badb = -999;
    assert(encodeSong("////////////A3/////A1/", instrs, badb) == 2 && badb == 18 && instrs == "xxx");
    instrs = "xxx";badb = -999;
    assert(encodeSong("A/b5/", instrs, badb) == 1);
    instrs = "xxx";badb = -999;
    assert(encodeSong("C-Ab4-A//", instrs, badb) == 1);
    instrs = "xxx";badb = -999;
    assert(encodeSong("A/B/C/D/E/F/G/", instrs, badb) == 0 && badb == -999 && instrs == "QWGHJKL");
    instrs = "xxx";badb = -999;
    assert(encodeSong("ABC/DEF/G/A/", instrs, badb) == 0 && badb == -999 && instrs == "[QWG][HJK]LQ");
    instrs = "xxx";badb = -999;
    assert(encodeSong("DDDDDDDDD/", instrs, badb) == 0 && badb == -999 && instrs == "[HHHHHHHHH]");
    instrs = "xxx";badb = -999;
    assert(encodeSong("C5/C#5/Db5/D5/D#5/Eb5/E5/E#5/F5/F#5/Gb5/G5/G#5/", instrs, badb) == 0 && badb == -999 && instrs == "E^^R&&TYY**U(");
    instrs = "xxx";badb = -999;
    assert(encodeSong("  ABC/", instrs, badb) == 1 && badb == -999 && instrs == "xxx");
    instrs = "xxx";badb = -999;
    assert(encodeSong("/C5#/", instrs, badb) == 1 && badb == -999 && instrs == "xxx");
    instrs = "xxx";badb = -999;
    assert(encodeSong("//B5Ab4//B3/Db4/A4B3/", instrs, badb) == 0 && instrs == "  [O$] F![QF]" && badb == -999);
    
    cerr << "Good job buddy" << endl;
}

char encodeNote(int octave, char noteLetter, char accidentalSign)
{
    // This check is here solely to report a common CS 31 student error.
    if (octave > 9)
    {
        cerr << "********** encodeNote was called with first argument = "
        << octave << endl;
    }
    
    // Convert Cb, C, C#/Db, D, D#/Eb, ..., B, B#
    //      to -1, 0,   1,   2,   3, ...,  11, 12
    
    int note;
    
    switch (noteLetter)
    {
        case 'C':  note =  0;
            break;
        case 'D':  note =  2;
            break;
        case 'E':  note =  4;
            break;
        case 'F':  note =  5;
            break;
        case 'G':  note =  7;
            break;
        case 'A':  note =  9;
            break;
        case 'B':  note = 11;
            break;
        default:   return ' ';
    }
    
    switch (accidentalSign)
    {
        case '#':  note++; break;
        case 'b':  note--; break;
        case ' ':  break;
        default:   return ' ';
    }
    
    // Convert ..., A#1, B1, C2, C#2, D2, ... to
    //         ..., -2,  -1, 0,   1,  2, ...
    
    int sequenceNumber = 12 * (octave - 2) + note;
    
    string keymap = "Z1X2CV3B4N5M,6.7/A8S9D0FG!H@JK#L$Q%WE^R&TY*U(I)OP";
    if (sequenceNumber < 0  ||  sequenceNumber >= keymap.size())
        return ' ';
    return keymap[sequenceNumber];
}

bool letterCheck(char cho) //checks if the character is a letter A-G
{
    bool Let = false;
    switch(cho)
    {
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
        case 'G':
            Let = true;
            break;
        default: Let = false;
    }
    return Let;
}

bool isacciSign(char sig)
{
    bool sign = false;
    if(sig == '#' || sig == 'b')
    {
        sign = true;
    }
    
    return sign;
}

bool hasCorrectSyntax(string song)
{
    
    string checker = "Y"; //This string checks if every character has correct Syntax in the string. I add a Y in checker if it is okay. I put a N if it is not. If there are any N's then it returns false.
    if(song.size() == 0) //Checking for any 0 beat situations
    {
        return true;
    }
    
    if((letterCheck(song[0]) || (song[0] == '/')) && (song[song.size()-1] == '/')) //checks that the first character is a letter or a '/' and that the last character is a '/'. I did the first character first so that I could check for characters before an accidental sign or digit without going to negative character positions.
    {
        for(string::size_type s = 1; s<song.size(); s++) //started it at one because I already checked the first character
        {
            if(letterCheck(song[s]))
            {
                checker += "Y"; //adds Y to string if it is a letter
            }
            else if(isacciSign(song[s]))
            {
                if(letterCheck(song[s-1])) //the character before must be a letter
                    checker +="Y";
                else
                    checker +="N";
                
                if(letterCheck(song[s+1]) || isdigit(song[s+1]) || song[s+1]=='/') //the character after must be a letter, digit, or slash
                    checker +="Y";
                else
                    checker += "N";
            }
            else if(isdigit(song[s]))
            {
                if(letterCheck(song[s-1]) || isacciSign(song[s-1])) //the character before must be a letter, accidental sign
                    checker +="Y";
                else
                    checker +="N";
                
                if(letterCheck(song[s+1]) || song[s+1]== '/') //the character before must be a letter or a slash
                    checker +="Y";
                else
                    checker +="N";
            }
            else if(song[s] == '/') //checking for beats only
            {
                checker +="Y";
            }
            else
                return false;
        }
        bool chool = false;
        
        for(string::size_type ooch = 0; ooch<checker.size(); ooch++) //loops through the string checker to check for any N's. If there are any it will return false.
        {
            if(checker[ooch]== 'N')
                return false;
            else
                chool = true;
        }
        return chool;
    }
    else
    {
        return false;
    }
    
}


int encodeSong(string song, string& instructions, int& badBeat)
{
    string singleNotes = ""; //stores all single character notes
    string doubNotes = ""; //stores all double character notes such as G5, E#, etc.
    string tripNotes = ""; //stores all triple character notes such as E#3, Bb5, etc.
    string playCheck = ""; //I am adding a "Y" for every playable note and a "N" for every nonplayable note to use it to check if its a
    //playable song
    string finalNote = ""; //I store the single, double, or triple note in here and use it to go to the next note in my for loop
    int numbeat = 1;
    int noteamount = 0; //number of notes passed
    int octave = 4; //default
    char accidentalSign = ' '; //default
    string finalString = "";
    string almString = ""; //to use to put together notes for final string
    if(hasCorrectSyntax(song))
    {
        for(string::size_type play = 0; play<song.size(); play+= finalNote.size()) //I use the size of the previous note to increment to
            //the next note
        {
            if(song[play] == '/')
            {
                numbeat++; //increment beat number
                if(noteamount == 0) // if no notes have passed then add a space
                {
                    finalString += " ";
                    almString = "";
                }
                else if(noteamount == 1) //if there was a preceding note then must add the preceding note to finalstring
                {
                    finalString += almString;
                    almString = ""; //setting almstring to empty so that I can get new notes every time
                }
                else
                {
                    finalString += "["+almString+"]"; //when several notes have passed, I need them in brackets.
                    almString = "";
                }
                
                finalNote = "/"; //setting the finalNote to / so that it the for loop can increment by one
                noteamount = 0; //I reset the noteamount to 0
            }
            else{
                if(letterCheck(song[play])) //if it is a letter by itself then I store it in string singleNotes
                { noteamount++;
                    if(isacciSign(song[play+1])) //if the second character is an accidental sign then I store in doubleNotes
                    {
                        if(isdigit(song[play+2])) //if it has a third character digit then I store it in string tripNotes
                        {
                            tripNotes += song[play];
                            tripNotes += song[play+1];
                            tripNotes += song[play+2];
                            int playtwo = song[play+2]-'0'; //to get rid of ASCII character value
                            almString += encodeNote(playtwo, song[play], song[play+1]);
                        }
                        else
                        {
                            doubNotes += song[play];
                            doubNotes += song[play+1];
                            almString += encodeNote(octave, song[play], song[play+1]);
                        }
                    }
                    else if(isdigit(song[play+1])) //if the second character is a digit then I store the note in doubNotes
                    {
                        doubNotes += song[play];
                        doubNotes += song[play+1];
                        int playone = song[play+1] - '0';
                        almString += encodeNote(playone, song[play], accidentalSign);
                    }
                    else
                    {
                        singleNotes += song[play];
                        almString += encodeNote(octave, song[play], accidentalSign);
                    }
                }
                if(singleNotes.size()>0) //If it is a single note then it has to be correct and I add a "Y" to playCheck
                {
                    playCheck +="Y";
                    finalNote = singleNotes; //setting it equal to finalNote so that it will increment to the next note correctly
                }
                else if(doubNotes.size()>0) //checking if it's a two character note
                {
                    switch(doubNotes[1])
                    {
                        case '#': //It will be correct if it has an accidental sign after
                        case 'b':
                            playCheck += "Y";
                            break;
                        case '2':
                        case '3':
                        case '4':
                        case '5':
                            playCheck +="Y"; //in two character notes, cases with digits 2,3,4,5 are always good
                            break;
                        case '6':
                            if(doubNotes[0] == 'C') //C6 is okay but any other letters with digit 6 are not
                                playCheck += "Y";
                            else
                                playCheck += "N";
                            break;
                        default: playCheck +="N"; //in case of any errors
                            break;
                    }
                    finalNote = doubNotes;
                }
                else if(tripNotes.size()>0)
                {
                    switch(tripNotes[2])
                    {
                        case '1':
                            if(tripNotes[1] == '#' && tripNotes [0] == 'B') //digit can only be 1 if it is B#1
                                playCheck+="Y";
                            else
                                playCheck+="N";
                            break;
                        case '2':
                            if(tripNotes[1] == 'b' && tripNotes[0] == 'C') // All cases of digit 2 are okay except Cb2
                                playCheck += "N";
                            else
                                playCheck += "Y";
                            break;
                        case '3':
                        case '4':
                        case '5':
                            playCheck += "Y"; //all cases of digits 3,4,5 are good
                            break;
                        case '6':
                            if(tripNotes[1] == 'b' && tripNotes[0] == 'C') //Only Cb6 is okay in triple character Notes
                                playCheck += "Y";
                            else
                                playCheck +="N";
                            break;
                        default: playCheck +="N";
                            break;
                    }
                    finalNote = tripNotes;
                }
                for(string::size_type kameo = 0; kameo<playCheck.size(); kameo++) //Checking for the character 'N' to see if there are errors
                {
                    if(playCheck[kameo] == 'N')
                    {
                        badBeat = numbeat; //If there is an error, then I set badBeat equal to numbeat which is the beat number that there was an error and return 2
                        return 2;
                    }
                    else
                    {
                        singleNotes = ""; //set them all to empty strings so I can start over again with the next note
                        doubNotes = "";
                        tripNotes = "";
                    }
                }
            }
        }
        instructions = finalString; //set the finalized string equal to instructions
        return 0;
    }
    else
        return 1;
}


