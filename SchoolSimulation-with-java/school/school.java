package school;

import java.util.*;
import java.util.Collections;

//a class to be inherited by students and teachers
class Person{
    String name;
    int ClassroomId;
    int FloorNumber;
    boolean IsInClass;
    int tiredness;
    int degree;
    Person(String name,int ClassroomID,int FloorNumber,int degree){
        this.name = name;
        this.ClassroomId = ClassroomID;
        this.FloorNumber = FloorNumber;
        IsInClass = false;
        tiredness = 0;
        this.degree = degree;
    }
    //print the stats of a person
    public void print(){
        System.out.println(" Name: " + name + " Floor: " + FloorNumber + " Class: " + ClassroomId); 
    }
    //print only the name of person
    public void print_name(){
        System.out.print(name);
    }
    //return the number of the floor
    public int get_floor(){
        return FloorNumber - 1;
    }
    //return the number of classroom
    public int get_classroom(){
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
    //change the status of person. now person is in class
    public void set_inClass(boolean value){
        IsInClass = value;
    }
    //return the tiredness of the person
    public int get_tiredness(){
        return tiredness;
    }
    //changes the tiredness
    public void set_tiredness(int Hours){
        tiredness = degree * Hours;
    }
};
//class the represent a student and is inherited by junior and senior class
class Student extends Person{
    Student(String name,int ClassroomID,int FloorNumber,int degree){
        super(name,ClassroomID,FloorNumber,degree);
    }
};
//represent a junior students
class Junior extends Student{
    Junior(String name,int ClassroomID,int FloorNumber,int Lj){
        super(name,ClassroomID,FloorNumber,Lj);
        System.out.print("A new Junior has been created! ");
        print();
    }
};
//represent a senior student
class Senior extends Student{
    Senior(String name,int ClassroomID,int FloorNumber,int Ls){
        super(name,ClassroomID,FloorNumber,Ls);
        System.out.print("A new Senior has been created! ");
        print();
    }
};
//represent a teacher
class teacher extends Person{
    teacher(String name,int ClassroomID,int FloorNumber,int Lt){
        super(name,ClassroomID,FloorNumber,Lt);
        System.out.print("A new Teacher has been created! ");
        print();
    }
    //a function to check if teacher is in classroom
    public boolean get_inClass(){
        return IsInClass;
    }
};
//represent a space of the school and its inherited by all spaces of school
class Space{
    Vector<Student> students = new Vector<Student>(0);              //a vector to keep students in each space
    Space(){}
    //put a student into the vector and print the name of the student
    void enter(Student student){
        students.add(student);
        students.get(students.size()-1).print_name();
    }
};

class schoolyard extends Space{
    schoolyard(){
        System.out.println("A new Schoolyard has been created!");
    }
    //call Spaces enter and then print a message
    public void enter(Student student){                                  
        super.enter(student);
        System.out.println(" has enter Schoolyard!");
    }
    //removing a student from the vector and print the name and a message
    public Student exit(){
        Student kid = students.get(0);
        students.get(0).print_name();
        System.out.println(" has exit Schoolyard!");
        students.remove(0);
        return kid;
    }
}

class stairs extends Space{
    stairs(){
        System.out.println("A new stair has been created!");
    }
    //call Spaces enter and then print a message
    public void enter(Student student){                    
        super.enter(student);
        System.out.println(" has enter Stairs!");
    }
    //removing a student from the vector and print the name and a message
    public Student exit(){
        Student kid = students.get(0);
            students.get(0).print_name();
            System.out.println(" has exit Stairs!");
            students.remove(0);
            return kid;
    }
}

class floor extends Space{
    private corridor cor;                                           //floor has one corridor
    private classroom[] room = new classroom[6];                    //and 6 classrooms
    private int number;

    floor(int Cclass,int number,int Lj,int Ls){
        System.out.println("A new floor has been created!");
        this.number = number;
        cor = new corridor();
        for(int i = 0; i < 6; i++){
            if(this.number == 1){                                  //the classroom id depents on floor number
                if(i<3){
                    room[i] = new classroom(Cclass,i+1,1,false,Lj);
                }
                else{
                    room[i] = new classroom(Cclass,i+1,1,true,Ls);
                }
            }
            else if(this.number == 2){
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
    //print the name of the student, then a message, and then calls enter-exit of cor and enter of classroom
    public void enter(Student student){
        student.print_name();
        System.out.println(" has enter Floor " + number + " !");
        cor.enter(student);
        room[student.get_classroom()].enter(cor.exit());
    }
    //A function to check if the whole floor has available space
    public boolean IsFull(){
        int counter = 0;
        for(int i = 0; i < 6; i++){                     
                if(room[i].IsFull()==true){
                        counter++;

                }
        }
        if(counter == 6){                       //if all 6 classroom of floor doen't have available  space then the floor is full
                return true;
        }
        return false;
    }    
    //A function to check if the whole floor has available space for a teacher
    public boolean HasTeacher(){
        int counter = 0;
        for(int i = 0; i < 6; i++){
            if(room[i].HasTeacher()==true){
                counter++;
            }
        }
        if(counter == 6){                       //if all 6 classroom of floor have teachers then floor is full of teachers
            return true;
        }
        return false;   
    }
    //assign a student into a classroom
    public Student assign(String name){
        for(int i = 0; i < 6; i++){
            if(room[i].IsFull()==false){                    //find the first class that have available space 
                return room[i].create_Student(name);    //and assign student in it        
            } 
        }
        return null;
    }    
    //assign a teacher into a classroom
    public teacher assignteach(String name,int Lt){
        for(int i = 0; i < 6; i++){
            if(room[i].HasTeacher()==false){               //find the first class that does not have a teacher
                return room[i].create_teacher(name,Lt);    //and assign teacher in it
            } 
        }   
        return null;
    }
    //prints the peoples in each classroom of floor
    public void print(){
        System.out.println("Floor " + number + " contains: ");
        for(int i = 0; i < 6; i++){
            room[i].print();
        }
    }
    //return the id of the first class tht is not empty
    //if all classes are empty return -1
    public int is_class_empty(){
        for(int i =0; i < 6; i++){
            if(room[i].is_empty()==false){
                return i;
            }
        }
        return -1;
    }
    //a student leave his class then enter corridor exits and then exit floor
    public Student exit(int index){
        Student student = room[index].exit();
        cor.enter(student);
        cor.exit();
        student.print_name();
        System.out.println(" Has exit floor " + number + "!");
        return student;
    }
    //all teacher of the floor exit the classroom
    public void teachers_out(){
        for(int i = 0; i < 6; i++){
            room[i].teacher_out();
        }
    }
}

class corridor extends Space{
    corridor(){
        System.out.println("A new corridor has been created!");
    }
    //call Spaces enter and then print a message
    public void enter(Student student){
        super.enter(student);
        System.out.println(" has enter Corridor!");
    }
    //removing a student from the vector and print the name and a message
    public Student exit(){
            Student kid = students.get(0);
            students.get(0).print_name();
            students.remove(0);
            System.out.println(" has exit Corridor!");
            return kid;
    }
}

class classroom extends Space{
    private boolean IsSeniorClass;                              //true if the class is for senior students, false for the oposite
    private int degree;                                         //for senior class degree = LS, for junior degree = Lj
    private teacher teach;                                      //this object will help in create teacher function 
    private Student kid;                                        //this object will help in create Student function
    private int available;                                      //a variable to check if a Student can be assign to the classroom
    private boolean hasteach;                                   //if a teacher has been assing to class then true, else false
    private int id;                                             //number of class
    private int floor_number;                                   //number of floor
    classroom(int Cclass,int id,int floor_number,boolean IsSeniorClass,int degree){
        System.out.println("A new classroom has been created!");
        this.id = id;
        available = Cclass;                                     
        hasteach = false;
        this.floor_number = floor_number;
        this.IsSeniorClass = IsSeniorClass;
        this.degree = degree;
    }
    //calls spaces enter,then changes the status of the students,and then prints a message
    public void enter(Student student){
        super.enter(student);
        students.get(students.size()-1).set_inClass(true);
        System.out.println(" has enter Classroom " + id + " !");
    }
    //A function to check if classroom has available space
    public boolean IsFull(){
        if(available == 0){
            return true;
        }
        return false;
    }
    //check if the class has a teacher
    public boolean HasTeacher(){
        return hasteach;
    }
    //creates a student 
    public Student create_Student(String name){                
        if(IsSeniorClass == false){
            kid = new Junior(name,id,floor_number,degree);
        }
        else{
            kid = new Senior(name,id,floor_number,degree);
        }
        available--;      
        return kid;
    }
    //created a teacher
    public teacher create_teacher(String name,int Lt){
        teach = new teacher(name,id,floor_number,Lt);
        hasteach = true;
        return teach;
    }
    //print people in class
    public void print(){
        System.out.println("People in classroom " + id + " are: ");
        for(int i = 0; i < students.size(); i++){
            System.out.print("-");
            students.get(i).print_name();
            System.out.println(" degree of tiredness: " + students.get(i).get_tiredness());
        }
        if(teach.get_inClass()==true){
            System.out.println("The Teacher is: ");
            System.out.print("-");
            teach.print_name();
            System.out.println(" degree of tiredness: " + teach.get_tiredness());
        }
    }
    //if vector size is 0 the class is emepty
    public boolean is_empty(){
        if(students.size()!=0){
            return false;
        }
        else{
            return true;
        }
    }
    //Remove student from vector and print the stat of student
    //returns the student to be removed
    public Student exit(){
            Student student = students.get(students.size()-1);
            students.get(students.size()-1).print_name();
            System.out.println(" Starts exiting!");
            students.get(students.size()-1).print_name();
            students.get(students.size()-1).set_inClass(false);
            students.remove(students.size()-1);
            System.out.println(" Exits classroom " + id + "!");
            return student;
    }
    //print the name of the teacher and thn change his status to be not in class
    public void teacher_out(){
        teach.print_name();
        System.out.println(" Teacher is out!");
        teach.set_inClass(false);
    }
}

public class school extends Space{
    private Vector<teacher> teach = new Vector<teacher>(0);                     //vector to keep teachers
    private schoolyard yard;
    private stairs stair;
    private floor[] number = new floor[3];
    private int Lj;
    private int Ls;
    private int Lt;
    private int Hours;
    
    public school(int Cclass,int Lj,int Ls,int Lt,int N){
        System.out.println("A new school has been created!");
        this.Lj = Lj;
        this.Ls = Ls;
        this.Lt = Lt;
        Hours = N;
        yard = new schoolyard();
        stair = new stairs();
        for(int i = 0; i < 3; i++){
            number[i] = new floor(Cclass,i+1,this.Lj,this.Ls);
        }
    }
    //A function that assign a Student in a class
    public void studreg(String name){                              
        for(int i = 0; i < 3; i++){                             //for each floor
            if(number[i].IsFull() == false){               //find the first floor that has available space
                students.add(number[i].assign(name));                //and call the assign function to put student in a class
                break;
            }
        }
    }
    //A function that assign a teacher in a class
    public void teachreg(String name){
        for(int i = 0; i < 3; i++){                             //for each floor
            if(number[i].HasTeacher() == false){           //find the first floor that a class does not have a teacher
                teach.add(number[i].assignteach(name,Lt));             //assign the teacher to a class
                break;
            }
        } 
    }
    //run through the vector of students printing the name of all and a message
    private void enter(){
        for(int i=0; i < students.size(); i++){                     //places all the students inside school
            students.get(i).print_name();
            System.out.println(" has enter school! ");
        }
    }
    //calls a fuction to print the students and teachers
    public void print(){
        System.out.println("School life consist of:");
        for(int i = 0; i < 3; i++){
            number[i].print();
        }
    }
    //the fuction that places students and teachers to classroom
    public void simulation(){
        Collections.shuffle(students);
        Collections.shuffle(teach);
        
        enter();                                                //first all students go inside school
        for(int i = 0; i < students.size(); i++){                           //then each one will go in class through schoolyard then stairs then floor,corridor 
            yard.enter(students.get(i));
            stair.enter(yard.exit());
            number[students.get(i).get_floor()].enter(stair.exit());
        }
        for(int i = 0; i < teach.size(); i++){                  //and then for each teacher chabge the status to be inside of classroom
            teach.get(i).set_inClass(true);
        }
    }
    //a fuction the changes the tiredness of students and teachers
    public void attend(){
            for(int i = 0; i < students.size(); i++){    
                students.get(i).set_tiredness(Hours);           
            }
            for(int i = 0; i < teach.size(); i++){
                teach.get(i).set_tiredness(Hours);
            }
    }
    //the function the makes all the students and techers exit the school building
    public void empty(){
        for(int i = 0; i < 3; i++){                                             //for each floor
            while(number[i].is_class_empty()!= -1){                             //while classrooms of floor are not empty
                                                                                     //exit class,then enter corridor,exit corridor and exit floor
                stair.enter(number[i].exit(number[i].is_class_empty()));             //enter stairs
                yard.enter(stair.exit());                                            //exit stairs-enter schoolyard
                yard.exit();                                                         //exit schoolyard
            }
        }
        for(int i = 0; i < 3; i++){                                             //for each floor
            number[i].teachers_out();                                           //teachers of each class of floor exit school
        }
    }

}
