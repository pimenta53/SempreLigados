
/**
 * Write a description of class Amigos here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
import java.util.TreeSet;
import java.util.List;
import java.util.ArrayList;
import java.util.Iterator;

public class Amigos
{
    //variaveis de instancia
    private TreeSet<Long> amigos;
    
    //construtores
    public Amigos() {
        amigos = new TreeSet<Long>();
    }
    
    public Amigos(TreeSet<Long> amg) {
        amigos = new TreeSet<Long>();
        for (Long i: amg)
            amigos.add(i);
    }
    
    public Amigos(Amigos amg) {
        for (Long i: amg.getAmigos())
            if (amigos.contains(i) == false)
                amigos.add(i);
    }
    
    //metodos de instancia
    public List<Long> getAmigos() {
        ArrayList<Long> res = new ArrayList<Long> ();
        for (Long i: amigos)
            res.add(i);
        return res;
    }
    
    public void addAmigo(long nifAmigo) {
        if (amigos.contains(nifAmigo) == false)
            amigos.add(nifAmigo);
    }
    
    public void removerAmigo(long nifAmigo) {
        if (amigos.contains(nifAmigo))
            amigos.remove(nifAmigo);
    }
    
    public int getNumAmigos() { return amigos.size(); }
        
    public Amigos clone(){ return new Amigos(this); }
    
    public String toString() {
        StringBuilder s = new StringBuilder();
        if (amigos.size() > 0) {
            s.append("\nAmigos: \n");
            for (Long i: amigos)
                s.append(i + "\n");
        } 
        else s.append("\nNão possui amigos\n");
        return s.toString();
    }
    
    public boolean equals(Object o)  {
        if (this == o) return true;
        if (o == null || (this.getClass() != o.getClass()))
            return false;
            
        Amigos a = (Amigos) o;
        boolean contem = true;
        Iterator<Long> it = amigos.iterator();
        List<Long> amgObj = a.getAmigos();
        
        while (it.hasNext() && contem)
            if (amgObj.contains(it.next()) == false) 
                contem = false;
        return contem;
                
     }
}
