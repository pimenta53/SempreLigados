
/**
 * Write a description of class SoLigados here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
import java.util.ArrayList;
import java.util.List;
import java.util.Iterator;
import java.util.Collections;
import java.io.*;
import java.util.StringTokenizer;
import java.util.GregorianCalendar;
import java.lang.Math;

public class SoLigados
{
    ArrayList<PerfilArrList> listaOrdNif;
    ArrayList<PerfilArrList> listaOrdNome;
   
    public SoLigados() {
        listaOrdNif = new ArrayList<PerfilArrList>();
        listaOrdNome = new ArrayList<PerfilArrList>();
    }
    
     public int compareNif(Object p1, Object p2){
        long p1Age = ((PerfilArrList) p1).getUtilizador().getNif();
        long p2Age = ((PerfilArrList) p2).getUtilizador().getNif();
        if( p1Age > p2Age ) return 1;
        if( p1Age < p2Age ) return -1;
        return 0;
    }
    
    public int compareNome(Object p1, Object p2){
        String p1Name = ( (PerfilArrList) p1 ).getUtilizador().getNome();
        String p2Name = ( (PerfilArrList) p2 ).getUtilizador().getNome();
        return p1Name.compareTo(p2Name);
    }
    
    public boolean inserirListaNif(PerfilArrList p) {
        boolean found = false;
        int index = 0, res = 1;
        Iterator<PerfilArrList> it = listaOrdNif.iterator();
        while(it.hasNext() && !found) {
            if ((res = compareNif(it.next(),p)) >= 0)
                found = true;
            else
                index++;
        }
        if (!found || (found && res!=0)) {
            listaOrdNif.add(index,p);
            return true;
        }
        return false;
    }
    
    public void inserirListaNome(PerfilArrList p) {
        boolean found = false;
        int index = 0;
        Iterator<PerfilArrList> it = listaOrdNome.iterator();
        while(it.hasNext() && !found) {
            if (compareNome(it.next(),p) >= 0) {
                found = true;
            }
            else
                index++;
        }
        listaOrdNome.add(index,p);
    }
                
    public void inserirPerfil(String nome, long nif, String morada) {
        PerfilArrList novo = new PerfilArrList(new Utilizador(nome,nif,morada));
        if (inserirListaNif(novo)) 
            inserirListaNome(novo);
    }
    
    public void removerPerfil(String nifU) {
       long nif = Long.parseLong(nifU);
       PerfilArrList aRemover = new PerfilArrList(new Utilizador("",nif,""));
       if (listaOrdNif.contains(aRemover)) {
            listaOrdNif.remove(aRemover);
            listaOrdNome.remove(aRemover);
        }
    }
    
    public void addAmigo(String nifU, String nifA) {
        long nifUtiliz = Long.parseLong(nifU);
        long nifAmig = Long.parseLong(nifA);
        int index;
        if (listaOrdNif.contains(new PerfilArrList(new Utilizador("",nifAmig,"")))) {
            index = listaOrdNif.indexOf(new PerfilArrList(new Utilizador("",nifUtiliz,"")));
            if (index != -1) {
                PerfilArrList pDest = listaOrdNif.get(index);
                pDest.addAmigo(nifAmig);
            }
        }
    }
    
    public void removerAmigo(String nifU, String nifA) {
        long nifUtiliz = Long.parseLong(nifU);
        long nifAmig = Long.parseLong(nifA);
        int index = listaOrdNif.indexOf(new PerfilArrList(new Utilizador("",nifUtiliz,"")));
            if (index != -1) {
                PerfilArrList pDest = listaOrdNif.get(index);
                pDest.removerAmigo(nifAmig);
            }
    }
        
    public void enviarMensagem(String msg, Long nifDest, Long nifRem) {
        int index = listaOrdNif.indexOf(new PerfilArrList(new Utilizador("",nifDest,"")));
        if (index != -1) {
            PerfilArrList pDest = listaOrdNif.get(index);
            pDest.addMensagem(nifRem,msg);
        }
    }
    
    public void apagarMensagem(String msg, String nifD, String nifR) {
        long nifDest = Long.parseLong(nifD);
        long nifRem = Long.parseLong(nifR);
        int index = listaOrdNif.indexOf(new PerfilArrList(new Utilizador("",nifDest,"")));
        if (index != -1) {
            PerfilArrList pDest = listaOrdNif.get(index);
            pDest.removeMsg(msg);
        }
    }
    
    public PerfilArrList procuraNif(Long nif) {
        int index = listaOrdNif.indexOf(new PerfilArrList(new Utilizador("",nif,"")));
        if (index != -1)
            return listaOrdNif.get(index).clone();
        return null;
    }
    
    public PerfilArrList procuraNome(String nome) {
        PerfilArrList p = new PerfilArrList(new Utilizador(nome,0,"")), pAux;
        boolean found = false;
        Iterator<PerfilArrList> it = listaOrdNome.iterator();
        while(it.hasNext() && !found) {
            pAux = it.next();
            if (compareNome(pAux,p) == 0) {
                found = true;
                return pAux.clone();
            }
        }
        return null;
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
                
            while (ficheiro.ready()) { //enquanto não chegar ao fim do ficheiro
                linha = ficheiro.readLine(); //ler uma linha
                cont++;

                str = new StringTokenizer(linha,";"); 
                nif = Long.parseLong(str.nextToken());
                nome = str.nextToken();
                endereco = str.nextToken();
                inserirPerfil(nome,nif,endereco);
            }
            ficheiro.close();
        } catch (IOException e) {System.out.println(e.getMessage());}
    }
    
    public void imprime() {
        if (listaOrdNif.size() == 0)
            System.out.println("Base de Dados Vazia\n");
        else {
            System.out.println("Base de Dados\n");
            for (PerfilArrList p: listaOrdNif){
                System.out.println(p.toString());
            }
        }
    }
                
    public void carregaBdTime() {
        int i = 0;
        ArrayList<Long> arr = new ArrayList<Long>();
        while (i < 1 )  {
            GregorianCalendar agora = new GregorianCalendar(); 
            carregarBd();
            GregorianCalendar fim = new GregorianCalendar();
            arr.add(fim.getTimeInMillis() - agora.getTimeInMillis());
            listaOrdNif = new ArrayList<PerfilArrList>();
            listaOrdNome = new ArrayList<PerfilArrList>();
            i++;
        }
        i=0;
        for(Long a: arr)
            i+=a;
        System.out.println(i/arr.size());
    }
    

   public void timeProcurasNif() {
        ArrayList<Long> l= new ArrayList<Long>();
        String nif = "9000011000";
        long startTime;
        long n = Long.parseLong(nif);
        int i = 0;
        for (i=0;i<50; i++){ 
            n+=(100);
            startTime = System.nanoTime();
            procuraNif(n);
            l.add(System.nanoTime() - startTime); 
        }
        i=0;
        for(Long a: l)
            i+=a;
        System.out.println(i/l.size());
    }
    
    public List<String> getNomes() {
        ArrayList<String> l= new ArrayList<String>();
        String nif = "9000011000";
        long n = Long.parseLong(nif);
        int i = 0;
        for (i=0;i<40; i++){ 
            n+=(100);
            l.add(procuraNif(n).getUtilizador().getNome());
        }
        return l;
    }
    
   public void timeProcurasNome() {
        List<String> n = getNomes();  
        ArrayList<Long> l= new ArrayList<Long>();
        long startTime, endTime;
        int i = 0;
        String nome;
        for (i=0;i<n.size(); i++){ 
            nome = n.get(i);
            startTime = System.nanoTime();
            procuraNome(nome);
            endTime = System.nanoTime();
            l.add(endTime - startTime); 
        }
        i=0;
        for(Long a: l)
            i+=a;
        System.out.println(i/l.size());
   }
   
    public void timeInserirUser() {
        ArrayList<Long> l= new ArrayList<Long>();
        String nif = "9000011000";
        String nome;
        PerfilArrList p;
        long n = Long.parseLong(nif), startTime, endTime;
        int i = 0;
        for (i=0;i<100; i++){ 
            n+=(100);
            nome = nif + Integer.toString(i%5);
            startTime = System.nanoTime();
            inserirPerfil(nome,n,"");
            endTime = System.nanoTime();
            l.add(endTime - startTime); 
        }
        i=0;
        for(Long a: l)
            i+=a;
        System.out.println(i/l.size());
    }
    
    public void tempoMsg(){
      int i=0;
      long tempo=0;
      long startTime,endTime;
      inserirPerfil("nome1",1,"morada");
      inserirPerfil("nome2",2,"morada");
      while (i < 10000 )  {
            startTime = System.nanoTime();
            enviarMensagem("lol",(new Long(1)),(new Long(2)));
            endTime = System.nanoTime();
            tempo+=(endTime - startTime);
            i++;
      } 
      System.out.println(tempo/10000);
    }    
    
    public void timePercorrer() {
        ArrayList<Long> l= new ArrayList<Long>();
        long startTime, endTime;
        int i = 0;
        for (i=0;i<100; i++){ 
            GregorianCalendar agora = new GregorianCalendar(); 
            imprime();
            GregorianCalendar fim = new GregorianCalendar();
            l.add(fim.getTimeInMillis() - agora.getTimeInMillis());
        }
        i=0;
        for(Long a: l)
            i+=a;
        System.out.println(i/l.size());
    }
}
            
