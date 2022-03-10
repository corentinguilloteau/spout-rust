use cxx::CxxString;
#[cxx::bridge]
mod ffi {

    unsafe extern "C++" {
        include!("spout-rust/SpoutGL/SpoutAdapter.h");

        type SpoutAdapter;

        fn new_spout_adapter() -> UniquePtr<SpoutAdapter>;

        fn AdapterSetSenderName(self: Pin<&mut SpoutAdapter>, sendername: Pin<&mut CxxString>);
    }
}

pub fn main() {}
