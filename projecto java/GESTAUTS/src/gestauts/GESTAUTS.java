/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package gestauts;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.TreeSet;
import javax.swing.JFileChooser;
import javax.swing.filechooser.FileNameExtensionFilter;
import gestauts.source.Crono;
import gestauts.source.Parser;
import gestauts.source.Pub_File;
import gestauts.source.Publication;
import java.io.FileNotFoundException;
import java.util.logging.Level;
import java.util.logging.Logger;


/**
 *
 * @author Pedro
 */
public class GESTAUTS {

    
    public static boolean isNumeric(String str)  
{  
  try  
  {  
    double d = Double.parseDouble(str);  
  }  
  catch(NumberFormatException nfe)  
  {  
    return false;  
  }  
  return true;  
}
    
    /**
     * @param args the command line arguments
     */
      
         
    public static void main(String[] args) 
    {
        // TODO code application logic here
        Crono timer = new Crono();
         Parser parser = new Parser();
       // BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
	//String s;
        JFileChooser chooser = new JFileChooser();
        chooser.setMultiSelectionEnabled(false);
        FileNameExtensionFilter txtfilter = new FileNameExtensionFilter("txt files (*.txt)", "txt");
        chooser.setFileFilter(txtfilter);
        int option = chooser.showOpenDialog(chooser);
        if (option == JFileChooser.APPROVE_OPTION) {
          File sf = chooser.getSelectedFile();
          
          String filepath  = sf.getAbsolutePath();
          String filename  = sf.getName();
            
       
        try 
        { 
            Pub_File file = new Pub_File(filepath, filename);
            
            timer.start();
           
            parser.parsefile(file);
            System.out.println(timer.print());
            System.out.println(file.printInfo());
        }catch (FileNotFoundException ex2)
        {
            System.out.println("file not found");
        } 
        catch (IOException ex) 
        {
            Logger.getLogger(GESTAUTS.class.getName()).log(Level.SEVERE, null, ex);
        } 
    
        }
    
    
    
    
    
    
    
    
    
    }
}
