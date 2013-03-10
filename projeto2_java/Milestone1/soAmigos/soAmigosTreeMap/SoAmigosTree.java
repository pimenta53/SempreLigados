
/**
 * Write a description of class SoAmigosHash here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
import java.util.ArrayList;
import java.util.Iterator;
import java.util.Collections;
import java.util.TreeSet;
import java.util.Set;
import java.util.List;
import java.io.*;
import java.util.TreeMap;
import java.util.StringTokenizer;
import java.util.GregorianCalendar;

public class SoAmigosTree{
   
    TreeMap<Integer,PerfilTreeMap> treeNif;
    TreeMap<String,PerfilTreeMap> treeNome;
   
       public SoAmigosTree() {
        treeNif = new TreeMap<Integer,PerfilTreeMap>();
        treeNome = new TreeMap<String,PerfilTreeMap>();
    }
    
    public void inserirPerfil(String nome, long nif, String morada) {
        PerfilTreeMap novo = new PerfilTreeMap(new Utilizador(nome,nif,morada));
        treeNif.put((new Long(nif)).hashCode(),novo);
        treeNome.put(nome,novo);
    }
   
   public void removerPerfil(long nif) {
       PerfilTreeMap p=treeNif.remove((new Long(nif)).hashCode());
       if(p!=null) treeNome.remove((p.getUtilizador().getNome()));
    }
    
    public void removerPerfil(String nome) {
       PerfilTreeMap p=treeNome.remove(nome);
       if(p!=null) treeNif.remove((new Long(p.getUtilizador().getNif())).hashCode());
    }
    
   public void addAmigo(long nifUtiliz,long nifAmig) {
        PerfilTreeMap utilizador= treeNif.get((new Long(nifUtiliz)).hashCode());
        PerfilTreeMap amigo= treeNif.get((new Long(nifAmig)).hashCode());
        if(utilizador!=null && amigo!=null) {
            utilizador.addAmigo(nifAmig);
            amigo.addAmigo(nifUtiliz);
        } 
    }
    
   public void addAmigo(String nomeU,String nomeA) {
        PerfilTreeMap utilizador= treeNome.get(nomeU);
        PerfilTreeMap amigo= treeNome.get(nomeA);
        if(utilizador!=null && amigo!=null) {
            utilizador.addAmigo(amigo.getUtilizador().getNif());
            amigo.addAmigo(utilizador.getUtilizador().getNif());
        } 
    }
    
    public void removerAmigo(long nifUtiliz,long nifAmig) {
        PerfilTreeMap utilizador= treeNif.get((new Long(nifUtiliz)).hashCode());
        PerfilTreeMap amigo= treeNif.get((new Long(nifAmig)).hashCode());
        if (utilizador!=null && amigo!=null) {
                utilizador.removerAmigo(nifAmig);
                amigo.removerAmigo(nifUtiliz);
        }
    }
    
    public void removerAmigo(String nomeU,String nomeA) {
        PerfilTreeMap utilizador= treeNome.get(nomeU);
        PerfilTreeMap amigo= treeNome.get(nomeA);
        if (utilizador!=null && amigo!=null) {
                amigo.removerAmigo(utilizador.getUtilizador().getNif());
                utilizador.removerAmigo(amigo.getUtilizador().getNif());
        }
     }
    
    public int numUsers(){ 
        return treeNif.size();
    }
        
    public void enviarMensagem(String msg, long nifDest, long nifRem) {
        PerfilTreeMap dest= treeNif.get((new Long(nifDest)).hashCode());
        if (dest!=null) {
           if(treeNif.containsKey((new Long(nifRem)).hashCode())) dest.addMensagem(nifRem,msg);
        }
    }
    
    public void enviarMensagem(String msg,String ndest,String nrem) {
        PerfilTreeMap dest= treeNome.get(ndest);
        PerfilTreeMap rem= treeNome.get(nrem);
        if (dest!=null && rem!=null) {
            dest.addMensagem((new Long(rem.getUtilizador().getNif())).hashCode(),msg);
        }
    }
    
    public void apagarMensagem(String msg,long nifDest,long nifRem) {// ainda não acabada
        PerfilTreeMap utilizador= treeNif.get((new Long(nifRem)).hashCode());
        PerfilTreeMap pDest= treeNif.get((new Long(nifDest)).hashCode());
        pDest.removeMsg(msg);
    }
    
    public void verAmigos(long nif){
        PerfilTreeMap p = treeNif.get((new Long(nif)).hashCode()).clone();
        PerfilTreeMap a ;        
    }
    
    
    public String toString(){
         StringBuilder s = new StringBuilder("----------- SóAmigos --------\n");
        for(PerfilTreeMap p : treeNif.values()){
            s.append(p.toString());
        }
        System.out.println(s);
    return s.toString();
    }
    
   
    
     public void carregarBd() {
        try {

            String linha = ""; 
            StringTokenizer str;
            String nifStr, nome, endereco;
            long nif;
            int cont = 0;

            //abrir para leitura o ficheiro clientes.csv
            BufferedReader ficheiro = new BufferedReader(new FileReader("clientes18.csv"));
                
            //ler primeiro
            linha = ficheiro.readLine(); //ler uma linha
            cont++;
            str = new StringTokenizer(linha,";"); 
            nifStr = str.nextToken();
            nifStr=nifStr.substring(1);
            nome = str.nextToken();
            endereco = str.nextToken();
            nif = Long.parseLong(nifStr);
            inserirPerfil(nome,nif,endereco);
                
            while (ficheiro.ready()) { //enquanto não chegar ao fim do ficheiro
                linha = ficheiro.readLine(); //ler uma linha
                cont++;

                str = new StringTokenizer(linha,";"); 
                nif = Long.parseLong(str.nextToken());
                nome = str.nextToken();
                endereco = str.nextToken();
                /*if ((cont%1200) == 0)
                    System.out.println(inserirPerfil(nome,nif,endereco));
                else*/
                    inserirPerfil(nome,nif,endereco);
                
                    
                //System.out.println("Cliente "+ cont + " --> " + "NIF: "+ nif + " NOME: " + nome + " ENDERECO: "+ endereco);
            }
            ficheiro.close();
        } catch (IOException e) {System.out.println(e.getMessage());}
    }

        public void carregaBdTime() {
        int i = 0;
        int tempo=0;
        while (i < 1000 )  {
            GregorianCalendar agora = new GregorianCalendar(); 
            carregarBd();
            GregorianCalendar fim = new GregorianCalendar(); 
            tempo+=(fim.getTimeInMillis() - agora.getTimeInMillis());
            treeNif = new TreeMap<Integer,PerfilTreeMap>();
            treeNome = new TreeMap<String,PerfilTreeMap>();
            i++;
        }
        System.out.println(tempo/1000);
    }
     public void tempoToString(){
         int i=0;
         int tempo=0;
         while (i < 5 )  {
            GregorianCalendar agora = new GregorianCalendar(); 
            System.out.println(treeNif.toString());
            GregorianCalendar fim = new GregorianCalendar();
            tempo+=(fim.getTimeInMillis() - agora.getTimeInMillis());
        i++;
        } 
        System.out.println(tempo/5);
    }
    
    public void tempoPercorrer(){
        int i=0;
         int tempo=0;
         Utilizador u;
        while (i < 50 )  {
            GregorianCalendar agora = new GregorianCalendar(); 
            for(PerfilTreeMap p : treeNif.values()){
                u=p.getUtilizador();}
            GregorianCalendar fim = new GregorianCalendar();
            tempo+=(fim.getTimeInMillis() - agora.getTimeInMillis());
        i++;
        } 
        System.out.println(tempo/50);
    }
    
    public void tempoInserir(){
        int i=0;
        long tempo=0;
        long startTime,endTime;
        long nif=1;
        String nome="andre",morada="rua x";
        while (i < 50 )  {
            startTime = System.nanoTime();
            inserirPerfil(nome,nif,morada);
            endTime = System.nanoTime();
            tempo+=(endTime - startTime);
            i++;
            nif++;
        } 
        System.out.println(tempo/50);
    }
   
    public void tempoMsg(){
      int i=0;
      long tempo=0;
      long startTime,endTime;
      inserirPerfil("nome1",1,"morada");
      inserirPerfil("nome2",2,"morada");
      while (i < 100 )  {
            startTime = System.nanoTime();
            enviarMensagem("lol",1,2);
            endTime = System.nanoTime();
            tempo+=(endTime - startTime);
            i++;
      } 
      System.out.println(tempo/100);
    }    
    
    public void tempoPesquisaNif(){
      int i=0;
      long tempo=0;
      long startTime,endTime;
      String nif = "9000011000";
      long n = Long.parseLong(nif);
      Long nifL =new Long(n);
      PerfilTreeMap p;
      while (i < 10000 )  {
            startTime = System.nanoTime();
            p=treeNif.get(nifL.hashCode());
            endTime = System.nanoTime();
            tempo+=(endTime - startTime);
            i++;
      } 
      System.out.println(tempo/10000);
    }    
    
    public void tempoPesquisaNome(){
      int i=0;
      long tempo=0;
      long startTime,endTime;
      String nome = "Jon Yang";
      PerfilTreeMap p=treeNome.get(nome);
      while (i < 10000 )  {
            startTime = System.nanoTime();
            p=treeNome.get(nome);
            endTime = System.nanoTime();
            tempo+=(endTime - startTime);
            i++;
      } 
      System.out.println(p.toString());
      System.out.println(tempo/10000);
    }    
}
 
    