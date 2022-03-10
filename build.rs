fn main() {
    println!(
        "cargo:rustc-link-search={}",
        "C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.18362.0\\um\\x64"
    );

    println!("cargo:rustc-link-lib={}", "OpenGL32");
    println!("cargo:rustc-link-lib={}", "Uuid");
    println!("cargo:rustc-link-lib={}", "User32");
    println!("cargo:rustc-link-lib={}", "Gdi32");

    cxx_build::bridge("src/main.rs")
        .file("SpoutGL/SpoutAdapter.cpp")
        .file("SpoutGL/Spout.cpp")
        .file("SpoutGL/SpoutCopy.cpp")
        .file("SpoutGL/SpoutDirectX.cpp")
        .file("SpoutGL/SpoutFrameCount.cpp")
        .file("SpoutGL/SpoutGL.cpp")
        .file("SpoutGL/SpoutGLextensions.cpp")
        .file("SpoutGL/SpoutReceiver.cpp")
        .file("SpoutGL/SpoutSender.cpp")
        .file("SpoutGL/SpoutSenderNames.cpp")
        .file("SpoutGL/SpoutSharedMemory.cpp")
        .file("SpoutGL/SpoutUtils.cpp")
        //.compiler(clang)
        // .target("x86_64-pc-windows-msvc")
        // .flag("-mssse3")
        // .pic(false)
        //.archiver(ar)
        .warnings(false)
        //.no_default_flags(true)
        .compile("spout-rust");
}
