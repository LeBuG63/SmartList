SmartList
=========

Un générateur de suite logique "intelligente".

Utilisation
-----------

./smartlist 10 "1 2 3"
./smartlist 42 "1.8 5.3"
./smartlist 20 "2 1 0.5"

Le premier argument est le totale de nombre à afficher
Le deuxième argument est la suite, le programme va s'en servir pour determiner une suite logique

Explication
-----------

Le programme va lire la suite, et en déduire son type:
- "UNKNOW": Il n'y aucune suite logique, du type ("1 2 5")
- "CONSTANT": La suite est constante ("1 1 1")
-	"GEOMETRIC": N est divisible par N-1 (2 1 0.5)
-	"ARITHMETIC": Repère si la suite peut additionner N et N-1 ou soustraire N et N-1

Ensuite, il fais le calcule pour les X membres de la suite.
