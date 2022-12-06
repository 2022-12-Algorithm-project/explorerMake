#include <iostream>
#include <string>
#include <utility>
#include <Windows.h>
#include <iomanip>
#define MaxDirCount 20
#define MaxFileCount 20

typedef struct File{
    std::string name;
}File;

typedef struct Directory{
    std::string name;
    int Dcount;
    int Fcount;
    struct Directory* SubDir[MaxDirCount]{};
    struct File* SubFile[MaxFileCount]{};
}Directory;

Directory* RootDir(std::string Username){
    auto* root = new Directory;
    root->name = std::move(Username);
    root->Dcount = 0;
    root->Fcount = 0;
    return root;
}

int search(Directory* root,std::string target){
    Directory* temp = root;
    for(int i=0; i<temp->Dcount;i++){
        if(temp->SubDir[i]->name == target)
            return i;
    }
    return -1;
}

void macro(Directory* Root,std::string username) {
    system("color 02");
    std::cout << username;
    system("color");
    if(Root->name == username) {

        std::cout << ":~$ >> ";
    }
    else{

        std::cout << ":" << Root->name << " $ >> " ;
    }

}

Directory* ChangeDir(std::string CL,Directory* root){
    Directory* temp = root;
    int index = search(temp,std::move(CL));
    if(index > -1){
        //root = root->SubDir[/*인덱스값*/ 0];
        temp = temp->SubDir[index];
        return temp;
    }else{
        std::cout << "없는 디렉토리 입니다" << std::endl;
        return temp;
    }
}


void MakeDir(Directory* root,std::string ND){
    Directory* temp = root;

    int i=0;
    try {
        while (i < temp->Dcount) {

            if (temp->SubDir[i]->name == ND)
                throw ND;
            i++;
        }
        Directory* NewDir = RootDir(ND);
        temp->SubDir[i] = NewDir;
        temp->Dcount++;
    }catch (std::string e){
        std::cout << e << "는 이미 있는 디렉토리명 입니다" << std::endl;
    }

}
void List(Directory* root){
    Directory* temp = root;
    for(int i=0; i<temp->Dcount;i++){
        std::cout << temp->SubDir[i]->name << " ";
    }
    for(int j=0; j<temp->Fcount;j++){
        std::cout << temp->SubFile[j]->name << " ";
    }
    std::cout << std::endl;
}



int main() {

    std::cout << "유저 이름을 입력해주세요 : ";
    std::string Username;
    std::cin >> Username;
    system("cls");
    Directory* root = RootDir(Username);
    Directory* NL = root;
    std::string cmd;
    std::cin.ignore();
    while(cmd != "exit") {
        macro(NL,Username);
        getline(std::cin,cmd,'\n');
        //Command(cmd,NL);
        if(cmd.rfind("cd", 0) == 0){
            std::string temp = cmd.substr(3);
            NL = ChangeDir(temp,NL);
        }
        else if(cmd.rfind("mkdir", 0) == 0){
            std::string temp = cmd.substr(6);
            MakeDir(NL,temp);
        }
        else if(cmd.rfind("ls", 0) == 0){
            List(NL);
        }
    }


    return 0;
}
