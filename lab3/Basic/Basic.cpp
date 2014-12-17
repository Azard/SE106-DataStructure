#include <iostream>
#include <cctype>
#include <algorithm>
#include <vector>
#include <map>
#include <string>

using namespace std;

/* Global Variable */
map<int, string> instruction_list;	// save input instruction list
map<string, int> variable;			// save variable
bool can_run = true;

/*
 *	Function: is_operator 
 *	help token_scanner to analyse
 */

bool is_operator (char ch)
{
	return (ch == '=' || ch == '(' || ch == ')' || ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
			ch == '>' || ch == '<' );
}

/*
 *	Function: token_scanner 
 *	get string, return tokens in order in a vector<string>
 *	Usage: vector<string> tokens = token_scanner(input);
 */
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
 *	Function: is_statement
 *	determine is this input is statement with number ahead and not empty
 *	if true, add to instruction_list
 */

bool is_statement_and_addto_list(string &input) 
{
	vector<string> tokens = token_scanner(input);
	if (tokens.size()>1) {
		for (char i: tokens[0])
			if (!isdigit(i))	return false;
		for (int i = 0; i < input.length(); ++i)
			if (!isdigit(input[i]) && input[i] != ' ') {
				instruction_list[atoi(tokens[0].c_str())] = input.substr(i, string::npos);
				return true;
			}
	}
	else if (tokens.size() == 1) {
		for (char i: tokens[0])
			if (!isdigit(i))	return false;
		auto temp = instruction_list.find(atoi(tokens[0].c_str()));
		if ( temp != instruction_list.end() )
			instruction_list.erase(temp);
	}
	return false;
}

// is_variable, not number
bool is_variable(string input)
{
	return (isalpha(input[0]));
}


/*
 *	Function: read_exp
 *	0: =
 *	1: +-
 *	2: *'/' %
 */

int read_exp(vector<string>& tokens, int& pos, int prec)
{
	if (!can_run)
		return 0;
	int left,right, new_prec, save_pos;
	string op;
	if (is_variable(tokens[pos])) {
		auto temp = variable.find(tokens[pos]);
		if (temp == variable.end() && tokens[pos+1] != "=") {
			cout << "VARIABLE NOT DEFINED" << endl;
			can_run = false;
			return 0;
		}
		left = variable[tokens[pos]];
	}
	else
		left = atoi(tokens[pos].c_str());	
	if (tokens.size() == 1)	// for condition like print 1
		return left;
	if (pos == tokens.size()-1) // for last number
		return left;
	if (tokens[pos] == "(") {
		new_prec = 0;
		pos++;
		left = read_exp(tokens, pos, new_prec);
		if (pos == tokens.size()-1)
			return left;
	}

	while(true) {
		op = tokens[pos+1];
		if (op == ")") {
			pos++;
			return left;
		}
		if (op == "=") {
			new_prec = 0;
			save_pos = pos;
			pos += 2;
			right = read_exp(tokens, pos, new_prec);
			if (is_variable(tokens[save_pos]))
				variable[tokens[save_pos]] = right;
			else
				cerr << " = operate for number\n";
			return variable[tokens[save_pos]];
		}
		else if (op == "+" || op == "-" || op == "*" || op == "/" || op == "%") {
			new_prec = (op == "+" || op == "-")? 1 : 2;
			if (new_prec <= prec) return left;
			pos += 2;
			right = read_exp(tokens, pos, new_prec);
			if (op == "+") left = left + right;
			if (op == "-") left = left - right;
			if (op == "*") left = left * right;
			if (op == "/") {
				if (right == 0) {
					cout << "DIVIDE BY ZERO" << endl;
					can_run = false;
					return 0;
				}
				left = left / right;
			}
			if (op == "%") left = left % right;
		}
		else
			cerr << "Unknow operate\n";
		if (pos >=  tokens.size()-1)
			break;
	}
	return left;
}

/*
 *	Function: run_statement
 *	Only run one line statement
 *	REM, LET, PRINT, INPUT, END, GOTO, IF THEN 
 */

int run_statement(string& input)
{
	vector<string> tokens = token_scanner(input);
	if (tokens[0] == "REM") ;
	else if (tokens[0] == "LET") {
		tokens.erase(tokens.begin());
		int pos = 0;
		int prec = 0;
		read_exp(tokens, pos, prec);
	}
	else if (tokens[0] == "PRINT") {
		tokens.erase(tokens.begin());
		int pos = 0;
		int prec = 0;
		int value = read_exp(tokens, pos, prec);
		if (can_run)
			cout << value << endl;
	}
	else if (tokens[0] == "INPUT") {
		string var = tokens[1];
		while(true) {
			cout << " ? ";
			string exp;
			getline(cin, exp);
			bool valid_flag = true;
			for (auto i: exp) {
				if (!isdigit(i) && i!='-')
					valid_flag = false;
			}
			if (valid_flag) {
				variable[var] = atoi(exp.c_str());
				break;
			}
			cout << "INVALID NUMBER" << endl;
		}
	}
	else if (tokens[0] == "END") {
		return -2;	//halt
	}
	else if (tokens[0] == "GOTO") {
		return atoi(tokens[1].c_str());
	}
	else if (tokens[0] == "IF") {
		int op_pos = 0;
		string op;
		int target_val = 0;
		int then_pos = 0;
		int i = 1;
		while (true) {
			if (tokens[i] == "=" || tokens[i] == "<" || tokens[i] == ">") {
				op = tokens[i];
				op_pos = i;
			}
			if (tokens[i] == "THEN") {
				then_pos = i;
				target_val = atoi(tokens[i+1].c_str());
				break;
			}
			i++;
		}
		vector<string> if_left;
		vector<string> if_right;
		for (int p = 1; p < op_pos; p++)
			if_left.push_back(tokens[p]);
		for (int p = op_pos+1; p < then_pos; p++)
			if_right.push_back(tokens[p]);
		int left_temp_pos = 0;
		int left_temp_prec = 0;
		int right_temp_pos = 0;
		int right_temp_prec = 0;
		int left_val = read_exp(if_left, left_temp_pos, left_temp_prec);
		int right_val = read_exp(if_right, right_temp_pos, right_temp_prec);
		if (op == "=") {
			if (left_val == right_val)
				return target_val;
			else
				return -1;
		}
		else if (op == "<") {
			if (left_val < right_val)
				return target_val;
			else
				return -1;
		}
		else if (op == ">") {
			if (left_val > right_val)
				return target_val;
			else
				return -1;
		}
	}
	return -1;	//continue
}

// When input RUN
void run_all()
{
	for (auto i = instruction_list.begin(); i != instruction_list.end();)
	{	
		if (!can_run)
			break;
		string input = i->second;
		transform(input.begin(), input.end(), input.begin(), ::toupper);
		int flag = run_statement(input);
		if (flag == -2)
			break; // END: halt
		if (flag != -1) {
			i = instruction_list.find(flag);
			if (i == instruction_list.end())
				cout << "LINE NUMBER ERROR" << endl;
		}
		else
			i++;
	}
}


int main()
{
	while (true) {
		can_run = true;
		string input;
		int pos = 0;
		int prec = 0;
		getline(cin, input);
		if (is_statement_and_addto_list(input)) ;
		else
		{
			transform(input.begin(), input.end(), input.begin(), ::toupper);
			if (input == "RUN") {
				can_run = true;
				run_all();
			}
			else if (input == "LIST")
				for (auto i: instruction_list)
					cout << i.first << " " << i.second << endl;
			else if (input == "CLEAR") {
				variable.clear();
				instruction_list.clear();	
			}
			else if (input == "QUIT")
				exit(0);
			else if (input == "HELP")
				cout << "熊伟伦 5120379076\n";
			else
				run_statement(input);
		}
	}
	return 0;
}
