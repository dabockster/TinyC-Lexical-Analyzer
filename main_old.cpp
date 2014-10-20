/*
	Steven Bock
	10-9-2014
	CSCE 343
	Lab 2

	BUGS:


	SOURCES CITED:
	- Previous code from CSCE487 (CSCE Special Topics - C++ and the Linux Environment)
	  taught in J-Term 2014 by Dr. David Wolff
	- Comparing with classmates
	- http://www.cplusplus.com/reference/fstream/ifstream/
	- http://stackoverflow.com/questions/12133379/c-using-ifstream-with-getline
	- http://www.cplusplus.com/forum/general/94010/
	- http://gehrcke.de/2011/06/reading-files-in-c-using-ifstream-dealing-correctly-with-badbit-failbit-eofbit-and-perror/
	- http://www.cplusplus.com/doc/tutorial/other_data_types/
	- http://stackoverflow.com/questions/2179946/i-would-like-to-see-a-hash-map-example-in-c
	- http://kengine.sourceforge.net/tutorial/g/stdmap-eng.htm
	- http://stackoverflow.com/questions/236129/how-to-split-a-string-in-c/5208977#5208977
	- http://www.cplusplus.com/reference/sstream/stringstream/
	- http://stackoverflow.com/questions/3617797/regex-to-match-only-letters/3617808#3617808
	- http://cs.baylor.edu/~donahoo/tools/gdb/tutorial.html
	- http://www.cplusplus.com/forum/beginner/45081/#msg244551
	- http://www.cplusplus.com/forum/beginner/8404/#msg38975

	DOGE:
           ▄              ▄
          ▌▒█           ▄▀▒▌
          ▌▒▒▀▄       ▄▀▒▒▒▐
	     ▐▄▀▒▒▀▀▀▀▄▄▄▀▒▒▒▒▒▐                          wow
	   ▄▄▀▒▒▒▒▒▒▒▒▒▒▒█▒▒▄█▒▐
	  ▄▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▀██▀▒▌
	 ▐▒▒▒▄▄▄▒▒▒▒▒▒▒▒▒▒▒▒▒▀▄▒▒▌
	 ▌▒▒▐▄█▀▒▒▒▒▄▀█▄▒▒▒▒▒▒▒█▒▐        very arguments
	▐▒▒▒▒▒▒▒▒▒▒▒▌██▀▒▒▒▒▒▒▒▒▀▄▌
	▌▒▀▄██▄▒▒▒▒▒▒▒▒▒▒▒░░░░▒▒▒▒▌
	▌▀▐▄█▄█▌▄▒▀▒▒▒▒▒▒░░░░░░▒▒▒▐
	▐▒▀▐▀▐▀▒▒▄▄▒▄▒▒▒▒▒░░░░░░▒▒▒▌                                many C++
	▐▒▒▒▀▀▄▄▒▒▒▄▒▒▒▒▒▒░░░░░░▒▒▒▐
	 ▌▒▒▒▒▒▒▀▀▀▒▒▒▒▒▒▒▒░░░░▒▒▒▒▌
	 ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▐
	  ▀▄▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▄▄▄▄▌                so lexems
	    ▀▄▒▒▒▒▒▒▒▒▒▒▄▄▄▀
	      ▀▄▄▄▄▄▄▀▀▀
	*/

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>

using namespace std;

// g++ -Wall -g main.cpp -o main

void symbol_header(){
	cout << "=======================" << endl;
	cout << "Symbol table" << endl;
	cout << "=======================\n" << endl;
}

int main(int argc, char* argv[]){

	/* check for proper number of args */
	if (argc != 2){
		cout <<
		"\nERROR: Invalid number of arguments\nThe only argument accepted is the input filename."
		<< endl;
		return 1;
	}

	/* declare file data stream */
	ifstream tiny_c;

	/* open file stream */
	tiny_c.open(argv[1]);

	/* Print file reading statement */
	cout << "\nReading filename " << argv[1] << "...done.\n" << endl;

	/*
		------------------------------
		-------- SYMBOL TABLE --------
		------------------------------
	*/

	/* print header */
	symbol_header();

	/* declare token counters */
	enum token_types {
		TOK_ID,
		TOK_INT_LIT,
		TOK_REAL_LIT,
		TOK_STRING_LIT,
		TOK_SPECIAL,
		TOK_KEYWORD
	};

	/* maps for literals */
	map <string, int> keywords;
	map <string, int> identifiers;
	map <int, int> int_literal;
	map <double, int> real_literal;
	map <string, int> string_literal;
	map <string, int> special_cases;


	/* build maps */
	keywords["if"] = 0;
	keywords["else"] = 0;
	keywords["for"] = 0;
	keywords["do"] = 0;
	keywords["while"] = 0;
	keywords["switch"] = 0;
	keywords["case"] = 0;
	keywords["default"] = 0;
	keywords["break"] = 0;
	keywords["return"] = 0;

	//identifiers["[a-zA-Z]"] = 0;

	int_literal[0] = 0;
	int_literal[1] = 0;
	int_literal[2] = 0;
	int_literal[3] = 0;
	int_literal[4] = 0;
	int_literal[5] = 0;
	int_literal[6] = 0;
	int_literal[7] = 0;
	int_literal[8] = 0;
	int_literal[9] = 0;

	//check for 1.23, then add it to real_literal

	//check for string literals and add them to string_literal

	special_cases["(|)"] = 0;
	special_cases["[|]"] = 0;
	special_cases["+"] = 0;
	special_cases["-"] = 0;
	special_cases["="] = 0;
	special_cases[","] = 0;
	special_cases[";"] = 0;
	special_cases["{|}"] = 0;
	special_cases["&"] = 0;
	special_cases["*"] = 0;
	special_cases["/"] = 0;

	/* line placeholder */
	string line;

	/* whitespace_counter */
	int whitespace_counter = 0;

	/* scan the file */
	while(! tiny_c.eof()){
		/* needed for later */
		vector<string> tokens;

		/* grab the line for reading */
		tiny_c >> line;

		/* get rid of the spaces */
		string delimiter = " ";
		size_t position = 0;

		/* count whitespaces */
		for (unsigned int i = 0; i<line.length(); i++){
			if (line.at(i) == ' '){
				whitespace_counter += 1;
			}
		}
		while((position = line.find(delimiter)) != string::npos){
			whitespace_counter = whitespace_counter + 1;
			string tok = line.substr(0, position);
			tokens.push_back(tok);
			line.erase(0, position + delimiter.length());
		}
		tokens.push_back(line);

		/* find lexemes */
		for (int i=0; i<tokens.size(); i++){
			string tok = tokens[i];
			
			/* extract possible special case at the end of the token */
			string psc = *tok.rbegin();

			if (special_cases.count(psc) > 0){
				//DEBUG
				cout << "SPECIAL CASE: " << psc << endl;
			}

			

			if (keywords.count(tok) > 0){

			}

			//DEBUG
			cout << tok << endl;
		}



	}

	//DEBUG
	cout << "\n\nWhitespace: " << whitespace_counter << endl;

	/* Close the file at the end of everything */
	tiny_c.close();

	return 0;
}
