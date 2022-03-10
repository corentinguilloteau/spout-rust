#[cxx::bridge]
mod ffi {
    use cxx::CxxString;

    unsafe extern "C++" {
        include!("spout-rust/SpoutGL/Spout.h");

        type Spout;

        fn new_spout() -> UniquePtr<Spout>;

        fn SetSenderName(&self, sendername: &CxxString);
    }
}
