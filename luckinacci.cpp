/*
 *  The Luckinacci Sieve
 *  Program by Casey Brito
 *  
 *  Original Program (c) 2013, Revisions (c) 2018.
 *
 */

#include <iostream>
#include <unistd.h>
#include <list>
#include <cmath>

using namespace std;

//Global variables to maximize the amount of memory we can use.
list<int> Luckinacci;
list<int> Fibonacci;
list<int> Prime;

int main(int argc, char **argv) 
{
    unsigned int luckinacciMax;
    //Main program loop
    while(true) 
    {
        //Erase the lists in case we want to run the program again
        Luckinacci.clear();
        Fibonacci.clear();
        Prime.clear();
        
        //Initial program setup
        cout << "What number should the Luckinacci-Prime comparison stop at?: ";
        
        cin >> luckinacciMax;
        
        //Seed Values for the Fibonacci Sequence
        Fibonacci.push_back(2);
        Fibonacci.push_back(3);
        
        //Generate nitial Luckinacci Sieve (odd numbers only since even numbers are guaranteed to be eliminated)
        for(int i = 1; i <= luckinacciMax; i = i+2) 
        {
            Luckinacci.push_back(i);
        }
        
        //Now, begin sieving the Luckinacci list based on the Fibonacci sequence
        for(int i = Fibonacci.back(); i <= luckinacciMax; i = Fibonacci.back())
        {
            unsigned int counter = 1;
            //Iterate through the Luckinacci list deleting the ith element
            for(list<int>::iterator j = Luckinacci.begin(); j != Luckinacci.end(); ++j, counter++) 
            {
                //Delete every ith element in the list
                if(counter % i == 0)
                {   
                    Luckinacci.erase(j++);
                    --j;
                }
            }
            //Generate the next Fibonacci number
            Fibonacci.push_back(Fibonacci.back() + *prev(Fibonacci.end(), 2));
            
        }
        
        //Print the Luckinacci numbers that we generated
        cout << "There are " << Luckinacci.size() << " Luckinacci numbers ≤ " << luckinacciMax << ". They are:" << endl;
        for(list<int>::iterator i = Luckinacci.begin(); i != Luckinacci.end(); ++i) {
            cout << *i << "  ";
        }
        cout << endl;
        
        /*
         *  END OF LUCKINACCI GENERATION
         */
        
        //Numerical calculations for the analysis of the Luckinaccis
        cout << "\nGeneral x/ln(x) approximation:\n\t" << ((double)luckinacciMax)/log((double)luckinacciMax) << "\t (compare to " << Luckinacci.size() << ")" << endl;
        cout << "(No. of Luckinaccis ≤ " << luckinacciMax << ")/[" << luckinacciMax << 
            "/ln(" << luckinacciMax << ")] = " << ((double)Luckinacci.size()) / (((double)luckinacciMax) / log((double)luckinacciMax)) << endl;
        
        //Determine if we need to rerun the program
        cout << "Rerun the program for another number of Luckinaccis? (y/n): ";
        char choice;
        cin >> choice;
        if (choice == 'y' || choice == 'Y') 
        {
            continue;
        } 
        else 
        {
            break;
        }
        
    }
    
    //Prime number generation (excluding all non-trivial multiples of 2)
    Prime.push_back(2);
    for(int i = 3; i <= Luckinacci.back(); i = i+2) 
    {
        Prime.push_back(i);
    }
    
    //Cycle through the list and cross out all numbers that aren't prime
    for(list<int>::iterator i = next(Prime.begin(), 1); i != Prime.end(); ++i)
    {
        //Iterate through the Prime list deleting the ith element
        for(list<int>::iterator j = next(i,1); j != Prime.end(); ++j) 
        {
            //Delete every ith element in the list
            if(*j % *i == 0)
            {   
                Prime.erase(j++);
                j--;
            }
        }
    }
    
    //Print the Prime numbers that we generated
    cout << "There are " << Prime.size() << " Prime numbers ≤ " << luckinacciMax << ". They are:" << endl;
    for(list<int>::iterator i = Prime.begin(); i != Prime.end(); ++i)
    {
        cout << *i << "  ";
    }
    cout << endl;
    
    //Now we want to find the intersection between the two lists.
    for(list<int>::iterator prime = Prime.begin(), luckinacci = Luckinacci.begin(); prime != Prime.end(); prime++)
    {
        while(luckinacci != Luckinacci.end())
        {
            if(*prime > *luckinacci)
            {
                Luckinacci.erase(luckinacci++);

            }
            else if(*prime < *luckinacci)
            {
                break;
            }
            else    //They are equal
            {
                ++luckinacci;
                break;
            }
        }
        //Executes only at the very end of the loop
        if(next(prime, 1) == Prime.end())
        {
            Luckinacci.erase(luckinacci, Luckinacci.end());
        }
    }
    
    //Print the Luckinacci-Primes that we generated
    cout << "There are " << Luckinacci.size() << " Luckinacci-Primes ≤ " << luckinacciMax << ". They are:" << endl;
    for(list<int>::iterator i = Luckinacci.begin(); i != Luckinacci.end(); ++i) {
        cout << *i << "  ";
    }
    cout << endl;
    
    cout << "The ratio of " << luckinacciMax << "/ln(" << luckinacciMax << ") to " << Luckinacci.size() << 
    " (the number of Luckinacci-Primes) is \n\t" << ((double)luckinacciMax / log((double)luckinacciMax)) / ((double)Luckinacci.size()) << endl;
    
    cout << "Press any key to continue...";
    char input;
    cin >> input;
    
    //Now we will compute the ratio of the number of Luckinacci-Primes to the number of Primes up to luckinacciMax
    unsigned int primeCounter = 0, luckinacciPrimeCounter = 0;
    
    //Iterate through the Luckinacci-Primes
    for(list<int>::const_iterator luckinacciPrime = Luckinacci.begin(), prime = Prime.begin(); luckinacciPrime != Luckinacci.end(); luckinacciPrime++)
    {
        //Increase the LP-counter
        luckinacciPrimeCounter++;
        
        //Iterate through the primes up to the current luckinacciPrime
        while(prime != Prime.end())
        {
            
            if(*prime <= *luckinacciPrime)
            {
                primeCounter++;
                ++prime;
                if(primeCounter % 500 == 0)
                    {
                        cout << "The ratio of the number of Luckinacci-Primes to the number of Primes ≤ " << *luckinacciPrime << " is r = "
                    << ((double)luckinacciPrimeCounter)/((double)primeCounter) << endl;
                    }
            }
            else
            {
                break;
            }
        }
        
        cout << "The ratio of the number of Luckinacci-Primes to the number of Primes ≤ " << *luckinacciPrime << " is r = "
                    << ((double)luckinacciPrimeCounter)/((double)primeCounter) << "\t\t\t";
                    cout.flush();
                    usleep(1000);
                    cout << "\r";
                    
    }
    cout << endl;
    cout << "Counted " << primeCounter << " primes, and " << luckinacciPrimeCounter << " Luckinacci-Primes." << endl;
    
    return 0;
}
