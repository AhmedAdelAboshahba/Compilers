#include <map>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <stack>
#include <set>




class ParsingTable{
private:
    map<string, int> allTerminals;
    map<string, int> nonTerminals;
    map<string , vector<vector< Grammar* > > > myMap;
    map<string , NonTerminal*> pool;
    NonTerminal* startState;
public:
    ParsingTable(map<string , vector<vector< Grammar*> > > pro , map<string , NonTerminal*> p , NonTerminal* start){
        myMap = pro;
        pool =p;
        startState =    start ;
    }
    map<string, int> getTerminals(map<string, vector<vector<Grammar *>>> &myMap) {
        map<string, int> allTerminals;
        int index = 0;
        for (map<string, vector<vector<Grammar *>>>::iterator it = myMap.begin(); it != myMap.end(); ++it) {
            for (int i = 0; i < it->second.size(); i++) {
                for (int j = 0; j < it->second[i].size(); j++) {
                    if (it->second[i][j]->getType() == "terminal" && allTerminals.find(it->second[i][j]->getName())==allTerminals.end()) {
                        allTerminals.insert(pair<string, int>(it->second[i][j]->getName(), index));
                        index++;
                    }
                }
            }
        }
        allTerminals.insert(pair<string, int>("$", index));
        return allTerminals;
    }

    void addEmptyRowInParseTable(vector<vector<string>> &parseTable, int size) {
        vector<string> temp;// return object
        for (int i = 0; i < size; i++) {
            temp.push_back("");
        }
        parseTable.push_back(temp);

    }
    void fillSynch(map<string, vector<vector<Grammar *>>> myMap,vector<vector<string>> &parseTable,map<string, int > nonTerminals,map<string, int> terminals, map<string, NonTerminal *> pool){
        for (map<string, vector<vector<Grammar *>>>::iterator it = myMap.begin(); it != myMap.end(); ++it) {
            string nonTerminalName=it->first;
            int row=nonTerminals[nonTerminalName];
            set<Terminal*> followTemp=pool[nonTerminalName]->followSet;
            for (set<Terminal *>::iterator itFollow = followTemp.begin();itFollow != followTemp.end(); itFollow++) {
                string terminalName = (*itFollow)->getName();
                int col=terminals[terminalName];
                if(parseTable[row][col]==""){
                    parseTable[row][col]="synch";
                }
            }
        }
    }
    void writeProduction(vector<vector<string>> &parseTable, vector<Grammar *> production, int row, int col) {
        for (int i = 0; i < production.size(); i++) {
            parseTable[row][col] += production[i]->getName();
            parseTable[row][col] +=" ";
        }
    }

    vector<vector<string>> initMap() {
        cout<<"fady"<<endl;
        for (map<string, vector<vector<Grammar *>>>::iterator it = myMap.begin(); it != myMap.end(); ++it) {
            cout << it->first << endl;
            for (int j = 0; j < it->second.size(); j++) {
                for (int i = 0; i < it->second[j].size(); i++) {
                    cout << it->second[j][i]->getName() << " " << it->second[j][i]->getType() << endl;
                }
                cout << "new prod"<<endl;
            }
        }
        cout<<"mark"<<endl;
        vector<vector<string>> parseTable;
        allTerminals = getTerminals(myMap);
        int indexForNonTerminals = 0;


        for (map<string, vector<vector<Grammar *>>>::iterator it = myMap.begin(); it != myMap.end(); ++it) {
            nonTerminals.insert(pair<string, int>(it->first, indexForNonTerminals));
            addEmptyRowInParseTable(parseTable, allTerminals.size());
            for (int i = 0; i < it->second.size(); i++) {
                cout << it->second[i][0]->getName()<<endl;
                if (it->second[i][0]->getType() == "terminal") {

                    if (it->second[i][0]->getName() == "epsilon") { //special case
                        NonTerminal *leftHand = pool[it->first];
                        set<Terminal *> followTemp = leftHand->followSet;  // check pointers
                        for (set<Terminal *>::iterator itFollow = followTemp.begin();itFollow != followTemp.end(); itFollow++) {
                            string temp = (*itFollow)->getName();
                            int ind = allTerminals[temp];
                            vector<Grammar *> t;
                            t.push_back(it->second[i][0]);
                            cout << it->second[i][0]->getName()<<endl;
                            for(int k = 0; k<t.size(); k++){
                                cout << t[k]->getName() <<endl;
                            }
                            writeProduction(parseTable, t, indexForNonTerminals, ind);

                        }
                    }
                    else {
                        int ind = allTerminals[it->second[i][0]->getName()];
                        writeProduction(parseTable, it->second[i], indexForNonTerminals, ind);
                    }
                } else {
                    bool isEpsilon = false;
                    NonTerminal* temp;
                    temp = (NonTerminal*)(it->second[i][0]);

                    set<Terminal *> firstTemp = temp->firstSet;

                    for (set<Terminal *>::iterator itFirst = firstTemp.begin(); itFirst != firstTemp.end(); itFirst++) {
                        string temp = (*itFirst)->getName();
                        if (temp == "epsilon") {
                            isEpsilon = true;
                        }
                    }
                    if (isEpsilon) { // get by follow // need use pool function
                        NonTerminal *leftHand = pool[it->first];
                        set<Terminal *> followTemp = leftHand->followSet;  // check pointers
                        for (set<Terminal *>::iterator itFollow = followTemp.begin();
                             itFollow != followTemp.end(); itFollow++) {
                            string temp = (*itFollow)->getName();
                            int ind = allTerminals[temp];
                            //parseTable[indexForNonTerminals][ind] += it->second[i][0]->getName();
                            writeProduction(parseTable, it->second[i], indexForNonTerminals, ind);
                        }
                    } else { // get by first
                        for (set<Terminal *>::iterator itFirst = firstTemp.begin(); itFirst != firstTemp.end(); itFirst++) {
                            string temp = (*itFirst)->getName();
                            int ind = allTerminals[temp];
                            writeProduction(parseTable, it->second[i], indexForNonTerminals, ind);
                        }
                    }
                }
            }
            indexForNonTerminals++;
        }
        fillSynch(myMap,parseTable,nonTerminals,allTerminals,pool);
        return  parseTable;
    }
    map<string, int> getTerminalIndex (){
        return allTerminals;
    }
    map<string, int> getNonTerminalIndex (){
        return nonTerminals;
    }

    NonTerminal* getStart(){
    return startState;
   }

};


/*int main(){

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

    vector<vector<string>> table = initMap(productions, pool);

    for(int i=0; i<table.size(); i++){
        for(int j=0; j < table[i].size(); j++){
            cout << table[i][j];
        }
        cout << "\n";
    }

    return 0;
}
*/