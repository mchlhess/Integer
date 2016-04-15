//
//  signed_integer.cpp
//  Homework 2
//
//  Created by Michael Hess on 4/9/16.
//  Copyright © 2016 Michael Hess. All rights reserved.
//

#include "signed_integer.h"

// Default constructor
SignedInteger::SignedInteger() : Integer()
{
  //Set Integer to postive zero
  sign_ = false;
}

// Overloaded constructor
// Calls Integer constructor, then sets sign_ based on sign of Integer
SignedInteger::SignedInteger(int num) : Integer(num)
{
  //Find out whether positive or negative
  //If negative, set sign bit to 1
  //If positive, sign bit is 0
  if (num < 0)
  {
    sign_ = true;
  }
  else
  {
    sign_ = false;
  }
}

// Generates a string with decimal representation of Integer
//
// @return a string with decimal
std::string SignedInteger::decimal_string() {
  std::string output;
  if (sign_) {
    return "-" + Integer::decimal_string();
  }
  else {
    return "+" + Integer::decimal_string();
  }
}

std::string SignedInteger::binary_string() {
  if (sign_) {
    return "-" + Integer::binary_string();
  }
  else {
    return "+" + Integer::binary_string();
  }
}

Integer SignedInteger::absolute_value()
{
  return Integer(decimal_());
}

SignedInteger& SignedInteger::operator+= (SignedInteger b)
{
  //-a + b = b - a
  if (sign_ && !b.sign_) {
    std::swap(*this, b);
    b.sign_ = false;
    return (*this -= b);
  }
  //a + (-b) = a - b
  else if (!sign_ && b.sign_) {
    b.sign_ = false;
    return *this -= b;
  }
  //a + b = a + b
  //-a + -b = -(a + b)
  else {
    Integer::operator+=(b);
    return *this;
  }
}

SignedInteger& SignedInteger::operator-=(SignedInteger b)
{
  bool carry = 0;
  bool overflow = false;
  std::vector<bool> result;
  std::vector<bool> vec_a = bits_;
  std::vector<bool> vec_b = b.bits_;
  
  if (!sign_ && !b.sign_) {
    //If subtracting number is greater, then result will be negative so switch the two numbers and set overflow negative
    if (decimal_() < b.decimal_()) {
      std::swap(vec_a, vec_b);
      overflow = true;
    }
    
    //Equalize length of vectors
    equalize_(vec_a, vec_b);
    
    for (int i = static_cast<int>(vec_b.size()) - 1; i >= 0; --i) {
      //Compare digits:
      //0 - 0 = 0 (!carry) -
      //0 - 0 = 1 (carry) -
      //0 - 1 = 1 (!carry)
      //0 - 1 = 0 (carry)
      //1 - 0 = 1 (!carry)
      //1 - 0 = 0 (carry)
      //1 - 1 = 0 (!carry) -
      //1 - 1 = 1 (carry) -
      result.insert(result.begin(), (((vec_a[i] == vec_b[i]) == carry) || ((!vec_a[i] && vec_b[i]) && !carry) || ((vec_a[i] && !vec_b[i]) && !carry)));
      
      //Carry if digits equal AND carry from last digit, or carry if 0 - 1 and no carry
      carry = (((vec_a[i] == vec_b[i]) && carry) || (!vec_a[i] && vec_b[i]));
    }
    //If carry, we have to insert an extra 1
    if (carry) {
      result.insert(result.begin(), 1);
    }
    
    if (overflow)
    {
      sign_ = true;
    }
    bits_ = result;
    return *this;
  }
  
  else if (sign_ && !b.sign_) {
    Integer::operator+=(b);
    return *this;
  }
  
  else if (sign_ && b.sign_) {
    if (decimal_() < b.decimal_()) {
      std::swap(vec_a, vec_b);
      Integer::operator-=(b);
      sign_ = false;
      return *this;
    }
    else {
      Integer::operator-=(b);
      return *this;
    }
  }
  
  else if (!sign_ && b.sign_) {
    Integer::operator+=(b);
    return *this;
  }
  return *this;
}

SignedInteger& SignedInteger::operator*=(SignedInteger b)
{
  if (sign_ && b.sign_) {
    sign_ = false;
    Integer::operator*=(b);
    return *this;
  }
  else if (sign_ || b.sign_) {
    sign_ = true;
    Integer::operator*=(b);
    return *this;
  }
  else {
    Integer::operator*=(b);
    return *this;
  }
}

SignedInteger& SignedInteger::operator/= (SignedInteger b) {
  if (sign_ && b.sign_) {
    sign_ = false;
    Integer::operator/=(b);
    return *this;
  }
  else if (sign_ || b.sign_) {
    sign_ = true;
    Integer::operator/=(b);
    return *this;
  }
  else {
    Integer::operator/=(b);
    return *this;
  }
}

SignedInteger& SignedInteger::operator%= (SignedInteger b) {
  Integer::operator%=(b);
  return *this;
}

SignedInteger& SignedInteger::operator++() {
  // Create an Integer "one" with value 1
  SignedInteger one(1);
  
  // Add "one" to this instance.
  operator+=(one);
  
  return *this;
}

SignedInteger& SignedInteger::operator++(int unused) {
  // Make a copy of this Integer
  SignedInteger copy(*this);
  
  // Increment this version
  SignedInteger::operator++();
  
  // Return the copy containing the previous version
  return copy;
}

SignedInteger& SignedInteger::operator--() {
  // Create an Integer "one" with value 1
  SignedInteger one(1);
  
  // Subtract "one" from this instance.
  operator-=(one);
  
  return *this;
}

SignedInteger& SignedInteger::operator--(int unused) {
  // Make a copy of this Integer
  SignedInteger copy(*this);
  
  // Decrement this version
  SignedInteger::operator--();
  
  // Return the copy containing the previous version
  return copy;
}

SignedInteger operator+ (SignedInteger a, SignedInteger b) { return a += b; }
SignedInteger operator- (SignedInteger a, SignedInteger b) { return a -= b; }
SignedInteger operator* (SignedInteger a, SignedInteger b) { return a *= b; }
SignedInteger operator/ (SignedInteger a, SignedInteger b) { return a /= b; }
SignedInteger operator% (SignedInteger a, SignedInteger b) { return a %= b; }