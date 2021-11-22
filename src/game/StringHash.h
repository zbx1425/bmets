#pragma once

typedef unsigned long long hash_t;  
   
constexpr hash_t prime = 0x100000001B3ull;  
constexpr hash_t basis = 0xCBF29CE484222325ull;  
  
hash_t strhash(char const* str) {  
    hash_t ret{basis};  
   
    while(*str) {  
        ret ^= *str;  
        ret *= prime;  
        str++;  
    }  
   
    return ret;  
}  

constexpr hash_t static_hash(char const* str, hash_t last_value = basis) {  
    return *str ? static_hash(str+1, (*str ^ last_value) * prime) : last_value;  
}  