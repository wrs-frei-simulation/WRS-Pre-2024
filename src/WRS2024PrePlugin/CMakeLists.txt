set(sources
  WRS2024PrePlugin.cpp
)

set(headers

)

set(target CnoidWRS2024PrePlugin)
make_gettext_mofiles(${target} mofiles)
choreonoid_add_plugin(${target} ${sources} ${mofiles} HEADERS ${headers})
target_link_libraries(${target} PUBLIC CnoidBodyPlugin CnoidWRSUtilPlugin)