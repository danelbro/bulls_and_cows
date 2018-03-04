// game of bulls and cows
// v1.0 2018-03-03

#include "../../std_lib_facilities.h"

vector<int> number_gen(vector<int> goal)
{
	srand(time(NULL));
	for (int i = 0; i < goal.size(); ++i)
	{
		goal[i] = (rand() % 10);
		if (i >= 1)
		{
			for (int j = i; j >= 0; --j)
			{
				if (goal[i] == goal[j]) // removes repeated digits
				{
					goal[i] = (rand() % 10);
				}
			}
		}
	}
	return goal;
}

vector<int> initialise(vector<int> local_bulls_and_cows_1)
{
	for (int i = 0; i<local_bulls_and_cows_1.size(); ++i)
		local_bulls_and_cows_1[i] = 0;
	return local_bulls_and_cows_1;
}

vector<int> get_user_num(vector<int> empty_user_num)
// populates user_num vector
// elements of the vector must be integers and there cannot be any repeated digits
{
	for (int i = 0; i < empty_user_num.size(); ++i)
	{
		if (!(cin >> empty_user_num[i])) error("Need integers");
		if (i >= 1)
		{
			for (int j = i; j >= 0; --j)
			{
				if (empty_user_num[i] == empty_user_num[j]) // bars repeated digits
				{
					error("No repeated digits");
				}
			}
		} 
	}
	return empty_user_num;
}

vector<int> game_loop(vector<int> guess, vector<int> goal, vector<int> local_bulls_and_cows_2)
{
	for (int i = 0; i < guess.size(); ++i)
	{
		if (guess[i] == goal[i]) ++local_bulls_and_cows_2[0];
		else if (guess[i] != goal[i])
		{
			for (int j = 0; j < goal.size(); ++j)
			{
				if (guess[i] == goal[j])
				{
					++local_bulls_and_cows_2[1];
					break;
				}
			}
		}
	}
	return local_bulls_and_cows_2;
}

void win_text(vector<int> goal, int final_guesses)
{
	cout << "You win! My number was:\n";
	for (int i : goal)
		cout << i;
	cout << "\nYou took " << final_guesses << " guesses\n";
}

bool play_again_fun()
{
	string play_again_in = "";
	cout << "Play again? (y/n)\n";
	while (play_again_in != "y" && play_again_in != "n")
	{
		cin >> play_again_in;
		if (play_again_in == "n")
		{
			return false;
		}
		else if (play_again_in == "y")
		{
			return true;
		}
		else cout << "Please enter y/n\n";
	}
}

int main()
{
	try 
	{
		bool play_again = true;
		while (play_again)
		{
			vector<int> number(4);
			number = number_gen(number);
			cout << "I am thinking of a number. It has 4 digits, all different. Try to guess it...\n";
			vector<int> user_num(4);
			int guesses = 0;
			vector<int> bulls_and_cows(2);
			bulls_and_cows = initialise(bulls_and_cows);
			while (bulls_and_cows[0] != 4)
			{
				bulls_and_cows = initialise(bulls_and_cows);
				++guesses;
				user_num = get_user_num(user_num);
				bulls_and_cows = game_loop(user_num, number, bulls_and_cows);
				cout << "[" << bulls_and_cows[0] << "] Bulls and [" << bulls_and_cows[1] << "] Cows\n";
				if (bulls_and_cows[0] == 4)
					win_text(number, guesses);
			}
			play_again = play_again_fun();
		}
		keep_window_open();
		return 0;
	}
	catch (runtime_error& e)
	{
		cerr << "runtime error: " << e.what() << '\n';
		keep_window_open();
		return 1;
	}
	catch (...)
	{
		cerr << "unknown error\n";
		keep_window_open();
		return 2;
	}
}