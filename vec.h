#pragma once

#include <iostream>
#include <utility>

namespace EXP6 {

template <typename T> class vec1 {};

template <typename T> class vec2 {
  private:
    T *data_{};
    size_t size_{};
    size_t limit_{};

  public:
    vec2(size_t size = 6) : size_{}, limit_{size} { data_ = new T[size]; }

    ~vec2() {
        if (data_) {
            delete[] data_;
            data_ = nullptr;
        }
    }
};

extern int fLogMemory;       // Perform logging (0=no; nonzero=yes)?
extern int cBlocksAllocated; // Count of blocks allocated.

template <typename T> class vec3 {
  private:
    T *data_{};
    size_t size_{};
    size_t limit_{};
    unsigned int id_{};

  public:
    static unsigned int seq_;

    unsigned int &id() { return id_; }

    // # TODO0 const version of id()
    unsigned int id() const { return id_; } 

  public:
    vec3(size_t size = 6) : size_{}, limit_{size} {
        data_ = new T[size];
        // other initialization
    }

    // TODO1 copy constructor of vec3
    vec3(const vec3 &other) : size_{other.size_}, limit_{other.limit_}, id_{++seq_} {
        data_ = new T[size_];
        std::copy(other.data_, other.data_ + size_, data_);
    } 

    // TODO2 copy assign for vec3, garding case of a=a
    vec3& operator=(const vec3& other){
        if(this!=&other){
          delete[] data_;
          size_=other.size_;
          limit_=other.limit_;
          data_=new T[other.size_];
          std::copy(other.data_, other.data_+size_, data_);
          id_=++seq_;
        }
        return *this;
    }
    // TODO3 move construct for vec3
    vec3(vec3&& other) noexcept :data_{other.data_},size_{other.size_},limit_{other.limit_}, id_{other.id_}{
        other.data_=nullptr;
        other.size_=0;
        other.limit_ = 0;
        other.id_ = 0;
    }
    // TODO4 move assign for vec3, garding case of a=std::move(a)
    vec3& operator=(vec3&& other) noexcept{
        if(this!=&other){
          delete[] data_;
          data_=other.data_;
          size_ = other.size_;
          limit_ = other.limit_;
          id_ = other.id_;
          other.data_ = nullptr;
          other.size_ = 0;
          other.limit_ = 0;
          other.id_ = 0; 
        }
        return *this;
    }

    // TODO5 destructor of vec3
    ~vec3(){
      delete[] data_;
    }

    // User-defined operator new & delete
    void *operator new(size_t stAllocateBlock) {
        static int fInOpNew = 0; // Guard flag

        if (fLogMemory && !fInOpNew) {
            fInOpNew = 1;
            std::clog << "Memory block " << ++cBlocksAllocated << " malloc "
                      << stAllocateBlock << "\n";
            fInOpNew = 0;
        }
        return malloc(stAllocateBlock);
    }

    void operator delete(void *pvMem) {
        static int fInOpDelete = 0; // Guard flag
        if (fLogMemory && !fInOpDelete) {
            fInOpDelete = 1;
            std::clog << "Memory block " << cBlocksAllocated-- << " free  \n";
            fInOpDelete = 0;
        }

        free(pvMem);
    }
};

// TODO6 add operator==, using id() for comparing
template <typename T>
bool operator==(const vec3<T>& lhs, const vec3<T>& rhs) {
    return lhs.id() == rhs.id();
}


// definition of static member of seq_ in vec3
template <typename T> unsigned int vec3<T>::seq_ = 0;

} // namespace EXP6
