
// This helper file includes either 2.4 or 2.5/2.6 version, to workaround
// an automake limitation:

#ifdef BUILD_24
    #include "mozilla/mozilla_wrap.cpp"
#else
    #include "mozilla25/gtk/mozilla_wrap.cpp"
#endif
