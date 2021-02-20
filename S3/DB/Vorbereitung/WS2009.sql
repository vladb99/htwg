-- Aufgabe 2

-- a) An wie viele Personen ist ein Nobelpreis bisher mehrmals verliehen worden?
create view mehrmals(pnr) as
select n.pnr
from Nobelpreis n
group by n.pnr
having count(*) > 1;

select count(*)
from mehrmals;


-- b) Welches Land besitzt die höchste Anzahl an Nobelpreisträgern in Physik?
create view PhysikLand(land, anzahl) as
select p.land, count(*) as 'Anzahl'
from Nobelpreis n, Preisträger p
where n.pnr = p.pnr
	and n.Kategorie = 'Physik'
group by p.land;

select pl.land
from PhysikLand pl
where pl.anzahl = (select max(anzahl) from PhysikLand);

-- c) In wie vielen Jahren wurde bereits ein Nobelpreis an Deutsche verliehen.
select count(distinct n.jahr)
from Nobelpreis n, Preisträger p
where n.pnr = p.pnr
	and p.land = 'Deutschland';

-- d) Stellen Sie dar, welche Länder wie viele Nobelpreise in Physik erhalten haben.
-- Länder, die weniger als zwei Nobelpreise in Physik erhalten haben, sollen nicht
-- aufgelistet werden.
create view PhysikLand(land, anzahl) as
select p.land, count(*) as 'Anzahl'
from Nobelpreis n, Preisträger p
where n.pnr = p.pnr
	and n.Kategorie = 'Physik'
group by p.land
having count(*) >= 2;

select * from PhysikLand;

-- e) In welchen Jahren hat keine Person aus den USA einen Nobelpreis erhalten?
select n.jahr
from Nobelpreis n
where n.jahr not in (
					select distinct n2.jahr
					from Nobelpreis n2, Preisträger p
					where n2.pnr = p.pnr
						and p.land = 'USA'
					);


-- f) Wie viele Preisträger haben ihren Nobelpreis mit anderen Personen teilen müssen?
select count(distinct p1.pnr)
from Preisträger p1, Preisträger p2, Nobelpreis n1, Nobelpreis n1
where p1.pnr = n1.pnr
	and p2.pnr = n2.pnr
	and p1.pnr <> p2.pnr
	and n1.jahr = n2.jahr
	and n1.Kategorie = n2.Kategorie;

-- g) Ein Nobelpreis darf aus maximal drei Preisträger je Kategorie aufgeteilt werden. Wie
-- lässt sich dieses Constraint beschreiben?

create assertion maximal_drei_preistraeger_je_kategorie_jahr
	check (0 = (
			select count(*)
			from Nobelpreis
			group by n.kategogie, n.jahr
			having count(*) > 3));


alter table Nobelpreis add(
	constraint maximal_drei_preistraeger_je_kategorie_jahr
		check(NOT EXISTS (
				select n.kategogie, n.jahr
				from Nobelpreis n
				group by n.kategogie, n.jahr
				having count(*) > 3
			))
);

-- Aufgabe 6b):

create view beste_note(jahr, note)
as
select a.abschlussjahr, min(a.abschlussnote)
from alumni a
group by a.abschlussjahr;

select a.abschlussjahr, a.name
from alumni a, beste_note b
where a.abschlussnote = b.note
	and a.abschlussjahr = b.jahr
	

--and a.abschlussnote = any (select note from beste_note);















