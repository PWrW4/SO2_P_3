# Opis
Projekt ma symulować piętro uczelni wraz z funkcjonującymi pracownikami/studentami.

## Wątki:
### Studenci (kilkadziesiąt)
uczestniczą w zajęciach(pracują, mają problem który rozwiązuje prowadzący), uczą się na ławce w korytarzu, chodzą do dziekanatu po dokumenty 
### Prowadzący (kilkunastu)
prowadzi zajęcia, idzie na nie, pomaga studentom przy problemach na zajęciach 
### Pani z dziekanatu (kilka)
Konkuruje z pozostałymi pracownikami dziekanatu o pieczątki. Posiadając 2, na prośbę studenta może produkować dokumenty określonego typu i umieszczać je w buforze.
### Pani Szatniarka (kilka)
wydaje/pobiera kurtki, oddaje/pobiera numerki.
Każdy może iść do toalety i pobrać papier toaletowy z magazynu.

## Zasoby:
### Sale
stanowiska jedno/wielo osobowe.
### Szatnia
wieszaki, stanowiska oddania/odebrania kurtki.
### Dziekanat
Miejsce w którym odbywa się konkurowanie o pieczątki, produkcja i odbiór dokumentów określonego typu
#### Stosy dokumentów
stosy grupujące dokumenty według typów, produkowane przez pracowników dziekanatu, pobierane przez studentów
#### Pieczątki
warunek konieczny przystąpienia pracownika dziekanatu do produkowania dokumentów
### Korytarz
aby przejść z jednego pomieszczenia do kolejnego należy przejść przez korytarz, który może być przepełniony uniemożliwiając/spowalniając przejście
### Ławki na korytarzu
kilka/wiele osób może korzystać z jednej ławki.
### Toaleta
kabiny(mało) i pisuary(kilka)(obowiązuje zasada zachowania odstępu).
### Magazyn
tusze do drukarki, tusz do pieczątki, papier do kabin toaletowych.

# Struktura projektu
## Application
Główne funkcje programu
## Visualization
Wizualizacja - ncurses
## Timer
Wygodne obudowanie delaya
## Person
klasa nadrzędna dla wątków
## Room
Klasa nadrzędna dla zasobów ( pomieszczeń)
## Floor
Zawiera pomieszczenia (klasy):
#### Korytarz
#### Toaleta
#### Magazyn

## Cloakroom
Zawiera klasy Szatniarki i Szatni
## Deanoffice
Dziekanat i jego pracownicy
## Classroom
Sala i osprzęt
## Lecturer
Klasa prowadzącego
## Student
Klasa studenta

# Docker  
`winpty docker run --rm -it --mount src="$(pwd)",target=/workdir,type=bind rikorose/gcc-cmake:latest bash`  
`cat /proc/version`  
