
/**
 * Write a description of class PerfilHashMap here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
import java.util.Iterator;
import java.util.Collections;
import java.util.HashMap;
import java.util.Set;
import java.io.*;
import java.util.*;
import static java.lang.System.out;
import java.util.ArrayList;

public class PerfilHashMap 
{
    //variaveis de instancia
    private Utilizador utiliz;
    private Amigos amgs;
    private HashMapMsg correio;
    
    //construtores
    public PerfilHashMap(Utilizador utiliz) {
        this.utiliz = utiliz.clone();
        amgs = new Amigos();
        correio = new HashMapMsg();
    }
    
    public PerfilHashMap(Utilizador utiliz, Amigos amgs, HashMapMsg cm) {
        this.utiliz = new Utilizador(utiliz);
        this.amgs = new Amigos(amgs);
        correio = new HashMapMsg(cm);
    }
    
    public PerfilHashMap(PerfilHashMap p) {
        utiliz = new Utilizador (p.getUtilizador());
        amgs = new Amigos (p.getAmigos());
        correio = new HashMapMsg(p.getCorreio());
    }
    
    //metodos de instancia
    public Utilizador getUtilizador() { return utiliz.clone(); }
    public Amigos getAmigos() { return amgs.clone(); }
    public HashMapMsg getCorreio() { return correio.clone(); }
    
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
            
        PerfilHashMap p = (PerfilHashMap) o;
        return (this.getUtilizador().equals(p.getUtilizador()));
    }
    
    public PerfilHashMap clone() { return new PerfilHashMap(this); }
}
