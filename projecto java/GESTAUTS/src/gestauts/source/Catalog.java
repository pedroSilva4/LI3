/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package gestauts.source;

import java.util.ArrayList;
import java.util.TreeMap;
import java.util.HashSet;
import java.util.ArrayList;
import java.util.TreeSet;

/**
 *
 * @author Pedro
 */
public class Catalog {
 
    private TreeMap<Integer,YearInfo> catalog;
    
    
    public Catalog()
    {   
       catalog = new TreeMap<>();
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
}
