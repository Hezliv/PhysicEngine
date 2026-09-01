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

    void deallocate(T* p) /* O(1)*/ {
        ptrdiff_t block = reinterpret_cast<byte*>(p) - reinterpret_cast<byte*>(&memoryPool[0]);
        size_t index = block / sizeof(PoolBlock);
        if (index < MAX_ELEMENTS)
        {
            memoryPool[index].occupied = false;
            memoryPool[index].next = head;
            head = &memoryPool[index];
        }
    }

    void* rawAllocate() {
        if (!head) return nullptr;
        void* mem = head;
        head->occupied = true;
        head = head->next;
        return mem;
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
        void* mem = rawAllocate();
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
//    MemoryPool<int> pool;
//    int* rawMemory = pool.allocate();
//    if (!rawMemory) return -1;
//    
//
//    pool.destroy(rawMemory);
//}
