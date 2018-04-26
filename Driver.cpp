
#include "ParseGrammar.cpp"

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


  LLGrammer l(productions , pool);
  l.leftRecursion();
  //l.printProductions();
  Computations c(l.getGrammar() , l.getPool());
  c.startComputation();
  c.printFirst();
  c.printFollow();

  ParsingTable parser;
 

  vector<vector<string>> table =  parser.initMap(c.getGrammar() , c.getPool());


   for(int i=0; i<table.size(); i++){
        for(int j=0; j < table[i].size(); j++){
            cout << table[i][j];
        }
        cout << "\n";
    }


  //c.printProductions();




  

  return 0;
}
