--LAND

INSERT INTO land(lname) VALUES ('Spanien');
INSERT INTO land(lname) VALUES ('Italien');
INSERT INTO land(lname) VALUES ('Deutschland');
INSERT INTO land(lname) VALUES ('Frankreich');

--ADRESSE

INSERT INTO adresse(nr, plz, strasse, stadt, lname)
	VALUES(5, '08001', 'Carrer de Corsega', 'Barcelona', 'Spanien');
INSERT INTO adresse(nr, plz, strasse, stadt, lname)
	VALUES(30, '08001', 'Carrer de Paris', 'Barcelona', 'Spanien');
INSERT INTO adresse(nr, plz, strasse, stadt, lname)
	VALUES(8, '48001', 'Carrer de Planas', 'Bilbao', 'Spanien');
INSERT INTO adresse(nr, plz, strasse, stadt, lname)
	VALUES(13, '46001', 'Carrer de Cuba', 'Paris', 'Frankreich');

INSERT INTO adresse(nr, plz, strasse, stadt, lname)
	VALUES(21, '50100', 'Via Donatello', 'Paris', 'Italien');
INSERT INTO adresse(nr, plz, strasse, stadt, lname)
	VALUES(17, '00100', 'Via del Tritone', 'Rom', 'Italien');

INSERT INTO adresse(nr, plz, strasse, stadt, lname)
	VALUES(12, '78462', 'Bahnhofstrasse', 'Konstanz', 'Deutschland');
INSERT INTO adresse(nr, plz, strasse, stadt, lname)
	VALUES(18, '80331', 'Zentnerstrasse', 'München', 'Deutschland');
INSERT INTO adresse(nr, plz, strasse, stadt, lname)
	VALUES(5, '20095', 'Osterstrasse', 'Hamburg', 'Deutschland');

--ATTRAKTION

INSERT INTO attraktion(atname, beschreibung)
	VALUES('Sagrade Familia', 'Wundervoller Sakralbau');
INSERT INTO attraktion(atname, beschreibung)
	VALUES('Camp Nou', 'Fußballstation');
INSERT INTO attraktion(atname, beschreibung)
	VALUES('Casa Vicens', 'Museum');
INSERT INTO attraktion(atname, beschreibung)
	VALUES('Pantheon', 'Gebäude aus antiken Rom');

--AUSSTATTUNG

INSERT INTO ausstattung(auname) VALUES('Sauna');
INSERT INTO ausstattung(auname) VALUES('Schwimmbad');
INSERT INTO ausstattung(auname) VALUES('Tennisplatz');

--WOHNUNG

INSERT INTO wohnung(anr, wname, groesse, preis, anz)
	VALUES(1, 'Wohnung 1', 120.00, 400.00, 5);
INSERT INTO wohnung(anr, wname, groesse, preis, anz)
	VALUES(2, 'Wohnung 2', 100.00, 450.00, 3);
INSERT INTO wohnung(anr, wname, groesse, preis, anz)
	VALUES(4, 'Wohnung 3', 90.00, 600.00, 4);
INSERT INTO wohnung(anr, wname, groesse, preis, anz)
	VALUES(6, 'Wohnung 4', 70.00, 650.00, 3);
INSERT INTO wohnung(anr, wname, groesse, preis, anz)
	VALUES(5, 'Wohnung 5', 200.00, 800.00, 6);
INSERT INTO wohnung(anr, wname, groesse, preis, anz)
	VALUES(3, 'Wohnung 6', 250.00, 500.00, 4);

--ENTFERNT

INSERT INTO entfernt(wnr, atname, entfernung)
	VALUES(1, 'Sagrade Familia', 5.00);
INSERT INTO entfernt(wnr, atname, entfernung)
	VALUES(2, 'Camp Nou', 2.50);
INSERT INTO entfernt(wnr, atname, entfernung)
	VALUES(4, 'Casa Vicens', 3.00);
INSERT INTO entfernt(wnr, atname, entfernung)
	VALUES(6, 'Pantheon', 2.00);

--BESITZT

INSERT INTO besitzt(wnr, auname)
	VALUES(1, 'Sauna');
INSERT INTO besitzt(wnr, auname)
	VALUES(1, 'Schwimmbad');
INSERT INTO besitzt(wnr, auname)
	VALUES(6, 'Sauna');
INSERT INTO besitzt(wnr, auname)
	VALUES(6, 'Tennisplatz');
INSERT INTO besitzt(wnr, auname)
	VALUES(2, 'Sauna');
INSERT INTO besitzt(wnr, auname)
	VALUES(5, 'Schwimmbad');

--BILD
INSERT INTO bild(wnr, bild)
	VALUES(1, utl_raw.cast_to_raw('Bild 1'));
INSERT INTO bild(wnr, bild)
	VALUES(1, utl_raw.cast_to_raw('Bild 2'));
INSERT INTO bild(wnr, bild)
	VALUES(3, utl_raw.cast_to_raw('Bild 3'));

--KUNDE
INSERT INTO kunde(anr, kname, vorname, newsletter, iban, email)
	VALUES(7, 'Müller', 'Max', 'Y', 'DE1234455678', 'max.mueller@gmail.com');
INSERT INTO kunde(anr, kname, vorname, newsletter, iban, email)
	VALUES(8, 'Maller', 'Tom', 'N', 'DE3243434343', 'tom.maller@gmail.com');
INSERT INTO kunde(anr, kname, vorname, newsletter, iban, email)
	VALUES(7, 'Schneider', 'Sebastian', 'N', 'DE12345128690', 'seb.schneider@gmail.com');

--BUCHUNG

INSERT INTO buchung(wnr, knr, anreise, abreise, bDatum, beDatum, anz, rnr, rDatum, betrag)
	VALUES(1,
		1,
		to_date('10.20.2021','MM.DD.YYYY'),
		to_date('10.23.2021', 'MM.DD.YYYY'),
		to_date('10.1.2021', 'MM.DD.YYYY'),
		to_date('10.25.2021', 'MM.DD.YYYY'),
		5,
		rechnungID.NEXTVAL,
		to_date('10.26.2021', 'MM.DD.YYYY'),
		500.00);
INSERT INTO buchung(wnr, knr, anreise, abreise, bDatum, beDatum, anz)
	VALUES(2,
		3,
		to_date('11.01.2021','MM.DD.YYYY'),
		to_date('11.06.2021', 'MM.DD.YYYY'),
		to_date('10.01.2021', 'MM.DD.YYYY'),
		to_date('11.15.2021', 'MM.DD.YYYY'),
		4);
INSERT INTO buchung(wnr, knr, anreise, abreise, bDatum, beDatum, anz, rnr, rDatum, betrag)
	VALUES(2,
		2,
		to_date('10.01.2021','MM.DD.YYYY'),
		to_date('10.06.2021', 'MM.DD.YYYY'),
		to_date('09.01.2021', 'MM.DD.YYYY'),
		to_date('10.15.2021', 'MM.DD.YYYY'),
		5,
		rechnungID.NEXTVAL,
		to_date('09.01.2021', 'MM.DD.YYYY'),
		1000.00);
INSERT INTO buchung(wnr, knr, anreise, abreise, bDatum, beDatum, anz)
	VALUES(3,
		1,
		to_date('09.01.2021','MM.DD.YYYY'),
		to_date('09.06.2021', 'MM.DD.YYYY'),
		to_date('08.01.2021', 'MM.DD.YYYY'),
		to_date('09.15.2021', 'MM.DD.YYYY'),
		3);
INSERT INTO buchung(wnr, knr, anreise, abreise, bDatum, beDatum, anz, rnr, rDatum, betrag)
	VALUES(6,
		1,
		to_date('08.01.2021','MM.DD.YYYY'),
		to_date('08.06.2021', 'MM.DD.YYYY'),
		to_date('07.01.2021', 'MM.DD.YYYY'),
		to_date('08.15.2021', 'MM.DD.YYYY'),
		5,
		rechnungID.NEXTVAL,
		to_date('07.01.2021', 'MM.DD.YYYY'),
		900.00);

--ANZAHLUNG

INSERT INTO anzahlung(bnr, datum, betrag)
	VALUES(1, to_date('10.26.2021', 'MM.DD.YYYY'), 250.00);
INSERT INTO anzahlung(bnr, datum, betrag)
	VALUES(1, to_date('11.26.2021', 'MM.DD.YYYY'), 250.00);
INSERT INTO anzahlung(bnr, datum, betrag)
	VALUES(3, to_date('09.01.2021', 'MM.DD.YYYY'), 1000.00);
INSERT INTO anzahlung(bnr, datum, betrag)
	VALUES(5, to_date('07.01.2021', 'MM.DD.YYYY'), 900.00);

commit;









