add_subdirectory(idl)

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

