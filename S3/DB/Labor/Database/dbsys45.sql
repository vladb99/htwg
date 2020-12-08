SELECT * FROM dbsys25.land;
INSERT INTO dbsys25.land(lname) VALUES ('Griechenland');

SELECT * FROM dbsys25.adresse;
INSERT INTO dbsys25.adresse(nr, plz, strasse, stadt, lname)
	VALUES(9, '00000', 'Test', 'Konstanz', 'Deutschland');
UPDATE dbsys25.adresse
	SET plz = 78462, strasse = 'Bahnhofstrasse'
    WHERE anr = 10;

SELECT * FROM dbsys25.kunde;
INSERT INTO dbsys25.kunde(anr, kname, vorname, newsletter, iban, email)
	VALUES(7, 'Test', 'Test', 'N', 'DE12345128690', 'seb.schneider@gmail.com');
UPDATE dbsys25.kunde
	SET kname = 'Meyer', vorname = 'Michael'
    WHERE knr = 4;
DELETE
	FROM dbsys25.kunde
	WHERE knr = 4;
    
rollback;