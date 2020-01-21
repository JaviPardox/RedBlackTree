
/*
 * @file rbapp.cpp   
 *  
 * @brief  File where multiple commmands to utilize the tree are implemented    
 * @author Judy Challinger and Javier Pardo
 * 
 * @date 9/10/15
 */
#include<iostream>
#include<string>
#include"rbapp.h"

using std::cin;
using std::string;
using std::cout;
using std::endl;

/**
 *  @brief Main function, initializes the tree app
 *         and calls mainloop.
 *
 *  @param Nothing.
 * 
 *  @return 0.
 * 
 */

int main()
{
  RBapp RBstart;
  RBstart.mainLoop();
  return 0;
}

/**
 *  @brief This function reads the whole input and inserts
 *         it into the process command function.
 *
 *  @param Nothing.
 * 
 *  @return Nothing.
 * 
 */

void RBapp::mainLoop()
{
  string ip;
  while(std::getline(cin,ip))
  {
    if(!processCommand(ip))
    {
      return;
    }
  }
}

/**
 *  @brief This function processes the command,
 *         divides the initial string to interpret
 *         what command we want to use.
 *
 *  @param String containing the input.
 * 
 *  @return True when a valid command is inserted
 *          False when an invalid command is inserted.
 * 
 */

bool RBapp::processCommand(string& ip)
{
  unsigned int pos = ip.find(" ");
  string command = ip.substr(0,pos);
  ip.erase(0,(pos+1));
  if(command == "insert")
  {
    if(command != ip)
    {
      processInsert(ip);
    }
    return 1;
  }
  if(command == "print")
  {
    processPrint();
    return 1;
  }
  if(command == "find")
  {
    processFind(ip);
    return 1;
  }
  if(command == "delete")
  {
    if(command != ip)
    {
      processDelete(ip);
    }
    return 1;
  }
  if(command == "quit")
  {
    myRBT.deleteTree();
    return 0;
  }
  else
  {
    myRBT.deleteTree();
    return 0;
  }
  return 1;
}

/**
 *  @brief This function divides the rest of the input
 *         and inputs it into the insertion from the tree.
 *
 *  @param Strig containing the input.
 * 
 *  @return Nothing.
 * 
 */

void RBapp::processInsert(string& ip)
{
  unsigned int pos = ip.find(" ");
  string key = ip.substr(0,pos);
  ip.erase(0,(pos+1));
  string data = ip;
  if(pos != 4294967295) //case when there is only one parameter as input
  {
    myRBT.rbInsert(key,data);
  }
}

/**
 *  @brief Function that calls the print function from
 *         the tree.
 *
 *  @param Nothing.
 * 
 *  @return Nothing.
 * 
 */

void RBapp::processPrint()
{
  myRBT.rbPrintTree();
}

/**
 *  @brief Prints all the nodes found with the same key.
 *
 *  @param String containing the rest of the input.
 * 
 *  @return Nothing.
 * 
 */

void RBapp::processFind(string& ip)
{
  vector<const string*> op;
  string key = ip;
  op = myRBT.rbFind(key);
  if(op.size() >= 1)
  {
    for(unsigned int i = 1; i < op.size(); i++)
    {
      if(op[0] != nullptr && op[i] != nullptr)
      {
        cout << *op[0] << " " << *op[i] << endl;
      }
    }
  }
  if(op.size() == 0)
  {
    cout << endl;
  }
}

/**
 *  @brief This function divides the rest of the input
 *         and initializes the delete process.
 *
 *  @param String containing the rest of the input.
 * 
 *  @return Nothing.
 * 
 */

void RBapp::processDelete(string& ip)
{
  unsigned int pos = ip.find(" ");
  string key = ip.substr(0,pos);
  ip.erase(0,(pos+1));
  string data = ip;
  myRBT.rbDelete(key,data);
}

