/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package gestauts;

import gestauts.source.AuthorsPair;
import gestauts.source.Catalog;
import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.TreeSet;
import javax.swing.JFileChooser;
import javax.swing.filechooser.FileNameExtensionFilter;
import gestauts.source.Crono;
import gestauts.source.MostArticlesComp;
import gestauts.source.PairsComparator;
import gestauts.source.Parser;
import gestauts.source.Pub_File;
import gestauts.source.Publication;
import java.io.FileNotFoundException;
import java.util.HashSet;
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
        
              
      
            boolean flag = true;
            
    while(flag){
      try 
        {
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
                        
                        catalog.setFilename(filename);
                        
                        catalog.setFilepath(filepath);
                        
                        timer.start();
                        
                        
                        parser.parsefile(file);
                    
                        for(Publication pub : file.getPublications())
                        {
                            catalog.add(pub.clone());
                        }
                        
                        catalog.setN_pubs(file.getN_pubs());
                        catalog.setN_authors(file.getN_authors());
                        catalog.setSmallest_year(file.getSmallest_year());
                        catalog.setBiggest_year(file.getBiggest_year());
                        
                         System.out.println("\nTIMER : "+timer.print());
                         System.out.println(file.printInfo());
                          flag = false;
                    }   
                     break;
                    
                }
                case "2":
                {
                    chooser.setMultiSelectionEnabled(false);
                    FileNameExtensionFilter txtfilter = new FileNameExtensionFilter("obj files (*.obj)", "obj");
                    chooser.setFileFilter(txtfilter);
                    int option = chooser.showOpenDialog(chooser);
                      if (option == JFileChooser.APPROVE_OPTION) 
                    {
                         File sf = chooser.getSelectedFile();
                         String filepath  = sf.getAbsolutePath();
                        
                         
                        
                         
                         catalog = new Catalog(catalog.load(filepath));
                         flag =false;
                         //file = new Pub_File(catalog.getFilepath(),catalog.getFilename());
                    }
                    break;
                }
                case "3":
                {
                    return;
                }
                case "": break;
                default: 
                {
                    System.out.println("Command does not exits");
                    break;
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
            flag= true;
            System.out.println(printMenu2()+"\n");
            while(flag)
            {   
                try{
                 
                System.out.print("Catalog@Gestauts : ");
                 BufferedReader bufferReader = new BufferedReader(new InputStreamReader(System.in));
                 String command = bufferReader.readLine();
                 String[] tokens = command.split(" ");
                 switch(tokens[0])
                 {
                     case "info":
                     {
                        
                             System.out.println("\n"+catalog.printInfo());
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
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
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
                             if(min < catalog.getSmallest_year() && max > catalog.getBiggest_year() && max < min)
                             {
                                  System.out.println("Invalid Years!");
                                  break;
                             }
                             else
                             {
                                boolean quit = false;
                                 System.out.println(printInterative());
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
                                        case "pairs":
                                        {
                                            if(inTokens.length!= 2 && isNumeric(inTokens[1]))
                                            {   
                                                System.out.println("WRONG ARGUMENTS!");
                                                break;
                                            }
                                            
                                            TreeSet<AuthorsPair> pairs= new TreeSet<>(new PairsComparator());
                                            pairs.addAll(catalog.pairs(min, max));
                                            int i = 0;
                                            int k = Integer.parseInt(inTokens[1]);
                                            for(AuthorsPair p : pairs)
                                            {
                                                if(i==k){break;}
                                                
                                                System.out.println(p.toString());
                                                i++;
                                            }
                                            System.out.println("\n");
                                            break;
                                        }
                                        case "commonCoats":
                                        {
                                            System.out.println();
                                            if(inTokens.length < 2)
                                            {
                                                System.out.println("WRONG ARGUMENTS!");
                                                break;
                                            }
                                               int n =inTokens.length; 
                                               StringBuilder sb = new StringBuilder();
                                               for(int i= 1; i<n ;i++)
                                                {
                                                    if((i+1) != n)
                                                    {
                                                        sb.append(inTokens[i]);
                                                        sb.append(" ");
                                                    }
                                                    else
                                                        sb.append(inTokens[i]);
                                                }
                                               
                                               String[] names = sb.toString().split("\\s*,\\s*");
                                                if(names.length>3){
                                                                    System.out.println("ONLY 3 AUTHORS PERMITED");
                                                                    break;
                                                                  }
                                                if(names.length==1)
                                                {
                                                    TreeSet<String> coats1 = new TreeSet<>(catalog.authorCoauts(min, max, names[0]));
                                                    System.out.println("Co-authors for "+names[0]+" between ["+min+","+max+"]:\n");
                                                    for(String s: coats1)
                                                        System.out.println(s);
                                                    break;
                                                }
                                                if(names.length == 2)
                                                {
                                                    TreeSet<String> coats1 = new TreeSet<>(catalog.authorCoauts(min, max, names[0]));
                                                    TreeSet<String> coats2 = new TreeSet<>(catalog.authorCoauts(min, max, names[1]));
                                                   
                                                    System.out.println("Common Co-authors for "+names[0]+"and "+names[1]+" between ["+min+","+max+"]:\n");
                                                    for(String s : coats1)
                                                        if(coats2.contains(s))
                                                            System.out.println(s);
                                                }
                                                if(names.length == 3)
                                                {
                                                    TreeSet<String> coats1 = new TreeSet<>(catalog.authorCoauts(min, max, names[0]));
                                                    TreeSet<String> coats2 = new TreeSet<>(catalog.authorCoauts(min, max, names[1]));
                                                    TreeSet<String> coats3 = new TreeSet<>(catalog.authorCoauts(min, max, names[2]));

                                                    System.out.println("Common Co-authors for "+names[0]+", "+names[1]+" and "+names[2]+" between ["+min+","+max+"]:\n");
                                                    for(String s : coats1)
                                                        if(coats2.contains(s) && coats3.contains(s))
                                                            System.out.println(s);
                                                }
                                                
                                              System.out.println();
                                             break;
                                               
                                       
                                        }
                                        case "allyears":
                                        {
                                            if(max-min == 0) {System.out.println("\nCannot do this with this interval :["+min+","+max+"]\n");break;}
                                            else
                                            {
                                                TreeSet<String> auths = new TreeSet<>(catalog.getAuthors(min));
                                                ArrayList<TreeSet<String>> arr= new ArrayList<>();
                                                for(int i = min+1;i<=max;i++)
                                                {
                                                    arr.add(catalog.getAuthors(i));
                                                }
                                                TreeSet<String> removals =new TreeSet<>();
                                                
                                                for(String s: auths)
                                                {
                                                 
                                                    for(TreeSet<String> ts : arr)
                                                    {
                                                        if(!ts.contains(s)){ removals.add(s);
                                                                            break;
                                                                           }
                                                    }
                                                    
                                                }
                                                auths.removeAll(removals);
                                                System.out.println("\nAuthors that published every year between ["+min+","+max+"]:\n");
                                                for(String s : auths)
                                                {
                                                    System.out.println(s);
                                                }
                                                break;
                                            }
                                        }
                                        case "quit":
                                        { 
                                            quit = true;
                                            break;
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
                     //acaba aqui as queries inetrativas
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//                     
                     case "duplicates":
                     {
                         if(file!=null){
                             
                         if(file.isParsed())
                         {
                            int allPubs = file.getN_pubs();
                             HashSet<Publication> pubs = new HashSet<>(file.getPublications());
                             
                             System.out.println("Total Lines: "+allPubs);
                             System.out.println("Duplicates : "+(allPubs - pubs.size())+"\n");
                         }
                         else
                         {
                             parser.parsefile(file);
                             int allPubs = file.getN_pubs();
                             HashSet<Publication> pubs = new HashSet<>(file.getPublications());
                             
                             System.out.println("Total Lines: "+allPubs);
                             System.out.println("Duplicates : "+(allPubs - pubs.size())+"\n");
                             
                         }
                         }
                         else
                         {
                             file = new Pub_File(catalog.getFilepath(), catalog.getFilename());
                             parser.parsefile(file);
                             int allPubs = file.getN_pubs();
                             HashSet<Publication> pubs = new HashSet<>(file.getPublications());
                             
                             System.out.println("Total Lines: "+allPubs);
                             System.out.println("Duplicates : "+(allPubs - pubs.size())+"\n");
                           
                         }
                         break;
                     }
                     case "save":
                     {
                         if(tokens.length!=2){System.out.println("WRONG ARGUMENTS"); break;}
                         catalog.save(tokens[1]);
                         break;
                     }
                     case "load":
                     {
                         if(tokens.length!=2){System.out.println("WRONG ARGUMENTS"); break;}
                         Catalog cat = catalog.load(tokens[1]);
                         
                         if(cat!=null)
                         {
                            System.out.println(cat.soloPubs());
                            catalog = new Catalog(cat);
                         }
                         break;
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
       catch (FileNotFoundException ex2)
       {
            System.out.println("file not found");
       } 
       catch (IOException ex) 
       {
            Logger.getLogger(GESTAUTS.class.getName()).log(Level.SEVERE, null, ex);
       } 
    
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
       sb.append("\t\t#==========================GESTAUTS=============================#\n");
       sb.append("\t\t#                          CATALOG                              #\n");
       sb.append("\t\t#                    info -> File Information                   #\n");
       sb.append("\t\t#                   authors ->Number of Authors                 #\n");
       sb.append("\t\t#articles -n number -> n Authors with more than \"number\" pubs   #\n");
       sb.append("\t\t#           articles -u ->Number of articles 1 one Author       #\n");
       sb.append("\t\t#          soloAuthors -> Authors that only published alone     #\n");
       sb.append("\t\t#          notSolo -> Authors that never published alone        #\n");
       sb.append("\t\t#     interative \"year1\" \"year2\" -> Enter interative mode      #\n");
       sb.append("\t\t#     duplicates -> Show number of duplicated lines in file     #\n");
       sb.append("\t\t#                save \"path\" -> saves the catalog              #\n");
       sb.append("\t\t#                load \"path\" ->loads a new Catalog             #\n");
       sb.append("\t\t#                      help - Show Menu                         #\n");
       sb.append("\t\t#                    exit - Close the Program                   #\n");
       sb.append("\t\t#                                                               #\n");
       sb.append("\t\t#===============================================================#\n");
       return sb.toString();
   }
    
   public static String printInterative()
    {
       StringBuilder sb = new  StringBuilder();
       sb.append("\t\t#==================GESTATUS==================#\n");
       sb.append("\t\t#               Interative Mode              #\n");
       sb.append("\t\t#    morePubs x - x Authors with more Pubs   #\n");
       sb.append("\t\t#     pairs x - x pairs with mores Pubs      #\n");
       sb.append("\t\t#  commonCoats a1,a2,a3 - Common Co-authors  #\n");
       sb.append("\t\t#allyears - Authors that published every year#\n");
       sb.append("\t\t#       quit - leave interative mode         #\n");
       sb.append("\t\t#                                            #\n");
       sb.append("\t\t#============================================#\n");
       return sb.toString();
   }
}

