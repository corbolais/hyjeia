#include "LiquidCrystal_I2C.h"
#include "chibi.h"

#define MY_ADDR               0x5
#define LCD_ADDRESS             0x27

LiquidCrystal_I2C lcd(LCD_ADDRESS, 16, 2);

uint32_t startTime;
uint8_t payload[100];

void setup()
{    
    Serial.begin(57600);
    chibiInit();
}

void loop()
{   
    float intensity, dosage;
    uint8_t *pbuf;
    
    if (chibiDataRcvd() == true)
    {
        int rssi, srcAddr;
        uint8_t len;
        
        len = chibiGetData(payload);
        if (len == 0) return;
        
        // retrieve the data and the signal strength
        rssi = chibiGetRSSI();
        srcAddr = chibiGetSrcAddr();

        // if len is 0, then it's a duplicate so ignore
        if (len)
        {
            pbuf = payload;
            memcpy(&intensity, pbuf, sizeof(intensity));
            pbuf += sizeof(intensity);
            memcpy(&dosage, pbuf, sizeof(dosage)); 
            pbuf += sizeof(dosage);
            Serial.print(intensity);
            Serial.print(",");
            Serial.print(dosage);
            Serial.println();
        }
    }
}
