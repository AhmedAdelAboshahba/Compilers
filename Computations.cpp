
#include <map>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <stack>
#include <set>

using namespace std;













class Computations{
private:
	map<string , vector<vector< Grammar* > > > productions;
	map<string , NonTerminal*> pool;
	NonTerminal* startState; 
public:
	Computations(map<string , vector<vector< Grammar*> > > pro , map<string , NonTerminal*> p , NonTerminal* start ){
		productions = pro;
		pool =p;
		startState =	start ;
	}
	void computeFirst(string name){
		NonTerminal* A = pool[name];
		if(A->firstSet.size()!=0)return;
		vector<vector< Grammar*>> rightHand = productions[name];
		for(int i=0;i<rightHand.size();i++){
			Grammar *firstElem= rightHand[i][0];

			if(firstElem->getType() == "terminal") {
				A->firstSet.insert((Terminal*)firstElem);
			}
			else{
				NonTerminal *temp;
				temp = (NonTerminal*)(firstElem);
				computeFirst(temp->getName());
				A->firstSet.insert(temp->firstSet.begin(),temp->firstSet.end());
				
			}
		}
		

	}
	void startComputation(){
		map<string , NonTerminal*>::iterator it;

		for(it=pool.begin();it!=pool.end();it++){
			//cout<<(*it).first<<"---------------------"<<endl;

			computeFirst((*it).first);
		}
		for(it=pool.begin();it!=pool.end();it++){
			computeFollow((*it).first);
		}
	}

	void printFirst(){
		map<string , NonTerminal*>::iterator it;
		for(it=pool.begin();it!=pool.end();it++){
			set<Terminal*> first = (*it).second->firstSet;
			set<Terminal*>::iterator itt;
			cout<<"NonTerminal name is "<<(*it).first<<" My first is   ";
			for(itt=first.begin();itt!=first.end();itt++){
				cout << (*itt)->getName()<<" ";
			}
			cout<<"\n";
			
		}
	}

	void printFollow(){
		map<string , NonTerminal*>::iterator it;
		for(it=pool.begin();it!=pool.end();it++){
			set<Terminal*> follow = (*it).second->followSet;
			set<Terminal*>::iterator itt;
			cout<<"NonTerminal name is "<<(*it).first<<" My follow is   ";
			for(itt=follow.begin();itt!=follow.end();itt++){
				cout << (*itt)->getName()<<" ";
			}
			cout<<"\n";
			
		}
	}

	void computeFollow(string name){
		NonTerminal* A = pool[name];
		if(A->followSet.size() != 0) return;
		Terminal* dollar;
		dollar = new Terminal("$");
		if(A->isStart()){
			 A->followSet.insert(dollar);
		}
			map<string , vector<vector< Grammar* > > >::iterator it;
			for(it=productions.begin();it!=productions.end();it++){
				vector<vector< Grammar* >  > vv=(*it).second;
				for(int i=0;i<vv.size();i++){
					for(int j=0;j<vv[i].size();j++){

						if(vv[i][j]->getName()==name){
							Grammar* temp;
							// Have nothing after it
							if(j==vv[i].size()-1){
								computeFollow((*it).first);
								A->followSet.insert(pool[(*it).first]->followSet.begin(),pool[(*it).first]->followSet.end());
							}
							// followed by a terminal
							else if(vv[i][j+1]->getType() == "terminal"){
								temp = vv[i][j+1];
								A->followSet.insert((Terminal*)temp);

							}
							else{

								temp = vv[i][j+1];
								NonTerminal *temp2;
								temp2 = (NonTerminal*)(temp);
								searchForEpsilon(temp2 , A);
							}
						}
					}
				}
			}


	}


	void searchForEpsilon(NonTerminal* searchIn , NonTerminal* insertIn){
		set<Terminal*>::iterator it;
		for(it = searchIn->firstSet.begin() ;it != searchIn->firstSet.end();it++){

			if((*it)->getName() != "epsilon"){
				insertIn->followSet.insert((*it));
			}
			// first of this non terminal has an epsilon so we need to get it's follow
			else{
				// follow not computed yet
				if(searchIn->followSet.size() == 0){
					computeFollow(searchIn->getName());
				}
				insertIn->followSet.insert(searchIn->followSet.begin() , searchIn->followSet.end());
			}

		}

	}


	void printProductions(){
      map< string , vector< vector < Grammar*> > >::iterator it;
      for(it = productions.begin();it!= productions.end();it++){
        cout << (*it).first <<"=  ";
        for(int i=0;i<(*it).second.size();i++){
            for(int j=0;j<(*it).second[i].size();j++){
              cout << (*it).second[i][j]->getName();
            }
            cout<<"| ";
        }
        cout <<"\n";
      }
   }

   map< string , vector< vector < Grammar*> > > getGrammar(){
      return productions;
   }

   map<string , NonTerminal*> getPool(){
      return pool;
   }

   NonTerminal* getStart(){
   	return startState;
   }

};

/*
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
	pool["E'"] =&EE;
	pool["T"] =&T;
	pool["T'"] =&TT;
	pool["F"] =&F;
	map<string , vector<vector< Grammar*> > > productions;
	vector<vector< Grammar*> > rhs;
	vector<Grammar*> v;
	temp = (Grammar*) &T;
	v.push_back(temp);
	temp = (Grammar*) &EE;
	v.push_back(temp);
	rhs.push_back(v);
	productions["E"] = rhs;
	rhs.clear();
	v.clear();
	temp = (Grammar*) &plus;
	v.push_back(temp);
	temp = (Grammar*) &T;
	v.push_back(temp);
	temp = (Grammar*) &EE;
	v.push_back(temp);
	rhs.push_back(v);
	v.clear();
	temp = (Grammar*) &eps;
	v.push_back(temp);
	rhs.push_back(v);
	productions["E'"] = rhs;




	rhs.clear();
	v.clear();
	temp = (Grammar*) &F;
	v.push_back(temp);
	temp = (Grammar*) &TT;
	v.push_back(temp);
	rhs.push_back(v);
	productions["T"] = rhs;



	rhs.clear();
	v.clear();
	temp = (Grammar*) &as;
	v.push_back(temp);
	temp = (Grammar*) &F;
	v.push_back(temp);
	temp = (Grammar*) &TT;
	v.push_back(temp);
	rhs.push_back(v);
	v.clear();
	temp = (Grammar*) &eps;
	v.push_back(temp);
	rhs.push_back(v);
	productions["T'"] = rhs;


	rhs.clear();
	v.clear();
	temp = (Grammar*) &open;
	v.push_back(temp);
	temp = (Grammar*) &E;
	v.push_back(temp);
	temp = (Grammar*) &closed;
	v.push_back(temp);
	rhs.push_back(v);
	v.clear();
	temp = (Grammar*) &id;
	v.push_back(temp);
	rhs.push_back(v);
	productions["F"] = rhs;








	Computations c(productions , pool);
	c.startComputation();
	c.printFirst();
	c.printFollow();

/*
	set<Terminal*> first = F.first;
			set<Terminal*>::iterator itt;
			cout<<" My first is   ";
			for(itt=first.begin();itt!=first.end();itt++){
				cout << (*itt)->getName()<<" ";
			}
			*/


	
/*
	return 0;
}

*/





/*
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
	pool["E'"] =&EE;
	pool["T"] =&T;
	pool["T'"] =&TT;
	pool["F"] =&F;
	map<string , vector<vector< Grammar*> > > productions;
	vector<vector< Grammar*> > rhs;
	vector<Grammar*> v;





	temp = (Grammar*) &T;
	v.push_back(temp);
	temp = (Grammar*) &EE;
	v.push_back(temp);
	rhs.push_back(v);
	productions["E"] = rhs;




	rhs.clear();
	v.clear();
	temp = (Grammar*) &plus;
	v.push_back(temp);
	temp = (Grammar*) &T;
	v.push_back(temp);
	temp = (Grammar*) &EE;
	v.push_back(temp);
	rhs.push_back(v);
	v.clear();
	temp = (Grammar*) &eps;
	v.push_back(temp);
	rhs.push_back(v);
	productions["E'"] = rhs;




	rhs.clear();
	v.clear();
	temp = (Grammar*) &F;
	v.push_back(temp);
	temp = (Grammar*) &TT;
	v.push_back(temp);
	rhs.push_back(v);
	productions["T"] = rhs;



	rhs.clear();
	v.clear();
	temp = (Grammar*) &as;
	v.push_back(temp);
	temp = (Grammar*) &F;
	v.push_back(temp);
	temp = (Grammar*) &TT;
	v.push_back(temp);
	rhs.push_back(v);
	v.clear();
	temp = (Grammar*) &eps;
	v.push_back(temp);
	rhs.push_back(v);
	productions["T'"] = rhs;


	rhs.clear();
	v.clear();
	temp = (Grammar*) &open;
	v.push_back(temp);
	temp = (Grammar*) &E;
	v.push_back(temp);
	temp = (Grammar*) &closed;
	v.push_back(temp);
	rhs.push_back(v);
	v.clear();
	temp = (Grammar*) &id;
	v.push_back(temp);
	rhs.push_back(v);
	productions["F"] = rhs;








	Computations c(productions , pool);
	c.startComputation();
	c.printFirst();
	c.printFollow();





	return 0;
}
*/


