#include <stdio.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char *argv[]){

    //check if missing requiered files
    if(argc<3 || argc>5){
        printf("usage: <file1> <file2> [-f] [-v]\n");
        return 1;
    }

    // get files and flags from argv
    char *file1=argv[1];
    char *file2=argv[2];
    char *flag1=NULL;
    char *flag2=NULL;

    if(argc>=4) flag1=argv[3];
    if(argc==5) flag2=argv[4];

    //check if file2 exists
    if((flag1==NULL && flag2==NULL) ||
         (flag1 != NULL && strcmp(flag1, "-v")==0 && flag2==NULL) || 
         (flag2 != NULL && strcmp(flag2, "-v")==0 && flag1==NULL)){
        if(access(file2, F_OK)==0){
            if((flag1 != NULL && strcmp(flag1, "-v")==0) || (flag2 != NULL && strcmp(flag2, "-v")==0)) printf("target file exist\n");
            return 1;
        }
    }

    // opening/ creating files
    FILE *f1=fopen(file1, "rb");
    FILE *f2=fopen(file2, "wb");

    if(f1==NULL){
        printf("could not open file1\n");
        if(f2!=NULL) fclose(f2);
        if((flag1 != NULL && strcmp(flag1, "-v")==0) || (flag2 != NULL && strcmp(flag2, "-v")==0)) printf("general failure\n");
        return 1;
    }

    if(f2==NULL){
        printf("could not open file2\n");
        fclose(f1);
        if((flag1 != NULL && strcmp(flag1, "-v")==0) || (flag2 != NULL && strcmp(flag2, "-v")==0)) printf("general failure\n");
        return 1;
    }

    // copy file1 to file2
    char buffer[1024];
    size_t n;
    while((n=fread(buffer, 1, sizeof(buffer), f1))>0){
        fwrite(buffer, 1, n, f2);
    }

    if((flag1 != NULL && strcmp(flag1, "-v")==0) || (flag2 != NULL && strcmp(flag2, "-v")==0)) printf("success\n");
    fclose(f1);
    fclose(f2);
    return 0;
}