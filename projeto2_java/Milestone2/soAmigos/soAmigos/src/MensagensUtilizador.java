
import java.io.*;
import java.util.*;

public class MensagensUtilizador implements Serializable
{

    private TreeMap<String,MsgRem> mensagens;

     public MensagensUtilizador() {
        mensagens=new TreeMap<String,MsgRem>();
    }
    public MensagensUtilizador(TreeMap<String,MsgRem> msgs) {
          mensagens= new TreeMap<String,MsgRem> ();
          String nif;
          for(MsgRem msg : msgs.values()){
            nif =msg.getRemetente();
            mensagens.put(nif, msg.clone());
        }
    }

    public MensagensUtilizador(MensagensUtilizador m){
        mensagens= new TreeMap<String,MsgRem> ();
        String nif;
        Collection<MsgRem> val = m.getMensagens();
        for(MsgRem rem : val){
            nif=rem.getRemetente();
            mensagens.put(nif,rem.clone());
        }
    }

/**
 * Metodo que dá o conjunto de todas as MsgRem de um utilizador
 * @return conjunto de MsgRem
 */
    private Collection<MsgRem> getMensagens(){
    Collection<MsgRem> val = mensagens.values();
    return val;
    }

/**
 * Metodo que retorna todos os utilizador que enviaram mensagens para um utilizador
 * @return Set de nif desses utilizadores
 */
    public Set<String> remetentesNif(){
    Set<String> keys = mensagens.keySet();
    return keys;
    }

/**
 * Total de mensagens recebidas
 * @return total de mensagens recebidas
 */
    public int numMensagens(){
        int total=0;
        for(MsgRem rem : mensagens.values()){
            total+=rem.numMensagens();
        }
    return total;
    }

    /**
     * Verifica se existe o remetente
     * @param nif do remetente
     * @return boolen que confirma se existe ou não
     */
    public boolean existeRem(String nif){
        return mensagens.containsKey(nif);
    }

/**
 * Metodo que retorna as mensagens de um determinado utilizador sobre a forma da Class MsgRem que comtem o nif desse utilizador e as suas mensagens
 * @param nif de quem se pretende as mensagens
 * @return class MsgRem
 */
     public MsgRem getListaMensagens(String nif){
         if(!existeRem(nif)) return null;
         return mensagens.get(nif).clone();
     }

/**
 * Adiciona uma Class MsgRem que tem o nif e as mensagens do utilizador correspondete a esse nif
 * @param lm conjunto de mensagens nif(class MsgRem) a adicionar
 */
    public void addListaMensagens(MsgRem lm){
       String nif=lm.getRemetente();
       mensagens.put(nif,lm.clone());
    }

    /**
     * Inserir uma nova mensagem
     * @param nif nif de quem pertence a mensagem
     * @param msg mensagem escrita
     */
    public void inserMensagem(String nif,String msg,String assunto){
        MsgRem rem;
        if(existeRem(nif)) rem=getListaMensagens(nif);
        else rem= new MsgRem(nif);
        rem.inserirMsg(msg,assunto);
        addListaMensagens(rem);
    }

    /**
     * Total de remetentes que já enviaram mensagens
     * @return total de remetentes que já enviaram mensagens
     */
    public int numListaMensagens(){
        return mensagens.size();
    }

    /**
     * Remove todas as mensagens e o registo nas mensagens enviadas ao utilizador pelo utilizador pertencente ao nif passado como paramentro
     * @param nif do utilizador que se pretende apagar o registo de mensagens
     */
    public void removeListaMensagens(String nif){
       mensagens.remove(nif);
    }

    /**
     * Apagar uma mensagem se saber a quem pertence
     * @param msg mensagem que se pretende apagar
     */
    public void removeMsg(Mensagem msg) {
        for(MsgRem r : mensagens.values()){
            r.removerMsg(msg);
        }
    }

    /**
     * Passar toda a informação do objecto para uma unica string
     * @return string om os dados do objecto
     */
    public String toString(){
         StringBuilder s = new StringBuilder("----------- Lista de Mensagens --------\n");
        for(MsgRem msg : mensagens.values()){
            s.append(msg.toString());
        }
         return s.toString();
    }

    /**
     * compara duas class de MensagensUtilizador
     * @param o class que se pretende comparar
     * @return boolean que confirma se são iguais ou não
     */
    public boolean equals(Object o) {
        if (this == o)
            return true;
        if ((o==null) || (o.getClass()!=this.getClass()))
            return false;
        MensagensUtilizador ml = (MensagensUtilizador) o;
        return this.mensagens.equals(ml.getMensagens());
    }

    /**
     * Criar um clone da objecto
     * @return clone do objecto
     */
   public MensagensUtilizador clone(){return  new MensagensUtilizador(this);}
}