/**

@mainpage Logic Assignment I

@author Aashish Chandra K (2021A7PS0467)
@author Rishabh Patil (2021A7PS0464H)
@author Kaustubh Mahatme (2021A7PS0464H)
@author Tanmay Srivastava (2021A7PS0---H)

Description of the project.
   
*/
#include <iostream>
#include <string.h>
using namespace std;
/*! \file define.h
    \brief testing defines
    
    This is to test the documentation of defines.
*/
/*!
  \def op(x) (x=='+' || x=='*' || x=='>')
  A macro to check whether a character is an operator or not.
*/

/*!
  \def nl '\n'
  Incorporating new-line..
*/

/*!
  \def sp " "
  Incorporating space.
*/
#define op(x) (x=='+' || x=='*' || x=='>') 
#define nl '\n' 
#define sp " " 


int values[26]={0};/**< A global array to store truth values of propositional atoms */

class Node{
    public:
    char data; /*!< Variable storing character operator/operand */
    Node* left; /*!< Left child of Node */
    Node* right; /*!< Right child of Node */
    
    //! A constructor.
    /*!
      A single parameter constructor initizaling data to character argument and left and right children nodes to NULL.
    */
    Node(char ch){
        data=ch;
        left=NULL;right=NULL;
    }
};
/*! \class Node
        \brief A Tree Node.

        A character binary tree node(2 children nodes- left and right) with parent nodes being operators and leaf nodes being operands -> "A Parse Tree". 
    */
    
/*! 
    \fn string infix_to_prefix(string in) 
    \code{.cpp}
        string infix_to_prefix(string in){
            string out="";
            int ind=0,cnt=0;
            for(;ind<in.size();ind++){
                if(op(in[ind]) && cnt==0)break;
                if(in[ind]=='(')cnt++;
                if(in[ind]==')')cnt--;
            }
            if(in.size()==1) 
                return in;
            if(ind==in.size()){
                if(in[0]=='(' && in[in.size()-1]==')')
                    return infix_to_prefix(string(in.begin()+1,in.end()-1));
                else if(in[0]=='~' && in[1]=='(' && in[in.size()-1]==')')
                    return '~' + infix_to_prefix(string(in.begin()+2,in.end()-1));
                else
                    return in;
            }
            out+=in.at(ind);
            if(in[0]=='('&&in[ind-1]==')')
                out += infix_to_prefix(string(in.begin()+1,in.begin()+ind-1));
            else
                out += infix_to_prefix(string(in.begin(),in.begin()+ind));
            if(in[ind+1]=='('&&in[in.size()-1]==')')
                out += infix_to_prefix(string(in.begin()+ind+2,in.end()-1));
            else
                out += infix_to_prefix(string(in.begin()+ind+1,in.end()));
            return out;
        }
    \endcode
    
    \brief \b Solution \b To \b Task \b 1
    \param in Infix Logical statement as Input.
*   \paragraph <-- write algo here and remove the - and >< -->
    \return Returns prefix statement of the given infix string.
 */

string infix_to_prefix(string in){
    string out="";
    int ind=0,cnt=0;
    for(;ind<in.size();ind++){
        if(op(in[ind]) && cnt==0)break;
        if(in[ind]=='(')cnt++;
        if(in[ind]==')')cnt--;
    }
    if(in.size()==1) 
        return in;
    if(ind==in.size()){
        if(in[0]=='(' && in[in.size()-1]==')')
            return infix_to_prefix(string(in.begin()+1,in.end()-1));
        else if(in[0]=='~' && in[1]=='(' && in[in.size()-1]==')')
            return '~' + infix_to_prefix(string(in.begin()+2,in.end()-1));
        else
            return in;
    }
    out+=in.at(ind);
    if(in[0]=='('&&in[ind-1]==')')
        out += infix_to_prefix(string(in.begin()+1,in.begin()+ind-1));
    else
        out += infix_to_prefix(string(in.begin(),in.begin()+ind));
    if(in[ind+1]=='('&&in[in.size()-1]==')')
        out += infix_to_prefix(string(in.begin()+ind+2,in.end()-1));
    else
        out += infix_to_prefix(string(in.begin()+ind+1,in.end()));
    return out;
}

 
/*! 
    \fn Node* prefix_to_tree(string in) 
    \code{.cpp}
        Node* prefix_to_tree(string in){
            Node* root=new Node(in[0]);
            if(op(in[0]))
            {
                int ind=0,cnt=1;
                while(ind<in.size() && (cnt!=0))
                {
                    ind++;
                    //cout<<ind<<sp<<in[ind]<<sp<<cnt<<nl;
                    if(op(in[ind]))cnt++;
                    else if(in[ind]=='~');
                    else cnt--;
                }
                //cout<<string(in.begin()+1,in.begin()+ind+1)<<" === "<<string(in.begin()+ind+1,in.end())<<nl;
                root->left=prefix_to_tree(string(in.begin()+1,in.begin()+ind+1));
                root->right=prefix_to_tree(string(in.begin()+ind+1,in.end()));
            }
            else if(in[0]=='~')
                root->right=prefix_to_tree(string(in.begin()+1,in.end()));
                
            return root;
        }
    \endcode
    
    \brief \b Solution \b To \b Task \b 2
    \param in Prefix String of which the tree is to be made.
*   \paragraph <-- write algo here and remove the - and >< -->
    \return Returns rooted binary Parse Tree of the given prefix string.
 */
Node* prefix_to_tree(string in)
{
    Node* root=new Node(in[0]);
    if(op(in[0]))
    {
        int ind=0,cnt=1;
        while(ind<in.size() && (cnt!=0))
        {
            ind++;
            //cout<<ind<<sp<<in[ind]<<sp<<cnt<<nl;
            if(op(in[ind]))cnt++;
            else if(in[ind]=='~');
            else cnt--;
        }
        //cout<<string(in.begin()+1,in.begin()+ind+1)<<" === "<<string(in.begin()+ind+1,in.end())<<nl;
        root->left=prefix_to_tree(string(in.begin()+1,in.begin()+ind+1));
        root->right=prefix_to_tree(string(in.begin()+ind+1,in.end()));
    }
    else if(in[0]=='~')
        root->right=prefix_to_tree(string(in.begin()+1,in.end()));
        
    return root;
}
/*! 
    \fn string inorder(Node* root) 
    \code{.cpp}
        string inorder(Node* root){
            if(root)
                return inorder(root->left)+ root->data +inorder(root->right);
            else
                return "";
        }
    \endcode
    
    \brief \b Solution \b To \b Task \b 3
    \param root ?whatisroot?.
   \paragraph <-- write algo here and remove the - and >< -->
    \return Returns inorder traversal of the parse tree.
 */
string inorder(Node* root)
{
    if(root)
        return inorder(root->left)+ root->data +inorder(root->right);
    else
        return "";
}
/*! 
    \fn int height(Node* root) 
    \code{.cpp}
        int height(Node* root)
        {
            if(root)
                return 1+max(height(root->left),height(root->right));
            else
                return 0;
        }
    \endcode
    
    \brief \b Solution \b To \b Task \b 3
    \param root ?whatisroot?.
   \paragraph <-- write algo here and remove the - and >< -->
    \return Height of the parse tree.
 */
int height(Node* root)
{
    if(root)
        return 1+max(height(root->left),height(root->right));
    else
        return 0;
}
/*! 
    \fn bool value(Node* root) 
    \code{.cpp}
        bool value(Node* root)
        {
            switch(root->data)
            {
                case '+': return value(root->left)||value(root->right);
                case '*': return value(root->left)&&value(root->right);
                case '>': return !value(root->left)||value(root->right);
                case '~': return !value(root->right);
                default: return values[root->data-'a'];
            }
        }

    \endcode
    
    \brief \b Solution \b To \b Task \b 3
    \param root ?whatisroot?.
   \paragraph <-- write algo here and remove the - and >< -->
    \return Height of the parse tree.
 */
bool value(Node* root)
    {
        switch(root->data)
        {
            case '+': return value(root->left)||value(root->right);
            case '*': return value(root->left)&&value(root->right);
            case '>': return !value(root->left)||value(root->right);
            case '~': return !value(root->right);
            default: return values[root->data-'a'];
        }
    }

int main()
{
    cout<<"\n\nIMPLEMENTING PARSE TREE:"<<nl;
    string k= "p";
    cout<<"\nPLEASE ENTER A WELL-DEFINED INFIX EXPRESSION : ";
    cin>>k;

    cout<<"\nThe Prefix Logical expression for the given input is :";
    cout<<infix_to_prefix(k)<<nl;
    Node* root = prefix_to_tree(infix_to_prefix(k));
    cout<<"\n A parse Tree has been successfully created.\n";
    //auto start1 = chrono::steady_clock::now();
    //auto finish1 = chrono::steady_clock::now();
    //double elapsed_time1 = double(chrono::duration_cast<chrono::nanoseconds>(finish1-start1).count());
    //cout <<"task1: "<< elapsed_time1 << "ns\n";

    cout<<"\nThe inorder traversal(infix) of the Parse tree is: ";
    cout<<inorder(root)<<nl;
    cout<<"\nThe Height of the Parse tree is: ";
    cout<<height(root)<<nl;

    int count=0;
    cout<<"\nEnter the number of propositional atoms which are true : "<<nl;
    cin>>count;
    cout<<"\nPlease enter all the propositional atoms which are true: \n";
    while(count--)
    {   
        char ch; cin>>ch;
        values[ch-'a']++;
    }
    cout<<"The truth value of the given logical expression under these premises is: ";
    cout<<value(root)<<nl<<nl;
    return 0;
}
