//G.S. - TerrarIA

#include <LiquidCrystal.h> // biblioteca do lcd
#include <IRremote.h> // biblioteca do sensor infravermelho

LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // RS, E, D4, D5, D6, D7

int ledVerde = 13;
int ledVerm = 12;
int ledAzul = 11;
int recv = 10;
int rele = 8;
int umidSolo = A5;
int sensorTemp = A4;
//declarando as entradas no arduino

IRrecv irrecv(recv);
decode_results results;
//as variaveis para o sensor infravermelho

float umidade;
float umidPorc;
float temperatura;
float temp;
float tensao;
//mais variaveis pra transformação dos sensores

bool sistemaLigado = false;
//loop pra liga/desliga do controle

void setup() {

  pinMode(ledVerde, OUTPUT);
  pinMode(ledVerm, OUTPUT);
  pinMode(ledAzul, OUTPUT);
  pinMode(rele, OUTPUT);
  pinMode(umidSolo, INPUT);
  pinMode(sensorTemp, INPUT);

  Serial.begin(9600);
  lcd.begin(16, 2);
  irrecv.enableIRIn();
  
  Serial.print("Sistema desligado");
}

void loop() {
	
  if (irrecv.decode(&results)) {
    unsigned int codRec = results.value;  
    //recebe sinal do controle
    
    Serial.print("Codigo Infravermleho Binario = ");
    Serial.print(codRec);
    Serial.print("    /    ");
    Serial.print("Codigo Infravermleho Hexadecimal = ");
    Serial.println(codRec, HEX);
    irrecv.resume();

    if (codRec == 65535) { // Código do botão do controle remoto
      if (!sistemaLigado) {
        ligarSistema();
      } else {
        desligarSistema();
      }
    }
  }

  if (sistemaLigado) {
    // Código a ser executado quando o botáo for pressionado
    
    Serial.print("Umidade: ");
    Serial.println(umidade);
    Serial.print("Umidade %: ");
    Serial.println(umidPorc);

    Serial.print("Temperatura C: ");
    Serial.println(temp);

    umidade = analogRead(umidSolo); // valor do sensor, 0 - 798
    umidPorc = (umidade / 798)*100; // transforma o valor em porcentagem

    temperatura = analogRead(sensorTemp);
    tensao = (temperatura / 1023.0) * 5000;
    temp = (tensao - 500) * 0.1; // cálculo para transformar a leitura em graus °C

    if (umidade < 438) {
      // se for menor que a metade do limite do sensor
      digitalWrite(ledVerm, LOW);
      digitalWrite(ledVerde, HIGH);
      digitalWrite(ledAzul, LOW);
      digitalWrite(rele, LOW); // desliga motor
      lcd.setCursor(0, 0);
      lcd.print("Umidade: ");
      lcd.print(umidPorc);
      lcd.print("%");
      lcd.setCursor(0, 1);
      lcd.print("Solo seco");
      delay(2000);

      // motor ligado
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Umidade: ");
      lcd.print(umidPorc);
      lcd.print("%");
      lcd.setCursor(0, 1);
      lcd.print("Irrigando...");
      // liga motor
      digitalWrite(rele, HIGH); 
      digitalWrite(ledVerm, HIGH);
      digitalWrite(ledAzul, LOW);
            
      int piscadas = 6;
      int delayPisc = 417;//fazendo durar 2500 ms
      
      //faz o led vermelho piscar enquanto a bomba fica ligada
      for (int i = 0; i < piscadas; i++) {
  		digitalWrite(ledVerde, HIGH);
  		delay(delayPisc);
 		digitalWrite(ledVerde, LOW);
  		delay(delayPisc);
      }
      digitalWrite(rele, LOW);
      lcd.clear();
	//desliga a bomba
    } 
    
    else {
      // acima da metade da leitura máxima do sensor
      digitalWrite(ledVerm, LOW);
      digitalWrite(ledVerde, HIGH);
      digitalWrite(ledAzul, LOW);
      lcd.setCursor(0, 0);
      lcd.print("Umidade: ");
      lcd.print(umidPorc);
      lcd.print("%");
      lcd.setCursor(0, 1);
      lcd.print("Solo Umido");
      delay(2500);
      lcd.clear();
    }

    // exibe a temperatura ambiente no display após quualquer leitura de umidade
    digitalWrite(ledAzul, HIGH);
    digitalWrite(ledVerm, LOW);
    digitalWrite(ledVerde, LOW);
    lcd.setCursor(0, 0);
    lcd.print("Temperatura: ");
    lcd.setCursor(0, 1);
    lcd.print(temp);
    lcd.print(" C");
    delay(2500);
    lcd.clear();
  }
}

void ligarSistema() {
  //apertando o botão, ligando sistema e realizando o circuito
  sistemaLigado = true;
  digitalWrite(ledVerde, HIGH);
  Serial.println("Sistema ligado.");
}

void desligarSistema() {
  //apertando o botão após ligado, desligando todos os dispositivos
  sistemaLigado = false;
  lcd.clear();
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledVerm, HIGH);
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledAzul, LOW);
  digitalWrite(rele, LOW); 
  Serial.println("Sistema desligado.");
}