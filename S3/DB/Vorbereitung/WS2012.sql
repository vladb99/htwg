-- Aufgabe 2:

-- a) Welche Sendungen hatten noch nie eine Einschaltquote von mindestens 40% ?
select s.name
from Sendung s
where s.sendungNr not in (
					select e.sendungNr
					from Einschaltquote e
					where e.quote >= 40
						);


-- b) Welche Sendungen hatten am 03.07.12 eine höhere Einschaltquote als „Tatort“?
select s2.name
from Sendung s1, Einschaltquote e1, Sendung s2, Einschaltquote e2
where s1.sendungNr = e1.sendungNr
	and s2.sendungNr = e2.sendungNr
	and s1.name = 'Tatort'
	and e1.datum = to_date('03.07.2012', 'DD.MM.YY')
	and e2.datum = to_date('03.07.2012', 'DD.MM.YY')
	and e2.quote > e1.quote;

-- c) An wie vielen Tagen hatte „Tagesthemen“ eine Einschaltquote von mindestens 60% ?
select count(*) as 'Anzahl Tagen'
from Sendung s, Einschaltquote e
where s.sendungNr = e.sendungNr
	and s.name = 'Tagesthemen'
	and e.quote >= 60;

-- d) Geben Sie alle Sender mit ihren durchschnittlichen Einschaltquoten im Jahre 2012 an.
-- Sortieren Sie die Ausgabe absteigend nach der durchschnittlichen Einschaltquote.
select s.name, avg(e.quote)
from Sender s, Einschaltquote e
where s.senderNr = e.senderNr
	and to_char(e.datum, 'YY') = '12'
group by s.name
order by avg(e.quote) desc;

-- e) Welche Sendung hatte die größte Differenz bezüglich minimaler und maximaler
-- Einschaltquote im Jahr 2012?
create view diff_min_max(name, diff) as
select s.name, (max(e.quote) - min(e.quote)) as 'Differenz'
from Sendung s, Einschaltquote e
where s.sendungNr = e.sendungNr
	and to_char(e.datum, 'YY') = '12'
group by s.name;

select name
from diff_min_max d1
where d1.diff = (select max(d2.diff) from diff_min_max d2);


-- f) Welche RTL-Sendung hatte 2012 im Durchschnitt die höchste Einschaltquote?
create view rtl_quote(sendungNr, quote) as
select e.sendungNr, avg(e.quote)
from Sender s, Einschaltquote e
where s.senderNr = e.senderNr
	and s.name = 'RTL'
	and to_char(e.datum, 'YY') = '12'
group by e.sendungNr;

select s.name
from rtl_quote r1, Sendung s
where r1.sendungNr = s.sendungNr
	and r1.quote = (select max(r2.quote) from rtl_quote r2);


-- g) Definieren Sie einen View, der die durchschnittliche Einschaltquote aller ARDSendungen pro Kalendertag des Jahres 2012 beinhaltet.
create view ARDSendungen(datum, quote) as
select e.datum, avg(e.quote)
from Sender s, Einschaltquote e
where s.senderNr = e.senderNr
	and s.name = 'ARD'
	and to_char(e.datum, 'YY') = '12'
group by e.datum;

-- h) Wie viele Sendungen werden von mehr als einem Sender gesendet?
select count(*)
from Einschaltquote e
group by e.sendungNr
having count(distinct e.senderNr) > 1;

-- ODER

select count(distinct e1.sendungNr)
from Einschaltquote e1, Einschaltquote e2
where e1.sendungNr = e2.sendungNr
	and e1.senderNr != e2.senderNr;
























