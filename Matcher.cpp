#include <map>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <stack>
#include <set>
using namespace std;


class Matcher {
private:
	vector<vector< string > > parsingTable;
	NonTerminal* startState;
	map<string ,int > nonTerminalIndex;
	map<string ,int > terminalIndex;
	vector<string> tokens;
	stack <string> gStack;
	int row , column;



public:
	Matcher(vector<vector< string > > table , NonTerminal* start , map<string ,int > nonTerminalMap , map<string ,int > terminalMap  , vector<string> t){
		parsingTable = table;
		startState = start;
		nonTerminalIndex = nonTerminalMap;
		terminalIndex = terminalMap;
		tokens = t;
		gStack.push("$");
		gStack.push(start->getName());
		tokens.push_back("$");
	}

	void startMatching(){
		for(int i=0;i<tokens.size();i++){
			matchToken(tokens[i]);
		}
	}

	void matchToken(string token){
		string top = gStack.top();
		gStack.pop();
		if(nonTerminalIndex.find(top) == nonTerminalIndex.end()){ 
			if(token == top ){
				cout << token <<" is Matched "<<endl;

			}
			else{
				matchToken(token);
				return;
			}
		}
		else{
			row = nonTerminalIndex[top];
			column = terminalIndex[token];
			string entry = parsingTable[row][column];
			if(entry.size() == 0){
				cout <<"Error "<<endl;
				gStack.push(top);
				return;
			}
			cout << top << "----> " << entry<<endl;
			if(entry == "epsilon"){
				matchToken(token);
				return;
			}
			else{
				vector<string> split{explode(entry, ' ')};
				for(int i =split.size()-1 ; i>=0;i--){
					gStack.push(split[i]);
				}
				matchToken(token);
				return;
			} 

		}


	}

	const vector<string> explode(const string& s, const char& c)
	{
		string buff{""};
		vector<string> v;
	
		for(auto n:s)
		{
			if(n != c) buff+=n; else
			if(n == c && buff != "") { v.push_back(buff); buff = ""; }
		}
		if(buff != "") v.push_back(buff);
		return v;
}





};