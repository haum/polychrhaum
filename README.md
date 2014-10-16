# PolychrHAUM

PolychrHAUM est un appareil conçu au sein de l'association HAUM (http://haum.org/) qui n'a pas de but précis, sinon d'être hacké.
Il s'agit d'un boîtier qui dispose de 150 leds multicolores et deux boutons pour les utilisateurs.

Le premier projet réalisé sur cette plateforme est un Pong en une dimension.

## Dépôt

Ce dépôt contient la bibliothèque Arduino facilitant l'interaction avec l'appareil.

## Émulateur

Les sources contiennent un émulateur pour le développement et tests sur PC.

Celui-ci permet d'essayer différents programmes sans avoir accès au système électronique.
Il faut néanmoins garder en tête que la cible principale est un microcontrôleur 8 bits avec assez peu de mémoire vive.

Les boutons sont émulés par des touches de calvier :

 - Flèche Gauche ou touche Q sur clavier AZERTY = bouton 1
 - Flèche Droite ou touche D sur clavier AZERTY = bouton 2

Une touche permet aussi de quitter l'émulateur :

 - Échap = Quitter l'émulateur
 - La touche Espace permet de simuler l'appui sur le bouton POWER.

Les leds sont émulés par des pixels dans une fenêtre.

Les caractères envoyés sur la liaison série sont redirigés vers la sortie standard du programme.

## Compilation

Voir le dépôt "polychrhaum-examples".

## Licence

Le projet est fourni sous licence MIT.

C'est une licence libre qui vous permet par exemple :
 - de le copier,
 - de l'étudier,
 - de l'adapter à vos besoins,
 - de le redistribuer

Nous vous encourageons vivement à forker et partager !
