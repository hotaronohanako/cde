$ $TOG: dtinfo_start.msg /main/3 1999/09/20 13:28:30 mgreess $
$ 
$ (c) Copyright 1996 Digital Equipment Corporation.
$ (c) Copyright 1996 Hewlett-Packard Company.
$ (c) Copyright 1996 International Business Machines Corp.
$ (c) Copyright 1996 Sun Microsystems, Inc.
$ (c) Copyright 1996 Novell, Inc. 
$ (c) Copyright 1996 FUJITSU LIMITED.
$ (c) Copyright 1996 Hitachi.
$ 
$ ******************************************************************************
$ 
$set 1
$ The messages in this set will only appear in the users
$   "errorlog" file.
$ 
$ ******************************************************************************
$ 
$ Messages 1-5: These messages result from an error in a tt_* function
$    call.
$ 
1 El proceso ttsession(1) no se est� ejecutando y el servicio ToolTalk\n\
no lo puede reiniciar.
2 El identificador de proceso predeterminado actual est� desactualizado o no es v�lido.
3 La sesi�n de ToolTalk especificada est� desactualizada o no es v�lida.

$ 
$ Message 4: Do not localize the word DtInfo_Start.
$ 
4 El tipo de proceso 'DtInfo_Start' no es el\n\
nombre de un tipo de proceso instalado.

5 No se reconoce el n�mero de error.

6 No se puede invocar una operaci�n porque malloc(1) ha fallado.

$ 
$ Message 7: Do not localize the word DISPLAY.  Do not localize the
$   word XtOpenDisplay().
$ 
7 XtOpenDisplay() ha fallado.  Es posible que la variable de entorno DISPLAY\n\
no est� configurada o no sea v�lida.

$ 
$ Message 8: Do not localize the word DtAppInitialize().
$ 
8 DtAppInitialize() ha fallado.  Es posible que el entorno de escritorio\n\
no est� instalado correctamente.

$ 
$ Message 9: Do NOT localize the word DTINFOLIBDEFAULT
$ 
9 No se suministr� ninguna infobiblioteca en el mensaje '%s'.\n\
Se utilizar� el valor de la variable de entorno DTINFOLIBDEFAULT\n\
(%s) para la infobiblioteca.

$ 
$ Message 10: Do NOT localize the word DTINFOLIBDEFAULT
$ 
10 No se suministr� ninguna infobiblioteca en el mensaje '%s'\n\
y no se defini� la variable de entorno DTINFOLIBDEFAULT.

$ 
$ Messages 11-16: These message are the result of the dtinfo_start
$   getting an error while trying to parse a ToolTalk message.
$ 
$   Do NOT localize the word NULL
$   
11 La operaci�n de mensaje '%d' no est� soportada.

12 El mensaje '%s' no cuenta con la cantidad de\n\
argumentos necesaria '%d'.

13 El mensaje '%s' ha especificado un nombre de operaci�n NULL.\n\
Se invocar� la acci�n '%s'.

14 El mensaje '%s' ha especificado un anfitri�n de ejecuci�n NULL.

15 El mensaje '%s' ha especificado una ubicaci�n NULL.

16 El mensaje '%s' ha especificado un tema NULL.

$set 2
$ *****************************************************************************
$ **
$ ** Message set for  DieFromToolTalkError Dialog
$ **
$ *****************************************************************************
$ These are the messages for the ToolTalk error dialog
$ "-NEW"
1 Dtinfo: Error
$ "-NEW"
2 "Could not connect to ToolTalk:\n%s\nExiting ..."
$ "-NEW"
3 OK
