// bulls_and_cows
// v3.0 2018-03-13

#include "std_lib_facilities.h"

// TEXT CONSTANTS
// -----------------------------------------------------------------------------

const string rules_check_text = "Would you like to read the rules?";
const string play_again_text = "Would you like to play again?";

// FUNCTIONS
// -----------------------------------------------------------------------------

bool check(string check_text)
// general [Y/n] test
{
	char checker = 'x';

	while (checker != 'Y' && checker != 'n') {
		cout << check_text << " [Y/n]\n";
		cin >> checker;
		switch (checker) {
		case 'Y':
			return true;
		case 'n':
			return false;
		default:
			continue;
		}
	}
}

string number_gen(string number)
{
	srand(static_cast<unsigned int>(time(NULL)));
	vector<int> local_number(4);
	// find another way to do this
	vector<char> numbers = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

	for (size_t i = 0; i < local_number.size(); ++i) {
		local_number[i] = (rand() % 10);
		// removes repeated digits
		// if (i >= 1) {
		//	for (size_t j = i - 1; j < local_number.size(); --j) {
		//		while (local_number[i] == local_number[j]) 
		//			local_number[i] = (rand() % 10);
		//	}
		// }
	}
	for (size_t i = 0; i < local_number.size(); ++i)
		number[i] = numbers[local_number[i]]; // populates string with char digits identical to local_number
	return number;
}

vector<int> initialise(vector<int> local)
{
	for (size_t i = 0; i < local.size(); ++i)
		local[i] = 0;
	return local;
}

bool is_number(string& s)
{
	return !s.empty() && find_if(s.begin(),
		s.end(), [](char c) { return !isdigit(c); }) == s.end();
}

string get_guess(string local)
// accepts a string in the form "0000". Rejects wrong size and not all digits
{
	cin >> local;
	if (local.size() != 4 || !is_number(local)) error("Guess must be 4 digits");
	//	for (size_t i = 1; i < local.size(); ++i) {
	//	for (size_t j = i - 1; j < local.size(); --j) {
	//		if (local[i] == local[j]) error("No repeated digits");
	//	}
	//}
	return local;
}

vector<int> compare(string guess, string goal, vector<int> result)
{
  // work out bulls
  for (size_t i = 0; i < guess.size(); ++i) {
    if (guess[i] == goal[i]) {
      ++result[0];
      goal[i] = 'x';
    }
  }
  //work out cows
  for (size_t i = 0; i < guess.size(); ++i) {
    if (guess[i] != goal[i]) {
      for (size_t j = 0; j < goal.size(); ++j) {
	if (guess[i] == goal[j]) {
	  ++result[1];
	  goal[j] = 'x';
	  break;
	}
      }
    }
  }
  return result;
}

void win(string number, int guesses)
{
	cout << "You win! My number was:\n"
		<< number
		<< "\nYou took " << guesses << " guesses\n";
}

void rules()
{
	cout << "I will think of 4 digits. You have to guess\n"
	     << "each digit correctly and in the right place\n"
	     << "to win. If you guess a digit correctly in\n"
	     << "the right place, you get a Bull. If you guess\n"
	     << "a digit correctly but in the wrong place, you\n"
	     << "get a Cow. 4 Bulls wins!\n";
	return;
}

void intro()
{
	bool print_rules = false;

	cout << '\n'
		<< "        ==== B U L L S ====\n"
		<< "        ====== A N D ======\n"
		<< "        ===== C O W S =====\n"
		<< '\n';

	print_rules = check(rules_check_text);
	if (print_rules) {
		rules();
	}
	else
		return;
	return;
}

void gameloop()
{
	bool play_again = true;
	vector<int> bulls_and_cows(2);
	string goal = "    ";
	string guess;

	while (play_again) {
		int guesses = 0;
		bulls_and_cows = initialise(bulls_and_cows);
		goal = number_gen(goal);

		cout << "\nI am thinking of 4 digits...try to guess them!\n";

		while (bulls_and_cows[0] != 4) {
			bulls_and_cows = initialise(bulls_and_cows);
			++guesses;
			guess = get_guess(guess);
			bulls_and_cows = compare(guess, goal, bulls_and_cows);
			cout << "[" << bulls_and_cows[0] << "] Bulls and [" << bulls_and_cows[1] << "] Cows\n";
			if (bulls_and_cows[0] == 4)
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
		keep_window_open("~~");
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
