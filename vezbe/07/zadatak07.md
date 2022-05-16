# Vežbe 7 - procesi i pajpovi

## Proces i dete

Napisati program koji pravi jedno dete proces. Dete treba da ispise da je dete, a roditelj da je roditelj. Koristiti sistemski poziv `fork`.

Doterati da roditelj ceka da se dete zavrsi i ispise poruku o tome pre nego sto se i sam proces zavrsi. Koristiti sistemski poziv `wait`.

## Proces i dete pricaju

Napisati program baziran na prethodnom. Promeniti ga tako da dete posalje roditelju poruku, a roditelj tu poruku ispise na ekran. Koristiti pajpove za komunikaciju.

## Neefikasni faktorijel

Napraviti program koji racuna faktorijel datog broja tako sto pravi po jedan proces za racunanje svakog koraka. Svaki proces (osim poslednjeg) treba od deteta da dobije rezultat i da ga pomnozi sa adekvatnim brojem. Svi procesi (osim pocetnog) treba da rezultat vrate roditelju.

Za komunikaciju medju procesima koristiti pajpove.

## Korisne man stranice

* `man fork`
* `man wait`
* `man pipe`
* `man dup`
* `man 2 write`
* `man 2 read`
* `man close`
