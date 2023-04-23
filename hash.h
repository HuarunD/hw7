#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <ctime>
#include <cstdlib>
typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
			HASH_INDEX_T wValues[5] = {0,0,0,0,0};
			int length = k.size();
			for(int i=0; i<length/6+1; i++){
				unsigned long long sum = 0;
				for(int j= 0 ; j<6; j++){
					if(length-(i+1)*6+j <0){
						sum +=0;
					}
					else{
						sum = sum* 36 + letterDigitToNumber(k[length-(i+1)*6+j]);
					}
					//std::cout << sum << std::endl;
				}
				wValues[5-i-1] = sum;
				//std::cout << wValues[5-i-1] << std::endl;
			}
			unsigned long long hashed = 0;
			for(int i=0; i<5; i++){
				hashed += rValues[i]*wValues[i];
			}
			return hashed;

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
				HASH_INDEX_T temp = (int)letter;

				if(temp <=57){
					temp -= 22;
					return temp;
				}
				else{
					if(temp <=90){
						temp +=32;
					}
					temp-= 97;
					//std::cout << temp << std::endl;
					return  temp;
				}
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
