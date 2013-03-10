
import javax.swing.JOptionPane;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * Env_Mensagem.java
 *
 * Created on 8/Jun/2010, 20:49:46
 */

/**
 *
 * @author miguel
 */
public class Env_Mensagem extends javax.swing.JFrame {

    SoAmigos amigos;
    String nifUser;
    String nif;

    /** Creates new form Env_Mensagem */
    public Env_Mensagem(SoAmigos amigos, String nifUser, String nif) {
        this.nifUser=nifUser;
        this.amigos=amigos;
        this.nif=nif;
        initComponents();
        if (!nif.equals("false")) destinotxt.setText(nif);
    }

    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {
        java.awt.GridBagConstraints gridBagConstraints;

        btEnviar = new javax.swing.JButton();
        jScrollPane1 = new javax.swing.JScrollPane();
        txtmensagem = new javax.swing.JTextArea();
        btCancelar = new javax.swing.JButton();
        destinotxt = new javax.swing.JTextField();
        cbopc = new javax.swing.JComboBox();
        txtassunto = new javax.swing.JTextField();
        jLabel1 = new javax.swing.JLabel();

        setDefaultCloseOperation(javax.swing.WindowConstants.DISPOSE_ON_CLOSE);
        setTitle("Enviar Mensagem");
        setMinimumSize(new java.awt.Dimension(650, 450));
        addWindowListener(new java.awt.event.WindowAdapter() {
            public void windowClosing(java.awt.event.WindowEvent evt) {
                formWindowClosing(evt);
            }
        });
        getContentPane().setLayout(new java.awt.GridBagLayout());

        btEnviar.setText("Enviar");
        btEnviar.setMaximumSize(new java.awt.Dimension(70, 30));
        btEnviar.setMinimumSize(new java.awt.Dimension(70, 30));
        btEnviar.setPreferredSize(new java.awt.Dimension(70, 30));
        btEnviar.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btEnviarActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 5;
        gridBagConstraints.gridy = 3;
        gridBagConstraints.ipadx = 26;
        gridBagConstraints.ipady = 8;
        gridBagConstraints.insets = new java.awt.Insets(12, 0, 0, 0);
        getContentPane().add(btEnviar, gridBagConstraints);

        txtmensagem.setColumns(20);
        txtmensagem.setRows(5);
        jScrollPane1.setViewportView(txtmensagem);

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 1;
        gridBagConstraints.gridy = 3;
        gridBagConstraints.gridwidth = 2;
        gridBagConstraints.gridheight = 3;
        gridBagConstraints.fill = java.awt.GridBagConstraints.VERTICAL;
        getContentPane().add(jScrollPane1, gridBagConstraints);

        btCancelar.setText("Sair");
        btCancelar.setMaximumSize(new java.awt.Dimension(70, 30));
        btCancelar.setMinimumSize(new java.awt.Dimension(70, 30));
        btCancelar.setPreferredSize(new java.awt.Dimension(70, 30));
        btCancelar.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btCancelarActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 5;
        gridBagConstraints.gridy = 5;
        gridBagConstraints.fill = java.awt.GridBagConstraints.HORIZONTAL;
        gridBagConstraints.ipady = 5;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.SOUTH;
        gridBagConstraints.insets = new java.awt.Insets(7, 0, 0, 0);
        getContentPane().add(btCancelar, gridBagConstraints);
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 2;
        gridBagConstraints.gridy = 0;
        gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
        getContentPane().add(destinotxt, gridBagConstraints);

        cbopc.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "Nome", "Nif" }));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 1;
        gridBagConstraints.gridy = 0;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.WEST;
        getContentPane().add(cbopc, gridBagConstraints);
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 2;
        gridBagConstraints.gridy = 2;
        gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
        getContentPane().add(txtassunto, gridBagConstraints);

        jLabel1.setText("Assunto:");
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 1;
        gridBagConstraints.gridy = 2;
        gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
        getContentPane().add(jLabel1, gridBagConstraints);

        java.awt.Dimension screenSize = java.awt.Toolkit.getDefaultToolkit().getScreenSize();
        setBounds((screenSize.width-650)/2, (screenSize.height-450)/2, 650, 450);
    }// </editor-fold>//GEN-END:initComponents

    private void btEnviarActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btEnviarActionPerformed
        String amigo = destinotxt.getText();
        String opc = cbopc.getSelectedItem().toString();
        String mensagem = txtmensagem.getText();
        String assunto = txtassunto.getText();

        if (opc.equals("Nif")) {

            while (amigo.length()<10) {
            amigo = ("0" + amigo);
                }

            if (amigos.getPerfil(amigo)!=null) {
                amigos.enviarMensagemNif(mensagem, assunto, amigo, nifUser);
                JOptionPane.showMessageDialog(null,"Mensagem enviada com sucesso!");
                txtmensagem.setText("");
                destinotxt.setText("");
                txtassunto.setText("");
            }
            else JOptionPane.showMessageDialog(null,"Nif inexistente!");
        }

        if (opc.equals("Nome")) {
            if (amigos.getPerfilNome(amigo)!=null) {
                amigos.enviarMensagemNome(mensagem, assunto, amigo, amigos.getPerfil(nifUser).getUtilizador().getNome());
                JOptionPane.showMessageDialog(null,"Mensagem enviada com sucesso!");
                txtmensagem.setText("");
                destinotxt.setText("");
                txtassunto.setText("");
            }
            else JOptionPane.showMessageDialog(null,"Nome enixistente!");
        }
        // TODO add your handling code here:
}//GEN-LAST:event_btEnviarActionPerformed

    private void btCancelarActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btCancelarActionPerformed
        if (nif.equals("false")) new Mensagens(amigos,nifUser).setVisible(true);
        if (!nif.equals("false")) new ver_amigos(amigos,nifUser).setVisible(true);
        this.dispose(); // TODO add your handling code here:
    }//GEN-LAST:event_btCancelarActionPerformed

    private void formWindowClosing(java.awt.event.WindowEvent evt) {//GEN-FIRST:event_formWindowClosing
        if (nif.equals("false")) new Mensagens(amigos,nifUser).setVisible(true);
        if (!nif.equals("false")) new ver_amigos(amigos,nifUser).setVisible(true);        // TODO add your handling code here:
    }//GEN-LAST:event_formWindowClosing

    /**
    * @param args the command line arguments
    */
    public static void main(String args[]) {
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new Env_Mensagem(new SoAmigos(), new String(), new String()).setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton btCancelar;
    private javax.swing.JButton btEnviar;
    private javax.swing.JComboBox cbopc;
    private javax.swing.JTextField destinotxt;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JTextField txtassunto;
    private javax.swing.JTextArea txtmensagem;
    // End of variables declaration//GEN-END:variables

}