-- Teil 5 --
CREATE OR REPLACE VIEW kundenstatistik(knr, anzahl_buchungen, anzahl_stornierungen, summe_zahlungen) AS
SELECT kunde.knr, count(distinct buchung.bnr) as "Anzahl Buchungen", count(stornierung.bnr) as "Anzahl stornierter Buchungen", sum(nvl(anzahlung.betrag, 0)) as "Summe aller Zahlungen"
FROM kunde LEFT OUTER JOIN buchung on kunde.knr = buchung.knr
    LEFT OUTER JOIN stornierung on kunde.knr = stornierung.knr
    LEFT OUTER JOIN anzahlung on buchung.bnr = anzahlung.bnr
GROUP BY kunde.knr;

SELECT * FROM kundenstatistik;

-- Just to see all the combinations
SELECT *
FROM kunde LEFT OUTER JOIN buchung on kunde.knr = buchung.knr
    LEFT OUTER JOIN stornierung on kunde.knr = stornierung.knr
    LEFT OUTER JOIN anzahlung on buchung.bnr = anzahlung.bnr;