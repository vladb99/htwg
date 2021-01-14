import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import javax.swing.text.DefaultCaret;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;
import java.sql.*;
import java.util.LinkedList;

public class Ferienwohnung extends JFrame {
    public static Connection conn = null;
    String[] possibleCountries = {};
    String[] possibleAusstattung = {};
    LinkedList<String> selectedAusstattungen = new LinkedList<>();

    Statement stmt = null;
    ResultSet rset = null;

    JComboBox countryCb;
    JComboBox ausstattungCb;
    JTextField anreiseTextField;
    JTextField abreiseTextField;
    JButton addBtn;
    JButton deleteBtn;
    JButton searchBtn;
    JButton reserveBtn;
    JLabel selectedAusstattungLabel;
    DefaultTableModel tableModel;
    JTable table;

    public Ferienwohnung() throws SQLException {
        initCountries();
        initAusstattung();

        this.setTitle("Ferienwohnung");
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setPreferredSize(new Dimension(700, 400));

        JLabel countryLabel = new JLabel("Land:");
        JLabel anreiseLabel = new JLabel("Anreise (TT.MM.JJJJ):");
        JLabel abreiseLabel = new JLabel("Abreise (TT.MM.JJJJ):");
        JLabel ausstattungLabel = new JLabel("Ausstattungen:");
        JLabel ausgewaehltLabel = new JLabel("Ausgewählt:");
        selectedAusstattungLabel = new JLabel("");

        countryCb = new JComboBox(possibleCountries);
        ausstattungCb = new JComboBox(possibleAusstattung);

        anreiseTextField = new JTextField("", 10);
        abreiseTextField = new JTextField("", 10);

        addBtn = new JButton("auswählen");
        addBtn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String selectedItem = (String) ausstattungCb.getSelectedItem();
                if (selectedItem != "" && !selectedAusstattungen.contains(selectedItem)) {
                    selectedAusstattungen.add(selectedItem);
                    selectedAusstattungLabel.setText(selectedAusstattungen.toString());
                }
            }
        });

        deleteBtn = new JButton("löschen");
        deleteBtn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                selectedAusstattungen = new LinkedList<>();
                selectedAusstattungLabel.setText("");
            }
        });

        searchBtn = new JButton("suchen");
        searchBtn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                searchAppartments();
            }
        });

        reserveBtn = new JButton("buchen");
        reserveBtn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                reserveAppartment();
            }
        });

        tableModel = new DefaultTableModel() {
            @Override
            public boolean isCellEditable(int row, int column) {
                return false;
            }
        };

        table = new JTable(tableModel);
        tableModel.addColumn("Wohnungsname");
        tableModel.addColumn("Durschschnittliche Bewertung");

        table.setPreferredScrollableViewportSize(new Dimension(400, 50));
        table.setFillsViewportHeight(true);

        JScrollPane scrollPane = new JScrollPane(table);

        JPanel eingabePanel = new JPanel();
        eingabePanel.setLayout(new GridLayout(3, 2));

        eingabePanel.add(countryLabel);
        eingabePanel.add(countryCb);
        eingabePanel.add(anreiseLabel);
        eingabePanel.add(anreiseTextField);
        eingabePanel.add(abreiseLabel);
        eingabePanel.add(abreiseTextField);

        JPanel ausstattungPanel = new JPanel();
        ausstattungPanel.setLayout(new GridLayout(2, 3));

        ausstattungPanel.add(ausstattungLabel);
        ausstattungPanel.add(ausstattungCb);
        ausstattungPanel.add(addBtn);
        ausstattungPanel.add(ausgewaehltLabel);
        ausstattungPanel.add(selectedAusstattungLabel);
        ausstattungPanel.add(deleteBtn);

        JPanel ausgabePanel = new JPanel();
        ausgabePanel.setLayout(new FlowLayout());
        ausgabePanel.add(scrollPane);

        JPanel actionsPanel = new JPanel();
        actionsPanel.setLayout(new GridLayout(1, 2));
        actionsPanel.add(searchBtn);
        actionsPanel.add(reserveBtn);

        this.setLayout(new GridLayout(4, 1));
        this.add(eingabePanel);
        this.add(ausstattungPanel);
        this.add(ausgabePanel);
        this.add(actionsPanel);

        this.pack();
        this.setLocationRelativeTo(null);
        this.setVisible(true);
        this.setResizable(false);
    }

    private void searchAppartments() {
        if (countryCb.getSelectedItem().equals("")
            || anreiseTextField.getText().equals("")
            || abreiseTextField.getText().equals("")) {
            JOptionPane.showMessageDialog(this, "Sie müssen alle Felder belegen!");
        } else {
            resetTableModel();
            try {
                String country = (String) countryCb.getSelectedItem();
                String anreise = anreiseTextField.getText().replace('.', '-');
                String abreise = abreiseTextField.getText().replace('.', '-');

                stmt = conn.createStatement();

                String mySelectQuery = "SELECT wohnung.wname, avg(buchung.anz) as \"Durchschnittliche Bewertung\" " +
                        "FROM dbsys25.wohnung wohnung " +
                        "LEFT OUTER JOIN dbsys25.besitzt besitzt on wohnung.wnr = besitzt.wnr " +
                        "LEFT OUTER JOIN dbsys25.buchung buchung on wohnung.wnr = buchung.wnr " +
                        "INNER JOIN dbsys25.adresse adresse on wohnung.anr = adresse.anr " +
                        "WHERE adresse.lname = '" + countryCb.getSelectedItem() + "' ";

                for (String ausstattung : selectedAusstattungen) {
                    if (!ausstattung.equals("")) {
                        mySelectQuery = mySelectQuery + "AND besitzt.auname = '" + ausstattung + "' ";
                    }
                }
                //if (selectedAusstattungen.size() > 0) {
                //    mySelectQuery = mySelectQuery + "AND besitzt.auname = '" + selectedAusstattungen.get(0) + "' ";
                //}

                mySelectQuery = mySelectQuery + "AND wohnung.wname NOT IN " +
                        "(" +
                        "SELECT wohnung.wname " +
                        "FROM dbsys25.wohnung wohnung " +
                        "INNER JOIN dbsys25.buchung buchung on wohnung.wnr = buchung.wnr " +
                        "WHERE (buchung.anreise >= to_date('" + anreise + "','DD-MM-YYYY') AND buchung.anreise <= to_date('" + abreise + "','DD-MM-YYYY')) " +
                        "OR (buchung.abreise >= to_date('" + anreise + "','DD-MM-YYYY') AND buchung.abreise <= to_date('" + abreise + "','DD-MM-YYYY')) " +
                        "OR (buchung.anreise <= to_date('" + anreise + "','DD-MM-YYYY') AND buchung.abreise >= to_date('" + abreise + "','DD-MM-YYYY')) " +
                        ") " +
                        "GROUP BY wohnung.wname " +
                        "ORDER BY avg(buchung.anz) desc";

                System.out.println(mySelectQuery);
                rset = stmt.executeQuery(mySelectQuery);

                while(rset.next()) {
                    tableModel.insertRow(tableModel.getRowCount(), new Object[] { rset.getString("wname"), rset.getDouble("Durchschnittliche Bewertung") });
                }

                stmt.close();

            } catch (SQLException se) {
                System.out.println();
                System.out
                        .println("SQL Exception occurred while establishing connection to DBS: "
                                + se.getMessage());
                System.out.println("- SQL state  : " + se.getSQLState());
                System.out.println("- Message    : " + se.getMessage());
                System.out.println("- Vendor code: " + se.getErrorCode());
                System.out.println();
                System.out.println("EXITING WITH FAILURE ... !!!");
                System.out.println();
                try {
                    conn.rollback();
                } catch (SQLException e) {
                    e.printStackTrace();
                }
                System.exit(-1);
            }
        }
    }

    private void resetTableModel() {
        while (tableModel.getRowCount() > 0)
        {
            tableModel.removeRow(0);
        }
    }

    private void reserveAppartment() {
        int row = table.getSelectedRow();
        if (row == -1) {
            JOptionPane.showMessageDialog(this, "Sie müssen eine Ferienwohnung selektieren!");
        } else {
            try {
                String anreise = anreiseTextField.getText().replace('.', '-');
                String abreise = abreiseTextField.getText().replace('.', '-');

                stmt = conn.createStatement();
                String name = (String) table.getValueAt(row, 0);

                String mySelectQuery = "SELECT wohnung.wnr FROM dbsys25.wohnung wohnung WHERE wohnung.wname = '" + name + "'";
                rset = stmt.executeQuery(mySelectQuery);

                rset.next();
                int wnr = rset.getInt("wnr");

                String myUpdateQuery = "INSERT INTO dbsys25.buchung(wnr, knr, anreise, abreise, bDatum, beDatum, anz, rnr, rDatum, betrag) " +
                        "VALUES(" + wnr + ", 4, to_date('" + anreise + "','DD-MM-YYYY'), to_date('" + abreise + "','DD-MM-YYYY'), SYSDATE, null, null, null, null, null)";

                System.out.println(myUpdateQuery);
                stmt.executeUpdate(myUpdateQuery);

                conn.commit();
                stmt.close();
                resetTableModel();
            } catch (SQLException se) {														// SQL-Fehler abfangen
                System.out.println();
                System.out
                        .println("SQL Exception occurred while establishing connection to DBS: "
                                + se.getMessage());
                System.out.println("- SQL state  : " + se.getSQLState());
                System.out.println("- Message    : " + se.getMessage());
                System.out.println("- Vendor code: " + se.getErrorCode());
                System.out.println();
                System.out.println("EXITING WITH FAILURE ... !!!");
                System.out.println();
                try {
                    conn.rollback();														// Rollback durchführen
                } catch (SQLException e) {
                    e.printStackTrace();
                }
                System.exit(-1);
            }
        }
    }

    private void initCountries() throws SQLException {
        LinkedList<String> countries = new LinkedList<>();
        countries.add("");

        stmt = conn.createStatement(); 												// Statement-Objekt erzeugen

        String mySelectQuery = "SELECT distinct adresse.lname\n" +
                "FROM dbsys25.adresse adresse INNER JOIN dbsys25.wohnung wohnung on adresse.anr = wohnung.anr";
        rset = stmt.executeQuery(mySelectQuery);									// Query ausführen

        while(rset.next()) {
            countries.add(rset.getString("lname"));
        }

        possibleCountries = countries.toArray(new String[]{});
        stmt.close();																// Verbindung trennen
    }

    private void initAusstattung() throws SQLException {
        LinkedList<String> ausstattung = new LinkedList<>();
        ausstattung.add("");

        stmt = conn.createStatement(); 												// Statement-Objekt erzeugen

        String mySelectQuery = "SELECT * FROM dbsys25.ausstattung";
        rset = stmt.executeQuery(mySelectQuery);									// Query ausführen

        while(rset.next()) {
            ausstattung.add(rset.getString("auname"));
        }

        possibleAusstattung = ausstattung.toArray(new String[]{});
        stmt.close();
    }

    public static void main(String[] args) {
        try {
            DriverManager.registerDriver(new oracle.jdbc.OracleDriver()); 				// Treiber laden
            String url = "jdbc:oracle:thin:@oracle19c.in.htwg-konstanz.de:1521:ora19c"; // String für DB-Connection
            conn = DriverManager.getConnection(url, "dbsys51", "dbsys51"); 						// Verbindung erstellen

            conn.setTransactionIsolation(Connection.TRANSACTION_SERIALIZABLE); 			// Transaction Isolations-Level setzen
            conn.setAutoCommit(false);													// Kein automatisches Commit

            JFrame myApp = new Ferienwohnung();

        } catch (SQLException se) {														// SQL-Fehler abfangen
            System.out.println();
            System.out
                    .println("SQL Exception occurred while establishing connection to DBS: "
                            + se.getMessage());
            System.out.println("- SQL state  : " + se.getSQLState());
            System.out.println("- Message    : " + se.getMessage());
            System.out.println("- Vendor code: " + se.getErrorCode());
            System.out.println();
            System.out.println("EXITING WITH FAILURE ... !!!");
            System.out.println();
            try {
                conn.rollback();														// Rollback durchführen
            } catch (SQLException e) {
                e.printStackTrace();
            }
            System.exit(-1);
        }
    }
}
