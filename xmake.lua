-- xmake.lua for Modern C++ Features Showcase
set_project("cpp_features")
set_version("1.0.0")

-- Global settings
set_warnings("all", "error")
set_optimize("fastest")

-- Add standard library support
add_requires("fmt")

-- C++11 features target
target("cpp11_features")
    set_kind("binary")
    add_files("src/cpp11/*.cpp")
    add_includedirs("include")
    set_targetdir("bin")
    add_languages("c++11")

-- C++14 features target  
target("cpp14_features")
    set_kind("binary")
    add_files("src/cpp14/*.cpp")
    add_includedirs("include")
    set_targetdir("bin")
    add_languages("c++14")

-- C++17 features target
target("cpp17_features")
    set_kind("binary")
    add_files("src/cpp17/*.cpp")
    add_includedirs("include")
    set_targetdir("bin")
    add_languages("c++17")

-- C++20 features target
target("cpp20_features")
    set_kind("binary")
    add_files("src/cpp20/*.cpp")
    add_includedirs("include")
    set_targetdir("bin")
    add_languages("c++20")

-- C++23 features target
target("cpp23_features")
    set_kind("binary")
    add_files("src/cpp23/*.cpp")
    add_includedirs("include")
    set_targetdir("bin")
    add_languages("c++23")
    add_packages("fmt")

-- C++26 features target (experimental/proposed features)
target("cpp26_features")
    set_kind("binary")
    add_files("src/cpp26/*.cpp")
    add_includedirs("include")
    set_targetdir("bin")
    add_languages("c++23") -- Use C++23 as base for experimental features
    add_packages("fmt")
    -- Enable latest C++ standard for experimental features
    if is_plat("windows") then
        add_cxxflags("/std:c++latest")
    else
        add_cxxflags("-std=c++2c") -- Experimental C++26
    end

-- Main showcase program
target("modern_cpp_showcase")
    set_kind("binary")
    add_files("src/main_simple.cpp")
    add_includedirs("include")
    set_targetdir("bin")
    add_languages("c++17") -- Use C++17 for compatibility

-- Examples target
target("examples")
    set_kind("binary")
    add_files("examples/*.cpp")
    add_includedirs("include")
    set_targetdir("bin/examples")
    add_languages("c++17")
    add_packages("fmt")
    set_default(false)

-- Test target
target("tests")
    set_kind("binary")
    add_files("tests/*.cpp")
    add_includedirs("include")
    set_targetdir("bin/tests")
    add_languages("c++17")
    set_default(false)