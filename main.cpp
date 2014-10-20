/*
	Steven Bock
	10-9-2014
	CSCE 343
	Lab 2

	BUGS:
	- int literals aren't being recorded properly
	- can't output strings without map iterators
	- don't know how to use map iterators
	- some of these might be fixed by using C++11, but I opted to avoid using compiler flags to shift the language
	- would have loved to have an easter egg, but the app kept segfaulting when it was input


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
	- http://stackoverflow.com/questions/12240010/how-to-read-from-a-text-file-character-by-character-in-c/12240035#12240035
	- http://www.cplusplus.com/reference/cctype/isspace/
	- http://www.java2s.com/Code/Cpp/Map-Multimap/Loopthroughmapandprintallthekeyvaluepair.htm

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

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

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
	map <int, int> int_literal;
	map <char, int> special_cases;


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

	/* identifiers["[a-zA-Z]"] */
	vector<string> idents;
	int ident_count = 0;

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

	/* check for 1.23, then add it to real_literal */
	vector<string> real_literal;
	int real_counter = 0;

	/* check for string literals and add them to string_literal */
	vector<string> str_literal;
	int str_counter = 0;

	special_cases['('] = 0;
	special_cases[')'] = 0;
	special_cases['['] = 0;
	special_cases[']'] = 0;
	special_cases['+'] = 0;
	special_cases['-'] = 0;
	special_cases['='] = 0;
	special_cases[','] = 0;
	special_cases[';'] = 0;
	special_cases['{'] = 0;
	special_cases['}'] = 0;
	special_cases['&'] = 0;
	special_cases['*'] = 0;
	special_cases['/'] = 0;
	
	/* scan the file */
	char curChar;
	string identifier;
	while(tiny_c >> curChar){
		/* check identifier if it matches anything */
		if (identifier == "if"){
			keywords["if"] += 1;
			identifier = "";
		}	
		else if (identifier == "else"){
			keywords["else"] += 1;
			identifier = "";
		}
				
		else if (identifier == "for"){
			keywords["for"] += 1;
			identifier = "";
		}	
			
		else if (identifier == "do"){
			keywords["do"] += 1;
			identifier = "";
		}
			
		else if (identifier == "while"){
			keywords["while"] += 1;
			identifier = "";
		}
				
		else if (identifier == "switch"){
			keywords["switch"] += 1;
			identifier = "";
		}
				
		else if (identifier == "case"){
			keywords["case"] += 1;
			identifier = "";
		}
				
		else if (identifier == "default"){
			keywords["default"] += 1;
			identifier = "";
		}
			
		else if (identifier == "break"){
			keywords["break"] += 1;
			identifier = "";
		}
				
		else if (identifier == "return"){
			keywords["return"] += 1;
			identifier = "";
		}
				
		else if (identifier == "0"){
			int_literal[0] += 1;
			identifier = "";
		}
			
		else if (identifier == "1"){
			int_literal[1] += 1;
			identifier = "";
		}
		else if (identifier == "2"){
			int_literal[2] += 1;
			identifier = "";
		}
		else if (identifier == "3"){
			int_literal[3] += 1;
			identifier = "";
		}
		else if (identifier == "4"){
			int_literal[4] += 1;
			identifier = "";
		}
		else if (identifier == "5"){
			int_literal[5] += 1;
			identifier = "";
		}
		else if (identifier == "6"){
			int_literal[6] += 1;
			identifier = "";
		}
		else if (identifier == "7"){
			int_literal[7] += 1;
			identifier = "";
		}
		else if (identifier == "8"){
			int_literal[8] += 1;
			identifier = "";
		}
		else if (identifier == "9"){
			int_literal[9] += 1;
			identifier = "";
		}
		
		else{
			break;
		}
		
		
		
		
		/* push current character onto string */
		identifier.push_back(curChar);

	}
	
	/* print out results using iterator*/
	cout << "Lexeme, # appearances, Class" << endl;
	
	/* print int literals */
	for (int i=0; i<10; i++){
		cout << int_literal[i] << ", " << int_literal[i] << ", int literal" << endl;
	}
	

	/* Close the file at the end of everything */
	tiny_c.close();

	return 0;
}
