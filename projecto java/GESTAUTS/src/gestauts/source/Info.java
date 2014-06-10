/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package gestauts.source;

import java.util.ArrayList;
import java.util.HashSet;

/**
 *
 * @author Pedro
 */
public class Info {
    
    
    private String author;
    private int publications;
    private int soloPubs;
    private HashSet<Co_Author> co_authors;
    
    //implementaar equals
    //clone
    //getters e setters
    //construtores
    //inc publications
    //add co_author
    
    public Info()
    {
        this.author ="";
        this.publications= 0;
        this.soloPubs = 0 ;
        this.co_authors = new HashSet();
    }
    
    public Info(String aut, int pub,int solo, HashSet<Co_Author> coaut)
    {
        this.author = aut;
        this.publications = pub;
        this.soloPubs = solo;
        this.co_authors = new HashSet<>(coaut);
    }
    
    public Info(Info entrada)
    {
        this.author = entrada.author;
        this.publications = entrada.publications;
        this.soloPubs = entrada.soloPubs;
        this.co_authors = new HashSet<>(entrada.co_authors);
    }
    
    public String daAuthor() {return this.author;}
    public int daPublications() {return this.publications;}
    public HashSet<Co_Author> daCoAuthor() {return new HashSet<>(this.co_authors);}
    
    public void setAuthor(String autor) {this.author = autor;}
    public void setPublications(int pubs) {this.publications = pubs;}
    public void setco_authors(HashSet<Co_Author> sa) {this.co_authors = sa;}
    
    /**
     * @return the soloPubs
     */
    public int getSoloPubs() {
        return soloPubs;
    }

    /**
     * @param soloPubs the soloPubs to set
     */
    public void setSoloPubs(int soloPubs) {
        this.soloPubs = soloPubs;
    }
    public Info clone()
    {
        return new Info(this);
    }
    
    public boolean equals(Info entrada)
    {
        if (this == entrada) return true;
        
        if((entrada == null) || this.getClass() != entrada.getClass())
            return false;
        
        return this.author.equals(entrada.author) && this.publications == entrada.publications &&this.getSoloPubs() == entrada.getSoloPubs() 
                        &&this.co_authors.equals(entrada.co_authors);
    }
    
    void addCoAuthor(String person)
    {
       boolean b= false;
      
            for(Co_Author thing : co_authors)
            {
                 if(thing.daAutor().equals(person))
                {
                    b = true;
                    thing.increment();
                    break;
                }
            }
           if(!b)
           {
               Co_Author newCA = new Co_Author(person,1);
               co_authors.add(newCA);
           }
          
       
    }
    
    void increment()
    {
        this.publications++;
    }
    void soloInc()
    {
        this.publications++;
        this.soloPubs++;
    }

    public HashSet<AuthorsPair> generatePairs()
    {
        HashSet<AuthorsPair> pairs = new HashSet<>();
        
        for(Co_Author co : co_authors ){
            AuthorsPair p = new AuthorsPair(author,co.daAutor(),co.daNtimes());
            pairs.add(p);
        }
    
    return pairs;
    }
    
}

