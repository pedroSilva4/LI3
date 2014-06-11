/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package gestauts.source;


import java.io.IOException;

/**
 *
 * @author Pedro
 */
public class Parser {
   
   
   public void parsefile(Pub_File file) throws IOException
   {
       if(!file.isParsed()){
           
       String line;
       int i = 0,n_authors = 0,smallYear = 3000, bigYear = 0,year = 0;
       String parts[];
       Publication pub;
                while ((line = file.getFileReader().readLine()) != null) 
                {
                  pub = new Publication();
                
                   parts = line.split(",\\s");
                   for(String stuff : parts)
                   {
                      if(isNumeric(stuff))
                      {
                          year = Integer.parseInt(stuff);
                                if(year>bigYear) bigYear = year;
                                if(year<smallYear) smallYear = year;
                              pub.setYear(year);
                      }
                      else
                      {
                          n_authors++;
                         
                        pub.addAuthor(stuff);
                      }
                   }
                   i++;
                 file.addPublication(pub);
                }
                file.setN_pubs(i);
                file.setN_authors(n_authors);
                file.setBiggest_year(bigYear);
                file.setSmallest_year(smallYear);
                file.setParsed(true);
                
       }
          
   }
   
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
}
