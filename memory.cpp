#include <iostream>
#include<new>
using namespace std;

#define ELEMENT_SIZE 255
#define MAX_ELEMENTS 20

class MemoryPool {
    struct PoolBlock
    {
        PoolBlock* next = nullptr;
        bool occupied = false;
        byte memory[ELEMENT_SIZE];
    };
    PoolBlock memoryPool[MAX_ELEMENTS];
    PoolBlock* head = nullptr;
public:
    MemoryPool() {
        
        for (int i = 0; i < MAX_ELEMENTS - 1; i++)
        {
            memoryPool[i].next = &memoryPool[i + 1];
        }
        head = &memoryPool[0];
    }
    void* allocate(size_t size) // O(1)
    {
        if (size <= ELEMENT_SIZE)
        {
            auto t = head->memory;
            head = head->next;
            return t;
        }
        return nullptr;
    }

    void deallocate(void* p) // O(1)
    {
        ptrdiff_t block = static_cast<byte*>(p) - memoryPool->memory;
        size_t index = block / sizeof(PoolBlock);
        if(index < MAX_ELEMENTS)
        {
            memoryPool[index].occupied = false;
            memoryPool[index].next = head;
            head = &memoryPool[index];
        }
    }

};


//int main()
//{
//    MemoryPool pool;
//    void* rawMemory = pool.allocate(10);
//    if (!rawMemory) return -1;
//    
//
//    pool.deallocate(rawMemory);
//}
