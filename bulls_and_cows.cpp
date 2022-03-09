// bulls_and_cows
// v5.0 2022-03-09

#include <algorithm>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

using std::string;
using std::vector;
using std::runtime_error;
using std::cin; using std::cout; using std::cerr;
using std::find_if;
using std::unordered_map;
using std::srand;
using std::exception;
using std::numeric_limits;
using std::streamsize;

// GLOBAL CONSTANTS
// -----------------------------------------------------------------------------

const string bulls = "bulls";
const string cows = "cows";
const string prompt = "> ";
const string quit = "quit";
const string quit_text = "Gave up after ";
const string rules_check_text = "Would you like to read the rules?";
const string play_again_text = "Would you like to play again?";

// FUNCTION DECLARATIONS
// -----------------------------------------------------------------------------

void intro();
void gameloop();
void rules();
int difficulty();
unordered_map<string, int> initialise(unordered_map<string, int> bulls_and_cows);
string number_gen(string number,int top);
string get_guess(string local, int guesses);
unordered_map<string, int> evaluate_guess(string guess, string goal,
                                          unordered_map<string, int> bulls_and_cows);
void give_up(string goal, int guesses);
void win(string number, int guesses);
void score(unordered_map<string, int> bulls_and_cows);

// utilities
void max_ignore();
void clean(runtime_error e);
bool y_or_n(string check_text);
bool is_number(string& s);

// FUNCTION DEFINITIONS
// -----------------------------------------------------------------------------

int main()
{
    try {
        intro();
        gameloop();
        return 0;
    }
    catch (exception& e) {
        cerr << "runtime error: " << e.what() << '\n';
        return 1;
    }
    catch (...) {
        cerr << "unknown error\n";
        return 2;
    }
}

void max_ignore()
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void clean(runtime_error e)
{
    cerr << e.what();
    cin.clear();
    max_ignore();
}

int difficulty ()
{
    const string easy = "easy";
    const string medium = "medium";
    const string hard = "hard";
    const string error_text = string("Enter ") + easy + '/' + medium + '/' + hard + string(": ");

    const unordered_map<string, int> difficulties = {
        {easy, 6},
        {medium, 8},
        {hard, 10}
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
            if (diff_label != easy &&
                diff_label != medium &&
                diff_label != hard)
                throw runtime_error(error_text);
            else break;
        }
        catch (runtime_error& e) {
            clean(e);
        }
    }
    max_ignore();

    cout << "\nDifficulty selected: " << diff_label << ".\n";
    return difficulties.at(diff_label);
}

bool y_or_n(string check_text)
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
                throw runtime_error(error_text);
            switch (checker) {
            case affirm:
                max_ignore();
                return true;
            case neg:
                max_ignore();
                return false;
            default:
                    throw runtime_error(error_text);
            }
        }
        catch (runtime_error& e) {
            clean(e);
        }
    }
    throw runtime_error("unknown error!");
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
    return !s.empty() && find_if(s.begin(), s.end(), [](char c) {
        return !isdigit(c); }) == s.end();
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
                throw runtime_error("Guess must be 4 digits!\n");
            break;
        }
        catch (runtime_error& e) {
            clean(e);
        }
    }
    return local;
}

unordered_map<string, int> evaluate_guess(string guess, string goal, unordered_map<string, int> bulls_and_cows)
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
}

void score(unordered_map<string, int> bulls_and_cows)
{
    cout << "[" << bulls_and_cows[bulls] << "] Bulls and ["
         << bulls_and_cows[cows] << "] Cows\n";
}

void rules()
{
    cout << "\nI will think of 4 digits. You have to guess\n"
        << "each digit correctly and in the right place\n"
        << "to win. If you guess a digit correctly in\n"
        << "the right place, you get a Bull. If you guess\n"
        << "a digit correctly but in the wrong place, you\n"
        << "get a Cow. 4 Bulls wins! (Type \"" + quit + "\" to\n"
        << "give up for the round.)\n";
}

void intro()
{
    cout << '\n'
        << "        ==== B U L L S ====\n"
        << "        ====== A N D ======\n"
        << "        ===== C O W S =====\n"
        << '\n';

    if (y_or_n(rules_check_text)) {
        rules();
    }
}

void gameloop()
{
    bool play_again = true;
    unordered_map<string, int> bulls_and_cows = {
            {bulls,  0},
            {cows, 0 }
    };
    string goal = "    "; // 4 spaces
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

            bulls_and_cows = evaluate_guess(guess, goal, bulls_and_cows);
            score(bulls_and_cows);

            if (bulls_and_cows[bulls] == 4)
                win(goal, guesses);
        }
        play_again = y_or_n(play_again_text);
    }
}
