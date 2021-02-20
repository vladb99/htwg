-- Aufgabe 2:

-- a) In welchen Jahren ist in Datenbanksysteme niemand durchgefallen (niemand hat Note
-- 5,0 erzielt)?
create view durchgefallen(jahr, anzahl) as
select to_char(k.datum, 'YY') as 'Jahr', nvl(count(*), 0)
from Vorlesung v, Klausur k
where v.vnr = k.vnr
	and v.name = 'Datenbanksysteme'
	and k.note = '5,0'
group by to_char(k.datum, 'YY');

select d.jahr
from durchgefallen d
where d.anzahl = 0;

-- b) Welche Studierenden haben in Datenbanksysteme bereits eine 1,0 als auch eine 5,0
-- erzielt?
select s.name
from Vorlesung v, Klausur k1, Klausur k2, Studierende s
where v.vnr = k1.vnr
	and s.matrikelnr = k1.matrikelnr
	and v.name = 'Datenbanksysteme'
	and k1.matrikelnr = k2.matrikelnr
	and k1.note = '1,0'
	and k2.note = '5,0';

-- c) In welcher Vorlesung wurden 2020 durchschnittlich die besten Noten erzielt? Falls
-- mehrere Vorlesungen den besten Notenschnitt erzielt haben, sollen alle ausgegeben
-- werden.
create view bestAvg(vorlesung, avg) as
select v.name, avg(k.note) 
from Vorlesungen v, Klausur k
where v.vnr = k.vnr
	and to_char(k.datum, 'YY') = '20'
group by v.name;

select b.vorlesung
from bestAvg b
where b.avg = (select max(avg) from bestAvg);

-- d) Wie viele Studierende haben noch keine Klausur in Datenbanken geschrieben?
select count(*) as 'Anzahl'
from Studierende s
where s.matrikelnr not in (
						select k.matrikelnr
						from Vorlesung v, Klausur k
						where v.vnr = k.vnr
							and v.name = 'Datenbanksysteme'
						);

-- e) Stellen Sie pro Kalenderjahr die Durchschnittsnoten über sämtliche Vorlesungen
-- hinweg zusammen? Sortieren Sie nach Kalenderjahr absteigend.
select to_char(k.datum, 'YY') as 'Jahr', avg(k.note)
from Klausur k
group by to_char(k.datum, 'YY')
order by to_char(k.datum, 'YY') desc;

-- f) Wie oft kommt es vor, dass zwei oder mehrere Studierende den gleichen Namen
-- haben? Es soll die Anzahl der betreffenden Namen ausgegeben werden.
create view namen(name, anzahl) as
select s1.name, count(distinct s1.matrikelnr)
from Studierende s1, Studierende s2
where s1.name = s2.name
	and s1.matrikelnr != s2.matrikelnr
group by s1.name;

select sum(n.anzahl)
from namen n;

-- Geben Sie die folgende Anfrage in der relationalen Algebra an:
-- g) Welche Note hat Gaby Müller in Datenbanken am 24.06.2020 erzielt?

-- siehe A2g.pdf
