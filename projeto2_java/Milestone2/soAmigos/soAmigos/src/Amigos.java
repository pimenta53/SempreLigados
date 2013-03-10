
/**
 * Write a description of class Amigos here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
import java.io.Serializable;
import java.util.TreeSet;
import java.util.List;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.Set;

public class Amigos implements Serializable
{
    //variaveis de instancia
    private TreeSet<String> amigos;

    //construtores
    public Amigos() {
        amigos = new TreeSet<String>();
    }

    public Amigos(TreeSet<String> amg) {
        amigos = new TreeSet<String>();
        for (String i: amg)
            amigos.add(i);
    }

    public Amigos(Amigos amg) {
        amigos = (TreeSet) amg.getAmigos();
    }
    

    //metodos de instancia
    /**
     * Metodo que cria uma lista com todos os nif's 
     * @return lista com todos nif's de amigos
     */
    public Set<String> getAmigos() {
        Set<String> res = new TreeSet<String> ();
        for (String i: amigos)
            res.add(i);
        return res;
    }

    /**
     * Metodo que adiciona um nif ao TreeSet de amigos
     * @param nifAmigo nif que se pretende adicionar
     */
    public void addAmigo(String nifAmigo) {
        if (amigos.contains(nifAmigo) == false)
            amigos.add(nifAmigo);
    }

    /**
     * Metodo que remove um amigo da lista
     * @param nifAmigo nif a remover
     */
    public void removerAmigo(String nifAmigo) {
        if (amigos.contains(nifAmigo))
            amigos.remove(nifAmigo);
    }
    /**
     * Metodo que retorna o total de amigos
     * @return total de amigos
     */
    public int getNumAmigos() { return amigos.size(); }

    /**
     * Metodo que diz se existe ou não um amigo no TreeSet
     * @param nif
     * @return um boolean que confirma se existe amigo ou não
     */
    public boolean existeAmigo(String nif){
        return amigos.contains(nif);
    }

     /**
      * Faz um clone TreeSet de amigos
      * @return
      */
    public Amigos clone(){ return new Amigos(this); }

    /**
     * Transforma a lista de amigos uma String
     * @return String com os amigos
     */
    public String toString() {
        StringBuilder s = new StringBuilder();
        if (amigos.size() > 0) {
            s.append("\nAmigos: \n");
            for (String i: amigos)
                s.append(i + "\n");
        }
        else s.append("\nNão possui amigos\n");
        return s.toString();
    }

       /**
        * Compara duas class's Amigos
        * @param Class que se pretende comparar
        * @return boolean que confirma se são iguais ou não
        */
    public boolean equals(Object o)  {
        if (this == o) return true;
        if (o == null || (this.getClass() != o.getClass()))
            return false;

        Amigos a = (Amigos) o;
        boolean contem = true;
        Iterator<String> it = amigos.iterator();
        Set<String> amgObj = a.getAmigos();

        while (it.hasNext() && contem)
            if (amgObj.contains(it.next()) == false)
                contem = false;
        return contem;

     }
}