#include "SpoutDXAdapter.h"

#include <stdio.h>

SpoutDXAdapter::SpoutDXAdapter() : spoutDX() {}
SpoutDXAdapter::~SpoutDXAdapter() {}

std::unique_ptr<SpoutDXAdapter> new_spout_adapter() {
    return std::unique_ptr<SpoutDXAdapter>(new SpoutDXAdapter());
}

bool SpoutDXAdapter::AdapterOpenDirectX11() { return this->OpenDirectX11(); }

void SpoutDXAdapter::AdapterCloseDirectX11() { this->CloseDirectX11(); }

void SpoutDXAdapter::AdapterSetReceiverName(std::string& sendername) {
    const char* convertedSenderName = sendername.c_str();

    this->SetReceiverName(convertedSenderName);
}

void SpoutDXAdapter::AdapterReleaseReceiver() { this->ReleaseReceiver(); }

bool SpoutDXAdapter::AdapterReceiveImage(rust::Slice<uint8_t> pixels,
                                         unsigned int width,
                                         unsigned int height, bool bRGB,
                                         bool bInvert) {
    const size_t store_size = pixels.size();

    if (store_size < width * height * 3) {
        return false;
    }

    unsigned char* raw_pixels =
        (unsigned char*)calloc(width * height * 4, sizeof(unsigned char));

    bool res = this->ReceiveImage(raw_pixels, width, height, false, bInvert);

    for (int i = 0; i < store_size / 3; i++) {
        pixels[3 * i] = (uint8_t)raw_pixels[4 * i + 2];
        pixels[3 * i + 1] = (uint8_t)raw_pixels[4 * i + 1];
        pixels[3 * i + 2] = (uint8_t)raw_pixels[4 * i];
    }

    free(raw_pixels);

    return res;
}

bool SpoutDXAdapter::AdapterIsUpdated() { return this->IsUpdated(); }

bool SpoutDXAdapter::AdapterIsConnected() { return this->IsConnected(); }

bool SpoutDXAdapter::AdapterIsFrameNew() { return this->IsFrameNew(); }

unsigned int SpoutDXAdapter::AdapterGetSenderWidth() {
    return this->GetSenderWidth();
}

unsigned int SpoutDXAdapter::AdapterGetSenderHeight() {
    return this->GetSenderHeight();
}

int SpoutDXAdapter::AdapterGetSenderCount() { return this->GetSenderCount(); }

rust::String SpoutDXAdapter::AdapterGetSenderNameByIndex(int index) {
    char* name = (char*)calloc(1024, sizeof(char));

    this->GetSender(index, name, 1024);

    const rust::String* transformedName = new rust::String(name);

    free(name);

    return *transformedName;
}