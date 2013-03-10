
/**
 * Write a description of class Utilizador here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
import java.util.ArrayList;

public class Utilizador
{
    //variaveis de instancia  
    private String nome;
    private long nif;
    private String morada;
    
    //construtores
    public Utilizador() {
        nome = "";
        nif = -1;
        morada = "";
    }
    
    public Utilizador(String nome, long nif, String morada) {
        this.nome = nome;
        this.nif = nif;
        this.morada = morada;
    }
    
    public Utilizador(Utilizador ut) {
        nome = ut.getNome();
        nif = ut.getNif();
        morada = ut.getMorada();
    }
    
    public String getNome() { return nome; }
    public long getNif() { return nif; }        
    public String getMorada() { return morada; }
    public void setNome(String nome) { this.nome = nome; }
    public void setNif(long nif) { this.nif = nif; }        
    public void setMorada(String morada) { this.morada = morada; }
    
    public String toString() {
        StringBuilder s = new StringBuilder("---------------Utilizador------------\n");
        s.append("Nome: " + nome + "\n");
        s.append("Nif: " + nif + "\n");
        s.append("Morada: " + morada + "\n");
        return s.toString();
    }
    
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || (this.getClass() != o.getClass()))
            return false;
            
        Utilizador ut = (Utilizador) o;
        return this.nif == ut.getNif();
     }
     
     public Utilizador clone() { return new Utilizador(this); }       
}
