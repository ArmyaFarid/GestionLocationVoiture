#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>
char menu();

/*Definition des structures*/
struct car{
    int ref_car;
    char marque[15];
    char model[15];
    char matriculation[15];
    int diponibilite; // 1=oui et 0=non
    int etat; // de 1 à 10
};

struct client{
    int num_client;
    char nom[15];
    char prenom[15];
    char sex[2]; // M ou F
    char adresse[15];
};

struct date{
    char jj;
    int mm;
    int aa;
} ;

struct contrat{
    int num_contrat;
    struct client locataire;
    struct date date_start;
    int duration;
    struct date date_end;
    int ref_car;
    int status; // 1=on et 0=off
    float price;
};

struct contrats{
    struct contrat list_contrat[100];
    int nbre_contrats;
};

struct cars{
    struct car list_car[30];
    int nbre_cars;
};

struct clients{
    struct client list_client[50];
    int nbre_clients;
};


int controleSaisi(int min, int max){
    int val;
    do{
        printf("\t\tSaisir entre %d - %d \t",min,max);
        scanf("%d",&val);
    } while ( val<min || val>max);
    return val;
}

void controleSaisiDate(struct date *dt){
    printf("\t\tAnnee:\t");
    dt->aa=controleSaisi(0,50000);
    printf("\t\tMois:\t");
    dt->mm=controleSaisi(0,12);
    printf("\t\tJour\t");
    if (dt->mm==1 || dt->mm==3 || dt->mm==5 || dt->mm==7 || dt->mm==8 || dt->mm==10 || dt->mm==12)
    {
        dt->jj=controleSaisi(0,31);
    }
    else{
        if (dt->mm==4 || dt->mm==6 || dt->mm==9 || dt->mm==11)
        {
            dt->jj=controleSaisi(0,30);
        }
        else{
                if((dt->aa % 4 == 0) && (dt->aa % 100 == 0) && (dt->aa % 400 == 0)){
                        dt->jj=controleSaisi(0,28);
                }
                else{
                        dt->jj=controleSaisi(0,29);
                }

            }

    }


}

void add_car(struct cars *c){
    c->list_car[c->nbre_cars].ref_car=c->nbre_cars;
    printf("\t\tMarque:");
    fflush(stdin);
    gets(c->list_car[c->nbre_cars].marque);
    printf("\t\tModel:");
    fflush(stdin);
    gets(c->list_car[c->nbre_cars].model);
    printf("\t\tMatriculation:");
    fflush(stdin);
    gets(c->list_car[c->nbre_cars].matriculation);
    c->list_car[c->nbre_cars].diponibilite=1;
    printf("\t\tEtat:");
    c->list_car[c->nbre_cars].etat=controleSaisi(1,10);
    c->nbre_cars=c->nbre_cars+1;

}

void affich_Allcar(struct cars c){
    int i;
    for ( i = 0; i < c.nbre_cars; i++)
    {
        affich_1car(c,i);
    }

}

void affich_Acar(struct cars c){
    int i;
    printf("Saisir reference");
    scanf("%d",&i);
        affich_1car(c,i);


}

void affich_1car(struct cars c,int i){
        printf("Reference est \n: %d",c.list_car[i].ref_car);
        printf("\tMarque:\t %s",c.list_car[i].marque);
        printf("\n");
        printf("\tModel: \t %s",c.list_car[i].model);
        printf("\n");
        printf("\tMatriculation: \t %s",c.list_car[i].matriculation);
        printf("\n");
        if(c.list_car[i].diponibilite==1){
            printf(" \t Disponible");
        }
        else{
            printf(" \t Occupe");
        }
        printf(" \t Disponible: %d",c.list_car[i].diponibilite);
        printf("\n");
        printf("\t Etat: \t %d",c.list_car[i].etat);
        printf("\n\n");
}

void affich_Avalcar(struct cars c){
    int i;
        for ( i = 0; i < c.nbre_cars; i++){
            if (c.list_car[i].diponibilite==1)
            {
                printf("Reference est \n: %d",c.list_car[i].ref_car);
                printf("\tMarque:\t %s",c.list_car[i].marque);
                printf("\n");
                printf("\tModel: \t %s",c.list_car[i].model);
                printf("\n");
                printf("\tMatriculation: \t %s",c.list_car[i].matriculation);
                printf("\n");
                printf("Etat: \t %d",c.list_car[i].etat);
                printf("\n\n");
            }
        }
}

int check_Avalcar(struct cars c, int ref){
    char rep;
    if(c.nbre_cars==0){
                printf("Il n'y pas de voiture disponible.");
                return 0;
            }
    if (c.list_car[ref].diponibilite!=1 || c.list_car[ref].etat<3 || ref>c.nbre_cars){
        printf("Cette voiture ne peut pas être utilisée.\n Raison:\t");
            if(c.list_car[ref].diponibilite!=1){printf("Pas dispo");}
            if(c.list_car[ref].etat<3){printf("Mauvais etat");}
            if(ref>c.nbre_cars){printf("Reference inexistant");}

        do
        {
            printf("\nVoulez vous afficher la liste des voitures disponible? o ou n:\t");
            fflush(stdin);
            scanf("%c",&rep);
        } while (rep!='o' && rep!='n');
        if(rep=='o'){
            affich_Avalcar(c);
        }
        return 0;

        }

    return 1;
}

void getNowDate(struct date *dt){
    time_t timestamp;
    struct tm * t;

    timestamp = time(NULL);
    t = localtime(&timestamp);
    dt->jj=t->tm_mday;
    dt->mm=t->tm_mon;
    dt->aa=1900 + t->tm_year;
}

void create_contrat(struct contrats *ct, struct clients *cl, struct cars cr){
    char rep;
    int i,id,n,a;
    i=ct->nbre_contrats;
    printf("\n\t\t\t i=%d \n\n",i);
    ct->list_contrat[i].num_contrat=ct->nbre_contrats;
    printf("Informations sur le demandeur\n");

     do
    {
        printf("\nEst-ce un ancien client? o(oui)/n(non)\t");
        fflush(stdin);
        scanf("%s",&rep);
    } while (rep!='o' && rep!='n');
    if (rep=='o'){
        id=get_contratIdByName(cl);

        if (id==-1)
        {
            printf("\n Client inexistant,veuillez remplir manuellement\n");
            cl->list_client[cl->nbre_clients].num_client=cl->nbre_clients;
            printf("\n");
            printf("\t\tNom:\t");
            fflush(stdin);
            gets(ct->list_contrat[i].locataire.nom);

            printf("\t\tPrenom:\t");
            fflush(stdin);
            gets(ct->list_contrat[i].locataire.prenom);

            printf("\t\tGenre:\t");
            fflush(stdin);
            gets(ct->list_contrat[i].locataire.sex);

            printf("\t\tAdresse:\t");
            fflush(stdin);
            gets(ct->list_contrat[i].locataire.adresse);


            cl->list_client[cl->nbre_clients]=ct->list_contrat[i].locataire;
            cl->nbre_clients=cl->nbre_clients+1;
        }
        else{
        ct->list_contrat[i].locataire.num_client=id;
        ct->list_contrat[i].locataire=cl->list_client[id];

        }


    }
    else{
        cl->list_client[cl->nbre_clients].num_client=cl->nbre_clients;
            printf("\n");
            printf("\t\tNom:\t");
            fflush(stdin);
            gets(ct->list_contrat[i].locataire.nom);

            printf("\t\tPrenom:\t");
            fflush(stdin);
            gets(ct->list_contrat[i].locataire.prenom);

            printf("\t\tGenre:\t");
            fflush(stdin);
            gets(ct->list_contrat[i].locataire.sex);

            printf("\t\tAdresse:\t");
            fflush(stdin);
            gets(ct->list_contrat[i].locataire.adresse);


            cl->list_client[cl->nbre_clients]=ct->list_contrat[i].locataire;
            cl->nbre_clients=cl->nbre_clients+1;
    }

    printf("Essais client %d",cl->nbre_clients);
    printf("\n");
    printf("\t\tDate de location(format annee/moi/jour):\n");
     do
    {
        printf("\n\t\t\tVoulez vous utiliser la date d'aujourd'hui o ou n");
        fflush(stdin);
        scanf("%s",&rep);
    } while (rep!='o' && rep!='n');

    if (rep=='o')
            {
                getNowDate(&ct->list_contrat[i].date_start);
            }
    else{controleSaisiDate(&ct->list_contrat[i].date_start);}

    printf("\t\tDate de fin location(format annee/moi/jour):\n");
    controleSaisiDate(&ct->list_contrat[i].date_end);

    printf("\t\tDuree:\t");
    scanf("%d",&ct->list_contrat[i].duration);

    do{
    printf("\nReference voiture pour la location:\t");
    scanf("%d",&ct->list_contrat[i].ref_car);
    a=check_Avalcar(cr,ct->list_contrat[i].ref_car);
    if(a==0){
    printf("Taper autre que chiffre que 0 pour continuer quand meme");
    scanf("%d",&a);}
    }while(a==0);
    cr.list_car[ct->list_contrat[i].ref_car].diponibilite=0;

    printf("\t\tPrix:\t");
    scanf("%f",&ct->list_contrat[i].price);
    ct->list_contrat[i].status=1;
    ct->nbre_contrats=i+1;
}


void turnOff_contrat(struct contrats *ct){
    int num;
    printf("Numero du contrat à modifier:");
    scanf("%d",&num);
    ct->list_contrat[num].status=0;
}

void affich_client(struct client cl){
    printf("\t\tIdentifiant: %d",cl.num_client);
    printf("\n");
    printf("\t\tNom: %s",cl.nom);
    printf("\n");
    printf("\t\tPrenom: %s",cl.prenom);
    printf("\n");
    printf("\t\tGenre: %s",cl.sex);
    printf("\n");
    printf("\t\tAdresse: %s",cl.adresse);
}

void modify_contrat(struct contrats *ct){
    int rep,num;
    printf("Numero du contrat à modifier:\t");
    scanf("%d",&num);
    printf("Informations sur le demandeur\t");
    printf("\n");
    printf("\t\tNom:\t");
    fflush(stdin);
    gets(ct->list_contrat[num].locataire.nom);
    printf("\t\tPrenom:\t");
    fflush(stdin);
    gets(ct->list_contrat[num].locataire.prenom);
    printf("\t\tGenre:\t");
    fflush(stdin);
    gets(ct->list_contrat[num].locataire.sex);
    printf("\t\tAdresse:\t");
    fflush(stdin);
    gets(ct->list_contrat[num].locataire.adresse);
    printf("\n");
    printf("\tDate de location(format annee/moi/jour):\n");
     do
    {
        printf("\nVoulez vous utiliser la date d'aujourd'hui o ou n");
        fflush(stdin);
        scanf("%c",&rep);
    } while (rep!='o' && rep!='n');

    if (rep=='o')
            {
                getNowDate(&ct->list_contrat[num].date_start);
            }

    controleSaisiDate(&ct->list_contrat[num].date_start);

    printf("\t\tDate de fin location(format annee/moi/jour):\n");
    controleSaisiDate(&ct->list_contrat[num].date_end);
    printf("\t\tDuree en jour:");
    scanf("%d",&ct->list_contrat[num].duration);
    printf("\t\tReference voiture pour la location:");
    scanf("%d",&ct->list_contrat[num].ref_car);
    printf("\t\tPrix:");
    scanf("%2.f",&ct->list_contrat[num].price);
    }

int compareString(char A1[],char A2[], int index){
    if (strlen(A1) != strlen(A2)) return 0;

    if (index == strlen(A1)) return 1;

    if (A1[index] != A2[index]) return 0;

    return compareString(A1, A2, index+1);
}

int get_contratIdByName(struct clients cl){
    char nom[15], prenom[15];
    int i;
    printf("\tSaisir le nom:\t");
    fflush(stdin);
    gets(nom);
    printf("\tSaisir le prenom:\t");
    fflush(stdin);
    gets(prenom);
    for (i = 0; i < cl.nbre_clients; i++)
    {
        if (compareString(cl.list_client[i].nom,nom,0)==1 && compareString(cl.list_client[i].prenom,prenom,0)==1)
        {
            return cl.list_client[i].num_client;
        }
    }
    return -1;
}

void affich_AllContrat(struct contrats ct){
    int i;
    for ( i = 0; i < ct.nbre_contrats; i++)
    {
        affich_AContrat(ct,i);

    }


}


void affich_AContrat(struct contrats ct,struct cars cr, int i){

        printf("Informations sur le demandeur");
        affich_client(ct.list_contrat[i].locataire);
        printf("\n");
        printf("Date de location(format annee/moi/jour):");
            printf("\n\tJour: %d",ct.list_contrat[i].date_start.jj);
            printf("\n\tMois: %d",ct.list_contrat[i].date_start.mm);
            printf("\n\tAnnee: %d",ct.list_contrat[i].date_start.aa);
        printf("\n");
        printf("Duree: %d",ct.list_contrat[i].duration);
        printf("\n");
        printf("Date de fin location(format annee/moi/jour):\n");
            printf("\n\tJour: %d",ct.list_contrat[i].date_end.jj);
            printf("\n\tMois: %d",ct.list_contrat[i].date_end.mm);
            printf("\n\tAnnee: %d",ct.list_contrat[i].date_end.aa);
        printf("\n");
        printf("Info sur la voiture:");
        printf("\n");
            printf("\t");
            affich_1car(cr,ct.list_contrat[i].ref_car);
        printf("\n");
        printf("Prix: %f",ct.list_contrat[i].price);
        printf("\n");
}

void find_associateClientContrats(struct clients cl,struct contrats ct, struct cars cr ){
        int id,i;
        id=get_contratIdByName(cl);
        for(i=0;i<ct.nbre_contrats;i++){
            if(ct.list_contrat[i].locataire.num_client==id){
                affich_AContrat(ct,cr,i);
            }
        }


}

void controle_CarState(struct cars cr){
    int i,state,total;
    total=0;
    printf("Pour afficher les vehicules deffectueux, donner le soeuil minimum [1 -10]");
    controleSaisi(0,10);
    for(i=0;i<cr.nbre_cars;i++){
        if(cr.list_car[i].diponibilite==1 && cr.list_car[i].etat<=state){
            total++;
        }
    }

    if(cr.nbre_cars==0 && total==0){
        printf("Il n'y pas de vehicule disponible");
    }
    else{
         printf("\n");
         printf("\t Il y'a en total %d vehicules en dessous du soeuil defini",total);
         printf("\n\n");
         for(i=0;i<cr.nbre_cars;i++){
            if(cr.list_car[i].diponibilite==1 && cr.list_car[i].etat<=state){
                affich_1car(cr,i);
                }
            }
        }
}


int main()
{
    char choix,save,go_menu,option;
    int end;
    int i;
    struct contrats contrat_contain;
    struct clients client_contain;
    struct cars car_contain;
/*contrat_contain.list_contrat[0].locataire.num_client=0;
contrat_contain.list_contrat[0].locataire.nom[0]='m';
contrat_contain.list_contrat[0].locataire.prenom[0]='m';
contrat_contain.list_contrat[0].locataire.sex[0]='m';
contrat_contain.list_contrat[0].locataire.adresse[0]='m';
contrat_contain.list_contrat[0].num_contrat=0;
contrat_contain.list_contrat[0].date_end.aa=11;
contrat_contain.list_contrat[0].date_end.jj=11;
contrat_contain.list_contrat[0].date_end.mm=11;
contrat_contain.list_contrat[0].date_start.aa=11;
contrat_contain.list_contrat[0].date_start.jj=11;
contrat_contain.list_contrat[0].date_start.mm=11;
contrat_contain.list_contrat[0].ref_car=11;
contrat_contain.list_contrat[0].status=11;
contrat_contain.list_contrat[0].price=11;


contrat_contain.list_contrat[1].locataire.num_client=1;
contrat_contain.list_contrat[1].locataire.nom[0]='m';
contrat_contain.list_contrat[1].locataire.prenom[0]='o';
contrat_contain.list_contrat[1].locataire.sex[0]='m';
contrat_contain.list_contrat[1].locataire.adresse[0]='m';
contrat_contain.list_contrat[1].num_contrat=1;
contrat_contain.list_contrat[1].date_end.aa=11;
contrat_contain.list_contrat[1].date_end.jj=11;
contrat_contain.list_contrat[1].date_end.mm=11;
contrat_contain.list_contrat[1].date_start.aa=11;
contrat_contain.list_contrat[1].date_start.jj=11;
contrat_contain.list_contrat[1].date_start.mm=11;
contrat_contain.list_contrat[1].ref_car=11;
contrat_contain.list_contrat[1].status=11;
contrat_contain.list_contrat[1].price=11;*/

    contrat_contain.nbre_contrats=0;
    client_contain.nbre_clients=0;
    car_contain.nbre_cars=0;
    /*struct contrats contrat_contain;
    struct clients client_contain;
    struct cars car_contain;
    contrat_contain.nbre_contrats=0;
    client_contain.nbre_client=0;
    car_contain.nbre_car=0;*/
    do{
    choix=menu();
    printf("%c",&choix);

    switch (choix){

        case '1':
            do{
                fflush(stdin);
                create_contrat(&contrat_contain,&client_contain,car_contain);
                printf("\n%d \n",contrat_contain.nbre_contrats);
                affich_AContrat(contrat_contain,car_contain,contrat_contain.nbre_contrats-1);

                printf("Voulez vous enregistrer? Taper o(enregistrer)/autre pour modifier");
                fflush(stdin);
                scanf("%c",&save);
            }while(save!='o');
            printf("\nRetour au menu? o(oui) taper autre pour quitter");
            fflush(stdin);
            scanf("%c",&go_menu);
            break;

        case '2':
            modify_contrat(&contrat_contain);
            printf("\nRetour au menu? o(oui) taper autre pour quitter");
            fflush(stdin);
            scanf("%c",&go_menu);
            break;

        case '3':
            turnOff_contrat(&contrat_contain);
            printf("\nRetour au menu? o(oui) taper autre pour quitter");
            fflush(stdin);
            scanf("%c",&go_menu);
            break;

        case '4':
                do{
                printf("1-Contrat specifique \n 2-Tous les contrats");
                fflush(stdin);
                scanf("%c",&option);
                }while(option!='1' && option!='2');

                if(option=='1'){
                    do{
                        printf("Donner le numero du contract entre 0 et %d:",contrat_contain.nbre_contrats-1);
                        scanf("%d",&i);
                        }while(i>contrat_contain.nbre_contrats-1);
                    affich_AContrat(contrat_contain,car_contain,i);

                }
                else{
                    printf("\n nombre de contrats %d \n",contrat_contain.nbre_contrats);
                    affich_AllContrat(contrat_contain);
                }
                printf("\nRetour au menu? o(oui) taper autre pour quitter");
                fflush(stdin);
                scanf("%c",&go_menu);
            break;

        case '5':

            for(i=0;i<client_contain.nbre_clients;i++){
                    affich_client(client_contain.list_client[i]);
            }
            printf("\nRetour au menu? o(oui) taper autre pour quitter");
            fflush(stdin);
            scanf("%c",&go_menu);
            break;
        case '6':
            find_associateClientContrats(client_contain,contrat_contain,car_contain);
            printf("\nRetour au menu? o(oui) taper autre pour quitter");
            fflush(stdin);
            scanf("%c",&go_menu);
            break;

        case '7':
            add_car(&car_contain);
            printf("\nRetour au menu? o(oui) taper autre pour quitter");
            fflush(stdin);
            scanf("%c",&go_menu);
            break;


        case '8':
            controle_CarState(car_contain);
            printf("\nRetour au menu? o(oui) taper autre pour quitter");
            fflush(stdin);
            scanf("%c",&go_menu);
            break;


        case '9':
            affich_Allcar(car_contain);
            printf("\nRetour au menu? o(oui) taper autre pour quitter");
            fflush(stdin);
            scanf("%c",&go_menu);
            break;

}

    }while(go_menu=='o');


    return 0;
}


char menu(){
    char choix;

    printf("Application de gestionn de Location de vehicule");

    printf("GESTION DE CONTRATS");
    printf("\n");
    printf("\t\t1 Nouveau contrat");
    printf("\n");
    printf("\t\t2 Modifier un contrat");
    printf("\n");
    printf("\t\t3 Terminer un contrat");
    printf("\n");
    printf("\t\t4 Afficher la liste des contrats");

    printf("\n\n");
    printf("GESTION DES CLIENTS");
    printf("\n");
    printf("\t\t5 Afficher la liste des clients");
    printf("\n");
    printf("\t\t6 Afficher les contrats associes a un client");

    printf("\n\n");
    printf("GESTION DES VEHICULES");
    printf("\n");
    printf("\t\t7 Ajouter un vehicule");
    printf("\n");
    printf("\t\t8 Verifier l'etat des vehicules");
    printf("\n");
    printf("\t\t9 Afficher les vehicules");
    printf("\n");

    do{
        printf("Que souhaitez vous faire (1-9)");
        fflush(stdin);
        scanf("%c",&choix);
    }while(choix!='1' && choix!='2' && choix!='3' && choix!='4' && choix!='5' && choix!='6' && choix!='7' && choix!='8' && choix!='9' );

    return choix;

}
