/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package gestauts.source;

import java.util.Comparator;

/**
 *
 * @author Pedro
 */

public class EntryComparator implements Comparator<Info>{

    @Override
    public int compare(Info o1, Info o2) {
       return o1.daAuthor().compareTo(o2.daAuthor());
    }

   
    
}
