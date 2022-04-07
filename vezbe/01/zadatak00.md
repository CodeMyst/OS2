# Zadatak 0

## Upoznavanje sa komandnom linijom

Pozeljno je da su studenti upozati sa osnovama rada u terminalu - da znaju da navigiraju kroz fajl sistem, prave foldere i podfoldere, kompajliraju zadatke i pokrecu ih.

Upoznati se sa komandama `pwd`, `ls`, `cd`, `mkdir`, `rmdir`, `man`, `cp`, `mv`, `ln`.

### Kreiranje foldera

Napraviti sledecu strukturu foldera iz komandne linije:

```
   fax
   +--os1
   +--os2
   |  +--predavanja
   |  +--vezbe
   +--spa1
   |  +--liste
   +--spa2
   |  +--stabla
   +--sp-pu
   |  +--predavanja
   |  +--vezbe
```

Uveriti se da je dobra struktura direktorijuma. Koristiti `ls -R` ili `komandu tree`.

### Kopiranje fajlova

Koristeci editor `joe` (ili neki drugi), napraviti mali fajl "pozdrav.txt", sa sadrzajem "pozdrav".

Iskopirati ga u folder fax/os2/vezbe.

Otici u taj folder i kopirati fajl, tako da se nova kopija nalazi u istom folderu sa imenom "pozdrav2.txt".

Napraviti meki link sa imenom "meki.txt" na "pozdrav.txt".

Vratiti se u pocetni folder. Napraviti folder "novi" i u njega prekopirati folder vezbe u koji smo malopre kopirali fajl, zajedno sa tim fajlom. Koristiti jednu komadnu za celu operaciju.

Iz pocetnog foldera, napraviti tvrdi link sa imenom "tvrdi.txt" na originalni "pozdrav.txt".
