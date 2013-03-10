
/**
 * Write a description of class Mensagem here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class Mensagem
{
    //variaveis de instancia
    private String msg;
    // private Data data;----------------------------------------------Falta a DATA---------------------------
    
    //construtores
    public Mensagem() { msg="";}
    public Mensagem(String msg){this.msg=msg;}
    public Mensagem (Mensagem msg){ this.msg=msg.getMsg();}
   
    //métodos de insancia
    public String getMsg() { return msg; }
    public void setMsg(String msg){ this.msg=msg; }
    
    public String toString() {
        StringBuilder s = new StringBuilder();
        s.append(msg);
        return s.toString();
    } 
    
    public boolean equals(Mensagem m) {
        if (m==null || (m.getClass() != this.getClass())) 
            return false;
        else return (msg.equals(m.getMsg())); 
   }
   
   public Mensagem clone() {return new Mensagem(this);}   
}
