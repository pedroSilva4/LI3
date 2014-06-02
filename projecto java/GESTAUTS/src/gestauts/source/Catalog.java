/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package gestauts.source;

import java.util.HashMap;
import java.util.TreeSet;

/**
 *
 * @author Pedro
 */
public class Catalog {
 
    private HashMap<Integer,TreeSet<Entry>> catalog;
    
    
    public int key(int year)
    {
        int key =year-1960;
        
        if(key < 0)
            return 0;
        else return key;
        
    }
    
    public void add(String nome)
    {
    }
}
