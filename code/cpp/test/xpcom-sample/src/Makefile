CXX   = c++
CPPFLAGS +=     -fno-rtti              \
		-fno-exceptions        \
		-shared  
 
# Change this to point at your Gecko SDK directory. 
GECKO_SDK_PATH = /home/ml/code/crawler/code/cpp/3rdparty/xulrunner-3.6.10/linux_64_release
 
# GCC only define which allows us to not have to #include mozilla-config 
# in every .cpp file.  If your not using GCC remove this line and add 
# #include "mozilla-config.h" to each of your .cpp files. 
#GECKO_CONFIG_INCLUDE = -include mozilla-config.h 
 
GECKO_DEFINES  = -DXPCOM_GLUE
 
GECKO_INCLUDES = -I $(GECKO_SDK_PATH)/include 
 
GECKO_LDFLAGS =  -L $(GECKO_SDK_PATH)/sdk/lib -lxpcomglue \
                 -lnspr4      \
                 -lplds4      

FILES = MyComponent.cpp MyComponentModule.cpp 

TARGET = MyComponent.so

build: 
	$(CXX) -Wall -Os -o $(TARGET) $(GECKO_CONFIG_INCLUDE) $(GECKO_DEFINES) $(GECKO_INCLUDES) $(GECKO_LDFLAGS) $(CPPFLAGS) $(CXXFLAGS) $(FILES)
	chmod +x $(TARGET)
	strip $(TARGET)
 
clean: 
	rm $(TARGET)
