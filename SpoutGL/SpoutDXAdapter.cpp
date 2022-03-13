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

    std::cout << "here " << convertedSenderName << std::endl;
}

void SpoutDXAdapter::AdapterReleaseReceiver() { this->ReleaseReceiver(); }

bool SpoutDXAdapter::AdapterReceiveImage(rust::Slice<uint8_t> pixels,
                                         unsigned int width,
                                         unsigned int height, bool bRGB,
                                         bool bInvert) {
    const size_t store_size = pixels.size();

    if (store_size < width * height * 4) {
        return false;
    }

    std::cout << "Size: " << store_size << std::endl;

    unsigned char* raw_pixels =
        (unsigned char*)calloc(width * height * 4, sizeof(unsigned char));

    bool res = this->ReceiveImage(raw_pixels, width, height, bRGB, bInvert);

    printf("Inside pixel: %d %d %d\n", raw_pixels[100], raw_pixels[101],
           raw_pixels[102]);

    for (int i = 0; i < store_size; i++) {
        pixels[i] = (uint8_t)raw_pixels[i];
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