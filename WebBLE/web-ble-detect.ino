#include <ArduinoBLE.h>

uint8_t uvindexValue = 0x0;
#define UUID16_SVC_ENVIRONMENTAL_SENSING 0x181A
#define UUID16_CHR_UV_INDEX 0x2A76

BLEService environmental_sensing_service = BLEServicec(UUID16_SVC_ENVIRONMENTAL_SENSING);
BLECharacteristic uv_index_characteristic = BLECharacteristic(UUID16_CHR_UV_INDEX);

void setup() {
    //Used for communication between the Arduino board and a computer or other devices.
    Serial.begin(115200);
    delay(500);
    Serial.println("Start!");

    //Initialize the BLE device
    BLE.begin();

    //Set the device name in the built in device name characteristic
    BLE.setDeviceName("Greg's Arduino");

    setupESService();
    
    startAvd();
}

void loop() {
    uvindexvalue = random(0, 11);

    Serial.print("UV Index: ");
    Serial.println(uvindexvalue);

    if(uv_index_characteristic.indicate(&uvindexvalue, sizeof(uvindexvalue))) {
        Serial.print("Update UV Index: ");
        Serial.println(unindexvalue);
    }
    else {
        Serial.println("UV Index Indicate not set");
    }

    delay(1000);
}

//Start advertising
void startAvd(void) {
    //Add service
    BLE.addService(environmental_sensing_service);

    //Set the advertising interval in units of 0.625 ms.
    BLE.setAdvertisingInterval(1600);

    //Start advertising
    BLE.advertise();
}

void setupESService {
    environmental_sensing_service.begin();

    uv_index_characteristic.setProperties(CHR_PROPS_INDICATE);
    uv_index_characteristic.setPermission(SECMODE_OPEN, SECMODE_NO_ACCESS);
    uv_index_characteristic.setFixedLen(1);
    uv_index_characteristic.begin();

    uv_index_characteristic.write(&uvindexvalue, sizeof(uvindexvalue));
}