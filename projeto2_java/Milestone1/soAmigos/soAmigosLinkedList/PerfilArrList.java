
/**
 * Write a description of class PerfilArrList here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
import java.util.ArrayList;
import java.util.List;

public class PerfilArrList 
{
    //variaveis de instancia
    private Utilizador utiliz;
    private Amigos amgs;
    private CaixaMsg correio;
    
    //construtores
    public PerfilArrList(Utilizador utiliz) {
        this.utiliz = utiliz.clone();
        amgs = new Amigos();
        correio = new CaixaMsg();
    }
    
    public PerfilArrList(Utilizador utiliz, Amigos amgs, CaixaMsg cm) {
        this.utiliz = new Utilizador(utiliz);
        this.amgs = new Amigos(amgs);
        correio = new CaixaMsg(cm);
    }
    
    public PerfilArrList(PerfilArrList p) {
        utiliz = new Utilizador (p.getUtilizador());
        amgs = new Amigos(p.getAmigos());
        correio = new CaixaMsg(p.getCorreio());
    }
    
    //metodos de instancia
    public Utilizador getUtilizador() { return utiliz.clone(); }
    public List<Long> getAmigos() { return amgs.getAmigos(); }
    public CaixaMsg getCorreio() { return correio.clone(); }
    
    public void setMorada(String nova) { utiliz.setMorada(nova); }
    
    public void addAmigo(long nifAmigo) { 
        amgs.addAmigo(nifAmigo);
    }
    
   public void removerAmigo(long nifAmigo) {
        amgs.removerAmigo(nifAmigo);
    }
    
    public void addMensagem(long nifRem, String msg) {
        correio.inserirNovaMsg(new MsgRem(nifRem,msg));
    }
    
    public void removeMsg(String msg) {
        correio.removeMsg(new Mensagem(msg));
    }
    
    public void removeMsgIndice(long nifRem, int indice) {
        correio.removeMsgRem(nifRem,indice);
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
            
        PerfilArrList p = (PerfilArrList) o;
        return (this.getUtilizador().equals(p.getUtilizador()));
    }
    
    public PerfilArrList clone() { return new PerfilArrList(this); }
}
