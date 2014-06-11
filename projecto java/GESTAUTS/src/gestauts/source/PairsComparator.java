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

public class PairsComparator implements Comparator<AuthorsPair>{

    @Override
    public int compare(AuthorsPair o1, AuthorsPair o2) {
    
       return (-1)*o1.compareTo(o2);
    }

   
}
