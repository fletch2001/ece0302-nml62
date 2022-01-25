#include "bitset.hpp"

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

// TODO COMMENT
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

// TODO COMMENT
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

// TODO COMMENT
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