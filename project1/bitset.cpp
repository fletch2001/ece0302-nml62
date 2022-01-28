#include "bitset.hpp"
#include <cmath>

/** default constructor
 * initializes bitset to array of type intmax_t of size 8.
 * sets all bits in array to 0 and sets isValid to true.
*/
Bitset::Bitset()
{
    N = 8;
    numEl = std::ceil(N/ELEMENT_BIT_SIZE);
    bit_array = new u_int8_t[numEl];

    for(unsigned int i = 0; i < numEl; i++)
    {
        resetBit(i);
    }
    isValid = true;
}

/** constructor that takes size argument
 * takes intmax_t type argument 'size' for size of bitset.
 * as long as size is > 0, initializes the bitset of size size to all zeroes and sets isValid to true
 * otherwise, sets isValid to false and does nothing else
 */
Bitset::Bitset(intmax_t size)
{
    if(size <= 0)
    {
        N = 0;
        numEl = 0;
        isValid = false;
    }
    else
    {
        //set N
        N = size;

        numEl = std::ceil(N/ELEMENT_BIT_SIZE);

        //allocate array for bit container
        bit_array = new u_int8_t[numEl];

        //initialize all elements of Bitset to 0
        for(unsigned int i = 0; i < N; i++)
        {
            resetBit(i);
        }

        isValid = true;   
    }
}

/** constructor with bitstring argument
 * takes a string of bits as the argument (e.g. "00010000")
 * and converts string to bitset. If any element in string is not a '1' or a '0', the bitset is invalid and
 * the program stops reading in bits
 * 
 * sets isValid to true when successfully setting bitset and false when above condition is not met
 */
Bitset::Bitset(const std::string & value)
{
    N = value.length();
    numEl = std::ceil(N/ELEMENT_BIT_SIZE);
    if(N <= 0){
        isValid = false;
    }else{
        bit_array = new u_int8_t[numEl];
        isValid = true;
        for(unsigned int i = 0; i < value.length(); i++)
        {
            if(value[i] != '1' && value[i] != '0')
            {
                isValid = false;
                break;
            }
            else
            {
                isValid = true;
                if(value[i] == '1') setBit(i);
                else resetBit(i);
            }
        }
    }
}

/** Default destructor
 * Deletes bit_array and deallocates memory for array
 */
Bitset::~Bitset()
{
    //delete and deallocate bit array if N > 0
    //assign nullptr to bit_array
    if(size() > 0) delete [] bit_array;
        //else delete bit_array;
    bit_array = nullptr;
}

/** returns size of bitset */
intmax_t Bitset::size() const
{
    return N;
}

/** returns validity of bitset */
bool Bitset::good() const
{
    return isValid;
}

/** sets bit at index index to a 1. if index is >=0 or <N, bitset is marked invalid */
void Bitset::set(intmax_t index)
{
    if(index >= 0 && index < N) setBit(index);
    else isValid = false;
}

/** sets bit at index index to a 0. if index is >=0 or <N, bitset is marked invalid */
void Bitset::reset(intmax_t index)
{
    if(index >= 0 && index < N) resetBit(index);
    else isValid = false;
}

/** toggles index index. if index is >=0 or <N, bitset is marked invalid */
void Bitset::toggle(intmax_t index)
{
    if(index >= 0 && index < N) toggleBit(index);
    else isValid = false;
}

/** returns bool logic value of bit at index index. if index is out of range returns false */
bool Bitset::test(intmax_t index)
{
    if(index >= 0 && index < N) return getBit(index);
    else return isValid = false;
}

/** assembles and returns bitstring of bitset */
std::string Bitset::asString() const
{
    std::string bitString;
    for(unsigned int i = 0; i < N; i++) bitString += std::to_string(getBit(i));

    return bitString;
}
/*
11 10 9 8  7 6 5 4   3 2 1 0
|=|=|=|=| |=|=|=|=| |=|=|=|=|
    2        1          0

   numEl = 3
   ELEMENT_BIT_SIZE = 4

    index = 2

        elNum = index / ELEMENT_BIT_SIZE = 0.5 = 0

    index = 5

        elNum = index / ELEMENT_BIT_SIZE = 5/4 = 1.25 = 1


    SETTING

        set bit 3 to 1

        1. get element number for bit 3
            elNum = index / ELEMENT_BIT_SIZE = 3/4 = 0
        2. create mask
            u_int4_t = 1(u_int4_t) << (3 - elNum * ELEMENT_BIT_SIZE ) 'shifts 1 3 bits to the left'

*/

/** returns bit value at index */
u_int8_t Bitset::getBit(intmax_t index) const
{
    u_int8_t elNum = std::ceil(index / ELEMENT_BIT_SIZE); 

    //bit shift left and and with array element to obtain bit and bit shift right to get 1 or 0
    return (bit_array[elNum] & ((u_int8_t)1 << (index - (elNum * ELEMENT_BIT_SIZE)))) >> (index - (elNum * ELEMENT_BIT_SIZE));
}

/** sets bit at index */
void Bitset::setBit(intmax_t index)
{
    u_int8_t elNum = std::ceil(index / ELEMENT_BIT_SIZE); 

    bit_array[elNum] |= ((u_int8_t)1 << (index - (elNum * ELEMENT_BIT_SIZE)));
}

/** resets bit at index */
void Bitset::resetBit(intmax_t index)
{
    u_int8_t elNum = std::ceil(index / ELEMENT_BIT_SIZE); 

    bit_array[elNum] &= ~((u_int8_t)1 << (index - (elNum * ELEMENT_BIT_SIZE)));
}

/** toggles bit at index */
void Bitset::toggleBit(intmax_t index)
{
    u_int8_t elNum = std::ceil(index / ELEMENT_BIT_SIZE); 

    bit_array[elNum] ^= ((u_int8_t)1 << (index - (elNum * ELEMENT_BIT_SIZE)));
}