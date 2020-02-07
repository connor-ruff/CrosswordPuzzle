#include<iostream>
#include<fstream>
using namespace std;
#include"cross.h"

int main(int argc, char *argv[]) {

	Cross cw;
	// Interactive Mode
	if (argc == 1) {

		
		string a; // Temp String Variable Read Into
		int count = 0; // Counter For Words
		cout << "Begin Entering Up To 20 Words." << endl;
		cout << "No Spaces, Max 15 Characters." << endl;

		while(count <=20) {
			
			getline(cin, a);
		
			// Check For End and Length of Word to Add
			if (a == ".")
				break;
			if (a.length() > 15) {
				cout << "Word Too Long. Not Added. ";
				cout << "You May Continue Adding" << endl;
				continue;
			}
			if (a.length() < 2) {
				cout << "Word Too Short. Not Added. ";
				cout << "You May Continue Adding." << endl;
				continue;
			}
	
			cw.addWord(a); // Add the Word
			++count;
		} // end of while loop
	}

	// If User Enters A File To Be Read
	else if ( (argc == 2) || (argc ==3)) {

		ifstream ifs;
		ifs.open(argv[1]);
		string a;
		int count =0;

		while (count <=20) {
			getline(ifs,a);
			
			if (a == ".")
				break;
			if (a.length() > 15) {
				cout << a << " Is Too Long. Not Added." << endl;
				continue;
			}
			if (a.length() < 2) {
				cout << a << " Is Too Short. Not Added." << endl;
				continue;
			}
			cw.addWord(a);
			++count;
		}
	}

	//Print Results To Screen
	if (argc == 1 || argc == 2) {

		cw.setLengths(); //Initiate Lengths Vector	
		cw.convertToUpper();//Convert Words To Capital
		cw.sizeSort(); //Sort In Increasing Order
		cw.placeFirst();// Put Down First Word
		cw.placeAll(); // Put Rest of Words In
		cw.createFinalBoards();// Finalize Boards
		cw.displaySol();// Display Solution Board
		cout  << endl << endl;
		cw.displayGame(); // Display Game Board
		cout << endl << endl;
		cw.scramble();
		cw.wasNotPlaced();
		cw.displayClues();
	}

	// Print Results To Output File
	else if (argc == 3) {
		
		
		
		cw.setLengths();
		cw.convertToUpper();
		cw.sizeSort();
		cw.placeFirst();
		cw.placeAll();
		cw.createFinalBoards();
		cw.scramble();
		cw.wasNotPlaced();

		// Display Methods Specifically For Ofstreams
		ofstream ofs;
		ofs.open(argv[2]);
		cw.displaySolOfs(ofs);
		cw.displayGameOfs(ofs);
		cw.displayCluesOfs(ofs);


	}
			
	

	
	


	return 0;
}

