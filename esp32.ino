char buf[8];
int mcVal[2];
int bufIndex = 0;
int curPos = 0;
int state = 0; //0初始，1m , 2c , 3s 
void setup()
{
  Serial.begin(9600);
  delay(20);
}


void loop()
{

  if (Serial.available() > 0) {
    int data = Serial.read();
    showMC((char)data);
  }
}

void showMC(char data ){
      if(state == 0){
        if(data == 'm'){
          state = 1;
        }
      }else if(state == 1){
        if(data == 'c'){
          state = 2;
        }else{
          state = 0;
        }
      }else if(state == 2){
        if(data == 's'){
          state = 3;
          bufIndex = 0;
          curPos = 0;
        }else{
          state = 0;
        }
      }else if(state == 3){
        if(data == 'm' || data == '\n' || data == 's'){
         
          buf[bufIndex] = '\0';
          int value = atoi(buf);
          bufIndex = 0;
          mcVal[curPos++] = value;
          if(data == 's'){
            
          }else{
            dacWrite(25,mcVal[0]);
            dacWrite(26,mcVal[1]);
            state = 0;
          }

        }else{
           buf[bufIndex++] = data;
        }
      }else {

      }
}