# Vežbe 8 - komplikovaniji pajpovi

## Neefikasni Fibonaci

Napisati program koji ucitava broj `n` i potom racuna i ispisuje `n`-ti
Fibonacijev broj.

```
f(n) = f(n-1) + f(n-2); f(1) = 1; f(0) = 0;
```

Program prvo treba da ucita broj `n` i napravi stablo procesa. Svaki proces u
ovom lancu ce pokusavati da izracuna `i`-ti Fibonacijev broj tako sto ce od svoja
dva deteta traziti da izracunaju `(i-1)`-i i `(i-2)`-i Fibonacijev broj.

Svaki proces osim najnizih treba da preuzme rezultat od svoja dva potomka i
sabere ih. Najnizi procesi treba odmah da vracaju rezultat.

Za medjuprocesnu komunikaciju koristiti pajpove. Obratiti narocito paznju
na cinjenicu da imamo vise dece na istom roditelju, te da sledece dete
nasledjuje i stvari koje smo namestili kad se pravilo prvo dete. Npr, ako
se pravi pajp za svako dete, drugo dete ce od roditelja naslediti i delove
pajpa od prvog deteta.

Potrebni sistemski pozivi su: `fork`, `pipe`, `dup`, `dup2`, `read`, `write`, `close`.
