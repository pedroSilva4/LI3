/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package gestauts.source;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.ArrayList;
import gestauts.source.Publication;

/**
 *
 * @author Pedro
 */
public class Pub_File {
    
     private final BufferedReader fileReader;
   //information of file
  private boolean parsed;
   private String name;
   private int n_pubs;
   private int n_authors;
   private int smallest_year;
   private int biggest_year;
   private ArrayList<Publication> publications;
    
   public Pub_File (String filePath, String fileName) throws FileNotFoundException
   {
       fileReader = new BufferedReader(new FileReader(filePath));
       parsed = false;
       name = fileName;
       n_pubs = 0;
       n_authors = 0;
       smallest_year = 3000;
       biggest_year = 0;
       publications = new ArrayList<>();
   }
   
   public Pub_File(Pub_File pubs)
   {
       fileReader = pubs.getFileReader();
       parsed = pubs.parsed;
       name = pubs.name;
       n_pubs = pubs.n_pubs;
       n_authors = pubs.n_authors;
       smallest_year  =pubs.smallest_year;
       biggest_year = pubs.biggest_year;
       publications = new ArrayList<>(pubs.getPublications());
       
   }
    /**
     * @return the parsed
     */
    public boolean isParsed() {
        return parsed;
    }

    /**
     * @return the name
     */
    public String getName() {
        return name;
    }

    /**
     * @return the n_pubs
     */
    public int getN_pubs() {
        return n_pubs;
    }

    /**
     * @return the n_authors
     */
    public int getN_authors() {
        return n_authors;
    }

    /**
     * @return the smallest_year
     */
    public int getSmallest_year() {
        if(!isParsed())
            return 0;

        return smallest_year;
    }

    /**
     * @return the biggest_year
     */
    public int getBiggest_year() {
        return biggest_year;
    }

    /**
     * @param parsed the parsed to set
     */
    public void setParsed(boolean parsed) {
        this.parsed = parsed;
    }

    /**
     * @param name the name to set
     */
    public void setName(String name) {
        this.name = name;
    }

    /**
     * @param n_pubs the n_pubs to set
     */
    public void setN_pubs(int n_pubs) {
        this.n_pubs = n_pubs;
    }

    /**
     * @param n_authors the n_authors to set
     */
    public void setN_authors(int n_authors) {
        this.n_authors = n_authors;
    }

    /**
     * @param smallest_year the smallest_year to set
     */
    public void setSmallest_year(int smallest_year) {
        this.smallest_year = smallest_year;
    }

    /**
     * @param biggest_year the biggest_year to set
     */
    public void setBiggest_year(int biggest_year) {
        this.biggest_year = biggest_year;
    }

    public ArrayList<Publication> getPublications() {
        ArrayList<Publication> res = new ArrayList<>();
        for(Publication pub: this.publications)
        {
            res.add(pub.clone());
        }
        
        return res;
    }
    
    public void setPublications(ArrayList<Publication> pubs) {
        publications = new ArrayList<>();
        for(Publication pub: pubs)
        {
            this.publications.add(pub.clone());
        }
        
    }
   
   public void addPublication(Publication p)
   {
       publications.add(p.clone());
   }

    /**
     * @return the fileReader
     */
    public BufferedReader getFileReader() {
        return fileReader;
    }
 
    public String printInfo()
    {
        StringBuilder s  =new StringBuilder();
         s = s.append("Name: ").append(this.name);
         s = s.append("\nPublications: ").append(this.n_pubs);
         s = s.append("\nAuthors: ").append(this.n_authors);
         s = s.append("\nTime Interval: [").append(this.smallest_year).append(",")
                                          .append(this.biggest_year).append("]\n");
  
         return s.toString();
    }
}
