#include <stdio.h> 
#include <stdlib.h>
#include <iostream>
#include <ostream> 

using namespace std;

int TT, NNtotal, NN;
int NNarray[11] = {
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  -1
};
int segmentSize = 15;
// int NNarray[8]={15,15,15,15,15,15,10,-1};
// int NNarray[8]={4,4,-1};
int segment;
int guesses[30], scores[30], numGuesses = 0;
int answers[20];
int counter = 0, found = 0;
char guessString[202];

int scoreCompute(int aa, int bb) {
	int ii;
	int plusses = 0;

	for (ii = 0; ii < NN; ii++) {
		if ((aa % 2) == (bb % 2))
			plusses++;
		aa >>= 1;
		bb >>= 1;
	}

	return plusses;
}

int consistent(int counter) {
	int ii;

	for (ii = 0; ii < numGuesses; ii++) {
		if (scoreCompute(counter, guesses[ii]) != scores[ii]) {
			return 0;
		}
	}

	return 1;
}

int printGuess(int is0or1, int guess) {
	int ii, jj, ss, NNseg;

	guessString[2 * NNtotal] = '\0';
	ss = 0;
	ii = 0;
	while (ii < NNtotal) {
		NNseg = NNtotal - ii;
		NNseg = (segmentSize < NNseg) ? segmentSize : NNseg;
		if (ss != segment) {
			for (jj = 2 * NNseg - 1; jj >= 0;) {
				guessString[2 * ii + jj--] = is0or1 + '0';
				guessString[2 * ii + jj--] = ' ';
			}
		}
		else {
			for (jj = 2 * NNseg - 1; jj >= 0;) {
				guessString[2 * ii + jj--] = (guess % 2) + '0';
				guessString[2 * ii + jj--] = ' ';
				guess >>= 1;
			}
		}
		ii += NNseg;
		ss++;
	}

	//printf("Q%s\n", guessString);
	cout << "Q" << guessString << "\n" << flush;

	return 1;
}

int printAnswer() {
	int ii, jj, ss, NNseg, guess;

	guessString[2 * NNtotal] = '\0';
	ss = 0;
	ii = 0;
	while (ii < NNtotal) {
		NNseg = NNtotal - ii;
		NNseg = (segmentSize < NNseg) ? segmentSize : NNseg;
		guess = answers[ss++];
		for (jj = 2 * NNseg - 1; jj >= 0;) {
			guessString[2 * ii + jj--] = (guess % 2) + '0';
			guessString[2 * ii + jj--] = ' ';
			guess >>= 1;
		}
		ii += NNseg;
	}

	//printf("A%s\n", guessString);
	cout << "A" << guessString << "\n" << flush;
	
	return 1;
}

void shapiro() {
	while (1) {
		if (consistent(counter)) {
			return;
		}
		else {
			counter++;
			if (counter >= (1 << NN)) {
				counter = -1;
				return;
			}
		}
	}
}

int main() {
	int score, baseScore, delta;
	int counterSave;
	int tt, ii;

	scanf("%d", &TT);
	
	for (tt = 0; tt < TT; tt++) {

		scanf("%d", &NNtotal);
		printGuess(0, 0);
		scanf("%d", &baseScore);

		segment = 0;
		ii = 0;
		while (ii < NNtotal) {

			NN = NNtotal - ii;
			NN = (segmentSize < NN) ? segmentSize : NN;
			counter = 0;
			numGuesses = 0;
			printGuess(1, 0);

			scanf("%d", &score);
			delta = (score - baseScore - NN + NNtotal) / 2;
			score -= delta;
			guesses[numGuesses] = 0;
			numGuesses++;
			scores[numGuesses - 1] = score;

			while (1) {
				shapiro();
				if (counter == -1) {
					cout << "CANNOT FIND" << "\n"
					//printf("cannot find\n");
				}
				counterSave = counter;

				counter++;
				shapiro();
				if (counter == -1) {
					break;
				}

				printGuess(1, counterSave);
				
				// printGuess(1, counter);

				scanf("%d", &score);
				score -= delta;
				guesses[numGuesses] = counterSave;
				numGuesses++;
				scores[numGuesses - 1] = score;

				if (score == NN) {
					break;
				}
			}
			answers[segment++] = counterSave;
			ii += NN;
		}

		printAnswer();
		
	}
}