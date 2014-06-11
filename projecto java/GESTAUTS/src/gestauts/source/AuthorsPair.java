/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package gestauts.source;

/**
 *
 * @author Pedro
 */
public class AuthorsPair implements Comparable<AuthorsPair> {
    
 private String author1;
 private String author2;
 private int n_times;
 
 public AuthorsPair(String a1,String a2,int n)
 {
     author1 = a1;
     author2 = a2;
     n_times = n;
 }

    /**
     * @return the auhtor1
     */
    public String getAuthor1() {
        return author1;
    }

    /**
     * @return the author2
     */
    public String getAuthor2() {
        return author2;
    }

    /**
     * @param auhtor1 the auhtor1 to set
     */
    public void setAuthor1(String auhtor1) {
        this.author1 = auhtor1;
    }

    /**
     * @param author2 the author2 to set
     */
    public void setAuthor2(String author2) {
        this.author2 = author2;
    }

    public boolean equals(AuthorsPair ap)
    {
         if (this == ap) return true;
        
        if((ap == null) || this.getClass() != ap.getClass())
            return false;
        
        return (author1.equals(ap.author1) || author1.equals(ap.author2)) && (author2.equals(ap.author1)|| author2.equals(ap.author2));
    }

    public void increment(int i)
    {
        setN_times(getN_times() + i);
    }

    /**
     * @return the n_times
     */
    public int getN_times() {
        return n_times;
    }

    /**
     * @param n_times the n_times to set
     */
    public void setN_times(int n_times) {
        this.n_times = n_times;
    }
    
    
    
  @Override
    public String toString()
    {
        return author1+" - "+author2+" : "+n_times+"\n";
    }
    
    public String key2()
    {
        return author2+" - "+author1;
    }
     public String key1()
    {
        return author1+" - "+author2;
    }

    @Override
    public int compareTo(AuthorsPair o) {
        if((author1.equals(o.author1) || author1.equals(o.author2)) && (author2.equals(o.author1)|| author2.equals(o.author2)))
            return 0;
        else {
                if(n_times>o.getN_times()) return 1;
                else return -1;
        }
    }
}
