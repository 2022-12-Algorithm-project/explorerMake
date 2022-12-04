#include <iostream>
#include <string>
#include <utility>
#include <windows.h>
#define MaxDirCount 20
#define MaxFileCount 20

typedef struct File{
    std::string name;
}File;

typedef struct Directory{
    std::string name;
    struct Directory* SubDir[MaxDirCount]{};
    struct File* SubFile[MaxFileCount]{};
}Directory;

Directory* RootDir(std::string Username){
    auto* root = new Directory;
    root->name = std::move(Username);

    return root;
}

void macro(Directory* Root) {
    std::cout << "$" << Root->name << "\t\t";
}

int main() {
    std::string Username;
    std::cout << "유저 이름을 입력해주세요\t : ";
    std::cin >> Username;
    Directory* root = RootDir(Username);
    std::cout << root->name << std::endl;
    std::string command = "";
    while(command != "exit") {
        macro(root);
        std::cin >> command;

    }

    return 0;
}
