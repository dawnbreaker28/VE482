$set 1
$ EPERM
1 Op�ration non autoris�e
$ ENOENT
2 Fichier ou r�pertoire introuvable
$ ESRCH
3 Processus introuvable
$ EINTR
4 Appel syst�me interrompu
$ EIO
5 Erreur d'entr�e/sortie
$ ENXIO
6 P�riph�rique non configur�
$ E2BIG
7 Liste de param�tres trop longue
$ ENOEXEC
8 Erreur de format d'ex�cutable
$ EBADF
9 Descripteur de fichier invalide
$ ECHILD
10 Pas de processus fils
$ EDEADLK
11 Etreinte fatale �vit�e
$ ENOMEM
12 Plus de m�moire
$ EACCES
13 Autorisation refus�e
$ EFAULT
14 Adresse invalide
$ ENOTBLK
15 N�cessite un p�riph�rique en mode bloc
$ EBUSY
16 P�riph�rique occup�
$ EEXIST
17 Fichier existant
$ EXDEV
18 Lien hors du p�riph�rique
$ ENODEV
19 Op�ration non support�e par le p�riph�rique
$ ENOTDIR
20 N'est pas un r�pertoire
$ EISDIR
21 C'est un r�peroire
$ EINVAL
22 Param�tre invalide
$ ENFILE
23 Trop de fichiers ouverts dans le syst�me
$ EMFILE
24 Trop de fichiers ouverts
$ ENOTTY
25 Ioctl inconnu du p�riph�rique
$ ETXTBSY
26 Fichier ex�cutable utilis�
$ EFBIG
27 Fichier trop grand
$ ENOSPC
28 Plus de place sur le p�riph�rique
$ ESPIPE
29 Positionnement ill�gal
$ EROFS
30 Syst�me de fichier prot�g� en �criture
$ EMLINK
31 Trop de liens
$ EPIPE
32 Tube cass�
$ EDOM
33 Param�tre num�rique hors du domaine
$ ERANGE
34 R�sultat trop grand
$ EAGAIN, EWOULDBLOCK
35 Ressource temporairement indisponible
$ EINPROGRESS
36 Op�ration actuellement en cours
$ EALREADY
37 Op�ration d�j� en cours
$ ENOTSOCK
38 Op�ration r�serv�e aux sockets
$ EDESTADDRREQ
39 Adresse de destination n�c�ssaire
$ EMSGSIZE
40 Message trop long
$ EPROTOTYPE
41 Protocole inadapt� au socket
$ ENOPROTOOPT
42 Protocole non disponible
$ EPROTONOSUPPORT
43 Protocole non support�
$ ESOCKTNOSUPPORT
44 Type de socket non support�
$ EOPNOTSUPP
45 Op�ration non support�e
$ EPFNOSUPPORT
46 Famille de protocoles non support�e
$ EAFNOSUPPORT
47 Famille d'adresses non support� par cette famille de protocoles
$ EADDRINUSE
48 Adresse d�j� utilis�e
$ EADDRNOTAVAIL
49 Impossible d'affecter l'adresse demand�e
$ ENETDOWN
50 R�seau arr�t�
$ ENETUNREACH
51 R�seau non atteignable
$ ENETRESET
52 Connexion perdue apr�s un RAZ du r�seau
$ ECONNABORTED
53 Fin de connexion caus�e par logiciel
$ ECONNRESET
54 Connexion termin�e par le correspondant
$ ENOBUFS
55 Plus de place pour la m�moire tampon
$ EISCONN
56 Socket d�j� connect�
$ ENOTCONN
57 Socket non connect�
$ ESHUTDOWN
58 Impossible de transmettre apr�s fermeture du socket
$ ETOOMANYREFS
59 Trop de r�f�rences: impossible � r�assembler
$ ETIMEDOUT
60 D�lai de connexion expir�
$ ECONNREFUSED
61 Connexion refus�e
$ ELOOP
62 Trop de niveaux de liens symboliques
$ ENAMETOOLONG
63 Nom de fichier trop long
$ EHOSTDOWN
64 Machine arr�t�e
$ EHOSTUNREACH
65 Pas de route vers cette machine
$ ENOTEMPTY
66 R�pertoire non vide
$ EPROCLIM
67 Trop de processus
$ EUSERS
68 Trop d'utilisateurs
$ EDQUOT
69 Quota disque �puis�
$ ESTALE
70 Identificateur NFS p�rim�
$ EREMOTE
71 Trop de points de montages dans le chemin
$ EBADRPC
72 Structure RPC invalide
$ ERPCMISMATCH
73 Mauvaise version RPC
$ EPROGUNAVAIL
74 Programme RPC non disponible
$ EPROGMISMATCH
75 Mauvaise version de programme
$ EPROCUNAVAIL
76 Proc�dure inexistante
$ ENOLCK
77 Pas de verrous disponibles
$ ENOSYS
78 Fonction non impl�ment�e
$ EFTYPE
79 Type ou format de fichier inadapt�
$ EAUTH
80 Erreur lors de l'authentification
$ ENEEDAUTH
81 Authentication n�cessaire
$ EIDRM  
82 Identifiant supprim�
$ ENOMSG
83 Pas de message du type demand�
$ EOVERFLOW
84 Valeur trop grande pour stocker dans le type de donn�es
$ EILSEQ
85 S�quence d'octets ill�gale
$ ENOTSUP
86 Non support�
$ ECANCELED
87 Op�ration annul�e
$ EBADMSG
88 Message invalide ou corrompu
$ ENODATA
89 Pas de message disponible
$ ENOSR
90 Pas de ressource de type STREAM disponible
$ ENOSTR
91 N'est pas un STREAM
$ ETIME 
92 D�lai expir� pour un ioctl STREAM
$ ENOATTR 
93 Attribut non trouv�
$set 2
$ SIGHUP
1 Raccroch�
$ SIGINT
2 Interruption
$ SIGQUIT
3 Quitte
$ SIGILL
4 Instruction ill�gale
$ SIGTRAP
5 Point de trace/arr�t
$ SIGABRT
6 Avort�
$ SIGEMT
7 Appel �mulateur
$ SIGFPE
8 Exception num�rique
$ SIGKILL
9 Tu�
$ SIGBUS
10 Erreur bus
$ SIGSEGV
11 Erreur de segmentation
$ SIGSYS
12 Appel syst�me invalide
$ SIGPIPE
13 Tube cass�
$ SIGALRM
14 Alarme
$ SIGTERM
15 Termin�
$ SIGURG
16 Condition d'E/S urgente
$ SIGSTOP
17 Arr�t� par un signal
$ SIGTSTP
18 Arr�t�
$ SIGCONT
19 Reprise
$ SIGCHLD
20 Fin d'un fils
$ SIGTTIN
21 Arr�t� (lecture sur tty)
$ SIGTTOU
22 Arr�t� (�criture sur tty)
$ SIGIO
23 E/S possible
$ SIGXCPU
24 Limite du temps CPU atteinte
$ SIGXFSZ
25 Limite de taille de fichier atteinte
$ SIGVTALRM
26 Timer virtuel expir�
$ SIGPROF
27 Timer de profiling expir�
$ SIGWINCH
28 Changement de taille de la fen�tre
$ SIGINFO
29 Demande d'informations
$ SIGUSR1
30 Signal utilisateur 1
$ SIGUSR2
31 Signal utilisateur 2
$ SIGPWR
32 Coupure/reprise d'alimentation
