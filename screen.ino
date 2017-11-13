void screen_menu(){
//  byte old_i = i; // для возврата в предыдущий рецепт
//  i=0; //начало позиции меню
//  byte s=i; 
//  unsigned long prevTime=millis();
//  display.clear(); 
//  bool x = 1;
//  while(1){ 
 //   structures(id);
    encoder();
        
    if (_i != i) {
      //prevTime=millis();
      _i=i;
        display.clear(); 
      }
      
    display.setCursor(0,0);
 
    if (i == -1){i=2;}

   // display.println(prg.RCP_Name);
   // display.println();
    if (i == 1) {display.println("=>Irrigation ");}
    else display.println("  Irrigation ");
//    display.println(prg.Mode);
    
//    display.println("START"); 
    
    if (i == 2) {display.print("=>");}
    display.println("  Termocontol ");
//    display.println(prg.Start);
    
    if (i == 3) {display.print("=>");}
    display.println("  Sun Timer ");
//    display.println("  Русский ");
//    display.println(!prg.Start);

//    if (i == 4) {display.print("=>");}
  //  else {display.setTextColor(WHITE);}
//    display.print("Pin=");
//    display.println("SETTINGS");
 
    
//    if (i == 0) {display.print("=>");}
//    else {display.setTextColor(WHITE);}
//    display.println("EXIT");
    
    if (i > 3){i=1;}
 //     display.print(" "); 

//      start_recipe(prg);
 //   ControlRecipe(prg);
   if (!Btn){
     delay(500);
     switch (i){
       case 1:{screen_sensor((*_poliv)); break;}
       case 2:{screen_sensor((*_heating)); break;}
       case 3:{screen_timer_settings_set_time((*_timer1)); break;}
//       case 4:{screen_sensor_settings(prg);  display.clear();   prevTime=millis(); break;}       
//       case 0:{x = 0; break;}
      
   }

 }
//    if ((!x) || (millis()-  prevTime>100000)){  display.clear();  i=old_i; break;}


//  }//while
} //screen

void screen_sensor(struct sensor &prg){
  byte old_i = i; // для возврата в предыдущий рецепт
  i=0; //начало позиции меню
  byte s=i; 
  unsigned long prevTime=millis();
  display.clear(); 
  bool x = 1;
  while(1){ 
 //   structures(id);
    encoder();
        
    if (s != i) {
      prevTime=millis();
      s=i;
        display.clear(); 
      }
      
    display.setCursor(0,0);
 
    if (i == -1){i=5;}

   // display.println(prg.RCP_Name);
   // display.println();
    if (i == 1) {display.print(">");}
    display.print("MODE ");
    display.println(prg.Mode);
    
//    display.println("START"); 
    
    if (i == 2) {display.print(">");}
    display.print("START ");
    display.println(prg.Start);
    
    if (i == 3) {display.print(">");}
    display.print("STOP ");
    display.println(!prg.Start);

    if (i == 4) {display.print(">");}
    display.print("DryStop ");
    display.println(prg.dryRunProtec);


    if (i == 5) {display.print(">");}
  //  else {display.setTextColor(WHITE);}
//    display.print("Pin=");
    display.println("SETTINGS");
 
    
    if (i == 0) {display.print(">");}
//    else {display.setTextColor(WHITE);}
    display.println("EXIT");
    
    if (i > 5){i=0;}
      display.print(" "); 

//      start_recipe(prg);
 //   ControlRecipe(prg);
   if (!Btn){
     delay(500);
     switch (i){
       case 1:{prg.Mode = prg.write_bit_E(!prg.Mode, 1); prevTime=millis(); break;}
 //      case 1:{if (prg.Mode){prg.Mode = poliv.write_bit_E(0, 1);} else{prg.Mode = poliv.write_bit_E(1, 1);}; prevTime=millis(); break;}
       case 2:{prg.Start = prg.write_bit_E(!prg.Start, 2); prg.dryRunAlmIsActive = 0; prevTime=millis(); break;}
       case 3:{prg.stop();prevTime=millis(); break;}

       case 4:{prg.dryRunProtec = prg.write_bit_E(!prg.dryRunProtec, 3); prevTime=millis(); break;}

       case 5:{screen_sensor_settings(prg);  display.clear();   prevTime=millis(); break;}       
       case 0:{x = 0; break;}
      
   }

 }
    if ((!x) || (millis()-  prevTime>100000)){  display.clear();  i=old_i; break;}


  }//while
} //screen

void screen_sensor_settings(struct sensor &prg){
  i=0;
  byte s=i;
  unsigned long prevTime=millis();
 display.clear(); 
  while(1){ 
 
    encoder();
        
    if (s != i) {
      prevTime=millis();
      s=i;
      display.clear(); 
      }
      
    display.setCursor(0,0);


    if (i < 0){i=6;}
    if (i > 6){i=0;}

//   display.println(ch.ch_name);
 //   display.println();

    if (i == 1) {display.print("=>");}
    display.print("ContactL: ");
    display.print(prg.ContactL);
    display.println(" %");    
  
    if (i == 2) {display.print("=>");}
    display.print("ContactH: ");
    display.print(prg.ContactH);
    display.println(" %");

    
    if (i == 3) {display.print("=>");}
    display.print("Sensor Pin: ");
    display.println(prg.SensorPin);

    if (i == 4) {display.print("=>");}
    display.print("Rele Pin: ");
    display.println(prg.RelePin);
//    display.println(" ml"); 
    if (i == 5) {display.print("=>");}
    display.print("Update Time: ");
    display.print(prg.timePV_Update);
    display.println(" sec");

    if (i == 6) {display.print("=>");}
    display.print("DryRun Time: ");
    display.print(prg.almEmptyTank);
    display.println(" sec");

  
    display.println();  
    
    if (i == 0) {display.print("=>");}
    display.print("EXIT");
    display.println(i);

    
    //display.display();

   if (!Btn){
     switch (i){

       case 1:{prg.write_value_analog(prg.ContactL_E, prg.ContactL);break;}
       case 2:{prg.write_value_analog(prg.ContactH_E, prg.ContactH);break;}
       case 3:{prg.write_value_analog(prg.SensorPin_E, prg.SensorPin);break;}
       case 4:{prg.write_value_analog(prg.RelePin_E, prg.RelePin);break;}
       case 5:{prg.write_value_analog(prg.timePV_Update_E, prg.timePV_Update);break;}
       case 6:{prg.write_value_analog(prg.almEmptyTank_E, prg.almEmptyTank);break;}
       
     }//switch
  prevTime=millis(); 
 }

    if ((!Btn && i == 0) || (millis()-  prevTime>30000)){ delay(500); break;}

  }//while
} //screen


void screen_timer_settings_set_time(struct timer &prg){
  i=0;
  byte s=i;
  unsigned long prevTime=millis();
 display.clear(); 
  while(1){ 
 
    encoder();
        
    if (s != i) {
      prevTime=millis();
      s=i;
      display.clear(); 
      }
      
    display.setCursor(0,0);
    display.print("Now: ");
    RTC.read(tm);
    print2digits(tm.Hour);
    display.print(':');
    print2digits(tm.Minute);
    display.print(':');
    print2digits(tm.Second);
    display.println(" ");

    if (i < 0){i=8;}
    if (i > 8){i=0;}

    display.print("On: ");
    if (i == 1) {display.print(">");}
    print2digits(prg.timeOnHour);
    display.print(":");    
  
    if (i == 2) {display.print(">");}

    print2digits(prg.timeOnMinute);
    display.println();

    

    display.print("Off: ");
    if (i == 3) {display.print(">");}
    print2digits(prg.timeOffHour);
    display.print(":");  

    if (i == 4) {display.print(">");}
    print2digits(prg.timeOffMinute);
    display.println();

    if (i == 5) {display.print(">");}
    display.print("MODE ");
    display.println(prg.Mode);
    
//    display.println("START"); 
    
    if (i == 6) {display.print(">");}
    display.print("START ");
    display.println(prg.Start);
    
    if (i == 7) {display.print(">");}
    display.print("STOP ");
    display.println(!prg.Start);

    if (i == 8) {display.print(">");}
    display.print("Rele Pin: ");
    display.println(prg.RelePin);
    
  

    
    if (i == 0) {display.print(">");}
    display.print("EXIT");
    display.println(i);





    
//timer1.CSAdress_E = 5;
//  timer1.Mode = timer1.read_bit_E(1);
//  timer1.Start = timer1.read_bit_E(2);

   if (!Btn && i !=0){
     delay(500);
     switch (i){

       case 1:{prg.write_value_analog(prg.timeOnHour_E, prg.timeOnHour); prg.updateTime(); break;}
       case 2:{prg.write_value_analog(prg.timeOnMinute_E, prg.timeOnMinute); prg.updateTime();break;}
       case 3:{prg.write_value_analog(prg.timeOffHour_E, prg.timeOffHour); prg.updateTime(); break;}
       case 4:{prg.write_value_analog(prg.timeOffMinute_E, prg.timeOffMinute); prg.updateTime(); break;}

       case 5:{prg.Mode = prg.write_bit_E(!prg.Mode, 1); prevTime=millis(); break;}
       case 6:{prg.Start = prg.write_bit_E(!prg.Start, 2); prevTime=millis(); break;}
       case 7:{prg.stop();prevTime=millis(); break;}

       case 8:{prg.write_value_analog(prg.RelePin_E, prg.RelePin);break;}

       
     }//switch
  prevTime=millis(); 
 }

    if ((!Btn && i == 0) || (millis()-  prevTime>30000)){ delay(500); break;}

  }//while
} //screen

