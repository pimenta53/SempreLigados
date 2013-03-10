/**
 * Write a description of class userHashMap here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
import java.util.List;
import java.util.Iterator;
import java.util.Collections;
import java.util.TreeMap;
import java.util.Set;
import java.io.*;
import java.util.*;
import static java.lang.System.out;

public class TreeMapMsg implements Serializable
{
 
    private TreeMap<Integer,MsgRem> mensagens;
    
     public TreeMapMsg() {
        mensagens=new TreeMap<Integer,MsgRem>();
    }
    public TreeMapMsg(TreeMap<Integer,MsgRem> msgs) {
          mensagens= new TreeMap<Integer,MsgRem> ();
          Long nif;
          for(MsgRem msg : msgs.values()){
            nif =msg.getRemetente();
            mensagens.put(nif.hashCode(), msg.clone());
        }
    }
    
    public TreeMapMsg(TreeMapMsg m){
        mensagens= new TreeMap<Integer,MsgRem> ();
        Long nif;
        Collection<MsgRem> val = m.getMensagens();
        for(MsgRem rem : val){
            nif=rem.getRemetente();
            mensagens.put(nif.hashCode(),rem.clone());
        }
    }
    
    
    private Collection<MsgRem> getMensagens(){
    Collection<MsgRem> val = mensagens.values();
    return val;
    }

    
    private Set<Integer> keys(){
    Set<Integer> keys = mensagens.keySet();
    return keys;
    }
    
   
    public int numMensagens(){
        int total=0;
        for(MsgRem rem : mensagens.values()){
            total+=rem.numMensagens();
        }
    return total;
    }
    
    public boolean existeRem(long index){
        return mensagens.containsKey((new Long(index)).hashCode());
    }
    

     public MsgRem getListaMensagens(long index){ 
         if(!existeRem(index)) return null;
         return mensagens.get((new Long(index)).hashCode()).clone();
     }
    

    public void addListaMensagens(MsgRem lm){
       Long nif=lm.getRemetente();
       mensagens.put(nif.hashCode(),lm.clone());
    }
    public void inserMensagem(long nif,String msg){
        MsgRem rem;
        if(existeRem(nif)) rem=getListaMensagens(nif);
        else rem= new MsgRem(nif);
        rem.inserirMsg(msg);
        addListaMensagens(rem);
    }
   
    public int numListaMensagens(){ 
        return mensagens.size();
    }
    
    public void removeListaMensagens(long index){
       mensagens.remove((new Long(index)).hashCode());
    }
   
    /** Remove Mensagem da Lista **/
    public void removeMsgRem(long nifRem,Mensagem msg) {
       MsgRem rem=getListaMensagens(nifRem);
       if(rem!=null)  rem.removerMsg(msg);
    }
        
    public void removeMsg(Mensagem msg) {
        for(MsgRem r : mensagens.values()){   
            r.removerMsg(msg);
        }
    }
    
    public String toString(){
         StringBuilder s = new StringBuilder("----------- Lista de Mensagens --------\n");
        for(MsgRem msg : mensagens.values()){
            s.append(msg.toString());
        }
         return s.toString();
    }
    
    public boolean equals(Object o) {
        if (this == o)
            return true;
        if ((o==null) || (o.getClass()!=this.getClass()))
            return false;
        TreeMapMsg ml = (TreeMapMsg) o;
        return this.mensagens.equals(ml.getMensagens());
    }
   
   public TreeMapMsg clone(){return  new TreeMapMsg(this);}
}