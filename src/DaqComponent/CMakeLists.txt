add_subdirectory(idl)

file(COPY  Condition.h             DESTINATION ${CMAKE_BINARY_DIR}/include)
file(COPY  DaqComponentBase.h      DESTINATION ${CMAKE_BINARY_DIR}/include)
file(COPY  DaqComponentException.h DESTINATION ${CMAKE_BINARY_DIR}/include)
file(COPY  FatalType.h             DESTINATION ${CMAKE_BINARY_DIR}/include)
file(COPY  Timer.h                 DESTINATION ${CMAKE_BINARY_DIR}/include)
file(COPY  json2conlist.h          DESTINATION ${CMAKE_BINARY_DIR}/include)
file(COPY  DaqLog.h                DESTINATION ${CMAKE_BINARY_DIR}/include)



install(FILES
  Condition.h
  DaqComponentBase.h
  DaqComponentException.h
  FatalType.h
  Timer.h
  json2conlist.h
  DaqLog.h
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  )

