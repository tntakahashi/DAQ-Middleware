foreach(dir 
  BestEffortDispatcher
  change-SampleComp-name
  ConditionSampleMonitor
  Dispatcher
  SampleFilter
  SampleLogger
  SampleMonitor
  SampleReader
  SampleReader2
  Skeleton
  SkeletonSink
  SkeletonSource
  TinySink
  TinySource)
install(DIRECTORY ${dir} DESTINATION ${CMAKE_INSTALL_DATADIR}/examples)
endforeach(dir)

