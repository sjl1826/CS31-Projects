//
//  main.cpp
//  array.cpp
//
//  Created by Samuel J. Lee on 10/31/17.
//  Copyright © 2017 Samuel J. Lee. All rights reserved.
//

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int appendToAll(string a[], int n, string value);
int lookup(const string a[], int n, string target);
int positionOfMax(const string a[], int n);
int rotateLeft(string a[], int n, int pos); //don't use an extra array
int countRuns(const string a[], int n);;
int flip(string a[], int n); //don't use an extra array
int differ(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int lookupAny(const string a1[], int n1, const string a2[], int n2);
int split(string a[], int n, string splitter); //don't use an extra array


int main()
{
    string h[7] = { "selina", "reed", "diana", "tony", "", "logan", "peter" };
    assert(lookup(h, 7, "logan") == 5);
    assert(lookup(h, 7, "diana") == 2);
    assert(lookup(h, 2, "diana") == -1);
    assert(positionOfMax(h, 7) == 3);
    
    string g[4] = { "selina", "reed", "peter", "sue" };
    assert(differ(h, 4, g, 4) == 2);
    assert(appendToAll(g, 4, "?") == 4 && g[0] == "selina?" && g[3] == "sue?");
    assert(rotateLeft(g, 4, 1) == 1 && g[1] == "peter?" && g[3] == "reed?");
    
    string e[4] = { "diana", "tony", "", "logan" };
    assert(subsequence(h, 7, e, 4) == 2);
    
    string d[5] = { "reed", "reed", "reed", "tony", "tony" };
    assert(countRuns(d, 5) == 2);
    
    string f[3] = { "peter", "diana", "steve" };
    assert(lookupAny(h, 7, f, 3) == 2);
    assert(flip(f, 3) == 3 && f[0] == "steve" && f[2] == "peter");
    
    assert(split(h, 7, "peter") == 3);
    
    cout << "All tests succeeded" << endl;
}

int appendToAll(string a[], int n, string value)
{
    if(n<0)
        return -1;
    for(int i = 0; i<n; i++)
    {
        a[i] += value; //loops through every array position and appends value to it
    }
    return n;
}

int lookup(const string a[], int n, string target)
{
    if(n<0)
        return -1;
    for(int k = 0; k<n; k++)
    {
        if(a[k] == target) //if string at array position k equals target, return array position k
        {
            return k;
        }
    }
    return -1;
}

int positionOfMax(const string a[], int n)
{
    if(n<1)
        return -1;
    int tracker = 0;
    for(int first = 0; first<n; first++)
    {
        for(int others = 0; others<n; others++)
        {
            if(a[first] >= a[others])
            {
                tracker++; //check to see if each position is greater than or equal to all the others and increments tracker
            }
            if(tracker == n)
            {
                return first; //tracker should be equal to n if the position is the greatest
            }
        }
        tracker = 0;
    }
    return -1;
}


int rotateLeft(string a[], int n, int pos)
{
    if(n<=0 || pos<0 || pos>=n)
        return -1;
    string holder = a[pos]; //record initial position to add to the end later
    for(int s = pos; s<n-1; s++)
    {
        a[s] = a[s+1]; //take the right array string and move it to the left
    }
    a[n-1] = holder; //adding the initial string to the end
    return pos;
}

int countRuns(const string a[], int n)
{
    int fint = 1;
    if(n<0)
        return -1;
    if(n == 0)
        return 0;
    for(int d = 0; d<n-1; d++)
    {
        if(a[d] != a[d+1]) //if the string does not equal the one after, it is a new sequence
        {
            fint++; //keeps track of all sequences
        }
    }
    return fint;
}

int flip(string a[], int n)
{
    if(n<0)
        return -1;
    int g = n-1;
    string holder;
    for(int b = 0; b<(n/2); b++) // n/2 is the middle
    {
        holder = a[b]; //record the initial one that is getting switched
        a[b] = a[g];  //move the opposite string to the initial position
        a[g] = holder; //move the initial to the opposite
        g--;
    }
    
    return n;
}

int differ(const string a1[], int n1, const string a2[], int n2)
{
    if(n1<0 || n2<0)
        return -1;
    int h = 0;
    for(; h<n1 && h<n2; h++)
    {
        if(a1[h] == a2[h]) //if they are equal/corresponding, keep going to check every position
            continue;
        else
            break; //if they are not equal anymore, then break out of the loop and return the position
    }
    return h;
}

int subsequence(const string a1[], int n1, const string a2[], int n2)
{
    if(n1<0 || n2<0 || (n2>n1)) //n1 and n2 cannot be negative
        return -1;
    if(n1>=n2 && n2 == 0)
        return 0;
    int u = 0;
    int z = 1;
    for(int t = 0; t<n1; t++)
    {
        if(a1[t] == a2[0]) //finds the first position that a2's first position is equal to
        {
            u = t; //sets the variable equal to first position to return it
                for(int y = t+1; y<n1; y++)
                {
                    if(z<n2)
                    {
                        if(a1[y] == a2[z]) //checks if every contiguous is equal to the next one
                        {
                            z++; //if they are all equal, z will equal n2
                        }
                        else
                            return -1;
                    }
                }
            
            if(z == n2)
                return u;
        }
    }
    return -1;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
    if(n1<1 || n2<1)
        return -1;
    for(int m = 0; m<n1; m++)
    {
        for(int n = 0; n<n2; n++)
        {
            if(a1[m] == a2[n]) //checks every element in m to every element in n
            {
                return m; //if it is equal it will return the first position
            }
        }
    }
    return -1;
}

int split(string a[], int n, string splitter)
{
    if(n<0)
        return -1;
    string holder; //holds the string element to change it
    int numElm = 0; //the number the element is at
    for(int one = 0; one<n; one++)
    {
        if(a[one]<splitter)
        {
        holder = a[numElm]; //holds element
        a[numElm] = a[one]; //switch them
        a[one] = holder; //puts the held element into other position
        numElm++;
        }
        
    }
    for(int arr3 = 0; arr3<n; arr3++)
    {
        if(a[arr3] == splitter)
        {
        holder = a[numElm];
        a[numElm] = a[arr3];
        a[arr3] = holder;
        numElm++;
        }
    }
    
    for(int cool = 0; cool<n; cool++)
    {
        if(a[cool]>=splitter)
        {
            return cool; //checks for elements that are bigger than or equal to splitter, if there are none than it will break
        }
    }
    return n;
}
