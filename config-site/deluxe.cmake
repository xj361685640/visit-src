include(${VISIT_SOURCE_DIR}/config-site/windows.cmake)

# can provide overrides for windows.cmake settings below

# disable some warnings
# 4244 conversion double to float etc
# 4305 truncation from 'double' to 'float', etc
# 4800 'int' forcing value to bool (performance warning)
ADD_DEFINITIONS(/wd4244 /wd4305 /wd4800)

VISIT_OPTION_DEFAULT(VISIT_INSTALL_THIRD_PARTY ON TYPE BOOL)

