#ifndef CAN_LIB_H
#define CAN_LIB_H

class LINUX_CAN
{
public:
    // Initialize CAN interface
    bool init() { return true; }

    // Configure alerts ???
    bool alertConfigure() { return true; }

    // Get detects alerts TWAI controller
    bool getAlerts() { return false; }

    // Deinitialize TWAI controller
    void close() { }

    // Send a CAN frame
    bool send(uint32_t id, const uint8_t *data, uint8_t length, bool extended = false) { return true; }

    // Check if a frame is available
    bool available() { return false; }

    // Receive a CAN frame
    bool receive(uint32_t *id, uint8_t *data, uint8_t *length, bool *extended = nullptr) { return false; }
};

#endif //CAN_LIB_H