//void eeprom_str_adr()
//{
//  int eeprom_number = 10;
//  for (byte y=0; y <= count_recipe-1; y++){
//    
//    prg[y].RCP_Name = recipe_name[y];
// 
//    for (byte x=0; x<= count_channel-1; x++){
//      
//      prg[y].ch[x].K = eeprom_number;
//      eeprom_number = eeprom_number + 2;
//      
//      prg[y].ch[x].V = eeprom_number;
//      eeprom_number = eeprom_number + 2;
//      
//      prg[y].ch[x].Pin = eeprom_number;
//      eeprom_number = eeprom_number + 2;
//      
//      prg[y].ch[x].ch_name = channel_name[x];
//      
//
//      }
//
//   } 
// 
//      
//}
//void initialization()
//{
//  prg[1].Start = false;
//  prg[1].Stop = true;
//  prg[1].IsRun = false;
//
//};

void initialization_eeprom()
{
  poliv.CSAdress_E = 1;
  poliv.Mode = poliv.read_bit_E(1);
  poliv.Start = poliv.read_bit_E(2);
  poliv.dryRunProtec = poliv.read_bit_E(3);
  
  poliv.SensorPin_E = 100;
  poliv.SensorPin = EEPROM_uint_read(poliv.SensorPin_E); 
  
  poliv.RelePin_E = 102;
  poliv.RelePin = EEPROM_uint_read(poliv.RelePin_E);

  poliv.ContactL_E = 200; //адрес памяти
  poliv.ContactL = EEPROM_uint_read(poliv.ContactL_E);
  
  poliv.ContactH_E = 202; //адрес памяти
  poliv.ContactH = EEPROM_uint_read(poliv.ContactH_E);
  
  poliv.timePV_Update_E = 204; //адрес памяти
  poliv.timePV_Update = EEPROM_uint_read(poliv.timePV_Update_E);

  poliv.almEmptyTank_E = 206; //адрес памяти
  poliv.almEmptyTank = EEPROM_uint_read(poliv.almEmptyTank_E);


  heating.CSAdress_E = 3;
  heating.Mode = heating.read_bit_E(1);
  heating.Start = heating.read_bit_E(2);
  heating.dryRunProtec = heating.read_bit_E(3);
  
  heating.SensorPin_E = 110;
  heating.SensorPin = EEPROM_uint_read(heating.SensorPin_E); 
  
  heating.RelePin_E = 112;
  heating.RelePin = EEPROM_uint_read(heating.RelePin_E);

  heating.ContactL_E = 210; //адрес памяти
  heating.ContactL = EEPROM_uint_read(heating.ContactL_E);
  
  heating.ContactH_E = 212; //адрес памяти
  heating.ContactH = EEPROM_uint_read(heating.ContactH_E);
  
  heating.timePV_Update_E = 214; //адрес памяти
  heating.timePV_Update = EEPROM_uint_read(heating.timePV_Update_E);

  heating.almEmptyTank_E = 216; //адрес памяти
  heating.almEmptyTank = EEPROM_uint_read(heating.almEmptyTank_E);



  timer1.CSAdress_E = 5;
  timer1.Mode = timer1.read_bit_E(1);
  timer1.Start = timer1.read_bit_E(2);
  timer1.RelePin_E = 120;
  timer1.RelePin = EEPROM_uint_read(timer1.RelePin_E);


  timer1.timeOnHour_E = 220; //адрес памяти
  timer1.timeOnHour = EEPROM_uint_read(timer1.timeOnHour_E);

  timer1.timeOnMinute_E = 222; //адрес памяти
  timer1.timeOnMinute = EEPROM_uint_read(timer1.timeOnMinute_E);

  timer1.timeOffHour_E = 224; //адрес памяти
  timer1.timeOffHour = EEPROM_uint_read(timer1.timeOffHour_E);

  timer1.timeOffMinute_E = 226; //адрес памяти
  timer1.timeOffMinute = EEPROM_uint_read(timer1.timeOffMinute_E);
  
  timer1.timeOn = timer1.timeOnHour * 60 + timer1.timeOnMinute;
  timer1.timeOff = timer1.timeOffHour * 60 + timer1.timeOffMinute;



};


