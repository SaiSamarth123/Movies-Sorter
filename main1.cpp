// 
// Completed version of Project 3 written by
// Author: Sai Samarth, U. of Illinois Chicago, Fall 2020
// Description: Stores netflix movies into an array and then sorts them based on ID and title

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>  // isspace


using namespace std;

struct Movies
{
   string title;
   int movieID;
   int year;
};

void sortID(Movies* netflix, int size) // function to sort the movies by ID
{
    
   for (int i = 0; i < size - 1; ++i) {

   // Find index of smallest remaining element
   int indexSmallest = i;
   for (int j = i + 1; j < size; ++j) {

      if (netflix[j].movieID < netflix[indexSmallest].movieID) 
      {
         
         indexSmallest = j;
      }
   }

  // Swap netflix[i] and netflix[indexSmallest]
  Movies temp = netflix[indexSmallest];
  netflix[indexSmallest] = netflix[i];
  netflix[i] = temp;
}


}
    
void sortTitle(Movies* netflix, int size) // function to sort the movies by title
{
    for (int i = 0; i < size - 1; ++i) {

   // Find index of smallest remaining element
   int indexSmallest = i;
   for (int j = i + 1; j < size; ++j) {

      if (netflix[j].title < netflix[indexSmallest].title) {
         indexSmallest = j;
      }
   }

  // Swap netflix[i] and netflix[indexSmallest]
  Movies temp = netflix[indexSmallest];
  netflix[indexSmallest] = netflix[i];
  netflix[i] = temp;
}



}

void outputArray(Movies* netflix, int size) // function to output elements of array
{
   for(int i = 0; i < size; i++) 
   {
       cout << netflix[i].movieID << " " << netflix[i].year << " '" <<  netflix[i].title << "'" << endl;
   }
}


int fillArray(Movies*& netflix, int& size) // function that fills the arrays 
{
   string fileName, firstLine; 
    int moviesNum;
    cout << "Movies filename> ";
    cin >> fileName;
    
    ifstream infile(fileName);

   if (!infile.good())
   {
       cout << "**Error: unable to open input file '" << fileName << "'." << endl;
       return 0;
   }
    
    
    getline(infile,firstLine);
    //cout << firstLine<< endl;
    
    infile >> firstLine;
    infile >> moviesNum;
    cout << "**Number_Movies: " << moviesNum<< endl;
    
    netflix = new Movies[moviesNum]; 
    //int id, year;
    string name;
    for(int i = 0; i < moviesNum; i++) {
        infile >> netflix[i].movieID;
        infile >> netflix[i].year;
        getline(infile, name);
        netflix[i].title = name.substr(1);
    }
 cout << "**First movie: " << netflix[0].movieID << " " << netflix[0].year << " '" <<  netflix[0].title << "'" << endl;
 cout << "**Last movie: " << netflix[moviesNum-1].movieID << " " << netflix[moviesNum-1].year << " '" <<  netflix[moviesNum-1].title << "'" << endl;  
 size = moviesNum;
 return 1; 
}


//
// main:
//
int main()
{
   int size;
   Movies* netflix;
   fillArray(netflix, size);
   
   cout << "**MOVIES BY ID**" << endl;
   sortID(netflix, size);
   outputArray(netflix, size);
   cout << "**MOVIES BY TITLE**" << endl;
   sortTitle(netflix, size);
   outputArray(netflix, size);
   cout << "**Done**" << endl;
   delete[] netflix;
   return 0;
}