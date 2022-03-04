#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Looked up how to create int array type of function


int * readFromStdIn();
int * readFromFile(char argv[], int n);
void printInfo(char argv[], int* totalsGiven, int n, int f, int c, int w, int l);

int main(int argc, char *argv[]){


    int flags = 0;
    int wflag = 0;
    int lflag = 0;
    int cflag = 0;
    int f = 1;
    int fileExists = 0;
    int multipleFiles = 0;
    int flagSearching = 1;

    int totalChars = 0;
    int totalWords = 0;
    int totalLines = 0;
    int * totalArray;
    
    if(argv[1] == NULL) {
        totalArray = readFromStdIn(f);
        printInfo("-stdin- ", totalArray, -1, 0, 1, 1, 1);
    }

    else {
        while(argv[f] != NULL) { 

            if(flagSearching) {
            
                if(strcmp(argv[f], "-c") == 0) {
                    cflag = 1;
                    flags = 1;
                }

                else if(strcmp(argv[f], "-l") == 0) {
                    lflag = 1;
                    flags = 1;
                }

                else if(strcmp(argv[f], "-w") == 0) {
                    wflag = 1;
                    flags = 1;
                }

                else {
                    flagSearching = 0;
                    f--;
                }

            }

            else {
                

                if(fileExists) {
                    multipleFiles = 1;
                }

                fileExists = 1;


                if(strcmp(argv[f],"+") == 0) {
                    totalArray = readFromStdIn(f);

                    printInfo(argv[f], totalArray, -1, flags, cflag, wflag, lflag);

                    totalChars += totalArray[0];
                    totalWords += totalArray[1];
                    totalLines += totalArray[2];
                    free(totalArray);
                }

                else {

                    totalArray = readFromFile(argv[f], f);

                    printInfo(argv[f], totalArray, f, flags, cflag, wflag, lflag);

                    totalChars += totalArray[0];
                    totalWords += totalArray[1];
                    totalLines += totalArray[2];
                    free(totalArray);
                }

            }


            f++;

            
        }

    }


    if(multipleFiles) {

        printf("total ");


        if(!flags) {

            printf("%d %d %d\n", totalLines, totalWords, totalChars);

        }

        else {

            if(lflag) {
                printf("%d ", totalLines);
            }

            

            if(wflag) {
                printf("%d ", totalWords);
            }

            if(cflag) {
                printf("%d ", totalChars);
            }

            printf("\n");
        }

    }




}

void printInfo(char argv[], int* totalsGiven, int n, int f, int c, int w, int l) {
    
    if(n == -1) {
        printf("-stdin- ");
    }

    else {
        printf("%s ", argv);
    }

    if(!f) {

        printf("%d %d %d\n", totalsGiven[2], totalsGiven[1], totalsGiven[0]);
    }

    else {

        if(l) {
            printf("%d ", totalsGiven[2]);
        }

        

        if(w) {
            printf("%d ", totalsGiven[1]);
        }

        if(c) {
            printf("%d ", totalsGiven[0]);
        }

        printf("\n");
    }

}


int * readFromFile(char argv[], int n) {

    FILE * infile = fopen(argv, "r");
    


    int charTotal = 0;
    int lineTotal = 0;
    int wordTotal = 0;
    char a;
    char b = ' ';

    while(a = fgetc(infile)) {
        if(a == EOF) {
            break;
        }
        if(a == '\n') {
            lineTotal++;
        }

        if(!isspace(a) && isspace(b)) {
            wordTotal++;
        }
        charTotal++;
        b = a;
    }


    int * totals = (int *) malloc(sizeof(int) * 3);
    totals[0] = charTotal;
    totals[1] = wordTotal;
    totals[2] = lineTotal;

    return totals;


    }






int * readFromStdIn() {

    int charTotal = 0;
    int lineTotal = 0;
    int wordTotal = 0;
    char a;
    char b = ' ';

    while(a = getchar()) {

        if(a == EOF) {
            break;
        }
        if(a == '\n') {
            lineTotal++;
        }

        if(!isspace(a) && isspace(b)) {
            wordTotal++;
        }
        charTotal++;
        b = a;
    }

    int * totals = (int *) malloc(sizeof(int) * 3);
    totals[0] = charTotal;
    totals[1] = wordTotal;
    totals[2] = lineTotal;

    return totals;

    
}
