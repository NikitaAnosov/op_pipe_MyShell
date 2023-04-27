#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]){

    //check if missing requiered files
    if(argc<3 || argc>5){
        printf("usage: <file1> <file2> [-i] [-v]\n");
        return 1;
    }

    // get files and flags from argv
    char *file1=argv[1];
    char *file2=argv[2];
    char *flag1=NULL;
    char *flag2=NULL;

    if(argc>=4) flag1=argv[3];
    if(argc==5) flag2=argv[4];

    //opening files
    FILE *f1=fopen(file1, "rb");
    FILE *f2=fopen(file2, "rb");

    if(f1==NULL){
        printf("could not open file1\n");
        if(f2!=NULL) fclose(f2);
        return 2;
    }

    if(f2==NULL){
        printf("could not open file2\n");
        fclose(f1);
        return 2;
    }

    //compare files
    int bytes1, bytes2;

    do {
        bytes1 = fgetc(f1);
        bytes2 = fgetc(f2);

        // if -i ignore case
        if((flag1 != NULL && strcmp(flag1, "-i")==0) || (flag2 != NULL && strcmp(flag2, "-i")==0)){
            bytes1=tolower(bytes1);
            bytes2=tolower(bytes2);
        }

        if(bytes1 != bytes2){
            // if -v print to terminal distinct
            if((flag1 != NULL && strcmp(flag1, "-v")==0) || (flag2 != NULL && strcmp(flag2, "-v")==0)){
                printf("distinct\n");
            }
            fclose(f1);
            fclose(f2);
            return 1;
        }
    } while (bytes1 != EOF && bytes2 != EOF);

    // check if files are not the same length
    if(bytes1 != bytes2){
        // if -v print to terminal distinct
        if((flag1 != NULL && strcmp(flag1, "-v")==0) || (flag2 != NULL && strcmp(flag2, "-v")==0)){
            printf("distinct\n");
        }
        fclose(f1);
        fclose(f2);
        return 1;
    }

    // if -v print to terminal if equal
    if((flag1 != NULL && strcmp(flag1, "-v")==0) || (flag2 != NULL && strcmp(flag2, "-v")==0)){
        printf("equal\n");
    }

    fclose(f1);
    fclose(f2);
    return 0;
}
