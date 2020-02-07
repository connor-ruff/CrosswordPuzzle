#include<iostream>
using namespace std;
#include"cross.h"

Cross::Cross() {
	//Initilize Empty Boards
	
	// Top Border
	for (int j=0; j < 17; ++j) 
		sboard[0][j] = '-';
	
	
	// Bottom Border
	for (int j=0; j <17; ++j)
		sboard[16][j] = '-';
	
	// Left Border
	for (int i=1; i < 16; ++i)
		sboard[i][0] = '|';
	
	// Right Border
	for (int i=1; i <16; ++i)
		sboard[i][16] = '|';

	// Fill In Rest With Blanks
	for (int i =1; i < 16; ++i) {
		for (int j=1; j < 16; ++j){
			sboard[i][j] = ' ' ;
		}
	}
	//Put +'s on corners
	sboard[0][0] = '+';
	sboard[0][16] = '+';
	sboard[16][0] = '+';
	sboard[16][16] = '+';

	// Create Empty Game Board 
	for (int i =0; i < 17; ++i)
		for (int j=0; j <17; ++j)
			gboard[i][j] = sboard[i][j];
}

// Display The CrossWord
void Cross::displaySol() {

	cout << "Solution: " << endl;
	for (int i=0; i<17; ++i){
		for (int j=0; j<17; ++j){
			cout << sboard[i][j];
		}
		cout << endl;
	}

}

void Cross::displayGame() {

	cout << "Puzzle: " << endl;
	for (int i=0; i <17; ++i) {
		for (int j =0; j<17; ++j) {
			cout << gboard[i][j];
		}
		cout << endl;
	}
}

int Cross::getNumWords(){
	int size = words.size();
	return size; 
}

void Cross::addWord(string a) {
	words.push_back(a);
}

void Cross::setLengths() {
	int size = words.size();
	for (int i=0; i < size; ++i) {
		int l = words.at(i).size();
		lengths.push_back(l);
	}
}
// Displays Words and Sizes (Used in De-Bugging Only)
void Cross::displayWords() {

	int size = words.size();
	for(int i=0; i < size; ++i)
			cout << words.at(i) << ": " << lengths.at(i) << endl;
}

// Converts All Words to Capital Letter
void Cross::convertToUpper() {

	char temp;
	for(int i=0; i < words.size(); ++i){
		for(int j=0; j < words.at(i).length(); ++j){
		temp = words.at(i).at(j);
		temp = toupper(temp);
		words.at(i).at(j) = temp;
		}
	}
}

// Sort the Vectors Containing Words and Their Lengths
void Cross::sizeSort(){

	int size = words.size();
	string temp;
	int temp2;
	for(int i=0; i < words.size(); ++i) {
		for(int j=0; j < size-1; ++j) {
			if (words.at(j).length() < words.at(j+1).length()) {
				temp = words.at(j);
				temp2 = lengths.at(j);
				words.at(j) = words.at(j+1);
				lengths.at(j) = lengths.at(j+1);
				words.at(j+1) = temp;
				lengths.at(j+1) = temp2;

			}
		}
	}

}

// Places First Word In The Center
void Cross::placeFirst() {

	Word temp;
	temp.word = words.at(0);
	temp.row = 7;
	temp.orientation = "ACROSS";

	// Ensures First Is Placed Horizontally In Middle of Board
	int position =( 15- words.at(0).length() ) / 2 + 1;
	temp.col = position;

	for (int i = 0; i < words.at(0).length(); ++i){
		sboard[7][position] = words.at(0).at(i) ;
		++position;
	}
	
	onboard.push_back(temp);
}

void Cross::placeAll(){

Word temp;
// Looop through each word
for(int w = 1; w < words.size(); ++w) {
	bool fitV = false;
	bool placed = false;
	bool fitV2 = false;
	bool fitH = false;
	bool fitH2 = false;
	// Loop Through Letters of Given Word
	for(int j=0; j < words.at(w).length(); ++j) {
		if (placed)
			break;
		// Loop through Board
		for(int row=1; row < 16; ++row) {
			if (placed)
				break;
			for (int col=1; col < 16; ++col) {
				if (placed)
					break;
				// Check If Current Letter Matches A Letter On Board
				if (sboard[row][col] == words.at(w).at(j)) {
					fitV =checkIfFitVert(row,col,words.at(w), j);// Pass coords,word,and pos of match
					fitV2 = checkIfFitVert2(row,col,words.at(w),j);
					fitH = checkIfFitHoriz(row,col,words.at(w), j);
					fitH2 = checkIfFitHoriz2(row,col,words.at(w),j);
					if (fitV2 && fitV){ // Places Word Vertically If Possible
						placeItVert(row,col,words.at(w),j);
						temp.word = words.at(w);
						temp.row = row - j;
						temp.col = col;
						temp.orientation = "DOWN" ;
						onboard.push_back(temp);
						placed = true;
					}
					else if (fitH && fitH2) { // Places Word Horizontally If Possible
						placeItHoriz(row,col,words.at(w),j);
						temp.word = words.at(w);
						temp.row = row;
						temp.col = col - j;
						temp.orientation = "ACROSS";
						onboard.push_back(temp);
						placed = true;
					}
					
				
				}
	    	}
	   }
	}
}

}

// This Checks If There Is Enough Vertical Room To Place The Word
bool Cross::checkIfFitVert(int row, int col, string word,int loc) {
	
	int sz = word.size();
	int numAbove = loc;
	int numBelow = sz - numAbove - 1;

	//Initial Check If It Is In Range of Board
	if ( (row + numBelow > 15) || ( row - numAbove < 1) )
		return false;

	// Check If It Fits Above 
	int countAbove=0;
	for(int i = 1; i <= numAbove+1; ++i) {
		if ((sboard[row-i][col] == ' ') || (sboard[row-i][col]== '-')) {
			++countAbove;
		}
	}
	bool fitsAbove;
	if (countAbove == numAbove+1)
		fitsAbove = true;
	else 
		fitsAbove = false;
	
	// Check If It Fits Below
	
	int countBelow=0;
	for(int i =1; i <= numBelow+1; ++i) {
		if( (sboard[row+i][col] == ' ')||(sboard[row+i][col] == '-')) {
			++countBelow;
		}
	}
	bool fitsBelow;
	if (countBelow == numBelow+1) 
		fitsBelow = true;
	else
		fitsBelow = false;

	
	// Final Return
	if (fitsAbove && fitsBelow)
		return true;
	else
		return false;

}

// Places the Word Vertically On The Board
void Cross::placeItVert(int row, int col, string word, int loc) {

	int sz = word.size();
	int startRow = row - loc;
	int currRow = startRow;
	for (int i =0; i < sz; ++i) {
		sboard[currRow][col] = word.at(i);
		currRow++ ;
	}
}

// This Checks if the Spaces To Right and Left of Vertical Word Are Open
bool Cross::checkIfFitVert2(int row, int col, string word, int loc) {

	int sz = word.size();
	int numAbove = loc;
	int numBelow = sz - numAbove - 1;

	// Check Above Portion
	int aboveCount=0;
	for (int i =1; i <= numAbove; ++i)
		if ( ((sboard[row-i][col+1] == ' ') || (sboard[row-i][col+1] == '|')) && 
			 ((sboard[row-i][col-1] == ' ') || (sboard[row-i][col-1] == '|'))   )
			++aboveCount;

	// Check Below Portion
	
	int belowCount=0;
	for (int i=1; i <= numBelow; ++i)
		if ( ((sboard[row+i][col+1] == ' ') || (sboard[row+i][col+1] == '|')) && 
			 ((sboard[row+i][col-1] == ' ') || (sboard[row+i][col-1] == '|'))   )
			++belowCount;

	if ((aboveCount == numAbove)&&(belowCount == numBelow))
		return true;
	else
		return false;

}

bool Cross::checkIfFitHoriz(int row, int col, string word, int loc) {

	int sz = word.size();
	int	numLeft = sz - loc;
	int numRight = sz - numLeft - 1;

	// Check If Fits Within Bounds of Board
	if ( ((col+numRight) > 15)|| ((col-numLeft<1) ) )
		return false;
	
	// Check If It Fits To The Right
	int rightCount=0;
	for(int i =1; i <= numRight+1; ++i){
		if ( (sboard[row][col+i] == ' ')||(sboard[row][col+i]=='|')) 
			++rightCount;			
	}
	
	bool fitsRight;
	if (rightCount == numRight +1)
		fitsRight = true;
	else
		fitsRight = false;
	
	// Check If It Fits To The Left
	int leftCount = 0;
	for (int i =1; i <= numLeft+1; ++i) {
		if ( (sboard[row][col-i] == ' ') || (sboard[row][col=i]=='|') )
			++leftCount;
	}

	bool fitsLeft;
	if (leftCount == numLeft +1)
		fitsLeft = true;
	else
		fitsLeft = false;
	
	// Final Return
	if (fitsLeft && fitsRight ){
		return true;}
	else{
		return false;}


	
}

bool Cross::checkIfFitHoriz2(int row, int col, string word, int loc) {
	
	int sz = word.size();
	int numLeft = loc;
	int numRight = sz - numLeft - 1;

	// Check If Left Portion Is Good
	int leftCount=0;
	for (int i =1; i <= numLeft; ++i)
		if ( ((sboard[row+1][col-i] == ' ') || (sboard[row+1][col-i] == '-')) && 
			 ((sboard[row-1][col-i] == ' ') || (sboard[row-1][col-i] == '-'))   )
			++leftCount;

	// Check If Right Portion Is Good
	int rightCount=0;
	for (int i =1; i <= numRight; ++i)
		if ( ((sboard[row+1][col+i] == ' ') || (sboard[row+1][col+i] == '-')) && 
			 ((sboard[row-1][col+i] == ' ') || (sboard[row-1][col+i] == '-'))   )
			++rightCount;

	// Final Return
	if ((numLeft == leftCount)&&(numRight == rightCount)){ 
		return true;}
	else{
		return false;}
}


void Cross::placeItHoriz(int row, int col, string word, int loc) {

	int sz = word.size();
	int startCol = col - loc;
	int currCol = startCol;
	for (int i =0; i < sz; ++i) {
		sboard[row][currCol] = word.at(i);
		currCol++ ;
	}
}

void Cross::createFinalBoards() {
	
	// Add .'s to Solution Board
	for (int i =1; i < 16; ++i){
		for (int j=1; j < 16; ++j) {
			if (sboard[i][j] == ' ') {
				sboard[i][j] = '.';
			}
		}
	}
				
	// Create Game Game Board
	for (int i =1; i < 16; ++i) {
		for (int j=1; j < 16; ++j){
			if (sboard[i][j] == '.')
				gboard[i][j] = '#';
			else
				gboard[i][j] = ' ';
		}
	} 
			

}

void Cross::scramble() {
	srand(time(0));
	char tempc;
	string tempw;
	// Loop through each word on the board
	for(int i=0; i < onboard.size(); ++i){
		int len = onboard.at(i).word.length();
		tempw = onboard.at(i).word;
		for(int j= len; j >0; --j) {
			int r = rand() % len;
			tempc = tempw.at(j-1);
			tempw.at(j-1) = tempw.at(r);
			tempw.at(r) = tempc;
		}
		onboard.at(i).scrambled = tempw;
	}
		
		
}


	
void Cross::displayClues() {

	if (notPlaced.size() > 0) {
		cout << "The Following Words Could Not Be Placed:" << endl;
		for(int i=0; i < notPlaced.size(); ++i)
			cout << notPlaced.at(i) << endl ;
		cout << endl;
	}

	cout << "Clues: " << endl << endl;
	for (int i = 0; i < onboard.size(); ++i){

	cout << setw(5) << left << "Row:" ;
	cout << setw(2) << right << onboard.at(i).row ;
	cout << "  ";
	cout << setw(8) << left << "Column:" ;
	cout << setw(2) << right << onboard.at(i).col;
	cout << "  ";
	cout << setw(13) << left << "Orientation:" ;
	cout << setw(8) << left << onboard.at(i).orientation;
	cout << setw(11) << left << "Scrambled:";
	cout << onboard.at(i).scrambled;
	cout << endl;
	}

}

// Make Function To Show What Could Not Be Placed
void Cross::wasNotPlaced() {

	bool found= false;
	
	for(int i=0; i < words.size(); ++i) {
		found = false;
		for (int j=0; j < onboard.size(); ++j) {
			if ( onboard.at(j).word == words.at(i))
				found = true;
		}
			if (!found)
				notPlaced.push_back(words.at(i));
	}


}


ostream& Cross::displaySolOfs(ostream &ofs) {


	ofs << "Solution: " << endl;
	for (int i=0; i<17; ++i){
		for (int j=0; j<17; ++j){
			ofs << sboard[i][j];
		}
		ofs << endl;
	}

}

ostream& Cross::displayGameOfs(ostream &ofs) {


	ofs << "Puzzle: " << endl;
	for (int i=0; i <17; ++i) {
		for (int j =0; j<17; ++j) {
			ofs << gboard[i][j];
		}
		ofs << endl;
	}
}

ostream& Cross::displayCluesOfs(ostream &ofs) {


	if (notPlaced.size() > 0) {
		ofs << "The Following Words Could Not Be Placed:" << endl;
		for(int i=0; i < notPlaced.size(); ++i)
			ofs << notPlaced.at(i) << endl ;
		ofs << endl;
	}

	ofs << "Clues: " << endl << endl;
	for (int i = 0; i < onboard.size(); ++i){

	ofs << setw(5) << left << "Row:" ;
	ofs << setw(2) << right << onboard.at(i).row ;
	ofs << "  ";
	ofs << setw(8) << left << "Column:" ;
	ofs << setw(2) << right << onboard.at(i).col;
	ofs << "  ";
	ofs << setw(13) << left << "Orientation:" ;
	ofs << setw(8) << left << onboard.at(i).orientation;
	ofs << setw(11) << left << "Scrambled:";
	ofs << onboard.at(i).scrambled;
	ofs << endl;
	}

}
