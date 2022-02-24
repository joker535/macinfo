String dataIn = ""; 
int mcVal[2];
void setup()
{
  Serial.begin(9600);
  delay(20);
}


void loop()
{

  if (Serial.available() > 0) {
    dataIn = Serial.readString();  // Read the data as string
    if(dataIn.startsWith("mc")){
      String dataInS = dataIn.substring(2, dataIn.length());
      showMC(dataInS.c_str(),dataInS.length());
    }
  }
}

void showMC(char* data , int len){
  int index =0;
  int state =0;
  char buf[10];
  int bufIndex = 0;
  int curPos = 0;
  char bufchar =0;
  while (index < len)
  {
      if(data[index] == 's' && state == 0){
          bufchar= data[index+1];
          curPos = bufchar-'0';
          index +=2;
          state = 1;
      }else if(data[index] == ' ' || index == len-1){
          if(index == len-1){
            buf[bufIndex++] = data[index];
          }
          buf[bufIndex] = '\0';
          int value = atoi(buf);
          mcVal[curPos-1] = value;
      
          bufIndex=0;
          state=0; 
          index++;
      }else if(state == 1 && data[index] != ' '){
          buf[bufIndex++] = data[index++];
      }
  }
  dacWrite(25,mcVal[0]);
  dacWrite(26,mcVal[1]);
}