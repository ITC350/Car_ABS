#include "sensor.hpp"

void sensor::event() {
    counter++;
}

void sensor::average() {
    value = counter;
    //counter = 0;
}

uint16_t sensor::getvalue() {
    return value;
}

bool sensor::Datacollector(){

    if (dataArrItt < MAXDATAINPUT) {
        dataArr[dataArrItt++] = getvalue();
        //Serial.println(m_sensors[2].getvalue());
        return true;
    }
    return false;
}
