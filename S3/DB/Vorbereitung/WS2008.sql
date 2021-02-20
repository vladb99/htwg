-- Aufgabe 1:

-- c)
CREATE TABLE spiel
(
typName				varchar2(30) NOT NULL,
team1				varchar2(30) NOT NULL,
team2				varchar2(30) NOT NULL,
stadtName			varchar2(30) NOT NULL,
datum 				date,
CONSTRAINT spiel_pk PRIMARY KEY (typName, team1, team2),
CONSTRAINT spiel_fk1 FOREIGN KEY (typName) REFERENCES typ(typName),
CONSTRAINT spiel_fk2 FOREIGN KEY (team1) REFERENCES land(team1),
CONSTRAINT spiel_fk3 FOREIGN KEY (team2) REFERENCES land(team2),
CONSTRAINT unterschiedliche_teams CHECK (team1 != team2)
);

-- d)
alter table EM add(
	constraint em_alle_vier_jahre
		check(jahr % 4 = 0)
);

-- Aufgabe 2:

-- a) Wie vielen AOK-Patienten wurde bereits ein Bein eingegipst?
select count(distinct a.pnr)
from Leistung l, Arztbesuch a, durchfuehren d, Patient p
where l.lnr = d.Lnr
	and d.anr = a.anr
	and a.pnr = p.pnr
	and l.beschreibung = 'Bein eingipsen'
	and p.Krankenkasse = 'AOK';

-- b) Wie viele Patienten haben 2008 die Praxis nicht besucht?
select count(*)
from Patient p
where p.pnr not in (
				select a.pnr
				from Arztbesuch a
				where to_char(a.datum, 'YY') == '08'
			);

-- c) Stellen Sie die Anzahl der Masernfälle in 2007 pro Krankenkasse zusammen.
select p.Krankenkasse, count(*)
from Patient p, Arztbesuch a
where p.pnr = a.pnr
	and a.diagnose = 'Masern'
	and to_char(a.datum, 'YY') = '07'
group by p.Krankenkasse;

-- d) Welche Leistung hat die meisten Kosten verursacht?
create view kosten(leistung, kosten) as
select l.beschreibung, sum(l.kosten)
from Leistung l, durchfuehren d, Arztbesuch a
where l.lnr = d.lnr
	and d.anr = a.anr
group by l.beschreibung;

select k.leistung
from kosten k
where k.kosten = (select max(k2.kosten) from kosten k2);

-- e) Wie viele Personen sind bereits mehrmals an Masern erkrankt?
select count(distinct a1.pnr)
from Arztbesuch a1, Arztbesuch a2
where a1.pnr = a2.pnr
	and a1.anr != a2.anr
	and a.diagnose = 'Masern';


-- Aufgabe 3:
-- Geben sie die PersonNr aller noch lebenden Vorfahren von 'Jogi Löw' in der Syntax von
-- Oracle9i aus.
select p1.personNr
from Person p1, Eltern e1
where p1.personNr = e1.elternteil
	and p1.lebt_noch = 'ja'
connect by p1.personNr = prior e1.elternteil 
start with p1.PersonNr = 
	(
	select elternteil
	from Person p2, Eltern e2
	where p2.personNr = e2.kind
		and p2.Name = 'Jogi Löw'
	);

-- Aufgabe 5:
-- SQL-Injection kann dadurch vermieden werden, dass man z.B die Eingabedaten auf Länge und
-- Sonderzeichen prüft. Weitere Möglichkeiten wäre das zuweisen von Privilegien (Authentifikation)
-- oder Parametrisierte Kommandos. 

-- Aufgabe 6:

-- a) Korrelation, führt zu langsame Zeiten

-- b):

select Name
from Patient p, Arztbesuch a1, Arztbesuch a2
where p.pnr = a1.pnr
	and a1.pnr = a2.pnr
	and a1.diagnose = 'Beinbruch'
	and a2.diagnose = 'Masern';



















