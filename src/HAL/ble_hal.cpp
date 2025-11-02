/******************************************************************************
 *
 * Copyright (c) 2025 Marconatale Parise. All rights reserved.
 *
 * This file is part of proprietary software. Unauthorized copying, distribution,
 * or modification of this file, via any medium, is strictly prohibited without
 * prior written permission from the copyright holder.
 *
 *****************************************************************************/
/**
 * @file ble_hal.c
 * @brief Abstraction of ble communication Interface 
 *
 * This implementation file provides an abstraction interface to manage ble communication.
 * 
 * @author Marconatale Parise
 * @date 09 June 2025
 *
 */
#include "HAL/ble_hal.h"

BLEServer *pServer;
BLECharacteristic* characteristic_temp = nullptr;
BLECharacteristic* characteristic_humidity = nullptr;
BLECharacteristic* characteristic_slrrad = nullptr;
bool deviceConnected = false;

class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) override{
      deviceConnected = true;
      DEBUG_PRINT("Device Connected\n");
    };
  void onDisconnect(BLEServer *pServer) override{
    deviceConnected = false;
    DEBUG_PRINT("Device Disconnected\n");
    // restart advertising so central can discover again
    BLEAdvertising *pAdvertising = pServer->getAdvertising();
    if (pAdvertising) {
        pAdvertising->start();
        DEBUG_PRINT("Advertising restarted on disconnect\n");
    }
  }
};

/***********************************************************
 Function Definitions
***********************************************************/
void ble_init(){
    BLEDevice::init("IoT Sensor Node");
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());
    ble_create_service();
}

void ble_create_service() {
  BLEService *pService = pServer->createService(SERVICE_UUID);
  characteristic_temp = pService->createCharacteristic(
                     CHARACTERISTIC_UUID_TEMP,
                      BLECharacteristic::PROPERTY_READ |
                      BLECharacteristic::PROPERTY_NOTIFY
                   );
  characteristic_temp->addDescriptor(new BLE2902());
  characteristic_humidity = pService->createCharacteristic(
                     CHARACTERISTIC_UUID_HUMIDITY,
                      BLECharacteristic::PROPERTY_READ |
                      BLECharacteristic::PROPERTY_NOTIFY
                   );
  characteristic_humidity->addDescriptor(new BLE2902());
  characteristic_slrrad = pService->createCharacteristic(
                     CHARACTERISTIC_UUID_SLRRAD,
                      BLECharacteristic::PROPERTY_READ |
                      BLECharacteristic::PROPERTY_NOTIFY
                   );
  characteristic_slrrad->addDescriptor(new BLE2902());
  pService->start();
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();
}

void ble_transmit_temp(uint16_t value){
    characteristic_temp->setValue(value);
    characteristic_temp->notify();
}

void ble_transmit_humidity(uint16_t value){
    characteristic_humidity->setValue(value);
    characteristic_humidity->notify();
}

void ble_transmit_slrrad(uint16_t value){
    characteristic_slrrad->setValue(value);
    characteristic_slrrad->notify();
}

