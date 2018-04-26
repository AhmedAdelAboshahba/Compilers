
#include "ParsingTable.cpp"
/*
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
*/



class GrammarParser{
	private:
	map<string , vector<vector< Grammar* > > > productions;
	map<string , NonTerminal*> pool;
	public:
	map< string , vector< vector < Grammar*> > > getGrammar(){
      return productions;
    }

    map<string , NonTerminal*> getPool(){
      return pool;
    }	

};