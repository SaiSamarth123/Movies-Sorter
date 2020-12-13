// 
// Completed version of Project 3 written by
//   Author: Sai Samarth, U. of Illinois Chicago, Fall 2020
//   Description: Stores netflix movies and their reviews into an array and then sorts them based on ID and title.

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>  // isspace


using namespace std;

struct Movies // struct that contains all the information about the movies
{
   string title;
   int movieID = 0;
   int year = 0;
   int numReviews = 0;
   int numStars = 0;
   double avgRating = 0;
};

void sortID(Movies* netflix, int size) // function that sorts the movies based on their ID
{
    
   for (int i = 0; i < size - 1; ++i) { 

   // find index of smallest remaining element
   int indexSmallest = i;
   for (int j = i + 1; j < size; ++j) {

      if (netflix[j].movieID < netflix[indexSmallest].movieID) 
      {
         
         indexSmallest = j;
      }
   }

   // swap movies[i] and movies[indexSmallest]
  Movies temp = netflix[indexSmallest];
  netflix[indexSmallest] = netflix[i];
  netflix[i] = temp;
   }
}
   

void sortTitle(Movies* netflix, int size) // function to sort movies by their title
{
    for (int i = 0; i < size - 1; ++i) {

   // Find index of smallest remaining element
   int indexSmallest = i;
   for (int j = i + 1; j < size; ++j) {

      if (netflix[j].title < netflix[indexSmallest].title) {
         indexSmallest = j;
      }
   }

  // swap movies[i] and movies[indexSmallest]
  Movies temp = netflix[indexSmallest];
  netflix[indexSmallest] = netflix[i];
  netflix[i] = temp;
    }
}

void outputArray(Movies* netflix, int size) // function that outputs the contents of the movies array
{
   for(int i = 0; i < size; i++) 
   {
       cout << netflix[i].movieID << " " << netflix[i].year << " '" <<  netflix[i].title << "' " << netflix[i].numReviews << " reviews " << netflix[i].avgRating << " avg rating" << endl;
   }
}


int fillArray(Movies*& netflix, int& size) // function that fills that movies array
{
    string fileName, firstLine, reviewFile, reviewLine; 
    int moviesNum, reviewsNum;
    cout << "Movies filename> ";
    cin >> fileName;
    
   ifstream infile(fileName);

   if (!infile.good())
   {
       cout << "**Error: unable to open input file '" << fileName << "'." << endl;
       return 0;
   }
    cout << "Reviews filename> ";
    cin >> reviewFile; 
    
   ifstream review(reviewFile);
    
   if (!review.good())
   {
       cout << "**Error: unable to open input file '" << reviewFile << "'." << endl;
       return 0;
   }
    
    
    getline(infile, firstLine);
    getline(review, reviewLine);
    //cout << firstLine<< endl;
    
    infile >> firstLine;
    infile >> moviesNum;
    review >> reviewLine;
    review >> reviewsNum;
    
    cout << "**Number_Movies: " << moviesNum<< endl;
    cout << "**Number_Reviews: " << reviewsNum<< endl;
    
    netflix = new Movies[moviesNum];
    
    
    string name;
    for(int i = 0; i < moviesNum; i++) { // for loop to loop through the array and add movies
        infile >> netflix[i].movieID;
        infile >> netflix[i].year;
        getline(infile, name);
        netflix[i].title = name.substr(1);
        }
    
    int stars, id, revID;
    
    for(int i = 0; i < reviewsNum; i++) // for loop to loop through the review file
    {
        review >> revID;
        review >> id;
        review >> stars;
        for(int j = 0; j < moviesNum; j++) // for loop to loop through the movies array and add reviews
        {
            if(id == netflix[j].movieID) {
                netflix[j].numStars = netflix[j].numStars + stars;
                netflix[j].numReviews++;
            }
        }
     }
    
    for(int i = 0; i < moviesNum; i++) // for loop to compute average
    {
       if (netflix[i].numReviews != 0) // check if number of reviews is 0 and compute average
       {
           netflix[i].avgRating = double(netflix[i].numStars)/netflix[i].numReviews;
       }
        else {
            netflix[i].avgRating = 0; // average is 0 if there are no reviews
        }
    }
 
    //cout << "**First movie: " << netflix[0].movieID << " " << netflix[0].year << " '" <<  netflix[0].title << "'" << endl;
 //cout << "**Last movie: " << netflix[moviesNum-1].movieID << " " << netflix[moviesNum-1].year << " '" <<  netflix[moviesNum-1].title << "'" << endl;  
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
   
   if(fillArray(netflix, size) == 0)// delete the array if the .txt files are empty
   {
       //cout << "**Done**" << endl;
       delete[] netflix;
       return 0;
   }
   
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