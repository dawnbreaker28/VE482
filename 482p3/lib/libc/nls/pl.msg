$set 1
$ EPERM
1 Operacja nie dozwolona
$ ENOENT
2 Nie ma takiego pliku ani katalogu
$ ESRCH
3 Nie ma takiego procesu
$ EINTR
4 Przerwane wywo�anie systemowe
$ EIO
5 B��d wej�cia/wyj�cia
$ ENXIO
6 Urz�dzenie nie skonfigurowane
$ E2BIG
7 Lista argument�w jest za d�uga
$ ENOEXEC
8 B��dny format pliku wykonywalnego
$ EBADF
9 Z�y deskryptor pliku
$ ECHILD
10 Brak proces�w potomnych
$ EDEADLK
11 Unikni�to zakleszczenia zasob�w
$ ENOMEM
12 Brak pami�ci do przydzia�u
$ EACCES
13 Brak dost�pu
$ EFAULT
14 Z�y adres
$ ENOTBLK
15 Wymagane urz�dzenie blokowe
$ EBUSY
16 Urz�dzenie zaj�te
$ EEXIST
17 Plik istnieje
$ EXDEV
18 Powi�zanie miedzy urz�dzeniami
$ ENODEV
19 Operacja nie obs�ugiwana przez urz�dzenie
$ ENOTDIR
20 To nie jest katalog
$ EISDIR
21 To jest katalog
$ EINVAL
22 B��dny argument
$ ENFILE
23 Za du�o otwrtych plik�w w systemie
$ EMFILE
24 Za du�o otwartych plik�w
$ ENOTTY
25 Niew�a�ciwy dost�p do urz�dzenia
$ ETXTBSY
26 Plik tekstowy zaj�ty
$ EFBIG
27 Plik zbyt du�y
$ ENOSPC
28 Nie ma miejsca na urz�dzeniu
$ ESPIPE
29 B��dne przesuni�cie
$ EROFS
30 System plik�w tylko do odczytu
$ EMLINK
31 Za du�o link�w
$ EPIPE
32 Przerwany potok
$ EDOM
33 Argument liczbowy spoza zakresu
$ ERANGE
34 Za du�y wynik
$ EAGAIN, EWOULDBLOCK
35 Zasoby chwilowo niedost�pne
$ EINPROGRESS
36 Operacja jest w�a�nie wykonywana
$ EALREADY
37 Operacja jest ju� wykonywana
$ ENOTSOCK
38 Operacja na obiekcie, kt�ry nie jest gniazdem
$ EDESTADDRREQ
39 Wymagany adres przeznaczenia
$ EMSGSIZE
40 Wiadomo�� za d�uga
$ EPROTOTYPE
41 Ty protoko�u nie pasuje do gniazda
$ ENOPROTOOPT
42 Protoc� nie jest dost�pny
$ EPROTONOSUPPORT
43 Protoc� nie jest obs�ugiwany
$ ESOCKTNOSUPPORT
44 Nie obs�ugiwany typ gniazda
$ EOPNOTSUPP
45 Operacja nie obs�ugiwana
$ EPFNOSUPPORT
46 Nie obs�ugiwana rodzina protoko��w
$ EAFNOSUPPORT
47 Rodzina adres�w nie obs�ugiwana przez rodzin� protoko��w
$ EADDRINUSE
48 Adres jest aktualnie w u�yciu
$ EADDRNOTAVAIL
49 Nie mo�na przypisa� ��danego adresu
$ ENETDOWN
50 Sie� nie dzia�a
$ ENETUNREACH
51 Sie� jest niedost�pna
$ ENETRESET
52 Sie� przerwa�a po��czenie po resecie
$ ECONNABORTED
53 Oprogramowanie spowodowa�o przerwanie po��czenia
$ ECONNRESET
54 Po��czenie zerwane przez drug� stron�
$ ENOBUFS
55 Brak miejsca w buforze
$ EISCONN
56 Gniazdo jest ju� po��czone
$ ENOTCONN
57 Gniazdo nie jest po��czone
$ ESHUTDOWN
58 Nie mo�na wysy�a� po zamkni�ciu gniazda
$ ETOOMANYREFS
59 Za du�o powi�za�: dowi�zanie nie mo�liwe
$ ETIMEDOUT
60 Przekroczono czas oczekiwania na po��czenie
$ ECONNREFUSED
61 Po��czenie odrzucone
$ ELOOP
62 Za du�o wzajemnych symlink�w
$ ENAMETOOLONG
63 Zbyt d�uga nazwa pliku
$ EHOSTDOWN
64 Host jest wy��czony
$ EHOSTUNREACH
65 Brak drogi do hosta
$ ENOTEMPTY
66 Katalog nie jest pusty
$ EPROCLIM
67 Za du�o proces�w
$ EUSERS
68 Zbyt wielu u�ytkownik�w
$ EDQUOT
69 Przekroczono limit miejsca na dysku
$ ESTALE
70 Uchwyt pliku NFS jest nieaktualny
$ EREMOTE
71 Za du�o poziom�w zagnie�d�enia w �cie�ce
$ EBADRPC
72 RPC b��dna struktura
$ ERPCMISMATCH
73 RPC z�a wersja
$ EPROGUNAVAIL
74 RPC program niedost�pny
$ EPROGMISMATCH
75 Z�a wersja programu
$ EPROCUNAVAIL
76 Z�a procedura dla programu
$ ENOLCK
77 Blokady nie s� dost�pne
$ ENOSYS
78 Niezaimplementowana funkcja
$ EFTYPE
79 Niew�a�ciwy typ lub format pliku
$ EAUTH
80 B��d uwierzytelnienia
$ ENEEDAUTH
81 Wymagane uwierzytelnienie
$ EIDRM
82 Identyfikator zosta� usuni�ty
$ ENOMSG
83 Brak komunikatu po�adanego typu
$ EOVERFLOW
84 Warto�� za du�a aby zapami�ta� j� w zdefiniowanym typie danych
$ EILSEQ
85 B��dna sekwencja bajt�w
$set 2
$ SIGHUP
1 Roz��czenie
$ SIGINT
2 Przerwanie
$ SIGQUIT
3 Wyj�cie
$ SIGILL
4 Nieznana instrukcja
$ SIGTRAP
5 Pu�apka debuggera/BPT
$ SIGABRT
6 Przerwanana pu�apka
$ SIGEMT
7 Pu�apka EMT
$ SIGFPE
8 B��d w obliczeniach zmiennoprzecinkowych
$ SIGKILL
9 Unicestwiony
$ SIGBUS
10 B��d szyny
$ SIGSEGV
11 Naruszenie ochrony pami�ci
$ SIGSYS
12 B��dne wywo�anie systemowe
$ SIGPIPE
13 Przerwany potok
$ SIGALRM
14 Budzik
$ SIGTERM
15 Zako�czony
$ SIGURG
16 Nag�y wypadek I/O
$ SIGSTOP
17 Zatrzymany (sygna�)
$ SIGTSTP
18 Zatrzymany
$ SIGCONT
19 Kontynuacja
$ SIGCHLD
20 Proces potomny zako�czy� prac�
$ SIGTTIN
21 Zatrzymany (wej�cie z tty)
$ SIGTTOU
22 Zatrzymany (wyj�cie z tty)
$ SIGIO
23 Wej/Wyj dozwolone
$ SIGXCPU
24 Przekroczony limit czasu procesora
$ SIGXFSZ
25 przekroczony limit wielko�ci pliku
$ SIGVTALRM
26 Wirtualny stoper wyczerpany
$ SIGPROF
27 Koniec stopera profiluj�cego
$ SIGWINCH
28 Zmiana rozmiaru okna
$ SIGINFO
29 ��danie infromacji
$ SIGUSR1
30 Sygna� u�ytkownika 1
$ SIGUSR2
31 Sygna� u�ytkownika 2
$ SIGPWR
32 Awaria zasilania/restart
