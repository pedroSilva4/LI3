/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package gestauts.source;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.TreeMap;
import java.util.TreeSet;

/**
 *
 * @author Pedro
*/

 public class YearInfo implements Serializable{
    
    private TreeMap<String,Info> yearNetwork;
    private int yearTotal;
    
    public YearInfo()
    {
        yearNetwork = new TreeMap<>();
        yearTotal=0;
    }
    
      public int getYearPubs()
    {
        return this.yearTotal;
    }
    
    public void add(Publication pub)
    {
        if(pub.getAuthors().size() == 1)
        {
            if(!yearNetwork.containsKey(pub.getAuthors().get(0)))
            {
                Info info = new Info(pub.getAuthors().get(0), 1, 1,new HashSet<Co_Author>());
                yearNetwork.put(info.daAuthor(), info);
            }
            else
            {
                yearNetwork.get(pub.getAuthors().get(0)).soloInc();
            }
        }
        else
        {
            for(String auth:pub.getAuthors())
            {
                ArrayList<String> co_authors =  new ArrayList<>();
                for(String s: pub.getAuthors())
                {
                    if(!s.equals(auth))
                        co_authors.add(s);
                }
               
                
                 if(!yearNetwork.containsKey(auth))
                    {
                        Info info = new Info(auth, 1, 0,new HashSet<Co_Author>());
                        for(String c: co_authors)
                        {
                            info.addCoAuthor(c);
                        }
                        yearNetwork.put(info.daAuthor(), info);
                    }
                 else
                 {
                    
                     for(String c : co_authors)
                        {
                            yearNetwork.get(auth).addCoAuthor(c);
                        }
                     yearNetwork.get(auth).increment();
                 }
            }
        }
        yearTotal++;
    }
    
    public ArrayList<String> keySet()
    {
        return new ArrayList<>(yearNetwork.keySet());
    }
    public int nPubs(String author)
    {
        return yearNetwork.get(author).daPublications();
    }
    public int uApubs()
    {
        int res = 0;
        for(String s: yearNetwork.keySet())
            res+=yearNetwork.get(s).getSoloPubs();
        
        
        return res;
    }
    
    public void soloPubs(HashSet<String> solo,TreeSet<String> notsolo)
    { 
            
          for(String s: yearNetwork.keySet()){
              if(yearNetwork.get(s).daCoAuthor().isEmpty() && !notsolo.contains(s))
                  solo.add(s);
              else{
                  notsolo.add(s);
                  if(solo.contains(s))
                  solo.remove(s);
                  }
          }
         
    } 
    
    public void notSolo(HashSet<String> notsolo,TreeSet<String> solo)
    { 
            
          for(String s: yearNetwork.keySet()){
              if(yearNetwork.get(s).getSoloPubs() == 0 && !solo.contains(s))
                 notsolo.add(s);
              else{
                   solo.add(s);
                 if(notsolo.contains(s))
                   notsolo.remove(s);
              }
          }
        
    } 
    
    public void totpubs(TreeMap<String,Integer> auths)
    {
        
        for(String s: yearNetwork.keySet())
        {
            if(auths.containsKey(s)) {
                int v = auths.get(s) + yearNetwork.get(s).daPublications();
                
                auths.put(s,v);
            }
            else
            {
                auths.put(s,yearNetwork.get(s).daPublications());
            }
        }
        
    }
    
  
    
    public  HashSet<AuthorsPair> pairs()
    {
        HashSet<AuthorsPair> pairs = new HashSet<>();
       
        
        for(String s : yearNetwork.keySet() )
        {
             
            pairs.addAll(yearNetwork.get(s).generatePairs());
            
            
         }
        return pairs;
    }
    
    public HashSet<String> authorCoauts(String auth)
    {
        if(yearNetwork.containsKey(auth)) return yearNetwork.get(auth).getCoatsNames();
        else return new HashSet<>();
        
    }
    
    public TreeSet<String> pubsCoauth(String auth)
    {
        Integer pubs = 0;
        TreeSet<String>coauts = new TreeSet<>();
        for(String s : yearNetwork.keySet())
        {
            if(s.equals(auth) && !yearNetwork.get(s).daCoAuthor().isEmpty())
            {
                for(Co_Author co : yearNetwork.get(s).daCoAuthor())
                {
                    coauts.add(co.daAutor());
                    pubs+=co.daNtimes();
                }
             
            }        
        }
        coauts.add(pubs.toString());
        return coauts;
    }
    
    public TreeSet<String> pubsAllCoauth(String auth)
    {
        TreeSet<String>coauts = new TreeSet<>();
        for(String s : yearNetwork.keySet())
        {
            if(s.equals(auth) && !yearNetwork.get(s).daCoAuthor().isEmpty())
            {
                for(Co_Author co : yearNetwork.get(s).daCoAuthor())
                {
                    coauts.add(co.daAutor());
                }
            }        
        }
        return coauts;
    }
    
}

