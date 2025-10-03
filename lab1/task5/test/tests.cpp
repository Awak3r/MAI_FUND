#include <gtest/gtest.h>
#include <fstream>
#include <string>


class FileProcessingTest : public ::testing::Test {
protected:
    std::string input_file;
    std::string output_file;
    
    void SetUp() override {
        input_file = "test_input.txt";
        output_file = "test_output.txt";
    }
    
    void TearDown() override {
        remove(input_file.c_str());
        remove(output_file.c_str());
        remove(("out_" + input_file).c_str());
    }
    
    void CreateInputFile(const std::string& content) {
        std::ofstream file(input_file);
        file << content;
        file.close();
    }
    
    std::string ReadOutputFile(const std::string& filename) {
        std::ifstream file(filename);
        std::string content((std::istreambuf_iterator<char>(file)),
                           std::istreambuf_iterator<char>());
        file.close();
        return content;
    }
    
    int RunProgram(const std::string& flag) {
        std::string cmd = "./lab1_task5_exe " + flag + " " + input_file;
        return system(cmd.c_str());
    }
    
    int RunProgramWithOutput(const std::string& flag, const std::string& out) {
        std::string cmd = "./lab1_task5_exe " + flag + " " + input_file + " " + out;
        return system(cmd.c_str());
    }
};

TEST_F(FileProcessingTest, FlagD_MixedContent) {
    CreateInputFile("abc123def456");
    RunProgram("-d");
    
    std::string result = ReadOutputFile("out_" + input_file);
    EXPECT_EQ(result, "abcdef");
}

TEST_F(FileProcessingTest, FlagD_NoDigits) {
    CreateInputFile("abcdefghijk");
    RunProgram("-d");
    
    std::string result = ReadOutputFile("out_" + input_file);
    EXPECT_EQ(result, "abcdefghijk");
}

TEST_F(FileProcessingTest, FlagD_OnlyDigits) {
    CreateInputFile("0123456789");
    RunProgram("-d");
    
    std::string result = ReadOutputFile("out_" + input_file);
    EXPECT_EQ(result, "");
}

TEST_F(FileProcessingTest, FlagI_SingleLine) {
    CreateInputFile("Hello World");
    RunProgram("-i");
    
    std::string result = ReadOutputFile("out_" + input_file);
    EXPECT_EQ(result, "10\n");
}

TEST_F(FileProcessingTest, FlagI_MultipleLines) {
    CreateInputFile("abc\ndefgh\nij");
    RunProgram("-i");
    
    std::string result = ReadOutputFile("out_" + input_file);
    EXPECT_EQ(result, "3\n5\n2\n");
}

TEST_F(FileProcessingTest, FlagI_MixedContent) {
    CreateInputFile("Test123");
    RunProgram("-i");
    
    std::string result = ReadOutputFile("out_" + input_file);
    EXPECT_EQ(result, "4\n");
}

TEST_F(FileProcessingTest, FlagS_NoSpecialChars) {
    CreateInputFile("Hello World 123");
    RunProgram("-s");
    
    std::string result = ReadOutputFile("out_" + input_file);
    EXPECT_EQ(result, "0\n");
}

TEST_F(FileProcessingTest, FlagS_WithSpecialChars) {
    CreateInputFile("Hello! World?");
    RunProgram("-s");
    
    std::string result = ReadOutputFile("out_" + input_file);
    EXPECT_EQ(result, "2\n");
}

TEST_F(FileProcessingTest, FlagS_OnlySpecialChars) {
    CreateInputFile("!@#$%");
    RunProgram("-s");
    
    std::string result = ReadOutputFile("out_" + input_file);
    EXPECT_EQ(result, "5\n");
}

TEST_F(FileProcessingTest, FlagA_OnlyDigits) {
    CreateInputFile("123");
    RunProgram("-a");
    
    std::string result = ReadOutputFile("out_" + input_file);
    EXPECT_EQ(result, "123");
}

TEST_F(FileProcessingTest, FlagA_OnlyLetters) {
    CreateInputFile("abc");
    RunProgram("-a");
    
    std::string result = ReadOutputFile("out_" + input_file);
    EXPECT_EQ(result, "616263");
}

TEST_F(FileProcessingTest, FlagA_MixedContent) {
    CreateInputFile("a1b2");
    RunProgram("-a");
    
    std::string result = ReadOutputFile("out_" + input_file);
    EXPECT_EQ(result, "611622");
}

TEST_F(FileProcessingTest, FlagN_CustomOutput) {
    CreateInputFile("123abc456");
    RunProgramWithOutput("-nd", output_file);
    
    std::string result = ReadOutputFile(output_file);
    EXPECT_EQ(result, "abc");
}

TEST_F(FileProcessingTest, EmptyFile) {
    CreateInputFile("");
    RunProgram("-d");
    
    std::string result = ReadOutputFile("out_" + input_file);
    EXPECT_EQ(result, "");
}

TEST_F(FileProcessingTest, AllFlagsSequence) {
    CreateInputFile("Test123!");
    
    RunProgram("-d");
    EXPECT_EQ(ReadOutputFile("out_" + input_file), "Test!");
    
    RunProgram("-i");
    EXPECT_EQ(ReadOutputFile("out_" + input_file), "4\n");
    
    RunProgram("-s");
    EXPECT_EQ(ReadOutputFile("out_" + input_file), "1\n");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}