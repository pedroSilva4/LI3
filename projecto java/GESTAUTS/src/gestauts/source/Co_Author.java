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
public class Co_Author {
    
     private String author;
     private int n_times;
     
     public Co_Author()
     {
        this.author="";
        this.n_times= 0;
     }

    /** Construtor por partes*/
    public Co_Author(String autor, int times)
    {   this.author = autor;
        this.n_times = times;
    }

    /** Construtor por copia*/
    public Co_Author(Co_Author coautor)
    {
        this.author = coautor.author;
        this.n_times = coautor.n_times;
    }



    /**Métodos de instância*/

    public String daAutor() {return this.author;}
    public int daNtimes() {return this.n_times;}

    /**Modificadores**/
    public void setNtimes (int ntimesmod){this.n_times = ntimesmod;}

    /**Cria cópia co_author
     */
     @Override
    public Co_Author clone()
    {
        return new Co_Author(this);
    }

    public boolean equals(Co_Author CA)
    {
        if (this == CA) return true;

            if((CA == null) || this.getClass() != CA.getClass())
                return false;

            return this.n_times == CA.n_times && this.author.equals(CA.author);
    }

   void increment()
   {
       n_times++;
   }

}