SET(DepName "gcl")
ProcessDependencies(${DepName})


get_filename_component(GCL_ROOT ${CMAKE_CURRENT_LIST_DIR}/../ REALPATH)
SET(GCL_INCLUDE_DIR ${GCL_ROOT})


SET(gcl_INCLUDE_DIR ${GCL_INCLUDE_DIR} ${DEP_INC})
list(APPEND gcl_LIBS gcl)
list(APPEND gcl_LIBS ${DEP_LIBS} )

#SET(gcl_LIBS gcl ${DEP_LIBS})
