/*
  Prende leds con uso de millis para que se pueda hacer otras cosas si fuera necesario
  está en una secuencia de acuerdo a var changer que va aumentando hasta 9 segs y luego repite
 */

//cambiar nombres según color de led para acordarse: rojo en el 11, etc
//anodos resistencia y pata larga
int bla = 11; //los rojos a 11
int azu = 10; // los azules a 10
int ama = 9; // los amarillos a 9
int rojo= 3;  //los rojos a 3
int ver = 2; //los verdes a 2

// catodos directos y pata corta
int blue  = A2;// estos son lo que se comparten, color de cable en inglés pero no es obligatorio el cable de ese color
int purple= A3; // organización por la gráfica no que sea obligatoria...
int orange= A5;
int green = A4;

unsigned long previousMillis = 0;        // will store last time LED was updated
int changer;
// constants won't change:
const long interval = 1000; //inicialmente 1 segundo como base para todo
                            // si quieres más pequeño entonces cambiarlo aquí o se puede usar abajo con matematica
                            // interval*2 sería el doble, o interval*0.5 es la mitad, o un cuarto interval*0.25

// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.

  pinMode(bla, OUTPUT); //anodos resistencia y pata larga
  pinMode(azu, OUTPUT);
  pinMode(ama, OUTPUT);
  pinMode(rojo, OUTPUT);
  pinMode(ver, OUTPUT);
  
  pinMode(blue, OUTPUT); //todos quedan en OUTPUT, lo negativo o positivo funciona extraño, con HIGH y LOW
  pinMode(purple, OUTPUT);
  pinMode(orange, OUTPUT);
  pinMode(green, OUTPUT);
  
  digitalWrite(blue, HIGH);  // los directos (los cátodos), comenzar  HIGH para que los LEDS estén off:
  digitalWrite(purple, HIGH);
  digitalWrite(orange, HIGH);
  digitalWrite(green, HIGH);
}

// the loop routine runs over and over again forever:
void loop() {
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    changer ++; //esto va añadiendo 1 a la suma
    // if the LED is off turn it on and vice-versa:
    
  }  
  switch (changer){
    case 0: // cuando comienza qué pasa
      digitalWrite(blue, LOW);    // con LOW en los catodos se prende
      digitalWrite(rojo, HIGH);
      // si no se pone otro high solo se prende el rojo de la de abajo
      break;
    case 1: // después de un segundo vamos a prender todos de la segunda purple, y apagar la blue
      digitalWrite(purple,LOW); //catodo
      //anodos
      digitalWrite(bla, HIGH); 
      digitalWrite(azu, HIGH);
      digitalWrite(ama, HIGH);
      digitalWrite(rojo, HIGH);
      digitalWrite(ver, HIGH);
      //catodo a apagar
      digitalWrite(blue,HIGH);//LO BLUE catodo con que ya se apague ya el anodo no funciona y
      //digitalWrite(rojo,LOW); // rojo no low porque se bloquea en purple (los // significa que no se procesa)
      break;
    case 2 : //en dos segundos apagamos toda la blue y purple nada, dos específicos de orange
      //CATODO A APAGAR
      digitalWrite(purple,HIGH);
      //CATODO A PRENDER
      digitalWrite(orange,LOW);
      //anodos
      digitalWrite(bla, HIGH); //como viene prendido, no hay que repetir pero para entender mejor
      digitalWrite(azu, LOW); //apagar
      digitalWrite(ama, LOW); //apagar
      digitalWrite(rojo, HIGH); //como viene prendido, no hay que repetir pero para entender mejor
      digitalWrite(ver, LOW); //apagar
      break;
    case 3 : // en tres segundos prender todo green y blue
      //CATODO A APAGAR
      digitalWrite(orange,HIGH);
      //CATODO A PRENDER
      digitalWrite(green,LOW);
      digitalWrite(blue,LOW);
      //anodos
      digitalWrite(bla, HIGH); //como viene prendido, no hay que repetir pero para entender mejor
      digitalWrite(azu, HIGH); //prender
      digitalWrite(ama, HIGH); //prender
      digitalWrite(rojo, HIGH); //como viene prendido, no hay que repetir pero para entender mejor
      digitalWrite(ver, HIGH); //prender
      break;
    case 4 : //se apaga todo
      //CATODO A APAGAR
      digitalWrite(blue, HIGH);  // todos HIGH APAGA
      digitalWrite(purple, HIGH);
      digitalWrite(orange, HIGH);
      digitalWrite(green, HIGH);
      //CATODO A PRENDER
      //nada
      //anodos
      digitalWrite(bla, LOW); //apagar
      digitalWrite(azu, LOW); //apagar
      digitalWrite(ama, LOW); //apagar
      digitalWrite(rojo, LOW); //apagar
      digitalWrite(ver, LOW); //apagar
      break;
    case 5 :
       //NO SE HACE NADA ENTONCES SE MANTIENE TODO APAGADO
      break;
    case 6 : //PRENDER TODO
      //CATODO A APAGAR
      //NADA
      //CATODO A PRENDER
      digitalWrite(blue, LOW);  // todos LOW PRENDE
      digitalWrite(purple, LOW);
      digitalWrite(orange, LOW);
      digitalWrite(green, LOW);
      //anodos
      digitalWrite(bla, HIGH); //PRENDER
      digitalWrite(azu, HIGH); //PRENDER
      digitalWrite(ama, HIGH); //PRENDER
      digitalWrite(rojo, HIGH); //PRENDER
      digitalWrite(ver, HIGH); //PRENDER
      break;
    case 7 ://se apaga todo DE NUEVO 
      //CATODO A APAGAR
      digitalWrite(blue, HIGH);  // todos HIGH APAGA
      digitalWrite(purple, HIGH);
      digitalWrite(orange, HIGH);
      digitalWrite(green, HIGH);
      //CATODO A PRENDER
      //nada
      //anodos
      digitalWrite(bla, LOW); //apagar
      digitalWrite(azu, LOW); //apagar
      digitalWrite(ama, LOW); //apagar
      digitalWrite(rojo, LOW); //apagar
      digitalWrite(ver, LOW); //apagar
      break;
    case 8 ://se prenden todos los verdes blancos y amarillos 
      //CATODO A APAGAR
      //nada
      //CATODO A PRENDER todos
      digitalWrite(blue, LOW);  // todos LOW PRENDE
      digitalWrite(purple, LOW);
      digitalWrite(orange, LOW);
      digitalWrite(green, LOW);
      //anodos
      digitalWrite(bla, HIGH); //prtender
      digitalWrite(azu, LOW); //apagar
      digitalWrite(ama, HIGH); //prender
      digitalWrite(rojo, LOW); //apagar
      digitalWrite(ver, HIGH); //prender
      break;  
    case 9 :
      changer = 0; // con esto se vuelve a comenzar la secuencia de 8 segundos según interval 1000
      break;
  }

}
