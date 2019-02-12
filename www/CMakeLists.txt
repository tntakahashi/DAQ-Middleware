include(Distributions.cmake)

if(USE_MOD_WSGI)
  add_subdirectory(mod_wsgi)
elseif(USE_MOD_PYTHON)
  add_subdirectory(mod_python)
endif()
