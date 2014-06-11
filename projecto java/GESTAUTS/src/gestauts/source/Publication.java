/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package gestauts.source;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.Objects;

/**
 *
 * @author Pedro
 */
public class Publication implements Serializable{
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
    
        @Override
    public boolean equals(Object pub)
    {
        if(this == pub) return true;
            
        if(pub == null || pub.getClass()!= this.getClass()) return false;
        
        Publication p = (Publication) pub;
        
        return this.authors.equals(p.authors) && this.year == p.year;
    }

    @Override
    public int hashCode() {
        int hash = 7;
        hash = 67 * hash + Objects.hashCode(this.authors);
        hash = 67 * hash + this.year;
        return hash;
    }
}
