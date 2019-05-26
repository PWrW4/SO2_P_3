# Opis
Projekt ma symulować piętro uczelni wraz z funkcjonującymi pracownikami/studentami.

## Wątki:
### Studenci (kilkadziesiąt)
uczestniczą w zajęciach(pracują, mają problem który rozwiązuje prowadzący), uczą się na ławce w korytarzu, chodzą do dziekanatu
### Prowadzący (kilkunastu)
prowadzi zajęcia, idzie na nie, pomaga studentom przy problemach na zajęciach 
### Pani z dziekanatu (kilka)
przyjmuje studentów, drukuje, podbija pieczątką dokument, przynosi zasoby z magazynu
### Pani Szatniarka (kilka)
wydaje/pobiera kurtki, oddaje/pobiera numerki.
Każdy może iść do toalety i pobrać papier toaletowy z magazynu.

## Zasoby:
### Sale
stanowiska jedno/wielo osobowe.
### Szatnia
wieszaki, stanowiska oddania/odebrania kurtki.
### Dziekanat
drukarka dla pracowników, stanowiska o różnym przeznaczeniu, jedno miejsce gdzie pracownicy podbijają dokumenty pieczątką.
### Korytarz
aby przejść z jednego pomieszczenia do kolejnego należy przejść przez korytarz który może być przepełniony uniemożliwiając/spowalniając przejście
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
