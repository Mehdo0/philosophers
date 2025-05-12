# 🧠 Philosophers

## 📘 Description

**Philosophers** est un projet de l'école 42 basé sur le problème classique des philosophes mangeant. Le but est de simuler des philosophes assis autour d'une table, alternant entre manger, penser et dormir, tout en partageant des fourchettes. Le défi consiste à gérer l'accès concurrent aux ressources partagées (les fourchettes) en utilisant des mécanismes de synchronisation pour éviter les interblocages et les conditions de concurrence.

## 🎯 Objectifs pédagogiques

- Comprendre et implémenter la programmation concurrente avec des threads et des processus.
- Utiliser des mutex et des sémaphores pour synchroniser l'accès aux ressources partagées.
- Gérer les problèmes de synchronisation tels que les interblocages (deadlocks) et les conditions de famine (starvation).

## ⚙️ Compilation

Pour compiler le projet :

```bash
make
🚀 Utilisation

./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
number_of_philosophers: Nombre de philosophes et de fourchettes.

time_to_die: Temps en millisecondes avant qu'un philosophe meure s'il ne commence pas à manger.

time_to_eat: Temps en millisecondes qu'un philosophe met à manger.

time_to_sleep: Temps en millisecondes qu'un philosophe passe à dormir.

number_of_times_each_philosopher_must_eat (optionnel): Nombre de fois que chaque philosophe doit manger avant que la simulation se termine.

🧪 Exemple

./philo 5 800 200 200 3
Ce qui signifie :

5 philosophes

800ms avant qu'un philosophe meure s'il ne mange pas

200ms pour manger

200ms pour dormir

Chaque philosophe doit manger au moins 3 fois

📝 Sortie attendue
Le programme affiche les actions de chaque philosophe avec un horodatage :

csharp
Copier
Modifier
[0001] 1 has taken a fork
[0002] 1 has taken a fork
[0003] 1 is eating
[0203] 1 is sleeping
[0403] 1 is thinking
...
🧩 Bonus (optionnel)
Implémentation avec des processus et des sémaphores.

Gestion avancée des erreurs et des cas limites.

Visualisation de la simulation.

📁 Structure du projet

philosophers/
├── philo/          # Partie obligatoire (threads et mutex)
├── philo_bonus/    # Partie bonus (processus et sémaphores)
├── Makefile
└── README.md
📚 Ressources utiles
[Sujet du projet sur Intra 42]

[Guide sur les threads et les mutex]

[Guide sur les processus et les sémaphores]

© 2025 - Projet Philosophers - École 42