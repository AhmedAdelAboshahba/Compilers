#include "Grammar.cpp"
#include "Computations.cpp"
#include "llGrammar.cpp"
#include "ParseGrammar.cpp"
#include "ParsingTable.cpp"
#include "Matcher.cpp"

int main(){

  Grammar* temp;
  NonTerminal E("E");
  NonTerminal EE("E'");
  NonTerminal T("T");
  NonTerminal TT("T'");
  NonTerminal F("F");
  Terminal open("(");
  Terminal closed(")");
  Terminal plus("+");
  Terminal as("*");
  Terminal id("id");
  Terminal eps("epsilon");
  E.setStart();
  map<string , NonTerminal*> pool;
  pool["E"] =&E;
 // pool["E'"] =&EE;
  pool["T"] =&T;
  //pool["T'"] =&TT;
  pool["F"] =&F;
  map<string , vector<vector< Grammar*> > > productions;
  vector<vector< Grammar*> > rhs;
  vector<Grammar*> v;
 




  rhs.clear();
  v.clear();
  temp = (Grammar*) &E;
  v.push_back(temp);
  temp = (Grammar*) &plus;
  v.push_back(temp);
   temp = (Grammar*) &T;
  v.push_back(temp);
   rhs.push_back(v);
  v.clear();
    temp = (Grammar*) &T;
  v.push_back(temp);
  rhs.push_back(v);
  productions["E"] = rhs;



  rhs.clear();
  v.clear();
  temp = (Grammar*) &T;
  v.push_back(temp);
  temp = (Grammar*) &as;
  v.push_back(temp);
   temp = (Grammar*) &F;
  v.push_back(temp);
   rhs.push_back(v);
  v.clear();
    temp = (Grammar*) &F;
  v.push_back(temp);
  rhs.push_back(v);
  productions["T"] = rhs;



  rhs.clear();
  v.clear();
  temp = (Grammar*) &id;
  v.push_back(temp);
   rhs.push_back(v);
  v.clear();
   temp = (Grammar*) &open;
  v.push_back(temp);
    temp = (Grammar*) &E;
  v.push_back(temp);
    temp = (Grammar*) &closed;
  v.push_back(temp);
   rhs.push_back(v);
  v.clear();
  productions["F"] = rhs;
  
/*
  GrammarParser gParser;
  LLGrammer l(gParser.getGrammar() , gParser.getPool());

*/


  LLGrammer l(productions , pool , &E);
  l.leftRecursion();
  //l.printProductions();
  Computations c(l.getGrammar() , l.getPool() , l.getStart());
  c.startComputation();
  c.printFirst();
  c.printFollow();

  ParsingTable parser(c.getGrammar() , c.getPool() ,c.getStart());
 

  vector<vector<string>> table =  parser.initMap();

/*
   for(int i=0; i<table.size(); i++){
        for(int j=0; j < table[i].size(); j++){
        	if(table[i][j]==""){
        		cout<<"error ";

        	}
        	else
            cout << table[i][j] <<"  ";
        }
        cout << "\n";
    }
    */


    Matcher matcher(table , parser.getStart() ,parser.getNonTerminalIndex()  , parser.getTerminalIndex() ,  vector<string> {"+","id","+","id"});
    matcher.startMatching();


  //c.printProductions();




  

  return 0;
}
