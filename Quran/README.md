# Projet MOBG5

Ce dépôt contient les sources du projet <Lecture Coran>.

## Description

Cette application permet de trouver les differents chapitre du 'Coran', les telecharger via un appel API si le chapitre n'est pas deja present en local. Une fois le chapitre obtenu, le text du chapitre est affiche phrase par phrase. 
Enfin, l'User peut egalement lire les informations du chapitre, sous format texte.

L'acceuil est compose des chapitres les plus lus.

## Persistance des données

L'application conserve les chapitres les plus lus ainsi que les chapitres telecharger. Ces informations sont pesistées dans la base de données locale de l'application


## Backend

L'application mobile appelle via des services web les backend Chapters, Content, Chapter_Info.

## Service rest

Pour collecter les données relatives aux chapitres, des appels aux services rest suivants sont effectués :

https://api.quran.com/api/v4/chapters?language=en

https://api.quran.com/api/v4/verses/by_chapter/{chapter_id}?language=en&words=true

https://api.quran.com/api/v4/chapters/{chapter_id}/info?language=en

## Auteur

**FERRAJ Yassine** g52075
