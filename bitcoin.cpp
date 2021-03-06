#include "bitcoin.h"

volatile uint32_t counter = 0;
uint8_t sequence[] = {0x45,0x6D,0x62,0x65,0x64,0x64,0x65,0x64,
                0x20,0x53,0x79,0x73,0x74,0x65,0x6D,0x73,
                0x20,0x61,0x72,0x65,0x20,0x66,0x75,0x6E,
                0x20,0x61,0x6E,0x64,0x20,0x64,0x6F,0x20,
                0x61,0x77,0x65,0x73,0x6F,0x6D,0x65,0x20,
                0x74,0x68,0x69,0x6E,0x67,0x73,0x21,0x20,
                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
                
volatile uint64_t* key = (uint64_t*)&sequence[48];
uint64_t* nonce = (uint64_t*)&sequence[56];
uint64_t newKey;
Mutex newKey_mutex;

void computation(){
    uint8_t hash2[32];

    if(counter<5000){
        newKey_mutex.lock();
        if(*key != newKey){
            *key = newKey;
        }
        newKey_mutex.unlock();
        
        SHA256::computeHash(hash2,sequence,64);
        if(hash2[0]==0 && hash2[1]==0){
            putMessage(NONCE, 0, *nonce);
        }
        *nonce = *nonce + 1;
        counter +=1;
    }
}

void HashRate(){
        putMessage(COUNT, 0, (uint64_t)counter);
        counter=0;
}
    
