set(PYTHON_SITELIB "${CMAKE_INSTALL_LIBDIR}/python")

add_custom_target(confPanel
  COMMAND base64 images/one.gif  > images/one.gif.base64
  COMMAND base64 images/two.gif  > images/two.gif.base64
  COMMAND base64 images/four.gif > images/four.gif.base64
  COMMAND ./rewrite.sh 
)
  
install(PROGRAMS confPanel.py DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES
  __init__.py
  image_nb.py
  notebook.py
  writer.py
  DESTINATION ${PYTHON_SITELIB/configGUI}
  )
