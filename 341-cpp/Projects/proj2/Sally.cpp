// File: Sally.cpp
//
// CMSC 341 Spring 2017 Project 2
//
// Implementation of member functions of Sally Forth interpreter
//

#include <iostream>
#include <string>
#include <list>
#include <stack>
#include <stdexcept>
#include <cstdlib>
using namespace std ;

#include "Sally.h"


// Basic Token constructor. Just assigns values.
//
Token::Token(TokenKind kind, int val, string txt) {
   m_kind = kind ;
   m_value = val ;
   m_text = txt ;
}

//True/False constant Tokens
const Token TRUE_TOKEN = Token(INTEGER, 1);
const Token FALSE_TOKEN = Token(INTEGER, 0);

// Basic SymTabEntry constructor. Just assigns values.
//
SymTabEntry::SymTabEntry(TokenKind kind, int val, operation_t fptr) {
   m_kind = kind ;
   m_value = val ;
   m_dothis = fptr ;
}


// Constructor for Sally Forth interpreter.
// Adds built-in functions to the symbol table.
//
Sally::Sally(istream& input_stream) :
   istrm(input_stream)  // use member initializer to bind reference
{
  m_ifCount = 0;
  m_endCount = 0;

   symtab["DUMP"]    =  SymTabEntry(KEYWORD,0,&doDUMP) ;

   symtab["+"]    =  SymTabEntry(KEYWORD,0,&doPlus) ;
   symtab["-"]    =  SymTabEntry(KEYWORD,0,&doMinus) ;
   symtab["*"]    =  SymTabEntry(KEYWORD,0,&doTimes) ;
   symtab["/"]    =  SymTabEntry(KEYWORD,0,&doDivide) ;
   symtab["%"]    =  SymTabEntry(KEYWORD,0,&doMod) ;
   symtab["NEG"]  =  SymTabEntry(KEYWORD,0,&doNEG) ;

   symtab["."]    =  SymTabEntry(KEYWORD,0,&doDot) ;
   symtab["SP"]   =  SymTabEntry(KEYWORD,0,&doSP) ;
   symtab["CR"]   =  SymTabEntry(KEYWORD,0,&doCR) ;

   symtab["DUP"]  = SymTabEntry(KEYWORD, 0, &doDup);
   symtab["DROP"] = SymTabEntry(KEYWORD, 0, &doDrop);
   symtab["SWAP"] = SymTabEntry(KEYWORD, 0, &doSwap);
   symtab["ROT"] =  SymTabEntry(KEYWORD, 0, &doRot);

   symtab["SET"] = SymTabEntry(KEYWORD, 0, &doSet);
   symtab["@"] = SymTabEntry(KEYWORD, 0, &doAt); 
   symtab["!"] = SymTabEntry(KEYWORD, 0, &doStore);

   symtab["<"] = SymTabEntry(KEYWORD, 0, &doLess);
   symtab["<="] = SymTabEntry(KEYWORD, 0, &doLessEqual);
   symtab["=="] = SymTabEntry(KEYWORD, 0, &doEqual);
   symtab["!="] = SymTabEntry(KEYWORD, 0, &doNotEqual);
   symtab[">"] = SymTabEntry(KEYWORD, 0, &doMore);
   symtab[">="] = SymTabEntry(KEYWORD, 0, &doMoreEqual);

   symtab["AND"] = SymTabEntry(KEYWORD, 0, &doAnd);
   symtab["OR"] = SymTabEntry(KEYWORD, 0, &doOr);
   symtab["NOT"] = SymTabEntry(KEYWORD, 0, &doNot);

   symtab["IFTHEN"] = SymTabEntry(KEYWORD, 0, &doIf);
   symtab["ELSE"] = SymTabEntry(KEYWORD, 0, &doElse);
   symtab["ENDIF"] = SymTabEntry(KEYWORD, 0, &doEnd);

   symtab["DO"] = SymTabEntry(KEYWORD, 0, &doDo);
   symtab["UNTIL"] = SymTabEntry(KEYWORD, 0, &doUntil);
}


// This function should be called when tkBuffer is empty.
// It adds tokens to tkBuffer.
//
// This function returns when an empty line was entered 
// or if the end-of-file has been reached.
//
// This function returns false when the end-of-file was encountered.
// 
// Processing done by fillBuffer()
//   - detects and ignores comments.
//   - detects string literals and combines as 1 token
//   - detetcs base 10 numbers
// 
//
bool Sally::fillBuffer() {
   string line ;     // single line of input
   int pos ;         // current position in the line
   int len ;         // # of char in current token
   long int n ;      // int value of token
   char *endPtr ;    // used with strtol()


   while(true) {    // keep reading until empty line read or eof

      // get one line from standard in
      //
      getline(istrm, line) ;   

      // if "normal" empty line encountered, return to mainLoop
      //
      if ( line.empty() && !istrm.eof() ) {
         return true ;
      }

      // if eof encountered, return to mainLoop, but say no more
      // input available
      //
      if ( istrm.eof() )  {
         return false ;
      }


      // Process line read

      pos = 0 ;                      // start from the beginning

      // skip over initial spaces & tabs
      //
      while( line[pos] != '\0' && (line[pos] == ' ' || line[pos] == '\t') ) {
         pos++ ; 
      }

      // Keep going until end of line
      //
      while (line[pos] != '\0') {

         // is it a comment?? skip rest of line.
         //
         if (line[pos] == '/' && line[pos+1] == '/') break ;

         // is it a string literal? 
         //
         if (line[pos] == '.' && line[pos+1] == '"') {

            pos += 2 ;  // skip over the ."
            len = 0 ;   // track length of literal

            // look for matching quote or end of line
            //
            while(line[pos+len] != '\0' && line[pos+len] != '"') {
               len++ ;
            }

            // make new string with characters from
            // line[pos] to line[pos+len-1]
            string literal(line,pos,len) ;  // copy from pos for len chars

            // Add to token list
            //
            tkBuffer.push_back( Token(STRING,0,literal) ) ;  

            // Different update if end reached or " found
            //
            if (line[pos+len] == '\0') {
               pos = pos + len ;
            } else {
               pos = pos + len + 1 ;
            }

         } else {  // otherwise "normal" token

            len = 0 ;  // track length of token

            // line[pos] should be an non-white space character
            // look for end of line or space or tab
            //
            while(line[pos+len] != '\0' && line[pos+len] != ' ' && line[pos+len] != '\t') {
               len++ ;
            }

            string literal(line,pos,len) ;   // copy form pos for len chars
            pos = pos + len ;

            // Try to convert to a number
            //
            n = strtol(literal.c_str(), &endPtr, 10) ;

            if (*endPtr == '\0') {
               tkBuffer.push_back( Token(INTEGER,n,literal) ) ;
            } else {
               tkBuffer.push_back( Token(UNKNOWN,0,literal) ) ;
            }
         }

         // skip over trailing spaces & tabs
         //
         while( line[pos] != '\0' && (line[pos] == ' ' || line[pos] == '\t') ) {
            pos++ ; 
         }

      }
   }
}



// Return next token from tkBuffer.
// Call fillBuffer() if needed.
// Checks for end-of-file and throws exception 
//
Token Sally::nextToken() {
      Token tk ;
      bool more = true ;

      while(more && tkBuffer.empty() ) {
         more = fillBuffer() ;
      }

      if ( !more && tkBuffer.empty() ) {
         throw EOProgram("End of Program") ;
      }

      tk = tkBuffer.front() ;
      tkBuffer.pop_front() ;

      return tk ;
}

Token Sally::copyToken()
{
  Token tk;
  bool more = true;

  while(more && tkBuffer.empty() ) {
    more = fillBuffer() ;
  }

  if ( !more && tkBuffer.empty() ) {
    throw EOProgram("End of Program") ;
  }

  tk = tkBuffer.front() ;
  cpBuffer.push_back(tk);
  tkBuffer.pop_front();
  return tk;


}

// The main interpreter loop of the Sally Forth interpreter.
// It gets a token and either push the token onto the parameter
// stack or looks for it in the symbol table.
//
//
void Sally::mainLoop() {

   Token tk ;
   map<string,SymTabEntry>::iterator it ;

   try {
      while( 1 ) {
         tk = nextToken() ;

         if (tk.m_kind == INTEGER || tk.m_kind == STRING) {

            // if INTEGER or STRING just push onto stack
            params.push(tk) ;

         } else { 
            it = symtab.find(tk.m_text) ;
            
            if ( it == symtab.end() )  {   // not in symtab

               params.push(tk) ;

            } else if (it->second.m_kind == KEYWORD)  {

               // invoke the function for this operation
               //
               it->second.m_dothis(this) ;   
               
            } else if (it->second.m_kind == VARIABLE) {

               // variables are pushed as tokens
               //
               tk.m_kind = VARIABLE ;
               params.push(tk) ;

            } else {

               // default action
               //
               params.push(tk) ;

            }
         }
      }

   } catch (EOProgram& e) {

      cerr << "End of Program\n" ;
      if ( params.size() == 0 ) {
         cerr << "Parameter stack empty.\n" ;
      } else {
         cerr << "Parameter stack has " << params.size() << " token(s).\n" ;
      }

   } catch (out_of_range& e) {

      cerr << "Parameter stack underflow??\n" ;

   } catch (...) {

      cerr << "Unexpected exception caught\n" ;

   }
}

// -------------------------------------------------------


void Sally::doPlus(Sally *Sptr) {
   Token p1, p2 ;

   if ( Sptr->params.size() < 2 ) {
      throw out_of_range("Need two parameters for +.") ;
   }
   p1 = Sptr->params.top() ;
   Sptr->params.pop() ;
   p2 = Sptr->params.top() ;
   Sptr->params.pop() ;
   int answer = p2.m_value + p1.m_value ;
   Sptr->params.push( Token(INTEGER, answer, "") ) ;
}


void Sally::doMinus(Sally *Sptr) {
   Token p1, p2 ;

   if ( Sptr->params.size() < 2 ) {
      throw out_of_range("Need two parameters for -.") ;
   }
   p1 = Sptr->params.top() ;
   Sptr->params.pop() ;
   p2 = Sptr->params.top() ;
   Sptr->params.pop() ;
   int answer = p2.m_value - p1.m_value ;
   Sptr->params.push( Token(INTEGER, answer, "") ) ;
}


void Sally::doTimes(Sally *Sptr) {
   Token p1, p2 ;

   if ( Sptr->params.size() < 2 ) {
      throw out_of_range("Need two parameters for *.") ;
   }
   p1 = Sptr->params.top() ;
   Sptr->params.pop() ;
   p2 = Sptr->params.top() ;
   Sptr->params.pop() ;
   int answer = p2.m_value * p1.m_value ;
   Sptr->params.push( Token(INTEGER, answer, "") ) ;
}


void Sally::doDivide(Sally *Sptr) {
   Token p1, p2 ;

   if ( Sptr->params.size() < 2 ) {
      throw out_of_range("Need two parameters for /.") ;
   }
   p1 = Sptr->params.top() ;
   Sptr->params.pop() ;
   p2 = Sptr->params.top() ;
   Sptr->params.pop() ;
   int answer = p2.m_value / p1.m_value ;
   Sptr->params.push( Token(INTEGER, answer, "") ) ;
}


void Sally::doMod(Sally *Sptr) {
   Token p1, p2 ;

   if ( Sptr->params.size() < 2 ) {
      throw out_of_range("Need two parameters for %.") ;
   }
   p1 = Sptr->params.top() ;
   Sptr->params.pop() ;
   p2 = Sptr->params.top() ;
   Sptr->params.pop() ;
   int answer = p2.m_value % p1.m_value ;
   Sptr->params.push( Token(INTEGER, answer, "") ) ;
}


void Sally::doNEG(Sally *Sptr) {
   Token p ;

   if ( Sptr->params.size() < 1 ) {
      throw out_of_range("Need one parameter for NEG.") ;
   }
   p = Sptr->params.top() ;
   Sptr->params.pop() ;
   Sptr->params.push( Token(INTEGER, -p.m_value, "") ) ;
}


void Sally::doDot(Sally *Sptr) {

   Token p ;
   if ( Sptr->params.size() < 1 ) {
      throw out_of_range("Need one parameter for .") ;
   }

   p = Sptr->params.top() ;
   Sptr->params.pop() ;

   if (p.m_kind == INTEGER) {
      cout << p.m_value ;
   } else {
      cout << p.m_text ;
   }
}


void Sally::doSP(Sally *Sptr) {
   cout << " " ;
}


void Sally::doCR(Sally *Sptr) {
   cout << endl ;
}

void Sally::doDUMP(Sally *Sptr) {
  // do whatever for debugging

  /*  Token p;
  if ( Sptr->params.size() < 1 )
    {
      throw out_of_range("Need one parameter for DUP") ;
    }

  p = Sptr->params.top() ;

  cout << p.m_value << " " + p.m_text << endl;*/

  cout << Sptr->m_ifCount << endl << Sptr->m_endCount << endl;
} 

void Sally::doDup(Sally *Sptr)
{
  Token p ;
  if ( Sptr->params.size() < 1 ) 
    {
      throw out_of_range("Need one parameter for DUP") ;
    }
  //Pushes token equal to the param on the top of the stack
  p = Sptr->params.top() ;
  Sptr->params.push(p);
}

void Sally::doDrop(Sally *Sptr)
{
  if(Sptr->params.size() < 1)
    {
      throw out_of_range("Need one parameter for Drop");
    }
  //pop token on top of the stack
  Sptr->params.pop();
}

void Sally::doSwap(Sally *Sptr)
{
  Token p1, p2;
  if(Sptr->params.size() < 2)
    {
      throw out_of_range("Need two parameters for Swap");
    }
  p1 = Sptr->params.top();
  Sptr->params.pop();
  
  p2 = Sptr->params.top();
  Sptr->params.pop();
  
  Sptr->params.push(p1);
  Sptr->params.push(p2);
}

void Sally::doRot(Sally *Sptr)
{
  Token p1, p2, p3;
  if(Sptr->params.size() < 3)
    {
      throw out_of_range("Need three parameters for Rot");
    }

  p1 =  Sptr->params.top();
  Sptr->params.pop();

  p2 =  Sptr->params.top();
  Sptr->params.pop();

  p3 =  Sptr->params.top();
  Sptr->params.pop();

  Sptr->params.push(p2);
  Sptr->params.push(p1);
  Sptr->params.push(p3);
}

void Sally::doSet(Sally *Sptr)
{
  Token p1, p2;
  if(Sptr->params.size() < 2)
    {
      throw out_of_range("Need two parameter for Set");
    }

  p1 =  Sptr->params.top();
  Sptr->params.pop();

  p2 = Sptr->params.top();
  Sptr->params.pop();
  if(Sptr->symtab.count(p1.m_text) < 1)
    {
      Sptr->symtab[p1.m_text] = SymTabEntry(VARIABLE, p2.m_value);
    }
  else
    {
      cout << "You tried to create the variable " 
	   << p1.m_text 
	   << " but it already exists" << endl;
    }
}

void Sally::doAt(Sally *Sptr)
{
  Token p;
  if(Sptr->params.size() < 1)
    {
      throw out_of_range("Need one parameter for @");
    }

  p = Sptr->params.top();
  Sptr->params.pop();

  if(Sptr->symtab.count(p.m_text) < 1)
    {
      cout << "There is no such variable " << p.m_text << endl;
    }
  else
    {
      SymTabEntry variable = Sptr->symtab[p.m_text];
      Sptr->params.push(Token(INTEGER, variable.m_value, ""));
    }
}

void Sally::doStore(Sally *Sptr)
{
  Token p1, p2;
  if(Sptr->params.size() < 2)
    {
      throw out_of_range("Need two parameters for !");
    }

  p1 = Sptr->params.top(); //Variable
  Sptr->params.pop();

  p2 = Sptr->params.top(); //Value
  Sptr->params.pop();

  //if our Variable isn't in the SymTab
  if(Sptr->symtab.count(p1.m_text) < 1)
    {
      cout << "There is no such variable " << p1.m_text << endl;
    }
  else
    {
      Sptr->symtab[p1.m_text] = SymTabEntry(VARIABLE, p2.m_value);
    }

}

void Sally::doLess(Sally *Sptr)
{
  Token p1, p2;
  if(Sptr->params.size() < 2)
    {
      throw out_of_range("Need two parameters for <");
    }

  p1 = Sptr->params.top(); //Second Value
  Sptr->params.pop();

  p2 = Sptr->params.top(); //FIrst Value
  Sptr->params.pop();

  if(p2.m_value < p1.m_value)
    {
      Sptr->params.push(TRUE_TOKEN);
    }
  else
    {
      Sptr->params.push(FALSE_TOKEN);
    }

}
void Sally::doLessEqual(Sally *Sptr)
{
  Token p1, p2;
  if(Sptr->params.size() < 2)
    {
      throw out_of_range("Need two parameters for <=");
    }

  p1 = Sptr->params.top(); //Second Value
  Sptr->params.pop();

  p2 = Sptr->params.top(); //FIrst Value
  Sptr->params.pop();

  if(p2.m_value <= p1.m_value)
    {
      Sptr->params.push(TRUE_TOKEN);
    }
  else
    {
      Sptr->params.push(FALSE_TOKEN);
    }
}
void Sally::doEqual(Sally *Sptr)
{
  Token p1, p2;
  if(Sptr->params.size() < 2)
    {
      throw out_of_range("Need two parameters for ==");
    }

  p1 = Sptr->params.top(); //Second Value
  Sptr->params.pop();

  p2 = Sptr->params.top(); //FIrst Value
  Sptr->params.pop();

  if(p2.m_value == p1.m_value)
    {
      Sptr->params.push(TRUE_TOKEN);
    }
  else
    {
      Sptr->params.push(FALSE_TOKEN);
    }

}
void Sally::doNotEqual(Sally *Sptr)
{
  Token p1, p2;
  if(Sptr->params.size() < 2)
    {
      throw out_of_range("Need two parameters for !=");
    }

  p1 = Sptr->params.top(); //Second Value
  Sptr->params.pop();

  p2 = Sptr->params.top(); //FIrst Value
  Sptr->params.pop();

  if(p2.m_value != p1.m_value)
    {
      Sptr->params.push(TRUE_TOKEN);
    }
  else
    {
      Sptr->params.push(FALSE_TOKEN);
    }

}
void Sally::doMore(Sally *Sptr)
{
  Token p1, p2;
  if(Sptr->params.size() < 2)
    {
      throw out_of_range("Need two parameters for >");
    }

  p1 = Sptr->params.top(); //Second Value
  Sptr->params.pop();

  p2 = Sptr->params.top(); //First Value
  Sptr->params.pop();

  if(p2.m_value > p1.m_value)
    {
      Sptr->params.push(TRUE_TOKEN);
    }
  else
    {
      Sptr->params.push(FALSE_TOKEN);
    }
}
void Sally::doMoreEqual(Sally *Sptr)
{
  Token p1, p2;
  if(Sptr->params.size() < 2)
    {
      throw out_of_range("Need two parameters for >=");
    }

  p1 = Sptr->params.top(); //Second Value
  Sptr->params.pop();

  p2 = Sptr->params.top(); //FIrst Value
  Sptr->params.pop();

  if(p2.m_value >= p1.m_value)
    {
      Sptr->params.push(TRUE_TOKEN);
    }
  else
    {
      Sptr->params.push(FALSE_TOKEN);
    }
}

void Sally::doAnd(Sally *Sptr)
{
  Token p1, p2;
  if(Sptr->params.size() < 2)
    {
      throw out_of_range("Need two parameters for >");
    }

  p1 = Sptr->params.top(); //Second Value
  Sptr->params.pop();

  p2 = Sptr->params.top(); //First Value
  Sptr->params.pop();

  if(p1.m_value != 0 && p2.m_value != 0)
    {
      Sptr->params.push(TRUE_TOKEN);
    }
  else
    {
      Sptr->params.push(FALSE_TOKEN);
    }
}
void Sally::doOr(Sally *Sptr)
{
  Token p1, p2;
  if(Sptr->params.size() < 2)
    {
      throw out_of_range("Need two parameters for >");
    }

  p1 = Sptr->params.top(); //Second Value
  Sptr->params.pop();

  p2 = Sptr->params.top(); //First Value
  Sptr->params.pop();

  if(p1.m_value != 0 || p2.m_value != 0)
    {
      Sptr->params.push(TRUE_TOKEN);
    }
  else
    {
      Sptr->params.push(FALSE_TOKEN);
    }

}
void Sally::doNot(Sally *Sptr)
{
  Token p;
  if(Sptr->params.size() < 1)
    {
      throw out_of_range("Need one parameter for NOT");
    }

  p = Sptr->params.top(); 
  Sptr->params.pop();

  
  if(p.m_value != 0)
    {
      Sptr->params.push(FALSE_TOKEN);
    }
  else
    {
      Sptr->params.push(TRUE_TOKEN);
    }

}

void Sally::doIf(Sally *Sptr)
{
  Sptr->m_ifCount +=1;

  Token p;

  if(Sptr->params.size() < 1)
    {
      throw out_of_range("Need one parameter for IFTHEN");
    }

  p = Sptr->params.top();
  Sptr->params.pop();

  if(p.m_value == 0)
    {
      map<string,SymTabEntry>::iterator tit;
      Token tk = Sptr->nextToken();
      tit = Sptr->symtab.find(tk.m_text);
      while(tit == Sptr->symtab.end() || tit->first != "ELSE")
	{
	  tk = Sptr->nextToken();
	  tit = Sptr->symtab.find(tk.m_text);
	}
    }
  else
    {
      Sptr->params.push(TRUE_TOKEN);
      
    }
}
void Sally::doElse(Sally *Sptr)
{
  Token p;
  if(Sptr->params.size() < 1)
    {
      throw out_of_range("Need one parameter for ELSE");
    }

  
  p = Sptr->params.top();
  Sptr->params.pop();


  if(p.m_value != 0)
    {
      map<string,SymTabEntry>::iterator tit;
      Token tk = Sptr->nextToken();
      tit = Sptr->symtab.find(tk.m_text);

      while(tit == Sptr->symtab.end())
        {	    
	   tk = Sptr->nextToken();
	   tit = Sptr->symtab.find(tk.m_text);
        }
    }

}
void Sally::doEnd(Sally *Sptr)
{
  Sptr->m_endCount +=1;
  if(Sptr->m_endCount == Sptr->m_ifCount)
    {
      return;
    }
}


void Sally::doDo(Sally *Sptr)
{
  Sptr->fillBuffer();
  Sptr->fillBuffer();
  list<Token>::iterator ait;

  //ait = Sptr->cpBuffer.begin();
  //Sptr->cpBuffer.splice(ait,Sptr->tkBuffer);

  Sptr->cpBuffer = Sptr->tkBuffer;

  /*
  for(ait = Sptr->cpBuffer.begin(); ait != Sptr->cpBuffer.end(); ait++)
    {
      cout << ait->m_text << endl;
    }
  */
}

void Sally::doUntil(Sally *Sptr)
{
  if(Sptr->params.size() < 1)
    {
      throw out_of_range("Need one parameter for UNTIL");
    }

  Token p = Sptr->params.top();
  Sptr->params.pop();

  if(p.m_value == 0)
    {
      list<Token>::iterator lit;
      for(lit = Sptr->cpBuffer.begin(); lit != Sptr->cpBuffer.end(); lit++)
	{
	  Sptr->tkBuffer.push_back(*lit);
	}

    }

  
  
  
}
