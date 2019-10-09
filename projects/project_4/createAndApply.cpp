#include "createAndApply.h"
#include "hash.h"
#include "smallbergfxns.h"
#include <iostream>
using namespace std;

void createDiff(istream& fold, istream& fnew, ostream& fdiff)
{
    size_t hashnum = 8;
    // Read in the entire contents of the old file into a string. Read the entire contents of the new file into another string.
    //old string
    char c;
    string oldString = "";
    while (fold.get(c))
    {
        oldString += c;
    }
    //new string
    string newString = "";
    while (fnew.get(c))
    {
        newString += c;
    }
    
    //if the file is too big then increase the hash size
    if(newString.length() > 50000)
    {
        hashnum = 32;
    }
    
    //if both are same
    if(oldString == newString || newString.length() == 0)
    {
        fdiff << '\n';//should you do this
        return;
    }
    
    // new file is less than hashnum
    if(newString.length() < hashnum || oldString.length() < hashnum)
    {
        auto addNumChar = newString.length();
        auto addString = newString.substr(0,addNumChar);
        fdiff << 'A' << addNumChar << ':' << addString;
//        cerr << 'A' << addNumChar << ':' << addString;
        return;
    }
    
    // add to the hash table
    HashTable hashtable;
    for(size_t i = 0; i <= oldString.length() - hashnum; i++)
    {
        string oldChunk = oldString.substr(i, hashnum);
        hashtable.insert(oldChunk , i);
    }
    
    unsigned long offset = 0;
    size_t j = 0;
    for(; j <= newString.length() - hashnum; j++)
    {
        string newChunk = newString.substr(j, hashnum);
//        cerr << '<' <<newChunk << '>';
       bool contain = hashtable.contains(newChunk, offset);
        if(contain) // COPY
        {
            unsigned long bestlength;
            auto bestIndex = hashtable.findBestCopyIndex(oldString, newString, newChunk, bestlength, j);
            auto copyNumChar = bestlength;
            fdiff << 'C' << copyNumChar << ',' << bestIndex;
//            cerr << 'C' << copyNumChar << ',' << bestIndex;
            j = j + bestlength - 1;
            offset = 0;
        }
        else // ADD
        {
            offset = 0;
            size_t push = j;
            // while the hash num + the offset is less than or equal to the string and
            // the hashtable doesn't contain the string
            bool containsNext = false; // should be false
            bool notOutOfBounds = push + hashnum < newString.length();
            while( notOutOfBounds &&
                  !containsNext)
            {
                push++;
                containsNext = hashtable.contains(newString.substr(push, hashnum), offset);
                notOutOfBounds = push + hashnum <= newString.length();
            }
            if(containsNext)
            {
                push--;
            }
            if(!notOutOfBounds)
            {
                auto addNumChar = push - j + hashnum;
                auto addString = newString.substr(j, addNumChar);
                fdiff << 'A' << addNumChar << ':' << addString;
//                cerr << 'A' << addNumChar << ':' << addString;
                return;
            }
            auto addNumChar = 1 + push - j;
            auto addString = newString.substr(j, addNumChar);
            fdiff << 'A' << addNumChar << ':' << addString;
//            cerr << 'A' << addNumChar << ':' << addString;
            j = push;
        }
    }
    if(0 < newString.length() - hashnum - j)
    {
        auto addNumChar = newString.length() - j;
        auto addString = newString.substr(j, addNumChar);
        if(addNumChar == 0)
        {
            return;
        }
        fdiff << 'A' << addNumChar << ':' << addString;
//        cerr << 'A' << addNumChar << ':' << addString;
    }
}

bool applyDiff(istream& fold, istream& fdiff, ostream& fnew)
{
    // make a string for fold
    char c;
    string oldString = "";
    while (fold.get(c))
    {
        oldString += c;
    }
    
    //loop through the diff file
    string output = "";
    bool leave = false;
    while(fdiff && !leave)
    {
        char cmd;
        int length = 0;
        int offset = 0;
        if(!getCommand(fdiff, cmd, length, offset))
        {
            return false;
        }
        switch (cmd)
        {
            case 'A'://case add
                //loop for a certain ammount of char and add them to your new file
                if(length < 0)
                {
                    return false;
                }
                while( length != 0 )
                {
                    if(!fdiff.get(c))
                    {
                        return false;
                    }
                    fnew << c;
                    length--;
                }
                break;
            case 'C'://case copy
                if(offset + length > static_cast<int>(oldString.size()) || offset < 0 || length < 0)
                {
                    return false;
                }
                output = oldString.substr(offset, length);
                fnew << output;
                break;
            case 'x'://file end
                leave = true;
                break;
            case '\n':
            case '\r':
            default:
                break;
        }
    }
    return true;
}
