/*

                                        Spout.h

        Documentation - https://spoutgl-site.netlify.app/

        Copyright (c) 2014-2022, Lynn Jarvis. All rights reserved.

        Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

                1. Redistributions of source code must retain the above
   copyright notice, this list of conditions and the following disclaimer.

                2. Redistributions in binary form must reproduce the above
   copyright notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

        THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
   IS"	AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
   PURPOSE	ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
        PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
   EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/
#pragma once

#ifndef __SpoutAdapter__
#define __SpoutAdapter__

#include <memory>
#include <string>

#include "SpoutDX.h"
#include "rust/cxx.h"

class SPOUT_DLLEXP SpoutDXAdapter : private spoutDX {
   public:
    SpoutDXAdapter();
    ~SpoutDXAdapter();

    bool AdapterOpenDirectX11();
    void AdapterCloseDirectX11();

    bool AdapterReceiveImage(rust::Slice<uint8_t> pixels, unsigned int width,
                             unsigned int height, bool bRGB = false,
                             bool bInvert = false);
    // Specify sender for connection
    //   If a name is specified, the receiver will not connect to any other
    //   unless the user selects one If that sender closes, the receiver will
    //   wait for the nominated sender to open If no name is specified, the
    //   receiver will connect to the active sender
    void AdapterSetReceiverName(std::string& sendername);
    // Close receiver and release resources ready to connect to another sender
    void AdapterReleaseReceiver();
    //   Checked at every cycle before receiving data
    bool AdapterIsUpdated();
    // Query sender connection
    //   If the sender closes, receiving functions return false,
    bool AdapterIsConnected();
    // Query received frame status
    //   The receiving texture or pixel buffer is only refreshed if the sender
    //   has produced a new frame This can be queried to process texture data
    //   only for new frames
    bool AdapterIsFrameNew();
    // Received sender width
    unsigned int AdapterGetSenderWidth();
    // Received sender height
    unsigned int AdapterGetSenderHeight();
};

std::unique_ptr<SpoutDXAdapter> new_spout_adapter();

#endif
