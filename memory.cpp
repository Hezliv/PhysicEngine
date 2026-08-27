#include <iostream>
#include<new>
using namespace std;

#define ELEMENT_SIZE 255
#define MAX_ELEMENTS 20

template <typename T, typename... Args>
class MemoryPool {
    struct PoolBlock
    {
        PoolBlock* next = nullptr;
        bool occupied = false;
        byte memory[sizeof(T)];
    };
    PoolBlock memoryPool[MAX_ELEMENTS];
    PoolBlock* head = nullptr;

    void deallocate(T* p) // O(1)
    {
        ptrdiff_t block = static_cast<byte*>(p) - memoryPool->memory;
        size_t index = block / sizeof(PoolBlock);
        if (index < MAX_ELEMENTS)
        {
            memoryPool[index].occupied = false;
            memoryPool[index].next = head;
            head = &memoryPool[index];
        }
    }
public:
    MemoryPool() { 
        for (int i = 0; i < MAX_ELEMENTS - 1; i++)
        {
            memoryPool[i].next = &memoryPool[i + 1];
        }
        head = &memoryPool[0];
    }
    
    T* allocate(Args&&... args) // O(1)
    {
        void* mem = alocate(sizeof(T));
        if (!mem) return nullptr;
        return new (mem) T(std::forward<Args>(args)...); // ??????
    }

    void destroy(T* obj)
    {
        obj->~T();
        deallocate(obj);
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
