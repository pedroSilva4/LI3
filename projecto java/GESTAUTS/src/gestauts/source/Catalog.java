/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package gestauts.source;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.ObjectStreamException;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.TreeMap;
import java.util.HashSet;
import java.util.ArrayList;
import java.util.TreeSet;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Pedro
 */
public class Catalog implements Serializable{
 
    private TreeMap<Integer,YearInfo> catalog;
    private String filepath;
    private String filename;
    private int n_pubs;
    private int n_authors;
    private int smallest_year;
    private int biggest_year;
    
    public Catalog()
    {   
       catalog = new TreeMap<>();
       filepath = "";
       filename = ""; 
       n_pubs= 0;
       n_authors = 0;
       smallest_year =0;
       biggest_year = 0;
    }
     public Catalog(Catalog cat)
     {
         catalog = new TreeMap<>(cat.catalog);
         filepath = cat.filepath;
         filename = cat.filename;
          n_pubs= cat.n_pubs;
          n_authors = cat.n_authors;
          smallest_year =cat.smallest_year;
          biggest_year = cat.biggest_year;
         
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
        return smallest_year;
    }

    /**
     * @return the biggest_year
     */
    public int getBiggest_year() {
        return biggest_year;
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
    

     /**
     * @return the filepath
     */
    public String getFilepath() {
        return filepath;
    }

    /**
     * @return the filename
     */
    public String getFilename() {
        return filename;
    }

    /**
     * @param filepath the filepath to set
     */
    public void setFilepath(String filepath) {
        this.filepath = filepath;
    }

    /**
     * @param filename the filename to set
     */
    public void setFilename(String filename) {
        this.filename = filename;
    }
    
    
    public int key(int year)
    {
        int key =year-1960;
        
        if(key < 0)
            return 0;
        else return key;
        
    }
    
    public void add(Publication pub)
    {
      int k = key(pub.getYear());
      
      if(!catalog.containsKey(k))
      {
         YearInfo yearInfo  =new YearInfo();
         yearInfo.add(pub);
         catalog.put(k,yearInfo);
      }
      else
      {
          catalog.get(k).add(pub);   
      }
    }
    
    
    //metodos das queries estaticas
    
    public int totAuthors()
    {
        int res =0;
        HashSet<String> auths = new HashSet<>();
        for(int k : catalog.keySet())
        {
            auths.addAll(catalog.get(k).keySet());
        }
        
        res = auths.size();
        return res;
    }
    
    public int nPubs(String auth)
    {
        int res = 0;
        
        for(int i: catalog.keySet())
        {
            res += catalog.get(i).nPubs(auth);
        }
        
        return res;
    }
    
    public int uApubs()
    {
        int res =0;
        for(int i: catalog.keySet())
            res+=catalog.get(i).uApubs();
        
        return res;
    }
    
    public int soloPubs()
    {
        
         HashSet<String> solo = new HashSet<>();
         TreeSet<String> notsolo = new TreeSet<>();
        for(int i: catalog.keySet())
            catalog.get(i).soloPubs(solo,notsolo);
        
        
       
        return solo.size();
    }
    public int notSolo()
    {
      
        HashSet<String> notsolo = new HashSet<>();
        TreeSet<String> solo = new TreeSet<>();
        for(int i: catalog.keySet())
         
                  catalog.get(i).notSolo(notsolo,solo);
        
        return notsolo.size();
    }
    
    public int morethan(int min)
    {
        int res = 0;
        TreeMap<String,Integer> auths = new TreeMap<>();
        for(int i:catalog.keySet())
            catalog.get(i).totpubs(auths);
        
        for(String s: auths.keySet())
            if(auths.get(s)>min)
                res++;
        return res;
    }
    public TreeMap<String,Integer> moretimes(int min,int max)
     {
          TreeMap<String,Integer> auths = new TreeMap<>();
        for(int i= key(min);catalog.containsKey(i)&& i<= key(max);i++)
        {
            catalog.get(i).totpubs(auths);
        }
        
        
        
        return auths;
            
     }
     
    private void addToArrayPair(TreeMap<String,AuthorsPair> pairs, AuthorsPair p)
    {
        boolean added = false;
       
            if(pairs.containsKey(p.key1())){
                added = true;
                pairs.get(p.key1()).increment(p.getN_times());
            }
           
        if(!added)
        {
             if(pairs.containsKey(p.key2())){
                added = true;
                pairs.get(p.key2()).increment(p.getN_times());
             }
            if(!added)
            pairs.put(p.key1(),p);
        }
    }
    
    public TreeSet<AuthorsPair> pairs(int min,int max)
    {
        TreeMap<String,AuthorsPair> pairs = new TreeMap<>();
        
        for(int i= key(min);catalog.containsKey(i)&& i<= key(max);i++)
        {
            ArrayList<AuthorsPair> aux = new ArrayList<>(catalog.get(i).pairs());
           
            for(AuthorsPair p : aux)
            {
                addToArrayPair(pairs, p);
            }
        }
        return new TreeSet<>(pairs.values());
    }
    public TreeSet<String> authorCoauts(int min, int max,String auth)
    {
        TreeSet<String> coats = new TreeSet<>();
        
        for(int i= key(min);catalog.containsKey(i)&& i<= key(max);i++)
        {
            coats.addAll(catalog.get(i).authorCoauts(auth));
        }  
        
        return coats;
    }
    
    public TreeSet<String> getAuthors(int year)
    {
        int i = key(year);
        
        return new TreeSet<>(catalog.get(i).keySet());
        
    }
    
    public void save(String path)
    {
           FileOutputStream fos;
           ObjectOutputStream oos;
        try {
            fos = new FileOutputStream(path);
            oos = new ObjectOutputStream(fos);
            
            oos.writeObject(getN_pubs());
            oos.writeObject(getN_authors());
            oos.writeObject(getSmallest_year());
            oos.writeObject(getBiggest_year());
            oos.writeObject(catalog);
            oos.writeObject(filepath);
            oos.writeObject(filename);
            
            
            oos.close();
            
            
             
        } catch (FileNotFoundException ex) {
            Logger.getLogger(Catalog.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IOException ex) {
            Logger.getLogger(Catalog.class.getName()).log(Level.SEVERE, null, ex);
        }
     
    }
    
    public Catalog load(String path)
    {
           FileInputStream fis;
           ObjectInputStream ois;
           Catalog cat = new Catalog();
        try {
           
              fis = new FileInputStream(path);
              ois = new ObjectInputStream(fis);

                    cat.setN_pubs((int)ois.readObject());
                    cat.setN_authors((int)ois.readObject());
                    cat.setSmallest_year((int)ois.readObject()) ;
                    cat.setBiggest_year((int)ois.readObject()) ;
                    cat.catalog = new TreeMap<>((TreeMap<Integer,YearInfo>)ois.readObject());
                    cat.filepath = (String) ois.readObject();
                    cat.filename = (String) ois.readObject();
                    
      

                 ois.close();
             return cat;
        } catch (FileNotFoundException ex) {
            Logger.getLogger(Catalog.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IOException ex) {
            Logger.getLogger(Catalog.class.getName()).log(Level.SEVERE, null, ex);
        } catch (ClassNotFoundException ex) {
            Logger.getLogger(Catalog.class.getName()).log(Level.SEVERE, null, ex);
        }
        return null;
    }

     public String printInfo()
    {
        StringBuilder s  =new StringBuilder();
         s = s.append("Name: ").append(this.filename);
         s = s.append("\nPublications: ").append(this.n_pubs);
         s = s.append("\nAuthors: ").append(this.n_authors);
         s = s.append("\nTime Interval: [").append(this.smallest_year).append(",")
                                          .append(this.biggest_year).append("]\n");
  
         return s.toString();
    }
    
     public ArrayList<String> yearTable()
    {
        ArrayList<String> yearPub = new ArrayList<>();

        for (int i : catalog.keySet())
        {
            yearPub.add("Year: " + (i + 1960) + "\tNumber of publications: " + catalog.get(i).getYearPubs());
        }
        return yearPub;
    }
    
    public TreeSet<String> byLetter(char letter)
    {
        TreeSet<String> names = new TreeSet<>();
        TreeMap<String, Integer> auths = new TreeMap<>();
        for (int i : catalog.keySet())
        {
            catalog.get(i).totpubs(auths);
        }
        for(String s : auths.keySet())
        {
            if(s.charAt(0) == letter)
            {
                names.add(s);
            }
        }
        return names;
    }
    
    public TreeSet<String> coAuths(int yea, String name)
    {
        TreeSet<String> coauths = catalog.get(key(yea)).pubsCoauth(name);
        //coauths = catalog.get(key(yea)).pubsCoauth(name);
        return coauths;
        
    }
    
    public TreeSet<String> allCoauths(String name)
    {
        TreeSet<String> coauths = new TreeSet<>();
        for(int i : catalog.keySet())
        {
                coauths.addAll(catalog.get(i).pubsAllCoauth(name));
        }
        return coauths;
    }
}