# Projet1LINGI1252

Les codes sont tous munis de commentaires pour faciliter la compréhension à la lecture de ceux-ci.

# Organisation de notre référentiel
| Fichier | Description |
|  :---:  | :---         |
| Makefile | Inclus les commandes pour compiler notre programme |
| Fichiers .sh | Le code pour mesurer les performances des implementations de ce projet |
| Fichiers .py | Le code pour créer les graphes présent dans le rapport |
| header.h | Le fichier header commun pour les fichiers .c |
| main.c | La fonction main des autres codes .c |
| sem.c | Implémentation de notre sémaphore |
| verrou.c | Implémentation de nos verrous |
| Fichiers .c | Autres implémentations |
| Rapport_LINFO1252.pdf | Notre rapport pour ce projet |

# Explication des commandes accessible via Makefile
| Commande | Description |
|   :---:  | :---         |
| default | Le default est main ici |
| all | Une combinaison de tous les perf |
| main | Compile l'entièreté des codes en C |
| a.out | Lance le debugger gdb |
| perf1 | Mesure et affiche les performances de la tâche 1.5 |
| perf2 | Mesure et affiche les performances de la tâche 2.2 |
| perf1-2 | Mesure et affiche les performances de la tâche 2.5 |
| perfb | Mesure et affiche les performances de la tâche 2.6 |
| clean | Nettoie les fichiers crées par les autres commandes |
