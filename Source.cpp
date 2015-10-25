#include "Header.h"

int stringHash(string s);
int main() {

	const int SIZE = 9973;
	string input;
	ifstream inFile;
	string one;
	string two;
	string three;
	string four;
	string five;
	string six;
	string seven;
	string option;

	//array of Binary Search Tree objects where each index is a hashed string
	BSTree obs[SIZE];
	
	/*
	Set of the top 99 most common words in the english language
	This set of words wont be added to our hash table
	"The" is missing from this set because it is needed for a required query
	*/
	set<string> words{"be", "to", "of", "and", "a", "in", "that", "have", "i", "it", "for", "not", "on", "with", "he", "as", "you", "do", "at",
		"this", "but", "his", "by", "from", "they", "we", "say", "her", "she", "or", "an", "will", "my", "one", "all", "would", "there", "their", "what", "so",
		"up", "out", "if", "about", "who", "get", "which", "go", "me", "when", "make", "can", "like", "time", "no", "just", "him", "know", "take", "people", "into",
		"year", "your", "good", "some", "could", "them", "see", "other", "than", "then", "now", "look", "only", "come", "its", "over", "think", "also", "back",
		"after", "use", "two", "how", "our", "work", "first", "well", "way", "even", "new", "want", "because", "any", "these", "give", "day", "most", "us"};

	//set of all files that contain the words we are indexing
	set<string> file{ "cranfield0032", "cranfield0016", "cranfield0040", "cranfield0008", "cranfield0024", "cranfield0036", "cranfield0044"
		, "cranfield0004", "cranfield0012", "cranfield0020", "cranfield0028", "cranfield0034", "cranfield0038", "cranfield0042", "cranfield0048" 
		, "cranfield0002", "cranfield0006", "cranfield0010", "cranfield0014", "cranfield0018", "cranfield0022", "cranfield0026", "cranfield0030" 
		, "cranfield0033", "cranfield0035", "cranfield0037", "cranfield0039", "cranfield0041", "cranfield0043", "cranfield0046", "cranfield0049" 
		, "cranfield0001", "cranfield0003", "cranfield0005", "cranfield0007", "cranfield0009", "cranfield0011", "cranfield0013", "cranfield0015" 
		, "cranfield0017", "cranfield0019", "cranfield0021", "cranfield0023", "cranfield0025", "cranfield0027", "cranfield0029", "cranfield0031" 
		, "cranfield0045", "cranfield0047", "cranfield0050"};
	
	//auto increment over the set named file
	for (auto f : file) {
		inFile.open(f);
		while (inFile >> input) {
			//if the line begins with < or . or - or if the word is containined in the set named words then skip to next word
			if (input.at(0) == '<' || words.count(input) || input.at(0) == '.' || input.at(0) == '-') {
				inFile.ignore(1, '\n');
			}
			else {
				//if the file is not already contained in the tree then add the filename to the tree
				if (obs[stringHash(input)].search(f, obs[stringHash(input)].Root()) == false) {
					obs[stringHash(input)].insertNode(f);
				}				
			}
		}
		inFile.close();
	}

	//ask for user input then store in strings using stringstream
	cout << "Enter a Query or Type Q or q to Quit" << endl;
	getline(cin, option);
	stringstream ss(option);

	while (true) {
		getline(ss, one, ' ');
		getline(ss, two, ' ');
		getline(ss, three, ' ');
		getline(ss, four, ' ');
		getline(ss, five, ' ');
		getline(ss, six, ' ');
		getline(ss, seven, ' ');

		//Prints out query for one word
		if (two == "") {
			cout << one << " is found in the following files:" << endl;
			obs[stringHash(one)].inOrder(obs[stringHash(one)].Root());					
		}
		//Print out query for two words with an AND inbetween e.g. (flow AND stream)
		else if (two == "AND" && four == "") {
			cout << one << " " << two << " " << three << " are found in the following files:" << endl;
			for (auto f : file) {
				if (obs[stringHash(one)].search(f, obs[stringHash(one)].Root()) == true && obs[stringHash(three)].search(f, obs[stringHash(three)].Root()) == true) {
					cout << f << endl;
				}
			}
		}
		//Print out query for two words with an OR inbetween e.g. (flow OR stream)
		else if (two == "OR" && four == "") {
			cout << one << " " << two << " " << three << " are found in the following files:" << endl;
			for (auto f : file) {
				if (obs[stringHash(one)].search(f, obs[stringHash(one)].Root()) == true || obs[stringHash(three)].search(f, obs[stringHash(three)].Root()) == true) {
					cout << f << endl;
				}
			}
		}
		//Prints out query for three words with AND inbetween e.g. (the AND boundary AND layer)
		else if (two == "AND" && four == "AND" && six == "") {
			cout << one << " " << two << " " << three << " " << four << " " << five << " are found in the following files:" << endl;
			for (auto f : file) {
				if (obs[stringHash(one)].search(f, obs[stringHash(one)].Root()) == true && obs[stringHash(three)].search(f, obs[stringHash(three)].Root()) == true && obs[stringHash(five)].search(f, obs[stringHash(five)].Root()) == true) {
					cout << f << endl;
				}
			}
		}
		//Prints out query for three words with OR inbetween e.g. (the OR boundary OR layer)
		//It is also important to understand that OR statements will print out the file name if that file contains any of the words in your query
		else if (two == "OR" && four == "OR" && six == "") {
			cout << one << " " << two << " " << three << " " << four << " " << five << " are found in the following files:" << endl;
			for (auto f : file) {
				if (obs[stringHash(one)].search(f, obs[stringHash(one)].Root()) == true || obs[stringHash(three)].search(f, obs[stringHash(three)].Root()) == true || obs[stringHash(five)].search(f, obs[stringHash(five)].Root()) == true) {
					cout << f << endl;
				}
			}
		}
		//Prints out query for one grouping of two words or another word e.g ((flow AND stream) OR velocity)
		//if either return true then the filename is printed to the query
		else if (two == "AND" && four == "OR" && six == "") {
			cout << one << " " << two << " " << three << " " << four << " " << five << " are found in the following files:" << endl;
			for (auto f : file) {
				if ((obs[stringHash(one)].search(f, obs[stringHash(one)].Root()) == true && obs[stringHash(three)].search(f, obs[stringHash(three)].Root()) == true) || obs[stringHash(five)].search(f, obs[stringHash(five)].Root()) == true) {
					cout << f << endl;
				}
			}
		}
		//Prints out query for two groupings of words with AND between the words in the groups and OR between the main groupings e.g (reynolds AND number OR reynolds AND numbers)
		//This will print out in this format ((reynolds AND number) OR (reynolds AND numbers)) where if either group returns true the filename will be printed
		else if (two == "AND" && four == "OR" && six == "AND") {
			cout << one << " " << two << " " << three << " " << four << " " << five << " " << six << " " << seven << " are found in the following files:" << endl;
			for (auto f : file) {
				if ((obs[stringHash(one)].search(f, obs[stringHash(one)].Root()) == true && obs[stringHash(three)].search(f, obs[stringHash(three)].Root()) == true) || (obs[stringHash(five)].search(f, obs[stringHash(five)].Root()) == true && obs[stringHash(seven)].search(f, obs[stringHash(seven)].Root()))) {
					cout << f << endl;
				}
			}
		}
		//Prints out query for two groupings of words with OR between the words in the groups and OR between the main groupings e.g (reynolds OR number OR reynolds OR numbers)
		//This will print out in this format ((reynolds OR number) OR (reynolds OR numbers)) where if either group returns true the filename will be printed
		else if (two == "OR" && four == "OR" && six == "OR") {
			cout << one << " " << two << " " << three << " " << four << " " << five << " " << six << " " << seven << " are found in the following files:" << endl;
			for (auto f : file) {
				if ((obs[stringHash(one)].search(f, obs[stringHash(one)].Root()) == true || obs[stringHash(three)].search(f, obs[stringHash(three)].Root()) == true) || (obs[stringHash(five)].search(f, obs[stringHash(five)].Root()) == true || obs[stringHash(seven)].search(f, obs[stringHash(seven)].Root()))) {
					cout << f << endl;
				}
			}
		}
		
		//If input == Q or == q then the program exits
		if (option == "Q" || option == "q") {
			break;
		}
		//empty all saved strings ask for user input then restore strings from stringstream
		else {
			one.clear();
			two.clear();
			three.clear();
			four.clear();
			five.clear();
			six.clear();
			seven.clear();

			cout << "Enter a Query or Type Q or q to Quit" << endl;
			getline(cin, option);
			stringstream ss(option);
			getline(ss, one, ' ');
			getline(ss, two, ' ');
			getline(ss, three, ' ');
			getline(ss, four, ' ');
			getline(ss, five, ' ');
			getline(ss, six, ' ');
			getline(ss, seven, ' ');
		}
	}

	return 0;
}
//convert the input string to an integer that can be used as an index number in the hashTable
int stringHash(string s) {

	int sum = 7;

	//auto increment over each character in the string then take the sum * 31 then add the ascii value to that sum
	for (char& c : s) {
		sum = sum * 31 + c;
	}	

	return abs(sum % 9973);
}