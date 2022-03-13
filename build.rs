use std::env;
use std::path::Path;

fn main() {
    let mut clang_path;

    if let Some(t) = env::var_os("LIBCLANG_PATH") {
        clang_path = t.to_str().unwrap().to_owned();
        clang_path.push_str("\\clang++.exe");
    } else {
        eprintln!("LIBCLANG_PATH environnement variable must be specified.");
        return;
    }

    println!(
        "cargo:rustc-link-search={}",
        "C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.18362.0\\um\\x64"
    );

    // println!("cargo:rustc-link-arg={}", "/MT");

    println!("cargo:rustc-link-lib={}", "OpenGL32");
    println!("cargo:rustc-link-lib={}", "Uuid");
    println!("cargo:rustc-link-lib={}", "User32");
    println!("cargo:rustc-link-lib={}", "Gdi32");

    cxx_build::bridge("src/lib.rs")
        .file("SpoutGL/Spout.cpp")
        .file("SpoutGL/SpoutCopy.cpp")
        .file("SpoutGL/SpoutDirectX.cpp")
        .file("SpoutGL/SpoutDX.cpp")
        .file("SpoutGL/SpoutFrameCount.cpp")
        .file("SpoutGL/SpoutGL.cpp")
        .file("SpoutGL/SpoutGLextensions.cpp")
        .file("SpoutGL/SpoutReceiver.cpp")
        .file("SpoutGL/SpoutSender.cpp")
        .file("SpoutGL/SpoutSenderNames.cpp")
        .file("SpoutGL/SpoutSharedMemory.cpp")
        .file("SpoutGL/SpoutUtils.cpp")
        .file("SpoutGL/SpoutDXAdapter.cpp")
        // .compiler(Path::new(&clang_path))
        // .target("x86_64-pc-windows-msvc")
        // .flag("-mssse3")
        // .pic(false)
        // //.archiver(ar)
        // .static_crt(true)
        // .static_flag(true)
        // .warnings(false)
        //.no_default_flags(true)
        .compile("spout_rust");
}
