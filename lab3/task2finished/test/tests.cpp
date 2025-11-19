#include <gtest/gtest.h>
extern "C" {
    #include "../include/func.h"
}


// ============= ТЕСТЫ ДЛЯ ПРОСТЫХ ТИПОВ (int) =============


class VectorSimpleTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Используйте простые функции для int
    }
};


TEST_F(VectorSimpleTest, CreateVector_EmptyCapacity) {
    Vector v = create_vector(0, is_equal_simple, CopyVoidPtr_simple, DeleteVoidPtr_simple);
    EXPECT_EQ(v.size, 0);
    EXPECT_EQ(v.capacity, 0);
    EXPECT_EQ(v.data, nullptr);
    erase_vector(&v);
}


TEST_F(VectorSimpleTest, CreateVector_WithCapacity) {
    Vector v = create_vector(5, is_equal_simple, CopyVoidPtr_simple, DeleteVoidPtr_simple);
    EXPECT_EQ(v.size, 0);
    EXPECT_EQ(v.capacity, 5);
    EXPECT_NE(v.data, nullptr);
    erase_vector(&v);
}


TEST_F(VectorSimpleTest, PushBack_SingleElement) {
    Vector v = create_vector(5, is_equal_simple, CopyVoidPtr_simple, DeleteVoidPtr_simple);
    
    VECTOR_TYPE val = 42;
    push_back_vector(&v, val);
    
    EXPECT_EQ(v.size, 1);
    
    VECTOR_TYPE result;
    EXPECT_EQ(get_at_vector(&v, 0, &result), 0);
    EXPECT_EQ(result, 42);
    
    erase_vector(&v);
}


TEST_F(VectorSimpleTest, PushBack_MultipleElements) {
    Vector v = create_vector(2, is_equal_simple, CopyVoidPtr_simple, DeleteVoidPtr_simple);
    
    push_back_vector(&v, 10);
    push_back_vector(&v, 20);
    push_back_vector(&v, 30);
    
    EXPECT_EQ(v.size, 3);
    EXPECT_GE(v.capacity, 3);
    
    VECTOR_TYPE result;
    EXPECT_EQ(get_at_vector(&v, 0, &result), 0);
    EXPECT_EQ(result, 10);
    EXPECT_EQ(get_at_vector(&v, 1, &result), 0);
    EXPECT_EQ(result, 20);
    EXPECT_EQ(get_at_vector(&v, 2, &result), 0);
    EXPECT_EQ(result, 30);
    
    erase_vector(&v);
}


TEST_F(VectorSimpleTest, PushBack_Reallocation) {
    Vector v = create_vector(0, is_equal_simple, CopyVoidPtr_simple, DeleteVoidPtr_simple);
    
    for (int i = 0; i < 10; i++) {
        push_back_vector(&v, i);
    }
    
    EXPECT_EQ(v.size, 10);
    
    VECTOR_TYPE result;
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(get_at_vector(&v, i, &result), 0) << "Failed to get element at index " << i;
        EXPECT_EQ(result, i) << "Element at index " << i;
    }
    
    erase_vector(&v);
}


TEST_F(VectorSimpleTest, DeleteAt_MiddleElement) {
    Vector v = create_vector(5, is_equal_simple, CopyVoidPtr_simple, DeleteVoidPtr_simple);
    
    push_back_vector(&v, 10);
    push_back_vector(&v, 20);
    push_back_vector(&v, 30);
    push_back_vector(&v, 40);
    
    delete_at_vector(&v, 1);
    
    EXPECT_EQ(v.size, 3);
    
    VECTOR_TYPE result;
    EXPECT_EQ(get_at_vector(&v, 0, &result), 0);
    EXPECT_EQ(result, 10);
    EXPECT_EQ(get_at_vector(&v, 1, &result), 0);
    EXPECT_EQ(result, 30);
    EXPECT_EQ(get_at_vector(&v, 2, &result), 0);
    EXPECT_EQ(result, 40);
    
    erase_vector(&v);
}


TEST_F(VectorSimpleTest, DeleteAt_FirstElement) {
    Vector v = create_vector(5, is_equal_simple, CopyVoidPtr_simple, DeleteVoidPtr_simple);
    
    push_back_vector(&v, 10);
    push_back_vector(&v, 20);
    push_back_vector(&v, 30);
    
    delete_at_vector(&v, 0);
    
    EXPECT_EQ(v.size, 2);
    
    VECTOR_TYPE result;
    EXPECT_EQ(get_at_vector(&v, 0, &result), 0);
    EXPECT_EQ(result, 20);
    EXPECT_EQ(get_at_vector(&v, 1, &result), 0);
    EXPECT_EQ(result, 30);
    
    erase_vector(&v);
}


TEST_F(VectorSimpleTest, DeleteAt_LastElement) {
    Vector v = create_vector(5, is_equal_simple, CopyVoidPtr_simple, DeleteVoidPtr_simple);
    
    push_back_vector(&v, 10);
    push_back_vector(&v, 20);
    push_back_vector(&v, 30);
    
    delete_at_vector(&v, 2);
    
    EXPECT_EQ(v.size, 2);
    
    VECTOR_TYPE result;
    EXPECT_EQ(get_at_vector(&v, 0, &result), 0);
    EXPECT_EQ(result, 10);
    EXPECT_EQ(get_at_vector(&v, 1, &result), 0);
    EXPECT_EQ(result, 20);
    
    erase_vector(&v);
}


TEST_F(VectorSimpleTest, EraseVector_ClearsData) {
    Vector v = create_vector(5, is_equal_simple, CopyVoidPtr_simple, DeleteVoidPtr_simple);
    
    push_back_vector(&v, 10);
    push_back_vector(&v, 20);
    
    erase_vector(&v);
    
    EXPECT_EQ(v.size, 0);
    EXPECT_EQ(v.capacity, 0);
    EXPECT_EQ(v.data, nullptr);
}


TEST_F(VectorSimpleTest, IsEqualVector_EqualVectors) {
    Vector v1 = create_vector(5, is_equal_simple, CopyVoidPtr_simple, DeleteVoidPtr_simple);
    Vector v2 = create_vector(5, is_equal_simple, CopyVoidPtr_simple, DeleteVoidPtr_simple);
    
    push_back_vector(&v1, 10);
    push_back_vector(&v1, 20);
    push_back_vector(&v1, 30);
    
    push_back_vector(&v2, 10);
    push_back_vector(&v2, 20);
    push_back_vector(&v2, 30);
    
    EXPECT_EQ(is_equal_vector(&v1, &v2), 1);
    
    erase_vector(&v1);
    erase_vector(&v2);
}


TEST_F(VectorSimpleTest, IsEqualVector_DifferentSizes) {
    Vector v1 = create_vector(5, is_equal_simple, CopyVoidPtr_simple, DeleteVoidPtr_simple);
    Vector v2 = create_vector(5, is_equal_simple, CopyVoidPtr_simple, DeleteVoidPtr_simple);
    
    push_back_vector(&v1, 10);
    push_back_vector(&v1, 20);
    
    push_back_vector(&v2, 10);
    
    EXPECT_EQ(is_equal_vector(&v1, &v2), 0);
    
    erase_vector(&v1);
    erase_vector(&v2);
}


TEST_F(VectorSimpleTest, IsEqualVector_DifferentElements) {
    Vector v1 = create_vector(5, is_equal_simple, CopyVoidPtr_simple, DeleteVoidPtr_simple);
    Vector v2 = create_vector(5, is_equal_simple, CopyVoidPtr_simple, DeleteVoidPtr_simple);
    
    push_back_vector(&v1, 10);
    push_back_vector(&v1, 20);
    
    push_back_vector(&v2, 10);
    push_back_vector(&v2, 99);
    
    EXPECT_EQ(is_equal_vector(&v1, &v2), 0);
    
    erase_vector(&v1);
    erase_vector(&v2);
}


TEST_F(VectorSimpleTest, CopyVector_ExistingVector) {
    Vector src = create_vector(5, is_equal_simple, CopyVoidPtr_simple, DeleteVoidPtr_simple);
    Vector dest = create_vector(3, is_equal_simple, CopyVoidPtr_simple, DeleteVoidPtr_simple);
    
    push_back_vector(&src, 10);
    push_back_vector(&src, 20);
    push_back_vector(&src, 30);
    
    push_back_vector(&dest, 99);
    
    copy_vector(&dest, &src);
    
    EXPECT_EQ(dest.size, 3);
    EXPECT_EQ(is_equal_vector(&src, &dest), 1);
    
    VECTOR_TYPE result;
    EXPECT_EQ(get_at_vector(&dest, 0, &result), 0);
    EXPECT_EQ(result, 10);
    EXPECT_EQ(get_at_vector(&dest, 1, &result), 0);
    EXPECT_EQ(result, 20);
    EXPECT_EQ(get_at_vector(&dest, 2, &result), 0);
    EXPECT_EQ(result, 30);
    
    erase_vector(&src);
    erase_vector(&dest);
}


TEST_F(VectorSimpleTest, CopyVectorNew_CreatesNewVector) {
    Vector src = create_vector(5, is_equal_simple, CopyVoidPtr_simple, DeleteVoidPtr_simple);
    
    push_back_vector(&src, 10);
    push_back_vector(&src, 20);
    push_back_vector(&src, 30);
    
    Vector *dest = copy_vector_new(&src);
    
    ASSERT_NE(dest, nullptr);
    EXPECT_EQ(dest->size, 3);
    EXPECT_EQ(is_equal_vector(&src, dest), 1);
    
    VECTOR_TYPE result;
    EXPECT_EQ(get_at_vector(dest, 0, &result), 0);
    EXPECT_EQ(result, 10);
    EXPECT_EQ(get_at_vector(dest, 1, &result), 0);
    EXPECT_EQ(result, 20);
    EXPECT_EQ(get_at_vector(dest, 2, &result), 0);
    EXPECT_EQ(result, 30);
    
    erase_vector(&src);
    delete_vector(dest);
}


TEST_F(VectorSimpleTest, DeleteVector_FreesMemory) {
    Vector *v = (Vector*)malloc(sizeof(Vector));
    *v = create_vector(5, is_equal_simple, CopyVoidPtr_simple, DeleteVoidPtr_simple);
    
    push_back_vector(v, 10);
    push_back_vector(v, 20);
    
    delete_vector(v);
    
    SUCCEED();
}


// ============= ТЕСТЫ ДЛЯ СЛОЖНЫХ ТИПОВ (char*) =============


#ifdef VECTOR_TYPE_HARD


class VectorHardTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Используем функции для строк
    }
};


TEST_F(VectorHardTest, PushBack_Strings) {
    Vector v = create_vector(5, is_equal_hard, CopyVoidPtr_hard, DeleteVoidPtr_hard);
    
    push_back_vector(&v, (char*)"Hello");
    push_back_vector(&v, (char*)"World");
    push_back_vector(&v, (char*)"Test");
    
    EXPECT_EQ(v.size, 3);
    
    VECTOR_TYPE result;
    EXPECT_EQ(get_at_vector(&v, 0, &result), 0);
    EXPECT_STREQ(result, "Hello");
    EXPECT_EQ(get_at_vector(&v, 1, &result), 0);
    EXPECT_STREQ(result, "World");
    EXPECT_EQ(get_at_vector(&v, 2, &result), 0);
    EXPECT_STREQ(result, "Test");
    
    erase_vector(&v);
}


TEST_F(VectorHardTest, DeepCopy_IndependentStrings) {
    Vector v = create_vector(5, is_equal_hard, CopyVoidPtr_hard, DeleteVoidPtr_hard);
    
    char original[] = "Original";
    push_back_vector(&v, original);
    
    original[0] = 'X';
    
    VECTOR_TYPE result;
    EXPECT_EQ(get_at_vector(&v, 0, &result), 0);
    EXPECT_STREQ(result, "Original");
    
    erase_vector(&v);
}


TEST_F(VectorHardTest, DeleteAt_String) {
    Vector v = create_vector(5, is_equal_hard, CopyVoidPtr_hard, DeleteVoidPtr_hard);
    
    push_back_vector(&v, (char*)"First");
    push_back_vector(&v, (char*)"Second");
    push_back_vector(&v, (char*)"Third");
    
    delete_at_vector(&v, 1);
    
    EXPECT_EQ(v.size, 2);
    
    VECTOR_TYPE result;
    EXPECT_EQ(get_at_vector(&v, 0, &result), 0);
    EXPECT_STREQ(result, "First");
    EXPECT_EQ(get_at_vector(&v, 1, &result), 0);
    EXPECT_STREQ(result, "Third");
    
    erase_vector(&v);
}


TEST_F(VectorHardTest, IsEqualVector_EqualStrings) {
    Vector v1 = create_vector(5, is_equal_hard, CopyVoidPtr_hard, DeleteVoidPtr_hard);
    Vector v2 = create_vector(5, is_equal_hard, CopyVoidPtr_hard, DeleteVoidPtr_hard);
    
    push_back_vector(&v1, (char*)"Hello");
    push_back_vector(&v1, (char*)"World");
    
    push_back_vector(&v2, (char*)"Hello");
    push_back_vector(&v2, (char*)"World");
    
    EXPECT_EQ(is_equal_vector(&v1, &v2), 1);
    
    erase_vector(&v1);
    erase_vector(&v2);
}


TEST_F(VectorHardTest, IsEqualVector_DifferentStrings) {
    Vector v1 = create_vector(5, is_equal_hard, CopyVoidPtr_hard, DeleteVoidPtr_hard);
    Vector v2 = create_vector(5, is_equal_hard, CopyVoidPtr_hard, DeleteVoidPtr_hard);
    
    push_back_vector(&v1, (char*)"Hello");
    push_back_vector(&v2, (char*)"World");
    
    EXPECT_EQ(is_equal_vector(&v1, &v2), 0);
    
    erase_vector(&v1);
    erase_vector(&v2);
}


TEST_F(VectorHardTest, CopyVector_Strings) {
    Vector src = create_vector(5, is_equal_hard, CopyVoidPtr_hard, DeleteVoidPtr_hard);
    Vector dest = create_vector(3, is_equal_hard, CopyVoidPtr_hard, DeleteVoidPtr_hard);
    
    push_back_vector(&src, (char*)"Apple");
    push_back_vector(&src, (char*)"Banana");
    push_back_vector(&src, (char*)"Cherry");
    
    copy_vector(&dest, &src);
    
    EXPECT_EQ(dest.size, 3);
    
    VECTOR_TYPE result;
    EXPECT_EQ(get_at_vector(&dest, 0, &result), 0);
    EXPECT_STREQ(result, "Apple");
    EXPECT_EQ(get_at_vector(&dest, 1, &result), 0);
    EXPECT_STREQ(result, "Banana");
    EXPECT_EQ(get_at_vector(&dest, 2, &result), 0);
    EXPECT_STREQ(result, "Cherry");
    
    erase_vector(&src);
    erase_vector(&dest);
}


TEST_F(VectorHardTest, CopyVectorNew_Strings) {
    Vector src = create_vector(5, is_equal_hard, CopyVoidPtr_hard, DeleteVoidPtr_hard);
    
    push_back_vector(&src, (char*)"One");
    push_back_vector(&src, (char*)"Two");
    
    Vector *dest = copy_vector_new(&src);
    
    ASSERT_NE(dest, nullptr);
    EXPECT_EQ(dest->size, 2);
    
    VECTOR_TYPE result;
    EXPECT_EQ(get_at_vector(dest, 0, &result), 0);
    EXPECT_STREQ(result, "One");
    EXPECT_EQ(get_at_vector(dest, 1, &result), 0);
    EXPECT_STREQ(result, "Two");
    
    erase_vector(&src);
    delete_vector(dest);
}


TEST_F(VectorHardTest, EmptyString) {
    Vector v = create_vector(5, is_equal_hard, CopyVoidPtr_hard, DeleteVoidPtr_hard);
    
    push_back_vector(&v, (char*)"");
    
    EXPECT_EQ(v.size, 1);
    
    VECTOR_TYPE result;
    EXPECT_EQ(get_at_vector(&v, 0, &result), 0);
    EXPECT_STREQ(result, "");
    
    erase_vector(&v);
}


TEST_F(VectorHardTest, LongString) {
    Vector v = create_vector(5, is_equal_hard, CopyVoidPtr_hard, DeleteVoidPtr_hard);
    
    char long_str[1000];
    for (int i = 0; i < 999; i++) {
        long_str[i] = 'a' + (i % 26);
    }
    long_str[999] = '\0';
    
    push_back_vector(&v, long_str);
    
    VECTOR_TYPE result;
    EXPECT_EQ(get_at_vector(&v, 0, &result), 0);
    EXPECT_STREQ(result, long_str);
    
    erase_vector(&v);
}


#endif // VECTOR_TYPE_HARD


// ============= ГРАНИЧНЫЕ СЛУЧАИ =============


TEST(VectorEdgeCases, GetAt_InvalidIndex) {
    Vector v = create_vector(5, is_equal_simple, CopyVoidPtr_simple, DeleteVoidPtr_simple);
    push_back_vector(&v, 10);
    
    VECTOR_TYPE result;
    EXPECT_NE(get_at_vector(&v, 10, &result), 0);
    
    erase_vector(&v);
}


TEST(VectorEdgeCases, GetAt_NullVector) {
    VECTOR_TYPE result;
    EXPECT_NE(get_at_vector(nullptr, 0, &result), 0);
}


TEST(VectorEdgeCases, GetAt_NullResult) {
    Vector v = create_vector(5, is_equal_simple, CopyVoidPtr_simple, DeleteVoidPtr_simple);
    push_back_vector(&v, 10);
    
    EXPECT_NE(get_at_vector(&v, 0, nullptr), 0);
    
    erase_vector(&v);
}


TEST(VectorEdgeCases, IsEqualVector_NullPointers) {
    Vector v = create_vector(5, is_equal_simple, CopyVoidPtr_simple, DeleteVoidPtr_simple);
    
    EXPECT_EQ(is_equal_vector(nullptr, &v), 0);
    EXPECT_EQ(is_equal_vector(&v, nullptr), 0);
    EXPECT_EQ(is_equal_vector(nullptr, nullptr), 0);
    
    erase_vector(&v);
}


TEST(VectorEdgeCases, CopyVectorNew_NullSource) {
    Vector *result = copy_vector_new(nullptr);
    EXPECT_EQ(result, nullptr);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
