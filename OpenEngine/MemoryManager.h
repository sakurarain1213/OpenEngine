#pragma once
#include "IRuntimeModule.h"
#include "Allocator.h"
#include <new>

namespace My {
    class MemoryManager : _implements_ IRuntimeModule
    {
    public:
        template<typename T, typename... Arguments>
        T* New(Arguments... parameters)
        {
            return new (Allocate(sizeof(T))) T(parameters...);
        }

        template<typename T>
        void Delete(T* p)
        {
            reinterpret_cast<T*>(p)->~T();
            Free(p, sizeof(T));
        }

    
        virtual ~MemoryManager() {}

        virtual int Initialize();
        virtual void Finalize();
        virtual void Tick();

        void* Allocate(size_t size);
        void  Free(void* p, size_t size);
    private:
        static size_t* m_pBlockSizeLookup;
        static Allocator* m_pAllocators;
    
        static Allocator* LookUpAllocator(size_t size);
    };
}