$ $XConsortium: dtcopy.msg /main/5 1996/11/19 18:29:23 rws $
$ *****************************************************************************  
$ **  
$ **  File:        dtcopy.msg  
$ **  
$ **  Project:     CDE File Manager  
$ **  
$ *****************************************************************************  
$quote "

$set 2
$ ****** Module: main_dtcopy.c ******  

3 "fichier"

4 "fichier(s)"

5 "sous-dossier"

6 "sous-dossier(s)"

7 "Erreur(s): aucune"

8 "Erreur(s): %d"

10 "Syntaxe: %s [options ...] source cible\n"

11 "Gestionnaire de fichiers - D�placer un dossier"

12 "Gestionnaire de fichiers - Copier un r�pertoire"

13 "%s n'a(ont) pas �t� supprim�(s) suite � des erreurs."

14 "Op�ration termin�e."

15 "Annul�(s) dans"
$ ** Message 20 - 32  
$ ** LongFileOpNames ... message number = op + 20.  

20 "traitement de"

21 "ouverture de"

22 "ouverture de"

23 "ouverture de"

24 "lecture de lien"

25 "suppression de "

26 "copie de"

27 "cr�ation du r�pertoire"

28 "copie de lien"

29 "cr�ation de lien"

30 "en cours"

31 "est une copie"

32 "est un lien"

33 "renommer"

$set 3        Redefine set#

$ ****** Module: copydialog.c ******  

1 "Reprendre"

2 "Suspendre"

3 "D�placer:"

4 "Copier:"

5 "Dans dossier:"

7 "Cette action va annuler l'op�ration de copie. Tous les\n\
fichiers copi�s resteront dans le dossier de destination."

10 "Cette action va annuler le d�placement. Tous les fichiers\n\
d�plac�s resteront dans le dossier de destination."

11 "Copier dossier - Avertissement"

12 "D�placer dossier - Avertissement"

13 "Annuler copie"

14 "Continuer copie"

15 "Annuler d�placement"

16 "Continuer d�placement"

17 "D�plac�"

18 "Copi�"

19 Impossible de d�placer le dossier sur lui-m�me\n\
%s\n\n

20 Impossible de copier le dossier sur lui-m�me\n\
%s\n\n


$set 4        Redefine set#

$ ****** Module: errordialog.c ******  

1 "Erreur(s) %s\n\
%s"

2 "Pause si erreur"

3 "Copie de dossier - Erreur"

4 "D�placement de dossier - Erreur"

5 "D�placement de dossier - Erreur"

6 "Copie d'objet - Erreur"

7 "Suppression d'objet (corbeille) - Erreur"

8 "Vous n'�tes pas autoris� � mettre l'objet\n\n\
    %s\n\n\
dans la corbeille.\n\n\
Pour vous accorder l'autorisation d'acc�der en lecture \n\
� l'objet, utilisez l'option Modifier les droits d'acc�s\n\
du menu instantan� de l'objet ou du menu S�lectionn�(s).\n\n\n\
Remarque: Si l'objet est un dossier, vous devez \n\
�galement avoir acc�s en lecture � tous les objets\n\
qu'il contient pour pouvoir le mettre dans la corbeille."

9 Impossible d'ouvrir %s


$set 5        Redefine set#

$ ****** Module: overwrtdialog.c ******  

1 "Un fichier appel�\n\
%s\n\
existe d�j� dans le dossier\n\
%s"

2 "D�placement de dossier - Ecraser le fichier"

3 "Remplacer le fichier existant"

4 "Modifier le nom du fichier existant en:"

5 "Modifier le nom du nouvel objet en:"

6 "Ignorer ce fichier"

7 "Appliquer cette action aux conflits de noms"

8 "Action:"

9 "Copie de dossier - Remplacer le fichier"

10 "%s\n\
existe d�j�: choisissez un autre nom."

11 "Remplacement de fichier - Erreur"

12 "%s\n\
ne peut pas �tre renomm� en\n\
%s\n\
%s"

$set 6        Redefine set#

$ ****** Module: utils.c ******  
$ ** Button labels.  

1 "OK"

2 "Suspendre"

3 "Annuler"

4 "Aide"

5 "Copie de r�pertoire - Aide"

6 "Continuer"

7 "Annuler la copie"

8 "Annuler le d�placement"
