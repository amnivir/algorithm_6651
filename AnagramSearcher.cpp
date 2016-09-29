//============================================================================
// Name        : ProgAssign1.cpp
// Author      : Shivam Nigam
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
/**
 * How to run this program?
 * STEP 1: copy the src file and input file
 *      * [ s_niga: ~/algorithm_6651/assign1/src ]$ ll
		total 168K
		-rw-r--r-- 1 s_niga s_niga 4.0K Sep 28 19:35 AnagramSearcher.cpp
		-rw-r--r-- 1 s_niga s_niga  123 Sep 28 19:36 ProgrammingAssignment1SampleInput1.txt
		-rw-r--r-- 1 s_niga s_niga  78K Sep 28 19:31 ProgrammingAssignment1SampleInput2.txt

	STEP2: Compile the src file with necessary flags.
	   [ s_niga: ~/algorithm_6651/assign1/src ]$ g++ -std=c++11 AnagramSearcher.cpp -o anagram

	STEP3: Execute the binary
	   [ s_niga: ~/algorithm_6651/assign1/src ]$ ./anagram
	   Size of Dictionary + Jumbled Words=13
	   Total Time Taken in Microseconds=3385

	STEP4: "outfile.txt" will be created in the same directory
	  [ s_niga: ~/algorithm_6651/assign1/src ]$ ll
	   total 168K
		-rw-r--r-- 1 s_niga s_niga 4.0K Sep 28 19:35 AnagramSearcher.cpp
		-rw-r--r-- 1 s_niga s_niga  123 Sep 28 19:36 ProgrammingAssignment1SampleInput1.txt
		-rw-r--r-- 1 s_niga s_niga  78K Sep 28 19:31 ProgrammingAssignment1SampleInput2.txt
		-rw-rw---- 1 s_niga s_niga  16K Sep 28 19:32 ProgrammingAssignment1SampleOutput2.txt
		-rwxrwxr-x 1 s_niga s_niga  43K Sep 28 19:40 anagram
		-rw-rw-r-- 1 s_niga s_niga  150 Sep 28 19:40 output.txt

  	STEP5: read or diff the "output" file from a reference
     */

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <sys/time.h>

using namespace std;

bool isAnagram(const string &, const string &);

int main() {
    timeval tv;
    long int startTime,endTime;

    gettimeofday(&tv, 0); //Read time before the algorithm start

    multimap<int , string > dictionary; //store dictionary words with their length as keys
    list < string > jumbledString; //store jumble words
    multimap<int ,string>::const_iterator itlow; // iterate through dictionary words

    int count=0; // count number of strings in dictionary with specific length

    startTime = tv.tv_usec; //stopwatch

    /**
     * Read file that contains dictionary and jumbled words.
     * This file must be located at the same directory where the binary is stored.
     *
     * */

    ifstream inFile("ProgrammingAssignment1SampleInput2.txt",ios::in);
    ofstream outFile;
    outFile.open("output.txt",ofstream::out);



    if(!inFile)
    {
        cerr<<"File cannot be opened. Check line 64-66 in AnagramSearcher.cpp!!";
        exit(EXIT_FAILURE);
    }

    string str;
    bool firstDelimiterFound=false;
    while(inFile>>str)
    {
        if(str.at(1)== '-')
            {
            firstDelimiterFound=true;
            continue;
            }

        if(!firstDelimiterFound)
            dictionary.insert(make_pair(str.length(),str));
        else
            jumbledString.push_back(str);
    }

    /*cout<<"Stringd before limiter"<<endl;
    for( auto mapItems : mapStringLength)
        cout << mapItems.second<<" "<<mapItems.first<< endl; // prints !!!Hello World!!!

    cout<<"Strings after limiter"<<endl;
    for(auto listItems : string2 )
        cout<<listItems<<endl;*/

    //itup = mapStrLength.upper_bound ('d');

    for(auto listItem : jumbledString )
    {
        int i=0;
        itlow = dictionary.lower_bound (listItem.length());  // itlow points to b
        count = dictionary.count(listItem.length());

        if( count == 0 )
        {
            outFile<<"No Answer Found"<<endl;
            continue;
        }

        bool anagramFound = false;
        while (i<count)
        {
            if(itlow->first == listItem.length())
            {
                if(isAnagram(itlow->second,listItem))
                {
                	anagramFound=true;
                    outFile<<itlow->second<<endl;
                }
            }

            else //if the length of the string does not occur
                {
            		outFile<<"No Answer Found"<<endl;
                }

            ++i;
            ++itlow;
        }

        if(!anagramFound)
            {
        		outFile<<"No Answer Found"<<endl;
            }
        outFile<<"-------------------"<<endl;
    }

    /*string x="abc";
    string y="abd";
    cout<<isAnagram(x,y);*/
    inFile.close();
    outFile.close();

    gettimeofday(&tv, 0);
    endTime= tv.tv_usec;
    cout<<"Size of Dictionary + Jumbled Words="<<dictionary.size()<<endl;
    cout<<"Total Time Taken in Microseconds="<<endTime-startTime<<endl;
    return 0;
}

/*
 * input: two strings
 * output: boolean true if strings are anagram , false otherwise
 * prerequsite: both strings must be equal in length
 * logic: Go through string1 and increase the frequency of each character in an Array A of length 26(26 alphabets)
 * 		  From the same array A , decrease the frequency of each character from other string
 * 		  If the Array has all 0's , then both strings are anagram otherwise not.
 *
 */
bool isAnagram(const string& string1 , const string& string2)
{
    int charFreq[26]={0}; //assign zero to all elements


    for(int i=0;i<string1.length();++i)//length of string1 and string2 are same!
    {
        ++charFreq[(int) string1.at(i) - 'a'];
        --charFreq[(int) string2.at(i) - 'a'];
    }

    for(int i=0;i<26;i++)
    {
        //cout<<charFreq[i];
        if(charFreq[i]!=0)
            return false;
    }
    return true;
}
