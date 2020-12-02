--LAND

INSERT INTO land(lname) VALUES ('Spanien');
INSERT INTO land(lname) VALUES ('Italien');
INSERT INTO land(lname) VALUES ('Deutschland');

--ADRESSE

INSERT INTO adresse(nr, plz, strasse, stadt, lname)
	VALUES(5, '08001', 'Carrer de Corsega', 'Barcelona', 'Spanien');
INSERT INTO adresse(nr, plz, strasse, stadt, lname)
	VALUES(30, '08001', 'Carrer de Paris', 'Barcelona', 'Spanien');
INSERT INTO adresse(nr, plz, strasse, stadt, lname)
	VALUES(8, '48001', 'Carrer de Planas', 'Bilbao', 'Spanien');
INSERT INTO adresse(nr, plz, strasse, stadt, lname)
	VALUES(13, '46001', 'Carrer de Cuba', 'Valencia', 'Spanien');

INSERT INTO adresse(nr, plz, strasse, stadt, lname)
	VALUES(21, '50100', 'Via Donatello', 'Florenz', 'Italien');
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


















