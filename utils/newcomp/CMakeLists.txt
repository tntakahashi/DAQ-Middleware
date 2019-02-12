add_custom_target(newcomp ALL
  COMMAND perl create_newcomp Skeleton SkeletonSource SkeletonSink > newcomp
  )
  
install(PROGRAMS newcomp
  DESTINATION ${CMAKE_INSTALL_BINDIR}
  )
  
  
