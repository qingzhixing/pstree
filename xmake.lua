add_rules("mode.debug", "mode.release")
set_languages("c++23")

target("pstree")
    set_kind("binary")
    add_files("src/*.cpp")