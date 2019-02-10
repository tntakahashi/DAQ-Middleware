get_filename_component(changes    "Changes"    REALPATH)
get_filename_component(changes-ja "Changes.ja" REALPATH)
get_filename_component(version    "VERSION"    REALPATH)

install(FILES
  README
  DAQ-Middleware-1.1.0-Tech.pdf
  DAQ-Middleware-1.4.0-DevManual.pdf
  ${changes}
  ${changes-ja}
  ${version}
  DESTINATION ${CMAKE_INSTALL_DATADIR}/docs
  )
