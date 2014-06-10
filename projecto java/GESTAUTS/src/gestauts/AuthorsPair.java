/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package gestauts;

/**
 *
 * @author Pedro
 */
public class AuthorsPair {
    
 private String author1;
 private String author2;
 
 public AuthorsPair(String a1,String a2)
 {
     author1 = a1;
     author2 = a2;
 }

    /**
     * @return the auhtor1
     */
    public String getAuhtor1() {
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
    public void setAuhtor1(String auhtor1) {
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
    }

}
