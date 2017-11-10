//void ControlRecipe(struct program &prg) //Control Recipe
//{
//  if (prg.Start){  
//    if (!prg.IsRun){
//      prg.IsRun = 1;
//      prg.ch[0].IsRun = 1;
//      prg.ch[0].startTime = millis();
//      prg.ch[0].stopTime = prg.ch[0].startTime + (EEPROM.read(prg.ch[0].V) * EEPROM_uint_read(prg.ch[0].K));
//    }
//    if (prg.ch[0].IsRun){
//      if (millis() > prg.ch[0].stopTime){
//        prg.ch[0].IsRun = 0;
//        prg.ch[1].IsRun = 1;
//        prg.ch[1].startTime = millis();
//        prg.ch[1].stopTime = prg.ch[1].startTime + (EEPROM.read(prg.ch[1].V) * EEPROM_uint_read(prg.ch[1].K));
//      }
//    }
//     if (prg.ch[1].IsRun){
//      if (millis() > prg.ch[1].stopTime){
//        prg.ch[1].IsRun = 0;
//        prg.ch[2].IsRun = 1;
//        prg.ch[2].startTime = millis();
//        prg.ch[2].stopTime = prg.ch[2].startTime + (EEPROM.read(prg.ch[2].V) * EEPROM_uint_read(prg.ch[2].K));
//      }
//    }
//    if (prg.ch[2].IsRun){
//      if (millis() > prg.ch[2].stopTime){
//        prg.ch[2].IsRun = 0;
//        prg.ch[3].IsRun = 1;
//        prg.ch[3].startTime = millis();
//        prg.ch[3].stopTime = prg.ch[3].startTime + (EEPROM.read(prg.ch[3].V) * EEPROM_uint_read(prg.ch[3].K));
//      }
//    }
//    if (prg.ch[3].IsRun){
//      if (millis() > prg.ch[3].stopTime){
//        prg.ch[3].IsRun = 0;
//        prg.IsRun = 0;
//        prg.Start = 0;
//        prg.Stop = 1;
//      }
//    }
//
//  }
//ControlOutput();
//}
//
//void ControlOutput() {//Control Output
//  for (byte y=0; y <= count_recipe-1; y++){
//    for (byte x=0; x<= count_channel-1; x++){
//      if (prg[y].ch[x].IsRun){
//        digitalWrite(EEPROM.read(prg[y].ch[x].Pin), HIGH);
//      } 
//      else{digitalWrite(EEPROM.read(prg[y].ch[x].Pin), LOW);}
//      
//    }
//  }
//
//}
