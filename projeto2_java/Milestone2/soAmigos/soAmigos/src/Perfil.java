

/**
 * Write a description of class PerfilHashMap here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
import java.io.*;
import java.util.Set;

public class Perfil implements Serializable {





    //variaveis de instancia
    private Utilizador utiliz;
    private Amigos amgs;
    private MensagensUtilizador correio;
    
    //construtores
     public Perfil() {
        utiliz = new Utilizador();
        amgs = new Amigos();
        correio = new MensagensUtilizador();
    }

    public Perfil(Utilizador utiliz) {
        this.utiliz = utiliz.clone();
        amgs = new Amigos();
        correio = new MensagensUtilizador();
    }
    
    public Perfil(Utilizador utiliz, Amigos amgs, MensagensUtilizador cm) {
        this.utiliz = new Utilizador(utiliz);
        this.amgs = new Amigos(amgs);
        correio = new MensagensUtilizador(cm);
    }
    
    public Perfil(Perfil p) {
        utiliz = new Utilizador (p.getUtilizador());
        amgs = new Amigos (p.getAmigosP());
        correio = new MensagensUtilizador(p.getCorreio());
    }
    
    //metodos de instancia

    /**
     * Retorna um utilizador
     * @return ulizador
     */
    public Utilizador getUtilizador() { return utiliz.clone(); }

    /**
     * Retorna os amigos do perfil
     * @return amigos do perfil
     */
    public Amigos getAmigosP() {
        if(amgs.getNumAmigos()==0) return null;
        else return amgs.clone();
    }

    /**
     * Alterar a morada de um utilizaor
     * @param morada nova morada
     */
    public void setMorada(String morada){
        utiliz.setMorada(morada);
    }


    /**
     * Retorna o correio de mensagens do utilizador
     * @return correio de mensagens do utilizador
     */
    public MensagensUtilizador getCorreio() { return correio.clone(); }

    /**
     * Lista de remetentes que enviaram mensagens para o perfil
     * @return
     */
    public Set<String> remetentes(){
        Set<String> rems = correio.remetentesNif();
    return rems;
    }


    /**
     * Total de amigos
     * @return total de amigos
     */
    public int totalAmigos(){
    return  amgs.getNumAmigos();
    }

    /**
     * Adicionar amigo
     * @param nifAmigo nif do amigo que se pretende adicionar
     */
    public void addAmigo(String nifAmigo) {
        amgs.addAmigo(nifAmigo);
    }

   /**
    * Remover amigo
    * @param nifAmigo nif de quem se pretende remover de amigo
    */
   public void removerAmigo(String nifAmigo) {
        amgs.removerAmigo(nifAmigo);
    }

   /**
    * Verificar se é amigo
    * @param nif nif da pessoa que se pretende verificar se pertence aos amigos
    * @return boolean que confirma se pertence ou não aos amigos
    */
   public boolean pertenceAmigos(String nif){
      return amgs.getAmigos().contains(nif);
   }

    /**
    * Remover mensagem com determinado indice pertencente ao utilizador com o nif passado como parametro
    * @param nif a quem pertence a mensagem que se pretende apagar
    * @param indice indice da mensagem a apagar
    */
   public void removeMsgIndice(String nif,int indice) {
        MsgRem r=correio.getListaMensagens(nif);
        r.removerMsgIndice(indice);
        correio.removeListaMensagens(nif);
        correio.addListaMensagens(r);
    }
    
/**
 * Nova mensagem de um utilizador
 * @param nifRem nif de quem envia a nova mensagem
 * @param msg mensagem que se pretende adicionar ao correio do utilizador
 */
    public void addMensagem(String nifRem, String msg,String assunto) {
        correio.inserMensagem(nifRem,msg,assunto);
    }
    /**
     * Remover todas as mensagens o registo de envio de mensagens de um utilizador
     * @param nifRem nif que se pretende apagar
     */
    public void removeMsgRem(String nifRem) {
        correio.removeListaMensagens(nifRem);
    }

    /**
     * Total de mensagens recebidas
     * @return total de mensagens recebidas
     */
    public int numMensagens() { return correio.numMensagens(); }

    /**
     * Passar o objecto para string
     * @return String com toda a informação do objecto
     */
    public String toString() {
        StringBuilder s = new StringBuilder();
        s.append(utiliz.toString());
        s.append(amgs.toString());
        s.append(correio.toString() + "\n\n");
        return s.toString();
    }

    /**
     * Comapara dois objectos
     * @param o objecto que se pretende comparar com a class Perfil
     * @return boolean que confirma se são iguais ou não
     */
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || (this.getClass() != o.getClass()))
            return false;
            
        Perfil p = (Perfil) o;
        return (this.getUtilizador().equals(p.getUtilizador()));
    }

    /**
     * Criar um clone da class
     * @return clone da class
     */
    public Perfil clone() { return new Perfil(this); }
    }



