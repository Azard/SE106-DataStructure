#include <iostream>
#include <string>
#include <cctype>
#include <vector>

using namespace std;

/*
 *	Function: is_operator help token_scanner to analyse
 *	token_scanner get string, return tokens in order.
 */

bool is_operator (char ch)
{
	return (ch == '=' || ch == '(' || ch == ')' || ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

vector<string> token_scanner(string& input)
{
	vector<string> tokens;
	bool id_flag = false;
	bool num_flag = false;
	string temp_token;

	for (char ch: input) {
		if (id_flag) {
			if (isalnum(ch))
				temp_token += ch;
			else if (ch == ' ') {
				tokens.push_back(temp_token);
				temp_token = "";
				id_flag = false;
			}
			else if (is_operator(ch)) {
				tokens.push_back(temp_token);
				string temp;
				temp.insert(temp.begin(), ch);
				tokens.push_back(temp);
				temp_token = "";
				id_flag = false;
			}
			else
				cerr << "Unknow character " << ch << " after " << temp_token << endl;
		}
		else if (num_flag) {
			if (isdigit(ch))
				temp_token += ch;
			else if (ch == ' ') {
				tokens.push_back(temp_token);
				temp_token = "";
				num_flag = false;
			}
			else if (is_operator(ch)) {
				tokens.push_back(temp_token);
				string temp;
				temp.insert(temp.begin(), ch);
				tokens.push_back(temp);
				temp_token = "";
				num_flag = false;
			}
			else
				cerr << "Unknow character " << ch << " after " << temp_token << endl;
		}
		else {
			if (ch == ' ')
				;
			else if (isalpha(ch)) {
				temp_token += ch;
				id_flag = true;
			}
			else if (isdigit(ch)) {
				temp_token += ch;
				num_flag = true;
			}
			else if (is_operator(ch)) {
				string temp;
				temp.insert(temp.begin(), ch);
				tokens.push_back(temp);
			}
			else
				cerr << "Unknow character " << ch << endl;
		}
	}
	if (!is_operator(input[input.length()-1]))
		tokens.push_back(temp_token);
	return tokens;
}



/*
 *
 *	Parse parentheses
 *	precess:	
 *	0: + -
 *	1: * /
 *	2: constant
 */

int parse_parenthese(vector<string>& input, int& pos)
{
	int length = input.size();
	int head, tail;
	int prec = 2;
	while(true) {
		if (input[pos] == "(") {
			head = pos;
			prec = parse_parenthese(input, ++pos);
			tail = pos;
			bool del = true;
			if ((head != 0) && (input[head-1] == "/"))
				del = false;
			if ((head != 0) && (input[head-1] == "*" || input[head-1] == "-") && prec == 0)
				del = false;
			if ((tail+1 != length) && (input[tail+1] == "*" || input[tail+1] == "/") && prec == 0)
				del = false;
			if (del) {
				input[head] = " ";
				input[tail] = " ";
			}
			if (pos ==  length-1)
				return prec;
			pos++;
		}
		if (input[pos] == ")")
			return prec;
		if (prec > 0 && (input[pos] == "+" || input[pos] == "-"))
			prec = 0;
		if (prec > 1 && (input[pos] == "*" || input[pos] == "/"))
			prec = 1;
		if (pos ==  length-1)
			return prec;
		pos++;
	}
}


int main()
{
	while(true) {
		cout << "Input:" << endl;
		string input;
		getline(cin, input);
		vector<string> tokens = token_scanner(input);
		cout << "Output:" << endl;
		int begin = 0;	
		parse_parenthese(tokens, begin);
		vector<string> output;
		for (string i: tokens) {
			if (i != " ") {
				if (i == "+" || i == "-" || i == "*" || i == "/") {
					if (output.size() != 0) output.push_back(" ");
					output.push_back(i);
					output.push_back(" ");
				}
				else
					output.push_back(i);
			}
		}
		for (string i: output)
			cout << i;
		cout << endl;
	}
	return 0;
}
