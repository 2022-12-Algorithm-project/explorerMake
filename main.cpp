#include <iostream>
#include <string>
#include <utility>
#include <Windows.h>
#include <iomanip>
#include <stdlib.h>
#define MaxDirCount 20
#define MaxFileCount 20
#define STACK_SIZE 100


typedef struct File {
    std::string name;
}File;

typedef struct Directory {
    std::string name;
    int Dcount;
    int Fcount;
    struct Directory* LastDir;
    struct Directory* SubDir[MaxDirCount]{};
    struct File* SubFile[MaxFileCount]{};
}Directory;

typedef int element;

typedef struct Stack {
    int top;
    element data[STACK_SIZE];
}Stack;

Stack s;

void initStack() {
    s.top = -1;
}

int isEmpty() {
    if (s.top == -1) return 1;
    else return 0;
}

int isFull() {
    if (s.top == STACK_SIZE - 1) return;
    else return 0;
}

void push(Directory* LastDir) {
    if (isFull()) return;
    s.top += 1;
    s.data[s.top] = LastDir;
}

element pop() {
    element temp;
    if (isEmpty()) return 0;
    temp = s.data[s.top];
    s.top -= 1;
    return temp;
}

element peek() {
    if (isEmpty()) return 0;
    return s.data[s.top];
}
//Stack�� LastDir�� �ּҸ� ����

Directory* RootDir(std::string Username) {
    auto* root = new Directory;
    root->name = std::move(Username);
    root->Dcount = 0;
    root->Fcount = 0;
    root->LastDir = NULL;
    return root;
}

int search(Directory* root, std::string target) {
    Directory* temp = root;
    try {
        for (int i = 0; i < temp->Dcount; i++) {
            if (temp->SubDir[i]->name == target)
                return i;
        }
        return -1;
    }
    catch (std::exception e) {
        std::cout << "������ �����" << std::endl;
    }
}

void macro(Directory* Root, std::string username) {
    system("color 02");
    std::cout << username;
    system("color");
    if (Root->name == username) {

        std::cout << ":~$ >> ";
    }
    else {

        std::cout << ":" << Root->name << " $ >> ";
    }

}

Directory* ChangeDir(std::string CL, Directory* root) {
    try {
        Directory* temp = root;
        int index = search(temp, std::move(CL));
        if (index > -1) {
            //root = root->SubDir[/*�ε�����*/ 0];
            temp = temp->SubDir[index];
            return temp;
        }
        else {
            std::cout << "���� ���丮 �Դϴ�" << std::endl;
            return temp;
        }
    }
    catch (std::exception e) {
        std::cout << "������ �߻��߽��ϴ� ��ɾ �������ֽʽÿ�" << std::endl;
    }
}


void MakeDir(Directory* root, std::string ND) {
    Directory* temp = root;

    int i = 0;
    try {
        while (i < temp->Dcount) {

            if (temp->SubDir[i]->name == ND)
                throw ND;
            i++;
        }
        Directory* NewDir = RootDir(ND);
        NewDir->LastDir = temp;
        temp->SubDir[i] = NewDir;
        temp->Dcount++;
    }
    catch (std::string e) {
        std::cout << e << "�� �̹� �ִ� ������ �Դϴ�" << std::endl;
    }

}
void List(Directory* root) {
    Directory* temp = root;
    for (int i = 0; i < temp->Dcount; i++) {
        std::cout << temp->SubDir[i]->name << "/ ";
    }
    for (int j = 0; j < temp->Fcount; j++) {
        std::cout << temp->SubFile[j]->name << " ";
    }
    std::cout << std::endl;
}



int main() {

    std::cout << "���� �̸��� �Է����ּ��� : ";
    std::string Username;
    std::cin >> Username;
    system("cls");
    Directory* root = RootDir(Username);
    Directory* NL = root;
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
            }
            else if (cmd.rfind("mkdir", 0) == 0) {
                std::string temp = cmd.substr(6);
                MakeDir(NL, temp);
            }
            else if (cmd.rfind("ls", 0) == 0) {
                List(NL);
            }
            else {
                std::cout << "���� ���� Ž���� �Դϴ�\n��ɾ�δ� ls,cd,mkdir,exit�� �ֽ��ϴ�" << std::endl;
            }
        }
        catch (std::exception e) {
            std::cout << "������ �߻��߽��ϴ� ��ɾ �������ֽʽÿ�" << std::endl;
        }
    }

    s.top = -1;
    push(root);
    printf("%d\n", pop());
    printf("%d\n", peek());
    printf("%d\n", pop());
    return 0;
}
