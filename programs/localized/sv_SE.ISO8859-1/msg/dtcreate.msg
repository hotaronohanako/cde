$ $XConsortium: dtcreate.msg /main/3 1995/11/08 13:32:50 rswiston $
$ %Z%%M%        %I%  %W% %G% %U%
$ 
$   COMPONENT_NAME: dtcreate
$ 
$   FUNCTIONS: none
$ 
$   ORIGINS: 27
$ 
$ 
$   (C) COPYRIGHT International Business Machines Corp. 1993
$   All Rights Reserved
$   Licensed Materials - Property of IBM
$   US Government Users Restricted Rights - Use, duplication or
$   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
$ 
$ **   Description:
$ **   ------------
$ **   This is the source message catalog file for dtcreate.

$set 2
$ *****************************************************************************
$ **
$ ** Message set for menu options on main window
$ **
$ *****************************************************************************
10 Fil
11 F
15 �ppna...
16 O
20 Nytt
21 N
25 Spara
26 S
30 Avsluta
31 x
35 Alternativ
36 O
40 Visa specialfunktioner
41 A
42 Visa ikoner
43 I
44 F�rg
46 C
47 Monokrom
48 M
49 Visa monokroma ikoner
50 M
53 Hj�lp
54 H
60 �versikt
61 v
65 Inneh�llsf�rteckning
66 C
70 Steg-f�r-steg-anvisningar
71 T
75 Referens
76 R
80 Om hj�lpfunktionen
81 U
85 Om Skapa funktion
86 A

$set 3
$ *****************************************************************************
$ **
$ ** Message set for  main Create Action window
$ **
$ *****************************************************************************
10 Skapa funktion
12 Funktionsnamn (ikonnamn):
13 Funktionsikoner:
20 Kommando n�r funktionsikonen dubbelklickas:
21 Kommando att exekvera vid dubbelklickning:
22 Kommando n�r funktionsikonen �ppnas (dubbelklickas):
30 Hj�lptext om funktionsikonen:
32 F�nstertyp:
34 Grafisk (X-f�nster)
36 Terminal (St�ng automatiskt)
38 Terminal (St�ng manuellt)
40 Inget f�nster
50 Special
52 Grundl�ggande

$set 4
$ *****************************************************************************
$ **
$ ** Message set for  main Create Action window advanced function area
$ **
$ *****************************************************************************
10 Specialfunktioner
11 Fr�ga anv�ndarna efter f�ljande n�r funktionen �ppnas:
12 Datatyper som anv�nder funktionen:
13 L�gg till...
14 Ta bort
15 Redigera...
16 Sl�ppbara datatyper:
17 Alla datatyper
18 Endast ovanst�ende lista

$set 5
$ *****************************************************************************
$ **
$ ** Error and Information message set for  main Create Action window
$ **
$ *****************************************************************************
10 Funktionsnamnet saknas.\n\
Skriv ett namn i f�ltet 'Funktionsnamn'.
$ 
15 Exekveringskommandot saknas.\n\
Skriv ett kommando i f�ltet\n\
'Kommando n�r funktionsikonen �ppnas (dubbelklickas)'.
$ 
20 Listan 'Datatyper som anv�nder funktionen' �r tom.\n\
Du har markerat 'Endast ovanst�ende lista' i\n\
f�ltet 'Sl�ppbara datatyper'.\n\
�ndra alternativet till 'Alla datatyper'\n\
eller l�gg till minst en datatyp i listan.
$ 
25 Det finns redan en definitionsfil f�r funktioner och\n\
datatyper f�r detta funktionsnamn.\n\
Du kan avbryta Spara och �ndra funktionsnamnet\n\
eller skriva �ver den befintliga definitionsfilen.\n\
Vill du skriva �ver den befintliga filen?
$ 
30 Det saknas ett variabelnamn i f�ltet\n\
'Kommando n�r funktionsikonen �ppnas (dubbelklickas)'.\n\
L�gg till ett variabelnamn f�r det namn du har angivit\n\
i f�ltet 'Fr�ga anv�ndarna efter f�ljande n�r funktionen �ppnas'.\n\
Giltiga variabelnamn �r $*, $1, $2, ..., $9.
$ 
35 Dessa �ndringar har inte sparats.\n\
Vill du spara �ndringarna innan du avslutar?
$ 
40 De aktuella �ndringarna har inte sparats.\n\
Vill du spara funktionen innan du tar bort\n\
f�lten och anger en ny funktion?
$ 
45 De aktuella �ndringarna har inte sparats.\n\
Vill du spara �ndringarna innan du tar bort\n\
f�lten f�r att ladda en annan definitionsfil f�r funktioner?
$ 
50 Funktionsnamnet inneh�ller ett eller flera\n\
ogiltiga tecken.\n\
F�ljande tecken f�r inte anv�ndas i namn:\n\
  / \\ " ' ;  (  ) ~ ! $ { } < > # @ | &
$ 
55 Det gick inte att skapa f�ljande fil:
$ 
60 Det gick inte att �ppna f�ljande fil:
$ 
65 Det gick inte att ladda f�ljande fil eftersom den\n\
inte har skapats av verktyget Skapa funktion:
$ 
66 Det gick inte att ladda filen eftersom den har �ndrats\n\
p� n�got annat s�tt �n med Skapa funktion. Filen kan ha\n\
�ndrats med en textredigerare eller n�got annat verktyg.
$ 
67 Skapa funktion kan bara redigera filer som har skapats\n\
och redigerats med Skapa funktion.
$ 
68 Det gick inte att ladda f�ljande fil:
$ 
$  The following messages are all part of the same message dialog
70 Den nya funktionen
71 har placerats i hemmappen.
73 Den nya definitionsfilen f�r funktioner heter:
$ 
80 Det gick inte att hitta alla storlekar av ikonen\n\
som du har markerat.
$ 
85 Det gick inte att starta ikonredigeraren.
$ 
90 Det gick inte att analysera f�ljande fil:
$ 
95 Det gick inte att hitta f�ljande ikonfil i ikons�kv�gen:\n\
$ 
98 Ikonen som du har markerat finns inte i ikons�kv�gen.\n\
Du m�ste flytta ikonen till en katalog i ikons�kv�gen\n\
s� att den kan visas p� r�tt s�tt p� skrivbordet.\n\
V�lj 'OK' om du vill anv�nda ikonen.\n\
V�lj 'Avbryt' om du vill markera en annan ikon.
$ 
$ ONLY TRANSLATE  "Usage"  and  "filename"
110 Syntax: dtcreate [<filnamn>] [-?]
$ 
120 Du har inte markerat n�gon datatyp\n\
i listan 'Datatyper som anv�nder funktionen'.
125 Markera den datatyp som du vill ta bort.
130 Markera den datatyp som du vill redigera.
$ 
150 Det aktuella arbetet har inte sparats.
152 Spara inte
154 Avbryt St�ng
$ 
160 Det g�r inte att spara sessionen i filen:
162 Det g�r inte att �terst�lla sessionen fr�n filen:
$ 
$ TRANSLATORS: DO NOT TRANSLATE the word "HOME" in the following message
170 HOME milj�variabeln �r inte angiven.\n\
HOME milj�variabel m�ste anges f�r att den\n\
h�r funktionen skall sparas.


$set 6
$ *****************************************************************************
$ **
$ ** General message set for dialogs
$ **
$ *****************************************************************************
10 OK
11 Till�mpa
12 Avbryt
13 Hj�lp
14 Ta bort
18 S�k upps�ttning
19 S�k upps�ttning...
20 Redigera ikon...
31 Skapa funktion - Fel
41 Skapa funktion - Bekr�ftelse
46 Skapa funktion - Information
51 Skapa funktion - Fr�ga

$set 7
$ *****************************************************************************
$ **
$ ** Message set for Add Datatype and Edit Datatype dialogs
$ **
$ *****************************************************************************
10 L�gg till datatyp
11 Redigera datatyp
14 Namn p� datatypsfamilj:
15 S�rskilda egenskaper:
16 Redigera...
17 Hj�lptext om datatypsikonen:
18 Datatypsikoner:
21 Kommandon
22 Kommando f�r att �ppna denna datatyp:
23 Kommando f�r att skriva ut denna datatyp:
30 �ppna
31 Skriv ut

$set 8
$ *****************************************************************************
$ **
$ ** Error and Information message set for
$ **    Add Datatype and Edit Datatype dialogs
$ **
$ *****************************************************************************
10 Namnet p� datatypsfamiljen saknas.\n\
Skriv ett namn i f�ltet 'Namn p� datatypsfamilj'.
$ 
15 De s�rskilda egenskaperna saknas.\n\
Du m�ste ange egenskaperna innan datatypen kan skapas.\n\
Du anger egenskaperna genom att v�lja knappen Redigera\n\
bredvid listan S�rskilda egenskaper.
$ 
20 F�ltet 'Namn p� datatypsfamilj' inneh�ller ett eller flera\n\
ogiltiga tecken.\n\
F�ljande tecken f�r inte anv�ndas i namn:\n\
  / \\ " ' ;  (  ) ~ ! $ { } < > # @ | &
$ 
25 Det finns redan en datatypsfamilj med detta namn.\n\
�ndra namnet i f�ltet 'Namn p� datatypsfamilj'.\n\

$set 9
$ *****************************************************************************
$ **
$ ** Message set for  Identifying Characteristics dialog
$ **
$ *****************************************************************************
10 S�rskilda egenskaper
11 Inkludera alla
12 Filer
13 Mappar
14 som matchar f�ljande:
20 Namnm�nster:
21 Beh�righetsm�nster:
22 Kan l�sas
24 Kan �ndras
25 Kan k�ras
27 OCH
28 Inneh�ll:
29 M�nster:
30 Typ:
31 String
32 Byte (Hex)
33 Kort (Decimal)
34 L�ng (Decimal)
35 Start-byte:
40 L�s:
41 Skriv:
42 Exekvera:
43 P�
44 Av
45 Endera

$set 10
$ *****************************************************************************
$ **
$ ** Error and Information message set for Identifying Characteristics dialog
$ **
$ *****************************************************************************
10 Namnm�nstret saknas.\n\
Om du har markerat Namnm�nster m�ste du ange ett namnm�nster.\n\
$ 
15 Alternativet Beh�righet saknas.\n\
Om du har markerat Beh�righetsm�nster m�ste\n\
du markera ett eller flera av alternativen\n\
under Beh�righetsm�nster.
$ 
20 Inneh�llsm�nstret saknas.\n\
Om du har markerat Inneh�ll m�ste du\n\
fylla i f�ltet M�nster under Inneh�ll.
$ 
25 V�rdet p� start-byte saknas.\n\
Om du har markerat Inneh�ll m�ste du\n\
ange ett v�rde i f�ltet 'Start-byte'.
$ 
30 Du har inte markerat n�gon egenskap.\n\
Markera en eller flera av egenskaperna\n\
Namnm�nster, Beh�righetsm�nster eller Inneh�ll.
$ 
45 Namnm�nstret inneh�ller ett eller flera\n\
ogiltiga tecken.\n\
F�ljande tecken f�r inte anv�ndas\n\
i namnm�nster:\n\
  / \\ " ' ;  (  ) ~ ! $ { } < > # @ | &
$ 
46 Inneh�llsm�nstret matchar inte formatet p�\n\
den inneh�llstyp som du har markerat.\n\
�ndra formatet p� inneh�llsm�nstret eller\n\
�ndra typen s� att den matchar inneh�llsm�nstret.
$ 
47 F�ltet 'Start-byte' inneh�ller ogiltiga tecken.\n\
Detta f�lt f�r bara inneh�lla tal i decimalform.
$ 
48 N�r du anger inneh�llsm�nstret kan det h�nda att\n\
filhanteraren blir betydligt l�ngsammare.\n\
Filhanteraren m�ste n�mligen s�ka igenom inneh�llet\n\
i alla filerna i en mapp innan den kan �ppna\n\
mappen. Detta inneb�r att det tar l�ngre tid att\n\
�ppna mapparna.\n\
Av denna anledning rekommenderas du att endast anv�nda\n\
namn- och beh�righetsm�nster.

$set 11
$ *****************************************************************************
$ **
$ ** Message set for  Icon Selection Dialog
$ **
$ *****************************************************************************
10 Kataloger
11 Ikonfiler
12 Ange ikonfilnamn
20 Laddar ikoner. V�nta...
30 Ikonmappar
50 Det angivna ikonfilnamnet �r ogiltigt.\n\
Skriv ett giltigt ikonfilnamn i f�ltet\n\
'Ange ikonfilnamn'.
$ ONLY TRANSLATE  "Empty".   Do not translate the brackets "[" and "]".
60 [Tom]

$set 12
$ *****************************************************************************
$ **
$ ** Message set for  Open File Dialog
$ **
$ *****************************************************************************
10 Filter
11 Kataloger
12 Filer
13 Markering
20 �ppna fil
25 Skapa funktion - �ppna
