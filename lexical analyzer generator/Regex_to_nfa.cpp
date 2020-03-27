#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <utility>
#include <unordered_map>
#include "Nfa.cpp"

using namespace std;









class regex_to_nfa{
private :
vector<unordered_map<char, string>> all_states;
unordered_map<string, pair<int, int>> NFAs;
vector<string> rule_sep;
unordered_map<string, pair<int, int>> priority;
Nfa *obj;
public:
    regex_to_nfa(string file_name){
        obj = new Nfa(all_states);
        parse_rules(file_name);

    }
    void parse_rules(string file_name){
        // storing the rules line by line
    //___________________________________
    ifstream ip_file(file_name);
    string rules;
    string line;
    while (getline (ip_file, line)) {
        rules += line;
        rules += "||";
     }
     // Close the file
     ip_file.close();
     vector<string> lines;
     size_t pos = 0;
     std::string token;
     while ((pos = rules.find("||")) != std::string::npos) {
         token = rules.substr(0, pos);
         if(token == "\\L"){
            token = ' ';
         }
         lines.push_back(token);
         rules.erase(0, pos + 2);
     }
     /*
     for(int counter1 =0 ;counter1<lines.size();counter1++){
            cout<<lines[counter1]<<endl;

     }
*/



unordered_map<char, string> state0 ;
        state0[' ']="0";
        all_states.push_back(state0);
int priority_num =1;

     ///the main loop that loops on each rule
     ///and perform the main algorithm on all lines
     for (int i = 0; i < lines.size(); i++){



        ///for each line
        for(int count =0 ; count < lines[i].size();count++){
            string token ;

            char c = lines[i].at(count);
            if(isalpha(c)){
            while(count < lines[i].size() && isalnum(c)){
                    token +=c;
                    count++;
                    if(count < lines[i].size()){
                    c = lines[i].at(count);
                    }

            }
            rule_sep.push_back(token);
            count--;
            }else if(!isspace(c)){
                token +=c;

                if(c == '\\'){
                    count++;
                    c = lines[i].at(count);
                    token +=c;

                }
                rule_sep.push_back(token);
            }




        }
/*
        for(int cnt=0;cnt<rule_sep.size();cnt++){
            cout <<cnt<<rule_sep[cnt]<<endl;
        }
*/


        if(rule_sep[0] =="[" || rule_sep[0] =="{"){// keywords and symbols
            for(int cnt=1;cnt<rule_sep.size()-1;cnt++){
                    pair<int,int> result = create_NFA(rule_sep[cnt]);
                    pair<int,int> pir ;
                    ///adjust priority
                    removeCharsFromString(rule_sep[cnt],"\\");
                    NFAs[rule_sep[cnt]]=result;
                    pir.first = 0;
                    pir.second = result.second;
                    priority[rule_sep[cnt]] =pir;
                    /*cout << "hereeee" << result.first <<endl;*/
                    unordered_map<char, string> &state0 = all_states[0];
                    string s = state0[' '] + ","+to_string(result.first);
                    state0[' '] = s;
            }
        }else{// expressions and definitions
        pair<int,int> result ;
        pair<int,int> pir ;
        ///are these necessary ?
        ///extract the id
        ///add start state = the vector size
        ///make the zero state goes to this state
        ///int first = num of the added start state
        result = process_exp(rule_sep,true);
        /*cout << result.first << " " << result.second <<endl;*/
        unordered_map<char, string> &state0 = all_states[0];
        state0[' '] += ","+to_string(result.first);
        NFAs[rule_sep[0]]=result;
                    pir.first = priority_num;
                    priority_num++;
                    pir.second = result.second;
                    priority[rule_sep[0]] =pir;
        ///make the first state above goes ro the first state of the result and the end state is the same


        }
        /*cout << state0[' '] << endl;*/
        rule_sep.clear();

     }

        unordered_map<string, pair <int,int>>:: iterator itr;
     for (itr = NFAs.begin(); itr != NFAs.end(); itr++)
    {
        pair <int,int> pr = itr->second;
        cout << itr->first << "  " << pr.first << " " <<pr.second << endl;

     }

    /* for(int i = 0 ; i < all_states.size(); i++){
        unordered_map<char,string> curr = all_states[i];
        cout << "state" <<i <<endl;
            unordered_map<char,string>:: iterator itr2;
            for (itr2 = curr.begin(); itr2 != curr.end(); itr2++){
                cout << itr2->first << " ---->> " << itr2->second <<endl;
            }
     }*/
cout<<"________________________________________________________"<<endl;
     unordered_map<string, pair <int,int>>:: iterator itr3;
     for (itr3 = priority.begin(); itr3 != priority.end(); itr3++)
    {
        pair <int,int> pr = itr3->second;
        cout << itr3->first << "  " << pr.first << " " <<pr.second << endl;

     }

    }

    pair<int,int> create_NFA(string s){
    pair<int,int> result;
    result.first = all_states.size();

    int counter =0;
    for(counter;counter < s.size();counter++){
            char curr = s.at(counter);
            unordered_map<char, string> state ;
            state[curr] =to_string(all_states.size()+1);
            all_states.push_back(state);


    }
    unordered_map<char, string> f_state ;
    f_state[' ']=to_string(all_states.size());
    result.second = all_states.size();
    all_states.push_back(f_state);
    return result;
}
pair<int,int> process_exp(vector<string> exp , bool f){
            pair<int,int> first;
            pair<int,int> result;
            pair<int,int> old_result;
            bool flag = false;
            int ors=0;
    for(int counter1 =2 ; counter1 < exp.size();counter1++){
            string token = exp[counter1];




        ///case of 2 successive tokens (conc)
         if(token != "+" && token != "-" && token != "*" && token != "|" ){//operand
                if(token == "("){
                        vector<string> temp ;
                        temp.push_back("empt1");
                        temp.push_back("empt2");
                        int cnt =0;
                        counter1++;
                        while(exp[counter1] != ")" || cnt != 0){
                                if(exp[counter1] == "("){
                                    cnt++;
                                }
                                if(exp[counter1] == ")"){
                                    cnt--;
                                }
                            temp.push_back(exp[counter1]);
                            counter1++;
                        }
                        first = process_exp(temp,true);



                }else{
                    /// case of range is detected first bec it's different
                    if(counter1+1 < exp.size() && exp[counter1+1] == "-"){
                    char a = token.at(0);
                    char b = exp[counter1+2].at(0);
                    first = obj->reg_nfa_op5(a,b);
                    counter1+=2;
                }else if(NFAs.find(token) != NFAs.end()){
                first = NFAs[token];
                }else{ // not there
                removeCharsFromString(token,"\\");
                first = create_NFA(token);
                }
                }

                if(counter1+1 < exp.size()&&exp[counter1+1] == "*"){
                    first = obj->reg_nfa_op3(first);
                }else if(counter1+1 < exp.size()&&exp[counter1+1] == "+"){
                    first = obj->reg_nfa_op4(first);
                }

                if(f || flag){//first token
                    result = first;
                }else{
                    if(flag){
                        result = obj->reg_nfa_op1(result,first);
                    }else{
                        result = obj->reg_nfa_op2(result,first);
                    }
                }

                }
                if(token == "|"){
                    flag = true;
                    if(ors ==0){
                    old_result = result;
                    }else{
                        old_result=  obj->reg_nfa_op1(result,old_result);
                    }
                    ors++;
                }else{
                    flag = false;
                }
                f = false;


    }
    if(ors >0){
    result = obj->reg_nfa_op1(result,old_result);
    }
    return result;
}

void removeCharsFromString( string &str, char* charsToRemove ) {
   for ( unsigned int i = 0; i < strlen(charsToRemove); ++i ) {
      str.erase( remove(str.begin(), str.end(), charsToRemove[i]), str.end() );
   }
}

};






/**
 * we still need to adjust the algorithm so it doesn't execute from a main
 * so that we can use it in the upcoming phase , also the file name should
 * be taken as a param
 */
int main()
{




        regex_to_nfa("lex_rules_ip.txt");


     /*
     unordered_map<char, string> &s_zer0 = all_states[0];
     cout << s_zer0[' '] << endl;
     cout << state0[' '] << endl;
     s_zer0 = state0;
     cout << s_zer0[' '] << endl;
     */

/*
    for(int counter =0 ; counter < all_states.size();counter++){
        unordered_map<char, string> s_zer0 = all_states[counter];
        cout << s_zer0[' '] << endl;
    }*/
    return 0;
}
// creates an nda for the key words or symbol or any undefined char
