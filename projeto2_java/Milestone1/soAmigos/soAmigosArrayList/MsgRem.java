
/**
 * Write a description of class MsgRem here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
import java.util.ArrayList;
import java.util.List;
import java.util.Iterator;

public class MsgRem
{
    //variaveis de instancia
    private long nifRemetente;
    private ArrayList<Mensagem> lstMsg;
    
    //construtores
    public MsgRem() {
        nifRemetente = -1;
        lstMsg = new ArrayList<Mensagem>();
    }
    
    public MsgRem(long nif, String msg) {
        nifRemetente = nif;
        lstMsg = new ArrayList<Mensagem>();
        lstMsg.add(new Mensagem(msg));
    }
    
    public MsgRem(long nif, ArrayList<Mensagem> msgs) {
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
    
    public MsgRem(long nif) {
        nifRemetente = nif;
        lstMsg = new ArrayList<Mensagem>();
    }
    /** Obter nif remetente **/
    public long getRemetente() { return nifRemetente; }
    public void setRemetente(long nif){ nifRemetente=nif;}  
    
    
    /** Obter lista de mensagens **/
    public List<Mensagem> getMensagens() {
        List<Mensagem> res = new ArrayList<Mensagem>();
        for (Mensagem msg : lstMsg)
            res.add(msg.clone());
        return res;
    }
    
    public void inserirMsg(Mensagem msg) {
        if (lstMsg.size() == 20)
            lstMsg.remove(0);
        lstMsg.add(msg.clone());
    }
    
    public void inserirMsg(String msg) {
        if (lstMsg.size() == 20)
            lstMsg.remove(0);
        lstMsg.add(new Mensagem(msg));
    }
    public void inserirListaMsg(List<Mensagem> msgs) {
        for (Mensagem s: msgs) {
            if (lstMsg.size() >=20)
                    lstMsg.remove(0);
            lstMsg.add(s.clone());
        }
    }
    
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
    
    public int numMensagens() { return lstMsg.size(); }
    
    public boolean equals(Object o) {
        if (this == o) return true;
        if ((o == null) || (this.getClass() != o.getClass()))
            return false;
        MsgRem mr = (MsgRem) o;
        
        return this.nifRemetente == mr.getRemetente();
    }
    
    public MsgRem clone() { return new MsgRem(this); }
    
    public String toString() {
        StringBuilder s = new StringBuilder("Remetente: " + this.nifRemetente + "\n");
        s.append("Mensagens: \n");
        for (Mensagem msg : lstMsg)
            s.append(msg.toString() + "\n");
        return s.toString();
    }
}