-- xmake.lua for Modern C++ Features Showcase
set_project("cpp_features")
set_version("1.0.0")

-- Global settings
set_languages("c++23")
set_warnings("all", "error")
set_optimize("fastest")

-- Add standard library support
add_requires("fmt", "range-v3")

-- Common compile options
add_cxxflags("-std=c++23", "-Wall", "-Wextra")
if is_plat("windows") then
    add_cxxflags("/std:c++latest", "/permissive-", "/Zc:__cplusplus")
end

-- C++11 features target
target("cpp11_features")
    set_kind("binary")
    add_files("src/cpp11/*.cpp")
    add_includedirs("include")
    set_targetdir("bin")

-- C++14 features target  
target("cpp14_features")
    set_kind("binary")
    add_files("src/cpp14/*.cpp")
    add_includedirs("include")
    set_targetdir("bin")

-- C++17 features target
target("cpp17_features")
    set_kind("binary")
    add_files("src/cpp17/*.cpp")
    add_includedirs("include")
    set_targetdir("bin")

-- C++20 features target
target("cpp20_features")
    set_kind("binary")
    add_files("src/cpp20/*.cpp")
    add_includedirs("include")
    set_targetdir("bin")
    add_packages("range-v3")

-- C++23 features target
target("cpp23_features")
    set_kind("binary")
    add_files("src/cpp23/*.cpp")
    add_includedirs("include")
    set_targetdir("bin")
    add_packages("fmt")

-- C++26 features target (experimental/proposed features)
target("cpp26_features")
    set_kind("binary")
    add_files("src/cpp26/*.cpp")
    add_includedirs("include")
    set_targetdir("bin")
    add_packages("fmt", "range-v3")
    -- Enable latest C++ standard for experimental features
    if is_plat("windows") then
        add_cxxflags("/std:c++latest")
    else
        add_cxxflags("-std=c++2c") -- or -std=c++26 when available
    end

-- Main showcase program
target("modern_cpp_showcase")
    set_kind("binary")
    add_files("src/main_simple.cpp")
    add_includedirs("include")
    set_targetdir("bin")

-- Examples target
target("examples")
    set_kind("binary")
    add_files("examples/*.cpp")
    add_includedirs("include")
    set_targetdir("bin/examples")
    add_packages("fmt", "range-v3")
    set_default(false)

-- Test target
target("tests")
    set_kind("binary")
    add_files("tests/*.cpp")
    add_includedirs("include")
    set_targetdir("bin/tests")
    set_default(false)