typedef int bool;
#define false 0
#define true -1

#include "stdlib.h"
#include "memory.h"
#include "stdio.h"
#include "string.h"

////////////////////////////////////////
// Exercice 1: Classement des Relations
typedef enum
{
    FRERE = 2,
    COUSIN,
    PARENT,
    ONCLE,
    EPOUX,
    AMI,
    VIT,
    CONNAIT,
    CHEF,
    COLLEGUE,
    LOCATAIRE,
    TRAVAILLE,
    PROPRIETAIRE,
    SITUE,
    DECOUVERT
} rtype;

/**
 * @brief Cette fonction détermine si un type d'identifiant est une relation de parenté.
 * @param[in] id L'identifiant de la relation à vérifier.
 * @return Vrai si l'identifiant correspond à une relation de parenté, faux sinon.
 */
bool est_lien_parente(rtype id)
{
    return (id >= FRERE && id <= EPOUX) ? true : false;
}
/**
 * @brief Cette fonction détermine si un type d'identifiant est un lien professionnel
 * @param[in] id: le type d'identifiant à vérifier
 * @return true si le type d'identifiant est un lien professionnel, sinon false
 */
bool est_lien_professionel(rtype id)
{
    return (id >= CHEF && id <= COLLEGUE) ? true : false;
}
/**
 * @brief Cette fonction détermine si un type d'identifiant est un lien de connaissance
 * @param[in] id: le type d'identifiant à vérifier
 * @return true si le type d'identifiant est un lien professionnel, sinon false
 */
bool est_lien_connaissance(rtype id)
{
    return (id >= AMI && id <= CONNAIT) ? true : false;
}
/**
 * @brief Cette fonction renvoie une chaîne de caractères correspondant à un type d'identifiant de relation
 * @param[in] id: le type d'identifiant de relation à convertir
 * @return une chaîne de caractères représentant le type d'identifiant de relation
 *         ou NULL si l'identifiant est hors de la plage d'index valides
 */

char *toString(rtype id)
{
    static const char *strings[] =
        {
            "Relation inexistante", "inconnu", "frere ou soeur de", "cousin ou cousine de",
            "pere ou mere de", "oncle ou tante de", "epoux ou epouse de", "ami(e) de", "vit avec", "connait", "superieur(e) de",
            "collegue de", "locataire de", "travaille a", "proprietaire de", "situe a", "decouvert a"};
    static const int num_strings = sizeof(strings) / sizeof(strings[0]);

    if (id < 0 || id >= num_strings)
    {
        // id est hors de la plage d'index valides
        return NULL;
    }
    else
    {
        return (char *)strings[id];
    }
}

////////////////////////////////////////
// Exercice 2: Liste de pointeurs
/**
 * @brief Définition d'une structure de liste chaînée générique
 * @param val pointeur vers un objet quelconque
 * @param suiv pointeur vers le nœud suivant dans la liste
 * @param listeg alias pour le pointeur vers le premier nœud de la liste
 */
typedef struct s_node
{
    void *val;
    struct s_node *suiv;
} *listeg;

/**
 * @brief Cette fonction crée une nouvelle liste chaînée générique vide
 * @return un pointeur NULL qui représente une liste vide
 */
listeg listegnouv()
{
    return NULL;
}

/**
 * @brief Cette fonction ajoute un nouvel élément au début d'une liste chaînée générique
 * @param lst: un pointeur vers le premier nœud de la liste existante
 * @param x: un pointeur vers l'élément à ajouter à la liste
 * @return un pointeur vers le nouveau premier nœud de la liste
 */
listeg adjtete(listeg lst, void *x)
{
    // Allocation d'une nouvelle liste
    listeg lst_nouv = (listeg)malloc(sizeof(struct s_node));
    if (lst_nouv == NULL)
    {
        printf("fatal error: L'allocation a échoué.\n");
        exit(EXIT_FAILURE);
    }
    lst_nouv->val = x;    // Initialise la valeur de l'element a ajouter.
    lst_nouv->suiv = lst; // Chaine le nouvel element en tete de liste.
    return lst_nouv;
}

/**
 * @brief Cette fonction ajoute un nouvel élément à la fin d'une liste chaînée générique
 * @param lst: un pointeur vers le premier nœud de la liste existante
 * @param x: un pointeur vers l'élément à ajouter à la liste
 * @return un pointeur vers le premier nœud de la liste avec le nouvel élément ajouté à la fin
 */
listeg adjqueue(listeg lst, void *x)
{
    // Allocation d'une nouvelle liste
    listeg lst_nouv = (listeg)malloc(sizeof(struct s_node));
    if (lst_nouv == NULL)
    {
        printf("fatal error: L'allocation a échoué.\n");
        exit(EXIT_FAILURE);
    }
    lst_nouv->val = x;
    lst_nouv->suiv = NULL;
    // Cas ou la liste est vide
    if (lst == NULL)
    {
        return lst_nouv;
    }
    // Parcours de la liste jusqu'au dernier element
    listeg lst_tmp = lst;
    while (lst_tmp->suiv != NULL)
    {
        lst_tmp = lst_tmp->suiv;
    }
    // Ajout du lst_nouv noeud a la fin de la liste
    lst_tmp->suiv = lst_nouv;
    return lst;
}

/**
 * @brief Cette fonction supprime le premier élément d'une liste chaînée.
 * @param lst La liste chaînée dont le premier élément doit être supprimé.
 * @return La liste chaînée avec le premier élément supprimé. Si la liste était vide, renvoie NULL.
 */
listeg suptete(listeg lst)
{
    if (lst == NULL)
        return NULL;
    listeg lst_tmp = lst;
    lst = lst_tmp->suiv; // lst pointe sur le deuxieme element de la liste
    free(lst_tmp);
    return lst;
}

/**
 * @brief Cette fonction calcule la longueur d'une liste chaînée.
 * @param lst La liste chaînée dont on veut calculer la longueur.
 * @return La longueur de la liste chaînée.
 */
int longueur(listeg lst)
{
    if (lst == NULL)
        return 0;
    else
        return 1 + longueur(lst->suiv);
}

/**
 * @brief Vérifie si une liste chaînée est vide.
 * @param lst La liste chaînée dont on veut vérifier si elle est vide.
 * @return true si la liste est vide, false sinon.
 */
bool estvide(listeg lst)
{
    return (lst == NULL) ? true : false;
}

/**
 * @brief Retourne la valeur du premier élément de la liste chaînée.
 * @param lst La liste chaînée dont on veut la valeur du premier élément.
 * @return Un pointeur vers la valeur du premier élément de la liste chaînée.
 */
void *tete(listeg lst)
{
    if (estvide(lst))
        exit(1);
    return lst->val;
}

/**
 * @brief Cette fonction libère la mémoire occupée par une liste chaînée en supprimant tous les éléments.
 * @param lst La liste chaînée à supprimer.
 */
void detruire(listeg lst)
{
    while (lst != NULL)
    {
        lst = suptete(lst);
    }
}

/**
 * @brief Recherche les éléments correspondants à une valeur x dans la liste
 * @param lst La liste à parcourir.
 * @param x La valeur à rechercher.
 * @param comp La fonction de comparaison
 * @return Une nouvelle liste contenant les éléments correspondants à la valeur recherchée.
 */
listeg rech(listeg lst, void *x, int (*comp)(void *, void *))
{
    listeg lst_nouv = NULL;
    listeg tmp = lst;
    while (tmp != NULL)
    {
        if (comp(tmp->val, x) == true)
        {
            lst_nouv = adjtete(lst_nouv, tmp->val);
        }
        tmp = tmp->suiv;
    }
    return lst_nouv;
}

////////////////////////////////////////
// Exercice 3: Construction du graphe

#define LONG_NOM_MAX 64
typedef enum
{
    PERSONNE = 1,
    OBJET,
    ADRESSE,
    VILLE
} etype;

/**
 * @brief Structure représentant une entité.
 */
typedef struct s_entite
{
    char nom[LONG_NOM_MAX]; // le nom de l'entite p.ex " Peugeot 106 "
    etype ident;            // l'identifiant associe, p.ex OBJET
} *Entite;

/**
 * @brief La structure de sommet du graphe.
 * @param larcs liste d'arcs sortants
 * @param x entité associée au sommet
 */
typedef struct s_sommet
{
    listeg larcs;
    Entite x;
} *Sommet;

/**
 * @brief Structure représentant un arc du graphe.
 * @param t Le type de relation entre le sommet de départ et le sommet d'arrivée.
 * @param x L'entité associée à l'arc.
 */
typedef struct s_arc
{
    rtype t;
    Entite x;
} *Arc;

/**
 * @brief Structure représentant un ensemble de relations entre différentes entités.
 * @note Les relations sont stockées sous forme de liste chaînée générique.
 * @param lstg_relations La liste chaînée générique contenant les relations.
 */
typedef struct s_relations
{
    listeg lstg_relations;
} *Relations;

// 3.2 les constructeurs
/**
 * @brief Crée une nouvelle entité avec un nom et un identifiant donnés.
 * @param s Le nom de l'entité.
 * @param e Le type de l'entité.
 * @return Un pointeur vers la nouvelle entité créée.
 */
Entite creerEntite(char *s, etype e)
{
    Entite ent = (Entite)malloc(sizeof(struct s_entite));
    if (ent == NULL)
    {
        printf("fatal error: L'allocation a échoué.\n");
        exit(EXIT_FAILURE);
    }
    ent->ident = e;
    unsigned long taille = strlen(s);
    if (taille <= LONG_NOM_MAX)
    {
        strcpy(ent->nom, s);
    }
    return ent;
}

/**
 * @brief Crée un nouveau sommet avec l'entité spécifiée
 * @param e Entité associée au sommet
 * @return Sommet nouvellement créé
 */
Sommet nouvSommet(Entite e)
{
    Sommet sommet_tmp = (Sommet)malloc(sizeof(struct s_sommet));
    if (sommet_tmp == NULL)
    {
        printf("fatal error: L'allocation a échoué.\n");
        exit(EXIT_FAILURE);
    }
    sommet_tmp->larcs = listegnouv();
    sommet_tmp->x = e;
    return sommet_tmp;
}

/**
 * @brief Crée un nouveau arc
 * @param e : l'entité associée à l'arc
 * @param type : le type de l'arc (rtype)
 * @return : un pointeur vers la nouvelle instance de Arc créée
 */
Arc nouvArc(Entite e, rtype type)
{
    Arc arc_tmp = (Arc)malloc(sizeof(struct s_arc));
    if (arc_tmp == NULL)
    {
        printf("fatal error: L'allocation a échoué.\n");
        exit(EXIT_FAILURE);
    }
    arc_tmp->x = e;
    arc_tmp->t = type;
    return arc_tmp;
}

/**
 * @brief Initialise une structure Relations en allouant de la mémoire et en initialisant sa liste de relations.
 * @param g Pointeur vers la structure Relations à initialiser.
 */
void relationInit(Relations *g)
{
    *g = (Relations)malloc(sizeof(struct s_relations));
    if (*g == NULL)
    {
        printf("fatal error: no memory allocation possible.\n");
        exit(EXIT_FAILURE);
    }
    (*g)->lstg_relations = listegnouv();
}

/**
 * @brief Libère la mémoire allouée pour une structure Relations
 * @param g un pointeur vers la structure Relations à libérer
 */
void relationFree(Relations *g)
{
    if (g != NULL)
    {
        listeg lstg = (*g)->lstg_relations;
        while (lstg != NULL)
        {
            if (lstg->val != NULL)
            {
                // on récupère le sommet
                Sommet s = (Sommet)lstg->val;
                free(s->x);
                listeg tmp = s->larcs;
                while (tmp != NULL)
                {
                    free(tmp->val);
                    tmp = tmp->suiv;
                }
                detruire(s->larcs);
                free(s);
            }
            lstg = lstg->suiv;
        }
        detruire((*g)->lstg_relations);
        free(*g);
    }
}

// 3.3 les comparaisons
/**
 * @brief Compare le nom d'une entité avec une chaîne de caractères donnée.
 * @param e Un pointeur vers une entité à comparer.
 * @param string Un pointeur vers une chaîne de caractères à comparer avec le nom de l'entité.
 * @return Retourne `true` si le nom de l'entité correspond à la chaîne de caractères, `false` sinon.
 */
int compEntite(void *e, void *string)
{
    Entite ent = (Entite)e;
    bool retour = false;
    if (strcmp(ent->nom, (char *)string) == 0)
    {
        retour = true;
    }
    return retour;
}

/**
 * @brief Compare le nom d'un sommet avec une chaîne de caractères donnée.
 * @param s Un pointeur vers un sommet à comparer.
 * @param string Un pointeur vers une chaîne de caractères à comparer avec le nom du sommet.
 * @return Retourne `true` si le nom du sommet correspond à la chaîne de caractères, `false` sinon.
 */
int compSommet(void *s, void *string)
{
    Sommet som = (Sommet)s;
    bool retour = false;
    if (strcmp(som->x->nom, (char *)string) == 0)
    {
        retour = true;
    }
    return retour;
}

/**
 * @brief Compare le nom d'un arc avec une chaîne de caractères donnée.
 * @param a Un pointeur vers un arc à comparer.
 * @param string Un pointeur vers une chaîne de caractères à comparer avec le nom de l'arc.
 * @return Retourne `true` si le nom de l'arc correspond à la chaîne de caractères, `false` sinon.
 */
int compArc(void *a, void *string)
{
    Arc arc = (Arc)a;
    bool retour = false;
    if (strcmp(arc->x->nom, (char *)string) == 0)
    {
        retour = true;
    }
    return retour;
}

// 3.4 ajout d'entites et de relations
/**
 * @brief Ajoute une entité à la liste des relations d'un graphe s'il n'y a pas déjà une entité avec le même nom dans la liste.
 * @param g Un pointeur vers le graphe à modifier.
 * @param nom Le nom de l'entité à ajouter.
 * @param t Le type de l'entité à ajouter.
 */
void adjEntite(Relations g, char *nom, etype t)
{
    if (g == NULL)
    {
        fprintf(stderr, "graphe non initialisé \n");
        exit(EXIT_FAILURE);
    }
    Entite e = creerEntite(nom, t);
    Sommet s = nouvSommet(e);
    if (g->lstg_relations == NULL)
    {
        g->lstg_relations = adjtete(g->lstg_relations, s);
    }
    else
    {
        listeg tmp = g->lstg_relations;
        while (tmp != NULL)
        {
            Sommet som = (Sommet)tmp->val;
            Entite entite = som->x;
            if (compEntite(entite, e->nom) == true)
            {
                fprintf(stderr, "l'entité %s existe dans la liste \n", e->nom);
                exit(EXIT_FAILURE);
            }
            tmp = tmp->suiv;
        }
        g->lstg_relations = adjqueue(g->lstg_relations, s);
    }
}

/**
 * @brief Parcourt une liste d'arcs pour trouver un arc ayant le nom spécifié, change son type et retourne vrai s'il existe, faux sinon.
 * @param lst_arcs La liste d'arcs à parcourir.
 * @param x Le nom de l'arc à chercher.
 * @param t Le type à attribuer à l'arc s'il est trouvé.
 * @return Vrai si un arc ayant le nom spécifié a été trouvé et son type a été changé, faux sinon.
 */
int existeArc(listeg lst_arcs, char *x, rtype t)
{
    listeg lstg_tmp = lst_arcs;
    bool retour = false;
    while (lstg_tmp != NULL)
    {
        if (compArc(lstg_tmp->val, x) == true)
        {
            Arc arc_tmp = (Arc)lstg_tmp->val;
            arc_tmp->t = t;
            retour = true;
        }
        lstg_tmp = lstg_tmp->suiv;
    }
    return retour;
}

// PRE CONDITION: id doit etre cohérent avec les types des sommets correspondants à x et y
// p.ex si x est de type OBJET, id ne peut pas etre une relation de parente
// PRE CONDITION: strcmp(nom1,nom2)!=0
/**
 * @brief Cette fonction ajoute une relation de type `id` entre deux entités `nom1` et `nom2` dans le graphe `g`.
 * @param g Le graphe dans lequel ajouter la relation.
 * @param nom1 Le nom de la première entité.
 * @param nom2 Le nom de la deuxième entité.
 * @param id Le type de la relation à ajouter.
 */
void adjRelation(Relations g, char *nom1, char *nom2, rtype id)
{
    if (g == NULL)
    {
        fprintf(stderr, "graphe non initialisé \n");
        exit(EXIT_FAILURE);
    }
    if (g->lstg_relations == NULL)
    {
        fprintf(stderr, "liste non initialisés\n");
        exit(EXIT_FAILURE);
    }
    listeg lstg_tmp = g->lstg_relations;
    Sommet s1 = NULL;
    Entite e1 = NULL;
    Sommet s2 = NULL;
    Entite e2 = NULL;

    while (lstg_tmp != NULL)
    {
        if (compSommet(lstg_tmp->val, nom1) == true)
        {
            s1 = (Sommet)lstg_tmp->val;
            e1 = s1->x;
        }
        if (compSommet(lstg_tmp->val, nom2) == true)
        {
            s2 = (Sommet)lstg_tmp->val;
            e2 = s2->x;
        }
        lstg_tmp = lstg_tmp->suiv;
    }
    detruire(lstg_tmp);

    Arc a1 = nouvArc(e2, id);
    Arc a2 = nouvArc(e1, id);
    if (estvide(s1->larcs) == true && estvide(s2->larcs) == true)
    {
        s1->larcs = adjtete(s1->larcs, a1);
        s2->larcs = adjtete(s2->larcs, a2);
    }
    if (estvide(s1->larcs) == false && estvide(s2->larcs) == true)
    {
        s2->larcs = adjtete(s2->larcs, a2);
        if (existeArc(s1->larcs, e2->nom, id) == false)
        {
            s1->larcs = adjqueue(s1->larcs, a1);
        }
    }
    if (estvide(s1->larcs) == true && estvide(s2->larcs) == false)
    {
        s1->larcs = adjtete(s1->larcs, a1);
        if (existeArc(s2->larcs, e1->nom, id) == false)
        {
            s2->larcs = adjqueue(s2->larcs, a2);
        }
    }
    if (estvide(s1->larcs) == false && estvide(s2->larcs) == false)
    {
        if (existeArc(s1->larcs, e2->nom, id) == false && existeArc(s2->larcs, e1->nom, id) == false)
        {
            s1->larcs = adjqueue(s1->larcs, a1);
            s2->larcs = adjqueue(s2->larcs, a2);
        }
    }
}
////////////////////////////////////////
// Exercice 4: Explorer les relations entre personnes

// 4.1 listes de relations
/**
 * @brief Cette fonction renvoie la liste des entités en relation avec l'entité x dans le graphe g.
 * @param g le graphe contenant les relations
 * @param x le nom de l'entité recherchée
 * @return la liste des entités en relation avec x
 */
listeg en_relation(Relations g, char *x)
{
    listeg lstg_nouv = g->lstg_relations;
    listeg tmp = rech(lstg_nouv, x, compSommet);
    Sommet sommet = (Sommet)tmp->val;
    detruire(tmp);
    return sommet->larcs;
}

/**
 * @brief Retourne une liste de tous les chemins de longueur 2 reliant les entités x et y dans le graphe g.
 * @param g Le graphe contenant les entités et relations
 * @param x Le nom de la première entité
 * @param y Le nom de la deuxième entité
 * @return La liste des chemins de longueur 2 reliant les deux entités
 */
listeg chemin2(Relations g, char *x, char *y)
{
    listeg retour = listegnouv();
    listeg lstg_rel = en_relation(g, x);
    while (!estvide(lstg_rel))
    {
        listeg lstg_tmp = en_relation(g, ((Arc)lstg_rel->val)->x->nom);
        listeg lstg_rech = rech(lstg_tmp, y, compArc);
        if (!estvide(lstg_rech))
        {
            retour = adjtete(retour, ((Arc)lstg_rel->val)->x);
        }
        lstg_rel = lstg_rel->suiv;
        detruire(lstg_rech);
    }
    return retour;
}

// // 4.2 verifier un lien de parente
// // PRE CONDITION: strcmp(x,y)!=0
/**
 * @brief Vérifie s'il existe un lien de parenté entre deux entités.
 * @param g Le graphe contenant les entités et leurs relations.
 * @param x Le nom de la première entité.
 * @param y Le nom de la deuxième entité.
 * @return Retourne true si un lien de parenté existe entre les deux entités, sinon false.
 */
bool ont_lien_parente(Relations g, char *x, char *y)
{
    listeg lstg = en_relation(g, x);
    bool retour = false;
    while (lstg != NULL)
    {
        if (compArc(lstg->val, y) == true)
        {
            Arc a = (Arc)lstg->val;
            if (est_lien_parente(a->t) == true)
            {
                retour = true;
            }
        }
        lstg = lstg->suiv;
    }
    return retour;
}

/**
 * @brief Vérifie si deux personnes sont directement connectées dans le graphe par un lien de parenté, de connaissance ou professionnel.
 * @param g Le graphe de relations
 * @param x Le nom de la première personne
 * @param y Le nom de la deuxième personne
 * @return true si les deux personnes sont directement connectées, false sinon
 */
// Fonction auxiliaire
bool connaisse_direct(Relations g, char *x, char *y)
{
    listeg lstg = en_relation(g, x);
    bool retour = false;
    while (lstg != NULL)
    {
        if (compArc(lstg->val, y) == true)
        {
            Arc a = (Arc)lstg->val;
            bool parent = est_lien_parente(a->t);
            bool connait = est_lien_connaissance(a->t);
            bool profession = est_lien_professionel(a->t);
            if (parent || connait || profession)
            {
                retour = true;
            }
        }
        lstg = lstg->suiv;
    }
    return retour;
}
// 4.3 tester connaissances
// PRE CONDITION: les sommets correspondants � x et y sont de type PERSONNE// PRE CONDITION: strcmp(x,y)!=0
/**
 * @brief Vérifie si deux entités se connaissent directement ou indirectement à travers une chaîne de connaissances.
 * @param g le graphe de relations
 * @param x le nom de la première entité
 * @param y le nom de la deuxième entité
 * @return true si les deux entités se connaissent, false sinon
 */
bool se_connaissent(Relations g, char *x, char *y)
{
    if (connaisse_direct(g, x, y) == true)
    {
        return true;
    }
    listeg lstg = chemin2(g, x, y);
    bool retour = false;
    listeg temp = lstg;
    while (temp != NULL)
    {
        Entite e = (Entite)temp->val;
        if (ont_lien_parente(g, x, e->nom) == true && ont_lien_parente(g, e->nom, y) == true)
        {
            retour = true;
        }
        temp = temp->suiv;
    }
    detruire(lstg);
    return retour;
}
// PRE CONDITION: les sommets correspondants � x et y sont de type PERSONNE // PRE CONDITION: strcmp(x,y)!=0
/**
 * @brief Vérifie si deux entités peuvent se connaître indirectement
 * et ont une probabilité de se connaître plutôt faible.
 * @param g Le graphe de relations
 * @param x Le nom de la première entité
 * @param y Le nom de la deuxième entité
 * @return Vrai si les deux entités peuvent se connaître indirectement
 * et ont une probabilité de se connaître plutôt faible, faux sinon.
 */
bool se_connaissent_proba(Relations g, char *x, char *y)
{
    if (se_connaissent(g, x, y) == true)
    {
        return false;
    }
    listeg lstg = chemin2(g, x, y);
    bool retour = false;
    listeg temp = lstg;
    while (temp != NULL)
    {
        Entite e = (Entite)temp->val;
        if ((ont_lien_parente(g, x, e->nom) == false && ont_lien_parente(g, e->nom, y) == true) || (ont_lien_parente(g, x, e->nom) == true && ont_lien_parente(g, e->nom, y) == false))
        {
            retour = true;
        }
        temp = temp->suiv;
    }
    detruire(lstg);
    return retour;
}
// PRE CONDITION: les sommets correspondants � x et y sont de type PERSONNE
// PRE CONDITION: strcmp(x,y)!=0
/**
 * @brief Vérifie si deux entités peuvent éventuellement se connaître à travers un chemin indirect
 * dans le graphe g. Renvoie true si c'est le cas, false sinon.
 * @param g Le graphe de relations
 * @param x Le nom de la première entité
 * @param y Le nom de la deuxième entité
 * @return  Un booléen indiquant si les entités peuvent se connaître éventuellement
 */
bool se_connaissent_peutetre(Relations g, char *x, char *y)
{
    if (connaisse_direct(g, x, y) == true || se_connaissent_proba(g, x, y) == true)
    {
        return false;
    }
    listeg lstg = chemin2(g, x, y);
    bool retour = false;
    if (lstg != NULL)
    {
        retour = true;
    }
    detruire(lstg);
    return retour;
}

// ////////////////////////////////////////
// // Exercice 5: Affichages

/**
 * @brief Affiche tous les éléments d'une liste chaînée en utilisant une fonction de rappel spécifique.
 * @param l La liste chaînée à afficher.
 * @param aff La fonction de rappel qui sera appelée sur chaque élément de la liste pour l'affichage.
 */
void affichelg(listeg l, void (*aff)(void *))
{
    while (l != NULL)
    {
        // Appel de la fonction de rappel "aff" sur la valeur de chaque élément
        aff(l->val);
        l = l->suiv;
    }
}

/**
 * @brief Affiche une entité en fonction de son type.
 * @param x Le pointeur vers l'entité à afficher.
 */
void afficheEntite(void *x)
{
    Entite e = (Entite)x;
    printf("%s : ", e->nom);
    if (e->ident == PERSONNE)
    {
        printf("PERSONNE\n");
    }
    else if (e->ident == OBJET)
    {
        printf("OBJET\n");
    }
    else if (e->ident == ADRESSE)
    {
        printf("ADRESSE\n");
    }
    else if (e->ident == VILLE)
    {
        printf("VILLE\n");
    }
    else
    {
        printf("INCONNU\n");
    }
}
/**
 * @brief Affiche un arc en reliant un type d'entité à un autre via un type de relation.
 * @param x Le pointeur vers l'arc à afficher.
 */
void afficheArc(void *x)
{
    Arc a = (Arc)x;
    printf("-- %s -->", toString(a->t));
    void *entite = a->x;
    afficheEntite(entite);
}

// ////////////////////////////////////////
// // Exercice 6: Parcours
/**
 * @brief Affiche les entités liées à l'entité spécifiée dans le graphe de relations et leur degré de séparation par rapport à cette entité.
 * @param r Le graphe de relations à utiliser.
 * @param x Le nom de l'entité de départ.
 */
void affiche_degre_relations(Relations r, char *x)
{
    listeg lstg_visite = listegnouv();
    listeg lstg = listegnouv();
    listeg lstg2 = listegnouv();
    listeg relations = en_relation(r, x);
    listeg som = rech(r->lstg_relations, x, compSommet);
    lstg_visite = adjtete(lstg_visite, ((Sommet)som->val)->x);
    detruire(som);
    for (; !estvide(relations); relations = relations->suiv)
    {
        lstg = adjqueue(lstg, ((Arc)relations->val)->x);
    }
    printf("%s\n", x);
    int degre = 1;
    while (!estvide(lstg))
    {
        printf("-- %d\n", degre++);
        listeg lstgIter = lstg;
        for (; !estvide(lstgIter); lstgIter = lstgIter->suiv)
        {
            printf("%s\n", ((Entite)lstgIter->val)->nom);
        }
        while (!estvide(lstg))
        {
            char *suivant = ((Entite)tete(lstg))->nom;
            lstg = suptete(lstg);
            listeg relations = en_relation(r, suivant);
            for (; !estvide(relations); relations = relations->suiv)
            {
                listeg comp = rech(lstg_visite, ((Arc)relations->val)->x->nom, compEntite);
                listeg lstg_comp = rech(lstg, ((Arc)relations->val)->x->nom, compEntite);
                listeg lstg_comp2 = rech(lstg2, ((Arc)relations->val)->x->nom, compEntite);
                if (estvide(comp) && estvide(lstg_comp) && estvide(lstg_comp2))
                {
                    listeg sommetFils = rech(r->lstg_relations, ((Arc)relations->val)->x->nom, compSommet);
                    lstg2 = adjqueue(lstg2, ((Sommet)sommetFils->val)->x);
                    detruire(sommetFils);
                }
                detruire(comp);
                detruire(lstg_comp);
            }
            listeg sommetSuivant = rech(r->lstg_relations, suivant, compSommet);
            lstg_visite = adjtete(lstg_visite, ((Sommet)sommetSuivant->val)->x);
            detruire(sommetSuivant);
        }
        lstg = lstg2;
        lstg2 = listegnouv();
    }
    detruire(lstg_visite);
}

int main()
{
    int i, j;
    Relations r;
    relationInit(&r);
    // ajouter les entites de l'exemple
    char *tabe[] = {"KARL", "LUDOVIC", "CELINE", "CHLOE", "GILDAS", "CEDRIC", "SEVERINE",
                    "PEUGEOT 106", "1, RUE DE LA RUE", "STRASBOURG"};
    for (i = 0; i < 7; i++)
        adjEntite(r, tabe[i], PERSONNE);
    adjEntite(r, tabe[7], OBJET);
    adjEntite(r, tabe[8], ADRESSE);
    adjEntite(r, tabe[9], VILLE);
    // ajouter les relations de l'exemple
    adjRelation(r, tabe[0], tabe[1], FRERE);
    adjRelation(r, tabe[0], tabe[2], AMI);
    adjRelation(r, tabe[0], tabe[3], CONNAIT);
    adjRelation(r, tabe[0], tabe[5], COUSIN);
    adjRelation(r, tabe[0], tabe[7], PROPRIETAIRE);
    adjRelation(r, tabe[0], tabe[8], PROPRIETAIRE);
    adjRelation(r, tabe[3], tabe[4], VIT);
    adjRelation(r, tabe[5], tabe[6], EPOUX);
    adjRelation(r, tabe[5], tabe[8], LOCATAIRE);
    adjRelation(r, tabe[7], tabe[8], DECOUVERT);
    adjRelation(r, tabe[8], tabe[9], SITUE);

    // explorer les relations
    printf("%s est en relation avec:\n", tabe[0]);
    affichelg(en_relation(r, tabe[0]), afficheArc);
    printf("\n");

    for (i = 0; i < 7; i++)
        for (j = i + 1; j < 10; j++)
        {
            printf("<%s> et <%s> ont les relations communes:\n", tabe[i], tabe[j]);
            affichelg(chemin2(r, tabe[i], tabe[j]), afficheEntite);
            printf("\n");
        }
    printf("\n\n");

    for (i = 0; i < 10; i++)
        for (j = i + 1; j < 10; j++)
        {
            printf("<%s> et <%s> ont lien de parente: %s\n",
                   tabe[i], tabe[j], ont_lien_parente(r, tabe[i], tabe[j]) ? "vrai" : "faux");
        }
    printf("\n");
    for (i = 0; i < 7; i++)
    {
        for (j = i + 1; j < 7; j++)
        {
            printf("<%s> et <%s> se connaissent: %s\n",
                   tabe[i], tabe[j], se_connaissent(r, tabe[i], tabe[j]) ? "vrai" : "faux");
            printf("<%s> et <%s> se connaissent tres probablement: %s\n",
                   tabe[i], tabe[j], se_connaissent_proba(r, tabe[i], tabe[j]) ? "vrai" : "faux");
            printf("<%s> et <%s> se connaissent peut etre: %s\n",
                   tabe[i], tabe[j], se_connaissent_peutetre(r, tabe[i], tabe[j]) ? "vrai" : "faux");
        }
        printf("\n");
    }
    affiche_degre_relations(r, tabe[3]);
    relationFree(&r);
    printf("\nPRESS RETURN\n");
    char buff[64];
    fscanf(stdin, "%s", buff);

    return 0;
}
