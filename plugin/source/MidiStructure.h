#include <cstdint> // for uint8_t
#include <vector>
#include <numeric> // for std::accumulate

static const std::vector<uint8_t> kRolandManufacturerId = {0x41};
static const uint8_t kRolandJv880ModelId = 0x46;
static const uint8_t kRolandDefaultDeviceId = 0x10;

static const uint8_t kMidiCommandIdRequestData = 0x11;
static const uint8_t kMidiCommandIdDataSet = 0x12;

struct MidiSysExMessage {
    const uint8_t startByte = 0xF0; // Start byte (0xF0)
    std::vector<uint8_t> manufacturerId = {}; // Manufacturer ID (variable size)
    uint8_t deviceId = 0x00; // Device ID
    uint8_t modelId = 0x00; // Model ID
    uint8_t commandId = 0x00; // Command byte
    uint8_t address[4] = {}; // 4 bytes for address
    const uint8_t endByte = 0xF7; // End byte (0xF7)

    MidiSysExMessage() = default;

    [[nodiscard]] virtual uint8_t calculateChecksum() const = 0; // Pure virtual function
    [[nodiscard]] virtual std::vector<uint8_t> toSysExData() const = 0; // Pure virtual function
};

template<typename T>
struct MidiSysExMessageDerived : MidiSysExMessage {
    T sizeOrData{}; // Variable type for size or data

    [[nodiscard]] uint8_t calculateChecksum() const override {
        int checksum = 0;
        for (uint8_t byte: address) {
            checksum += byte;
        }
        for (uint8_t byte: sizeOrData) {
            checksum += byte;
        }

        return static_cast<uint8_t>(128 - (checksum % 128));
    }

    [[nodiscard]] std::vector<uint8_t> toSysExData() const override {
        std::vector<uint8_t> vector = {startByte};
        vector.insert(vector.end(), std::begin(manufacturerId), std::end(manufacturerId));
        vector.push_back(deviceId);
        vector.push_back(modelId);
        vector.push_back(commandId);
        vector.insert(vector.end(), std::begin(address), std::end(address));
        vector.insert(vector.end(), std::begin(sizeOrData), std::end(sizeOrData));
        vector.push_back(calculateChecksum());
        vector.push_back(endByte);

        return vector;
    }
};

// Define RequestMessage with size as an array of 4 bytes
//typedef MidiSysExMessageDerived<uint8_t[4]> RequestMessage;
struct RequestMessage : MidiSysExMessageDerived<uint8_t[4]> {
    RequestMessage() {
        commandId = kMidiCommandIdRequestData;
    }
};
// Define DataSetMessage with data as a vector of bytes
//typedef MidiSysExMessageDerived<std::vector<uint8_t>> DataSetMessage;
struct DataSetMessage : MidiSysExMessageDerived<std::vector<uint8_t>> {
    DataSetMessage() {
        commandId = kMidiCommandIdDataSet;
    }
};


struct RolandRequestMessage : RequestMessage {
    RolandRequestMessage() {
        manufacturerId = kRolandManufacturerId;
        deviceId = kRolandDefaultDeviceId;
        modelId = kRolandJv880ModelId;
    }
};

struct RolandJv880RequestPanelMode : RolandRequestMessage {
    RolandJv880RequestPanelMode() {
        address[0] = 0x00;
        address[1] = 0x00;
        address[2] = 0x00;
        address[3] = 0x00;
        sizeOrData[0] = 0x00;
        sizeOrData[1] = 0x00;
        sizeOrData[2] = 0x00;
        sizeOrData[3] = 0x01;
    }
};