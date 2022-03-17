# embedded-machine-learning


Objectifs :

- implémenter avec le moins de ressources possibles un classificateur sur la cible embarquée (dans notre cas Raspberry Pi 4).
- Veiller à donner la preuve que le code fonctionne sur la cible.
- Mesurer la taille de des exécutables et évaluer les besoins en mémoire à l'exécution.
- Programmer une extraction de paramètres en C++ performante :
efficace dans son exécution (1 Go de données musicales peuvent être traitées en 60 secondes ou moins),
minimale en termes de paramètres significatifs générés pour l'apprentissage.  
- Programmer un arbre de décision :
générer automatiquement le code C++ à compiler pour exécuter la prise de décision sur la cible depuis un CART Python. 
- proposer une version C++-20 de CART à partir de celle proposée en Python.
- proposer un algorithme de type Random Forest à partir du code de CART et Python et/ou C++.
- Programmer une SVM :
- Implémenter la SVM en C++ : apprentissage et prédiction. Bien segmenter les phases d'extraction, d'apprentissage et de prédiction dans le code.
Chercher à limiter le nombre de paramètres nécessaires à la classification en cherchant les paramètres les plus significatifs.
- Implémenter la prédiction un contre tous et un contre un.
- Programmer un réseau de neurones :
- Implémenter un ANN en C++ (sans backpropagation !), on considèrera avec attention le fait d'utiliser l'OOP.
- Comparer une approche SVM à une approche NN.
- Comparer votre implémentation avec TensorFlow sur Raspberry Pi.
