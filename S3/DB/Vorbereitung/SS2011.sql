-- Aufgabe 2

-- a) Welche Weinsorte wird nie in 2.0-Flaschen verkauft?
select distinct w.Weinsorte
from Wein w
where w.wnr not in (
					select distinct f.wnr
					from flaschenpreis f
					where f.liter = 2.0
					);


-- b) Geben Sie alle Jahrgänge an, zusammen mit der Anzahl der unterschiedlichen
-- Weinsorten, die aus diesem Jahrgang angeboten werden.
select w.jahrgang, count(distinct w.weinsorte) as 'Anzahl'
from Wein w, Flaschenpreis f
where w.wnr = f.wnr
group by w.jahrgang;


-- c) Welchen durchschnittlichen Preis für 0.7-Liter Weinflaschen mit deutschen Weinen
-- erzielt?

select avg(f.Preis)
from Wein w, Flaschenpreis f
where w.wnr = f.wnr
	and w.land = 'Deutschland'
	and f.liter = 0.7;


-- d) Für wie viele Weine ist der Preis der 1.0-Liter Flasche günstiger als der Preis der
-- 0.7-Liter Flasche?

select count(distinct wnr)
from Flaschenpreis f1
where f1.liter = 1.0
	and f1.preis < (select f2.preis
					from Flaschenpreis f2
					where f2.liter = 0.7
						and f2.wnr = f1.wnr);


-- e) Welches Land bietet die höchste Anzahl verschiedener Weinsorten an?

create view landAngebot(land, anzahl)
as
select w.land, count(distinct w.weinsorte)
from Wein w
group by w.land;

select land
from landAngebot
where anzahl = (select max(anzahl) from landAngebot);

-- f) Häufig gilt die Aussage „Ältere Weine sind teurer“. Zählen Sie, in wie vielen Fällen
-- diese Aussage gilt. Es sollen hier nur Preise von 0.7-Liter Flaschen betrachtet
-- werden.

select count(*)
from Wein w1, Flaschenpreis f1
where w1.wnr = f1.wnr
	and f1.liter = 0.7
	and f1.preis > all (select f2.preis
						from Wein w2, Flaschenpreis f2
						where w2.wnr = f2.wnr
							and f2.liter = 0.7
							and w2.jahr > w1.jahr
		);


-- g) Definieren Sie einen View, der den durchschnittlichen Preis pro Liter aller Weine
-- eines Jahrgangs darstellt.

create view avg_preis(jahr, preis) as
select w1.jahrgang, avg(f1.preis / f1.liter)
from Wein w1, Flaschenpreis f1
where w1.wnr = f1.wnr
group by w1.jahrgang;

-- Aufgabe 6 b) :

select count(*)
from Wein w1, Flaschenpreis p1, Wein w2, Flaschenpreis p2
where w1.wnr = p1.wn2
	and w2.wnr = p2.wnr
	and w1.land = 'Frankreich'
	and w2.land = 'Deutschland'
	and w1.jahrgang = w2.jahrgang
	and p1.liter = p2.liter
	and p1.preis < p2.preis;












