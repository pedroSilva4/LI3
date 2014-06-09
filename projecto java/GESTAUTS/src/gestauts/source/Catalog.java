/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package gestauts.source;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.TreeSet;

/**
 *
 * @author Pedro
 */
public class Catalog {
 
    private HashMap<Integer,TreeSet<Entry>> catalog;
    
    
    public Catalog()
    {   
       catalog = new HashMap<>();
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
          TreeSet<Entry> entry = new TreeSet<>(new EntryComparator());
          for(String s:pub.getAuthors())
          {
             ArrayList<String> arr = new ArrayList<>(pub.getAuthors());
             arr.remove(s);
              HashSet<Co_Author> coAT  = new HashSet<>();
             for(String cA :arr)
             {
                 coAT.add(new Co_Author(cA, 1));
             }
             entry.add(new Entry(s, 1, coAT));
          }
          catalog.put(k, entry);
      }
      else
      {
           TreeSet<Entry> replace = new TreeSet<>(catalog.get(k));
          for(String auth: pub.getAuthors())
          {
            boolean b = false; 
            ArrayList<String> coAT  = new ArrayList<>(pub.getAuthors());
            coAT.remove(auth);
            for(Entry ent : replace)
            {
               if(ent.daAuthor().equals(auth))
               {
                   b = true;
                   ent.increment();
                   
                   for(String co : coAT)
                    ent.addCoAuthor(co);
                   
                   break;
               }
               
            }
            
            if(!b)
            {
                
               HashSet<Co_Author> coAT2  = new HashSet<>();
                for(String cA :coAT)
                {
                  coAT2.add(new Co_Author(cA, 1));
                }
               
            
                replace.add(new Entry(auth,1,coAT2));
                catalog.put(k, replace);
            }
          
          }
          
      }
    }
}
