#ifndef BITSET_HPP
#define BITSET_HPP
#include <string>

class Bitset{
public:

  /** default constructor
   * initializes bitset to array of type intmax_t of size 8.
   * sets all bits in array to 0 and sets isValid to true.
  */
  Bitset();

  /** constructor that takes size argument
   * takes intmax_t type argument 'size' for size of bitset.
   * as long as size is > 0, initializes the bitset of size size to all zeroes and sets isValid to true
   * otherwise, sets isValid to false and does nothing else
   */
  Bitset(intmax_t size);

  /** constructor with bitstring argument
   * takes a string of bits as the argument (e.g. "00010000")
   * and converts string to bitset. If any element in string is not a '1' or a '0', the bitset is invalid and
   * the program stops reading in bits
   * 
   * sets isValid to true when successfully setting bitset and false when above condition is not met
   */
  Bitset(const std::string & value);

  /** Default destructor
   * Deletes bit_array and deallocates memory for array
   */
  ~Bitset();

  //delete copy constructor and assignment operator
  Bitset(const Bitset & ) = delete;
  Bitset & operator=(const Bitset &) = delete;

  /** returns size of bitset */
  intmax_t size() const;

  /** returns validity of bitset */
  bool good() const;

  /** sets bit at index index to a 1. if index is >=0 or <N, bitset is marked invalid */
  void set(intmax_t index);

  /** sets bit at index index to a 1. if index is >=0 or <N, bitset is marked invalid */
  void reset(intmax_t index);

  /** toggles index index. if index is >=0 or <N, bitset is marked invalid */
  void toggle(intmax_t index);

  /** returns bool logic value of bit at index index. if index is out of range returns false */
  bool test(intmax_t index);

  /** assembles and returns bitstring of bitset */
  std::string asString() const;

private:
  //validity boolean
  bool isValid;

  //bitset size
  intmax_t N;

  //pointer to bitset container array
  intmax_t * bit_array;
};

#endif