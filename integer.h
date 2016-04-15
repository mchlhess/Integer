////////////////////////////////////////////////////////////////////////////////
// @file integer.h
// @author Michael Hess
// @date 2016-04-05
//
// @class Integer
// @brief Stores an integer as a boolean vector of the binary representation of the number
// Description: This class stores an integer as a binary representaton of a vector filled with boolean values. Multiplication (*), Subtraction (-), and Addition (+) are supported as overloaded operators, as well as +=, -=, and *=
//
// Example usage:
//
// Integer a(3);
// Integer b(4);
// Integer c;
// c = a + b;
//
// cout << c.binary_string(); //Output: (111) _2
//
//
////////////////////////////////////////////////////////////////////////////////

#ifndef INTEGER
#define INTEGER

#include <vector>
#include <iostream>
#include <math.h>

class Integer {
public:
  // Default constructor
  //
  // @return an Integer object with a value of 0
  Integer();
  
  // Overloaded constructor
  //
  // @param num passed number
  // @return an Integer object with a value of num
  Integer(int num);
  
  // Generates a string with the binary representation of integer
  //
  // @return a string with binary representation of integer
  virtual std::string binary_string();
  
  // Generates a string with the decimal representation of integer
  //
  // @return a string with decimal representation of integer
  virtual std::string decimal_string();
  
  // Adds another integer to Integer referenced
  //
  // @param b second integer
  // @return a reference to the Integer called
  Integer& operator+= (Integer b);
  
  // Subtracts another integer from Integer referenced
  //
  // @param b second integer
  // @return a reference to the Integer called
  Integer& operator-= (Integer b);
  
  // Multiplies Integer referenced by another integer
  //
  // @param b second integer
  // @return a reference to the Integer called
  Integer& operator*= (Integer b);
  
  // Divides Integer referenced by another integer
  //
  // @param b second integer
  // @return a reference to the Integer called
  Integer& operator/= (Integer b);
  
  // Returns a mod b
  //
  // @param b second integer
  // @return a reference to the Integer called
  Integer& operator%= (Integer b);
  
  // Increment this integer by one (prefix)
  // @return a reference to this integer (after incrementation).
  virtual Integer& operator++();
  
  // Increment this integer by one (postfix)
  // @return a reference which stores the value before incrementation.
  virtual Integer& operator++(int unused);
protected:
  // Returns decimal value of integer
  //
  // @return integer of Integer
  unsigned int decimal_();
  
  // Deletes zero values from beginning of Integer vector
  //
  // Suggested usage: important when one large number is subtracted from another,
  // as result will likely have many leading zeroes and will take up memory
  //
  // @return void
  void clean_(); //Private member function to clean up leading zeroes
  
  void equalize_(std::vector<bool>& vec_a, std::vector<bool>& vec_b);
  
  // Vector storage of binary value of integer
  std::vector<bool> bits_;
};

// Adds two Integers
//
// @param a first integer
// @param b second integer
// @return an Integer object
Integer operator+ (Integer a, Integer b);

// Subtracts one Integer from another
//
// @param a first integer
// @param b second integer
// @return an Integer object
Integer operator- (Integer a, Integer b);

// Multiplies two Integers
//
// @param a first integer
// @param b second integer
// @return an Integer object
Integer operator* (Integer a, Integer b);

// Divides two Integers
//
// @param a first integer
// @param b second integer
// @return an Integer object
Integer operator/ (Integer a, Integer b);

// Divides two Integers
//
// @param a first integer
// @param b second integer
// @return an Integer object
Integer operator% (Integer a, Integer b);


#endif /* __INTEGER__ */


