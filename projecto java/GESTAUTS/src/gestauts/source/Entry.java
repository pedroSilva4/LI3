/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package src.gestauts.source;

import java.util.HashSet;

/**
 *
 * @author Pedro
 */
public class Entry {
    
    
    private String author;
    private int publications;
    private HashSet<Co_Author> co_authors;
    
    //implementaar equals
    //clone
    //getters e setters
    //construtores
    //inc publications
    //add co_author
    
    public Entry()
    {
        this.author ="";
        this.publications= 0;
        this.co_authors = new HashSet();
    }
    
    public Entry(String aut, int pub, HashSet<Co_Author> coaut)
    {
        this.author = aut;
        this.publications = pub;
        this.co_authors = new HashSet<>(coaut);
    }
    
    public Entry(Entry entrada)
    {
        this.author = entrada.author;
        this.publications = entrada.publications;
        this.co_authors = new HashSet<>(entrada.co_authors);
    }
    
    public String daAuthor() {return this.author;}
    public int daPublications() {return this.publications;}
    public HashSet<Co_Author> daCoAuthor() {return this.co_authors;}
    
    public void setAuthor(String autor) {this.author = autor;}
    public void setPublications(int pubs) {this.publications = pubs;}
    public void setco_authors(HashSet<Co_Author> sa) {this.co_authors = sa;}
    
    public Entry clone()
    {
        return new Entry(this);
    }
    
    public boolean equals(Entry entrada)
    {
        if (this == entrada) return true;
        
        if((entrada == null) || this.getClass() != entrada.getClass())
            return false;
        
        return this.author.equals(entrada.author) && this.publications == entrada.publications && this.co_authors.equals(entrada.co_authors);
    }
}

