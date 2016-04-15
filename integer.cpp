////////////////////////////////////////////////////////////////////////////////
// @file integer.cpp
// @author Michael Hess
// @date 2016-04-05
//
// Description: Definition for Integer class
//
////////////////////////////////////////////////////////////////////////////////
#include "integer.h"


Integer::Integer()
{
  //Need to declare an empty vector, otherwise subtraction operator will dereference a null pointer
  std::vector<bool> bits_(0);
}


Integer::Integer(int num)
{
  if (num < 0) num *= -1;
  //Fill bits
  do {
    bits_.insert(bits_.begin(), num % 2);
    num /= 2;
  } while (num > 0);
}


unsigned int Integer::decimal_()
{
  clean_();
  int result = 0;
  int iter = 0;
  for (auto i = bits_.end(); i >= bits_.begin(); --i, ++iter) {
    if (*i) {
      result += (pow(2, iter - 1));
    }
  }
  return result;
}

void Integer::equalize_(std::vector<bool>& vec_a, std::vector<bool>& vec_b)
{
  //Calculate the difference in length of the vectors
  int diff = static_cast<int>(vec_a.size() - vec_b.size());
  
  //If vector A is longer than vector B, add zeroes to the beginning to make them the same length
  if (diff > 0) {
    for (int i = 1; i <= diff; ++i) {
      vec_b.insert(vec_b.begin(), 0);
    }
  }
  
  //Do the same thing, but vice versa
  if (diff < 0) {
    for (int i = -1; i >= diff; --i) {
      vec_a.insert(vec_a.begin(), 0);
    }
  }
  return;
}


void Integer::clean_()
{
  auto i = bits_.begin();
  while (i != bits_.end())
  {
    if (!*i) {
      bits_.erase(i, i + 1);
    }
    else {
      break;
    }
  }
  //To prevent an empty vector, we add a zero if the Integer's value is equal to 0
  if (bits_.size() < 1) {
    bits_.push_back(0);
  }
}


std::string Integer::binary_string()
{
  //Create output string which will be filled
  std::string output;
  
  //Clean up vector so that it doesn't return with unnecessary leading zeroes
  clean_();
  
  //Start formatting output
  output += "(";
  for (auto i : bits_)
  {
    //Convert to int - false = 0, true = 1
    if (i)
      output += "1";
    else
      output += "0";
  }
  //More formatting
  output += ")_2";
  return output;
}

std::string Integer::decimal_string()
{
  return std::to_string(decimal_());
}

Integer& Integer::operator+= (Integer b)
{
  bool carry = 0;
  std::vector<bool> result;
  std::vector<bool> vec_a = bits_;
  std::vector<bool> vec_b = b.bits_;
  
  equalize_(vec_a, vec_b);
  
  for (int i = static_cast<int>(vec_b.size()) - 1; i >= 0; --i)
  {
    //NOTE: != is functionally equivalent to XOR
    //Compare digits:
    //1 + 0 = 1 (!carry)
    //1 + 0 = 0 (carry)
    //1 + 1 = 0 (!carry)
    //1 + 1 = 1 (carry)
    //0 + 0 = 0 (!carry)
    //0 + 0 = 1 (carry)
    result.insert(result.begin(), (vec_a[i] != vec_b[i]) != carry);
    
    //We carry if both digits are 1, or if one digit is one and we had a carry last digit
    carry = ((vec_a[i] && vec_b[i]) || (vec_a[i] && carry) || (vec_b[i] && carry));
  }
  if (carry)
    result.insert(result.begin(), 1);
  bits_ = result;
  return *this;
}


Integer& Integer::operator-= (Integer b)
{
  bool carry = 0;
  std::vector<bool> result;
  std::vector<bool> vec_a = bits_;
  std::vector<bool> vec_b = b.bits_;
  
  //If b is larger than a, swap, so that this function only returns absolute value of result
  if (decimal_() < b.decimal_()) {
    std::swap(vec_a, vec_b);
  }
  
  //Equalize size of vectors by adding leading zeroes
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
  if (carry) {
    result.insert(result.begin(), 1);
  }
  bits_ = result;
  return *this;
}


Integer& Integer::operator*= (Integer b)
{
  Integer result;
  std::vector<bool> vec_a = bits_;
  std::vector<bool> vec_b = b.bits_;
  std::vector<Integer> carry(vec_a.size());
  
  //Using binary method of addition, multiply individually by each digit in multiplier
  for (int i = static_cast<int>(vec_a.size()) - 1; i >= 0; --i)
  {
    //Iterate through multiplicand vector and multiply every digit by current working digit
    for (int m = static_cast<int>(vec_b.size()) - 1; m >= 0; --m)
    {
      //1 and 1 = 1
      //0 and 1 = 0
      //1 and 0 = 0
      carry[i].bits_.insert(carry[i].bits_.begin(), (vec_b[m] && vec_a[i]));
    }
    
    //Add a zero for each 2^k
    for (int l = static_cast<int>(vec_a.size()) - 1; l > i; --l)
    {
      carry[i].bits_.push_back(false);
    }
  }
  
  //Add each individual multiplication operation together into final vector
  for (int i = static_cast<int>(carry.size() - 1); i >= 0; --i)
  {
    result += carry[i];
  }
  
  //Set current vector equal to result
  this->bits_ = result.bits_;
  //std::cout << this->bits_[0];
  return *this;
}

Integer& Integer::operator/= (Integer b)
{
  std::vector<bool> quotient;
  Integer int_a(0); int_a.bits_.pop_back(); //Need to have an empty vector to start
  
  //If divisor is 0, then we return an error
  if (b.decimal_() == 0) {
    std::cout << "Division by 0 error!" << std::endl;
    Integer* ret = new Integer(0);
    return *ret;
  }
  
  for (int s = 0; s < b.bits_.size(); ++s) {
    int_a.bits_.push_back(bits_[s]); //create chunk vector filled with as many digits as vec_b has
  }

  for (auto i = (b.bits_.size()); i <= this->bits_.size(); ++i) {
    //int_a.clean_();
    if (int_a.decimal_() >= b.decimal_()) {
      int_a -= b; //subtract divisor from chunk
      quotient.push_back(true); //add 1 to quotient
      int_a.bits_.push_back(this->bits_[i]); //bring down next digit
    }
    else {
      quotient.push_back(false);
      int_a.bits_.push_back(bits_[i]); //bring down next digit
    }
  }
  bits_ = quotient;
  return *this;
}

Integer& Integer::operator%= (Integer b)
{
  std::vector<bool> quotient;
  Integer int_a(0); int_a.bits_.pop_back(); //Need to have an empty vector to start
  
  //If divisor is 0, then we return an error
  if (b.decimal_() == 0) {
    std::cout << "Modulus by 0 error!" << std::endl;
    Integer* ret = new Integer(0);
    return *ret;
  }
  
  for (int s = 0; s < b.bits_.size(); ++s) {
    int_a.bits_.push_back(bits_[s]); //create chunk vector filled with as many digits as vec_b has
  }
  
  for (auto i = (b.bits_.size()); i <= this->bits_.size(); ++i) {
    //int_a.clean_();
    if (int_a.decimal_() >= b.decimal_()) {
      int_a -= b; //subtract divisor from chunk
      quotient.push_back(true); //add 1 to quotient
      int_a.bits_.push_back(this->bits_[i]); //bring down next digit
    }
    else {
      quotient.push_back(false);
      int_a.bits_.push_back(bits_[i]); //bring down next digit
    }
  }
  int_a.bits_.pop_back();
  bits_ = int_a.bits_;
  return *this;
}

Integer& Integer::operator++() {
  // Create an Integer "one" with value 1
  Integer one(1);
  
  // Add "one" to this instance.
  operator+=(one);
  
  return *this;
}

Integer& Integer::operator++(int unused) {
  // Make a copy of this Integer
  Integer copy(*this);
  
  // Increment this version
  ++(*this);
  
  // Return the copy containing the previous version
  return copy;
}


Integer operator+ (Integer a, Integer b) { return a += b; }

Integer operator- (Integer a, Integer b) { return a -= b; }

Integer operator* (Integer a, Integer b) { return a *= b; }

Integer operator/ (Integer a, Integer b) { return a /= b; }

Integer operator% (Integer a, Integer b) { return a %= b; }