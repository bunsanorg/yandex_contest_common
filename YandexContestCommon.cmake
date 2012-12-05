include(BunsanCommon)

# binary targets
function(yandex_contest_add_binary_targets bin_targets_)
    set(bin_targets)

    foreach(bin ${ARGN})
        set(trgt ${PROJECT_NAME}_${bin})
        list(APPEND bin_targets ${trgt})
        set(binprefix src/bin/${bin})
        if(EXISTS ${CMAKE_SOURCE_DIR}/${binprefix}.cpp)
            add_executable(${trgt} ${binprefix}.cpp)
        elseif(EXISTS ${CMAKE_SOURCE_DIR}/${binprefix}.c)
            add_executable(${trgt} ${binprefix}.c)
        else()
            message(SEND_ERROR "Source does not exist for target ${trgt}")
        endif()
        target_link_libraries(${trgt} ${PROJECT_NAME} ${libraries})
    endforeach()

    set(${bin_targets_} ${bin_targets} PARENT_SCOPE)
endfunction()
