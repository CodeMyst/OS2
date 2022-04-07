# Zadatak 4

## Selektivno listanje direktorijuma

Napraviti program koji ispisuje podatke o zadatim direktorijuma, ali selektivno. Za pocetak je dosta samo ispisivati imena fajlova.

Preporucuje se kopiranje resenja sa prethodnih zadataka i prilagodjavanje novim potrebama.

Napraviti program tako da menja svoje ponasanje u skladu sa prvim argumentom.

Ako je dat argument "--sort" ispisati sve sortirano azbucno.

Ako je dat argument "--Sa" ispisati samo fajlove koji pocinju sa slovom "a"

Ako je dat argument "--SN" ispisati samo fajlove koji pocinju sa slovom "N"

Idealno, trebalo bi generalizovati komandu "--S" tako da moze da prihvati bilo koje pocetno slovo. Komanda bi onda bila oblika: "--S_".

Pogledati opis poziva `scandir` za implementaciju ovih detalja.

Dodati ispise datuma promene (i drugih podataka iz prethodnog zadatka, ali trenuno nisu bitni).

Ako je dat argument "--p2020" ispisati samo fajlove koji su menjani nakon 2020, tj od 1 jan 2021 nadalje.

Ako je dat argument "--mart" ispisati samo fajlove koji su menjani poslednji put u martu mesecu, nebitno koje godine.

Za ove zadatke su potrebni dodatni podaci koji se mogu dobiti preko poziva stat.

**(Dodatak za domaci)** Dodatno prosiriti komandu "--S" da moze da prihvati listu od N pocetnih slova. Primer bi bio "--SaBc", u cijem slucaju bi se ispisivali fajlovi cija imena koji pocinju karakterima 'a', 'B' ili 'c'.
