#include <ArduinoJson.h>
String inData;
int is_matrix = true;
const int lengthX = 1;
const int lengthY = 3;
boolean stateMatrixR[lengthX][lengthY];
boolean stateMatrixG[lengthX][lengthY];
boolean stateMatrixB[lengthX][lengthY];
byte matricePin[lengthX][lengthY] = {
  2, 5, 8/*, 11,14,17,
  20,23,26,29,32,35*/
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

    }else{
      for (int x = 0; x < lengthX; x++) {
        for (int y = 0; y < lengthY; y++) {
          int p = parsed["data"][x][y];
          switch(p){
            case 1:
              stateMatrixR[x][y] = 1;
              stateMatrixG[x][y] = 0;
              stateMatrixB[x][y] = 0;
            case 2:
              stateMatrixR[x][y] = 1;
              stateMatrixG[x][y] = 1;
              stateMatrixB[x][y] = 0;
            case 3:
              stateMatrixR[x][y] = 1;
              stateMatrixG[x][y] = 1;
              stateMatrixB[x][y] = 1;
            case 4:
              stateMatrixR[x][y] = 0;
              stateMatrixG[x][y] = 1;
              stateMatrixB[x][y] = 0;
            case 5:
              stateMatrixR[x][y] = 0;
              stateMatrixG[x][y] = 1;
              stateMatrixB[x][y] = 1;
            case 6:
              stateMatrixR[x][y] = 0;
              stateMatrixG[x][y] = 0;
              stateMatrixB[x][y] = 1;
            case 7:
              stateMatrixR[x][y] = 1;
              stateMatrixG[x][y] = 0;
              stateMatrixB[x][y] = 1;         
            case 8:
              stateMatrixR[x][y] = 0;
              stateMatrixG[x][y] = 0;
              stateMatrixB[x][y] = 0;
          }
          //stateMatrix[x][y] = parsed["data"][x][y];
        }
      }
  
      inData = "";
      is_matrix = true;
    }
    if (is_matrix == true) {
      for (int x = 0; x < lengthX; x++) {
        for (int y = 0; y < lengthY; y++) {
          //Serial.println((String)"pin" + matricePin[x][y] + "etat : " + stateMatrix[x][y]);
          digitalWrite((matricePin[x][y]), stateMatrixR[x][y]);
          digitalWrite((matricePin[x][y] + 1), stateMatrixG[x][y]);
          digitalWrite((matricePin[x][y] + 2), stateMatrixB[x][y]);
        }

      }
      is_matrix = false;
    }
  
}


}
