-- xmake.lua for Third-Party Libraries Examples
-- This file demonstrates usage of popular C++ libraries

-- Global settings for all library examples
set_project("cpp_3rdparty_examples")
set_version("1.0.0")
set_warnings("all")
set_optimize("fastest")

-- Add required third-party packages
add_requires("fmt", "spdlog", "nlohmann_json", "catch2 3.x", "eigen")
-- Add raylib separately as it may require platform-specific configuration
add_requires("raylib")

-- Common C++17 language setting for compatibility
add_languages("c++17")

-- fmt library example
target("fmt_example")
    set_kind("binary")
    add_files("fmtlib/*.cpp")
    add_packages("fmt")
    set_targetdir("bin/third_party")
    add_languages("c++17")
    set_group("formatting")

-- spdlog logging library example  
target("spdlog_example")
    set_kind("binary")
    add_files("spdlog/*.cpp")
    add_packages("spdlog")
    set_targetdir("bin/third_party")
    add_languages("c++17")
    set_group("logging")

-- nlohmann/json library example
target("json_example")
    set_kind("binary")
    add_files("nlohmann_json/*.cpp")
    add_packages("nlohmann_json")
    set_targetdir("bin/third_party")
    add_languages("c++17")
    set_group("serialization")

-- Catch2 testing framework example
target("catch2_example")
    set_kind("binary")
    add_files("catch2/*.cpp")
    add_packages("catch2")
    set_targetdir("bin/third_party")
    add_languages("c++17")
    set_group("testing")

-- Eigen linear algebra library example
target("eigen_example")
    set_kind("binary")
    add_files("eigen/*.cpp")
    add_packages("eigen")
    set_targetdir("bin/third_party")
    add_languages("c++17")
    set_group("math")

-- Raylib game library example
target("raylib_example")
    set_kind("binary")
    add_files("raylib_cpp/*.cpp")
    add_packages("raylib")
    set_targetdir("bin/third_party")
    add_languages("c++17")
    set_group("graphics")
    -- Platform specific settings for raylib
    if is_plat("windows") then
        add_syslinks("winmm", "gdi32", "opengl32")
    elseif is_plat("linux") then
        add_syslinks("GL", "m", "pthread", "dl", "rt", "X11")
    elseif is_plat("macosx") then
        add_frameworks("OpenGL", "Cocoa", "IOKit", "CoreFoundation", "CoreVideo")
    end

-- Comprehensive demo showing multiple libraries together
target("combined_example")
    set_kind("binary")
    add_files("combined/*.cpp")
    add_packages("fmt", "spdlog", "nlohmann_json")
    set_targetdir("bin/third_party")
    add_languages("c++17")
    set_group("integration")

-- Information target (shows available examples)
target("show_examples")
    set_kind("phony")
    on_run(function (target)
        print("Available Third-Party Library Examples:")
        print("========================================")
        print("• fmt_example      - Modern C++ string formatting")
        print("• spdlog_example   - Fast C++ logging library")
        print("• json_example     - JSON parsing and serialization")
        print("• catch2_example   - Modern C++ testing framework")
        print("• eigen_example    - Linear algebra and matrix operations")
        print("• raylib_example   - Simple game programming framework")
        print("• combined_example - Integration of multiple libraries")
        print("")
        print("Usage:")
        print("  xmake build [target_name]    - Build specific example")
        print("  xmake run [target_name]      - Run specific example")
        print("  xmake build -g [group]       - Build examples by group")
        print("")
        print("Groups: formatting, logging, serialization, testing, math, graphics, integration")
    end)

-- Set default target
set_default("show_examples")