Nume, prenume: Cocor, Miruna-Alondra
Grupa, seria: 312, CA

Data inceperii temei : 30.04.2019
Data finalizarii temei : 4.05.2019

Problemele intampinate :
Tema a fost destul de stricta, foarte multe lucruri de
luat in calcul si foarte multe erori datorate timpului
si memoriei utilizate. Testele 7, 8, 9, 10 nu mi-au
rulat pe checker-ul local, desi manual imi
rulau. Calcularea distantei dintre intersectii
a mai fost o problema. 

Algoritmul utilizat:
Am utilizat 2 clase, Hashtable si Graph, implementate
pe parcursul semestrului in cadrul laboratoarelor,
adaugand o metoda clasei Graph pentru calcularea
distantei. Separat de aceste clase, am mai implementat
o functie de hash. Pe parcursul task-urilor am mai
utilizator un vector de strings pentru memorarea
intersectiilor si cateva variabile pentru citirea din
fisier. M-am folosit de hashtable pentru a obtine
indecsii intersectiilor din graf si pentru realizarea
grafului.
In cadrul primului task, am utilizat hashtable-ul pentru
indecsi si am realizat graful, verificand apoi daca exista
drum sau nu intre intersectiile citite din fisier. Am folosit
metoda din Graph, Path care returna o stiva ce continea nodurile
parcurse in drumul de la destinatie la sursa, sau o stiva goala
daca nu exista drum.
Al doilea task, asemanator primului, a constat in citirea
unui numar de perechi de intersectii pentru care trebuia
sa afisez lungimea drumului daca exista sau nu. Am folosit
o metoda din clasa Graph, distance, care imi returna aceasta
distanta sau -1 daca nu exista drum.
Al treilea task reprezenta o serie de modificari ce trebuiau
realizate in graf si am utilizat metode din graf care stergeau
un drum, realizau unul sau il faceau bidirectional sau trebuia
sa afisez distanta dintre intersectii.
Complexitatea temei : 8
