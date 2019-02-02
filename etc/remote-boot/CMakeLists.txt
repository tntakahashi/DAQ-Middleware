install(FILES
  bootComps-xinetd.sample
  services.sample
  DESTINATION ${PROJECT_INSTALL_DATADIR}/etc/remote-boot
  )

install(PROGRAMS
  bootComps.py
  DESTINATION ${PROJECT_INSTALL_DATADIR}/etc/remote-boot
  )
