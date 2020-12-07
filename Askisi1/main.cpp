#include"school.h"

int main(int argc, char *argv[]){
    string line[18];

    int Cclass = atoi(argv[1]);
    int Cyard = atoi(argv[2]);
    int Cstairs = atoi(argv[3]);
    int Ccorr = atoi(argv[4]);
    
    school school(Cclass,Cyard,Cstairs,Ccorr);

    char buf[20];
    int count = 0; 
    char* p;

    FILE* file;
    file = fopen("teacher.txt","r");
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
    school.print();

}