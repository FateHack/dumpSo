#APP_ABI  := armeabi
#APP_ABI  := x86
#APP_ABI  := mips
#APP_ABI := mips armeabi armeabi-v7a x86
#APP_ABI := armeabi x86
APP_ABI  := armeabi-v7a

# use static stl port
APP_STL := stlport_static
APP_CPPFLAGS += -fno-exceptions 
APP_CPPFLAGS += -g0
APP_CPPFLAGS +=	-fno-rtti

