#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include <string>
/*
 * Class that simulates a functions object.
 * Features include determining if a user's input is balanced
 * 	and translating balanced infix input to postfix form
 *
 * @author Logan Karney
 * @version Winter 2018
 */
class functions{

public:
	/* 
 	Default Constructor  
 	*/
	functions();

	/* 
 	Default Destructor  
	*/
	~functions();
	
	/** Determines if there is a closing parenthesis/bracket/brace 
 		for every corresponding opening symbol  */
	bool balancedSymbols(std::string input);
	
	/** Turns user input from infix to postfix  */
	std::string iToP(std::string input);

private:
	/** Determines if the input string is an operator 
 		or parenthesis/bracket/brace  */	
	bool is_operator(std::string s);

	/** Determines PEMDAS ordering of input string  */
	int precedence(std::string s);

	/** Returns true if input is a left parenthesis/bracket/brace  */
	bool is_left(std::string s);

	/** Returns true if the input is a right parenthesis/bracket/brace */
	bool is_right(std::string s);
};

#endif
