#include<iostream>
#include<cstring>
using namespace std;

#ifndef school_H
#define school_H

class classroom;
class teacher; 
class stairs;
class floor;

class student{
    string name;
    int ClassroomID;
    int ClassroomFloor;
    string position;
    public:
        student(string name,int clas,int floor);
        student();                                                 //an empty constuctor for declaration in each class
        ~student();
        void print();
        int get_floor();
        int get_classroom();
        void set_position(int index);
};

class schoolyard{
    student** students;
    int capacity;                                                   //max capacity
    int curcapacity;                                                //current capacity
    public:
        schoolyard();                                               //an empty constuctor for declaration in each class
        schoolyard(int Cyard);
        ~schoolyard();
        void enter(student* student,stairs* stairs,floor* floor);
        void exit(student* student,stairs* stairs,floor* floor);
        void print();
};

class stairs{
    student** students;
    int curcapacity;
    int capacity;
    public:
        stairs(int Cstairs); 
        stairs();                                                    //an empty constuctor for declaration in each class
        ~stairs();
        void enter(student* student,floor* floor);
        void exit(student* student,floor* floor);
        void print();
};

class corridor{
    student** students;
    int curcapacity;
    int capacity;
    public:
        corridor(int Ccorr); 
        corridor();                                                   //an empty constuctor for declaration in each class
        ~corridor();
        void enter(student* student);
        void exit(student* student);
        void print();
};

class classroom{
    student** students;
    teacher* teach;                                      //this object will help in create teacher function 
    student* kid;                                       //this object will help in create student function
    int available;                                      //a variable to check if a student can be assign to the classroom
    bool hasteach;                                      //if a teacher has been assing to class then true, else false
    int curcapacity;
    int capacity;
    int id;
    int floor_number;
    public:
        classroom(int Cclass,int id,int floor_number);
        classroom();                                    //an empty constuctor for declaration in each class
        ~classroom();
        void enter(student* student);
        void print();
        bool IsFull();                                  //A function to check if classroom has available space
        bool HasTeacher();
        student* create_student(string name);
        teacher* create_teacher(string name);
        bool isteacherinclass();                        //A function to check if teacher is in classroom
};

class floor{
    corridor* cor;
    classroom* room[6];      
    int number;

    public:
        floor(int Cclass,int Ccorr,int number); 
        floor();                                        //an empty constuctor for declaration in each class
        ~floor();
        void enter(student* student);
        void print();
        bool IsFull();                                  //A function to check if the whole floor has available space
        bool HasTeacher();                              //A function to check if the whole floor has available space for a teacher
        student* assign(string name);
        teacher* assignteach(string name);
};

class teacher{
    string name;
    int ClassroomID;
    bool IsInClass;
    public:
        teacher(string name,int id);
        teacher();
        ~teacher();
        void place();                                     //places teacher into classroom
        void print();
        bool IsInClassroom();
};



class school {
    schoolyard* yard;
    stairs* stair;
    floor* number[3]; 
    student** students;
    teacher** teach;
    int teachcounter;
    int curcapacity;
    public:
        school(int Cclass, int Cyard, int Cstairs, int Ccorr);
        ~school();                                        
        void enter();
        void exit(student* student,stairs* stairs,floor* floor);
        void print();
        void studreg(string name);                          //A function that assign a student in a class
        void teachreg(string name);                         //A function that assign a teacher in a class
        void simulation();                                 
};

#endif