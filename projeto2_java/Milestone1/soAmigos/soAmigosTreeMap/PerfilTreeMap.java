
/**
 * Write a description of class PerfilHashMap here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
import java.util.Iterator;
import java.util.Collections;
import java.util.TreeMap;
import java.util.Set;
import java.io.*;
import java.util.*;
import static java.lang.System.out;
import java.util.ArrayList;

public class PerfilTreeMap 
{
    //variaveis de instancia
    private Utilizador utiliz;
    private Amigos amgs;
    private TreeMapMsg correio;
    
    //construtores
    public PerfilTreeMap(Utilizador utiliz) {
        this.utiliz = utiliz.clone();
        amgs = new Amigos();
        correio = new TreeMapMsg();
    }
    
    public PerfilTreeMap(Utilizador utiliz, Amigos amgs, TreeMapMsg cm) {
        this.utiliz = new Utilizador(utiliz);
        this.amgs = new Amigos(amgs);
        correio = new TreeMapMsg(cm);
    }
    
    public PerfilTreeMap(PerfilTreeMap p) {
        utiliz = new Utilizador (p.getUtilizador());
        amgs = new Amigos (p.getAmigos());
        correio = new TreeMapMsg(p.getCorreio());
    }
    
    //metodos de instancia
    public Utilizador getUtilizador() { return utiliz.clone(); }
    public Amigos getAmigos() { return amgs.clone(); }
    public TreeMapMsg getCorreio() { return correio.clone(); }
    
    public void setMorada(String nova) { utiliz.setMorada(nova); }
    
    public void addAmigo(long nifAmigo) {
        amgs.addAmigo(nifAmigo);
    }
    
   public void removerAmigo(long nifAmigo) {
        amgs.removerAmigo(nifAmigo);
    }
    
    /*public void removeMsgIndice(Integer nifRem,Mensagem msg) {
        correio.removeMsgRem(nifRem,msg);
    }*/
    

    public void addMensagem(long nifRem, String msg) {
        correio.inserMensagem(nifRem,msg);
    }
        
    public void removeMsgRem(Integer nifRem) {
        correio.removeListaMensagens(nifRem);
    }
    public void removeMsg(String msg) {
        correio.removeMsg(new Mensagem(msg));
    }
    
    public int numMensagens() { return correio.numMensagens(); }
    
    public String toString() {
        StringBuilder s = new StringBuilder();
        s.append(utiliz.toString());
        s.append(amgs.toString());
        s.append(correio.toString() + "\n\n");
        //System.out.println(s.toString());
        return s.toString();
    }
    
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || (this.getClass() != o.getClass()))
            return false;
            
        PerfilTreeMap p = (PerfilTreeMap) o;
        return (this.getUtilizador().equals(p.getUtilizador()));
    }
    
    public PerfilTreeMap clone() { return new PerfilTreeMap(this); }
}
