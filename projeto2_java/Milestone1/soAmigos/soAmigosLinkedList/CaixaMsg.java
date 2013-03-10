
/**
 * Write a description of class CaixaMsg here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
import java.util.ArrayList;
import java.util.List;
import java.util.Iterator;

public class CaixaMsg
{
   //variáveis de instancia
   private ArrayList<MsgRem> listRem;
    
    //construtores
    public CaixaMsg() {
        listRem =new ArrayList<MsgRem>();
    }
    
    public CaixaMsg(CaixaMsg cm) {
        this(cm.getMensagens());
    }
    
    public CaixaMsg(List<MsgRem> rmt) {
        this();
        for (MsgRem m : rmt)
            this.listRem.add(m.clone());
    }
       
    /** Devolve lista das mensagens **/
    public List<MsgRem>getMensagens() {
        List<MsgRem> res = new ArrayList<MsgRem>();
        for(MsgRem m: listRem) {
            res.add(m.clone());
        }
        return res;
    }
    
    public MsgRem getRemetente(long nifRem) {
        boolean encontrado = false; 
        MsgRem rem = new MsgRem();
        Iterator<MsgRem> it = listRem.iterator();
        while(it.hasNext() && !encontrado) {
            rem = it.next();
            if (rem.getRemetente() == nifRem) {
                encontrado = true;
                return rem.clone();
            }
        }
        return rem;
    }
    
    public void addRemetente(MsgRem mr) {
        boolean superior = false;
        int index = 0;
        MsgRem aux;
        Iterator<MsgRem> it = listRem.iterator();
        while(it.hasNext() && !superior) {
            aux = it.next();
            if (aux.getRemetente() > mr.getRemetente())
                superior = true;
            else index++;
        }
        listRem.add(index,mr.clone());
    }
     
    
    public boolean existeRem(MsgRem rem) {
        return listRem.contains(rem.clone());
    }
        
    /** Inserir mensagem recebida na caixa de correio **/
    public void inserirNovaMsg(MsgRem mr) {
        int index;
        if (existeRem(mr)) {
            index = listRem.indexOf(mr);
            listRem.get(index).inserirListaMsg(mr.getMensagens());
        }
        else addRemetente(mr);
    }
   
    /** Obter numero de mensagens */
    public int numMensagens() {
        int total = 0;
        for (MsgRem r: listRem)
            total += r.numMensagens();
        return total;
    }
    
    /** Remove Mensagem da Lista **/
    public void removeMsgRem(long nifRem, int indice) {
        Iterator<MsgRem> i = listRem.iterator();
        MsgRem rem;
        boolean found = false;
        while (i.hasNext() && !found) {
            rem = i.next();
            if (rem.getRemetente() == nifRem) {
                rem.removerMsgIndice(indice);
                found = true;
            }
        }
    }
    
    public void removeMsg(Mensagem msg) {
        Iterator<MsgRem> i = listRem.iterator();
        boolean removida = false;
        while (i.hasNext() && !removida) {   
            removida = i.next().removerMsg(msg);
        }
    }
    
    public String toString() {
        StringBuilder s = new StringBuilder();
        if (this.numMensagens() == 0)
            s.append("\nNão recebeu mensagens.");
        else {
            s.append("\n---Mensagens---\n");
            for(MsgRem m : listRem)
                if (m.numMensagens() > 0)
                    s.append(m.toString() + "\n"); 
        }
        return s.toString();
    }  
    
    public CaixaMsg clone() { return new CaixaMsg(this); }
    
    public boolean equals(Object o) {
        if (this == o)
            return true;
        if ((o==null) || (o.getClass()!=this.getClass()))
            return false;
        CaixaMsg ml = (CaixaMsg) o;
        return this.listRem.equals(ml.getMensagens());
    }
    
    /*public List<MsgRem>setMensagens(List<MsgRem> listRem) {
        List<MsgRem> res = new ArrayList<MsgRem>();
        for(MsgRem m: listRem) {
            res.add(m.clone());
        }
        return res;
    }*/
}
