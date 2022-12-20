#include<iostream>
#include<string>
#include<vector>

using namespace std;

class classroom;
class corridor;
class stairs;
class floor;

//a class to be inherited by students and teachers
class Person{
    protected:
    string name;
    int ClassroomId;
    int FloorNumber;
    bool IsInClass;
    int tiredness;
    int degree;
    public:
    Person(string name,int ClassroomID,int FloorNumber,int degree);
    virtual ~Person();
    void print();                                               //print the stats of a person
    void print_name();                                          //print only the name of person
    int get_floor();                                            //return the number of the floor
    int get_classroom();                                        //return the number of classroom
    void set_inClass();                                         //change the status of person. now person is in class
    int get_tiredness();                                        //return the tiredness of the person
    void set_tiredness();                                       //changes the tiredness
};

//class the represent a student and is inherited by junior and senior class
class Student:public Person{
    public:
    Student(string name,int ClassroomID,int FloorNumber,int degree);
    ~Student();
};
//represent a junior students
class Junior:public Student{
    public:
    Junior(string name,int ClassroomID,int FloorNumber,int Lj);
    ~Junior();

};
//represent a senior student
class Senior:public Student{
    public:
    Senior(string name,int ClassroomID,int FloorNumber,int Ls);
    ~Senior();
};
//represent a teacher
class teacher:public Person{
    public:
    teacher(string name,int ClassroomID,int FloorNumber,int Lt);
    ~teacher();
    bool get_inClass();
};
//represent a space of the school and its inherited by all spaces of school
class Space{
    protected:
    vector<Student*> students;                          //a vector to keep students in each space
    public:
    Space();
    ~Space();
    virtual void enter(Student* student);               //put a student into the vector and print the name of the student
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class schoolyard:public Space{
    public:
        schoolyard();
        ~schoolyard();
        void enter(Student* Student)override;           //call Spaces enter and then print a message
        Student* exit();                                    //removing a student from the vector and print the name and a message
};

class stairs:public Space{
    public:
        stairs(); 
        ~stairs();
        void enter(Student* Student)override;        //call Spaces enter and then print a message
        Student* exit();                                //removing a student from the vector and print the name and a message
};

class floor:public Space{
    corridor* cor;                                          //floor has one corridor
    classroom* room[6];                                     //and 6 classrooms
    int number;
    public:
        floor(int Cclass,int number,int Lj,int Ls); 
        ~floor();
        void enter(Student* Student)override;           //print the name of the student, then a message, and then calls enter-exit of cor and enter of class
        void print();
        bool IsFull();                                  //A function to check if the whole floor has available space
        bool HasTeacher();                              //A function to check if the whole floor has available space for a teacher
        Student* assign(string name);                   //assign a student into a classroom
        teacher* assignteach(string name,int Lt);       //assign a teacher into a classroom
};      

class corridor:public Space{
    public:
        corridor(); 
        ~corridor();
        void enter(Student* Student)override;           //call Spaces enter and then print a message
        Student* exit();                                    //removing a student from the vector and print the name and a message
};

class classroom:public Space{
    bool IsSeniorClass;                                 //true if the class is for senior students, false for the oposite
    int degree;                                         //for senior class degree = LS, for junior degree = Lj
    teacher* teach;                                      //this object will help in create teacher function 
    Student* kid;                                       //this object will help in create Student function
    int available;                                      //a variable to check if a Student can be assign to the classroom
    bool hasteach;                                      //if a teacher has been assing to class then true, else false
    int id;                                             //number of class                    
    int floor_number;                                   //number of floor
    public:
        classroom(int Cclass,int id,int floor_number,bool IsSeniorClass,int degree);
        ~classroom();
        void enter(Student* Student)override;           //calls spaces enter,then changes the status of the students,and then prints a message
        void print();                                   //print people in class
        bool IsFull();                                  //A function to check if classroom has available space
        bool HasTeacher();                              //check if the class has a teacher
        Student* create_Student(string name);           //creates a student 
        teacher* create_teacher(string name,int Lt);    //created a teacher
};

class school:public Space {
    vector<teacher*> teach;                             //vector to keep teachers
    schoolyard* yard;                                   
    stairs* stair;
    floor* number[3]; 
    int Lj;
    int Ls;
    int Lt;
    int Hours;
    public:
        school(int Cclass,int Lj,int Ls,int Lt,int N);
        ~school();                                        
        void enter();                                       //run through the vector of students printing the name of all and a message 
        void print();                                       //calls a fuction to print the students and teachers
        void studreg(string name);                          //A function that assign a Student in a class
        void teachreg(string name);                         //A function that assign a teacher in a class
        void simulation();                                  //the fuction that places students and teachers to class
        void attend();                                      //a fuction the changes the tiredness of students and teachers
};   
