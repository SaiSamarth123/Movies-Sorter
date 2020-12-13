// 
// Completed version of Project 3 written by
//   Date: October 10th 2020
//   Author: Sai Samarth, U. of Illinois Chicago, Fall 2020
//   Description: Stores netflix movies and their reviews into an array and then lets the user access them through various commands.


#include <iostream>
#include <fstream>
#include <string>
#include <cctype>  // isspace


using namespace std;

struct Movies // struct that contains both the movies and their reviews
{
   string title;
   int movieID = 0;
   int year = 0;
   int numReviews = 0;
   int numStars = 0;
   double avgRating = 0;
};

//
// popularMovie
//
// Given a struct filled with movies and reviews and its size
// the function sorts the structs based on increasing average rating
//
void popularMovie(Movies* netflix, int size) { 
    for (int i = 0; i < size-1; ++i) {
        int popular = i;
        for (int j = i + 1; j < size; ++j) {
            if (netflix[j].avgRating < netflix[popular].avgRating) 
            {
                popular = j;
            }
        }
        Movies temp = netflix[popular];
        netflix[popular] = netflix[i];
        netflix[i] = temp;
    }
}

//
// sortID
// 
// Given a struct filled with movies, reviews and its size
// the function sorts the structs based on increasing ID
//
void sortID(Movies* netflix, int size) { 
    for (int i = 0; i < size - 1; ++i) {
        // assigning the index of the smallest element to indexSmallest
        int indexSmallest = i;
        for (int j = i + 1; j < size; ++j) {
            if (netflix[j].movieID < netflix[indexSmallest].movieID) // compares two elements to find the smaller movieID
            {
                indexSmallest = j;
            }
        }
        // swap netflix[indexSmallest] and netflix[i] using temp
        Movies temp = netflix[indexSmallest];
        netflix[indexSmallest] = netflix[i];
        netflix[i] = temp;
    }
}

//
// sortTitle
//
// Given a struct filled with movies and reviews and its size
// the function sorts the struct alphabetically based on movie titles
//
void sortTitle(Movies* netflix, int size) { 
    for (int i = 0; i < size - 1; ++i) {
        // assigning the index of the smallest element to indexSmallest
        int indexSmallest = i;
        for (int j = i + 1; j < size; ++j) {
            if (netflix[j].title < netflix[indexSmallest].title) { // compares two elements to find the title that comes alphabetically first
                indexSmallest = j;
            }
        }
        // swap netflix[indexSmallest] and netflix[i] using temp
        Movies temp = netflix[indexSmallest];
        netflix[indexSmallest] = netflix[i];
        netflix[i] = temp;
    }
}

//
// findID
//
// Given a struct filled with movies and reviews and its size and an user entered id
// the function finds a movie using the id
//
void findID(Movies* netflix, int id, int size) { 
    sortID(netflix, size); // sorts the struct by ID
    bool b = true;
    for(int i = 0; i < size; i++) { // loop through the struct
        if(netflix[i].movieID == id) { // compares the movie ID to the user entered id
            // prints out the movie if it is found
            cout << netflix[i].movieID << " " << netflix[i].year << " '" <<  netflix[i].title << "' " << netflix[i].numReviews << " reviews " << netflix[i].avgRating << " avg rating" << endl;
            b = false;
        }
    }
    // prints out movie not found if the movie is not in the struct
    if(b) {
        cout << "Movie not found..." << endl;
    }
    cout << endl;
}

//
// findTitle
//
// Given a struct filled with movies and reviews and its size and an user entered word
// the function finds a movie using its title
//
void findTitle(Movies* netflix, string word, int size) { 
    sortTitle(netflix, size); // sorts the struct by title
    bool b = true;
    for(int i = 0; i < size; i++) { // loop through the struct
        if(netflix[i].title.find(word) != string::npos) { // compares the title to the user entered word and checks if the word is present in the title
            // prints out the movie if it is found
            cout << netflix[i].movieID << " " << netflix[i].year << " '" <<  netflix[i].title << "' " << netflix[i].numReviews << " reviews " << netflix[i].avgRating << " avg rating" << endl;
            b = false;
        }
    }
    // prints out movie not found if the movie is not in the struct
    if(b) {
        cout << "Movie not found..." << endl;
    }
    cout << endl;
}

//
// outputArray
//
// Given a struct filled with movies and reviews and its size
// the function outputs all the elements of the struct
//
void outputArray(Movies* netflix, int size) { 
    for(int i = 0; i < size; i++) {
        cout << netflix[i].movieID << " " << netflix[i].year << " '" <<  netflix[i].title << "' " << netflix[i].numReviews << " reviews " << netflix[i].avgRating << " avg rating" << endl;
    }
}

//
// fillArray
//
// Given a struct filled with movies and reviews and its size
// the function fills the array with movies and reviews
//
int fillArray(Movies*& netflix, int& size) { 
    string fileName, firstLine, reviewFile, reviewLine; 
    int moviesNum, reviewsNum;
    
    cout << "Movies filename> ";
    cin >> fileName;
    
    ifstream infile(fileName);
    if (!infile.good()) // checks if the movies file is good
    {
        cout << "**Error: unable to open input file '" << fileName << "'." << endl;
        return 0;
    }
    
    // puts the contents of the movies file into the struct if the movie file exists
    getline(infile, firstLine);
    infile >> firstLine;
    infile >> moviesNum;
    netflix = new Movies[moviesNum];
    string name;
    for(int i = 0; i < moviesNum; i++) {
        infile >> netflix[i].movieID;
        infile >> netflix[i].year;
        getline(infile, name);
        netflix[i].title = name.substr(1);
    }

cout << "Reviews filename> ";
cin >> reviewFile; 
ifstream review(reviewFile);
int stars, id, revID;
if (!review.good()){ // checks if the reviews file is good
    cout << "**Error: unable to open input file '" << reviewFile << "'." << endl;
    return 0;
}
    // puts the contents of the reviews file into the struct if the file exists
    getline(review, reviewLine);
    review >> reviewLine;
    review >> reviewsNum;
    for(int i = 0; i < reviewsNum; i++) {
        review >> revID;
        review >> id;
        review >> stars;
        for(int j = 0; j < moviesNum; j++) { 
            if(id == netflix[j].movieID) { // adds the reviews to the movie if the ids match
                netflix[j].numStars = netflix[j].numStars + stars; 
                netflix[j].numReviews++;
            }
        }
    }
    for(int i = 0; i < moviesNum; i++) { // for loop that computes the average rating of each movie
        if (netflix[i].numReviews != 0) {
            netflix[i].avgRating = double(netflix[i].numStars)/netflix[i].numReviews;
        } else {
            netflix[i].avgRating = 0;
        }
    }

cout << "**Number_Movies: " << moviesNum<< endl; 
cout << "**Number_Reviews: " << reviewsNum<< endl;

size = moviesNum; // assigns the number of movies to the struct size
return 1; // returns 1 if the struct is filled
}


//
// main:
//
int main() {
    int size;
    Movies* netflix;
    string command;
    int r = fillArray(netflix,size); // calls the fillarray function to fill the struct
    if(r == 0) { // main returns 0 if the struct is not filled
        return 0;
    } 
    
    int com = 1;
    char c;
    int num = 0;
    
    while(com == 1) { // while loop keeps looping until the user quits
        cout << "Enter command (f id, f title, l, mp, q): ";
        cin >> command;
        if (command == "f") {// checks if the command is find
            cin >> command;
            bool b = false;
            for(size_t i = 0; i < command.length(); i++) { // loop to check if everything after the command is a number
                c = command.at(i);
                if(isdigit(c)) {
                    b = true;
                } else {
                    b = false;
                }
            }
            if (b){ // if the user inputs a number then the string is converted and the the findID function is called
                num = stoi(command);
                findID(netflix, num, size);
            } else { // else the findTitle function is called
                findTitle(netflix, command, size);
            }
        } else if (command == "l") { // checks for the command l which prints out the movies by id and title
            cout << "**MOVIES BY ID**" << endl;
            sortID(netflix, size);
            outputArray(netflix, size);
            cout << "**MOVIES BY TITLE**" << endl;
            sortTitle(netflix, size);
            outputArray(netflix, size);
            cout << endl;
        } else if (command == "mp") { // checks for the command mp which returns the movie with the best average review
            popularMovie(netflix, size);
            cout << netflix[size-1].movieID << " " << netflix[size-1].year << " '" <<  netflix[size-1].title << "' " << netflix[size-1].numReviews << " reviews " << netflix[size-1].avgRating << " avg rating" << endl;
            cout << endl;
        } else { // else it quits the loop
            com = 0;
        }
    }
    
    cout << "**Done**" << endl;
    delete[] netflix;
    return 0;
}