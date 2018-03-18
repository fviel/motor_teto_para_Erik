/***
   CÓDIGO PARA ACIONAMENTO DE MOTOR ATÉ CHAVE DE FIM DE CURSO NOTIFICAR.
*/

//pinagem do l298n
const byte ENA = 8;
const byte IN1 = 9;
const byte IN2 = 10;
const byte IN3 = 11;
const byte IN4 = 12;
const byte ENB = 13;

//pino do botão que irá acionar a interrupção
volatile byte pushButtonPin = 2;

//pino que notifica fim de curso
volatile byte fimCursoPin = 3;

//LED de teste
const byte ledTeste = 7;

//contador simples de eventos
int contador = 0;

boolean sentido = HIGH;


void setup() {
  Serial.begin(9600);
  Serial.println("Serial inicializada...");

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(ledTeste, OUTPUT);

  //configura o pino de acionamento dos motores
  pinMode(pushButtonPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(pushButtonPin), acionarMotores, RISING);

  //configura o pino de desacionamento dos motores
  pinMode(fimCursoPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(fimCursoPin), pararMotores, RISING);


  //define pinos da l298n como de output
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  //inicializa variáveis do motor A
  digitalWrite(ENA, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  //inicializa variáveis do motor B
  digitalWrite(ENB, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  //desativa o led de teste
  digitalWrite(ledTeste, LOW);

  //grava borda baixa nos pins de interrupção
  digitalWrite(pushButtonPin, LOW);
  digitalWrite(fimCursoPin, LOW);


}

void loop() {
  //não faz nada, é tudo por interrupção
}

void acionarMotores() {
  Serial.print("acionarMotores[");
  Serial.print(contador);
  Serial.print(+ "]\n");
  contador++;
  comandoMotores(256);
  //troca o sentido do motor para a próxima execução.
  sentido = trocaSentido(sentido);

}


void pararMotores() {
  Serial.print("pararMotores[");
  Serial.print(contador);
  Serial.print(+ "]\n");
  contador++;
  comandoMotores(0);
 
}

void comandoMotores(int vel) {
    motorA(sentido, vel);
    motorB(sentido, vel);   
}

boolean trocaSentido(boolean Sentido)
{
  if (Sentido == HIGH)
  {
    Sentido = LOW;
  }
  else
  {
    Sentido = HIGH;
  }
  return (Sentido);
}

/*
  Função principal para controle de sentido do motor A

*/
void motorA(boolean sentido, int velocidade)
{
  if (sentido == 1)
  {
    motorAFrente(velocidade);
  }
  else
  {
    motorARe(velocidade);
  }
}

void motorAFrente(int velocidade)
{
  digitalWrite(ENA, 0);
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  analogWrite(ENA, velocidade);
}

void motorARe(int velocidade)
{
  digitalWrite(ENA, 1);
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  analogWrite(ENA, velocidade);
}

/*
  Função principal para controle de sentido do motor B

*/
void motorB(boolean sentido, int velocidade)
{
  if (sentido == 1)
  {
    motorBFrente(velocidade);
  }
  else
  {
    motorBRe(velocidade);
  }
}

void motorBFrente(int velocidade)
{
  digitalWrite(ENB, 0);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
  analogWrite(ENB, velocidade);
}

void motorBRe(int velocidade)
{
  digitalWrite(ENB, 1);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
  analogWrite(ENB, velocidade);
}


