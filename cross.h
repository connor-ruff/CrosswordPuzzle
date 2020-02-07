#include<iostream>
#include<string>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<iomanip>
using namespace std;



struct Word {
	
	string word;
	string scrambled;
	int row;
	int col;
	string orientation;

};

class Cross {

	public:
	Cross();
	int getNumWords();
	void addWord(string);
	void displaySol();
	void displayGame();
	void displayClues();
	void setLengths();
	void displayWords();
	void convertToUpper();
	void sizeSort();
	void placeFirst();
	void placeAll();
	bool checkIfFitVert(int, int, string,int);
	bool checkIfFitVert2(int, int, string, int);	
	void placeItVert(int,int,string,int);
	bool checkIfFitHoriz(int,int,string,int);
	bool checkIfFitHoriz2(int,int,string,int);
	void placeItHoriz(int,int,string,int);
	void createFinalBoards();
	void scramble();
	void wasNotPlaced();

	ostream& displaySolOfs(ostream&);
	ostream& displayGameOfs(ostream&);
	ostream& displayCluesOfs(ostream&);

	private:
	char sboard[17][17];
	char gboard[17][17];
	vector<string> words;
	vector<int> lengths;
	vector<Word> onboard;
	vector<string> notPlaced;


};

