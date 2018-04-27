#include <map>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <stack>
#include <set>

 
using namespace std;




class LLGrammer{
private:
    map< string , vector< vector < Grammar*> > >modified;
    map<string , NonTerminal*> pool;
    NonTerminal* startState;
public:
     LLGrammer(map< string , vector< vector < Grammar*> > >mod , map<string , NonTerminal*> p , NonTerminal* start ){
        modified=mod;
        pool = p;
        startState = start;
    }
    void leftRecursion(){
       map< string , vector< vector < Grammar*> > >::iterator it;
       for(it=modified.begin();it!=modified.end();it++){

          NonTerminal *temp;
          string snew;
           bool isLL=false;
           vector< vector < Grammar*>  > vnew;
           //cout<<"the size is" <<the size is
           for(int i=0;i<(*it).second.size();i++){
            //cout<<" Error is here ------------------------------- caused by "<<(*it).first <<endl;
              if((*it).second[i][0]->getName()==(*it).first){
               // cout<<" Error is here ------------------------------- caused by "<<(*it).first <<endl;
                isLL=true;
                snew=(*it).first+"'";
                vector<Grammar*>v;
                (*it).second[i].erase((*it).second[i].begin());

                v = ((*it).second[i]);
                (*it).second.erase((*it).second.begin()+i);
                i--;
                
                temp=new NonTerminal (snew);
                v.push_back((Grammar*)(temp));
                vnew.push_back(v);
              }
           }
           if(isLL){
            for(int i=0;i<(*it).second.size();i++){

                (*it).second[i].push_back((Grammar*)(temp));
            }
            Terminal * epsilon;
            epsilon=new Terminal ("epsilon");
             vector<Grammar*>v;
             v.push_back((Grammar*)epsilon);
             vnew.push_back(v);
             modified[snew]=vnew;
             pool[snew]=temp;
           }
       } 
    }


     void eliminate_Left_Recursion (){
        map< string , vector< vector < Grammar*> > >::iterator itout,itin;

        for(itout =modified.begin();itout!=modified.end();itout++){
            for(itin=modified.begin();itin!=itout;itin++){
                for(int i=0;i<(*itout).second.size();i++){
                    for(int j=0;j<(*itout).second[i].size();j++){
                        if((*itout).second[i][j]->getName() == (*itin).first){
                          //cout<<i<<"  "<<j<<endl;
                            (*itout).second[i].erase((*itout).second[i].begin()+j);
                            vector<Grammar*> v1,v2;
                            v1=v2=(*itout).second[i];
                            (*itout).second.erase((*itout).second.begin()+i);
                            for(int k=0;k<(*itin).second.size();k++){
                                vector<Grammar*>::iterator beginit=v1.begin()+j;
                                v1.insert(beginit,(*itin).second[k].begin(),(*itin).second[k].end());
                                (*itout).second.push_back(v1);
                                v1=v2;
                            }
                        }
                    }
                }
            }

        }
    }

    bool detectLeftFactor(){
        map< string , vector< vector < Grammar*> > >::iterator it;
        for(it =modified.begin();it!=modified.end();it++){
            map<string ,int>maap;
            for(int i=0;i<(*it).second.size();i++){
                if(maap.find((*it).second[i][0]->getName()) == maap.end())
                    maap[(*it).second[i][0]->getName()]=1;
                else return true;
            }
        }
        return false;
    }



    map< string , vector< vector < Grammar*> > > getGrammar(){
      return modified;
    }

    map<string , NonTerminal*> getPool(){
      return pool;
    }

   void printProductions(){
      map< string , vector< vector < Grammar*> > >::iterator it;
      for(it = modified.begin();it!= modified.end();it++){
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


   NonTerminal* getStart(){
    return startState;
   }
};

/*
int main (){
  Grammar* temp;
  NonTerminal S("S");
  NonTerminal A("A");
  Terminal a("a");
  Terminal b("b");
  Terminal c("c");
  Terminal d("d");
  Terminal f("f");

  S.setStart();
  map<string , NonTerminal*> pool;
  pool["S"] =&S;
  pool["A"] =&A;
  map<string , vector<vector< Grammar*> > > productions;
  vector<vector< Grammar*> > rhs;
  vector<Grammar*> v;



  temp = (Grammar*) &A;
  v.push_back(temp);
  temp = (Grammar*) &a;
  v.push_back(temp);
  rhs.push_back(v);
  v.clear();
  temp=(Grammar*)&b;
  v.push_back(temp);
  rhs.push_back(v);
  productions["S"] = rhs;

  v.clear();
  rhs.clear();

  temp = (Grammar*) &A;
  //v.push_back(temp);
  temp = (Grammar*) &c;
  v.push_back(temp);
  rhs.push_back(v);
  v.clear();
  temp = (Grammar*) &a;
  v.push_back(temp);
  temp = (Grammar*) &S;
  v.push_back(temp);
  temp=(Grammar*)&d;
  v.push_back(temp);
  rhs.push_back(v);
  v.clear();
  temp = (Grammar*) &f;
  v.push_back(temp);
   rhs.push_back(v);
  productions["A"] = rhs;

 LLGrammer l(productions , pool);
 l.printProductions();
 l.eliminate_Left_Recursion();
  l.printProductions();
  /*Computations c(l.getGrammar() , l.getPool());
  c.startComputation();
  c.printFirst();
  c.printFollow();
  //c.printProductions();

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
  v.clear();
    temp = (Grammar*) &as;
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
  




  LLGrammer l(productions , pool);
  l.leftRecursion();
  l.printProductions();
  Computations c(l.getGrammar() , l.getPool());
  c.startComputation();
  c.printFirst();
  c.printFollow();
  c.printProductions();




  

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







LLGrammer l(productions , pool);
  l.leftRecursion();
  l.printProductions();
  Computations c(l.getGrammar() , l.getPool());
  c.startComputation();
  c.printFirst();
  c.printFollow();
  //c.printProductions();

  return 0;
}
*/