# Zadatak 2

## Listanje direktorijuma

Napisati program koji lista sadrzaj direktorijuma. Putanja do jednog ili vise direktorijuma koje je potrebno izlistati se zadaje iz komandne linije.

Prilikom listanja sadrzaja, ispisuju se samo imena stavki, i to samo onih koje nisu skrivene (ne pocinju tackom).

Za listanje sadrzaja koristiti sistemske pozive: `opendir`, `readdir` i `closedir`.

### Rekurzija

Prosiriti prethodni program, tako da ako primi prvi parametar da je "-R" onda ispisuje rekurzivno sadrzaj direktorijuma koji je prosledjen.

### Ipak, svi

Prosiriti prethodni program, tako da ako je prvi parametar "-A", onda ispisuje sve fajlove, ukljucujuci i skrivene.

Za pocetak se moze napraviti verzija koja dozvoljava samo "-A" ili "-R", tj da se ne mogu koristiti zajedno.

Dalje, prosiriti program da moze da ocekuje vise razlicitih parametara. Dakle moguce je proslediti u program oba prethodna parametra zajedno.

### Podaci o fajlu

Napraviti program koji za prosledjene parametre ispisuje broj linkova, ako je putanja validna, naravno.

Koristiti poziv `stat` da bi dobili ovu informaciju.

## Napomene

Kod svih poziva obratiti paznju na moguce greske i obraditi ih. Narocito stvari tipa da fajl ne postoji, nesto ne moze da se otvori i slicno. Za takve stvari koristiti `perror` i/ili `errno` i povezane pozive kao sto je `strerror`.
