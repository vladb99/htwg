-- Teil 5 --
--CREATE OR REPLACE VIEW kundenstatistik(knr, anzahl_buchungen, anzahl_stornierungen, summe_zahlungen) AS
--SELECT kunde.knr, count(distinct buchung.bnr) as "Anzahl Buchungen", count(stornierung.bnr) as "Anzahl stornierter Buchungen", sum(nvl(anzahlung.betrag, 0)) as "Summe aller Zahlungen"
--FROM kunde LEFT OUTER JOIN buchung on kunde.knr = buchung.knr
--    LEFT OUTER JOIN stornierung on kunde.knr = stornierung.knr
--    LEFT OUTER JOIN anzahlung on buchung.bnr = anzahlung.bnr
--GROUP BY kunde.knr;

--SELECT * FROM kundenstatistik;

-- Just to see all the combinations
--SELECT *
--FROM kunde LEFT OUTER JOIN buchung on kunde.knr = buchung.knr
--    LEFT OUTER JOIN stornierung on kunde.knr = stornierung.knr
--    LEFT OUTER JOIN anzahlung on buchung.bnr = anzahlung.bnr;
    
CREATE OR REPLACE VIEW kundenstatistik(knr, anzahl_buchungen, anzahl_stornierungen, summe_zahlungen) AS
SELECT anzahlBuchungen.knr, anzahlBuchungen.anzahl_buchungen, anzahlStornierungen.anzahl_stornierungen, summeZahlungen.summe_zahlugen
FROM anzahlBuchungen
INNER JOIN anzahlStornierungen on anzahlBuchungen.knr = anzahlStornierungen.knr
INNER JOIN summeZahlungen on anzahlBuchungen.knr = summeZahlungen.knr;

SELECT * FROM kundenstatistik;
    
--Anzahl Buchungen
CREATE OR REPLACE VIEW anzahlBuchungen(knr, anzahl_buchungen) AS
SELECT kunde.knr, count(buchung.knr) as "Anzahl Buchungen"
FROM kunde LEFT OUTER JOIN buchung ON kunde.knr = buchung.knr
GROUP BY kunde.knr;

--Anzahl Stornierungen
CREATE OR REPLACE VIEW anzahlStornierungen(knr, anzahl_stornierungen) AS 
SELECT kunde.knr, count(stornierung.knr) as "Anzahl Stornierungen"
FROM kunde LEFT OUTER JOIN stornierung on kunde.knr = stornierung.knr
GROUP BY kunde.knr;

--Summe Zahlungen
CREATE OR REPLACE VIEW summeZahlungen(knr, summe_zahlugen) AS
SELECT kunde.knr, sum(nvl(buchung.betrag, 0)) as "Summe Zahlungen"
FROM kunde LEFT OUTER JOIN buchung on kunde.knr = buchung.knr
GROUP BY kunde.knr;

SELECT * FROM anzahlbuchungen;
SELECT * FROM anzahlStornierungen;
SELECT * FROM summeZahlungen;
