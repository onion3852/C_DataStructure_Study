#include <stdio.h>
#include <string.h>

#define MAX_DATA 100
#define LIMIT    20

int read_til_space(char *ptr1, char *ptr2, char *ptr3, int num);
void add();
void find();
void delete();
void status();

int main(){
    char *name   [MAX_DATA];
    char *number [MAX_DATA];

    char a       [LIMIT];  // command
    char b       [LIMIT];  // name
    char c       [LIMIT];  // number

    const char *str1 = "add";
    const char *str2 = "find";        
    const char *str3 = "delete";    
    const char *str4 = "status";    
    const char *str5 = "exit";        

    printf("Phone Book Program Start...\n");
    printf("Type commands. ex) add, find, delete, status and exit\n\n");
    while(1){
        printf("$ ");
        read_til_space(a, b, c, LIMIT);
        
        if(!(strcmp(a, str1)))
            add();
        else if(!(strcmp(a, str2)))
            find();
        else if(!(strcmp(a, str3)))
            delete();
        else if(!(strcmp(a, str4)))
            status();
        else if(!(strcmp(a, str5))){
            printf("Program closed...\n");
            return 0;
        }
    }

    

    return 0;
}


////////////////////////////////////////////////////////////////
// function declaration
////////////////////////////////////////////////////////////////

int read_til_space(char *ptr1, char *ptr2, char *ptr3, int num){
    int ch;
    int n = 0;

    // store command
    while((ch = getchar()) != ('\0' || '\n')){
        if(n < num){
            ptr1[n] = ch;
            n++;
        }
    }
    ptr1[n] = '\0';
    n = 0;

    // store name if exists
    while((ch = getchar()) != ('\0' || '\n')){
        if(n < num){
            ptr2[n] = ch;
            n++;
        }
    }
    ptr2[n] = '\0';
    n = 0;

    // store number if exists
    while((ch = getchar()) != ('\0' || '\n')){
        if(n < num){
            ptr3[n] = ch;
            n++;
        }
    }
    ptr3[n] = '\0';
    n = 0;

    return n;
}

void add(){

}

void find(){

}

void delete(){

}

void status(){

}