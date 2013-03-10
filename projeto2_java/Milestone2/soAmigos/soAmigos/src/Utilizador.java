
import java.io.Serializable;


/**
 * Write a description of class Utilizador here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */

public class Utilizador implements Serializable
{
    //variaveis de instancia
    private String nome;
    private String nif;
    private String morada;

    //construtores
    public Utilizador() {
        nome = "";
        nif ="-1";
        morada = "";
    }

    public Utilizador(String nome, String nif, String morada) {
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
    public String getNif() { return nif; }
    public String getMorada() { return morada; }
    public void setNome(String nome) { this.nome = nome; }
    public void setNif(String nif) { this.nif = nif; }
    public void setMorada(String morada) { this.morada = morada; }

    @Override
    public String toString() {
        StringBuilder s = new StringBuilder("---------------Utilizador------------\n");
        s.append("Nome: " + nome + "\n");
        s.append("Nif: " + nif + "\n");
        s.append("Morada: " + morada + "\n");
        return s.toString();
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || (this.getClass() != o.getClass()))
            return false;

        Utilizador ut = (Utilizador) o;
        return this.nif.equals(ut.getNif());
     }


    @Override
     public Utilizador clone() { return new Utilizador(this); }
}