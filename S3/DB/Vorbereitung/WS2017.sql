-- Aufgabe 2:

-- a) Smartphones welcher Marke wurden 2018 noch nicht verkauft?
select distinct a.Marke
from Artikel a
where a.artikelgruppe = 'Smartphone'
	and a.artikelNr not in (
						select b.artikelNr
						from Bestellung b
						where to_char(b.datum, 'YY') = '18' -- oder extract(year from b.datum) = 2018
						);

-- b) Wie viele Kunden haben den Fernseher Kroni bisher gekauft?
select count(distinct b.kundennr)
from Artikel a, Bestellung b
where a.artikelNr = b.artikelNr
	and a.artikelgruppe = 'Fernseher'
	and a.marke = 'Kroni';

-- c) Mit welcher Artikelgruppe hat der Shop 2017 am meisten Geld eingenommen?
create view profit(gruppe, geld) as
select a.artikelgruppe, sum(a.preis)
from Artikel a, Bestellung b
where a.artikelNr = b.artikelNr
	and to_char(b.datum, 'YY') = '17'
group by a.artikelgruppe;

select p.gruppe
from profit p
where p.geld = (select max(p2.geld) from profit p2);

-- d) Wie viele Kunden haben bisher das gleiche Smartphone mehrmals gekauft?
select count(distinct b1.kundennr)
from Artikel a, Bestellung b1, Bestellung b2
where b1.artikelNr = b2.artikelNr
	and a.artikelNr = b1.artikelNr
	and a.artikelgruppe = 'Smartphone'
	and b1.bestellnr != b2.bestellnr
	and b1.kundennr = b2.kundennr;

-- e) Welches Smartphone ist das günstigste?
create view smartphones(marke, preis) as
select a.marke, a.preis
from Artikel a
where a.artikelgruppe = 'Smartphone';

select s.marke
from smartphones s 
where s.preis = (select min(preis) from smartphones);

-- f) Welche Kunden haben bereits ein Smartphone aber noch nie einen Fernseher
-- gekauft? Sortieren Sie die Ausgabe nach dem Kundennamen.
select count(*)
from Kunde k
where k.kundennr in (
					select b.kundennr
					from Artikel a, Bestellung b
					where a.artikelNr = b.artikelNr
						and a.artikelgruppe = 'Smartphone'
					)
	and k.kundennr not in (
					select b.kundennr
					from Artikel a, Bestellung b
					where a.artikelNr = b.artikelNr
						and a.artikelgruppe = 'Fernseher'
					)
order by k.name; 

-- g) Wie viele Fernseher sind günstiger als jedes Smartphone?
select count(*)
from Artikel a
where a.artikelgruppe = 'Fernseher'
	and a.preis < ALL (
					select a2.preis
					from Artikel a2
					where a.artikelgruppe = 'Smartphone'
					);

-- h) In welchem Jahr wurden bisher am meisten Fernseher verkauft?
create view fernseher(jahr, anzahl) as
select to_char(b.datum, 'YYYY'), count(*) as 'Anzahl'
from Artikel a, Bestellung b
where a.artikelNr = b.artikelNr
	and a.artikelgruppe = 'Fernseher'
group by to_char(b.datum, 'YYYY');

select f1.jahr
from fernseher f1
where f1.anzahl = (select max(f2.anzahl) from fernseher f2);

-- Geben Sie die folgende Anfrage in der relationalen Algebra an:
-- i) Artikel welcher Marke hat Hans Maier bisher gekauft?
















