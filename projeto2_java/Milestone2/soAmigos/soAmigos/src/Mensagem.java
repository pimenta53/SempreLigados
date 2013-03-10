
/**
 * Write a description of class Mensagem here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
import java.io.Serializable;
import java.util.Date;

public class Mensagem implements Serializable
{
    //variaveis de instancia
    private String msg;
    private String assunto;
    private Date data;

    //construtores
    public Mensagem() {
        data=new Date();
        msg="";
    }
    public Mensagem(String msg,String assunto){
        data=new Date();
        this.msg=msg;
        this.assunto=assunto;
    }
    public Mensagem (Mensagem msg){
        data=msg.getData();
        this.msg=msg.getMsg();
        assunto=msg.getAssunto();

    }

    public String getAssunto(){return assunto;}

    public Date getData(){
        return data;
    }
    /**
     * Metodo que retorna o texto da mensagem
     * @return texto da mensagem
     */
    public String getMsg() { return msg; }
    /**
     * Metodo que altera o texto da mensagem
     * @param msg mensagem que se pretende alterar o texto
     */
    public void setMsg(String msg){ this.msg=msg; }

    /**
     * Metodo que transforma a class Mensagem numa String
     * @return String com as informações da mensagem
     */
    public String toString() {
        StringBuilder s = new StringBuilder();
        s.append("Assunto:");s.append(assunto+"\n");
        s.append(msg);
        s.append("\nData:");s.append(data.toString());
        return s.toString();
    }

    /**
     * Metodo que compara duas mensagens
     * @param Mensagem a comparar
     * @return boolean que confirma se é igual ou não
     */
    public boolean equals(Mensagem m) {
        if (m==null || (m.getClass() != this.getClass()))
            return false;
        else return (msg.equals(m.getMsg()));
   }
/**
 * Criar um clone da mensagem
 * @return mensagem clonada
 */
   public Mensagem clone() {return new Mensagem(this);}
}