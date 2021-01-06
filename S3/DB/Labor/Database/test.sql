SELECT distinct adresse.lname
FROM dbsys25.adresse adresse INNER JOIN dbsys25.wohnung wohnung on adresse.anr = wohnung.anr;

SELECT *--wohnung.wname, avg(buchung.anz) as "Durchschnittliche Bewertung"
FROM dbsys25.wohnung wohnung
LEFT OUTER JOIN dbsys25.besitzt besitzt on wohnung.wnr = besitzt.wnr
LEFT OUTER JOIN dbsys25.buchung buchung on wohnung.wnr = buchung.wnr
INNER JOIN dbsys25.adresse adresse on wohnung.anr = adresse.anr
INNER JOIN dbsys25.ausstattung ausstattung on ausstattung.auname = besitzt.auname
WHERE adresse.lname = 'Spanien'
AND besitzt.auname = 'Sauna'
AND wohnung.wname NOT IN (SELECT wohnung.wname
            FROM dbsys25.wohnung wohnung
            INNER JOIN dbsys25.buchung buchung on wohnung.wnr = buchung.wnr
            WHERE (buchung.anreise >= to_date('10-01-2021','DD-MM-YYYY') AND buchung.anreise <= to_date('20-01-2021','DD-MM-YYYY')) OR (buchung.abreise >= to_date('10-01-2021','DD-MM-YYYY') AND buchung.abreise <= to_date('20-01-2021','DD-MM-YYYY')) OR (buchung.anreise <= to_date('10-01-2021','DD-MM-YYYY') AND buchung.abreise >= to_date('20-01-2021','DD-MM-YYYY')) )
--GROUP BY wohnung.wname ORDER BY avg(buchung.anz) desc;
;

SELECT wohnung.wname FROM dbsys25.wohnung wohnung INNER JOIN dbsys25.buchung buchung on wohnung.wnr = buchung.wnr WHERE (buchung.anreise >= to_date('10-01-2021','DD-MM-YYYY') AND buchung.anreise <= to_date('20-01-2021','DD-MM-YYYY')) OR (buchung.abreise >= to_date('10-01-2021','DD-MM-YYYY') AND buchung.abreise <= to_date('20-01-2021','DD-MM-YYYY')) OR (buchung.anreise <= to_date('10-01-2021','DD-MM-YYYY') AND buchung.abreise >= to_date('20-01-2021','DD-MM-YYYY'));



