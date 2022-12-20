#include"school.h"
#include<cstdlib>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//class student 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
student::student(string name,int id,int floor){
        this->name = name;
        ClassroomID = id;
        ClassroomFloor = floor;
        position = "outside of school";
        cout << "A new Student has been created! ";
        cout << "Name: " << this->name << " Classroom: " << ClassroomID << " Floor: " << ClassroomFloor << endl;
}
student::student(){}                            
student::~student(){
        cout << "Student to be destroyed " << name << " !" << endl;
}
void student::print(){

        cout << name;    
}
int student::get_floor(){                               //return ClassroomFloor-1 because students Classroom floor strats from 1
        return ClassroomFloor-1;
}
int student::get_classroom(){                           //The size of classroom array is 6, but students have classroom id from 1-18 
        if(ClassroomID <= 6){                           //Depending of the floor each student is
                return ClassroomID-1;                   //this function return the true index of the classroom array 
        }
        else if(ClassroomID <= 12){
                return ClassroomID - 7;
        } 
        else{
                return ClassroomID - 13;
        }
}
void student::set_position(int index){                        //A function to call when a student move to another area of school
        switch (index)
        {
        case 1:
                position = "in school";
                break;
        case 2:
                position = "in schoolyard";
                break;
        case 3:
                position = "in stairs";
                break;
        case 4:
                position = "in floor";
                break;
        case 5:
                position = "in corridor";
                break;
        case 6:
                position = "in class";
                break;
        default:
                cout << "wrong index" << endl;
                break;
        }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//class schollyard 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
schoolyard::schoolyard(int Cyard){
        cout << "A new Schoolyard has been created!\n";
        curcapacity = 0;
        capacity = Cyard;
        students = new student*[capacity];                      //An array of students to have the students that are currently in schoolyard
}
schoolyard::schoolyard(){}   
schoolyard::~schoolyard(){
        delete[] students;
        cout << "Schoolyard to be destroyed!\n";
}
void schoolyard::enter(student* student,stairs* stair,floor* floor){     //stairs and floor are needed in later fucntions to be called
        
        if(curcapacity < capacity){                                     
                students[curcapacity] = student;
                students[curcapacity]->set_position(2);
                students[curcapacity]->print();
                cout << " has enter Schoolyard!" << endl;
                curcapacity++;
                exit(students[curcapacity-1],stair,floor);
        }
}
void schoolyard::exit(student* student,stairs* stair,floor* floor){
        curcapacity--;
        students[curcapacity]->print();
        cout << " has exit Schoolyard!" << endl;
        stair->enter(student,floor);
}
void schoolyard::print(){
        cout << "People in Schoolyard are: " << endl;
        for(int i = 0; i < curcapacity; i++){
               cout << "-";
               students[i]->print();
               cout << endl; 
        }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//class stairs
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
stairs::stairs(){}  
stairs::~stairs(){
        delete[] students;
        cout << "Stairs to be destroyed!\n";
} 
stairs::stairs(int Cstairs){
        cout << "A new stair has been created!\n";
        curcapacity = 0;
        capacity = Cstairs;
        students = new student*[capacity];
}
void stairs::enter(student* student,floor* floor){                      //floor is needed to call in stairs exit
        if(curcapacity < capacity){
                students[curcapacity] = student;
                students[curcapacity]->set_position(3);
                students[curcapacity]->print();
                cout << " has enter Stairs!" << endl;
                curcapacity++;
                exit(students[curcapacity-1],floor);
        }
}
void stairs::exit(student* student,floor* floor){
        curcapacity--;
        students[curcapacity]->print();
        cout << " has exit Stairs!" << endl;
        floor->enter(student);
}
void stairs::print(){
        cout << "People in Stairs are: " << endl;
        for(int i = 0; i < curcapacity; i++){
               cout << "-";
               students[i]->print();
               cout << endl; 
        }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//class corridor
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
corridor::corridor(){}
corridor::~corridor(){
        for(int i=0;i<curcapacity;i++){
                delete students[i];
        }
        delete[] students;
        cout << "Corridor to be destroyed!\n";
}
corridor::corridor(int Ccorr){
        cout << "A new corridor has been created!\n";
        curcapacity = 0;
        capacity = Ccorr;
        students = new student*[capacity];
}
void corridor::enter(student* student){
        if(curcapacity < capacity){
                students[curcapacity] = student;
                students[curcapacity]->set_position(5);
                students[curcapacity]->print();
                cout << " has enter Corridor!" << endl;
                curcapacity++;
        }
}
void corridor::exit(student* student){
        curcapacity--;
        students[curcapacity]->print();
        cout << " has exit Corridor!" << endl;
}
void corridor::print(){
        cout << "People in Corridor are: " << endl;
        for(int i = 0; i < curcapacity; i++){
                cout << "-";
                students[i]->print();
                cout << endl; 
        }   
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//class classroom
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
classroom::classroom(){}  
classroom::~classroom(){
        for(int i=0;i<curcapacity;i++){
                delete students[i];
        }
        delete[] students;
        cout << "Classroom to be destroyed!\n";
}
classroom::classroom(int Cclass,int id,int floor_number){
        cout << "A new classroom has been created!\n";
        this->id = id;
        curcapacity = 0;
        capacity = Cclass;
        available = Cclass;                                     
        hasteach = false;
        this->floor_number = floor_number;
        students = new student*[capacity];
}
void classroom::enter(student* student){
        if(teach->IsInClassroom() == false){
                if(curcapacity < capacity){
                        students[curcapacity] = student;
                        students[curcapacity]->set_position(6);
                        students[curcapacity]->print();
                        cout << " has enter Classroom " << id  << " !" << endl;
                        curcapacity++;
                }
        }
}
void classroom::print(){
        cout << "People in classroom " << id << " are: " << endl;
        for(int i = 0; i < curcapacity; i++){
                cout << "-";
                students[i]->print();
                cout << endl; 
        }
}
bool classroom::IsFull(){
        if(available == 0){
                return true;
        }
        return false;
}
bool classroom::HasTeacher(){
        return hasteach;
}
student* classroom::create_student(string name){                
        kid = new student(name,id,floor_number);
        available--;      
        return kid;
}
teacher* classroom::create_teacher(string name){
        teach = new teacher(name,id);
        hasteach = true;
        return teach;
}
bool classroom::isteacherinclass(){                     
        return teach->IsInClassroom();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//class floor
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
floor::floor(){}    
floor::~floor(){
        delete cor;
        for(int i = 0; i<6;i++){
                delete room[i];
        }
        cout << "Floor to be destroyed!\n";
}  
floor::floor(int Cclass,int Ccorr,int number){
        cout << "A new floor has been created!\n";
        this->number = number;
        cor = new corridor(Ccorr);
        for(int i = 0; i < 6; i++){
                if(this->number == 1){                                  //the classroom id depents on floor number
                        room[i] = new classroom(Cclass,i+1,1);
                }
                else if(this->number == 2){
                        room[i] = new classroom(Cclass,i+7,2);
                }
                else{
                        room[i] = new classroom(Cclass,i+13,3);
                }
        }
}
void floor::enter(student* student){
        student->set_position(4);
        student->print();
        cout << " has enter Floor " << number << " !" << endl;
        cor->enter(student);
        if(room[student->get_classroom()]->isteacherinclass()==false){          //if teacher is in classroom then students can't go in
                cor->exit(student);
                room[student->get_classroom()]->enter(student);
        }
}
void floor::print(){
        cout << "Floor " << number << " contains: " << endl;
        cor->print();
        for(int i = 0; i < 6; i++){
                room[i]->print();
        }
}
bool floor::IsFull(){
        int counter = 0;
        for(int i = 0; i < 6; i++){                     
                if(room[i]->IsFull()==true){
                        counter++;

                }
        }
        if(counter == 6){                       //if all 6 classroom of floor doen't have available  space then the floor is full
                return true;
        }
        return false;
}
bool floor::HasTeacher(){
        int counter = 0;
        for(int i = 0; i < 6; i++){
                if(room[i]->HasTeacher()==true){
                        counter++;
                }
        }
        if(counter == 6){                       //if all 6 classroom of floor have teachers then floor is full of teachers
                return true;
        }
        return false;   
}
student* floor::assign(string name){
        for(int i = 0; i < 6; i++){
               if(room[i]->IsFull()==false){                    //find the first class that have available space 
                      return room[i]->create_student(name);    //and assign student in it
                      
                } 
        }
        return NULL;
}
teacher* floor::assignteach(string name){
        for(int i = 0; i < 6; i++){
                if(room[i]->HasTeacher()==false){               //find the first class that does not have a teacher
                      return room[i]->create_teacher(name);    //and assign teacher in it
                } 
        }   
        return NULL;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//class teacher
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
teacher::teacher(string name,int id){
        this->name = name;
        ClassroomID = id;
        IsInClass = false; 
        cout << "A new Teacher has been created! " << "Name: " << name << " Classroom: " << ClassroomID << endl;

        }
teacher::teacher(){}
teacher::~teacher(){
        cout << "Teacher to be destroyed " << name << " !" << endl;
}
void teacher::place(){
        IsInClass = true;
}
void teacher::print(){
        cout << "Teacher is: " << name << endl;    
}
bool teacher::IsInClassroom(){
        return IsInClass;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//class school
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
school::school(int Cclass, int Cyard, int Cstairs, int Ccorr){
        cout << "A new School has been created\n" ;
        curcapacity = 0;
        teachcounter = 0;
        for(int i = 0; i<3; i++){
                number[i] = new floor(Cclass,Ccorr,i+1);                        //floor number start from 1
        }
        yard = new schoolyard(Cyard);
        stair = new stairs(Cstairs);
        students = new student*[Cclass*18];
        teach = new teacher*[18];
}
school::~school(){
        for(int i = 0; i<3;i++){
                delete number[i];
        }
        delete yard;
        delete stair;
        for(int i = 0;i<teachcounter;i++){
                delete teach[i];
        }
        delete[] teach;
        delete[] students;
        cout << "School to be destroyed\n";

}

void school::enter(){
        for(int i=0; i < curcapacity; i++){                     //places all the students inside school
                students[i]->set_position(1);
                students[i]->print();
                cout  << " has enter school! " << endl;
        }
}
void school::exit(student* student,stairs* stairs,floor* floor){        //stairs and floor are needed in later functions
        curcapacity--;
        yard->enter(student,stairs,floor);
}
void school::print(){
        cout << "School life consist of:" << endl;
        yard->print();
        stair->print();
        for(int i = 0; i < 3; i++){
                number[i]->print();
        }
}
void school::studreg(string name){                              
        for(int i = 0; i < 3; i++){                             //for each floor
                if(number[i]->IsFull() == false){               //find the first floor that has available space
                        students[curcapacity] = number[i]->assign(name);                //and call the assign function to put student in a class
                        curcapacity++;
                        break;
                }
        }
}

void school::teachreg(string name){
        for(int i = 0; i < 3; i++){                             //for each floor
                if(number[i]->HasTeacher() == false){           //find the first floor that a class does not have a teacher
                        teach[teachcounter] = number[i]->assignteach(name);             //assign the teacher to a class
                        teachcounter++;
                        break;
                }
        } 
}
//swap 2 indexes of array type student
void swap(student** a,student** b){
        student* temp = *a;
        *a = *b;
        *b = temp;
}
//A function to suffle an array type students
void randomize_array(student** array,int size){
        srand(time(NULL));
        for(int i = size-1; i>=0; i--){
                int j = rand() % (i+1);
                swap(&array[i],&array[j]);
        }
}
void school::simulation(){
        int end = curcapacity;
        randomize_array(students,end);
        srand (time(NULL));
        enter();                                                //first all students go inside school
        for(int i = 0; i < end; i++){                           //then each one will go in class through schoolyard then stairs then floor,corridor
                if( rand()% 3 == 1){
                        int id = rand()%teachcounter;
                        if(teach[id]->IsInClassroom()==false){          //students will stay in corridor if teacher is in class
                                teach[id]->place();
                        }
                }
                exit(students[i],stair,number[students[i]->get_floor()]);               
        }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////