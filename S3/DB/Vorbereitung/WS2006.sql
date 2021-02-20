--WS2006

--Aufgabe 2:

-- c) In welchen Jahren seit 2000 hat Schauspieler Brad Pitt in keinem im Filmstudio
-- gedrehten Film mitgewirkt?
select f.jahr
from film f
where f.jahr not in (
				select distinct f.jahr
			    from Schauspieler s, speltMit sm, film f
				where s.snr = sm.snr
				 	and f.fnr = sm.fnr
		         	and s.name = 'Brad Pitt'
		         	and f.jahr >= 2000
		        );

-- d) Stellen Sie zusammen, in wie vielen Filmen Schauspieler Dustin Hoffman pro Jahr
-- mitgespielt hat.
select f.jahr, count(*) as 'Anzahl Filme'
from Schauspieler s, speltMit sm, Film f
where s.sNr = sm.sNr
	and f.fNr = sm.fNr
	and s.name = 'Dustin Hoffman'
group by f.jahr;

-- e) Welcher Schauspieler hat 2006 die meisten Filme gedreht? 
create view anzahlFilme2006(sNr, anzahl)
as
select s.sNr, count(*)
from Schauspieler s, speltMit sm, Film f
where s.sNr = sm.sNr
	and f.fNr = sm.fNr
	and f.jahr = 2006
group by s.sNr;

select s.name
from Schauspieler s, anzahlFilme2006 aF
where s.sNr = aF.sNr
	and aF.anzahl = (select max(anzahl)
					from anzahlFilme2006);

-- f) Wie oft haben Dustin Hoffman und Tom Cruise bereits zusammen in einem Film
-- mitgespielt?
select count(*) as 'Anzahl Filme'
from Schauspieler d, spieltMit smD
where d.sNr = smD.sNr
	and d.name = 'Dustin Hoffman'
	and smD.fNr in (
					select smT.fnr
					from Schauspieler t, spieltMit smT
					where t.sNr = smT.sNr
						and t.name = 'Tom Cruise'
					);

-- ODER
SELECT COUNT(p1.snr) AS Anzahl
FROM Schauspieler s1, spieltMit p1, Schauspieler s2, spieltMit p2
WHERE s1.name = 'Dustin Hoffman'
AND s2.name = 'Tom Cruise'
AND s1.snr = p1.snr
AND s2.snr = p2.snr
AND p2.fnr = p1.fnr;























