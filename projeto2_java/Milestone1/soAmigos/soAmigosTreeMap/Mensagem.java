
/**
 * Write a description of class Mensagem here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
import java.util.GregorianCalendar;

public class Mensagem
{
    //variaveis de instancia
    private String msg;
    private int dia;
    private int mes;
    private int ano;
    
    //construtores
    public Mensagem() {
        GregorianCalendar agora = new GregorianCalendar();
        dia=agora.get(agora.DATE);
        mes=agora.get(agora.MONTH);
        agora.get(agora.YEAR);
        msg="";
    }
    public Mensagem(String msg){
        GregorianCalendar agora = new GregorianCalendar();
        dia=agora.get(agora.DATE);
        mes=agora.get(agora.MONTH);
        agora.get(agora.YEAR);
        this.msg=msg;
    }
    public Mensagem (Mensagem msg){
        GregorianCalendar agora = new GregorianCalendar();
        dia=agora.get(agora.DATE);
        mes=agora.get(agora.MONTH);
        agora.get(agora.YEAR);
        this.msg=msg.getMsg();
    }
   
    //métodos de insancia
    public String getMsg() { return msg; }
    public void setMsg(String msg){ this.msg=msg; }
    
    public String toString() {
        StringBuilder s = new StringBuilder();
        s.append(msg);
        s.append("\nData:");s.append(dia);s.append("-");
        s.append(mes);s.append("-");
        s.append("201");s.append(ano);
        return s.toString();
    } 
    
    public boolean equals(Mensagem m) {
        if (m==null || (m.getClass() != this.getClass())) 
            return false;
        else return (msg.equals(m.getMsg())); 
   }
   
   public Mensagem clone() {return new Mensagem(this);}   
}
