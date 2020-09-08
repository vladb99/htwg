package aufgabe_9;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.Locale;

public class Taschenrechner extends JFrame implements ActionListener, ItemListener {

    JTextField op1TextField;
    JTextField op2TextField;
    JTextField resTextField;

    JRadioButton degBtn;
    JRadioButton radBtn;
    JCheckBox colorBtn;

    JButton btnPlus;
    JButton btnMal;
    JButton btnMin;
    JButton btnDiv;
    JButton btnSin;
    JButton btnCos;
    JButton btnPot;
    JButton btnLog2;
    JButton btnClr;

    boolean isRad;
    boolean isDark;

    public Taschenrechner() {
        this.setTitle("Taschenrechner");
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setPreferredSize(new Dimension(500, 275));

        // Labels and text fields
        JLabel op1Label = new JLabel("Operand x");
        JLabel op2Label = new JLabel("Operand y");
        JLabel resLabel = new JLabel("Resultat");
        op1TextField = new JTextField("0",10);
        op2TextField = new JTextField("0",10);
        resTextField = new JTextField("0",10);
        resTextField.setEditable(false);

        // Radio and check buttons
        colorBtn = new JCheckBox("Helles Display");
        colorBtn.setSelected(true);

        degBtn = new JRadioButton("Deg");
        degBtn.setSelected(true);
        radBtn = new JRadioButton("Rad");

        ButtonGroup group = new ButtonGroup();
        group.add(degBtn);
        group.add(radBtn);

        degBtn.addItemListener(this);
        radBtn.addItemListener(this);
        colorBtn.addItemListener(this);

        // Buttons
        btnPlus = new JButton("+");
        btnMal = new JButton("*");
        btnMin = new JButton("-");
        btnDiv = new JButton("/");
        btnSin = new JButton("sin");
        btnCos = new JButton("cos");
        btnPot = new JButton("x^y");
        btnLog2 = new JButton("log2");
        btnClr = new JButton("Clear");

        btnPlus.addActionListener(this);
        btnMal.addActionListener(this);
        btnMin.addActionListener(this);
        btnDiv.addActionListener(this);
        btnSin.addActionListener(this);
        btnCos.addActionListener(this);
        btnPlus.addActionListener(this);
        btnLog2.addActionListener(this);
        btnPot.addActionListener(this);
        btnClr.addActionListener(this);

        // Panels
        JPanel panelIO = new JPanel();
        panelIO.setPreferredSize(new Dimension(450, 100));
        panelIO.setBorder(BorderFactory.createLineBorder(Color.gray));
        panelIO.setLayout(new GridLayout(3, 2));
        panelIO.add(op1Label);
        panelIO.add(op1TextField);
        panelIO.add(op2Label);
        panelIO.add(op2TextField);
        panelIO.add(resLabel);
        panelIO.add(resTextField);

        JPanel panelChoice = new JPanel();
        panelChoice.setLayout(new GridLayout(1, 3));
        panelChoice.add(degBtn);
        panelChoice.add(radBtn);
        panelChoice.add(colorBtn);

        JPanel panelBtn = new JPanel();
        panelBtn.setPreferredSize(new Dimension(450, 75));
        panelBtn.setBorder(BorderFactory.createLineBorder(Color.gray));
        panelBtn.setLayout(new GridLayout(2, 4));
        panelBtn.add(btnPlus);
        panelBtn.add(btnMal);
        panelBtn.add(btnMin);
        panelBtn.add(btnDiv);
        panelBtn.add(btnSin);
        panelBtn.add(btnCos);
        panelBtn.add(btnPot);
        panelBtn.add(btnLog2);

        JPanel panelClr = new JPanel();
        panelClr.add(btnClr);

        // Hauptfenster
        this.setLayout(new FlowLayout());
        this.add(panelIO);
        this.add(panelChoice);
        this.add(panelBtn);
        this.add(panelClr);

        this.pack();
        this.setLocationRelativeTo(null);
        this.setVisible(true);
    }

    public static void main(String[] args) {
        JFrame myApp = new Taschenrechner();
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        Object source = e.getSource();
        String s1 = op1TextField.getText();
        String s2 = op2TextField.getText();

        double o1 = 0;
        double o2 = 0;

        try {
            o1 = Double.parseDouble(s1.replaceAll(",", "."));
            o2 = Double.parseDouble(s2.replaceAll(",", "."));
        } catch (Exception x) {
            if (source != btnClr) {
                System.out.println("Fehlereingabe!");
                source = null;
            }
        }
        if (source == btnPlus) {
            resTextField.setText("" + String.format(Locale.US, "%.2f",o1+o2));
        }
        else if (source == btnMal) {
            resTextField.setText("" + String.format(Locale.US, "%.2f",o1*o2));
        }
        else if (source == btnMin) {
            resTextField.setText("" + String.format(Locale.US, "%.2f",o1-o2));
        }
        else if (source == btnDiv) {
            resTextField.setText("" + String.format(Locale.US, "%.2f",o1/o2));
        }
        else if (source == btnSin) {
            if (isRad) {
                resTextField.setText("" + String.format(Locale.US, "%.2f", Math.sin(o1)));
            }
            else {
                resTextField.setText("" + String.format(Locale.US, "%.2f", Math.sin(Math.toRadians(o1))));
            }
            op2TextField.setText("0");
        }
        else if (source == btnCos) {
            if (isRad) {
                resTextField.setText("" + String.format(Locale.US, "%.2f", Math.cos(o1)));
            }
            else {
                resTextField.setText("" + String.format(Locale.US, "%.2f", Math.cos(Math.toRadians(o1))));
            }
            op2TextField.setText("0");
        }
        else if (source == btnPot) {
            resTextField.setText("" + String.format(Locale.US, "%.2f", Math.pow(o1, o2)));
        }
        else if (source == btnLog2) {
            resTextField.setText("" + String.format(Locale.US, "%.2f",Math.log(o1) / Math.log(2)));
            op2TextField.setText("0");
        }
        else if (source == btnClr) {
            op1TextField.setText("0");
            op2TextField.setText("0");
            resTextField.setText("0");
        }
    }

    @Override
    public void itemStateChanged(ItemEvent e) {
        Object source = e.getSource();

        if (source == colorBtn) {
            if (isDark) {
                op1TextField.setBackground(Color.white);
                op2TextField.setBackground(Color.white);
                resTextField.setBackground(Color.white);

                op1TextField.setForeground(Color.black);
                op2TextField.setForeground(Color.black);
                resTextField.setForeground(Color.black);

                isDark = false;
            } else {
                op1TextField.setBackground(Color.black);
                op2TextField.setBackground(Color.black);
                resTextField.setBackground(Color.black);

                op1TextField.setForeground(Color.yellow);
                op2TextField.setForeground(Color.yellow);
                resTextField.setForeground(Color.yellow);

                isDark = true;
            }
        }
        else if (source == degBtn) {
            isRad = false;
        }
        else if (source == radBtn) {
            isRad = true;
        }
    }
}
