Tematem projektu jest robotyczne ramię wykonane w technologii wydruku 3D. 

Projekt zakłada zamodelowanie w wybranym środowisku CAD modeli w rozszerzeniu .stl, elementów robotycznego ramienia. Następnie ich wydruk oraz montaż.
Robot kontrolowany jest za pomocą mikrokontrolera ESP32, a zadania sterujące zostały nadawane na mikrokontroler poprzez komunikację USB to UART, przy pomocy sterownika CP210x i oprogramowanie programistyczne Arduino IDE. W strukturze całej aplikacji do wykonywania przemieszczenia zostały wykorzostane: 
-silniki krokowe 28BYJ-48
-serwomechanizm SG90 (obsługujący chwytak)
-przełączniki krańcowe WK621
Komunikacja elementów elektronicznych realizowana jest za pomocą przewodów połączeniowych. Zasilanie obsługujące robota jest zasilaniem sieciowym 230V.

Założeniem bazowym projektu jest możliwość symulacji działania ramienia o 3 stopniach swobody. Tak aby poprzez obserwacje układu mniejszczego możnaby było zrealizować aplikację w większej skali.
W przypadku sterowania robotem zrealizowane zostały dwa rodzaje kontroli ramienia. Są to kontrola manualna oraz programowa.
W przypadku kontroli manualnej zotał wykorzystany wbudowany w ESP32 moduł Bluetooth umożliwiający komunikację platformy z zewnętrznym kontrolerem posiadającym moduł Bluetooth - w tym przypadku DualShock3.
Aby komunikacja została nawiązana oraz poszczególne zadania mogły zostać przypisane do konkretnych przycisków kontrolera, potrzebne jest wykorzystanie dedykowanej biblioteki Ps3Controller. Komunikacja Bluetooth nawiązywana jest na podstawie adresu MAC urządzenia DualShock3. Odkrycie lub zmiana adresu fizycznego urządzenia możliwe jest przy wykorzystaniu oprogramowania SixAxisPairTool.


W przypadku sterowania programowego przemieszczenie ramienia do wybranej pozycji zostało zrealizowane wykorzystując zadanie kinematyki odwrotnej.
W ramach budowy aplikacji przetestowano również zadanie kinematyki prostej. W przypadku rozwiązaywania zadań kinematyki prostej jak i odwrotnej zostały wykorzystana metoda geometryczna, opierająca się na rzeczywistych wymiarach wydrukowanych ramion.

Robot został umieszczony na stabilnej platformie a która rozmiarem przekraczała zasięg jego całkowitej przestrzeni roboczej, było to konieczne w celu poprawnego wykonania przemieszczeń ramienia.
Aplikacja robotyczna wyposażona jest w kontrolowany chwytak umożliwiający przenoszenie przedmiotów niskiej wagi. Został więc napisany program umożliwiający przemieszczenie danego z obiektu z pozycji początkowej (POS1) do pozycji końcowej (POS2).
Opis obiektu w przestrzeni został zrealizowany poprzez określenie pozycji obiektu w przestrzeni kartezjańskiej operując na trzech wektorach przestrzennych (x,y,z).
Wyliczenie zadań kinematyki odwrotnej dla zadanych wartości wymagało rozpoczęcie przemieszczenia według zdefiniowanej pozycji startowej do zadanych pozycji. W tym celu wykorzystane zostały przełączniki krańcowe które odpowiedzialne są za skorygowanie ustawienia ramienia do tejże pozycji startowej.

Przemieszczenia ramion zostały zrealizowane przy wykorzystaniu silników krokowych, odpowiednie wartości wyliczane poprzez zadania kinematyki były transformowane na wybraną ilość kroków oraz kierunek przesunięca wała silnika.
W celu realizacji tych zadań zostały wykorzystane biblioteki AccelStepper oraz Stepper. Serwomechanizm kontrolowany jest poprzez standardową bibliotekę Servo.

W celu testu zakresu przestrzeni roboczej został zrealizowany skrypt wizualizacyjny w oprogramowaniu Matlab, ukazujący możliwe konfiguracje przemieszczeń zarówno w płaszczyźnie 2D oraz 3D.
 
