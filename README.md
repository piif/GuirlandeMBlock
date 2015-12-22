Guirlande 2015
==============

Présentation
-----

Ce projet est issu des activités proposées dans le cadre du "club programmation et robotique" au collège Jean Demailly de Seclin.

Dans ce cadre, le logiciel MBlock est utilisé pour initier à la programmation des élèves de la 6ème à la 3ème.

Lors de l'année scolaire 2014-2015, l'une des activité à consisté à simuler une guirlande de 60 lumières de couleur, dans Scratch, puis contrôler une vraie guirlande à travers un arduino et une extension scratch, puis transférer le programme résultant dans un arduino, à travers un code expérimental de conversion de Scratch vers C.

En fin d'année scolaire, d'autres activités basées sur des MakeBlock nous ont amené à reprendre cette Guirlande en utilisant MBlco qui permet aussi de convertir un programme en code C transférable sur Arduino.

Ce dépot git reprend le résultat de cette activité, avec en plus un programme principal permettant d'enchainer les animations réalisées par les élèves.

Comment ça marche
-----

Chaque élève volontaire (et les encadrants) a réalisé une animation dans MBlock.

Comme MBlock ne permet pas de copier/coller entre programmes, on a ouvert chaque programme dans Scratch Online afin de tous les copier dans un seul projet Scratch qu'on a ensuite rouvert dans MBlock pour le convertir en code Arduino.
Le résultat est visible [ici](https://scratch.mit.edu/projects/90682074/)

Après quelques adaptations (principalement le renommage de quelques variables et la conversion des "double" en "int") on obtient le fichier animations.ino

Le fichier GuirlandeMBlock.ino est un programme qui effectue 2 choses :

 * enchainer les animations au hasard
 * lancer explicitement une animation lorsque son numéro est reçu par le port série

Pour permettre d'interrompre l'animation en cours lors de la réception d'un ordre, on teste l'arrivée de commande à chaque appel de la fonction qui change l'état d'une lumière.
Un hack à coup de longjmp permet alors d'interrompre l'animation en cours.

La version complète tourne sur un Yun sur lequel un portail captif permet de choisir une animation depuis une page web qui en affiche la liste.

ledStrip
-----

Le dossier ledStrip contient un mix entre la librairie de chez adafruit (Adafruit_NeoPixel) et le code inclu dans le firmware de mblock.
La version AdaFruit ne marche pas avec un Yun alors que celle de mblock oui.
Comme le coeur du protocole WS2812 est écrit en assembleur, j'ai pas cherché en profondeur ce qui déconnait, mais comme ça, cç marche.
