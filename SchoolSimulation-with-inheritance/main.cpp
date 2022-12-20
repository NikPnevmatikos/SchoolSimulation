#include"school.h"
#include<cstdlib>
#include<cstring>
int main(int argc, char *argv[]){
    string line[18];

    int Cclass = atoi(argv[1]);
    int Lj = atoi(argv[2]);
    int Ls = atoi(argv[3]);
    int Lt = atoi(argv[4]);
    int N = atoi(argv[5]);

    school school(Cclass,Lj,Ls,Lt,N);

    char buf[20];
    int count = 0; 
    char* p;

    FILE* file;
    file = fopen("teachers.txt","r");
    while (fgets(buf,20,file)!=NULL){
      p = strtok(buf,"\n");
      school.teachreg(p);
    }
    fclose(file);
    file = fopen("students.txt","r");

    while (fgets(buf,20,file)!=NULL){
      p = strtok(buf,"\n");
      school.studreg(p);
    }

    fclose(file);
    school.simulation();
    school.attend();
    school.print();

}