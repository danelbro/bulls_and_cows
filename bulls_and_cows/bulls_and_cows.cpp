#include "../../std_lib_facilities.h"

int main()
{
	try {
		int bulls = 0;
		int cows = 0;
		int guesses = 0;
		vector<int> number = { 1, 2, 3, 4 };
		cout << "I am thinking of a four digit number with no repeated digits. Try to guess it...\n";
		vector<int> user_num(4);
		while (bulls != 4)
		{
			bulls = 0;
			cows = 0;
			++guesses;
			for (int i = 0; i < user_num.size(); ++i)
			{
				if (!(cin >> user_num[i])) error("Need integers");
				if (i >= 1 && user_num[i] == user_num[i - 1]) error("No repeated digits");
			}
			for (int i = 0; i < user_num.size(); ++i)
			{
				if (user_num[i] == number[i]) ++bulls;
				else if (user_num[i] != number[i])
				{
					for (int j = 0; j < number.size(); ++j)
					{
						if (user_num[i] == number[j])
						{
							++cows;
							break;
						}
					}
				}
			}
			cout << "[" << bulls << "] Bulls and [" << cows << "] Cows\n";
			if (bulls == 4)
			{
				cout << "You win! My number was:\n";
				for (int i : number)
					cout << i;
				cout << "\nYou took " << guesses << " guesses\n";

			}
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