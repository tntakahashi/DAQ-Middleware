configure_file(bootComps-xinetd.sample.in bootComps-xinetd.sample @ONLY)

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/bootComps-xinetd.sample
  services.sample
  DESTINATION ${CMAKE_INSTALL_DATADIR}/etc/remote-boot
  )

install(PROGRAMS
  bootComps.py
  DESTINATION ${CMAKE_INSTALL_DATADIR}/etc/remote-boot
  )
