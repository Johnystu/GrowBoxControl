//void serial(){
//
//
// if (Serial.available() > 0) {
//    int inByte = Serial.read();
//    if ((inByte < (count_recipe + 48)) && (inByte >= 48)){ 
//      Serial.print("Start ");
//      Serial.println(prg[inByte-48].RCP_Name);      
//      prg[inByte-48].start();
//  //      Serial.println(_V-((stopTime - millis())/_K));
//      Serial.print("Batch ");
//      Serial.print(prg[inByte-48].RCP_Name);
//      Serial.println(" is Done");     
//
//    }
//    else {
//      
//      switch (inByte) {
//      case 't':    
//        Serial.println(updateDS(0));
//        break;
//      case '?': 
//   
//        Serial.println("help:");
//        for (byte y=0; y <= count_recipe-1; y++){
//          Serial.print(y);
//          Serial.print(": ");
//            Serial.println(prg[y].RCP_Name); 
//        }
//        Serial.println("t: temp");    
//
//        break;
//  
//      case 13:
//        break;
//      case 10:
//        break;
//
//    default:
//     Serial.print(inByte);
//     Serial.println(": BAD command");
//      }
//    }
//}}
