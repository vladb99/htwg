--Wie viele Ferienwohnungen sind pro Stadtnamen gespeichert?
--1, 2, 4, 6, 5, 3
--Barcelona++
--Paris++
--Rom+
--Bilbao+
--SELECT stadt, count(*)
--FROM dbsys25.adresse, dbsys25.wohnung
--WHERE dbsys25.adresse.anr = dbsys25.wohnung.anr
--GROUP BY stadt;

SELECT stadt, count(*) as "Anzahl"
FROM dbsys25.adresse adresse 
    INNER JOIN dbsys25.wohnung wohnung on adresse.anr = wohnung.anr
GROUP BY stadt;


--Welche Ferienwohnungen in Spanien haben durchschnittlich mehr als 4 Sterne erhalten?

SELECT wohnung.wnr
FROM dbsys25.land land 
    INNER JOIN dbsys25.adresse adresse on land.lname = adresse.lname
	INNER JOIN dbsys25.wohnung wohnung on adresse.anr = wohnung.anr
	INNER JOIN dbsys25.buchung buchung on wohnung.wnr = buchung.wnr
WHERE land.lname = 'Spanien'
GROUP BY wohnung.wnr
HAVING AVG(buchung.anz) > 4;

--Wie viele Ferienwohnungen wurden noch nie gebucht?
--https://stackoverflow.com/questions/38549/what-is-the-difference-between-inner-join-and-outer-join

SELECT count(*) as "Unreservierte Buchungen"
FROM dbsys25.wohnung wohnung 
    LEFT OUTER JOIN dbsys25.buchung buchung on wohnung.wnr = buchung.wnr
WHERE buchung.wnr IS NULL;

--Welche Ferienwohnung hat die meisten Ausstattungen?

--SELECT wohnung.wnr, count(*) as "Anzahl Ausstattungen"
--FROM dbsys25.wohnung wohnung INNER JOIN dbsys25.besitzt besitzt on wohnung.wnr = besitzt.wnr
--GROUP BY wohnung.wnr
--HAVING count(*) = (SELECT max(count(wohnung.wnr))
--                   FROM dbsys25.wohnung wohnung INNER JOIN dbsys25.besitzt besitzt on wohnung.wnr = besitzt.wnr
--                   GROUP BY wohnung.wnr);

CREATE OR REPLACE VIEW anzahl_ausstattungen(wnr, anzahl) AS
SELECT wnr, count(*)
FROM dbsys25.besitzt besitzt
GROUP BY wnr;

SELECT * FROM anzahl_ausstattungen;

SELECT wnr
FROM anzahl_ausstattungen
WHERE anzahl = (SELECT max(anzahl) from anzahl_ausstattungen);

--Wie viele Reservierungen gibt es für die einzelnen Länder? Länder, in denen keine Reservierungen
--existieren, sollen mit der Anzahl 0 ebenfalls aufgeführt werden. Das Ergebnis soll nach der Anzahl
--Reservierungen absteigend sortiert werden.

SELECT land.lname, count(adresse.lname) as "Anzahl Reservierungen"
FROM dbsys25.buchung buchung 
    INNER JOIN dbsys25.wohnung wohnung on buchung.wnr = wohnung.wnr
    INNER JOIN dbsys25.adresse adresse on wohnung.anr = adresse.anr
    RIGHT OUTER JOIN dbsys25.land land on adresse.lname = land.lname
GROUP BY land.lname
ORDER BY count(adresse.lname) desc;

--Welche Ferienwohnungen mit Sauna sind in Spanien in der Zeit vom 1.11.2019 – 21.11.2019 noch frei?
--Geben Sie den Ferienwohnungs-Namen und deren durchschnittliche Bewertung an. Ferienwohnungen
--mit guten Bewertungen sollen zuerst angezeigt werden.

SELECT wohnung.wname, avg(buchung.anz) as "Durchschnittliche Bewertung"
FROM dbsys25.wohnung wohnung 
    INNER JOIN dbsys25.besitzt besitzt on wohnung.wnr = besitzt.wnr
    LEFT OUTER JOIN dbsys25.buchung buchung on wohnung.wnr = buchung.wnr
    INNER JOIN dbsys25.adresse adresse on wohnung.anr = adresse.anr
WHERE adresse.lname = 'Spanien'
AND besitzt.auname = 'Sauna'
AND wohnung.wname NOT IN
(
SELECT wohnung.wname
FROM dbsys25.wohnung wohnung
INNER JOIN dbsys25.buchung buchung on wohnung.wnr = buchung.wnr
WHERE (buchung.anreise >= to_date('01-11-2021','DD-MM-YYYY') AND buchung.anreise <= to_date('21-11-2021','DD-MM-YYYY'))
OR (buchung.abreise >= to_date('01-11-2021','DD-MM-YYYY') AND buchung.abreise <= to_date('21-11-2021','DD-MM-YYYY'))
OR (buchung.anreise <= to_date('01-11-2021','DD-MM-YYYY') AND buchung.abreise >= to_date('21-11-2021','DD-MM-YYYY'))
)
GROUP BY wohnung.wname
ORDER BY avg(buchung.anz) desc;

--AND wohnung.wnr NOT IN
--(
--SELECT buchung.wnr
--FROM dbsys25.buchung buchung
--WHERE buchung.anreise >= to_date('01-11-2021','DD-MM-YYYY')
--AND buchung.abreise <= to_date('21-11-2021','DD-MM-YYYY')
--)

