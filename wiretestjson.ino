#include <ArduinoJson.h>
String inData;
int is_matrix = true;
const int lengthX = 2;
const int lengthY = 6;
boolean stateMatrix[lengthX][lengthY];
byte matricePin[lengthX][lengthY] = {
  2, 5, 8, 11,14,17,
  20,23,26,29,32,35
  /*19,22,25,28,31,34,
    37,40,43,46,49,52,
    55,58,61,64,70,73,
    76,79,82,85,88,91,
    94,97,100,103,106,109*/
};
//{{1,0,1,0,0,1},{1,1,1,1,1,1},{0,1,0,1,0,1},{0,0,0,1,1,1},{1,1,1,1,1,1},{1,1,1,1,1,1}}
//{"data": [[1,0,1,0],[1,1,1,1]]}
//{"data": [[1,0,1,0,1,0],[0,1,0,1,0,1]]}
//{"data": [[1,1,1,1,1,1],[1,1,1,1,1,1]]}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for (int x = 0; x < lengthX; x++) {
    for (int y = 0; y < lengthY; y++) {
      pinMode((matricePin[x][y]), OUTPUT);
      pinMode((matricePin[x][y] + 1), OUTPUT);
      pinMode((matricePin[x][y] + 2), OUTPUT);
    }
  }
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //digitalWrite(LED_BUILTIN, LOW);

  if (Serial.available() > 0)
  {
    //digitalWrite(LED_BUILTIN, HIGH);

    inData = Serial.readStringUntil('\n');
    //Serial.println("data: " + inData);
    DynamicJsonBuffer JSONBuffer;
    JsonObject&  parsed = JSONBuffer.parseObject(inData);
    if (!parsed.success()) {      //Check for errors in parsing

      Serial.println("Parsing failed");
      delay(1000);
      return;

    }
    for (int x = 0; x < lengthX; x++) {
      for (int y = 0; y < lengthY; y++) {
        stateMatrix[x][y] = parsed["data"][x][y];
      }
    }
  
    inData = "";
    is_matrix = true;
    if (is_matrix == true) {
      for (int x = 0; x < lengthX; x++) {
        for (int y = 0; y < lengthY; y++) {
          //Serial.println((String)"pin" + matricePin[x][y] + "etat : " + stateMatrix[x][y]);
          //digitalWrite((matricePin[x][y]), stateMatrix[x][y]);
          //digitalWrite((matricePin[x][y] + 1), stateMatrix[x][y]);
          digitalWrite((matricePin[x][y] + 2), stateMatrix[x][y]);
        }

      }
      is_matrix = false;
    }
  
}


}
