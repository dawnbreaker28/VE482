$set 1
$ EPERM
1 Operation nicht erlaubt
$ ENOENT
2 Datei oder Verzeichnis nicht gefunden
$ ESRCH
3 Prozess nicht gefunden
$ EINTR
4 Interrupt innerhalb eines Systemaufrufs
$ EIO
5 Ein/Ausgabefehler
$ ENXIO
6 Ger�t ist nicht konfiguriert
$ E2BIG
7 Argumentliste ist zu lang
$ ENOEXEC
8 Die Datei hat kein bekanntes ausf�hrbares Format
$ EBADF
9 Ung�ltiger Dateideskriptor
$ ECHILD
10 Kein Kindprozess
$ EDEADLK
11 Ein Deadlock wurde vermieden
$ ENOMEM
12 Kann nicht genug Speicher belegen
$ EACCES
13 Zugriff verboten
$ EFAULT
14 Ung�ltige Adresse
$ ENOTBLK
15 Es wird ein Blockger�t ben�tigt
$ EBUSY
16 Das Ger�t ist belegt
$ EEXIST
17 Datei existiert bereits
$ EXDEV
18 Link zwischen verschiedenen Ger�ten
$ ENODEV
19 Die Operation wird von diesem Ger�t nicht unterst�tzt
$ ENOTDIR
20 Kein Verzeichnis
$ EISDIR
21 Ist ein Verzeichnis
$ EINVAL
22 Ung�ltiges Argument
$ ENFILE
23 Zu viele offene Dateien im gesamten System
$ EMFILE
24 Zu viele offene Dateien
$ ENOTTY
25 Ung�ltiger Ioctl f�r dieses Ger�t
$ ETXTBSY
26 Ausf�hrbare Datei wird benutzt
$ EFBIG
27 Datei zu gro�
$ ENOSPC
28 Kein Platz mehr auf dem Ger�t
$ ESPIPE
29 Ung�ltige Positionierung
$ EROFS
30 Dateisystem ist schreibgesch�tzt
$ EMLINK
31 Zu viele Links
$ EPIPE
32 Unterbrochene Pipe
$ EDOM
33 Numerisches Argument ausserhalb des Wertebereichs
$ ERANGE
34 Ergebnis zu gro� oder zu klein
$ EAGAIN, EWOULDBLOCK
35 Ressource vor�bergehend nicht verf�gbar
$ EINPROGRESS
36 Operation wird jetzt fortgesetzt
$ EALREADY
37 Operation wird bereits ausgef�hrt
$ ENOTSOCK
38 Deskriptor ist kein Socket
$ EDESTADDRREQ
39 Zieladresse ben�tigt
$ EMSGSIZE
40 Nachricht zu lang
$ EPROTOTYPE
41 Ung�ltiger Protokolltyp f�r diesen Socket
$ ENOPROTOOPT
42 Protokoll nicht verf�gbar
$ EPROTONOSUPPORT
43 Protokoll nicht unterst�tzt
$ ESOCKTNOSUPPORT
44 Sockettyp nicht unterst�tzt
$ EOPNOTSUPP
45 Operation nicht unterst�tzt
$ EPFNOSUPPORT
46 Protokollfamilie nicht unterst�tzt
$ EAFNOSUPPORT
47 Addressart wird von der Protokollfamilie nicht unterst�tzt
$ EADDRINUSE
48 Adresse wird bereits benutzt
$ EADDRNOTAVAIL
49 Kann angeforderte Adresse nicht belegen
$ ENETDOWN
50 Netzwerk nicht verf�gbar
$ ENETUNREACH
51 Netzwerk nicht erreichbar
$ ENETRESET
52 Netzwerk hat Verbindung mit Reset abgebrochen
$ ECONNABORTED
53 Software verursachte einen Verbindungsabbruch
$ ECONNRESET
54 Verbindung wurde von der Gegenstelle geschlossen
$ ENOBUFS
55 Keine Buffer verf�gbar
$ EISCONN
56 Socket ist schon verbunden
$ ENOTCONN
57 Socket ist nicht verbunden
$ ESHUTDOWN
58 Kann nach einem Socket-Shutdown nicht mehr senden
$ ETOOMANYREFS
59 Zu viele Referenzen, kann nicht verbinden
$ ETIMEDOUT
60 Verbindungsabbruch durch Zeit�berschreitung
$ ECONNREFUSED
61 Verbindung wurde abgelehnt
$ ELOOP
62 Zu viele symbolische Links (zirkul�r?)
$ ENAMETOOLONG
63 Dateiname zu lang
$ EHOSTDOWN
64 Host nicht verf�gbar
$ EHOSTUNREACH
65 Keine Route zum Host
$ ENOTEMPTY
66 Verzeichnis ist nicht leer
$ EPROCLIM
67 Zu viele Prozesse
$ EUSERS
68 Zu viele Benutzer
$ EDQUOT
69 Plattenplatzlimit ersch�pft
$ ESTALE
70 Verwaister NFS-Dateideskriptor
$ EREMOTE
71 Zu viele Fernverweise in diesem Zugriff
$ EBADRPC
72 RPC-Struktur ist ung�ltig
$ ERPCMISMATCH
73 RPC-Version stimmt nicht
$ EPROGUNAVAIL
74 RPC-Programm nicht verf�gbar
$ EPROGMISMATCH
75 Falsche Programmversion
$ EPROCUNAVAIL
76 Falsche Prozedur f�r dieses Programm
$ ENOLCK
77 Keine Dateisperren verf�gbar
$ ENOSYS
78 Funktion nicht implementiert
$ EFTYPE
79 Ung�ltiger Dateityp oder Dateiformat
$ EAUTH
80 Authentikationsfehler
$ ENEEDAUTH
81 Authentikator ben�tigt
$ EIDRM
82 Identifizierung entfernt
$ ENOMSG
83 Keine Nachricht vom gew�nschten Typ
$ EOVERFLOW
84 Wert zu gro�, um in Datentyp zu speichern
$ EILSEQ
85 Illegale Byte-Sequenz
$ ENOTSUP
86 Operation nicht unterst�tzt
$ ECANCELED
87 Operation abgebrochen
$ EBADMSG
88 Ung�ltige Nachricht
$ ENODATA
89 Keine Nachricht verf�gbar
$ ENOSR
90 Keine STREAM-Ressourcen verf�gbar
$ ENOSTR
91 Kein STREAM
$ ETIME
92 Zeit�berschreitung bei STREAM Ioctl
$ ENOATTR
93 Attribut nicht gefunden
$ EMULTIHOP
94 Multihopversuch
$ ENOLINK
95 Verbindung wurde getrennt
$ EPROTO
96 Protokollfehler
$set 2
$ SIGHUP
1 Verbindungsende
$ SIGINT
2 Unterbrechung
$ SIGQUIT
3 Programmende
$ SIGILL
4 Ung�ltiger Maschinenbefehl
$ SIGTRAP
5 Trace/BPT trap
$ SIGABRT
6 Abort trap
$ SIGEMT
7 EMT trap
$ SIGFPE
8 Flie�kommafehler
$ SIGKILL
9 Unbedingter Programmabbruch
$ SIGBUS
10 Bus-Zugriffsfehler
$ SIGSEGV
11 Illegaler Speicherzugriff
$ SIGSYS
12 Ung�ltiger Systemaufruf
$ SIGPIPE
13 Unterbrochene Pipe
$ SIGALRM
14 Wecker
$ SIGTERM
15 Beendet
$ SIGURG
16 Dringende Ein/Ausgabeanforderung
$ SIGSTOP
17 Gestoppt (Signal)
$ SIGTSTP
18 Gestoppt
$ SIGCONT
19 Fortgesetzt
$ SIGCHLD
20 Kindprozess beendet
$ SIGTTIN
21 Gestoppt (Eingabe)
$ SIGTTOU
22 Gestoppt (Ausgabe)
$ SIGIO
23 Ein/Ausgabe ist m�glich
$ SIGXCPU
24 CPU-Zeitlimit ersch�pft
$ SIGXFSZ
25 Dateigr��e hat das Limit erreicht
$ SIGVTALRM
26 Virtueller Wecker abgelaufen
$ SIGPROF
27 Profil-Wecker abgelaufen
$ SIGWINCH
28 Fenstergr��e hat sich ge�ndert
$ SIGINFO
29 Informationsanforderung
$ SIGUSR1
30 Benutzerdefiniertes Signal 1
$ SIGUSR2
31 Benutzerdefiniertes Signal 2
$ SIGPWR
32 Status�nderung der Energieversorgung
