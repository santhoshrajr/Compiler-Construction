// Companion source code for "flex & bison", published by O'Reilly
// helper functions for fb3-1
#  include <iostream>
#  include <stdlib.h>
#  include "ast.h"
#  include <math.h>

double eval(Ast *a) {
  double v = 0;
  switch( a->getNodetype() ) {
  case 'K': v = a->getNumber(); break;
  case '+': v = eval(a->getLeft()) + eval(a->getRight()); break;
  case '-': v = eval(a->getLeft()) - eval(a->getRight()); break;
  case '*': v = eval(a->getLeft()) * eval(a->getRight()); break;
  case '/': v = eval(a->getLeft()) / eval(a->getRight()); break;
  case 'E': v = pow(eval(a->getLeft()),eval(a->getRight())); break;
  case 'M': v = -eval(a->getLeft()); break;
  default: std::cout << "internal error: bad node "
                << a->getNodetype() << std::endl;
  }
  return v;
}

void getLeft(const Ast* a,std::fstream& output){
             
           
              if(a->getLeft()->getNodetype()=='+'){
                   output<< " \"node1\":f1  " <<std::endl; 
                }
                
                else if(a->getLeft()->getNodetype()=='-'){
                   output<< " \"node2\":f1  " <<std::endl; 
                }
                else if(a->getLeft()->getNodetype()=='*'){
                   output<< " \"node3\":f1  " <<std::endl; 
                }
                else if(a->getLeft()->getNodetype()=='M'){
                  output<< " \"node0\":f1  " <<std::endl; 
                }
                else if(a->getLeft()->getNodetype()=='/'){
                  output<< " \"node4\":f1  " <<std::endl; 
                }
                else if(a->getLeft()->getNodetype()=='K'){
                  output<< a->getLeft()->getNumber() <<std::endl;
                }
                
                else if(a->getLeft()->getNodetype()=='E'){
                 output<< " \"node5\":f1  " <<std::endl; 
                }
}


void getRight(const Ast* a,std::fstream& output){
if(a->getRight()->getNodetype()=='+'){
                   output<< " \"node1\":f1  " <<std::endl; 
                }
               else if(a->getRight()->getNodetype()=='-'){
                   output<< " \"node2\":f1  " <<std::endl; 
                }
                else if(a->getRight()->getNodetype()=='*'){
                   output<< " \"node3\":f1  " <<std::endl; 
                }
                else if(a->getRight()->getNodetype()=='M'){
                  output<< " \"node0\":f1  " <<std::endl; 
                }
                else if(a->getRight()->getNodetype()=='/'){
                  output<< " \"node4\":f1  " <<std::endl; 
                }
                else if(a->getRight()->getNodetype()=='K'){
                  output<< a->getRight()->getNumber() <<std::endl;
                }
                
                else if(a->getRight()->getNodetype()=='E'){
                 output<< " \"node5\":f1  " <<std::endl; 
                }
                 

}

void makeGraph(const Ast* a, std::fstream& output)  {

   switch( a->getNodetype() ) {

    case '+':
            
            if(a->getLeft()){
              output << " \"node1\":f0  " <<" " << "-> ";
                
               getLeft(a,output);
                makeGraph(a->getLeft(),output);
              }
              if(a->getRight()){
               output << " \"node1\":f2  " <<" " << "-> ";
              getRight(a,output);
                 makeGraph(a->getRight(),output);
              }
              break;
    case '-':
           
            if(a->getLeft()){
               output << " \"node2\":f0  " <<" " << "-> ";
               getLeft(a,output);
                makeGraph(a->getLeft(),output);
              }
              if(a->getRight()){
               output << " \"node2\":f2  " <<" " << "-> ";
                //output <<a->getRight()->getNodetype()<<" "<<std::endl;
                getRight(a,output);
                 makeGraph(a->getRight(),output);
              }
              break;
    case '*':
           
            if(a->getLeft()){
               output << " \"node3\":f0  " <<" " << "-> ";
               getLeft(a,output);
                makeGraph(a->getLeft(),output);
              }
              if(a->getRight()){
                 output << " \"node3\":f2  " <<" " << "-> ";
                getRight(a,output);
                 makeGraph(a->getRight(),output);
              }
              break;
    case '/':
            
            if(a->getLeft()){
              output << " \"node4\":f0  " <<" " << "-> ";
               getLeft(a,output);
                makeGraph(a->getLeft(),output);
              }
              if(a->getRight()){
                output << " \"node4\":f2  " <<" " << "-> ";
                getRight(a,output);
                 makeGraph(a->getRight(),output);
              }
              break;
    case 'E':
            
            if(a->getLeft()){
              output << " \"node5\":f0  " <<" " << "-> ";
                getLeft(a,output);
                makeGraph(a->getLeft(),output);
              }
              if(a->getRight()){
                output << " \"node5\":f2  " <<" " << "-> ";
                getRight(a,output);
                 makeGraph(a->getRight(),output);
              }
              break;
             
           
    case 'M':
             
              if(a->getLeft()){
              output << " \"node0\":f0  " <<" " << "-> ";
                getLeft(a,output);
                
                makeGraph(a->getLeft(),output);
                }
             

              break;
    
    case 'K': 

   
              
              break;


  }



}



void makeGraph(Ast *a)  {
  std::fstream output;
  output.open("graph.gv", std::ios::out);
  output << "digraph G {" << std::endl;
  output<<"node [shape = record,height=.1];"<<std::endl;
  output<<" node1[label = \"<f0> |<f1> +|<f2> \"]"<<std::endl;
  output<<" node2[label = \"<f0> |<f1> -|<f2> \"]"<<std::endl;
  output<<" node3[label = \"<f0> |<f1> *|<f2> \"]"<<std::endl;
  output<<" node4[label = \"<f0> |<f1> /|<f2> \"]"<<std::endl;
  output<<" node0[label = \"<f0> |<f1> UnaryMinus|<f2> \"]"<<std::endl;
  output<<" node5[label = \"<f0> |<f1> **|<f2> \"]"<<std::endl;
  

  makeGraph(a, output);

  output << "}" << std::endl;
  output.close();
  system("dot -Tpng graph.gv -o graph.png");
}

void treeFree(Ast *a) {
  switch(a->getNodetype()) {
   // two subtrees
  case '+':
  case '-':
  case '*':
  case '/':
  case 'E':
    treeFree(a->getRight());

   // one subtrees
  case 'M':
    treeFree(a->getLeft());


   //no subtree
  case 'K':
    delete a;
    break;

  default: std::cout << "internal error: bad node "
                << a->getNodetype() << std::endl;;
  }
}

