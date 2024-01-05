#include <vector>
#include <cstdint>

// Define a base struct for the data parameters
struct DataParameters {
    [[nodiscard]] virtual std::vector<uint8_t> toVector() const = 0; // Convert the parameters to a vector of uint8
};

// Define a derived struct for a specific type of data parameters
struct RequestDataParameters : DataParameters {
    uint8_t paramPanelMode = 0x01;

    [[nodiscard]] std::vector<uint8_t> toVector() const override {
        return {paramPanelMode};
    }
};

// Define a struct to represent the SysEx data
struct SysExData {
    uint8_t manufacturerId = 0x41;
    uint8_t deviceId = 0x10;
    uint8_t modelId = 0x46;
//    uint8_t commandId = 0x12;
    uint8_t commandId = 0x11;
    uint8_t address[4] = {0x00, 0x00, 0x00, 0x00}; // This is always four bytes

    uint8_t filler[3] = {0x00, 0x00, 0x00};

    DataParameters* data = nullptr; // This can be of any length

    [[nodiscard]] uint8_t calculateChecksum() const {
        if (!data) return 0;

        int sum = 0;
        for (const auto& hex : data->toVector()) {
            sum += hex;
        }

        return static_cast<uint8_t>(128 - (sum % 128));
    }
};