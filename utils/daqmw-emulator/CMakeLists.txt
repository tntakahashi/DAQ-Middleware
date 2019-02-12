add_executable(daqmw-emulator
  daqmw-emulator.c
  gaussian_rand.c
  get_num.c
  my_signal.c
  prepare_send_data.c
  send_data.c
  )

install(TARGETS
  daqmw-emulator
  DESTINATION ${CMAKE_INSTALL_BINDIR}
  )
