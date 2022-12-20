#include"school.h"
#include<algorithm>

Person::Person(string name,int ClassroomID,int FloorNumber,int degree):
    name(name),ClassroomId(ClassroomID),FloorNumber(FloorNumber){
        IsInClass = false;                                          //when created the person is not in class
        tiredness = 0;                                              //and not tired
        this->degree = degree;
    }
Person::~Person(){
}
void Person::print(){
    cout << " Name: " << name << " Floor: " << FloorNumber << " Class: " << ClassroomId << endl; 
}
void Person::print_name(){
    cout << name;
}
int Person::get_floor(){                               //return ClassroomFloor-1 because students Classroom floor strats from 1
    return FloorNumber-1;
}
int Person::get_classroom(){
    if(ClassroomId <= 6){                           //Depending of the floor each student is
        return ClassroomId-1;                   //this function return the true index of the classroom array 
    }
    else if(ClassroomId <= 12){
        return ClassroomId - 7;
    } 
    else{
        return ClassroomId - 13;
    }

}
void Person::set_inClass(){
    IsInClass = true;
}
int Person::get_tiredness(){
    return tiredness;
}
void Person::set_tiredness(){
    this->tiredness += degree;
}
//////////////////////////////////////////////////////////////////////////////////////////////
Student::Student(string name,int ClassroomID,int FloorNumber,int degree):Person(name,ClassroomID,FloorNumber,degree){

}
Student::~Student(){
}
//////////////////////////////////////////////////////////////////////////////////////////////
Junior::Junior(string name,int ClassroomID,int FloorNumber,int Lj):
    Student(name,ClassroomID,FloorNumber,Lj){

        cout << "A new junior student has been created!";
        print();
}
Junior::~Junior(){
    cout << "Junior to be Destroyed!";
    print();
}
//////////////////////////////////////////////////////////////////////////////////////////////
Senior::Senior(string name,int ClassroomID,int FloorNumber,int Ls):
    Student(name,ClassroomID,FloorNumber,Ls){
        cout << "A new senior student has been created!";
        print();
}
Senior::~Senior(){
    cout << "Senior to be Destroyed!";
    print();
}
//////////////////////////////////////////////////////////////////////////////////////////////
teacher::teacher(string name,int ClassroomId,int FloorNumber,int Lt):Person(name,ClassroomId,FloorNumber,Lt){
    cout << "A new Teacher has been created! ";
    print();
}
teacher::~teacher(){
    cout << "Teacher to be destroyed!";
    print();
}
bool teacher::get_inClass(){
    return IsInClass;
}
//////////////////////////////////////////////////////////////////////////////////////////////
Space::Space(){}
Space::~Space(){
    students.clear();
}
void Space::enter(Student* student){
    students.push_back(student);                                    //add a student to vector
    students.at(students.size()-1)->print_name();                   //print the name
}
//////////////////////////////////////////////////////////////////////////////////////////////
schoolyard::schoolyard(){
    cout << "A new Schoolyard has been created!\n";
}
schoolyard::~schoolyard(){
    cout << "Schoolyard to be destroyed!\n";
}
void schoolyard::enter(Student* student){                            
        Space::enter(student);                              
        cout << " has enter Schoolyard!" << endl;
}
Student* schoolyard::exit(){
        Student* kid = students.at(0); 
        students.at(0)->print_name();                               //print the name
        cout << " has exit Schoolyard!" << endl;
        students.erase(students.begin());
        return kid;                           //remove from vector
}
//////////////////////////////////////////////////////////////////////////////////////////////
stairs::stairs(){
    cout << "A new stair has been created!\n";
}
stairs::~stairs(){
    cout << "Stairs to be destroyed!\n";
} 
void stairs::enter(Student* student){                     
    Space::enter(student);
    cout << " has enter Stairs!" << endl;
}
Student* stairs::exit(){
        Student* kid = students.at(0);
        students.at(0)->print_name();
        cout << " has exit Stairs!" << endl;
        students.erase(students.begin());
        return kid;
}
//////////////////////////////////////////////////////////////////////////////////////////////
floor::floor(int Cclass,int number,int Lj,int Ls){
    cout << "A new floor has been created!\n";
    this->number = number;
    cor = new corridor();
    for(int i = 0; i < 6; i++){
        if(this->number == 1){                                  //the classroom id depents on floor number
            if(i<3){                                            //if class is for senior or junior depents on class number
                room[i] = new classroom(Cclass,i+1,1,false,Lj);
            }
            else{
                room[i] = new classroom(Cclass,i+1,1,true,Ls);
            }
        }
        else if(this->number == 2){
            if(i < 3){
                room[i] = new classroom(Cclass,i+7,2,false,Lj);
            }
            else{
                room[i] = new classroom(Cclass,i+7,2,true,Ls);
            }
        }
        else{
            if(i < 3){
                room[i] = new classroom(Cclass,i+13,3,false,Lj);
            }
            else{
                room[i] = new classroom(Cclass,i+13,3,true,Ls);
            }
        }
    }
}
floor::~floor(){
    delete cor;
    for(int i = 0; i<6;i++){
        delete room[i];
    }
    cout << "Floor to be destroyed!\n";
} 
void floor::enter(Student* student){
        student->print_name();
        cout << " has enter Floor " << number << "!" << endl;
        cor->enter(student);
        //cor->exit(student);
        room[student->get_classroom()]->enter(cor->exit());
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
Student* floor::assign(string name){
    for(int i = 0; i < 6; i++){
        if(room[i]->IsFull()==false){                    //find the first class that have available space 
            return room[i]->create_Student(name);    //and assign student in it        
        } 
    }
    return NULL;
}
teacher* floor::assignteach(string name,int Lt){
    for(int i = 0; i < 6; i++){
        if(room[i]->HasTeacher()==false){               //find the first class that does not have a teacher
            return room[i]->create_teacher(name,Lt);    //and assign teacher in it
        } 
    }   
    return NULL;
}
void floor::print(){
    cout << "Floor " << number << " contains: " << endl;
    for(int i = 0; i < 6; i++){
        room[i]->print();
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////
corridor::corridor(){
    cout << "A new corridor has been created!\n";
}
corridor::~corridor(){
    cout << "Corridor to be destroyed!\n";
}
void corridor::enter(Student* student){
    Space::enter(student);
    cout << " has enter Corridor!" << endl;
}
Student* corridor::exit(){
        Student* kid = students.at(0);
        students.at(0)->print_name();
        students.erase(students.begin());
        cout << " has exit Corridor!" << endl;
        return kid;
}
//////////////////////////////////////////////////////////////////////////////////////////////
classroom::classroom(int Cclass,int id,int floor_number,bool IsSeniorClass,int degree){
    cout << "A new classroom has been created!\n";
    this->id = id;
    available = Cclass;                                     
    hasteach = false;
    this->floor_number = floor_number;
    this->IsSeniorClass = IsSeniorClass;
    this->degree = degree;
}
classroom::~classroom(){
    cout << "Classroom to be destroyed!\n";
}
void classroom::enter(Student* student){
    Space::enter(student);
    students.at(students.size()-1)->set_inClass();
    cout << " has enter Classroom " << id  << "!" << endl;
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
Student* classroom::create_Student(string name){                
    if(IsSeniorClass == false){
        kid = new Junior(name,id,floor_number,degree);
    }
    else{
        kid = new Senior(name,id,floor_number,degree);
    }
    available--;      
    return kid;
}
teacher* classroom::create_teacher(string name,int Lt){
    teach = new teacher(name,id,floor_number,Lt);
    hasteach = true;
    return teach;
}
void classroom::print(){
    cout << "People in classroom " << id << " are: " << endl;
    for(int i = 0; i < students.size(); i++){
        cout << "-";
        students.at(i)->print_name();
        cout <<" degree of tiredness: " << students.at(i)->get_tiredness() << endl;
    }
    if(teach->get_inClass()==true){
        cout << "The Teacher is: " << endl << "-";
        teach->print_name();
        cout <<" degree of tiredness: " << teach->get_tiredness() << endl;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////
school::school(int Cclass,int Lj,int Ls,int Lt,int N){        
    cout << "A new School has been created\n" ;
    yard = new schoolyard();
    stair = new stairs();
    for(int i = 0; i<3; i++){
        number[i] = new floor(Cclass,i+1,Lj,Ls);                        //floor number start from 1
    }
    this->Lj = Lj;
    this->Ls = Ls;
    this->Lt = Lt;
    Hours = N;
}
school::~school(){
    for(int i = 0; i<3;i++){
        delete number[i];
    }
    delete yard;
    delete stair;
    for(int i = 0; i < students.size(); i++){
        delete students.at(i);
    }
    for(int i = 0; i < teach.size(); i++){
        delete teach.at(i);
    }
    teach.clear();
    cout << "School to be destroyed\n";
}
void school::print(){
    cout << "School life consist of:" << endl;
    for(int i = 0; i < 3; i++){
        number[i]->print();
    }
}
void school::studreg(string name){                              
    for(int i = 0; i < 3; i++){                             //for each floor
        if(number[i]->IsFull() == false){               //find the first floor that has available space
            students.push_back(number[i]->assign(name));                //and call the assign function to put student in a class
            break;
        }
    }
}
void school::teachreg(string name){
    for(int i = 0; i < 3; i++){                             //for each floor
        if(number[i]->HasTeacher() == false){           //find the first floor that a class does not have a teacher
            teach.push_back(number[i]->assignteach(name,Lt));             //assign the teacher to a class
            break;
        }
    } 
}
void school::enter(){
    for(int i=0; i < students.size(); i++){                     //places all the students inside school
        students.at(i)->print_name();
        cout  << " has enter school! " << endl;
    }
}
void school::simulation(){
    random_shuffle(students.begin(),students.end());
    random_shuffle(teach.begin(),teach.end());
    enter();                                                //first all students go inside school
    for(int i = 0; i < students.size(); i++){                           //then each one will go in class through schoolyard then stairs then floor,corridor 
        yard->enter(students.at(i));
        stair->enter(yard->exit());
        number[students.at(i)->get_floor()]->enter(stair->exit());
    }
    for(int i = 0; i < teach.size(); i++){
        teach.at(i)->set_inClass();
    }
}

void school::attend(){
    for(int i = 0; i < Hours; i++){                                     //for every hour
        for(int j = 0; j < students.size(); j++){
            students.at(j)->set_tiredness();                            //increase tiredness of student
        }
        for(int j = 0; j < teach.size(); j++){
            teach.at(j)->set_tiredness();                              //increase tiredness of teacher
        }
    }
}