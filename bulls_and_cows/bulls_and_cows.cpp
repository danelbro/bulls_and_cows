// bulls_and_cows
// v4.3 2018-03-22

#include "std_lib_facilities.h"

// GLOBAL CONSTANTS
// -----------------------------------------------------------------------------

const string bulls = "bulls";
const string cows = "cows";
const string prompt = "> ";
const string quit = "quit";
const string quit_text = "Gave up after ";
const string rules_check_text = "Would you like to read the rules?";
const string play_again_text = "Would you like to play again?";

// FUNCTIONS
// -----------------------------------------------------------------------------

void clean(runtime_error e)
{
	cerr << e.what();
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return;
}

int difficulty ()
{	
	const string easy = "easy";
	const string medium = "medium";
	const string hard = "hard";
	const string error_text = string("Enter ") 
		                + string(easy + '/' 
			        + medium + '/' 
			  	+ hard + string(": "));

	const unordered_map<string, int> difficulties = {
		{ easy, 6 },
		{ medium, 8 },
		{ hard, 10 }
	};

	cout << "\nChoose a difficulty:\n"
	     << easy << " - play with numbers from 1-6\n"
	     << medium << " - play with numbers from 1-8\n"
	     << hard << " - play with numbers from 0-9\n"
	     << prompt;

	string diff_label;
	while (true) {
		try {
			cin >> diff_label;			
			if (diff_label != easy && diff_label != medium && diff_label != hard)
				error(error_text);
			else break;
		}
		catch (runtime_error& e) {
			clean(e);
		}
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	cout << "\nDifficulty selected: " << diff_label << ".\n";
	return difficulties.at(diff_label);
}

bool check(string check_text)
// general yes/no test
{
	const char affirm = 'y';
	const char neg = 'n';
	const string error_text = string("Enter ") + affirm + '/' + neg + string(": ");

	char checker = 'x';
	cout << check_text << " [" << affirm << '/' << neg << "]\n";

	while (checker != affirm && checker != neg) {
		try {
		        if (!(cin >> checker))
			        error(error_text);
			switch (checker) {
			case affirm:
			        cin.ignore(numeric_limits<streamsize>::max(), '\n');
				return true;
			case neg:
			        cin.ignore(numeric_limits<streamsize>::max(), '\n');
				return false;
			default:
			        error(error_text);
			}
		}
		catch (runtime_error& e) {
			clean(e);
		}
	}
	error("unknown error!");
	return false;
}

string number_gen(string number, int top)
{
	srand(static_cast<unsigned int>(time(NULL)));
	vector<int> local_number(4);
	// find another way to do this
	const vector<char> numbers = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

	for (size_t i = 0; i < local_number.size(); ++i) {
	    	if (top < 9)
			local_number[i] = (rand() % top + 1);
	    	else if (top > 9)
			local_number[i] = (rand() % top);
	}

	for (size_t i = 0; i < local_number.size(); ++i)
		number[i] = numbers[local_number[i]];       // populates string with char digits
	                                                    // identical to local_number
	return number;
}

unordered_map<string, int> initialise(unordered_map<string, int> bulls_and_cows)
{
        bulls_and_cows[bulls] = 0;
        bulls_and_cows[cows] = 0;
	return bulls_and_cows;
}

bool is_number(string& s)
{
	return !s.empty() && find_if(s.begin(),
		s.end(), [](char c) { return !isdigit(c); }) == s.end();
}

string get_guess(string local, int guesses)
// accepts a string in the form "0000". Rejects wrong size and not all digits
{
	while (true) {
		try {
		        cout << '\n' << guesses << prompt;
			cin >> local;
			if (local == quit)
			        break;
			else if (local.size() != 4 || !is_number(local))
			        error("Guess must be 4 digits!\n");
			break;
		}
		catch (runtime_error& e) {
			clean(e);
		}
	}	
	return local;
}

unordered_map<string, int> compare(string guess, string goal, unordered_map<string, int> bulls_and_cows)
{
	const char seen = 'x';
  	const char used = 'u';
  
  	// work out bulls
  	for (size_t i = 0; i < guess.size(); ++i) {
    		if (guess[i] == goal[i]) {
      			++bulls_and_cows[bulls];
      			guess[i] = used;
      			goal[i] = seen;
		}
	}
  
  	// work out cows
  	for (size_t i = 0; i < guess.size(); ++i) {
    		if (guess[i] != goal[i]) {
      			for (size_t j = 0; j < goal.size(); ++j) {
				if (guess[i] == goal[j]) {
	  				++bulls_and_cows[cows];
	  				guess[i] = used;
	  				goal[j] = seen;
	  				break;
				}
			}
		}
	}
  	return bulls_and_cows;
}

void win(string number, int guesses)
{
	cout << "You win! My number was: "
		<< number << '\n'
		<< "You took " << guesses << " guesses.\n";
}

void give_up(string goal, int guesses)
{
	cout << quit_text << guesses - 1 << " guesses!\n"
		<< "My number was: " << goal << '\n';
	return;
}

void score(unordered_map<string, int> bulls_and_cows)
{
	cout << "[" << bulls_and_cows[bulls] << "] Bulls and [" << bulls_and_cows[cows] << "] Cows\n";
}

void rules()
{
	cout << "\nI will think of 4 digits. You have to guess\n"
		<< "each digit correctly and in the right place\n"
		<< "to win. If you guess a digit correctly in\n"
		<< "the right place, you get a Bull. If you guess\n"
		<< "a digit correctly but in the wrong place, you\n"
		<< "get a Cow. 4 Bulls wins! (Type \"quit\" to\n"
		<< "give up for the round.)\n";
	return;
}

void intro()
{
	cout << '\n'
		<< "        ==== B U L L S ====\n"
		<< "        ====== A N D ======\n"
		<< "        ===== C O W S =====\n"
		<< '\n';

	if (check(rules_check_text)) {
		rules();
		return;
	}
	else
		return;
}

void gameloop()
{
	bool play_again = true;
	unordered_map<string, int> bulls_and_cows = {
	        { bulls,  0},
	        { cows, 0 }
	};
	string goal = "    ";
	string guess;

	while (play_again) {
		int diff_number = difficulty();
		int guesses = 0;
		bulls_and_cows = initialise(bulls_and_cows);
		goal = number_gen(goal, diff_number);

		cout << "\nI am thinking of 4 digits...try to guess them!\n";

		while (bulls_and_cows[bulls] != 4) {
			bulls_and_cows = initialise(bulls_and_cows);
			++guesses;
			
			guess = get_guess(guess, guesses);
			if (guess == quit) {
			        give_up(goal, guesses);
				break;
			}

			bulls_and_cows = compare(guess, goal, bulls_and_cows);
			score(bulls_and_cows);
			
			if (bulls_and_cows[bulls] == 4)
				win(goal, guesses);
		}
		play_again = check(play_again_text);
	}
	return;
}

int main()
{
	try {
		intro();
		gameloop();
		return 0;
	}
	catch (exception& e) {
		cerr << "runtime error: " << e.what() << '\n';
		keep_window_open("~1");
		return 1;
	}
	catch (...) {
		cerr << "unknown error\n";
		keep_window_open("~2");
		return 2;
	}
}
