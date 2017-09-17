#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <cstdlib>		//Required for srand(), rand().
#include <ctime>
#include <iomanip>		//setw()
#include <vector>

using namespace std;

bool binary_search(const vector<string>& sorted_vec, string key);
int rand_int(int a, int b);
bool linear_search(string word, char letter);
void make_man(int num);
void print_line(char characters[], string word, int k);
bool win(char characters[], string word, int length);
int index_search(const vector<string>& sorted_vec, string key);
void selection_sort(vector<string>& sorted_vec);


int main(void)
{
	int str_len, index, input, input1;
	string admin = "admin";
	string pass = "password";
	string tmp_word;
	string password;
	string text;
	string name;
	string word;
	string guess;
	string man;
	int num_guess;
	int num_chances = 0;
	int k = 0;
	char letter;
	vector<string> Dictionary;
	ifstream ifile ("Dictionary.txt");
	char alphabet[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
	'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
	char characters[26];
	char buffer[26];

	if (!ifile .is_open())
	{
	  cout<<"File ""Dictionary.txt"" could not be read"<<endl;
	  exit(0);

	}
	while(ifile  >> text)
	{
		Dictionary.push_back(text);
	}
	//Introduction
	cout <<"*******************************************************************************" <<endl;
	cout << "  HH  HH    AAAA   NN      N  GGGGGGG  MMM        MMM   AAAA   NN      N      " <<endl;
	cout << "  HH  HH   AA  AA  N N     N  GG   GG  MMM        MMM  AA  AA  N N     N      " <<endl;
	cout << "  HH  HH   AA  AA  N  N    N  GG       MM M      M MM  AA  AA  N  N    N      " <<endl;
	cout << "  HHHHHH   AAAAAA  N   N   N  GG  GGG  MM  M    M  MM  AAAAAA  N   N   N      " <<endl;
	cout << "  HH  HH   AA  AA  N    N  N  GG    G  MM   M  M   MM  AA  AA  N    N  N      " <<endl;
	cout << "  HH  HH   AA  AA  N     N N  GG    G  MM    MMM   MM  AA  AA  N     N N      " <<endl;
	cout <<	"  HH  HH   AA  AA  N       N  GGGGGGG  MM          MM  AA  AA  N       N      " <<endl;
	cout <<"*******************************************************************************" <<endl;
	cout << setw(33) << Dictionary.size() <<" Words Imported"<<endl;
	cout << endl;
	cout << "What is your name: ";
	cin >> name;

	if (admin.compare(name) == 0)
	{
		int tmp;

			cout<<endl<<endl;
			cout<<"Welcome administrator"<<endl;
			cout<<"Enter password: ";
			cin >> password;
			cout <<endl;
			if(pass.compare(password) == 0)
			{

					cout<<"What would you like to do?"<<endl;
					cout<<"Enter <1> to add a word"<<endl;
					cout<<"Enter else to Exit"<<endl;
						while(!(cin >> tmp))
						{
							cout<<"Enter <1> to add a word"<<endl;
							cout<<"Enter else to Exit"<<endl;
							cin.clear();
							cin.ignore(100, '\n');
						}
		     		if(tmp == 1)
			     	{
			     		cout<<"Please enter a word to add: ";
			     		cin >>tmp_word;
			     		if (!binary_search(Dictionary, tmp_word))
			     		{
				     		Dictionary.push_back(tmp_word);
				     		cout<<tmp_word<<" has been added"<<endl;
				     		selection_sort(Dictionary);
							ofstream ofile("Dictionary.txt");
							for(int i = 0; i < Dictionary.size(); i++)
							{
								ofile << Dictionary[i] <<endl;
							}
							ofile.close();
				     	}
				     	else
				     	{
				     		cout<<tmp_word<<" is already in Dictionary.txt"<<endl;
				     	}
			     	}
			     	else
			     	{
			     		cout<<"Exited!"<<endl;
			     		exit(0);
			     	}
			}
			else
			{
				cout<<"You entered the wrong password"<<endl;
				exit(0);
			}
			ifile .close();
			exit(0);
	}
	selection_sort(Dictionary);
	ofstream ofile("Dictionary.txt");
	for(int i = 0; i < Dictionary.size(); i++)
	{
		ofile << Dictionary[i] <<endl;
	}

	ofile.close();
	ifile.close();

	cout << endl << endl <<endl;
	cout<<"                 Welcome " <<name << ", how would you like to play?               " << endl;
	cout<<"           Press (1) for Single Player or Press (2) for Double Player            " <<endl;

	//randomize word pick from library array
	srand(time(NULL));
	do
	{
		index = rand_int(0, Dictionary.size());
		word = Dictionary[index];
		str_len = word.length();
	}
	while(str_len < 7);
	num_guess = 7;
	//cout <<word<<endl;


	while(!(cin >> input))
	{
		cout<<"           Press (1) for Single Player or Press (2) for Double Player        " <<endl;
		cin.clear();
		cin.ignore(100, '\n');
	}

	if(input == 1)
	{
		cout<<"                     Welcome to Single Player Mode                             " <<endl;
		cout<<"A word has been randomly picked and you have " << str_len<< " chances to guess " <<endl;
		cout<<endl;
		cout<<"\n  ================\n //\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n /\\\n//\\\\\n/||\\\\\n_||_\\\\\n";
		cout<<"                             "<< endl;
		for(int i = 0; i < str_len; i++)
		{
			cout<<'-';
		}
		cout<<endl;

		while(num_guess > 0)
		{
			cout<<"            	     You have "<< num_guess << " guess(es) left                     " <<endl;
			cout<<"             Enter(0) to Guess a word or Enter(1) to guess a letter            " <<endl;

			while(!(cin >> input1))
			{
				cout<<"            	     You have "<< num_guess << " guess(es) left                     " <<endl;
				cout<<"             Enter(0) to Guess a word or Enter(1) to guess a letter            " <<endl;
				cin.clear();
				cin.ignore(100, '\n');
			}

			if(input1==0)
			{
				cout <<"Word: ";
				cin >> guess;
				if(word.compare(guess)==0)
				{
					cout<<"                    Congratulations you have won!                             " <<endl;
					int x;
					x = index_search(Dictionary, word);
					cout<<"               The Word " << word << " was index at " << x <<endl;
					exit(0);
				}
				else
				{
					cout<<"                             Incorrect!                                      " <<endl;
					num_guess--;
					num_chances++;
					make_man(num_chances);
					characters[k] = letter;
					k++;
	 				print_line(characters, word, k);
				}
			}
			if(input1==1)
			{
				cout <<"Letter: ";
				cin >> letter;
				if(linear_search(word, letter))
				{
					cout<<"                             Correct!                                         "<<endl;
					make_man(num_chances);
					characters[k] = letter;
	 				k++;
					print_line(characters, word, k);
					if(win(characters, word, k))
					{
						int x;
						cout<<"                    Congratulations you have won!                             " <<endl;
						x = index_search(Dictionary, word);
						cout<<"               The Word " << word << " was index at " << x <<endl;
						exit(0);
					}
				}

	 			else
	 			{
	 				cout<<"                             Incorrect!                                       "<<endl;
	 				num_guess--;
	 				num_chances++;
	 				make_man(num_chances);
		 			characters[k] = letter;
		 			k++;
 	 				print_line(characters, word, k);
	 			}
			}
		}
			cout <<"You have ran out of chances. YOU LOSE!" << endl;

	}

	if(input == 2)
	{
		int AI_guess = 7;
		cout<<"                     Welcome to Double Player Mode                             " <<endl;
		cout<<"A word has been randomly picked and you have " << str_len<< " chances to guess " <<endl;
		cout<<"                    You will be playing against the AI                         " <<endl;
		cout<<endl;
		cout<<"\n  ================\n //\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n /\\\n//\\\\\n/||\\\\\n_||_\\\\\n";
		cout<<"                             "<< endl;
		for(int i = 0; i < str_len; i++)
		{
			cout<<'-';
		}
		cout<<endl;

		while(num_guess > 0)
		{
			cout<<"            	     You have "<< num_guess << " guess(es) left                     " <<endl;
			cout<<"             Enter(0) to Guess a word or Enter(1) to guess a letter            " <<endl;

			while(!(cin >> input1))
			{
				cout<<"            	     You have "<< num_guess << " guess(es) left                     " <<endl;
				cout<<"             Enter(0) to Guess a word or Enter(1) to guess a letter            " <<endl;
				cin.clear();
				cin.ignore(100, '\n');
			}

			if(input1==0)
			{
				cout <<"Word: ";
				cin >> guess;
				if(word.compare(guess)==0)
				{
					cout<<"                    Congratulations you have won!                             " <<endl;
					int x;
					x = index_search(Dictionary, word);
					cout<<"               The Word " << word << " was index at " << x <<endl;
					exit(0);
				}
				else
				{
					cout<<"                                  Incorrect!                                   " <<endl;
					num_guess--;
					num_chances++;
					make_man(num_chances);
					characters[k] = letter;
					k++;
	 				print_line(characters, word, k);
	 				int	AI = rand_int(0, 26) + 1;
					char s = alphabet[AI];
					cout<<endl;
					cout<<"                               The AI guessed " << s << "                             " <<endl;
					if(linear_search(word, s))
					{
						cout<<"                                    Correct!                                   	      "<<endl;
						make_man(num_chances);
						characters[k] = s;
		 				k++;
		 				print_line(characters, word, k);
		 				if(win(characters, word, k))
		 				{
		 					int x;
							cout<<"                           Sorry the AI has won              		               " <<endl;
							x = index_search(Dictionary, word);
							cout<<"               The Word " << word << " was index at " << x <<endl;
							exit(0);
						}
		 			}
		 			else
		 				{
			 				cout<<"                                    Incorrect!                                      " <<endl;
							make_man(num_chances);
							characters[k] = s;
							k++;
			 				print_line(characters, word, k);
		 				}
				}
			}
			if(input1==1)
			{
				cout <<"Letter: ";
				cin >> letter;
				if(linear_search(word, letter))
				{
					cout<<"                             Correct!                                         "<<endl;
					make_man(num_chances);
					characters[k] = letter;
	 				k++;
					print_line(characters, word, k);
					if(win(characters, word, k))
					{
						int x;
						cout<<"                    Congratulations you have won!                             " <<endl;
						x = index_search(Dictionary, word);
						cout<<"               The Word " << word << " was index at " << x <<endl;
						exit(0);
					}
					int	AI = rand_int(0, 26) + 1;
					char s = alphabet[AI];
					cout<<endl;
					cout<<"                               The AI guessed " << s << "                             " <<endl;
					if(linear_search(word, s))
					{
						cout<<"                                    Correct!                                   	      "<<endl;
						make_man(num_chances);
						characters[k] = s;
		 				k++;
		 				print_line(characters, word, k);
		 				if(win(characters, word, k))
		 				{
		 					int x;
							cout<<"                           Sorry the AI has won              		               " <<endl;
							x = index_search(Dictionary, word);
							cout<<"               The Word " << word << " was index at " << x <<endl;
							exit(0);
						}
		 			}
		 			else
		 				{
			 				cout<<"                                    Incorrect!                                      " <<endl;
							make_man(num_chances);
							characters[k] = s;
							k++;
			 				print_line(characters, word, k);
		 				}

				}
	 			else
	 			{
	 				cout<<"                                           Incorrect!                                       "<<endl;
	 				num_chances++;
	 				num_guess--;
	 				make_man(num_chances);
		 			characters[k] = letter;
		 			k++;
 	 				print_line(characters, word, k);
 	 				int	AI = rand_int(0, 26) + 1;
					char s = alphabet[AI];
					cout<<endl;
					cout<<"                                       The AI guessed " << s << "                             " <<endl;
				if(linear_search(word, s))
				{
					cout<<"                                          Correct!                                   	      "<<endl;
					make_man(num_chances);
					characters[k] = s;
	 				k++;
	 				print_line(characters, word, k);
	 				if(win(characters, word, k))
	 				{
	 					int x;
						cout<<"                    Sorry the AI has won              		               " <<endl;
						x = index_search(Dictionary, word);
						cout<<"               The Word " << word << " was index at " << x <<endl;
						exit(0);
					}
	 			}
	 			else
	 				{
		 				cout<<"                                     Incorrect!                                            " <<endl;
						make_man(num_chances);
						characters[k] = s;
						k++;
		 				print_line(characters, word, k);
	 				}
	 			}


			}
		}
		cout <<"You have ran out of chances. YOU LOSE!" << endl;

	}
		return 0;
	}


bool binary_search(const vector<string>& sorted_vec, string key)
 {
   size_t mid, left = 0 ;
   size_t right = sorted_vec.size(); // one position passed the right end
   while (left < right) {
      mid = left + (right - left)/2;
      if (key > sorted_vec[mid]){
          left = mid+1;
      }
      else if (key < sorted_vec[mid]){
        right = mid;
      }
      else
      {
        return true;
      }
   }

   return false;
}

int rand_int(int a, int b)
{
  return rand()%(b-a+1) + a;
}

bool linear_search(string word, char letter)
{
	int length = word.length();
	for(int i = 0; i < length; i++)
	{
		if(word[i] == letter)
		{
			return true;
		}

	}
	return false;
}

void make_man(int num)
{
    switch (num)
    {
        case 7:
        	cout<< "\n  ================|\n //               |\n ||               |\n ||               |\n ||              _^_\n ||             / ..\\\n ||            [  _  ]\n ||             \\___/\n ||\n ||               ||    - *Snap!!!*\n ||              /||\\\n ||             //||\\\\\n ||            // || \\\\\n ||            *  ||  *\n ||              //\\\\\n ||             //  \\\\\n /\\            //    \\\\\n//\\\\         ***      ***\n/||\\\\\n_||_\\\\\n";
        	break;
        case 6:
        	cout<< "\n  ================|\n //               |\n ||               |\n ||               |\n ||              _^_\n ||             / ..\\\n ||            [  _  ]\n ||             \\___/\n ||               ||\n ||              /||\\\n ||             //||\\\\\n ||            // || \\\\\n ||            *  ||  *\n ||              //\n ||             //\n ||            //\n /\\          ***\n//\\\\ \n/||\\\\ \n_||_\\\\\n";
        	break;
        case 5:
        	cout<< "\n  ================|\n //               |\n ||               |\n ||               |\n ||              _^_\n ||             / ..\\\n ||            [  _  ]\n ||             \\___/\n ||               ||\n ||              /||\\\n ||             //||\\\\\n ||            // || \\\\\n ||            *  ||  *\n ||\n ||\n ||\n /\\\n//\\\\\n/||\\\\\n_||_\\\\\n";
        	break;
        case 4:
        	cout<< "\n  ================|\n //               |\n ||               |\n ||               |\n ||              _^_\n ||             / ..\\\n ||            [  _  ]\n ||             \\___/\n ||               ||\n ||              /||\n ||             //||\n ||            // ||\n ||            *  ||\n ||\n ||\n ||\n /\\\n//\\\\\n/||\\\\\n_||_\\\\\n";
        	break;
        case 3:
        	cout<< "\n  ================|\n //               |\n ||               |\n ||               |\n ||              _^_\n ||             / ..\\\n ||            [  _  ]\n ||             \\___/\n ||               ||\n ||               ||\n ||               ||\n ||               ||\n ||               ||\n ||\n ||\n ||\n /\\\n//\\\\\n/||\\\\\n_||_\\\\\n";
        	break;
        case 2:
        	cout<< "\n  ================|\n //               |\n ||               |\n ||               |\n ||              _^_\n ||             / ..\\\n ||            [  _  ]\n ||             \\___/\n ||               ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n /\\\n//\\\\\n/||\\\\\n_||_\\\\\n";
        	break;
        case 1:
        	cout<< "\n  ================|\n //               |\n ||               |\n ||               |\n ||              _^_\n ||             / ..\\\n ||            [  _  ]\n ||             \\___/\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n /\\\n//\\\\\n/||\\\\\n_||_\\\\\n";
    		break;
    	case 0:
    		cout<<"\n  ================\n //\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n ||\n /\\\n//\\\\\n/||\\\\\n_||_\\\\\n";
    		break;
    }
}

bool win(char characters[], string word, int length)
{
	bool found = true;
	for(int i = 0; i<word.size();i++)
	{
		found = false;
		for(int j = 0; j<length;j++)
		{
			if(characters[j] == word.at(i))
				found = true;
		}
		if (!found)
			return false;
	}
	return true;
}



void print_line(char characters[], string word, int k)
{

	char letters[word.size()];
	for (int i = 0; i <word.size(); i++)
	{
		letters[i] = '-';
		for(int j = 0; j < k; j++)
		{
			if(word.at(i) == characters[j])
				letters[i] = characters[j];
		}
	}

	for(int i = 0; i <word.size(); i++)
		cout << letters[i];
	cout << endl;
	return;
}

int index_search(const vector<string>& sorted_vec, string key)
 {
   size_t mid, left = 0 ;
   size_t right = sorted_vec.size();
   while (left < right) {
      mid = left + (right - left)/2;
      if (key > sorted_vec[mid]){
          left = mid+1;
      }
      else if (key < sorted_vec[mid]){
        right = mid;
      }
      else
      {
        return mid;
      }
   }

   return 0;
}

void selection_sort(vector<string>& vector)
{
	int index;
	int length = vector.size();
	for(int i = 0; i < length; i++)
	{
		index = i;;
		for(int j = i; j < length; j++)
		{
			if(vector[j] < vector[index])
				index = j;
		}
		swap(vector[i], vector[index]);
	}
}
