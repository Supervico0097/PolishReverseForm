#include "polishReverseForm.h"
#include "stackCustom.h"
#include "stackCustom.cpp"
#include <iomanip>
#include<ctype.h>
#include <algorithm>
#include<vector>
#include <fstream>

polishReverseForm::polishReverseForm()
{
    string InputFile;
    cout<<"Please type name of input file: ";
    cin >> InputFile;
    file_.open(InputFile);  //open the file

}

polishReverseForm::~polishReverseForm()
{
    file_.close(); //close the file
}


bool polishReverseForm::isOperator(string token)
{
    for(int i=0; i<5; i++)
    {
        if (operators[i] == token) //if its on the operators vector then return true
        {
            return true;
        }
    }
    return false;
}

bool polishReverseForm::isLeftParenthesis(string token)
{
    if (token == "(" )
        return true;

    return false;
}

bool polishReverseForm::isRightParenthesis(string token)
{
    if (token == ")" )
        return true;

    return false;
}

void polishReverseForm::run()
{
    stackCustom<string> stack1(100);

    if(file_.is_open())
    {
        while(getline(file_, expression))
            { //for every expression in the txt file

            //print first row of table
                cout<<"Input expression: "<< expression<<endl<<endl;

            if(validate()){
                split(); //split tokens

                cout<<setw(20)<<left<<"Token"<<setw(20)<<left<<"Action"<<setw(20)<<left<<"Stack"
                <<setw(20)<<left<<"Output";
                cout<<endl<<endl;

                for (int j= 0; j < input_div.size(); j++)
                    { //start checking the expression


                        if (input_div.at(j)== "" || input_div.at(j) == ",")
                            continue;

                        else if (!isFunctionCall(input_div.at(j)) && input_div.at(j).find('+') == string::npos && input_div.at(j).find('-') == string::npos
                                 && input_div.at(j).find('*') == string::npos && input_div.at(j).find('/') == string::npos && input_div.at(j).find('=') == string::npos
                                 && input_div.at(j).find(')') == string::npos && input_div.at(j).find('(') == string::npos)
                                 { //if it's variable or constant
                                     output.push_back(input_div.at(j));
                                     printTable("Push to output",input_div.at(j) , stack1);
                                 }
                        else if (isFunctionCall(input_div.at(j))){
                            stack1.push(input_div.at(j));
                            printTable("Push to stack",input_div.at(j) , stack1);
                        } //if is a function

                        else if (isOperator(input_div.at(j)))
                        {
                            string current;
                            if (!stack1.isEmptyStack())
                                {
                            current = stack1.top();

                            if (isFunctionCall(current))
                                current = "fun";
                                }

                            while ((!stack1.isEmptyStack()) && ((op_precedence[current] > op_precedence[input_div.at(j)])
                                    || (op_precedence[current] == op_precedence[input_div.at(j)] && op_associativity[input_div.at(j)] == "Left"))
                                    && (!isLeftParenthesis(stack1.top())))
                                    {
                                        output.push_back(stack1.top());
                                        stack1.pop();

                                if (!stack1.isEmptyStack())
                                {
                            current = stack1.top();

                            if (isFunctionCall(current))
                                current = "fun";
                                }

                                  }
                                     stack1.push(input_div.at(j)); //push token into stack
                                     printTable("Push to stack",input_div.at(j) , stack1);

                        } //if its operator

                        else if (isLeftParenthesis(input_div.at(j)))
                        {
                            stack1.push(input_div.at(j)); //push token into stack
                            printTable("Push to stack",input_div.at(j) , stack1);
                        }

                        else if (isRightParenthesis(input_div.at(j)))
                        {
                            while (!isLeftParenthesis(stack1.top()))
                            {
                                output.push_back(stack1.top());
                                stack1.pop();

                            }

                            if (isLeftParenthesis(stack1.top()))
                            {
                                stack1.pop();
                            }

                            if (!stack1.isEmptyStack()){
                                if(isFunctionCall(stack1.top()))
                                {
                                    output.push_back(stack1.top());
                                    stack1.pop();
                                }
                            }


                        }

                    }

                    while (!stack1.isEmptyStack())
                    {
                        output.push_back(stack1.top());
                        stack1.pop();
                    }
                    cout<<endl<<endl;
                    cout<<"Output: ";


                    for (int j= 0; j < output.size(); j++)
                    {

                        cout<<output.at(j)<<" ";

                    }
                    output.clear();
                    functions.clear();
                    cout<<endl<<endl<<endl;
               }
               else
                    cout<<"ERROR: Expression is not a valid expression"<<endl<<endl;
            }
    }
}



void polishReverseForm::split()
{
string expr;
int prev = -1;
input_div.clear(); //clear vector
int start = 0;

for (int i=0; i<expression.length(); i++){

  if ((expression[i] == '+' || expression[i]=='-' || expression[i]=='*' || expression[i]=='/' || expression[i] == '='||
      expression[i] == '(' || expression[i] == ')')) //check if the current char is an operator
    {
        if (expression[i] == '(' && isalpha(expression[i-1])){
                for (int j=i; j<expression.length(); j++){
                    if (expression[j] == ')'){
                        expr = expression.substr(prev+1, j-(j-i)-start);
                        expr=expr+"("+")";
                        remove(expr.begin(), expr.end(), ' '); //remove spaces from the string
                        input_div.push_back(expr); //add functions to input vector
                        functions.push_back(expr);
                        input_div.push_back("(");
                        start = j;

                        for (int z =i+1; z<j; z++)
                        {
                            input_div.push_back(expression.substr(z,1));
                        }
                        i = j-1;
                        break;
                    }

                }
            }

        else
            {

        expr = expression.substr(start, i-start); //save variable
        remove(expr.begin(), expr.end(), ' '); //remove spaces from the string
        input_div.push_back(expr);


        expr = expression.substr(i,1); //save operator
        remove(expr.begin(), expr.end(), ' '); //remove spaces from the string
        input_div.push_back(expr);
        }
        start = i+1;
        prev = i;
    }

}
input_div.push_back(expression.substr(start,expression.size()-start));
}

bool polishReverseForm::isFunctionCall(string token)
{
    for (int j = 0; j< functions.size(); j++){
        if (token == functions.at(j))
            return true;
}
return false;

}

void polishReverseForm::printTable(string action, string token, stackCustom<string> stackCopy) //print outputs
{
                cout<<setw(20)<<left<<token<<setw(20)<<left<<action<<left;

                stackCopy.printStack();

                cout<<setw(20-stackCopy.getStackTop()-(stackCopy.getStackTop()))<<left<<"";



                 for (int j = 0; j< output.size(); j++)
                    {
                    cout<<output.at(j)<<" ";
                    }
                cout<<endl;
                cout<<setw(0);

}

bool polishReverseForm::validate()
{
    for (int i=0; i<expression.length(); i++){
        if (isOperator2(expression[0]) || isOperator2(expression[expression.length() - 1]) //if there is an operator at the beginning or end of the string
            //or two operator after each pther then its not a valid expression
            ||(i>0 && isOperator2(expression[i]) && isOperator2(expression[i-1])))
        {
            return false;
        }
    }
    return true;
}

bool polishReverseForm::isOperator2(char& token)
{
    if (token == '+' || token == '-' || token == '*' || token == '/' || token == '=')
        return true;

    return false;
}

