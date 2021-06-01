#ifndef POLISHREVERSEFORM_H
#define POLISHREVERSEFORM_H
#include <fstream>
#include "stackCustom.h"
#include<string>
#include<vector>
#include <map>

using namespace std;

class polishReverseForm
{
    private:
        ifstream file_;
        string expression;
        const string operators[5] = { "+", "-", "*", "/", "=" };
        vector<string> input_div;
        vector<string> output;    //queue which will save the output expression
        vector<string> functions;    //vector to store functions names
        map<string, int> op_precedence = {  //map of operators and thier precedence
                                        {"fun", 15},
                                        {"*", 10},
                                        {"/", 10},
                                        {"+", 5},
                                        {"-", 5},
                                        {"=", 0}
                                        };

        map<string, string> op_associativity = {  //map of operators and thier precedence
                                            {"fun", "Left"},
                                            {"*", "Left"},
                                            {"/", "Left"},
                                            {"+", "Left"},
                                            {"-", "Left"},
                                            {"=", "Right"}
                                            };

        void split(); //split the string into tokens and insert it into vector
        bool isFunctionCall(string token); //returns true if its a function
        bool isOperator(string token); //returns true if its an operator
        bool isOperator2(char& token); //returns true if its an operator
        bool isLeftParenthesis(string token);
        bool isRightParenthesis(string token);
        void printTable(string action, string token, stackCustom<string> stackCopy); //print your current step: INPUT ACTION STACK OUTPUT
        bool validate(); //check if the expression is valid


    public:
        polishReverseForm();    // Constructor which opens the txt file
        virtual ~polishReverseForm(); //Destrcutor which closes the txt file
        void run();   //function which allows the user to start the program


};

#endif // POLISHREVERSEFORM_H
