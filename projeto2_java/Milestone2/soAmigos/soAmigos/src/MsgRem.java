import java.io.*;
/**
 * Write a description of class MsgRem here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
import java.util.ArrayList;
import java.util.List;
import java.util.Iterator;

public class MsgRem implements Serializable
{
    //variaveis de instancia
    private String nifRemetente;
    private ArrayList<Mensagem> lstMsg;

    //construtores
    public MsgRem() {
        nifRemetente ="-1";
        lstMsg = new ArrayList<Mensagem>();
    }

    public MsgRem(String nif, String msg,String assunto) {
        nifRemetente = nif;
        lstMsg = new ArrayList<Mensagem>();
        lstMsg.add(new Mensagem(msg,assunto));
    }

    public MsgRem(String nif, ArrayList<Mensagem> msgs) {
        nifRemetente = nif;
        lstMsg = new ArrayList<Mensagem>();
        for (Mensagem msg: msgs)
            lstMsg.add(msg.clone());
    }

    public MsgRem(MsgRem m) {
        nifRemetente = m.getRemetente();
        lstMsg = new ArrayList<Mensagem>();
        for (Mensagem msg : m.getMensagens())
            lstMsg.add(msg.clone());
   }

    public MsgRem(String nif) {
        nifRemetente = nif;
        lstMsg = new ArrayList<Mensagem>();
    }
    /**
     * Retirar nif do remetente
     * @return nif do remetente
     */
    public String getRemetente() { return nifRemetente; }
    
    /**
     * Alterar o nif do remetente
     * @param nif novo nif
     */
    public void setRemetente(String nif){ nifRemetente=nif;}


    /** Obter lista de mensagens
     * @return lista de mensagens de um remetente
     */
    public List<Mensagem> getMensagens() {
        List<Mensagem> res = new ArrayList<Mensagem>();
        for (Mensagem msg : lstMsg)
            res.add(msg.clone());
        return res;
    }

    /**
     * inserir mensagem nas mensagens do remetente
     * @param msg mensagem a inserir
     */
    public void inserirMsg(Mensagem msg) {
        if (lstMsg.size() == 20)
            lstMsg.remove(0);
        lstMsg.add(msg.clone());
    }
    /**
     * inserir mensagem nas mensagens do remetente
     * @param msg mensagem a inserir como string
     */
    public void inserirMsg(String msg,String assunto) {
        if (lstMsg.size() == 20)
            lstMsg.remove(0);
        lstMsg.add(new Mensagem(msg,assunto));
    }

    /**
     * Inserir varias mensagens na caixa de correio
     * @param msgs mensagens a inserir
     */
    public void inserirListaMsg(List<Mensagem> msgs) {
        for (Mensagem s: msgs) {
            if (lstMsg.size() >=20)
                    lstMsg.remove(0);
            lstMsg.add(s.clone());
        }
    }

    /**
     * Remover mensagem correspondete a um indice das mensagens guardadas
     * @param indice indice que se pretende apagar a mensagem
     */
    public void removerMsgIndice(int indice) {
        if (lstMsg.size() >= indice)
            lstMsg.remove(indice);
    }

    public boolean removerMsg(Mensagem msg) {
        Mensagem aux;
        boolean removed = false;
        Iterator<Mensagem> it = lstMsg.iterator();
        while (it.hasNext() && !removed) {
            aux = it.next();
            if (aux.equals(msg)) {
                lstMsg.remove(aux);
                removed = true;
            }
        }
        return removed;
    }

    /**
     * Total de mensagens do remetente
     * @return numero de mensagens do remetente
     */
    public int numMensagens() { return lstMsg.size(); }

    /**
     * Comparar duas class MsgRem
     * @param MsgRem a ser comparada
     * @return boolean que confirma se são iguais ou não
     */
    public boolean equals(Object o) {
        if (this == o) return true;
        if ((o == null) || (this.getClass() != o.getClass()))
            return false;
        MsgRem mr = (MsgRem) o;

        return this.nifRemetente.equals(mr.getRemetente());
    }
/**
 * Clone da class
 * @return clone da class
 */
    public MsgRem clone() { return new MsgRem(this); }

    /**
     * Transforma a Class MsgRem numa String
     * @return String
     */
    public String toString() {
        StringBuilder s = new StringBuilder("Remetente: " + this.nifRemetente + "\n");
        s.append("Mensagens: \n");
        for (Mensagem msg : lstMsg)
            s.append(msg.toString() + "\n");
        return s.toString();
    }
}