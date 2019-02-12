find_program(LSB_RELEASE_EXEC lsb_release)

execute_process(COMMAND ${LSB_RELEASE_EXEC} -is
  OUTPUT_VARIABLE OS
  OUTPUT_STRIP_TRAILING_WHITESPACE
  )

execute_process(COMMAND ${LSB_RELEASE_EXEC} -rs
  OUTPUT_VARIABLE VERSION
  OUTPUT_STRIP_TRAILING_WHITESPACE
  )

find_program(UNAME_EXEC uname)

execute_process(COMMAND ${UNAME_EXEC} -m
  OUTPUT_VARIABLE ARCH
  OUTPUT_STRIP_TRAILING_WHITESPACE
  )

string(SUBSTRING ${VERSION} 0 1 MAJOR_VERSION)

message("LSB_RELEASE_EXEC: ${LSB_RELEASE_EXEC}")
message("OS:               ${OS}")
message("VERSION:          ${VERSION}")
message("ARCH:             ${ARCH}")
message("MAJOR_VERSION:    ${MAJOR_VERSION}")


########## Scientific Linux 5.0 - 5.7 ##########
# Scientific Linux older than or equal to 5.7 returns ScientificSL 
# Scientific Linux newer than or equal to 5.8 returns Scientific
if("${OS}" STREQUAL "ScientificSL")
  set(WWW_DOCUMENT_ROOT "/var/www/html")
  set(HTTPD_CONF_DIR    "/etc/httpd/conf.d")
  set(USE_MOD_PYTHON    1)

########## Scientific Linux 5.8 - , 7.x ##########
elseif("${OS}" STREQUAL "Scientific")
  set(WWW_DOCUMENT_ROOT "/var/www/html")
  set(HTTPD_CONF_DIR    "/etc/httpd/conf.d")
  set(USE_MOD_PYTHON    1)

  if(${MAJOR_VERSION} EQUAL 5)
    set(USE_MOD_PYTHON 1)
  else
    set(USE_MOD_WSGI 1)
  endif()
    
########## Scientific Linux CERN, CentOS ##########
elseif(("${OS}" STREQUAL "ScientificCERNSLC") OR ("${OS}" STREQUAL "CentOS"))
  set(WWW_DOCUMENT_ROOT "/var/www/html")
  set(HTTPD_CONF_DIR    "/etc/httpd/conf.d")

  if(${MAJOR_VERSION} EQUAL 5)
    set(USE_MOD_PYTHON 1)
  else
    set(USE_MOD_WSGI 1)
  endif()

########## Fedora ##########
elseif("${OS}" STREQUAL "Fedora")
  set(WWW_DOCUMENT_ROOT "/var/www/html")
  set(HTTPD_CONF_DIR    "/etc/httpd/conf.d")
  set(USE_MOD_WSGI      1)

########## Debian, Ubuntu ##########
elseif(("${OS}" STREQUAL "Debian") OR ("${OS}" STREQUAL "Ubuntu"))
  set(WWW_DOCUMENT_ROOT "/var/www")
  set(HTTPD_CONF_DIR    "/etc/apache2/conf.d")
  set(USE_MOD_WSGI      1)
  
########## ArchLinux  ##########
elseif(("${OS}" STREQUAL "archlinux") OR ("${OS}" STREQUAL "arch"))
  set(WWW_DOCUMENT_ROOT "/srv/http")
  set(HTTPD_CONF_DIR    "/etc/httpd/conf/extra")
  set(USE_MOD_WSGI      1)

########## Raspbian ##########
elseif("${OS}" STREQUAL "Rasbian")
  set(WWW_DOCUMENT_ROOT "/var/www/html")
  set(HTTPD_CONF_DIR    "/etc/apache2/conf-available")
  set(USE_MOD_WSGI      1)
endif()

########## Unknown ##########
if(NOT WWW_DOCUMENT_ROOT)
  set(WWW_DOCUMENT_ROOT "/")
  set(HTTPD_CONF_DIR    "/")
  set(USE_MOD_WSGI      1)
endif()



