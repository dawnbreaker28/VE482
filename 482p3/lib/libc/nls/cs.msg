$set 1
$ EPERM
1 Operace nen� povolena
$ ENOENT
2 Neexistuj�c� soubor nebo adres��
$ ESRCH
3 Proces neexistuje
$ EINTR
4 Syst�mov� vol�n� p�eru�eno
$ EIO
5 Vstupn�/v�stupn� chyba
$ ENXIO
6 Za��zen� nen� nakonfigurov�no
$ E2BIG
7 Seznam argument� je p��li� dlouh�
$ ENOEXEC
8 Chyba form�tu spu�t�n�ho souboru
$ EBADF
9 �patn� souborov� deskriptor
$ ECHILD
10 Neexistuje ��dn� potomek procesu
$ EDEADLK
11 Zabr�n�no uv�znut� (deadlock) prost�edku
$ ENOMEM
12 Nedostatek pam�ti
$ EACCES
13 P��stup odm�tnut
$ EFAULT
14 Chybn� adresa
$ ENOTBLK
15 Vy�adov�no blokov� za��zen�
$ EBUSY
16 Zdroj nebo za��zen� je zanepr�zdn�no
$ EEXIST
17 Soubor existuje
$ EXDEV
18 Odkaz vede na jin� za��zen�
$ ENODEV
19 Operace nen� za��zen�m podporov�na
$ ENOTDIR
20 Toto nen� adres��
$ EISDIR
21 Toto je adres��
$ EINVAL
22 Chybn� argument
$ ENFILE
23 P��li� mnoho otev�en�ch soubor� v syst�mu
$ EMFILE
24 P��li� mnoho otev�en�ch soubor�
$ ENOTTY
25 Pro dan� za��zen� nevhodn� ioctl
$ ETXTBSY
26 S textov�m souborem se pracuje
$ EFBIG
27 Soubor je p��li� velk�
$ ENOSPC
28 Na za��zen� nen� voln� m�sto
$ ESPIPE
29 Neplatn� lseek(2)
$ EROFS
30 Souborov� syst�m je pouze pro �ten�
$ EMLINK
31 P��li� mnoho odkaz�
$ EPIPE
32 P�eru�en� roura
$ EDOM
33 ��seln� argument mimo defini�n� obor
$ ERANGE
34 V�sledek p��li� velk� nebo p��li� mal�
$ EAGAIN, EWOULDBLOCK
35 Prost�edek je do�asn� nedostupn�
$ EINPROGRESS
36 Operace nyn� prob�h�
$ EALREADY
37 Operace ji� prob�h�
$ ENOTSOCK
38 Socketov� operace na ne�em, co nen� socket
$ EDESTADDRREQ
39 Vy�adov�na adresa c�le
$ EMSGSIZE
40 Zpr�va je p��li� dlouh�
$ EPROTOTYPE
41 Protokol nepodporuje dan� typ socketu
$ ENOPROTOOPT
42 Protokol nen� dostupn�
$ EPROTONOSUPPORT
43 Protokol nen� podporov�n
$ ESOCKTNOSUPPORT
44 Typ socketu nen� podporov�n
$ EOPNOTSUPP
45 Operace nen� podporov�na
$ EPFNOSUPPORT
46 Rodina protokol� nen� podporov�na
$ EAFNOSUPPORT
47 Rodina adres nen� protokolem podporov�na
$ EADDRINUSE
48 Adresa je ji� pou��v�na
$ EADDRNOTAVAIL
49 Nen� mo�no p�id�lit po�adovanou adresu
$ ENETDOWN
50 S�� je odpojena
$ ENETUNREACH
51 S�� je nedosa�iteln�
$ ENETRESET
52 S�� zru�ila spojen� po resetu
$ ECONNABORTED
53 Program zp�sobil ukon�en� spojen�
$ ECONNRESET
54 Spojen� zru�eno partnerem
$ ENOBUFS
55 Vyrovn�vac� pam� nen� k dispozici
$ EISCONN
56 Socket je ji� u� p�ipojen
$ ENOTCONN
57 Socket nen� p�ipojen
$ ESHUTDOWN
58 Nen� mo�no pos�lat po shutdownu socketu
$ ETOOMANYREFS
59 P��li� mnoho referenc�: nelze spojit
$ ETIMEDOUT
60 P�ekro�en �asov� limit pokusu o spojen�
$ ECONNREFUSED
61 Spojen� odm�tnuto
$ ELOOP
62 P��li� mnoho �rovn� symbolick�ch odkaz�
$ ENAMETOOLONG
63 Jm�no souboru p��li� dlouh�
$ EHOSTDOWN
64 Vzd�len� uzel je odpojen
$ EHOSTUNREACH
65 Neexistuje cesta ke vzd�len�mu uzlu
$ ENOTEMPTY
66 Adres�� nen� pr�zdn�
$ EPROCLIM
67 P��li� mnoho proces�
$ EUSERS
68 P��li� mnoho u�ivatel�
$ EDQUOT
69 Diskov� kv�ta p�ekro�ena
$ ESTALE
70 Propadnut� souborov� ukazatel pro NFS
$ EREMOTE
71 P��li� mnoho �rovn� vzd�len�ho v cest�
$ EBADRPC
72 �patn� RPC struktura
$ ERPCMISMATCH
73 RPC: Nekompatibiln� verze RPC
$ EPROGUNAVAIL
74 RPC: Program nen� dostupn�
$ EPROGMISMATCH
75 RPC: Neshoda programu nebo verze
$ EPROCUNAVAIL
76 RPC: Procedura nen� dostupn�
$ ENOLCK
77 Z�mky souborov�ch z�znam� nejsou dostupn�
$ ENOSYS
78 Funkce nen� implementov�na
$ EFTYPE
79 Nevhodn� typ nebo form�t souboru
$ EAUTH
80 Chyba autentifikace
$ ENEEDAUTH
81 Je t�eba se autentifikovat
$ EIDRM
82 Identifik�tor zru�en
$ ENOMSG
83 Neexistuje zpr�va ��dan�ho typu
$ EOVERFLOW
84 Hodnota je pro dan� datov� typ p��li� velk�
$ EILSEQ
85 Neplatn� posloupnost bajt�
$ ENOTSUP
86 Nepodporov�no
$ ECANCELED
87 Operace strornov�na
$ EBADMSG
88 �patn� nebo poru�en� zpr�va
$ ENODATA
89 ��dn� zpr�va nen� dostupn�
$ ENOSR
90 ��dn� STREAM prost�edky
$ ENOSTR
91 Nen� STREAM
$ ETIME
92 Vypr�el �asov� limit STREAM ioctl
$ ENOATTR
93 Atribut nebyl nalezen
$ EMULTIHOP
94 Pokus o spojen� p�es v�ce uzl�
$ ENOLINK
95 Odkaz byl zp�etrh�n
$ EPROTO
96 Chyba protokolu
$set 2
$ SIGHUP
1 Termin�l odpojen
$ SIGINT
2 P�eru�en�
$ SIGQUIT
3 Konec
$ SIGILL
4 Chybn� instrukce
$ SIGTRAP
5 Lad�c� instrukce
$ SIGABRT
6 N�siln� ukon�en�
$ SIGEMT
7 Emulovan� instrukce
$ SIGFPE
8 V�jimka pohybliv� ��rky
$ SIGKILL
9 Zabito
$ SIGBUS
10 Chyba sb�rnice
$ SIGSEGV
11 Chyba segmentace
$ SIGSYS
12 �patn� syst�move vol�n�
$ SIGPIPE
13 Broken pipe
$ SIGALRM
14 Alarm �asova�
$ SIGTERM
15 Ukon�eno
$ SIGURG
16 Nal�hav� I/O po�adavek
$ SIGSTOP
17 Pozastaveno (sign�l)
$ SIGTSTP
18 Pozastaveno
$ SIGCONT
19 Pokra�ov�n�
$ SIGCHLD
20 Potomek procesu ukon�en
$ SIGTTIN
21 Pozastaveno (termin�lov� vstup)
$ SIGTTOU
22 Pozastaveno (termin�lov� v�stup)
$ SIGIO
23 Vstup/v�stup mo�n�
$ SIGXCPU
24 P�ekro�en �asov� limit pro CPU
$ SIGXFSZ
25 P�ekro�en limit velikosti souboru
$ SIGVTALRM
26 Vypr�el virtu�ln� �asova�
$ SIGPROF
27 Vypr�el profilovac� �asova�
$ SIGWINCH
28 Velikost okna zm�n�na
$ SIGINFO
29 Informa�n� po�adavek
$ SIGUSR1
30 U�ivatelsk� sign�l 1
$ SIGUSR2
31 U�ivatelsk� sign�l 2
$ SIGPWR
32 Selh�n�/nastartov�n� nap�jen�
