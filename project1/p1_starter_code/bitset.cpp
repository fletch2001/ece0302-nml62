#include "bitset.hpp"

/** default constructor
 * initializes bitset to array of type intmax_t of size 8.
 * sets all bits in array to 0 and sets isValid to true.
*/
Bitset::Bitset()
{
    N = 8;
    bit_array = new intmax_t[N];

    for(unsigned int i = 0; i < N; i++)
    {
        bit_array[i] = 0;
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
        isValid = false;
    }
    else
    {
        //set N
        N = size;

        //allocate array for bit container
        bit_array = new intmax_t[N];

        //initialize all elements of Bitset to 0
        for(unsigned int i = 0; i < N; i++)
        {
            reset(i);
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
    bit_array = new intmax_t[N];
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
            if(value[i] == '1') set(i);
            else reset(i);
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
    bit_array = nullptr;
}

// TODO COMMENT
intmax_t Bitset::size() const
{
    return N;
}

// TODO COMMENT
bool Bitset::good() const
{
    return isValid;
}

// TODO COMMENT
void Bitset::set(intmax_t index)
{
    if(index >= 0 && index < N) bit_array[index] = 1;
    else isValid = false;
}

// TODO COMMENT
void Bitset::reset(intmax_t index)
{
    if(index >= 0 && index < N) bit_array[index] = 0;
    else isValid = false;
}

// TODO COMMENT
void Bitset::toggle(intmax_t index)
{
    if(index >= 0 && index < N) bit_array[index] = !bit_array[index];
    else isValid = false;
}

// TODO COMMENT
bool Bitset::test(intmax_t index)
{
    if(index >= 0 && index < N) return bit_array[index];
    else return isValid = false;
}

// TODO COMMENT
std::string Bitset::asString() const
{
    std::string bitString;
    for(unsigned int i = 0; i < N; i++) bitString += std::to_string(bit_array[i]);

    return bitString;
}