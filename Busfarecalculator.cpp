//
//  fare.cpp
// Project 2
//
//  Created by Samuel J. Lee on 10/12/17.
//  Copyright © 2017 Samuel J. Lee. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;
int main()
{
    cout.setf(ios::fixed); //so I can set everything to 2 decimal places from the beginning
    cout.precision(2);
    
    string destination;  // Initializing my string, char, int, and double variables
    char student;
    int age, boundaries;
    double fare = 0.00; //I set fare = 0.00 to avoid fare being uninitialized
    
    cout<<"Age of rider: "; //prints "Age of rider: " so that users can input the age
    cin>>age;
    
    cout<<"Student? (y/n): ";
    cin>>student;
    cin.ignore(10000,'\n');
    //cin before a getline outputs a result I don't want so I need to throw away until new line character or
    // until I've thrown away 10,000 characters (whichever comes first)
    
    cout<<"Destination: ";
    getline(cin, destination); //need to use getline() for strings
    
    cout<<"Number of zone boundaries crossed: ";
    cin>>boundaries;
    
    cout<<"---"<<endl; //so that it is always outputted before everything else
    
    //first set of if statements to test for erroneous/nonsensical inputs
    //I put them in order, to ensure that only one line of error comes out and it comes in the correct order
                if(age<0)
                        {
                            cout<<"The age must not be negative"<<endl;
                            return 1;  //returning nonzero to exit the program, showing failure
                        }
                if(student!='y' && student!='n')
                        {
                            cout<<"You must enter y or n"<<endl;
                            return 1;
                        }
                if(destination=="")
                        {
                            cout<<"You must enter a destination"<<endl;
                            return 1;
                        }
                if(boundaries<0)
                        {
                            cout<<"The number of zone boundaries crossed must not be negative"<<endl;
                            return 1;
                        }
    
    if(age<18 || student == 'y' || age>=65) //wrote a general if statement for all qualifications for discounts to lead to the else statement for those who do not qualify for any discounts
        
    {
        if(age<18 || student == 'y') //same benefits for those that are either under 18 or a student
        {
            if(boundaries==0 || boundaries==1)
            {
                fare=0.65;
            }
            else
            {
                fare = 1.35 + (0.55*boundaries); //standard charge for over 1 boundary
            }
            
        }
        if(age>=65 && student == 'n') //senior discount for non-students
        {
            
            if(boundaries==0) //if 0 boundaries are crossed, then the senior discount is always lower than the student one
            {
                fare=0.45;
            }
            else
            {
                fare = 0.55 + (0.25*boundaries);
                cout<<"The fare to "<<destination<<" is $"<<fare<<endl;
                return 1;
            }
            
            }
        
        if(age>=65 && student == 'y') //senior student discount
        {

            if(boundaries==0) //if 0 boundaries are crossed, then the senior discount is always lower than the student one
            {
                fare=0.45;
            }
            else
            {
                if(fare<(0.55 + (0.25*boundaries)))
                    //For seniors who are students that want the lowest fare possible. (usually only when only 1 boundary is crossed.
                    //It's not possible for them to be equal unless the boundary is a negative decimal number.
                {
                    cout<<"The fare to "<<destination<<" is $"<<fare<<endl;
                    return 1;
                }
                else
                {
                fare = 0.55 + (0.25*boundaries);
                }
            }
        }
    }
    else
    {
        fare = 1.35 + (0.55 * boundaries); //anyone who doesn't qualify for a discount
    }
    cout<<"The fare to "<<destination<<" is $"<<fare<<endl;
    
        
}
