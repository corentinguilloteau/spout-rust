use cxx::CxxString;
#[cxx::bridge]
pub mod ffi {

    unsafe extern "C++" {
        include!("spout_rust/SpoutGL/SpoutDXAdapter.h");

        pub type SpoutDXAdapter;

        pub fn new_spout_adapter() -> UniquePtr<SpoutDXAdapter>;

        pub fn AdapterSetReceiverName(
            self: Pin<&mut SpoutDXAdapter>,
            sendername: Pin<&mut CxxString>,
        );

        pub fn AdapterReceiveImage(
            self: Pin<&mut SpoutDXAdapter>,
            pixels: &mut [u8],
            width: u32,
            height: u32,
            bRGB: bool,
            bInverted: bool,
        ) -> bool;

        pub fn AdapterIsUpdated(self: Pin<&mut SpoutDXAdapter>) -> bool;
        pub fn AdapterIsConnected(self: Pin<&mut SpoutDXAdapter>) -> bool;
        pub fn AdapterIsFrameNew(self: Pin<&mut SpoutDXAdapter>) -> bool;
        pub fn AdapterGetSenderWidth(self: Pin<&mut SpoutDXAdapter>) -> u32;
        pub fn AdapterGetSenderHeight(self: Pin<&mut SpoutDXAdapter>) -> u32;

        // DirectX functions

        pub fn AdapterOpenDirectX11(self: Pin<&mut SpoutDXAdapter>) -> bool;
        pub fn AdapterCloseDirectX11(self: Pin<&mut SpoutDXAdapter>);

    }
}
