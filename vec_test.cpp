#include <cassert>
#include <gtest/gtest.h>
#include <memory>
#include <type_traits>

#include "vec.h"

using namespace EXP6;

// helper functions for memory monitoring
// operator new[]/delete[] override globally
void *operator new[](std::size_t sz) {
    void *ptr = std::malloc(sz);
    std::clog << "global new, location=" << ptr << " size=" << sz << '\n';
    return ptr;
}

void operator delete[](void *ptr) {
    std::clog << "global del, location=" << ptr << '\n';
    std::free(ptr);
}

// vec1 test
TEST(vec1, regular_function) {
    EXPECT_EQ(std::is_constructible<vec1<double>>{}, true);
    EXPECT_EQ(std::is_default_constructible<vec1<double>>{}, true);
    EXPECT_EQ(std::is_copy_constructible<vec1<double>>{}, true);
    EXPECT_EQ(std::is_copy_assignable<vec1<double>>{}, true);
    EXPECT_EQ(std::is_move_constructible<vec1<double>>{}, true);
    EXPECT_EQ(std::is_move_assignable<vec1<double>>{}, true);
    EXPECT_EQ(std::is_destructible<vec1<double>>{}, true);
}

// vec2 test
TEST(vec2, regular_function) {
    EXPECT_EQ(std::is_constructible<vec2<double>>{}, true);
    EXPECT_EQ(std::is_default_constructible<vec2<double>>{}, true);
    EXPECT_EQ(std::is_copy_constructible<vec2<double>>{}, true);
    EXPECT_EQ(std::is_copy_assignable<vec2<double>>{}, true);
    EXPECT_EQ(std::is_move_constructible<vec2<double>>{}, true);
    EXPECT_EQ(std::is_move_assignable<vec2<double>>{}, true);
    EXPECT_EQ(std::is_destructible<vec2<double>>{}, true);
}

// for vec2 test : both copy_construct & copy_assign will cause segment fault,
// Please comment them.
// TEST(vec2, copy_construct) {
    // std::clog << "vec2: copy_construct" << '\n';
    // {
        // vec2<double> big(10240);
        // { vec2<double> small{big}; }
    // }
// }
// 
// TEST(vec2, copy_assign) {
    // std::clog << "vec2: copy_assign" << '\n';
    // {
        // vec2<double> big(10240);
        // {
            // vec2<double> small(6);
            // small = big;
        // }
    // }
// }

// vec3 test
TEST(vec3, regular_function) {
    EXPECT_EQ(std::is_constructible<vec3<double>>{}, true);
    EXPECT_EQ(std::is_default_constructible<vec3<double>>{}, true);
    EXPECT_EQ(std::is_copy_constructible<vec3<double>>{}, true);
    EXPECT_EQ(std::is_copy_assignable<vec3<double>>{}, true);
    EXPECT_EQ(std::is_move_constructible<vec3<double>>{}, true);
    EXPECT_EQ(std::is_move_assignable<vec3<double>>{}, true);
    EXPECT_EQ(std::is_destructible<vec3<double>>{}, true);
}

TEST(vec3, copy_construct) {
    std::clog << "vec3: copy_construct" << '\n';
    {
        vec3<double> big(10240);
        { vec3<double> small{big}; }
    }
    EXPECT_TRUE(cBlocksAllocated == 0);
}

TEST(vec3, copy_assign) {
    std::clog << "vec3: copy_assign" << '\n';
    {
        vec3<double> big(10240);
        {
            vec3<double> small(6);
            small = big;
        }
    }
    EXPECT_TRUE(cBlocksAllocated == 0);
}

TEST(vec3, copy_assign_to_sefl) {
    std::clog << "vec3: copy_assign_to_sefl" << '\n';
    {
        vec3<double> big(10240);
        { big = big; }
    }
    EXPECT_TRUE(cBlocksAllocated == 0);
}

TEST(vec3, copy_assign_by_pointer) {
    std::clog << "vec3: copy_assign_by_pointer" << '\n';
    {
        vec3<double> *big = new vec3<double>(10240);
        {
            vec3<double> *small = new vec3<double>(6);
            *small = *big;
            delete small;
        }
        delete big;
    }
    EXPECT_TRUE(cBlocksAllocated == 0);
}

TEST(vec3, move_construct) {
    std::clog << "vec3: move_construct" << '\n';
    {
        vec3<double> big(10240);
        { vec3<double> small{std::move(big)}; }
    }
    EXPECT_TRUE(cBlocksAllocated == 0);
}

TEST(vec3, move_assign) {
    std::clog << "vec3: move_assign" << '\n';
    {
        vec3<double> big(10240);
        {
            vec3<double> small(6);
            small = std::move(big);
        }
    }
    EXPECT_TRUE(cBlocksAllocated == 0);
}

TEST(vec3, move_assign_to_self) {
    std::clog << "vec3: move_assign_to_self" << '\n';
    {
        vec3<double> big(10240);
        { big = std::move(big); }
    }
    EXPECT_TRUE(cBlocksAllocated == 0);
}