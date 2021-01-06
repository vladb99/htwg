import javax.swing.*;
import java.awt.*;

public class Register extends JFrame {
    JTextField foreNameTextField;
    JTextField nameTextField;
    JTextField strTextField;
    JTextField nrTextField;
    JTextField plzTextField;
    JTextField cityTextField;
    JTextField emailTextField;
    JTextField pwdTextField;
    JTextField bankTextField;

    JCheckBox newsBtn;

    JButton btnRegister;

    JComboBox countriesCb;

    String[] possibleCountries = {"", "Spanien", "Deutschland", "Thailand"};

    public Register() {
        this.setTitle("Kunden Registrierung");
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setPreferredSize(new Dimension(500, 400));

        JLabel foreNameLabel = new JLabel("Vorname:");
        JLabel nameLabel = new JLabel("Name:");
        JLabel strLabel = new JLabel("Strasse:");
        JLabel nrLabel = new JLabel("Nr.:");
        JLabel plzLabel = new JLabel("PLZ:");
        JLabel cityLabel = new JLabel("Stadt:");
        JLabel ctyLabel = new JLabel("Land:");
        JLabel emailLabel = new JLabel("Mailadresse:");
        JLabel pwdLabel = new JLabel("Passwort:");
        JLabel bankLabel = new JLabel("IBAN:");

        foreNameTextField = new JTextField("", 10);
        nameTextField = new JTextField("", 10);
        strTextField = new JTextField("", 10);
        nrTextField = new JTextField("", 10);
        plzTextField = new JTextField("", 10);
        cityTextField = new JTextField("", 10);
        emailTextField = new JTextField("", 10);
        pwdTextField = new JPasswordField("", 10);
        bankTextField = new JTextField("", 10);
        newsBtn = new JCheckBox("Newsletter abonnieren?");

        btnRegister = new JButton("Registrieren");

        countriesCb = new JComboBox(possibleCountries);

        JPanel panelPerson = new JPanel();
        panelPerson.setPreferredSize(new Dimension(450, 200));
        panelPerson.setLayout(new GridLayout(7, 2));
        panelPerson.add(foreNameLabel);
        panelPerson.add(foreNameTextField);
        panelPerson.add(nameLabel);
        panelPerson.add(nameTextField);
        panelPerson.add(strLabel);
        panelPerson.add(strTextField);
        panelPerson.add(nrLabel);
        panelPerson.add(nrTextField);
        panelPerson.add(plzLabel);
        panelPerson.add(plzTextField);
        panelPerson.add(cityLabel);
        panelPerson.add(cityTextField);
        panelPerson.add(ctyLabel);
        panelPerson.add(countriesCb);

        JPanel panelLogIn = new JPanel();
        panelLogIn.setPreferredSize(new Dimension(450, 50));
        panelLogIn.setLayout(new GridLayout(2, 2));
        panelLogIn.add(emailLabel);
        panelLogIn.add(emailTextField);
        panelLogIn.add(pwdLabel);
        panelLogIn.add(pwdTextField);

        JPanel panelBank = new JPanel();
        panelBank.setPreferredSize(new Dimension(450, 50));
        panelBank.setLayout(new GridLayout(2, 2));
        panelBank.add(bankLabel);
        panelBank.add(bankTextField);
        panelBank.add(newsBtn);

        JPanel panelRegister = new JPanel();
        panelRegister.add(btnRegister);

        this.setLayout(new FlowLayout());
        this.add(panelPerson);
        this.add(panelLogIn);
        this.add(panelBank);
        this.add(panelRegister);

        this.pack();
        this.setLocationRelativeTo(null);
        this.setVisible(true);
        this.setResizable(false);
    }

    public static void main(String[] args) {
        JFrame myApp = new Register();
    }
}
