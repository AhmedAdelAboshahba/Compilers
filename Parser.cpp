#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <stack>
 
using namespace std;

class Parser{

	public:
		vector<string> lines;

		string trim(string str)
		{
		    str.erase(0, str.find_first_not_of('\n'));       //prefixing spaces
		    str.erase(str.find_last_not_of('\n')+1);         //surfixing spaces
		    return str;
		}
		void readFile(){
			char buffer[100];
			FILE* file = fopen("grammar.txt","r");
			 if (file == NULL) perror ("Error opening file");
			 else {
			 	while ( ! feof (file) ){
			    	if ( fgets (buffer , 100 , file) == NULL ) break;
			    	string temp(buffer);
			    	temp = trim(temp);

			    	// The grammar hasnot ended yet 
			    	if(temp[0] == '|'){
			    		
			    		lines[lines.size()-1] =lines[lines.size()-1] + temp;
			    	}
			    	else{
			    		lines.push_back(temp);
			    	}
			    	
			    }
			    fclose (file);
			 }

		}


};
class Grammar{
public:
	string type;
};

class Terminal :public Grammar{
private:
	string name;
	
public:
	Terminal(string name){
		name = name;
		type = "terminal";
	}
	string getName(){
		return name;
	}
};

class NonTerminal :public Grammar{
private:
	vector<Terminal> first;
	vector<Terminal> follow;
	string name;
	
public:
	NonTerminal(string name){
		name = name;
		type = "non-terminal";
	}
	string getName(){
		return name;
	}

};

int main(){
		Parser parser;
		parser.readFile();
		for(int i=0;i<parser.lines.size();i++){
			cout<<"Line Number "<<i+1<<": "<<parser.lines[i]<<endl;
		}
		Terminal a("a");
		NonTerminal b("b");
		cout<<a.type<<" "<<b.type;
		return 0;
	}