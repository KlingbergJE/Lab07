#include "RombergIntegration.h"
#include "RecursiveIntegration.h"
#include "QueueLinked.h"
#include "Double.h"
using CSC2110::Double;

#include <math.h>
#include <utility>
using std::swap;

#include <iostream>
using namespace std;

//a is the lower limit and b is the upper limit
double RombergIntegration::accurateRomberg(MultiVarFunction* f, double a, double b, int level)
{
   Double* db, *db1;  //use this variable to place and retrieve values on the queue
   
   QueueLinked<Double>* q1 = new QueueLinked<Double>;
   QueueLinked<Double>* q2 = new QueueLinked<Double>;


   int counter = 0;
   int n = 1;  //current number of intervals
   while ( counter <= level )
   {
      //DO THIS
      //obtain the required number of trapezoid evaluations depending on the number of levels requested
      //put all of the level 0 results on the q1

      q1->enqueue(new Double(
            RecursiveIntegration::romberg(f, a, b, n)
      ));

      n = 2*n;  //double the number of intervals
      counter++;
   }

   //q1 now has all of the level 0 integration results

   double factor;  //use this to compute the current Romberg Factor (4^k stuff)
   int k = 1;  //k, used to compute the Romberg Factor

   //if level 0 has been requested, the loop will not execute
   //the total number of executions of the loop is ??

   //DO THIS
   
   while (q1->size() > 1)
   {
      //DO THIS
      //use the algorithm described in the lab to improve the accuracy of your level 0 results

       while (q1->size() > 1) 
       {
          db = q1->dequeue();
          db1 = q1->peek();
          q2->enqueue(new Double(((pow(4, k) * db1->getValue()) - db->getValue()) 
          /(pow(4, k) - 1)));
          
          delete db;
       }
      
      db = q1->dequeue();
      delete db;
      
      swap(q1, q2);

      k++;

   }

   //obtain the final answer
   db = q1->dequeue();
   double result = db->getValue();  
   delete db;

   delete q1;
   delete q2;

   return result;
}
