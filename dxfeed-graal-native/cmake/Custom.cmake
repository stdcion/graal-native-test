# Function to register BuildAll target
function(add_target_to_build_all target)
    set(BuildAll ${META_PROJECT_NAME}.build-all)
    if (NOT TARGET ${BuildAll})
        add_custom_target(${BuildAll})
    endif ()
    add_dependencies(${BuildAll} ${target})
endfunction()
