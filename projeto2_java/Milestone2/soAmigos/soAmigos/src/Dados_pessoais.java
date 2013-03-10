/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * Dados_pessoais.java
 *
 * Created on 7/Jun/2010, 23:22:40
 */

/**
 *
 * @author miguel
 */
public class Dados_pessoais extends javax.swing.JFrame {

    private SoAmigos amigos;
    private String nifUser;

    /** Creates new form Dados_pessoais */
    public Dados_pessoais(SoAmigos amigos, String nifUser) {
        this.amigos=amigos;
        this.nifUser = nifUser;
        initComponents();
        nometxt.setText(this.amigos.getPerfil(nifUser).getUtilizador().getNome());
        niftxt.setText(this.amigos.getPerfil(nifUser).getUtilizador().getNif());
        moradatxt.setText(this.amigos.getPerfil(nifUser).getUtilizador().getMorada());
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

        jLabel1 = new javax.swing.JLabel();
        jLabel2 = new javax.swing.JLabel();
        jLabel3 = new javax.swing.JLabel();
        nometxt = new javax.swing.JTextField();
        moradatxt = new javax.swing.JTextField();
        niftxt = new javax.swing.JTextField();
        btOK = new javax.swing.JButton();
        btGuardar = new javax.swing.JButton();

        setDefaultCloseOperation(javax.swing.WindowConstants.DISPOSE_ON_CLOSE);
        setTitle("Dados Pessoais");
        setMinimumSize(new java.awt.Dimension(650, 450));
        addWindowListener(new java.awt.event.WindowAdapter() {
            public void windowClosing(java.awt.event.WindowEvent evt) {
                formWindowClosing(evt);
            }
        });
        getContentPane().setLayout(new java.awt.GridBagLayout());

        jLabel1.setText("Nome:");
        jLabel1.setPreferredSize(new java.awt.Dimension(40, 20));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 0;
        gridBagConstraints.ipadx = 30;
        gridBagConstraints.insets = new java.awt.Insets(5, 0, 2, 0);
        getContentPane().add(jLabel1, gridBagConstraints);

        jLabel2.setText("Morada:");
        jLabel2.setPreferredSize(new java.awt.Dimension(40, 20));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 1;
        gridBagConstraints.ipadx = 30;
        gridBagConstraints.insets = new java.awt.Insets(5, 0, 2, 0);
        getContentPane().add(jLabel2, gridBagConstraints);

        jLabel3.setText("NIF:");
        jLabel3.setPreferredSize(new java.awt.Dimension(40, 20));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 2;
        gridBagConstraints.ipadx = 30;
        gridBagConstraints.insets = new java.awt.Insets(5, 0, 2, 0);
        getContentPane().add(jLabel3, gridBagConstraints);

        nometxt.setPreferredSize(new java.awt.Dimension(10, 25));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.ipadx = 150;
        gridBagConstraints.insets = new java.awt.Insets(5, 0, 2, 0);
        getContentPane().add(nometxt, gridBagConstraints);

        moradatxt.setPreferredSize(new java.awt.Dimension(10, 25));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 1;
        gridBagConstraints.gridy = 1;
        gridBagConstraints.ipadx = 150;
        gridBagConstraints.insets = new java.awt.Insets(5, 0, 2, 0);
        getContentPane().add(moradatxt, gridBagConstraints);

        niftxt.setPreferredSize(new java.awt.Dimension(10, 25));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 1;
        gridBagConstraints.gridy = 2;
        gridBagConstraints.ipadx = 150;
        gridBagConstraints.insets = new java.awt.Insets(5, 0, 2, 0);
        getContentPane().add(niftxt, gridBagConstraints);

        btOK.setText("Sair");
        btOK.setPreferredSize(new java.awt.Dimension(70, 30));
        btOK.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btOKActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 2;
        gridBagConstraints.gridy = 1;
        gridBagConstraints.ipadx = 40;
        gridBagConstraints.insets = new java.awt.Insets(5, 10, 2, 0);
        getContentPane().add(btOK, gridBagConstraints);

        btGuardar.setText("Guardar");
        btGuardar.setPreferredSize(new java.awt.Dimension(70, 30));
        btGuardar.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btGuardarActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 2;
        gridBagConstraints.gridy = 0;
        gridBagConstraints.ipadx = 40;
        gridBagConstraints.insets = new java.awt.Insets(5, 10, 0, 0);
        getContentPane().add(btGuardar, gridBagConstraints);

        java.awt.Dimension screenSize = java.awt.Toolkit.getDefaultToolkit().getScreenSize();
        setBounds((screenSize.width-650)/2, (screenSize.height-450)/2, 650, 450);
    }// </editor-fold>//GEN-END:initComponents

    private void btGuardarActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btGuardarActionPerformed
        this.amigos.getPerfil(nifUser).setMorada(moradatxt.getText());// TODO add your handling code here:
    }//GEN-LAST:event_btGuardarActionPerformed

    private void btOKActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btOKActionPerformed
        new Utilizador_menu(amigos,nifUser).setVisible(true);
        this.dispose();// TODO add your handling code here:
    }//GEN-LAST:event_btOKActionPerformed

    private void formWindowClosing(java.awt.event.WindowEvent evt) {//GEN-FIRST:event_formWindowClosing
        new Utilizador_menu(amigos, nifUser).setVisible(true);        // TODO add your handling code here:
    }//GEN-LAST:event_formWindowClosing

    /**
    * @param args the command line arguments
    */
    public static void main(String args[]) {
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new Dados_pessoais(new SoAmigos(), new String()).setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton btGuardar;
    private javax.swing.JButton btOK;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JLabel jLabel3;
    private javax.swing.JTextField moradatxt;
    private javax.swing.JTextField niftxt;
    private javax.swing.JTextField nometxt;
    // End of variables declaration//GEN-END:variables

}
