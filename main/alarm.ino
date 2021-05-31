const int morningAlarm[] = {0, 0, 0, 6, 30, 0};
const int nightAlarm[] = {0, 0, 0, 19, 0, 0};

void readTime() {
  DateTime robojax = rtc.now();
  Serial.println();
  Serial.print("Time:  ");
  Serial.print(robojax.year(), DEC);
  Serial.print("-");
  Serial.print(robojax.month(), DEC);
  Serial.print("-");
  Serial.print(robojax.day(), DEC);
  Serial.print("-");
  Serial.print(robojax.hour(), DEC);
  Serial.print("-");
  Serial.print(robojax.minute(), DEC);
  Serial.print("-");
  Serial.print(robojax.second(), DEC);
  Serial.println();


}

bool morning(DateTime timeNow) {
  if (
    timeNow.hour() == morningAlarm[3]
    &&
    timeNow.minute() == morningAlarm[4] 
  ) {
    return true;
  } else {
    return false;
  }
}

bool night(DateTime timeNow) {
  if (
    timeNow.hour() == nightAlarm[3]
    &&
    timeNow.minute() == nightAlarm[4]
  ) {
    return true;
  } else {
    return false;
  }
}

bool hourly(DateTime timeNow) {
  if(
    timeNow.minute() == 0
    &&
    timeNow.second() == 0){
      return true;
    }else{
      return false;
    }
}
