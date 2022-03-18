README
void adaugaFinal(ELEM* head, Country* data)
Functia adauga un element in lista dublu inlantuira dupa elementul pe care il primeste.


int putere_2(int nr_tari)
Functia calculeaza numarul maxim, putere a lui doi, care este mai mic decat numarul dat.


float scor_initial_minim(ELEM *head)
Functia calculeaza scorul initial minim al tarilor din lista, ca medie aritmetica a scorurilor jucatorilor.



void eliminare_tari_puterea_lui_2(ELEM *head, int nr_tari)
Functia calculeaza scorul initial al tarii curente pentru a-l compara cu scorul initial minim al tuturor tarilor din lista, daca scorul este egal cu scorul minim,
tara respectiva este scoasa din lista, aslfel lista ramane la fel. Operatia se repeta pana cand numarul tarilor ramase in lista este egal cu numarul furnizat de 
funtia putere_2.


void push(ESTIV**top, Country data)
Functie pentru adugarea de date in stiva.


int isEmpty(ESTIV*top)
Functie pentru a verifica daca stiva este goala;


Country pop(ESTIV**top)
Functie pentru a scoate date din stiva.



Queue* createQueue()
Functie pentru crearea unei cozi.


void enQueue(Queue *q,Meci data)
Functie pentru adaugarea de date in coada.



int isEmpty1(Queue*q)
Functie pentru a verifica daca este goala coada. 

Meci deQueue(Queue *q)
Functie pentru a scoate date din coada.


int cel_mai_mare_scor(Country tara)
Functie pentru a determina care este jucatorul cu cel mai mare scor dintr-o tara.



int nr_elemente_stiva(ESTIV *top)
Functie care returneaza numarul de elemente din stiva.


BST* newNode(Player *data)
BST* insert(BST* node, Player *key)
Funtii pentru adugarea unui nod in BST, ca frunza a arborelui existent. Cand adauga un nod, mai intai verifica daca jucatorul din nodul precedent
are acelasi scor ca cel care ar urma sa fie adaugat. Daca au acelasi scor, va fi introdus in arbore cel cu numele de familie mai mic din punct de 
vedere lexicografic.


void inorder(BST*root,FILE *rezultate)
Funtie pentru parcurgerea descrescatoare a arborelui, afisand jucatorii din noduri.


ESTIV winner(ESTIV *top,int castigatori,List *head,FILE *rezultate)
Functia creaza o coada pentru meciurile din fiecare tara, 2 cate 2, in meci sunt actualizate scorurile jucatorilor participanti. Odata ce este parcursa
stiva, se inchide o etapa, tarile care pierd fiind eliminate. Operatia se repeta pentru tarile ramase in stiva, reprezentand de fiecare data o noua etapa.
Functia se opreste cand in stiva ramane o singura tara. 
De asemenea, cand ajunge la ultimele 4 tari, introduce jucatorii celor 4 tari intr-o lista preliminara.

void afisare(ELEM *head,FILE *rezultate)
Functie pentru afisarea elementelor din lista dublu inlantuita.


int exista_jucatori(BST* root, char *first_name, char *last_name)
Functia verifica daca jucatorul citit se afla in arborele binar creat.


int jucatori_intermediari(BST*root,int scor1, int scor2)
Functia returneaza numarul de jucatori care au scorul intermediar intre scorurile celor doi jucatori cititi. 

In main() citesc conditiile pentru rezolvarea cerintelor si datele celor doi jucatori pentru cerinta 5.
Daca se rezolva cerinta 1 citeste din fisier datele pentru fiecare tara, si le introduce in lista dublu inlantuita, circulara, cu santinela. 
In cazul in care nu se rezolva cerinta 2, se vor afisa tarile din lista.
Daca se rezolva cerinta 2, apeleaza funtia eliminare_tari_puterea_lui_2, pentru a reduce numarul de tari la cel mai mare numar, putere a lui 2,
mai mic decat numarul initial de tari. Dupa aceea, afiseaza tarile din lista modificata.
Daca se rezolva cerinta 3, se introduc datele din lista modificata la cerinta 2, intr-o stiva. Dupa aceea, creaza lista intermediara si apeleaza functia winner,
care afiseaza meciurile si tarile castigatoare din fiecare etapa, si introduce in lista jucatorii din ultimele 4 tari castigatoare.
Daca se rezolva cerinta 4, se introduc datele din lista intermediara intr-un BST; si afiseza datele din BST, in ordinea descrescatoare a scorurilor jucatorilor.
Daca se rezolva cerinta 5, verifica daca cei doi jucatori cititi din fisierul cu cerinte se afla in BST-ul creat la cerinta 4, daca se afla, afiseaza numarul 
de jucatori care au scorurile cuprinse intre scorurile celor doi jucatori din cerinta. In caz contrar, afiseaza care jucator nu a fost gasit in BST.