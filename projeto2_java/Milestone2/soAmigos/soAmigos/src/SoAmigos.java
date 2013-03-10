
/**
 * Write a description of class SoAmigos here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
import java.io.*;
import java.util.*;

public class SoAmigos extends Observable implements Serializable{

    TreeMap<String,Perfil> treeNif;
    TreeMap<String,Perfil> treeNome;

       public SoAmigos() {
        treeNif = new TreeMap<String,Perfil>();
        treeNome = new TreeMap<String,Perfil>();
    }

       /**
        * Metodo responsavel por criar um novo utilizador
        * @param nome nome do utilizador
        * @param nif nif do utilizador
        * @param morada morada do utilizador
        */
    public void inserirPerfil(String nome,String nif, String morada) {
        Perfil novo = new Perfil(new Utilizador(nome,nif,morada));
        treeNif.put(nif,novo);
        treeNome.put(nome,novo);
        this.setChanged();
        this.notifyObservers();
    }

    public boolean pertenceAmigosNome(String nome,String nif){
        if(treeNome.containsKey(nome)==false ) return false;
        Perfil p= treeNif.get(nif);
        if(p!=null){
            if(p.pertenceAmigos(treeNome.get(nome).getUtilizador().getNif())) return true;
            else return false;
        }
        else return false;
    }
    
   /**
    * Remover perfil por nif
    * @param nif nif de quem se pretende remover a conta
    */
    public void removerPerfilNif(String nif) {
       Perfil p=treeNif.remove(nif);
       if(p!=null) treeNome.remove((p.getUtilizador().getNome()));
       this.setChanged();
       this.notifyObservers();
    }

    /**
     * Remover perfil por nome
     * @param nome nome de quem se pretende remover a conta
     */
    public void removerPerfilNome(String nome) {
       Perfil p=treeNome.remove(nome);
       if(p!=null) treeNif.remove(p.getUtilizador().getNif());
       this.setChanged();
       this.notifyObservers();
    }

    /**
     * Adicionar um amigo por nif
     * @param nifUtiliz nif a quem se pretende adiionar
     * @param nifAmig nif da pessoa que se pretende adicionar
     */
   public void addAmigoNif(String nifUtiliz,String nifAmig) {
        Perfil utilizador= treeNif.get(nifUtiliz);
        Perfil amigo= treeNif.get(nifAmig);
        if(utilizador!=null && amigo!=null) {
            utilizador.addAmigo(nifAmig);
            amigo.addAmigo(nifUtiliz);
        }
        this.setChanged();
        this.notifyObservers();
    }

   /**
    * Adicionar um amigo por nome
    * @param nomeU nome a quem se pretende adicionar um amigo
    * @param nomeA utilizador que se pretende adicionar como amigo
    */
   public void addAmigoNome(String nomeU,String nomeA) {
        Perfil utilizador= treeNome.get(nomeU);
        Perfil amigo= treeNome.get(nomeA);
        if(utilizador!=null && amigo!=null) {
            utilizador.addAmigo(amigo.getUtilizador().getNif());
            amigo.addAmigo(utilizador.getUtilizador().getNif());
        }
        this.setChanged();
        this.notifyObservers();
    }

    public void removerAmigoNif(String nifUtiliz,String nifAmig) {
        Perfil utilizador= treeNif.get(nifUtiliz);
        Perfil amigo= treeNif.get(nifAmig);
        if (utilizador!=null && amigo!=null) {
                utilizador.removerAmigo(nifAmig);
                amigo.removerAmigo(nifUtiliz);
        }
        this.setChanged();
        this.notifyObservers();
    }

    public void removerAmigoNome(String nomeU,String nomeA) {
        Perfil utilizador= treeNome.get(nomeU);
        Perfil amigo= treeNome.get(nomeA);
        if (utilizador!=null && amigo!=null) {
                amigo.removerAmigo(utilizador.getUtilizador().getNif());
                utilizador.removerAmigo(amigo.getUtilizador().getNif());
        }
        this.setChanged();
        this.notifyObservers();
    }

    public int totalAmigos(String nif){
    int total=0;
    if(treeNif.containsKey(nif)){
        total=treeNif.get(nif).totalAmigos();
    }
    return total;
    }

    public int numUsers(){
        return treeNif.size();
    }

    public void enviarMensagemNif(String msg,String assunto,String nifDest,String nifRem) {
        Perfil dest= treeNif.get(nifDest);
        if (dest!=null) {
           if(treeNif.containsKey(nifRem)) dest.addMensagem(nifRem,msg,assunto);
        }
    }


    public void enviarMensagemNome(String msg,String assunto,String ndest,String nrem) {
        Perfil dest= treeNome.get(ndest);
        Perfil rem= treeNome.get(nrem);
        if (dest!=null && rem!=null) {
            dest.addMensagem(rem.getUtilizador().getNif(),msg,assunto);
        }
    }


    public ArrayList<String> correioRemetentes(String nif){
        ArrayList<String> msgs = new ArrayList<String> ();
        msgs.add(" ");
        Perfil rem;
        if(treeNif.containsKey(nif)){
            Perfil p= treeNif.get(nif);
            for(String s :p.remetentes()){
                rem = treeNif.get(s);
                msgs.add(rem.getUtilizador().getNome());
            }
        }
    return msgs;
    }

   public ArrayList<Mensagem> mensagensRecebidas(String nif,String nome){
        ArrayList<Mensagem> megs = new ArrayList<Mensagem> ();
        Perfil p= treeNome.get(nome);
        String nifR;
        if (treeNif.containsKey(nif) && p!=null){
            nifR=p.getUtilizador().getNif();
            megs.addAll(treeNif.get(nif).getCorreio().getListaMensagens(nifR).getMensagens());
        }
   return megs;
    }

    public TreeMap<String,Perfil> verAmigos(String nif){
        TreeMap<String,Perfil> ams = new TreeMap<String,Perfil> ();
        Perfil amigo;
        if(treeNif.containsKey(nif)){
            Perfil p = treeNif.get(nif).clone();
            for(String s : p.getAmigosP().getAmigos()){
                amigo=treeNif.get(s).clone();
                ams.put(amigo.getUtilizador().getNif(),amigo);
            }
        }
    return ams;
    }

    public boolean login(String nome,String nif){
        Perfil nomeP =treeNif.get(nif);
        Perfil nifP =treeNome.get(nome);
        if(nifP==null || nomeP==null) return false;
    return nomeP.equals(nifP);
    }


    public String toString(){
         StringBuilder s = new StringBuilder("----------- SóAmigos --------\n");
        for(Perfil p : treeNif.values()){
            s.append(p.toString());
        }
        System.out.println(s);
    return s.toString();
    }

    public void guardaSoAmigos(String name) {

        try{
            ObjectOutputStream oout= new ObjectOutputStream(new FileOutputStream(name));
            oout.writeObject(this);
            oout.flush();oout.close();
        }
        catch(IOException e){e.printStackTrace();}

    }
/**
 * Metodo que dá o perfil correspondente ao nome passado como argumento
 * @param nif argumento utilizado como chave de procura na treeNif
 * @return Perfil pretendido caso exista, se não retorna null.
 */
    public Perfil getPerfil(String nif){
         return treeNif.get(nif);
    }
/**
 * Metodo que dá o perfil correspondente ao nome passado como argumento
 * @param nome argumento utilizado como chave de procura na treeNome
 * @return Perfil pretendido caso exista, se não retorna null.
 */
    public Perfil getPerfilNome(String nome){
        return treeNome.get(nome);
    }

/**
 * Metodo que edita os dados de um perfil
 * @param p perfil antigo, que está a ser editado
 * @param nome novo nome para o perfil
 * @param nif novo nif para o perfil
 * @param morada nova morada para o perfil
 */

    public void editPerfil(Perfil p,String nome,String nif,String morada){
    
    Utilizador novoU = new Utilizador(nome,nif,morada);
    Perfil novoP = new Perfil(novoU,p.getAmigosP(),p.getCorreio());
    treeNif.remove(p.getUtilizador().getNif());
    treeNif.put(nif,novoP.clone());

    }

}