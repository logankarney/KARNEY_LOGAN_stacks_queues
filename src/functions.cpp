#define CATCH_CONFIG_MAIN
#include <string>
#include <stack>
#include <iostream>
#include "functions.h"

/*
 * Program that instatiates a functions object.
 * Features include determining if a user's input is balanced,
 * 	and translating it from infix into postfix.
 *
 * @author Logan Karney
 * @version Winter 2018
*/
int main(){
	
	//Declaration of functions object
	functions f;
	
	//String used to store user input
	std::string input;


	std::cout << std::endl << 
	"Please enter a function, ie \"a + b * c + ( d * e + f ) * g\"" 
	<< std::endl;
	
	//Recieves user input in its entireity
	//http://www.cplusplus.com/reference/string/string/getline/
	std::getline(std::cin, input);

	//Adds space for the delimiter
	if(input[input.size()-1] != ' ')
		input += " ";
	
	//Only attempts to translate infix to postfix if the equation is balanced
	if(f.balancedSymbols(input)){
		std::cout << std::endl << "Infix:   " << input << std::endl 
		<< "Postfix: " << f.iToP(input) << std::endl << std::endl;

	} else {
		std::cout << std::endl << "Error: Syntax" << std::endl;
	}

}

/*
 * Default Constructor
 */
functions::functions(){
}

/*
 * Default Destructor
 */
functions::~functions(){
}

/*
 * Iterates through the input and determines whether it has the correct
 * 	amount of parenthesis/brackets/braces (p/b/b)
 */
bool functions::balancedSymbols(std::string input){
	
	//Declaration of stack data type
	std::stack<char> pile;
        char left[] = {'(', '[', '{' };
        char right[] = {')', ']', '}'};

	int size = sizeof(input)/sizeof(input[0]);

	for(char c : input){
        	for(int i = 0; i < size; i++){

			//Pushes char onto stack if it is a left p/b/b
                	if(c == left[i]){
                        	pile.push(c);
                        } else if ( c == right[i]){

				//Checks stack to see if the matching p/b/b matches the current one
                                if(pile.size() == 0 || pile.top() != left[i]){
                                        return false;
                                }
                                pile.pop();
                        }
                } 
        }
	return true;
}

/*
 * Translates valid infix input into postfix
 */
std::string functions::iToP(std::string input){

	//Deckaration of stack data type, holds operators and parenthesis/braces/brackets (p/b/b)
	std::stack<std::string> pile;
	std::string output;

	//https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
	std::string delimiter = " ";
	std::string token;

	size_t element = 0;
	
	//Fires while the delimiter still has more tokens
	while((element = input.find(delimiter)) != std::string::npos){
		token = input.substr(0, element);

		//Determines if the current token is an operator or p/b/b
		if(is_operator(token)){
			
			//When token is a right p/b/b
			if(precedence(token) == 0){
				
				//Removes tokens from the stack until it finds its left p/b/b
				while(pile.size() != 0 && !is_left(pile.top())){
					output += pile.top() + " ";
					pile.pop();
				}
			}			
			
			//When the stack is empty or when
			//	the token on top has a lower priority on PEMDAS
			else if(pile.size() == 0 || precedence(pile.top()) < precedence(token))
				pile.push(token);
			else{
			//When the top of the pile has a higher or equal precedence than 
			//	the current token

				//Copy of the stack's size
				int size_copy = pile.size();
		
				//While the stack still has tokens
				while(size_copy != 0){

					//When the stack's top token is not a left brace
					if(!is_left(pile.top())){

						//Adds stack's top token to output
						output += pile.top() + " ";
						pile.pop();
					}
					
					//Decrements size_copy
					size_copy--;
				}
		
				//Adds current token to stack
				pile.push(token);
			}
		} else{
		//When the token is not an operator or whitespace
			if(token.compare(" ") != 0)
				output += token + " ";
		}
		
		//Removes token
		input.erase(0, element + delimiter.length());
	}

	//Adds any remainding non-left p/b/b tokens on the stack to the output
	for(int i = 0; (i = pile.size()); i++){
		if(!is_left(pile.top()))
			output += pile.top() + " ";
		pile.pop();
	}

	//Returns output
	return output;
}

/*
 * Determines whether the input string is a parenthesis/bracket/brace or operator
 */
bool functions::is_operator(std::string s){	
	std::string operators[] = {"(", ")", "{", "}", "[", "]", "*", "/", 
	"+", "-"};

	for(std::string o : operators){
		if( s.compare(o) == 0)
			return true;
	}
	return false;
}

/*
 * Determines the PEMDAS ordering of the input string
 * 	Note: Right parenthesis/bracket/braces have the lowest priority
 */
int functions::precedence(std::string s){

	if(is_left(s))
		return 3;
	else if(s.compare("*") == 0 || s.compare("/") == 0)
		return 2;
	else if(s.compare("+") == 0 || s.compare("-") == 0)
		return 1;
	else if(is_right(s))
		return 0;

	return -1;
}

/*
 * Returns true if the input string is a left parenthesis/bracket/brace
 */
bool functions::is_left(std::string s){
	if(s.compare("(") == 0 || s.compare("{") == 0 || s.compare("[") == 0)
                return true;
	return false;
}

/*
 * Returns true if the input string is a right parenthesis/bracket/brace 
 */
bool functions::is_right(std::string s){
	if(s.compare(")") == 0 || s.compare("}") == 0 || s.compare("]") == 0)
                return true;
	return false;
}

