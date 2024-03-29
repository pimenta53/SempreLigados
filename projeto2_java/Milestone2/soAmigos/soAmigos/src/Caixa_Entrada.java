/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * Caixa_Entrada.java
 *
 * Created on 9/Jun/2010, 22:08:17
 */

/**
 *
 * @author miguel
 */
public class Caixa_Entrada extends javax.swing.JFrame {

    private SoAmigos amigos;
    private String nifUser;
    private int totalmsg = 0;
    private int i=0;

    /** Creates new form Caixa_Entrada */
    public Caixa_Entrada(SoAmigos amigos, String nifUser) {
        this.amigos=amigos;
        this.nifUser=nifUser;

        initComponents();

        //if (this.amigos.correioRemetentes(this.nifUser)!=null) System.out.println(this.amigos.correioRemetentes(this.nifUser).values().size());
        for (String rem : this.amigos.correioRemetentes(this.nifUser))
            cbremetente.addItem(rem);
                
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
        cbremetente = new javax.swing.JComboBox();
        jScrollPane1 = new javax.swing.JScrollPane();
        textomsg = new javax.swing.JTextArea();
        btseg = new javax.swing.JButton();
        btant = new javax.swing.JButton();
        btApagar = new javax.swing.JButton();
        jButton1 = new javax.swing.JButton();

        setDefaultCloseOperation(javax.swing.WindowConstants.DISPOSE_ON_CLOSE);
        setTitle("Caixa de Entrada");
        setMinimumSize(new java.awt.Dimension(650, 450));
        addWindowListener(new java.awt.event.WindowAdapter() {
            public void windowClosing(java.awt.event.WindowEvent evt) {
                formWindowClosing(evt);
            }
        });
        getContentPane().setLayout(new java.awt.GridBagLayout());

        jLabel1.setText("Remetente:");
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.insets = new java.awt.Insets(0, 0, 0, 2);
        getContentPane().add(jLabel1, gridBagConstraints);

        cbremetente.setPreferredSize(new java.awt.Dimension(70, 25));
        cbremetente.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                cbremetenteActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 3;
        gridBagConstraints.gridy = 0;
        gridBagConstraints.gridwidth = 4;
        gridBagConstraints.ipadx = 100;
        gridBagConstraints.insets = new java.awt.Insets(0, 14, 0, 0);
        getContentPane().add(cbremetente, gridBagConstraints);

        textomsg.setColumns(20);
        textomsg.setEditable(false);
        textomsg.setRows(5);
        textomsg.setPreferredSize(new java.awt.Dimension(360, 360));
        textomsg.setRequestFocusEnabled(false);
        jScrollPane1.setViewportView(textomsg);

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 1;
        gridBagConstraints.gridwidth = 7;
        gridBagConstraints.gridheight = 4;
        gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
        gridBagConstraints.ipadx = 21;
        gridBagConstraints.insets = new java.awt.Insets(2, 0, 0, 2);
        getContentPane().add(jScrollPane1, gridBagConstraints);

        btseg.setText("Seguinte");
        btseg.setEnabled(false);
        btseg.setMaximumSize(new java.awt.Dimension(70, 30));
        btseg.setMinimumSize(new java.awt.Dimension(70, 30));
        btseg.setPreferredSize(new java.awt.Dimension(70, 30));
        btseg.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btsegActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 8;
        gridBagConstraints.gridy = 1;
        gridBagConstraints.fill = java.awt.GridBagConstraints.HORIZONTAL;
        gridBagConstraints.insets = new java.awt.Insets(0, 2, 2, 0);
        getContentPane().add(btseg, gridBagConstraints);

        btant.setText("Anterior");
        btant.setEnabled(false);
        btant.setMaximumSize(new java.awt.Dimension(70, 30));
        btant.setMinimumSize(new java.awt.Dimension(70, 30));
        btant.setPreferredSize(new java.awt.Dimension(70, 30));
        btant.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btantActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 8;
        gridBagConstraints.gridy = 2;
        gridBagConstraints.ipadx = 27;
        gridBagConstraints.insets = new java.awt.Insets(0, 2, 2, 0);
        getContentPane().add(btant, gridBagConstraints);

        btApagar.setText("Apagar");
        btApagar.setEnabled(false);
        btApagar.setMaximumSize(new java.awt.Dimension(70, 30));
        btApagar.setMinimumSize(new java.awt.Dimension(70, 30));
        btApagar.setPreferredSize(new java.awt.Dimension(70, 30));
        btApagar.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btApagarActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 8;
        gridBagConstraints.gridy = 3;
        gridBagConstraints.fill = java.awt.GridBagConstraints.HORIZONTAL;
        gridBagConstraints.insets = new java.awt.Insets(0, 2, 2, 0);
        getContentPane().add(btApagar, gridBagConstraints);

        jButton1.setText("Sair");
        jButton1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton1ActionPerformed(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 8;
        gridBagConstraints.gridy = 4;
        gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
        gridBagConstraints.ipady = 6;
        gridBagConstraints.insets = new java.awt.Insets(0, 1, 2, 0);
        getContentPane().add(jButton1, gridBagConstraints);

        java.awt.Dimension screenSize = java.awt.Toolkit.getDefaultToolkit().getScreenSize();
        setBounds((screenSize.width-650)/2, (screenSize.height-450)/2, 650, 450);
    }// </editor-fold>//GEN-END:initComponents

    private void cbremetenteActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_cbremetenteActionPerformed
        //System.out.println(cbremetente.getSelectedItem());
        this.i = 0;
        this.totalmsg = this.amigos.mensagensRecebidas(nifUser, cbremetente.getSelectedItem().toString()).size()-1;
        if(!cbremetente.getSelectedItem().toString().equals(" ")) textomsg.setText(this.amigos.mensagensRecebidas(nifUser, cbremetente.getSelectedItem().toString()).get(0).toString());
        btant.setEnabled(false);
        if (cbremetente.getSelectedItem().equals(" ") || 0==this.amigos.mensagensRecebidas(nifUser, cbremetente.getSelectedItem().toString()).size()-1) {
            btseg.setEnabled(false);
            btApagar.setEnabled(false);
        }
        if (!cbremetente.getSelectedItem().equals(" ")) btApagar.setEnabled(true);
        if (this.totalmsg>0) btseg.setEnabled(true);

        // TODO add your handling code here:
    }//GEN-LAST:event_cbremetenteActionPerformed

    private void formWindowClosing(java.awt.event.WindowEvent evt) {//GEN-FIRST:event_formWindowClosing
        new Mensagens(amigos, nifUser).setVisible(true);        // TODO add your handling code here:
    }//GEN-LAST:event_formWindowClosing

    private void btsegActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btsegActionPerformed
        i++;
        btant.setEnabled(true);
        if(!cbremetente.getSelectedItem().toString().equals(" ")) textomsg.setText(this.amigos.mensagensRecebidas(nifUser, cbremetente.getSelectedItem().toString()).get(i).toString());
        if (i==totalmsg) btseg.setEnabled(false);
        // TODO add your handling code here:
    }//GEN-LAST:event_btsegActionPerformed

    private void btantActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btantActionPerformed
        i--;
        btseg.setEnabled(true);
        if(!cbremetente.getSelectedItem().toString().equals(" ")) textomsg.setText(this.amigos.mensagensRecebidas(nifUser, cbremetente.getSelectedItem().toString()).get(i).toString());
        if (i==0) btant.setEnabled(false);
        // TODO add your handling code here:
    }//GEN-LAST:event_btantActionPerformed

    private void btApagarActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btApagarActionPerformed
        String nifrem = amigos.getPerfilNome(cbremetente.getSelectedItem().toString()).getUtilizador().getNif();
        amigos.getPerfil(nifUser).removeMsgIndice(nifrem, i);
        this.totalmsg--;
        if (totalmsg==-1) {
            btApagar.setEnabled(false);
            textomsg.setText("");
            cbremetente.removeItem(cbremetente.getSelectedItem().toString());
        }
        else {
        while (i>totalmsg) i--;
        textomsg.setText(this.amigos.mensagensRecebidas(nifUser, cbremetente.getSelectedItem().toString()).get(i).toString());
        }
        // TODO add your handling code here:
    }//GEN-LAST:event_btApagarActionPerformed

    private void jButton1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButton1ActionPerformed
        this.dispose();
        new Mensagens(amigos, nifUser).setVisible(true);
    }//GEN-LAST:event_jButton1ActionPerformed

    /**
    * @param args the command line arguments
    */
    public static void main(String args[]) {
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new Caixa_Entrada(new SoAmigos(), new String()).setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton btApagar;
    private javax.swing.JButton btant;
    private javax.swing.JButton btseg;
    private javax.swing.JComboBox cbremetente;
    private javax.swing.JButton jButton1;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JTextArea textomsg;
    // End of variables declaration//GEN-END:variables

}
