#include<iostream>
#define nl endl
using namespace std;

class state{
    public:
    string left;
    string right;
    int index_of_operator;
    state(){
        left="";
        right="";
        index_of_operator=0;
    }
};

int index_of_closing_bracket(string part){
    int ct=1;
    int i=0;
    while(ct){
        i++;
        if(part[i]=='('){
            ct++;
        }
        else if(part[i]==')'){
            ct--;
        }
    }
    return i;
}

state seperate(string logic){
    int len = logic.size();
    state ans;
    string logicNew = logic.substr(1,len-2);
    if(logicNew[0]=='(' && logicNew[1]!='~'){
        int i = index_of_closing_bracket(logicNew);
        ans.left = logicNew.substr(0,i+1);
        ans.right = logicNew.substr(i+2);
        ans.index_of_operator=i+2;
        
    }
    else if(logicNew[0]=='(' && logicNew[1]=='~'){
        int i = index_of_closing_bracket(logicNew);
        ans.left = logicNew.substr(1,i-1);
        ans.right = logicNew.substr(i+2);
        ans.index_of_operator=i+2;        
    }
    else if(logicNew[0]=='~' && logicNew[1]!='('){
        ans.left = logicNew.substr(0,2);
        ans.right = logicNew.substr(3);
        ans.index_of_operator=3;
    }
    else{
        ans.left = logicNew.substr(0,1);
        ans.right = logicNew.substr(2);
        ans.index_of_operator=2;
    }
    return ans;  
}



bool check_equal(string a,string b){
    if(a==b){return true;}
    else{return false;}
}

bool andIntroduction(string lines[] , string logic , int lineNum,int pos1,int pos2){
    int l1 = (logic[pos2 + 1]) - '0';   //proper line number
    int l2 = (logic[pos2 + 3]) - '0';   //proper line number

    if(l1<lineNum && l2<lineNum){
        string part1 = lines[l1-1].substr(0,lines[l1-1].find("/"));
        string part2 = lines[l2-1].substr(0,lines[l2-1].find("/"));
        
        if(part2[0]=='~'){
            part2 = "("+part2+")";
        }

        state ans = seperate(logic.substr(0,pos1));
        if(logic[ans.index_of_operator]=='*'){
            if(check_equal(ans.left,part1) && check_equal(ans.right,part2)){return true;}
        }
    }
    return false;
}

bool andElimination1(string lines[] , string logic , int lineNum,int pos1,int pos2){
    int l1 = (logic[pos2 + 1]) - '0';   //proper line number
    string part = lines[l1-1].substr(0,lines[l1-1].find("/"));
    if(l1<lineNum){
        state ans = seperate(part);
        if(part[ans.index_of_operator]=='*'){
            return check_equal(ans.left,logic.substr(0,pos1));
        }
    }
    return false;
}

bool andElimination2(string lines[] , string logic , int lineNum,int pos1,int pos2){
    int l1 = (logic[pos2 + 1]) - '0';
    string part = lines[l1-1].substr(0,lines[l1-1].find("/"));  

    if(l1<lineNum){
        state ans = seperate(part);
        if(part[ans.index_of_operator]=='*'){
            if(part[ans.index_of_operator+2]=='~'){
                int len = ans.right.size();
                ans.right = ans.right.substr(1,len-2);
            }
            return check_equal(ans.right,logic.substr(0,pos1));
        }
    }
    return false;
}

bool orIntroduction1(string lines[] , string logic , int lineNum,int pos1,int pos2){  //not working 
    int l1 = (logic[pos2 + 1]) - '0';
    string part = lines[l1-1].substr(0,lines[l1-1].find("/"));

    if(l1<lineNum){
        state ans = seperate(logic.substr(0,pos1));
        if(logic[ans.index_of_operator]=='+'){
            if(ans.left[1]=='~'){
                int len = ans.left.size();
                ans.left = ans.left.substr(1,len-2);
            }
            return check_equal(ans.left,part);
        }
    }
    return false;
}

bool orIntroduction2(string lines[] , string logic , int lineNum,int pos1,int pos2){
    int l1 = (logic[pos2 + 1]) - '0';
    string part = lines[l1-1].substr(0,lines[l1-1].find("/"));

    if(l1<lineNum){
        state ans = seperate(logic.substr(0,pos1));
        if(logic[ans.index_of_operator]=='+'){
            int len = ans.right.size();
            if(ans.right[1]=='~'){
                ans.right = ans.right.substr(1,len-2);
            }
            return check_equal(ans.right,part);
        }
    }
    return false;
}

bool impliesElimination(string lines[] , string logic , int lineNum,int pos1,int pos2){
    int l1 = (logic[pos2 + 1]) - '0';   //proper line number
    int l2 = (logic[pos2 + 3]) - '0';   //proper line number

    if(l1<lineNum && l2<lineNum){
        string hasImplies = lines[l1-1].substr(0,lines[l1-1].find("/"));
        string part = lines[l2-1].substr(0,lines[l2-1].find("/"));

        state ans = seperate(hasImplies);
        if(hasImplies[ans.index_of_operator]=='>'){
            
            if(ans.left[1]=='~'){
                int len = ans.left.size();
                ans.left = ans.left.substr(1,len-2);
            }         
            if(ans.right[1]=='~'){
                int len = ans.right.size();
                ans.right = ans.right.substr(1,len-2);
            }
            return (check_equal(ans.left,part) && check_equal(ans.right,logic.substr(0,pos1)));
        }
    }
    return false;
}

bool MT(string lines[] , string logic , int lineNum,int pos1,int pos2){
    int l1 = (logic[pos2 + 1]) - '0';   //proper line number
    int l2 = (logic[pos2 + 3]) - '0';   //proper line number

    if(l1<lineNum && l2<lineNum){
        string hasImplies = lines[l1-1].substr(0,lines[l1-1].find("/"));
        string part = lines[l2-1].substr(0,lines[l2-1].find("/"));

        state ans = seperate(hasImplies);
        if(hasImplies[ans.index_of_operator]=='>'){
            if((ans.left).size()==1 || (((ans.left)[0]!='~') && (ans.left)[1]!='~')){
                return(check_equal("~"+ans.right,part) && check_equal("~"+ans.left,logic.substr(0,pos1)));
            }
            else{
                return(check_equal("~"+ans.right,part) && check_equal("~("+ans.left+")",logic.substr(0,pos1)));
            }
        }
    }
    return false;
}
bool checkValid(string lines[] , string logic , int lineNum){

    int pos1 = logic.find("/");
    if(logic[pos1+1]=='P'){
        return true;
    }
    int pos2 = logic.find("/",pos1+1);

    string rule =logic.substr(pos1+1,pos2-pos1-1);

    if(rule=="*i"){ 
        return andIntroduction(lines,logic,lineNum,pos1,pos2);                                                                                                     
    }
    else if(rule=="*e1"){
        return andElimination1(lines,logic,lineNum,pos1,pos2);                                              
    }
    else if(rule=="*e2"){
        return andElimination2(lines,logic,lineNum,pos1,pos2);                                                          
    }
    else if(rule=="+i1"){   
        return orIntroduction1(lines,logic,lineNum,pos1,pos2);                                                         
    }
    else if(rule=="+i2"){
        return orIntroduction2(lines,logic,lineNum,pos1,pos2);
    }
    else if(rule==">e"){
        return impliesElimination(lines,logic,lineNum,pos1,pos2);
    }
    else if(rule=="MT"){
        return MT(lines,logic,lineNum,pos1,pos2);
    }
    else{
        return false;
    }
}

int main(){
    int n;
    cin>>n;
    string lines[n];
    string str;

    for(int i=0;i<n;i++){  
        cin>>str;
        lines[i] = str;
    }

    for(int i=0;i<n;i++){
        if(checkValid(lines,lines[i],i+1)){
            continue;
        }
        else{
            cout<<"Invalid Proof"<<nl;
            return 0;
        }
    }
    cout<<"Valid Proof"<<nl;
}






