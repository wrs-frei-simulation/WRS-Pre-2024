set(sources
  WRSUtilBar.cpp
  WRSUtilPlugin.cpp
)

set(headers
  WRSUtilBar.h
  exportdecl.h
)

set(target CnoidWRSUtilPlugin)
make_gettext_mofiles(${target} mofiles)
choreonoid_add_plugin(${target} ${sources} ${mofiles} HEADERS ${headers})
target_link_libraries(${target} PUBLIC CnoidBodyPlugin CnoidCFDPlugin CnoidVFXPlugin)