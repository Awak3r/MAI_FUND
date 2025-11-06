#include <gtest/gtest.h>
#include <cstdio>
#include <string.h>
#include <iostream>
extern "C" {
#include "../include/func.h"
}

class StudentTest : public ::testing::Test {
protected:
    Student* students;
    int len;
    FILE* testFile;
    
    void SetUp() override {
        students = nullptr;
        len = 0;
        testFile = tmpfile();
    }
    
    void TearDown() override {
        if (students) {
            for (int i = 0; i < len; i++) {
                free(students[i].surname);
                free(students[i].name);
                free(students[i].group);
                free(students[i].marks);
            }
            free(students);
        }
        if (testFile) {
            fclose(testFile);
        }
    }
    
    void writeToFile(const char* data) {
        fprintf(testFile, "%s", data);
        rewind(testFile);
    }
    
    Student createStudent(unsigned int id, const char* surname, const char* name, 
                         const char* group, unsigned char m1, unsigned char m2, 
                         unsigned char m3, unsigned char m4, unsigned char m5) {
        Student s;
        s.id = id;
        s.surname = strdup(surname);
        s.name = strdup(name);
        s.group = strdup(group);
        s.marks = (unsigned char*)malloc(5 * sizeof(unsigned char));
        s.marks[0] = m1; s.marks[1] = m2; s.marks[2] = m3; 
        s.marks[3] = m4; s.marks[4] = m5;
        return s;
    }
    
    void freeStudent(Student* s) {
        if (s) {
            free(s->surname);
            free(s->name);
            free(s->group);
            free(s->marks);
        }
    }
};


TEST_F(StudentTest, ValidateStruct_ValidStudent) {
    Student s = createStudent(1, "Ivanov", "Ivan", "CS101", 5, 4, 5, 5, 4);
    int result = validate_struct(s);
    std::cout << "Test ValidateStruct_ValidStudent: id=" << s.id << ", surname=\"" << s.surname 
              << "\", name=\"" << s.name << "\", group=\"" << s.group 
              << "\", marks=[5,4,5,5,4], got result=" << result << ", expected=1\n";
    EXPECT_EQ(result, 1) << "Valid student should pass validation";
    freeStudent(&s);
}

TEST_F(StudentTest, ValidateStruct_NullSurname) {
    Student s;
    s.id = 1;
    s.surname = nullptr;
    s.name = strdup("Ivan");
    s.group = strdup("CS101");
    s.marks = (unsigned char*)malloc(5);
    int result = validate_struct(s);
    std::cout << "Test ValidateStruct_NullSurname: surname=nullptr, got result=" << result << ", expected=-1\n";
    EXPECT_EQ(result, -1) << "Null surname should fail validation";
    free(s.name);
    free(s.group);
    free(s.marks);
}

TEST_F(StudentTest, ValidateStruct_EmptySurname) {
    Student s = createStudent(1, "", "Ivan", "CS101", 5, 4, 5, 5, 4);
    int result = validate_struct(s);
    std::cout << "Test ValidateStruct_EmptySurname: surname=\"\", got result=" << result << ", expected=-1\n";
    EXPECT_EQ(result, -1) << "Empty surname should fail validation";
    freeStudent(&s);
}

TEST_F(StudentTest, ValidateStruct_SurnameWithDigits) {
    Student s = createStudent(1, "Ivanov123", "Ivan", "CS101", 5, 4, 5, 5, 4);
    int result = validate_struct(s);
    std::cout << "Test ValidateStruct_SurnameWithDigits: surname=\"Ivanov123\", got result=" << result << ", expected=-1\n";
    EXPECT_EQ(result, -1) << "Surname with digits should fail validation";
    freeStudent(&s);
}

TEST_F(StudentTest, ValidateStruct_InvalidMark) {
    Student s = createStudent(1, "Ivanov", "Ivan", "CS101", 5, 6, 5, 5, 4);
    int result = validate_struct(s);
    std::cout << "Test ValidateStruct_InvalidMark: marks=[5,6,5,5,4], got result=" << result << ", expected=-1\n";
    EXPECT_EQ(result, -1) << "Mark > 5 should fail validation";
    freeStudent(&s);
}

TEST_F(StudentTest, ValidateStruct_InvalidMarkLow) {
    Student s = createStudent(1, "Ivanov", "Ivan", "CS101", 5, 1, 5, 5, 4);
    int result = validate_struct(s);
    std::cout << "Test ValidateStruct_InvalidMarkLow: marks=[5,1,5,5,4], got result=" << result << ", expected=-1\n";
    EXPECT_EQ(result, -1) << "Mark < 2 should fail validation";
    freeStudent(&s);
}

TEST_F(StudentTest, ValidateStruct_ZeroId) {
    Student s = createStudent(0, "Ivanov", "Ivan", "CS101", 5, 4, 5, 5, 4);
    int result = validate_struct(s);
    std::cout << "Test ValidateStruct_ZeroId: id=0, got result=" << result << ", expected=-1\n";
    EXPECT_EQ(result, -1) << "Zero ID should fail validation";
    freeStudent(&s);
}

TEST_F(StudentTest, ValidateStruct_GroupWithNumbers) {
    Student s = createStudent(1, "Ivanov", "Ivan", "CS101", 5, 4, 5, 5, 4);
    int result = validate_struct(s);
    std::cout << "Test ValidateStruct_GroupWithNumbers: group=\"CS101\", got result=" << result << ", expected=1\n";
    EXPECT_EQ(result, 1) << "Group with letters and numbers should pass validation";
    freeStudent(&s);
}


TEST_F(StudentTest, ReadFromFile_ValidData) {
    writeToFile("1 Ivanov Ivan CS101 5 4 5 5 4\n2 Petrov Petr CS102 3 3 4 4 3\n");
    int result = read_from_file(testFile, &students, &len);
    std::cout << "Test ReadFromFile_ValidData: file has 2 students, got result=" << result 
              << ", len=" << len << ", expected result=1, len=2\n";
    EXPECT_EQ(result, 1) << "Should successfully read valid data";
    EXPECT_EQ(len, 2) << "Should read 2 students";
    if (len >= 1) {
        std::cout << "  Student[0]: id=" << students[0].id << ", surname=\"" << students[0].surname << "\"\n";
        EXPECT_EQ(students[0].id, 1u);
        EXPECT_STREQ(students[0].surname, "Ivanov");
    }
}

TEST_F(StudentTest, ReadFromFile_EmptyFile) {
    writeToFile("");
    int result = read_from_file(testFile, &students, &len);
    std::cout << "Test ReadFromFile_EmptyFile: file is empty, got result=" << result 
              << ", len=" << len << ", expected result=1, len=0\n";
    EXPECT_EQ(result, 1) << "Empty file should return success";
    EXPECT_EQ(len, 0) << "Should read 0 students";
}

TEST_F(StudentTest, ReadFromFile_ManyStudents) {
    std::string data;
    for (int i = 1; i <= 15; i++) {
        data += std::to_string(i) + " Student" + std::to_string(i) + " Name" + std::to_string(i) 
                + " G1 5 4 5 5 4\n";
    }
    writeToFile(data.c_str());
    int result = read_from_file(testFile, &students, &len);
    std::cout << "Test ReadFromFile_ManyStudents: file has 15 students, got result=" << result 
              << ", len=" << len << ", expected result=1, len=15\n";
    EXPECT_EQ(result, 1) << "Should handle multiple students";
    EXPECT_EQ(len, 15) << "Should read 15 students";
}


TEST_F(StudentTest, SortById_Ascending) {
    Student arr[3];
    arr[0] = createStudent(3, "Cvanov", "C", "G1", 5, 4, 5, 5, 4);
    arr[1] = createStudent(1, "Avanov", "A", "G1", 5, 4, 5, 5, 4);
    arr[2] = createStudent(2, "Bvanov", "B", "G1", 5, 4, 5, 5, 4);
    
    std::cout << "Test SortById_Ascending: before sort ids=[3,1,2], ";
    qsort(arr, 3, sizeof(Student), sort_i);
    std::cout << "after sort ids=[" << arr[0].id << "," << arr[1].id << "," << arr[2].id 
              << "], expected=[1,2,3]\n";
    
    EXPECT_EQ(arr[0].id, 1u) << "First should be id=1";
    EXPECT_EQ(arr[1].id, 2u) << "Second should be id=2";
    EXPECT_EQ(arr[2].id, 3u) << "Third should be id=3";
    
    for (int i = 0; i < 3; i++) freeStudent(&arr[i]);
}

TEST_F(StudentTest, SortBySurname_Alphabetical) {
    Student arr[3];
    arr[0] = createStudent(1, "Cvanov", "C", "G1", 5, 4, 5, 5, 4);
    arr[1] = createStudent(2, "Avanov", "A", "G1", 5, 4, 5, 5, 4);
    arr[2] = createStudent(3, "Bvanov", "B", "G1", 5, 4, 5, 5, 4);
    
    std::cout << "Test SortBySurname_Alphabetical: before sort surnames=[Cvanov,Avanov,Bvanov], ";
    qsort(arr, 3, sizeof(Student), sort_s);
    std::cout << "after sort surnames=[" << arr[0].surname << "," << arr[1].surname << "," 
              << arr[2].surname << "], expected=[Avanov,Bvanov,Cvanov]\n";
    
    EXPECT_STREQ(arr[0].surname, "Avanov") << "First should be Avanov";
    EXPECT_STREQ(arr[1].surname, "Bvanov") << "Second should be Bvanov";
    EXPECT_STREQ(arr[2].surname, "Cvanov") << "Third should be Cvanov";
    
    for (int i = 0; i < 3; i++) freeStudent(&arr[i]);
}

TEST_F(StudentTest, SortByName_Alphabetical) {
    Student arr[3];
    arr[0] = createStudent(1, "Same", "Charlie", "G1", 5, 4, 5, 5, 4);
    arr[1] = createStudent(2, "Same", "Alice", "G1", 5, 4, 5, 5, 4);
    arr[2] = createStudent(3, "Same", "Bob", "G1", 5, 4, 5, 5, 4);
    
    std::cout << "Test SortByName_Alphabetical: before sort names=[Charlie,Alice,Bob], ";
    qsort(arr, 3, sizeof(Student), sort_n);
    std::cout << "after sort names=[" << arr[0].name << "," << arr[1].name << "," 
              << arr[2].name << "], expected=[Alice,Bob,Charlie]\n";
    
    EXPECT_STREQ(arr[0].name, "Alice") << "First should be Alice";
    EXPECT_STREQ(arr[1].name, "Bob") << "Second should be Bob";
    EXPECT_STREQ(arr[2].name, "Charlie") << "Third should be Charlie";
    
    for (int i = 0; i < 3; i++) freeStudent(&arr[i]);
}

TEST_F(StudentTest, SortByGroup_Alphabetical) {
    Student arr[3];
    arr[0] = createStudent(1, "Same", "Same", "CS103", 5, 4, 5, 5, 4);
    arr[1] = createStudent(2, "Same", "Same", "CS101", 5, 4, 5, 5, 4);
    arr[2] = createStudent(3, "Same", "Same", "CS102", 5, 4, 5, 5, 4);
    
    std::cout << "Test SortByGroup_Alphabetical: before sort groups=[CS103,CS101,CS102], ";
    qsort(arr, 3, sizeof(Student), sort_g);
    std::cout << "after sort groups=[" << arr[0].group << "," << arr[1].group << "," 
              << arr[2].group << "], expected=[CS101,CS102,CS103]\n";
    
    EXPECT_STREQ(arr[0].group, "CS101") << "First should be CS101";
    EXPECT_STREQ(arr[1].group, "CS102") << "Second should be CS102";
    EXPECT_STREQ(arr[2].group, "CS103") << "Third should be CS103";
    
    for (int i = 0; i < 3; i++) freeStudent(&arr[i]);
}


TEST_F(StudentTest, FindById_Found) {
    Student arr[3];
    arr[0] = createStudent(1, "Ivanov", "Ivan", "G1", 5, 4, 5, 5, 4);
    arr[1] = createStudent(2, "Petrov", "Petr", "G1", 5, 4, 5, 5, 4);
    arr[2] = createStudent(3, "Sidorov", "Sidr", "G1", 5, 4, 5, 5, 4);
    
    std::cout << "Test FindById_Found: searching id=2 in array of 3, ";
    Student* found = find_by_i(arr, 3, 2);
    std::cout << "got " << (found ? "found" : "not found");
    if (found) std::cout << ", found->surname=\"" << found->surname << "\"";
    std::cout << ", expected found with surname=\"Petrov\"\n";
    
    ASSERT_NE(found, nullptr) << "Should find student with id=2";
    EXPECT_EQ(found->id, 2u) << "Found student should have id=2";
    EXPECT_STREQ(found->surname, "Petrov") << "Found student should be Petrov";
    
    for (int i = 0; i < 3; i++) freeStudent(&arr[i]);
}

TEST_F(StudentTest, FindById_NotFound) {
    Student arr[2];
    arr[0] = createStudent(1, "Ivanov", "Ivan", "G1", 5, 4, 5, 5, 4);
    arr[1] = createStudent(2, "Petrov", "Petr", "G1", 5, 4, 5, 5, 4);
    
    std::cout << "Test FindById_NotFound: searching id=99 in array of 2, ";
    Student* found = find_by_i(arr, 2, 99);
    std::cout << "got " << (found ? "found" : "not found") << ", expected not found\n";
    
    EXPECT_EQ(found, nullptr) << "Should not find student with id=99";
    
    for (int i = 0; i < 2; i++) freeStudent(&arr[i]);
}

TEST_F(StudentTest, FindBySurname_MultipleFound) {
    Student arr[4];
    arr[0] = createStudent(1, "Ivanov", "Ivan", "G1", 5, 4, 5, 5, 4);
    arr[1] = createStudent(2, "Petrov", "Petr", "G1", 5, 4, 5, 5, 4);
    arr[2] = createStudent(3, "Ivanov", "Petr", "G2", 3, 3, 3, 3, 3);
    arr[3] = createStudent(4, "Sidorov", "Sidr", "G1", 4, 4, 4, 4, 4);
    
    int find_len = 0;
    std::cout << "Test FindBySurname_MultipleFound: searching surname=\"Ivanov\" in array of 4, ";
    Student** found = find_by_s(arr, 4, &find_len, (char*)"Ivanov");
    std::cout << "got find_len=" << find_len << ", expected=2\n";
    
    ASSERT_NE(found, nullptr) << "Should find students";
    EXPECT_EQ(find_len, 2) << "Should find 2 students with surname Ivanov";
    if (find_len >= 2) {
        std::cout << "  Found[0]: id=" << found[0]->id << ", name=\"" << found[0]->name << "\"\n";
        std::cout << "  Found[1]: id=" << found[1]->id << ", name=\"" << found[1]->name << "\"\n";
    }
    
    free(found);
    for (int i = 0; i < 4; i++) freeStudent(&arr[i]);
}

TEST_F(StudentTest, FindBySurname_NoneFound) {
    Student arr[2];
    arr[0] = createStudent(1, "Ivanov", "Ivan", "G1", 5, 4, 5, 5, 4);
    arr[1] = createStudent(2, "Petrov", "Petr", "G1", 5, 4, 5, 5, 4);
    
    int find_len = 0;
    std::cout << "Test FindBySurname_NoneFound: searching surname=\"Nonexistent\" in array of 2, ";
    Student** found = find_by_s(arr, 2, &find_len, (char*)"Nonexistent");
    std::cout << "got find_len=" << find_len << ", found=" << (found ? "not null" : "null") 
              << ", expected find_len=0, found=null\n";
    
    EXPECT_EQ(found, nullptr) << "Should not find any students";
    EXPECT_EQ(find_len, 0) << "Find length should be 0";
    
    for (int i = 0; i < 2; i++) freeStudent(&arr[i]);
}

TEST_F(StudentTest, FindByName_Found) {
    Student arr[3];
    arr[0] = createStudent(1, "Ivanov", "Ivan", "G1", 5, 4, 5, 5, 4);
    arr[1] = createStudent(2, "Petrov", "Ivan", "G1", 5, 4, 5, 5, 4);
    arr[2] = createStudent(3, "Sidorov", "Petr", "G1", 5, 4, 5, 5, 4);
    
    int find_len = 0;
    std::cout << "Test FindByName_Found: searching name=\"Ivan\" in array of 3, ";
    Student** found = find_by_n(arr, 3, &find_len, (char*)"Ivan");
    std::cout << "got find_len=" << find_len << ", expected=2\n";
    
    ASSERT_NE(found, nullptr) << "Should find students";
    EXPECT_EQ(find_len, 2) << "Should find 2 students named Ivan";
    
    free(found);
    for (int i = 0; i < 3; i++) freeStudent(&arr[i]);
}

TEST_F(StudentTest, FindByGroup_Found) {
    Student arr[4];
    arr[0] = createStudent(1, "Ivanov", "Ivan", "CS101", 5, 4, 5, 5, 4);
    arr[1] = createStudent(2, "Petrov", "Petr", "CS102", 5, 4, 5, 5, 4);
    arr[2] = createStudent(3, "Sidorov", "Sidr", "CS101", 3, 3, 3, 3, 3);
    arr[3] = createStudent(4, "Fedorov", "Fedor", "CS103", 4, 4, 4, 4, 4);
    
    int find_len = 0;
    std::cout << "Test FindByGroup_Found: searching group=\"CS101\" in array of 4, ";
    Student** found = find_by_g(arr, 4, &find_len, (char*)"CS101");
    std::cout << "got find_len=" << find_len << ", expected=2\n";
    
    ASSERT_NE(found, nullptr) << "Should find students";
    EXPECT_EQ(find_len, 2) << "Should find 2 students in group CS101";
    
    free(found);
    for (int i = 0; i < 4; i++) freeStudent(&arr[i]);
}


TEST_F(StudentTest, FindSr_CalculatesAverage) {
    Student arr[3];
    arr[0] = createStudent(1, "Ivanov", "Ivan", "G1", 5, 5, 5, 5, 5);  
    arr[1] = createStudent(2, "Petrov", "Petr", "G1", 3, 3, 3, 3, 3);  
    arr[2] = createStudent(3, "Sidorov", "Sidr", "G1", 4, 4, 4, 4, 4);
    
    std::cout << "Test FindSr_CalculatesAverage: students with avg marks [5.0, 3.0, 4.0], ";
    double sr = find_sr(arr, 3);
    std::cout << "got sr=" << sr << ", expected=4.0\n";
    
    EXPECT_DOUBLE_EQ(sr, 4.0) << "Average should be 4.0";
    
    for (int i = 0; i < 3; i++) freeStudent(&arr[i]);
}

TEST_F(StudentTest, FindSr_SingleStudent) {
    Student arr[1];
    arr[0] = createStudent(1, "Ivanov", "Ivan", "G1", 4, 4, 4, 4, 4);
    
    std::cout << "Test FindSr_SingleStudent: single student with marks [4,4,4,4,4], ";
    double sr = find_sr(arr, 1);
    std::cout << "got sr=" << sr << ", expected=4.0\n";
    
    EXPECT_DOUBLE_EQ(sr, 4.0) << "Average for one student should be 4.0";
    
    freeStudent(&arr[0]);
}


TEST_F(StudentTest, WriteToFileAfterSort_Success) {
    Student* arr[2];
    Student s1 = createStudent(1, "Ivanov", "Ivan", "CS101", 5, 4, 5, 5, 5);
    Student s2 = createStudent(2, "Petrov", "Petr", "CS102", 3, 3, 3, 3, 3);
    arr[0] = &s1;
    arr[1] = &s2;
    
    FILE* outFile = tmpfile();
    std::cout << "Test WriteToFileAfterSort_Success: writing 2 students to file, ";
    int result = write_to_file_after_sort(outFile, arr, 2);
    std::cout << "got result=" << result << ", expected=1\n";
    
    EXPECT_EQ(result, 1) << "Should successfully write to file";
    
    rewind(outFile);
    char buf[256];
    fgets(buf, sizeof(buf), outFile);
    std::cout << "  First line: " << buf;
    EXPECT_NE(strstr(buf, "Ivanov"), nullptr) << "Should contain Ivanov";
    EXPECT_NE(strstr(buf, "4.8"), nullptr) << "Should contain average 4.8";
    
    fclose(outFile);
    freeStudent(&s1);
    freeStudent(&s2);
}


TEST_F(StudentTest, WriteToFileAboveSr_Success) {
    Student arr[3];
    arr[0] = createStudent(1, "Excellent", "Student", "G1", 5, 5, 5, 5, 5);  // avg = 5.0
    arr[1] = createStudent(2, "Good", "Student", "G1", 4, 4, 4, 4, 4);       // avg = 4.0
    arr[2] = createStudent(3, "Average", "Student", "G1", 3, 3, 3, 3, 3);    // avg = 3.0
    
    FILE* outFile = tmpfile();
    std::cout << "Test WriteToFileAboveSr_Success: writing students with avg>4.0, ";
    int result = write_to_file_above_sr(outFile, arr, 3, 4.0);
    std::cout << "got result=" << result << ", expected=1\n";
    
    EXPECT_EQ(result, 1) << "Should successfully write";
    
    rewind(outFile);
    char buf[256];
    fgets(buf, sizeof(buf), outFile);
    std::cout << "  Output line: " << buf;
    EXPECT_NE(strstr(buf, "Excellent"), nullptr) << "Should contain Excellent student";
    
    fclose(outFile);
    for (int i = 0; i < 3; i++) freeStudent(&arr[i]);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
