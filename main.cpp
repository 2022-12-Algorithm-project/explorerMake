#include <iostream>
#include <string>
#include <utility>
#include <Windows.h>
#include <iomanip>

#define MaxDirCount 20
#define MaxFileCount 20
struct File {
    std::string name;
};

struct Directory {
    std::string name;
    int Dcount{};
    int Fcount{};
    struct Directory *LastDir{};
    struct Directory *SubDir[MaxDirCount]{};
    struct File *SubFile[MaxFileCount]{};
};


Directory *RootDir(std::string Username) {
    auto *root = new Directory;
    root->name = std::move(Username);
    root->Dcount = 0;
    root->Fcount = 0;
    root->LastDir = nullptr;
    return root;
}

int search(Directory *root, const std::string &target) {
    Directory *temp = root;
    for (int i = 0; i < temp->Dcount; i++) {
        if (temp->SubDir[i]->name == target)
            return i;
    }
    return -1;

}

void macro(Directory *Root, const std::string &username) {
    system("color 02");
    std::cout << username;
    system("color");
    if (Root->name == username) {

        std::cout << ":~$ >> ";
    } else {

        std::cout << ":" << Root->name << " $ >> ";
    }

}

Directory *ChangeDir(const std::string &CL, Directory *root) {
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
        int index = search(temp, CL);
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


void MakeDir(Directory *root, const std::string &ND) {
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

void MakeFile(Directory *root, const std::string &NF) {
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

void PWD(Directory *root) {
    Directory *temp = root;
    if (temp->LastDir) PWD(temp->LastDir);
    std::cout << temp->name << "/";
}

void findDir(Directory *root, const std::string &target) {
    Directory *temp = root;
    std::cout << target << std::endl;
    int i = 0;
    if (temp->name == target) return PWD(temp);
    while (i < temp->Dcount) {
        if (temp->SubDir[i]->name == target) return PWD(temp);
        i++;
    }
    std::cout << "찾는 폴더가 없습니다" << std::endl;
}

void findFile(Directory *root, const std::string &target) {
    Directory *temp = root;
    std::cout << target << std::endl;
    int i = 0;
    while (i < temp->Fcount) {
        if (temp->SubFile[i]->name == target) {
            PWD(temp);
            std::cout << "/target" << std::endl;
        }
        i++;
    }
    std::cout << "찾는 폴더가 없습니다" << std::endl;
}

void Del2(Directory *root, Directory *deleted) {
    Directory *temp = root;
    int i = 0;
    while (i < temp->Dcount) {
        if (temp->SubDir[i] == deleted) {
            temp->SubDir[i] = nullptr;
            break;
        }
        i++;
    }
    while (i < temp->Dcount) {
        if (temp->SubDir[i + 1]) temp->SubDir[i] = temp->SubDir[i + 1];
        i++;
    }
    temp->Dcount--;
}

Directory *Delete(Directory *root) {
    Directory *temp = root;
    Directory *deleted = root->LastDir;
    int i = 0, j = 0;
    while (i < temp->Dcount) {
        if (temp->SubDir[i]) Delete(temp->SubDir[i]);
        i++;
    }
    while (j < temp->Fcount) {
        if (temp->SubFile[i]) delete (temp->SubFile[i]);
        j++;
    }
    Del2(temp->LastDir, temp);
    delete (temp);
    std::cout << "삭제 되었습니다" << std::endl;
    return deleted;

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
            if (cmd.rfind("cd ", 0) == 0) {
                std::string temp = cmd.substr(3);
                NL = ChangeDir(temp, NL);
            } else if (cmd.rfind("mkdir ", 0) == 0) {
                std::string temp = cmd.substr(6);
                MakeDir(NL, temp);
            } else if (cmd.rfind("touch ", 0) == 0) {
                std::string temp = cmd.substr(6);
                MakeFile(NL, temp);
            } else if (cmd.rfind("ls", 0) == 0) {
                List(NL);
            } else if (cmd.rfind("pwd", 0) == 0) {
                PWD(NL);
                std::cout << std::endl;
            } else if (cmd.rfind("finddir ", 0) == 0) {
                std::string temp = cmd.substr(8);
                findDir(NL, temp);
                std::cout << std::endl;
            } else if (cmd.rfind("findfile ", 0) == 0) {
                std::string temp = cmd.substr(9);
                findFile(NL, temp);
                std::cout << std::endl;
            } else if (cmd.rfind("delete", 0) == 0) {
                NL = Delete(NL);
            } else if (cmd.rfind("real ", 0) == 0) {
                const char *temp = cmd.substr(5).data();
                system(temp);
            } else if (cmd.rfind("help", 0) == 0) {
                std::cout << "가상 파일 탐색기 입니다\n명령어 : " << std::endl;
                std::cout << "cd %s          :: %s폴더로 이동합니다" << std::endl;
                std::cout << "mkdir %s       :: 현재 위치에 %s폴더를 만듭니다" << std::endl;
                std::cout << "touch %s       :: 현재 위치에 %s파일을 만듭니다" << std::endl;
                std::cout << "finddir %s     :: 현재 위치에 있는 %s 폴더를 찾습니다" << std::endl;
                std::cout << "findfile %s    :: 현재 위치에 있는 %s 파일을 찾습니다" << std::endl;
                std::cout << "delete         :: 현재 위치의 폴더를 삭제 하고 전 폴더로 이동합니다" << std::endl;
                std::cout << "ls             :: 현재 위치 폴더와 파일 목록을 제공합니다" << std::endl;
                std::cout << "pwd            :: root폴더부터 현재까지의 경로를 보여줍니다" << std::endl;
            } else {
                std::cout << cmd << " 명령어는 존재 하지 않습니다" << std::endl;
            }
        } catch (std::exception e) {
            std::cout << "에러가 발생했습니다 명령어를 점검해주십시오" << std::endl;
        }
    }


    return 0;
}
