/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package gestauts;

import gestauts.source.Catalog;
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
import gestauts.source.MostArticlesComp;
import gestauts.source.Parser;
import gestauts.source.Pub_File;
import gestauts.source.Publication;
import java.io.FileNotFoundException;
import java.util.Iterator;
import java.util.Map;
import java.util.TreeMap;
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
        Crono timer = new Crono();
        Parser parser = new Parser();
        Catalog catalog  =new Catalog();
        JFileChooser chooser = new JFileChooser();
        Pub_File file =null;
        
              
      try 
      {
            boolean flag = true;
            
            while(flag){
                 System.out.println(printMenu1()+"\n");
                System.out.print("@Gestauts: ");
             BufferedReader bufferReader = new BufferedReader(new InputStreamReader(System.in));
             String s = bufferReader.readLine();
            
            switch (s)
            {
                case "1":
                {
                   
                    chooser.setMultiSelectionEnabled(false);
                    FileNameExtensionFilter txtfilter = new FileNameExtensionFilter("txt files (*.txt)", "txt");
                    chooser.setFileFilter(txtfilter);
                    int option = chooser.showOpenDialog(chooser);
                    if (option == JFileChooser.APPROVE_OPTION) 
                    {
                        File sf = chooser.getSelectedFile();
                    
                        String filepath  = sf.getAbsolutePath();
                        String filename  = sf.getName();
                    
                        file = new Pub_File(filepath, filename);
                        timer.start();
                        
                        
                        parser.parsefile(file);
                    
                        for(Publication pub : file.getPublications())
                        {
                            catalog.add(pub.clone());
                        }
                         System.out.println("\nTIMER : "+timer.print());
                         System.out.println(file.printInfo());
                          flag = false;
                    }   
                     break;
                    
                }
                case "2":
                {
                    break;
                }
                case "3":
                {
                    return;
                }
                default: 
                {
                    break;
                }
            }        
            
            }
            flag= true;
            System.out.println(printMenu2()+"\n");
            while(flag)
            {   
                System.out.print("Catalog@Gestauts : ");
                 BufferedReader bufferReader = new BufferedReader(new InputStreamReader(System.in));
                 String command = bufferReader.readLine();
                 String[] tokens = command.split(" ");
                 switch(tokens[0])
                 {
                     case "info":
                     {
                         if(file!= null)
                             System.out.println("\n"+file.printInfo());
                        break;
                     }
                     case "authors":
                     {
                         System.out.println("\nNumber of Authors : "+catalog.totAuthors()+"\n");
                         break;
                     }
                     case "articles":
                     {
                         if(tokens.length < 2)
                         {
                             System.out.println("WRONG ARGUMENTS!\n");
                             break;
                         }
                         if(tokens[1].equals("-u"))
                         {
                            System.out.println("Publication with only one Author : "+ catalog.uApubs()+"\n");
                             break;
                         }
                         if(tokens[1].equals("-n") && tokens.length == 3)
                         {
                             if(isNumeric(tokens[2]))
                             {
                                 int min = Integer.parseInt(tokens[2]);
                                 System.out.println("Number of Authors with more than "+min+": "+catalog.morethan(min));
                                 break;
                             }
                             else
                             {
                                 System.out.println("WRONG ARGUMENTS!\n");
                                 break;
                             }
                         }
                         if(tokens[1].equals("-a") && tokens.length >= 3)
                         {
                             int n = tokens.length;
                             StringBuilder sb = new StringBuilder();
                             for(int i= 2; i<n ;i++)
                             {
                                 if((i+1) != n)
                                 {
                                     sb.append(tokens[i]);
                                     sb.append(" ");
                                 }
                                 else
                                     sb.append(tokens[i]);
                             }
                             
                              System.out.println(sb.toString());
                               break;
                         }
                         
                          System.out.println("WRONG ARGUMENTS!\nFLAG DOES NOT EXIST\n");
                          break;
                         
                     }
                     case "soloAuthors":
                     {
                         System.out.println("Number of Authors that Only Published Alone: "+catalog.soloPubs() +"\n");
                         
                         break;
                     }
                     case "notSolo":
                     {
                         System.out.println("Number of Authors that N1ever Published Alone: "+catalog.notSolo()+"\n");
                         break;
                     }
                     //consultas interativas
                     case "interative":
                     { 
                         if(tokens.length!=3)
                         {
                             
                             System.out.println("WRONG ARGUMENTS!");
                             break;
                         }
                         if(isNumeric(tokens[1]) && isNumeric(tokens[2]))
                         {
                             int min = Integer.parseInt(tokens[1]);
                             int max = Integer.parseInt(tokens[2]);
                             if(min < file.getSmallest_year() && max > file.getBiggest_year())
                             {
                                  System.out.println("Invalid Years!");
                                  break;
                             }
                             else
                             {
                                boolean quit = false;
                                while(!quit){
                                System.out.print("Interative@Gestauts : ");    
                                BufferedReader cmd = new BufferedReader(new InputStreamReader(System.in));
                                String itCmd = cmd.readLine();
                                String[] inTokens = itCmd.split(" ");
                                    switch(inTokens[0])
                                    {
                                        case "morePubs":
                                        {
                                            if(inTokens.length!= 2 && isNumeric(inTokens[1]))
                                            {   
                                                System.out.println("WRONG ARGUMENTS!");
                                                break;
                                            }
                                            
                                            TreeMap<String,Integer> auths = new TreeMap<>(catalog.moretimes(min, max));
                                            TreeSet<Map.Entry<String,Integer>> ordedByvalue = new TreeSet<>(new MostArticlesComp());
                                             int i = 0;
                                             int k = Integer.parseInt(inTokens[1]);
                                             ordedByvalue.addAll(auths.entrySet());
                                            TreeMap<String,Integer> auths2 = new TreeMap<>();
                                             for(Map.Entry<String,Integer> entry : ordedByvalue)
                                             {
                                               if(i == k)
                                               {break;}
                                               
                                               auths2.put(entry.getKey(), entry.getValue());
                                               i++;
                                             }
                                             System.out.println("The "+k+" Authors with more Publications between ["+min+","+max+"]\n");
                                             for(String s: auths2.keySet())
                                             {
                                                 System.out.println(s+" with "+auths2.get(s)+" publications\n");
                                                 
                                             }
                                             break;
                                        }
                                        case "quit":
                                        { 
                                            quit = true;break;
                                        }
                                    }
                                
                                }
                                break;
                                
                             }
                         }
                         else
                         {
                           System.out.println("WRONG ARGUMENTS!");
                           break;   
                         }
                         
                     }
                     case "help":
                     {
                         System.out.println(printMenu2()+"\n");
                         break;
                     }
                     case "exit":
                     {
                         return;
                     }
                     default:
                     {
                         System.out.println("Command "+tokens[0]+" does not exist\n");
                         break;
                     }
                 }
                 
            }
            
            
            
       }
       catch (FileNotFoundException ex2)
       {
            System.out.println("file not found");
       } 
       catch (IOException ex) 
       {
            Logger.getLogger(GESTAUTS.class.getName()).log(Level.SEVERE, null, ex);
       } 
    
    }
    
    
   public static String printMenu1()
   {
       StringBuilder sb = new  StringBuilder();
       sb.append("\t\t#==========GESTATUS==========#\n");
       sb.append("\t\t#                            #\n");
       sb.append("\t\t#    1 - load (.txt) file    #\n");
       sb.append("\t\t#                            #\n");
       sb.append("\t\t#    2 - load (.obj) file    #\n");
       sb.append("\t\t#                            #\n");
       sb.append("\t\t#    3 - exit                #\n");
       sb.append("\t\t#                            #\n");
       sb.append("\t\t#============================#\n");
       return sb.toString();
   }
    
    
   public static String printMenu2()
   {
       StringBuilder sb = new  StringBuilder();
       sb.append("\t\t#==========GESTAUTS==========#\n");
       sb.append("\t\t#          CATALOG           #\n");
       sb.append("\t\t#   info - File Information  #\n");
       sb.append("\t\t#                            #\n");
       sb.append("\t\t#      help - Show Menu      #\n");
       sb.append("\t\t#  exit - Close the Program  #\n");
       sb.append("\t\t#                            #\n");
       sb.append("\t\t#============================#\n");
       return sb.toString();
   }
    
}

