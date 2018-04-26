#include <map>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <stack>
#include <set>
 
using namespace std;

class Grammar{
public:
	virtual string getType() =0;
	virtual string getName () =0;

};

class Terminal :public Grammar{
private:
	string name;
	string type;
	
public:
	Terminal(string namee){
		name = namee;
		type = "terminal";
	}
	string getName(){
		return name;
	}
	string getType(){
		return type;
	}

};

class NonTerminal :public Grammar{
private:
	string name;
	string type;
	bool start;
	
public:
	NonTerminal(string namee ){
		name = namee;
		type = "non-terminal";
		start = false;
	}
	string getName(){
		return name;
	}
	string getType(){
		return type;
	}
	bool isStart(){
		return start;
	}
	void setStart(){
		start = true;
	}

	set<Terminal*> firstSet;
	set<Terminal*> followSet;

};