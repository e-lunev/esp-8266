1. Чтобы добавить поддержку модуля esp8266(esp-01) в arduino ide:
    - В меню File -> Preferences в поле "Additional Boards Manager URLs" добавил строку http://arduino.esp8266.com/stable/package_esp8266com_index.json
    - В меню Tools -> Board: "..." -> Boards Manager... в поисковой строке вводим esp8266 и нажимаю кнопку install
    - Выбираем Generic ESP8266 Module в меню Tools -> Board: "..." -> ESP8266 Boards (2.7.4)
    
2. Схема подключения модуля esp-01 и UART преобразователя:
<p><img src="circuit/esp-01_arduino_ideSketch_bb.png"
     alt=""
     title=""
     width="500" height="400"
/></p>

3. Чтобы залить прошивку надо:
    - Отключить питание по USB.
    - Нажать и удерживать кнопку "program".
    - Включить питание по USB.
    - Отжать кнопку "program".
    - Залить прошивку в Arduino IDE.
    
4. Мигание встроенным и внешним светодиодами для отладки:
    - По умолчанию в Tools -> Board: "..." -> ESP8266 Boards (2.7.4) -> Builtin Led: "2", но как оказалось что из-за этого не мигал встроенный светодиод на модуле esp-01. При исправлении Builtin Led: "2" на Builtin Led: "1" проблема решилась.
    - Код мигания встроенным светодиодом:
```c++
const int pin = 2;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(pin, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(pin, LOW);
  delay(500);
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(pin, HIGH);
  delay(500);
}
```
