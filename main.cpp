#include "header.h"
#include "game.h"
using namespace std;

int main()
{
	Game game;

	int option = 0;
	cout << "Longaga" << endl;
	do
	{
		cout << "Select an option " << endl;

		cout << "1. New game" << endl;
		cout << "2. Load game" << endl;
		cin >> option;

		//made with google gemini
		if (cin.fail()) {
			// 1. Clear the error flag
			cin.clear();

			// 2. Ignore everything in the buffer until the next newline
			// This "throws away" the bad characters (like the 'a')
			cin.ignore(1000, '\n');

			cout << "Invalid input!" << endl;
			continue; // Restart the loop
		}
	} while (option < 1 || option > 2);

	game.startGame(option);


}