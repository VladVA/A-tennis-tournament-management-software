#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include<math.h>
#define MAX_LENGTH 20

typedef struct Player
{
    char *last_name;
    char *first_name;
    int score;
} Player;

typedef struct Country
{
    char *name;
    int nr_players;
    int global_score;
    Player *players;
} Country;

typedef struct element //structura pentru elementele din lista dublu inlantuita
{
    Country *data;
    struct element *next,*prev;
} ELEM;

typedef struct element_lista //structura pentru elementele din lista simplu inlantuita
{
    Player *data;
    struct element_lista *next;
} List;

typedef struct element_arbore //structura pentru elementele din BST
{
    Player *data;
    struct element_arbore *left,*right;
} BST;

typedef struct element_stiva //structura pentru elementle din stiva
{
    Country data;
    struct element_stiva *next;
} ESTIV;

typedef struct meci //structura pentru datele meciurilor
{
    Player *a,*b;
} Meci;

typedef struct element_coada //structura pentru datele din coada
{
    Meci data;
    struct element_coada *next;
} EQueue;

typedef struct coada //structura pentru elementele din coada
{
    EQueue *front, *rear;
} Queue;

void adaugaFinal(ELEM* head, Country* data) //adauga un element in lista dublu inlantuita
{
    ELEM* new_node =malloc(sizeof(ELEM));
    new_node->data = data;
    new_node->next = head;
    (head)->prev->next = new_node; //adauga dupa elementul pe care il primeste
    new_node->prev=head->prev;
    head->prev=new_node;
}

int putere_2(int nr_tari)
{
    int nr_tari_ramase=2;
    while(nr_tari_ramase <= nr_tari)//numarul maxuim care este mai mic decat numarul de tari date
        nr_tari_ramase*=2;
    return nr_tari_ramase/2; //returneaza numarul maxim, putere a lui 2
}

float scor_initial_minim(ELEM *head) //calculeaza scorul initial minim din lista dublu inlantuita
{
    ELEM *current = head->next;
    float min=0,minc=0;
    int i;
    if(current == head)
    {
        return 0;
    }
    else
    {
        for(i=0; i<current->data->nr_players; i++) //calculeaza scorul initial al tarii curente
            min+=current->data->players[i].score;
        min=min/current->data->nr_players;
        current=current->next;
        while(current != head)
        {
            minc = 0;
            for(i=0; i<current->data->nr_players; i++) //calculeaza scorul initial al tarii urmatoare
                minc+=(current->data->players[i].score);
            minc=minc/current->data->nr_players;
            if(minc < min) //determin valoarea minima
                min = minc;
            current = current->next;

        }
    }
    printf("\n");
    return min; //functia returneaza scorul initial minim
}


void eliminare_tari_puterea_lui_2(ELEM *head, int nr_tari) //elimina tarile cu scor initial minim,
{
    ELEM *headcopy=head->next,*headcp;
    int nr_tari_ramase,i;
    float scor_min;
    nr_tari_ramase=putere_2(nr_tari);

    while(nr_tari > nr_tari_ramase) //elimina tari pana cand numarul de tari ramase este o putere a lui 2
    {
        headcopy = head->next;
        scor_min=scor_initial_minim(head);
        while(headcopy!=head)
        {
            float min=0;
            for(i=0; i<headcopy->data->nr_players; i++) //calculeaza scorul initial al tarii curente
                min+=(headcopy->data->players[i].score);
            min=min/headcopy->data->nr_players;
            if(min-scor_min==0 && nr_tari>nr_tari_ramase) // verifica daca scorul initial al tarii este scorul minim
            {

                headcp=headcopy->prev;   //daca este scorul minim, scoate acea tara din lista
                headcopy->prev->next=headcopy->next;
                headcopy->next->prev=headcopy->prev;
                for(i=0; i<headcopy->data->nr_players; i++) //eliberaza memoria ocupata de acea tara
                {
                    free(headcopy->data->players[i].first_name);
                    free(headcopy->data->players[i].last_name);
                }
                free(headcopy->data);
                free(headcopy);
                headcopy=headcp;
                --nr_tari;
            }
            headcopy=headcopy->next;
        }
    }

}


void push(ESTIV**top, Country data) //aduga date in stiva
{
    ESTIV* newNode=malloc(sizeof(ESTIV));
    newNode->data=data;
    newNode->next=*top;
    *top=newNode;
}

int isEmpty(ESTIV*top) //verifica daca stiva este goala
{
    return top==NULL;
}

Country pop(ESTIV**top) //scoate date din stiva
{
    int nr=0;
    ESTIV *temp=(*top);
    Country aux=temp->data;
    *top=(*top)->next;
    free(temp);
    return aux;
}


Queue* createQueue() //creaza o coada
{
    Queue *q;
    q=(Queue *)malloc(sizeof(Queue));
    if (q==NULL)
        return NULL;
    q->front=q->rear=NULL;
    return q;
}

void enQueue(Queue *q,Meci data) //adauga date in coada
{
    EQueue *newNode=malloc(sizeof(EQueue));
    newNode->next=NULL;
    newNode->data=data;
    if (q->rear==NULL)
        q->rear=newNode;
    else
    {
        (q->rear)->next=newNode;
        (q->rear)=newNode;
    }
    if (q->front==NULL)
        q->front=q->rear;

}


int isEmpty1(Queue*q) //verifica daca este coada goala
{
    return (q->front==NULL);
}

Meci deQueue(Queue *q) //scoate date din coada
{
    EQueue* aux;
    Meci meci;
    if (isEmpty1(q))
        return ;
    aux =q->front;
    meci=aux->data;
    q->front=(q->front)->next;
    return meci;
}



int cel_mai_mare_scor(Country tara)
{
    int i,max=0;
    for(i=0; i<tara.nr_players; i++)
    {
        if(tara.players[i].score > max)
            max=tara.players[i].score;
    }
    return max; //returneaza scorul maxim al jucatorilor dintr-o tara
}

int nr_elemente_stiva(ESTIV *top)
{
    int k=0;
    while(!isEmpty(top))
    {
        top=top->next;
        k++;
    }
    return k; //returneaza numarul din elemente din stiva
}

BST* newNode(Player *data)
{
    BST* node =malloc(sizeof(BST));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

BST* insert(BST* node, Player *key)//introduce noduri in BST
{
    if (node == NULL)
        return newNode(key);
    if(key->score == node->data->score) //verifica daca scorul introdus este egal cu scorul precedent din arbore
    {
        if(strcmp(key->last_name, node->data->last_name) < 0) //daca este egal, verifica daca unul dintre nume este mai mic din punct de vedere lexicografic
            node->data=key; //daca este, schimba datele exitente in nodul din arbore cu datele din key
    }
    if (key->score < node->data->score)
        node->left = insert(node->left, key);
    else if (key->score > node->data->score)
        node->right = insert(node->right, key);
    return node;
}

void parcurgere_descrescatoare(BST*root,FILE *rezultate) //afiseaza jucatorii din BST in ordine descrescatoare
{
    if (root)
    {
        parcurgere_descrescatoare(root->right,rezultate);
        fprintf(rezultate,"%s %s %d\n",root->data->last_name,root->data->first_name,root->data->score);
        parcurgere_descrescatoare(root->left,rezultate);
    }
}

ESTIV winner(ESTIV *top,int castigatori,List *head,FILE *rezultate)
{
    ESTIV *winner=NULL,*winner_copy=NULL;
    ESTIV *top_copy=NULL;
    Queue *q;
    q=createQueue();
    Country tara1,tara2;
    Meci meci;
    int lscor1=0,lscor2=0,i,j,k=1;

    while(nr_elemente_stiva(top) > (castigatori))
    {
        top_copy=top;
        if(nr_elemente_stiva(top)==4) //cand mai sunt doar 4 elemente
        {
            while(top_copy!=NULL)//introduce datele jucatorilor din cele 4 tari intr-o lista intermediara
            {
                for(i=0; i<top_copy->data.nr_players; i++)
                {
                    head->next=malloc(sizeof(List));
                    (head->next)->data=&top_copy->data.players[i];
                    head=head->next;
                    head->next=NULL;
                }
                top_copy=top_copy->next;
            }
        }

        fprintf(rezultate,"\n====== ETAPA %d ======\n",k);
        while(top!=NULL)
        {

            tara1=pop(&top); //scoate datele celor doua tari pentru a juca meciurile
            tara2=pop(&top);
            fprintf(rezultate,"\n%s %d ----- %s %d\n",tara1.name,tara1.global_score,tara2.name,tara2.global_score);
            for(i=0; i<tara1.nr_players; i++)
                for(j=0; j<tara2.nr_players; j++)
                {
                    meci.a=&tara1.players[i]; //copiaza adresele jucapilor
                    meci.b=&tara2.players[j];
                    enQueue(q,meci); //adauga datele in coada

                }
            int var=0;
            while(!isEmpty1(q))
            {
                meci=deQueue(q); //scoate adresele din coada
                fprintf(rezultate,"%s %s %d vs %s %s %d\n",meci.a->last_name,meci.a->first_name,meci.a->score,meci.b->last_name,meci.b->first_name,meci.b->score);
                if(meci.a->score == meci.b->score)
                {
                    meci.a->score += 2;//modifaca scorul de la adresa jucatorilor
                    meci.b->score += 2;
                    lscor1 += 1; //modifica scorul local
                    lscor2 += 1;
                }
                else if(meci.a->score > meci.b->score)
                {
                    meci.a->score += 5;
                    lscor1 += 3;
                }
                else
                {
                    meci.b->score += 5;
                    lscor2 += 3;
                }

            }


            tara1.global_score +=lscor1;//calculeza scorul global
            tara2.global_score +=lscor2;
            if(lscor1 == lscor2) //introduce tara castigatoare in stiva
            {
                if(cel_mai_mare_scor(tara1) < cel_mai_mare_scor(tara2))
                    push(&winner,tara2);
                else
                    push(&winner,tara1);
            }
            else if(lscor1 < lscor2)
                push(&winner,tara2);
            else
                push(&winner,tara1);

            lscor1=0;//egaleaza scorul local cu 0 pentru a nu se pastra pentru etapa urmatoare
            lscor2=0;
        }

        winner_copy=winner;
        fprintf(rezultate,"\n=== WINNER ===\n");
        while(winner_copy!=NULL) //afiseaza meciurile
        {
            fprintf(rezultate,"%s --- %d\n",winner_copy->data.name,winner_copy->data.global_score);
            winner_copy=winner_copy->next;
        }
        while(!isEmpty(winner))
        {
            push(&top,pop(&winner));
        }
        k++; //incrementeza numarul etapei
    }
}

void afisare(ELEM *head,FILE *rezultate) //afiseaza tarile
{
    ELEM *copy=head->next;
    while(copy!=head)
    {
        fprintf(rezultate,"%s\n",copy->data->name);
        copy=copy->next;
    }
}

int exista_jucatori(BST* root, char *first_name, char *last_name)
{
    int k=0;
    if(root)
    {
        if(strcmp(root->data->first_name,first_name)==0 && strcmp(root->data->last_name,last_name)==0)
            return 1; //returneaza 1 daca numele si prenumele sunt indentice din punct de vedere
        return(exista_jucatori(root->left,first_name,last_name) + exista_jucatori(root->right,first_name,last_name)) ;

    }
    return 0; //returneaza 0 in caz contrar
}

int jucatori_intermediari(BST*root,int scor1, int scor2)
{
    int k=0,aux=0;
    if(scor1 > scor2)
    {
        aux=scor1;
        scor1=scor2;
        scor2=aux;
    }
    if (root)
    {
        if(root->data->score > scor1 && root->data->score < scor2)//incrementeaza numarul de jucatori intermediari daca scorul din arbore esre cuprins intre scorurile celor doi jucatori
            return 1+jucatori_intermediari(root->right,scor1,scor2)+jucatori_intermediari(root->left,scor1,scor2);
        else
            return jucatori_intermediari(root->right,scor1,scor2)+jucatori_intermediari(root->left,scor1,scor2);
        //returneaza numarul jucatorilor intermediari
    }
    else
        return 0; //daca nu exista arborele, returneaza o
}

int main(int argc, char **argv)
{
    ELEM *head=NULL,*headcopy=NULL;
    Country *aux;
    ESTIV *stacktop=NULL,*winner_top=NULL;
    FILE *data,*cerinte,*rezultate;
    BST *node=NULL, *node_winner=NULL;
    List *head_list=NULL,*head_list_copy=NULL;
    char *nr_tari_c,buf[MAX_LENGTH];
    Player player_1,player_2,*aux_player;
    int nr_tari,i,j,cerinta_1=0,cerinta_2=0,cerinta_3=0,cerinta_4=0,cerinta_5=0;

    rezultate=fopen(argv[3],"wt"); //deschid fisierul in care afisez rezulatele
    if(rezultate==NULL)
    {
        puts("Fisierul nu s-a deschis.");
        exit (0);
    }

    cerinte=fopen(argv[1],"rt"); //deschid fisierul din care citesc cerintele
    if(cerinte==NULL)
    {
        puts("Fisierul nu s-a deschis.");
        exit (0);
    }

    fscanf(cerinte,"%d",&cerinta_1); //citesc conditile pentru rezolvarea cerintilor
    fscanf(cerinte,"%d",&cerinta_2);
    fscanf(cerinte,"%d",&cerinta_3);
    fscanf(cerinte,"%d",&cerinta_4);
    fscanf(cerinte,"%d",&cerinta_5);

    fscanf(cerinte,"%s",buf);                                //citesc datele jucatorilor pentru cerinta 5
    player_1.last_name=malloc(sizeof(char)*(strlen(buf)+1));
    strcpy(player_1.last_name,buf);
    fscanf(cerinte,"%s",buf);
    player_1.first_name=malloc(sizeof(char)*(strlen(buf)+1));
    strcpy(player_1.first_name,buf);
    fscanf(cerinte,"%d",&player_1.score);

    fscanf(cerinte,"%s",buf);
    player_2.last_name=malloc(sizeof(char)*(strlen(buf)+1));
    strcpy(player_2.last_name,buf);
    fscanf(cerinte,"%s",buf);
    player_2.first_name=malloc(sizeof(char)*(strlen(buf)+1));
    strcpy(player_2.first_name,buf);
    fscanf(cerinte,"%d",&player_2.score);

    fclose(cerinte);

    data=fopen(argv[2],"rt");  //deschid fisierul din care citesc datele tarilor
    if(data==NULL)
    {
        puts("Fisierul nu s-a deschis.");
        exit (0);
    }


    if(cerinta_1!=0)
    {
        head=malloc(sizeof(ELEM)); //creez lista dublu inlantuita,circulara, cu santinela
        head->next=head;
        head->prev=head;

        fscanf(data,"%d",&nr_tari); //citesc datele tarilor
        i=0;
        for(i=0; i<nr_tari; i++)
        {
            aux=malloc(sizeof(Country));
            fscanf(data,"%d",&aux->nr_players);

            fscanf(data,"%s",buf);
            aux->name=malloc(sizeof(char)*(strlen(buf)+1));
            strcpy(aux->name,buf);
            aux->global_score=0;
            aux->players=malloc(sizeof(Player)*aux->nr_players);
            for(j=0; j<aux->nr_players; j++)
            {

                fscanf(data,"%s",buf);
                aux->players[j].last_name=malloc(sizeof(char)*(strlen(buf)+1));
                strcpy(aux->players[j].last_name,buf);

                fscanf(data,"%s",buf);
                aux->players[j].first_name=malloc(sizeof(char)*(strlen(buf)+1));
                strcpy(aux->players[j].first_name,buf);

                fscanf(data,"%d",&aux->players[j].score);

            }
            adaugaFinal(head,aux); //adaug datele la finalul listei
        }
        if(cerinta_2==0)  //in cazul in care nu se rezolva cerinta 2 se afiseaza lista
            afisare(head,rezultate);

    }

    if(cerinta_2!=0)
    {
        eliminare_tari_puterea_lui_2(head,nr_tari);
        afisare(head,rezultate); //se afiseaza lista dupa stergera tarilor cu sciorul minim
    }

    if(cerinta_3!=0)
    {
        headcopy=head->next;
        while(headcopy!=head)
        {
            aux=headcopy->data;
            push(&stacktop,*aux);    //introduc datele din lista in stiva
            headcopy=headcopy->next;

        }
        head_list=malloc(sizeof(List)); //aloc spatiu pentru lista intermediara
        winner(stacktop,1,head_list,rezultate);
    }

    if(cerinta_4!=0)
    {
        head_list_copy=head_list->next;
        while(head_list_copy!=NULL)
        {
            node=insert(node,head_list_copy->data); //introduc datele din lista intermediara in BST
            head_list_copy=head_list_copy->next;
        }
        fprintf(rezultate,"\n====== CLASAMENT JUCATORI ======\n");
        parcurgere_descrescatoare(node,rezultate); //afisez in ordine descrescatoare a punctajelor jucatorii
    }



    if(cerinta_5!=0)
    {
        if(exista_jucatori(node,player_1.first_name,player_1.last_name)==1 && exista_jucatori(node,player_2.first_name,player_2.last_name)== 1)
            fprintf(rezultate,"\n%d",jucatori_intermediari(node,player_1.score,player_2.score)); //daca exista cei doi jucatori in BST afisez numarul de jucatori intermediari
        if(exista_jucatori(node,player_1.first_name,player_1.last_name)==0)
            fprintf(rezultate,"\n%s %s nu poate fi identificat!\n",player_1.last_name,player_1.first_name); //daca nu exista, afisez care dintre jucatori nu a fost gasit
        if(exista_jucatori(node,player_2.first_name,player_2.last_name)==0)
            fprintf(rezultate,"\n%s %s nu poate fi identificat!\n",player_2.last_name,player_2.first_name);
    }

    fclose(data);
    fclose(rezultate);

}

