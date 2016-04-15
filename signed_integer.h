//
//  signed_integer.hpp
//  Homework 2
//
//  Created by Michael Hess on 4/9/16.
//  Copyright © 2016 Michael Hess. All rights reserved.
//

#ifndef SIGNED_INTEGER
#define SIGNED_INTEGER

#include "integer.h"

class SignedInteger : public Integer {
public:
  SignedInteger();
  SignedInteger(int num);
  std::string decimal_string();
  std::string binary_string();
  
  Integer absolute_value();

  SignedInteger& operator-= (SignedInteger b);
  SignedInteger& operator+= (SignedInteger b);
  SignedInteger& operator*= (SignedInteger b);
  SignedInteger& operator/= (SignedInteger b);
  SignedInteger& operator%= (SignedInteger b);
  
  SignedInteger& operator++();
  SignedInteger& operator++ (int unused);
  SignedInteger& operator--();
  SignedInteger& operator-- (int unused);
private:
  bool sign_;
};

SignedInteger operator- (SignedInteger a, SignedInteger b);
SignedInteger operator+ (SignedInteger a, SignedInteger b);
SignedInteger operator* (SignedInteger a, SignedInteger b);
SignedInteger operator/ (SignedInteger a, SignedInteger b);
SignedInteger operator% (SignedInteger a, SignedInteger b);

#endif /* SIGNED_INTEGER */