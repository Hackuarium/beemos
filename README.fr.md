<p align="center">
  <img width="400" height="400" src="common/images/logoBeeMoS.svg">
</p>

# BeeMoS - Système de monitorage d'abeilles
# (En développement)

*[Read this in english](README.md)*

Le projet BeeMos est un système de monitorage de ruches développé au laboratoire d'open science Hackuarium, à Renens, Suisse.

# Objectifs 
Construire et programmer un système open source de monitorage d'abeilles avec les objectifs suivants:

- [x] Suivre l'activité des ruches pour étudier le comportement des abeilles et surveiller leur santé.
- [ ] Détecter les changements instantanés et progressifs dans le poids de la ruche au cours du temps (essaimage, production de miel, ...).
- [ ] Mesurer des variables environnemntales dont l'humidité, la température, la lumière et la pression atmosphérique pour comprendre leur effet sur les abeilles.
- [ ] Envoyer les données à un serveur à distance pour les analyser, visualiser et avertir l'utilisateur si quelque chose d'anormal se produit.

# Modules
Pour parvenir aux objectifs ci-dessus, le projet respecte une architecture modulaire avec différents composants physiques:

**Compteur**: Compte les abeilles qui entrent et sortent de la ruche au cours du temps en utilisant des senseurs infrarouge. [_(Détails techniques_)](counter-i2c/README.md)

**Balance**: Pèse la ruche périodiquement en utilisant 4 cellules de charge.

**Station météo**: Enregistre la température, l'humidité, la luminosité et la pression atmosphérique à l'extérieur des ruches. [_(Détails techniques)_](weather-i2c/README.md)

**Carte maître**: Communique avec tous les autres appareils par I2C et envoie les données de la ruche à un serveur à distance. La communication à distance est effectuée par un module à carte SIM. Mesure aussi la température et l'humidité à l'intérieur de la ruche. [_(Détails techniques)_](master-simple/README.md)


# Etat du projet
Nous avons conçu et commandé les circuits imprimés pour le compteur d'abeilles, la station météo, la balance et la carte maître. Tous les éléments de la station météo et du compteur sont soudés. Nous devrions recevoir les circuits imprimés pour la balance et la carte maître dans quelques jours. Le code Arduino est écrit pour compter les abeilles qui entrent et sortent de la ruche et les enregistrer pour toutes les portes en utilisant du multithreading. En utilisant une découpeuse laser, nous avons aussi construit un boîtier en bois qui sert à contenir le circuit imprimé du compteur d'abeilles. Ce boîtier comprend 8 portes individuelles que les abeilles peuvent emprunter pour transiter entre l'intérieur et l'extérieur de la ruche. Nous avons effectué quelques essais sur le terrain pour évaluer la précision du compteur (Plus de détails bientôt) mais nous devons encore effectuer quelquec calibration physiques et logicielles pour le faire fonctionner.

<p align="center">
  <img width="800" src="common/images/CounterFieldTest.jpg">
</p>


La station météo est aussi assemblée et programmée. Elle peut maintenant afficher la température, l'humidité, la pression atmosphérique et la luminosité relative. 

La prochaine étape sera de faire fonctionner et calibrer le compteur d'abeille ainsi que de souder les éléments de la balance et de la carte maître avant de les programmer.

# Ressources additionnelles 

Tous les codes, spécifications et schémas des circuits imprimés ainsi que la documentation sont disponible sur le [répertoire github BeeMoS](https://github.com/Hackuarium/beemos) (uniquement en anglais)

Voir ce projet sur [CADLAB.io](https://cadlab.io/project/1029)
