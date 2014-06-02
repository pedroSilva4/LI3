/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package gestauts.source;

import java.util.ArrayList;

/**
 *
 * @author Pedro
 */
public class Publication {
        private ArrayList<String> authors;
        private int year;

    
        
        
     public Publication()
     {
         authors = new ArrayList<>();
         year = 0;
     }
    
     public Publication(ArrayList<String> authorsp, int yearp)
     {
         authors = new ArrayList<>(authorsp);
         year = yearp;
     }
     
     
     public Publication(Publication pub)
     {
         authors = new ArrayList<String>(pub.getAuthors());
         year = pub.getYear();
     }  
        
     /**
     * @return the authors
     */
    public ArrayList<String> getAuthors() {
        ArrayList<String> res  = new ArrayList<>();
        int i = 0;
        for(String s : authors)
        {
          res.add(s);
        }
        return res;
    }

    /**
     * @param authors the authors to set
     */
    public void setAuthors(ArrayList<String> authors) {
        this.authors = new ArrayList<>(authors);
    }

    /**
     * @return the year
     */
    public int getYear() {
        return year;
    }

    /**
     * @param year the year to set
     */
    public void setYear(int year) {
        this.year = year;
    }
    
    public void addAuthor(String author)
    {
        authors.add(author);
    }
    
    /**metodos de instancia
     * @return a**/
    
        @Override
    public Publication clone()
    {
        return new Publication(this);
    }
}
