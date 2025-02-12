/********************/文件系统/************************************************************/
#include <filesystem>


//实例
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
    // 1. 创建目录
    fs::create_directory("test_dir");

    // 2. 创建文件路径
    fs::path file_path = "test_dir/example.txt";

    // 3. 创建文件并写入内容
    std::ofstream file(file_path);
    file << "Hello, Filesystem!";
    file.close();

    // 4. 检查文件是否存在
    if (fs::exists(file_path)) {
        std::cout << "File exists!" << std::endl;
    }

    // 5. 获取文件大小
    std::cout << "File size: " << fs::file_size(file_path) << " bytes" << std::endl;

    // 6. 遍历目录
    for (const auto& entry : fs::directory_iterator("test_dir")) {
        std::cout << entry.path() << std::endl;
    }

    // 7. 删除文件
    fs::remove(file_path);

    // 8. 删除目录
    fs::remove("test_dir");

    return 0;
}



