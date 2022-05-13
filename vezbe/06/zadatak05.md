# Zadatak 6, izvršavanje drugih programa, novi procesi

## Lenjo listanje

Umesto da sami pisemo programe koji listaju fajlove, mozemo pozvati komande kao iz komandne linije.

Napisati program koji ispisuje sadrzaj trenutnog direktorijuma u dugackom formatu, nesortirano, bez vlasnika i grupe.

Pozdraviti korisnika porukom "sadrzaj trenutnog direktorijuma", a nakon ispisa dodati "kraj ispisa".

### Verzija sys

Za pocetak, koristiti poziv `system`.

### Verzija exec

Primecujemo da je `system` lep i jednostavan, ali da ima dosta ekstra delova koji se desavaju u pozadini koje hocemo da izbegnemo.

Videti kako resiti isti problem koristeci neki od poziva iz porodice `exec`.

Resavati u kopiji programa koju cemo zvati npr "ex".

### Resavanje nedostajucih poruka

Primecujemo da nedostaje finalna poruka o kraju. Izgleda da su oni ekstra delovi bili potrebni za nesto.

Popraviti program "ex", tako sto cemo dodati pravljenje novog procesa sa `fork`. Novi proces radi `exec`, a stari saceka da novi umre koristeci `wait` i onda ispisati svoju poruku.

