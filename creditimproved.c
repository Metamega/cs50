/* This program takes a user input number and verifires whether its a valid
Mastercard, Visa, or Amex. It relies on user inputting correct length number. 
It will keep asking for input if string is entered. Also uses checksum algorithm
described below to verify if is a valid credit card number*/
// Check sum calculations
// Summing for every other digit IE: 13579 return: 9, 5, 1
// Multiply digits by 2          IE: 9, 5, 1 return: 18 , 10 , 2
// Sum the individual digits     IE: 18, 10 , 2 return: 1 + 8 + 1 + 0 + 2   
// Sum the left over digits      IE: 13579 return: 5 , 3
// Sum the totals, if ends in 0, check sum is validated
//                               IE: 11 + 8 = 19 return: false
//https://developer.paypal.com/docs/classic/payflow/payflow-pro/payflow-pro-testing/#credit-card-numbers-for-testing 
//used to test numbers
#include <stdio.h>
#include <cs50.h>
#include <cs50.c>
int nthdig(int a, long long b);
int card_length(long long c);
int two_dig(long long a);

int main(void)
{
    // Get user input for Credit card number
    long long n = get_long_long("Enter Valid Credit Card Number: ");

    
    int x, y , z, sum_1, sum_2;
    x = y = z = sum_1 = sum_2  =  0; // Initialize variables
   
    for (int i = 1; i < 16; i += 2)
    {
        x = nthdig(i, n) * 2;       // Getting first digits and * 2

        for (int j = 0; j < 2; j++) // If digit is 2 digits, will separate 
        {                           // and sum the total of all individual digits
            y = nthdig(j, x);
            sum_1 += y;
        }
    }
        
    for (int k = 0; k < 16; k +=2) // Sums the other digits 
    {
        z = nthdig(k, n);
        sum_2 += z;
    } 

    int total_sum = sum_1 + sum_2; // Sums both results together
    int valid;
    if (total_sum % 10 == 0) // If last digit of sums is 0, True else False
    {
        valid = 1;
    }
    else
    {
        valid = 0;
    }

     /********Logic for which type of card number was entered */// 
    int length = card_length(n); // get card length
    int begin = two_dig(n); // get first two digits 
    
    if (begin >= 40 && begin <= 49 && length == 16 && valid)
    {
        printf("VISA\n"); // Visa numbers are 16 digits long and begin with 4
    }
    else if (begin == 34 || begin == 37 && length == 13 && valid)
    {
        printf("AMEX\n"); // Amex numbers begin with 34 or 37 and are 15 long
        
    }
    else if (begin > 50 && begin < 56 && length == 16 && valid)
    {
        printf("MASTERCARD\n"); // Mastercard begin with 51, 52, 53, 54, 55
    }                           // and are 16 digits long
    else 
    {
        printf("INVALID\n");
    }
    


}

/****************Functions************/

int nthdig(int a,  long long b) // Int "a" is requested digit
{                               // Int "b" is input integer
    while(a--)                  // Count is from right to left first is 0
        b /= 10;                // IE : nthdig(3 , 13579 ) return : 3
    
    return b % 10;
}

int card_length(long long c)    // Function calculates numbers length
{
    int length = 0;             //IE: card_length(1234) return : 4
    
    while (c != 0)
    {    
        c /= 10;
        length++;               //Length increased with every division of 10;
    }
    
    return length; 
}

int two_dig(long long a)        // Function returns first two digits of number
{
    int b = 0;
    
    while(a > 100)              // Dividing by 10, when we get less than 100
        b =  a /= 10;           // we stop , This leaves us with two digits

    return b;
}

