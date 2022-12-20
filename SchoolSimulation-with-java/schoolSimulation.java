import java.io.*;
import school.*;

public class schoolSimulation {
    static public void main(String[] args)throws Exception{
        
        int Cclass = Integer.parseInt(args[0]);
        int Lj = Integer.parseInt(args[1]);
        int Ls = Integer.parseInt(args[2]);
        int Lt = Integer.parseInt(args[3]);
        int N = Integer.parseInt(args[4]);
        
        school school = new school(Cclass,Lj,Ls,Lt,N);

        File file = new File("teachers.txt");
        BufferedReader br = new BufferedReader(new FileReader(file));
        
        String st; 
        while ((st = br.readLine()) != null) {
            school.teachreg(st); 
        }
        br.close();

        file = new File("students.txt");
        br = new BufferedReader(new FileReader(file));
        while ((st = br.readLine()) != null) {
            school.studreg(st); 
        } 
        br.close();
        
        school.simulation();
        school.attend();
        school.print();
        school.empty();

    }
}
