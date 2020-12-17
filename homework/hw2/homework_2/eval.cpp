#include <iostream>
#include <string>
#include <stack>
#include <cassert>
using namespace std;//lines you need

//declarations of any additional functions you might have written
//to help you evaluate an expression
int precedence(char ch);
bool infixToPostfix(string infix, string& postfix);
bool postfixEval(string postfix);

int evaluate(string infix, string& postfix, bool& result)
{
    if(!infixToPostfix( infix , postfix )) // if its not valid return 1
    {
        return 1;
    }
    result = postfixEval(postfix);
    return 0;
}

int precedence(char ch)
{
    switch (ch)
    {
        case '!':
            return 3;
        case '&':
            return 2;
        case '^':
            return 1;
        default:
            exit(1);
    }
}

bool infixToPostfix(string infix, string& postfix)
{
    postfix = "";
    stack<char> operStack;
    
    //remove spaces
    string noSpaceInfix = "";
    for(int i = 0; i < infix.size(); i++)
    {
        if(infix[i] == ' ')
        {
            continue;
        }
        noSpaceInfix += infix[i];
    }
    infix = noSpaceInfix;
    
    //check if it is empty string
    if(infix == "")
    {
        //        cerr << "empty infix" << endl;
        return false;
    }
    
    //check begining
    switch (infix[0])
    {
        case '^':
        case '&':
//            cerr << "bad symbol at begining" << endl;
            return false;
        default:
            break;
    }
    //check end
    switch (infix[infix.size() - 1])
    {
        case '^':
        case '&':
        case '!':
        case '(':
//            cerr << "bad symbol at end" << endl;
            return false;
        default:
            break;
    }
    //check all infix characters and convert
    size_t sizeInfix = infix.size();
    for(int i = 0; i < sizeInfix; i++)
    {
        char ch = infix[i];
        switch (ch)
        {
            case 'T':
            case 'F':
                if(i + 1 < sizeInfix)
                {
                    switch (infix[i+1])
                        {
                            case 'T':
                            case 'F':
                            case '(':
                            case '!':
//                                cerr << "wrong symbol after T or F" << endl;
                                return false;
                            default:
                                break;
                        }
                }
                postfix += ch;
                break;
                
            case '(':
            case '!':
                if(i+1 < sizeInfix)
                {
                    switch (infix[i+1])
                    {
                        case ')':
                        case '&':
                        case '^':
//                            cerr << "wrong symbol after " << ch << endl;
                            return false;
                        default:
                            break;
                    }
                }
                
                operStack.push(ch);
                break;
                
            case ')':
                if(i+1 < sizeInfix)
                {
                    switch (infix[i+1])
                    {
                        case 'T':
                        case 'F':
                        case '(':
//                            cerr << "wrong symbol after )" << endl;
                            return false;
                        default:
                            break;
                    }
                }
                while(!operStack.empty() && operStack.top() != '(')
                {
                    postfix += operStack.top();
                    operStack.pop();
                }
                if(operStack.empty())
                {
//                    cerr << "wrong direction of paren" << endl;
                    return false;
                }
                operStack.pop();
                break;
            case '^':
            case '&':
                if(i+1 < sizeInfix)
                {
                    switch (infix[i+1])
                    {
                        case '&':
                        case '^':
                        case ')':
//                            cerr << "wrong symbol after " << ch << endl;
                            return false;
                        default:
                            break;
                    }
                }
                
                while(!operStack.empty() &&
                      operStack.top() != '(' &&
                      precedence(ch) <= precedence(operStack.top())) //^ << & << !
                {
                    postfix += operStack.top();
                    operStack.pop();
                }
                operStack.push(ch);
                break;
            default:
//                cerr << "bad symbol" << endl;
                return false;
        }
    }
    //check if there are any operators left in the stack
    while(!operStack.empty())
    {
        //if they are () return false
        if(operStack.top() == '(' || operStack.top() == ')')
        {
//            cerr << "wrong ammt of paren" << endl;
            return false;
        }
        postfix += operStack.top();
        operStack.pop();
    }
    return true;
}

bool postfixEval(string postfix)
{
    stack<bool> operStack;

    size_t sizePost = postfix.size();
    for(int i = 0; i < sizePost; i++)
    {

        char ch = postfix[i];
        if (ch == 'T' || ch == 'F')
        {
            switch (ch)
            {
                case 'T':
                    operStack.push(true);
                    break;
                case 'F':
                    operStack.push(false);
                    break;
            }
        }
        else if (ch == '&' || ch == '^')
        {
            bool operand2 = operStack.top();
            operStack.pop();
            bool operand1 = operStack.top();
            operStack.pop();
            switch (ch) {
                case '&':
                    operStack.push(operand1 & operand2);
                    break;
                case '^':
                    operStack.push(operand1 ^ operand2);
                    break;
            }
        }
        else if (ch == '!')
        {
            bool operTop = operStack.top();
            operStack.pop();
            operStack.push(!operTop);
        }
        else
        {
            exit(1);
        }
    }
    return operStack.top();
}

int main()
{
    string pf;
    bool answer;
    assert(evaluate("T^ F", pf, answer) == 0  &&  pf == "TF^"  &&  answer);
    assert(evaluate("T^", pf, answer) == 1);
    assert(evaluate("F F", pf, answer) == 1);
    assert(evaluate("TF", pf, answer) == 1);
    assert(evaluate("()", pf, answer) == 1);
    assert(evaluate("()T", pf, answer) == 1);
    assert(evaluate("T(F^T)", pf, answer) == 1);
    assert(evaluate("T(&T)", pf, answer) == 1);
    assert(evaluate("(T&(F^F)", pf, answer) == 1);
    assert(evaluate("T&(F^F))", pf, answer) == 1);
    assert(evaluate("T&(F^F)", pf, answer) == 0 && !answer && pf == "TFF^&");

    assert(evaluate("     T   &     (    F   ^   F   )   " , pf, answer) == 0 && !answer && pf == "TFF^&");
    assert(evaluate("T&(F^(T^(F&T)))", pf, answer) == 0 && answer && pf == "TFTFT&^^&");
    assert(evaluate("!T&(F^(T^(F&T)))", pf, answer) == 0 && !answer && pf == "T!FTFT&^^&");
    assert(evaluate("!T&!(T^F)", pf, answer) == 0 && !answer && pf == "T!TF^!&");
    assert(evaluate("((T))", pf, answer) == 0 && answer && pf == "T");
    assert(evaluate("((F))", pf, answer) == 0 && !answer && pf == "F");

    assert(evaluate("(!)", pf, answer) == 1);
    assert(evaluate("(^)", pf, answer) == 1);
    assert(evaluate("(&)", pf, answer) == 1);
    assert(evaluate("(T!)", pf, answer) == 1);
    assert(evaluate("(T^)", pf, answer) == 1);
    assert(evaluate("(T&)", pf, answer) == 1);
    assert(evaluate("(&T)", pf, answer) == 1);
    assert(evaluate("(^T)", pf, answer) == 1);
    assert(evaluate("((T)", pf, answer) == 1);
    assert(evaluate("(T))", pf, answer) == 1);

    assert(evaluate("T|F", pf, answer) == 1);
    assert(evaluate("", pf, answer) == 1);
    assert(evaluate("    ", pf, answer) == 1);
    assert(evaluate("!", pf, answer) == 1);
    assert(evaluate("^", pf, answer) == 1);
    assert(evaluate("&", pf, answer) == 1);
    assert(evaluate("TF", pf, answer) == 1);
    assert(evaluate("FT", pf, answer) == 1);

    assert(evaluate("F  ^  !F & (T&F) ", pf, answer) == 0 &&  pf == "FF!TF&&^"  &&  !answer);
    assert(evaluate(" F  ", pf, answer) == 0 &&  pf == "F"  &&  !answer);
    assert(evaluate("((T))", pf, answer) == 0 &&  pf == "T"  &&  answer);
//    cout << "Passed all my tests" << endl;

    //testing for bad infix
    assert(evaluate("", pf, answer) == 1);
    assert(evaluate("(sdf)", pf, answer) == 1);
    assert(evaluate("()sdf", pf, answer) == 1);
    assert(evaluate("!", pf, answer) == 1);
    assert(evaluate("(", pf, answer) == 1);
    assert(evaluate("!!!", pf, answer) == 1);
    assert(evaluate("TF", pf, answer) == 1);
    assert(evaluate("T(F", pf, answer) == 1);
    assert(evaluate("T(F)", pf, answer) == 1);
    assert(evaluate("()()", pf, answer) == 1);
    assert(evaluate("&!", pf, answer) == 1);
    assert(evaluate("^!", pf, answer) == 1);
    assert(evaluate("&()", pf, answer) == 1);
    assert(evaluate("!()", pf, answer) == 1);
    assert(evaluate("F && F", pf, answer) == 1);
    //checking evaluate for valid infix
    assert(evaluate("T", pf, answer) == 0);
    assert(evaluate("!T", pf, answer) == 0);
    assert(evaluate("(!(T))", pf, answer) == 0);
    assert(evaluate("!(((T&F)))", pf, answer) == 0);
    assert(evaluate("!T", pf, answer) == 0);
    assert(evaluate("!( T & !F ^ T)", pf, answer) == 0);
    assert(evaluate("T & !!F", pf, answer) == 0);
    assert(evaluate("F", pf, answer) == 0);
    //testing random stuff
    assert(evaluate("T", pf, answer) == 0 && pf == "T" && answer);
    assert(evaluate("(!(T))", pf, answer) == 0 && pf == "T!" && !answer);
    assert(evaluate("!(((T&F)))", pf, answer) == 0 && pf == "TF&!" && answer);
    assert(evaluate("!T", pf, answer) == 0 && pf == "T!" && !answer);

    assert(evaluate("F", pf, answer) == 0 && pf == "F" && !answer);
    assert(evaluate("!(T&!F) ^!T& !F", pf, answer) == 0 && pf == "TF!&!T!F!&^" && !answer);

    assert(infixToPostfix("!!!!T", pf) == 1 && pf == "T!!!!");
    assert(evaluate("!!!!T", pf, answer) == 0 && pf == "T!!!!" && answer);
    assert(evaluate("!!T", pf, answer) == 0);
    assert(evaluate("!!!!T", pf, answer) == 0);
    assert(evaluate("!!(T) & !F ^ T", pf, answer) == 0);
    assert(evaluate("!!!!T", pf, answer) == 0 && pf == "T!!!!" && answer);
    assert(evaluate("T & !!F", pf, answer) == 0 && pf == "TF!!&" && !answer);
    
    assert(evaluate("!( T & !F ^ T)", pf, answer) == 0 && pf == "TF!&T^!" && answer);
    //TF!&T^!
    //TT&T^!
    //TT^!
    //F!
    //T
    assert(evaluate("!!( T & !F ^ T)", pf, answer) == 0 && pf == "TF!&T^!!" && !answer);
    assert(evaluate("!!!( T & !F ^ T)", pf, answer) == 0 && pf == "TF!&T^!!!" && answer);

    assert(evaluate("!!(T) & !F ^ T", pf, answer) == 0 && pf == "T!!F!&T^" && !answer);
    //T!!F!&T^
    //F!F!&T^
    //TF!&T^
    //TT&T^
    //TT^
    //F
    
    assert(evaluate("(T&T)(T&T)", pf, answer) == 1);
    assert(evaluate("T!T", pf, answer) == 1);

    cout << "Passed all tests" << endl;
}
