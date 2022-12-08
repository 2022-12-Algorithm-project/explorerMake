#include <iostream>
#include <string>
#include <utility>
#include <Windows.h>
#include <iomanip>

#define MaxDirCount 20
#define MaxFileCount 20

typedef struct File {
    std::string name;
} File;

typedef struct Directory {
    std::string name;
    int Dcount{};
    int Fcount{};
    struct Directory *LastDir{};
    struct Directory *SubDir[MaxDirCount]{};
    struct File *SubFile[MaxFileCount]{};
} Directory;

Directory *RootDir(std::string Username) {
    auto *root = new Directory;
    root->name = std::move(Username);
    root->Dcount = 0;
    root->Fcount = 0;
    root->LastDir = NULL;
    return root;
}

int search(Directory *root, std::string target) {
    Directory *temp = root;
        for (int i = 0; i < temp->Dcount; i++) {
            if (temp->SubDir[i]->name == target)
                return i;
        }
        return -1;

}

void macro(Directory *Root, std::string username) {
    system("color 02");
    std::cout << username;
    system("color");
    if (Root->name == username) {

        std::cout << ":~$ >> ";
    } else {

        std::cout << ":" << Root->name << " $ >> ";
    }

}

Directory *ChangeDir(std::string CL, Directory *root) {
    try {
        Directory *temp = root;
        if (CL == "..") {
            if (!(temp->LastDir)) {
                std::cout << "처음 디렉토리 입니다" << std::endl;
                return temp;
            } else {
                temp = temp->LastDir;
                return temp;
            }
        }
        int index = search(temp, std::move(CL));
        if (index > -1) {
            temp = temp->SubDir[index];
            return temp;
        } else {
            std::cout << "없는 디렉토리 입니다" << std::endl;
            return temp;
        }
    } catch (std::exception e) {
        std::cout << "에러가 발생했습니다 명령어를 점검해주십시오" << std::endl;
    }
}


void MakeDir(Directory *root, std::string ND) {
    Directory *temp = root;
    int i = 0;
    try {
        while (i < temp->Dcount) {
            if (temp->SubDir[i]->name == ND)
                throw ND;
            i++;
        }
        Directory *NewDir = RootDir(ND);
        NewDir->LastDir = temp;
        temp->SubDir[i] = NewDir;
        temp->Dcount++;
    } catch (std::string e) {
        std::cout << e << "는 이미 있는 폴더명 입니다" << std::endl;
    }
}

void MakeFile(Directory *root, std::string NF) {
    Directory *temp = root;
    int i = 0;
    try {
        while (i < temp->Dcount) {
            if (temp->SubFile[i]->name == NF)
                throw NF;
            i++;
        }
        File *NewFile = new File;
        NewFile->name = NF;
        temp->SubFile[i] = NewFile;
        temp->Fcount++;
    } catch (std::string e) {
        std::cout << e << "는 이미 있는 파일명 입니다" << std::endl;
    }
}

void List(Directory *root) {
    Directory *temp = root;
    for (int i = 0; i < temp->Dcount; i++) {
        std::cout << temp->SubDir[i]->name << "/ ";
    }
    for (int j = 0; j < temp->Fcount; j++) {
        std::cout << temp->SubFile[j]->name << " ";
    }
    std::cout << std::endl;
}


int main() {

    std::cout << "유저 이름을 입력해주세요 : ";
    std::string Username;
    std::cin >> Username;
    system("cls");
    Directory *root = RootDir(Username);
    Directory *NL = root;
    std::string cmd;
    std::cin.ignore();
    while (cmd != "exit") {
        try {
            macro(NL, Username);
            getline(std::cin, cmd, '\n');
            //Command(cmd,NL);
            if (cmd.rfind("cd", 0) == 0) {
                std::string temp = cmd.substr(3);
                NL = ChangeDir(temp, NL);
            } else if (cmd.rfind("mkdir", 0) == 0) {
                std::string temp = cmd.substr(6);
                MakeDir(NL, temp);
            } else if (cmd.rfind("touch", 0) == 0) {
                std::string temp = cmd.substr(6);
                MakeFile(NL, temp);
            } else if (cmd.rfind("ls", 0) == 0) {
                List(NL);
            } else {
                std::cout << "가상 파일 탐색기 입니다\n명령어로는 ls,cd,mkdir,exit이 있습니다" << std::endl;
            }
        } catch (std::exception e) {
            std::cout << "에러가 발생했습니다 명령어를 점검해주십시오" << std::endl;
        }
    }


    return 0;
}
