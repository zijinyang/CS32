#include <string>
#include <stack>
#include <iostream>
#include <cassert>
using namespace std;

void removeSpaces(string &a)
{
   int i = 0;
   while (i < a.size())
   {
      if (a.at(i) == ' ')
         a.erase(i, 1);
      else
         i++;
   }
}

// highly disgusting code :(
// bool checkValidity(string infix)
// {
//    removeSpaces(infix);
//    int numOpenParenthesis = 0;
//    int numClosedParenthesis = 0;

//    if (infix.size() == 0 || infix.size() == 2)
//    {
//       return false;
//    }

//    if (!isnumber(infix.at(0)))
//    {
//       if (infix.at(0) == '(')
//          numOpenParenthesis++;
//       else
//          return false;
//    }

//    if (!isnumber(infix.at(infix.size() - 1)))
//    {
//       if (infix.at(infix.size() - 1) == ')')
//          numClosedParenthesis++;
//       else
//          return false;
//    }

//    for (int i = 1; i < infix.size() - 1; i++)
//    {
//       cout << infix.at(i);
//       char ch = infix.at(i);
//       if (isdigit(ch))
//       {
//          if (isnumber(infix.at(i - 1)))
//             return false;
//       }
//       else if (ch == '|' || ch == '&')
//       {
//          if (!isnumber(infix.at(i - 1)) && infix.at(i - 1) != ')')
//          {
//             cout << "ok1" << endl;
//             return false;
//          }
//          if (!isnumber(infix.at(i + 1)) && infix.at(i + 1) != '(')
//          {
//             cout << "ok2" << endl;
//             return false;
//          }
//       }
//       else if (ch == '(')
//       {
//          if (isnumber(infix.at(i - 1)))
//             return false;
//          numOpenParenthesis++;
//       }
//       else if (ch == ')')
//       {
//          numClosedParenthesis++;
//       }
//       else if (ch == '!')
//       {
//          if (!isnumber(infix.at(i + 1)) && infix.at(i + 1) != '(')
//             return false;
//       }
//       else
//       {
//          return false;
//       }
//    }
//    if (numOpenParenthesis != numClosedParenthesis)
//    {
//       return false;
//    }
//    return true;
// }

bool toPostfix(string infix, string &postfix)
{
   removeSpaces(infix);
   postfix = "";
   stack<char> operators;
   bool prevBinary = true;
   bool prevUnary = false;
   bool prevOperand = false;

   if(infix == "")
      return false;

   for (int i = 0; i < infix.size(); i++)
   {
      char ch = infix.at(i);
      switch (ch)
      {
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
         if (prevOperand)
            return false;
         prevBinary = false;
         prevUnary = false;
         prevOperand = true;
         postfix += ch;
         break;
      case '(':
         if (prevOperand)
            return false;
         prevBinary = false;
         prevUnary = true;
         prevOperand = false;
         operators.push(ch);
         break;
      case ')':
         if (operators.empty())
            return false;
         while (operators.top() != '(')
         {
            postfix += operators.top();
            operators.pop();
            if (operators.empty())
               return false;
         }
         prevOperand = true;
         prevBinary = false;
         prevUnary = false;
         operators.pop();
         break;
      case '|':
         if(!prevOperand)
            return false;
         prevBinary = true;
         prevUnary = false;
         prevOperand = false;
         while (!operators.empty() && operators.top() != '(')
         {
            postfix += operators.top();
            operators.pop();
         }
         operators.push(ch);
         break;
      case '&':
         if(!prevOperand)
            return false;
         prevBinary = true;
         prevUnary = false;
         prevOperand = false;
         while (!operators.empty() && operators.top() != '(' && operators.top() != '|')
         {
            postfix += operators.top();
            operators.pop();
         }
         operators.push(ch);
         break;
      case '!':
         if(prevOperand)
            return false;
         prevBinary = false;
         prevUnary = true;
         prevOperand = false;
         while (!operators.empty() && operators.top() != '(' && operators.top() != '|' && operators.top() != '&')
         {
            postfix += operators.top();
            operators.pop();
         }
         operators.push(ch);
         break;
      case ' ':
         break;
      default:
         return false;
      }
   }
   while (!operators.empty())
   {
      if(operators.top() == '(')
         return false;
      postfix += operators.top();
      operators.pop();
   }
   return true;
}

int evaluate(string infix, const bool values[], string &postfix, bool &result)
{
   if (!toPostfix(infix, postfix))
   {
      return 1;
   }

   stack<bool> operands;
   for (int i = 0; i < postfix.size(); i++)
   {
      char ch = postfix.at(i);
      if (isdigit(ch))
      {
         operands.push(values[ch - '0']);
      }
      else if (ch == '!')
      {
         if(operands.size() < 1)
            return 1;
         bool operand = operands.top();
         operands.pop();
         operands.push(!operand);
      }
      else
      {
         if(operands.size() < 2)
            return 1;
         bool operand2 = operands.top();
         operands.pop();
         bool operand1 = operands.top();
         operands.pop();
         if (ch == '|')
         {
            operands.push(operand1 || operand2);
         }
         if (ch == '&')
         {
            operands.push(operand1 && operand2);
         }
      }
   }
   if(operands.empty())
      return 1;
   result = operands.top();
   return 0;
}

int main() {
   bool ba[10] = {
       // 0      1      2      3      4      5      6      7      8      9
       true,  true,  true,  false, false, false, true,  false, true,  false
   };
   string pf;
   bool answer;

   // Basic tests
   assert(evaluate("2|3", ba, pf, answer) == 0 && pf == "23|" && answer);
   assert(evaluate("2&3", ba, pf, answer) == 0 && pf == "23&" && !answer);
   assert(evaluate("!2", ba, pf, answer) == 0 && pf == "2!" && !answer);
   assert(evaluate("(!2)&3", ba, pf, answer) == 0 && pf == "2!3&" && !answer);
   assert(evaluate("(!2)|3", ba, pf, answer) == 0 && pf == "2!3|" && !answer);

   // Basic operands
   assert(evaluate("0", ba, pf, answer) == 0 && pf == "0" && answer);
   assert(evaluate("9", ba, pf, answer) == 0 && pf == "9" && !answer);
   assert(evaluate("5", ba, pf, answer) == 0 && pf == "5" && !answer);

   // NOT operations
   assert(evaluate("!0", ba, pf, answer) == 0 && pf == "0!" && !answer);
   assert(evaluate("!3", ba, pf, answer) == 0 && pf == "3!" && answer);
   assert(evaluate("!5", ba, pf, answer) == 0 && pf == "5!" && answer);

   // AND operations
   assert(evaluate("0&1", ba, pf, answer) == 0 && pf == "01&" && answer);
   assert(evaluate("1&3", ba, pf, answer) == 0 && pf == "13&" && !answer);
   assert(evaluate("3&4", ba, pf, answer) == 0 && pf == "34&" && !answer);
   assert(evaluate("2&6", ba, pf, answer) == 0 && pf == "26&" && answer);

   // OR operations
   assert(evaluate("3|4", ba, pf, answer) == 0 && pf == "34|" && !answer);
   assert(evaluate("2|3", ba, pf, answer) == 0 && pf == "23|" && answer);
   assert(evaluate("0|9", ba, pf, answer) == 0 && pf == "09|" && answer);

   // Operator precedence
   assert(evaluate("2|3&4", ba, pf, answer) == 0 && pf == "234&|" && answer);
   assert(evaluate("3&4|2", ba, pf, answer) == 0 && pf == "34&2|" && answer);

   // Parentheses
   assert(evaluate("(2|3)&4", ba, pf, answer) == 0 && pf == "23|4&" && !answer);
   assert(evaluate("2&(3|4)", ba, pf, answer) == 0 && pf == "234|&" && !answer);
   assert(evaluate("!(2|3)", ba, pf, answer) == 0 && pf == "23|!" && !answer);
   assert(evaluate("!2|!3", ba, pf, answer) == 0 && pf == "2!3!|" && answer);

   // Complex expressions
   assert(evaluate("((!2)&(3|4))|5", ba, pf, answer) == 0 && pf == "2!34|&5|" && !answer);
   assert(evaluate("0|(1&(2|(3&4)))", ba, pf, answer) == 0 && pf == "01234&|&|" && answer);
   assert(evaluate("((0)&1)|(2&(3|4))", ba, pf, answer) == 0 && pf == "01&234|&|" && answer);

   // Multiple operators and nesting
   assert(evaluate("6&7|8&9", ba, pf, answer) == 0 && pf == "67&89&|" && !answer);
   assert(evaluate("6|7&8|9", ba, pf, answer) == 0 && pf == "678&|9|" && answer);
   assert(evaluate("!0&1|!2", ba, pf, answer) == 0 && pf == "0!1&2!|" && !answer);
   assert(evaluate("!3&(4|5)&6", ba, pf, answer) == 0 && pf == "3!45|&6&" && !answer);

   // Edge cases with parentheses
   assert(evaluate("((2))", ba, pf, answer) == 0 && pf == "2" && answer);
   assert(evaluate("(((3))&4)", ba, pf, answer) == 0 && pf == "34&" && !answer);

   // Invalid syntax tests
   assert(evaluate("", ba, pf, answer) == 1);
   assert(evaluate("&", ba, pf, answer) == 1);
   assert(evaluate("|", ba, pf, answer) == 1);
   assert(evaluate("!", ba, pf, answer) == 1);
   assert(evaluate("(", ba, pf, answer) == 1);
   assert(evaluate(")", ba, pf, answer) == 1);
   assert(evaluate("2&", ba, pf, answer) == 1);
   assert(evaluate("|3", ba, pf, answer) == 1);
   assert(evaluate("2a3", ba, pf, answer) == 1);
   assert(evaluate("(2&3", ba, pf, answer) == 1);
   assert(evaluate("2&3)", ba, pf, answer) == 1);
   assert(evaluate(")2&3(", ba, pf, answer) == 1);
   assert(evaluate("2||3", ba, pf, answer) == 1);
   assert(evaluate("22", ba, pf, answer) == 1);
   assert(evaluate("3 4", ba, pf, answer) == 1);
   assert(evaluate("10", ba, pf, answer) == 1);
   assert(evaluate("2!3", ba, pf, answer) == 1);
   assert(evaluate("()", ba, pf, answer) == 1);
   assert(evaluate("(&3)", ba, pf, answer) == 1);
   assert(evaluate("2&3))", ba, pf, answer) == 1);
   assert(evaluate("((2&3)", ba, pf, answer) == 1);
   assert(evaluate("2!&3", ba, pf, answer) == 1);
   assert(evaluate("2&+3", ba, pf, answer) == 1);
   assert(evaluate("0&&1", ba, pf, answer) == 1);
   assert(evaluate("0||1", ba, pf, answer) == 1);
   assert(evaluate("0!1", ba, pf, answer) == 1);
   assert(evaluate("(&0)", ba, pf, answer) == 1);
   assert(evaluate("0|(1&)", ba, pf, answer) == 1);
   assert(evaluate("7|(8&9", ba, pf, answer) == 1);
   assert(evaluate("5|6&", ba, pf, answer) == 1);
   assert(evaluate("5&6|", ba, pf, answer) == 1);
   assert(evaluate("!7|!8", ba, pf, answer) == 0 && pf == "7!8!|" && answer);
   assert(evaluate("!7&!8", ba, pf, answer) == 0 && pf == "7!8!&" && !answer);
   assert(evaluate("!(7&8)", ba, pf, answer) == 0 && pf == "78&!" && answer);
   assert(evaluate("6&7|!8&9", ba, pf, answer) == 0 && pf == "67&8!9&|" && !answer);
   assert(evaluate("5|6&7", ba, pf, answer) == 0 && pf == "567&|" && !answer);
   assert(evaluate("5&6|7", ba, pf, answer) == 0 && pf == "56&7|" && !answer);
   assert(evaluate("1&2|3&4", ba, pf, answer) == 0 && pf == "12&34&|" && answer);
   assert(evaluate("1&(2|3)&4", ba, pf, answer) == 0 && pf == "123|&4&" && !answer);
   assert(evaluate("!1&!2", ba, pf, answer) == 0 && pf == "1!2!&" && !answer);
   assert(evaluate("!(1|2)&3", ba, pf, answer) == 0 && pf == "12|!3&" && !answer);
   assert(evaluate("((0))", ba, pf, answer) == 0 && pf == "0" && answer);
   assert(evaluate("0&((1)|2)", ba, pf, answer) == 0 && pf == "012|&" && answer);
   assert(evaluate("!(3|4)&5", ba, pf, answer) == 0 && pf == "34|!5&" && !answer);
   assert(evaluate("0|1&2|3", ba, pf, answer) == 0 && pf == "012&|3|" && answer);
   assert(evaluate("9|!9", ba, pf, answer) == 0 && pf == "99!|" && answer);

   cout << "All tests passed." << endl;
   return 0;
}
