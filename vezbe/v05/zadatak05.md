# Zadatak 5 - prave putanje, filtriranja i premestanja

## Podaci o fajlu

Napraviti program koji za prosledjenu putanju nalazi "pravu" putanju, tj apsolutnu kanonicku putanju. To znaci bez simbolickih linkova, "." i ".." delova u putanji i slicno.

Za ovo se moze koristiti poziv `realpath`.

Ako nije dat parametar preko komandne linije, koristiti trenutni direktorijum. Moze se iskoristiti poziv `getcwd` za ove potrebe.

Takodje ispisati koliko je "duboko" folder u toj putanji, tj koliko ima foldera od root-a dotle. Root (/) je dubina 0, i svi fajlovi direktno tamo isto imaju dubinu 0.

## Veliki fajlovi

Ispisati sadrzaj prosledjenog direktorijuma. Za svaki fajl ispisati ime, broj linkova i velicinu u KB.

Ime direktorijuma se dobija kao parametar sa komandne linije.

Obratiti paznju u kojoj velicini se dobijaju podaci o velicini od poziva `stat`.

Ispisati samo fajlove vece od 100KB.

Ako postoji drugi parametar i moze se prepoznati kao broj, ispisati samo fajlove vece od toliko KB. Koristiti npr `strtol` za konverziju i proveriti da li je bilo grešaka.

## Premestanje

Program radi sa bar tri parametra - prvi je ime pocetnog direktorijuma, drugi je ciljni direktorijum, a svi ostali su imena fajlove koji ce se premestati.

Program treba iz prvog direktorijuma da premesti fajlove u drugi. Ako drugi ne postoji treba ga napraviti.

Pri premestanju, podesiti da je ciljni direktorijum takav da ima prava pisanja samo za grupu (ne za korisnika i ostale), a da korisnik moze da ga cita i izvrsava, dok ostali ne mogu nista.

Fajlove koje premestamo postaviti sa analognim privilegijama, ali naravno da ne budu izvrsni.

Ako fajl ne postoji u pocetnom direktorijumu prijaviti problem.

Ako fajlovi sa tim imenom vec postoje u ciljnom direktorijumu, samo ih "pregaziti".

Koristiti sistemski poziv `rename` za premestanja, `chmod` za menjanje privilegija i `mkdir` za pravljenje foldera. Moze se koristiti `access` za proveru da li postoji folder, ili neki drugi mehanizam, npr probati da se napravi, pa obraditi adekvatno ako se vrati ta greska.
