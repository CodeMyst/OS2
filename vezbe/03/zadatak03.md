# Zadatak 3

## Sadrzaj direktorijuma sa dodatnim podacima

Napisati program koji prikazuje sadrzaj direktorijuma i podatke o svim fajlovima. Putanja do jednog ili vise direktorijuma ciji sadrzaj je potrebno prikazati se zadaje iz komandne linije.

Od podataka se prikazuju tip fajla, prava pristupa, broj linkova, velicina u blokovima, datum i vreme poslednje izmene i ime fajla.

U sustini treba ispisati podatke kao sto bi uradila komanda:

`ls -lgGU --time-style=long-iso`

redom su parametri za dugacki ispis; ne ispisivanje vlasnika; ne ispisivanje grupe; nesortiranost izlaza; podesavanje ispisa vremena.

Za listanje sadrzaja direktorijuma koristiti sisetmske pozive `opendir`, `readdir` i `closedir`, a za dobijanje informacija o fajlu koristiti sistemski poziv `stat`. Za konverzije vremena koristiti localtime.

Korisne konstante se mogu naci i u man-u za inode.

Korisne informacije: man opendir man readdir man closedir man 2 stat man localtime
