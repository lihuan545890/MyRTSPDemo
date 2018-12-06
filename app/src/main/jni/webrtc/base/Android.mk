LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := librtc_base_approved
LOCAL_CFLAGS += -DWEBRTC_POSIX
LOCAL_C_INCLUDES := $(JNI_PATH)/webrtc
#$(warning $(LOCAL_C_INCLUDES))

LOCAL_SRC_FILES := checks.cc exp_filter.cc md5.cc platform_file.cc stringencode.cc stringutils.cc timeutils.cc
include $(BUILD_STATIC_LIBRARY) 

include $(CLEAR_VARS)
LOCAL_MODULE    := libwebrtc_base
LOCAL_CPPFLAGS += -DWEBRTC_POSIX -DWEBRTC_LINUX -DWEBRTC_ANDROID  -DHAVE_OPENSSL_SSL_H

LOCAL_C_INCLUDES := $(JNI_PATH)/webrtc \
					$(JNI_PATH)/webrtc/webrtc/third_party/openssl/include


LOCAL_SRC_FILES :=  asyncfile.cc \
					asynchttprequest.cc \
					asyncinvoker.cc \
					asyncsocket.cc \
					asynctcpsocket.cc \
					asyncudpsocket.cc \
					autodetectproxy.cc \
					bandwidthsmoother.cc \
                    base64.cc  \
					bytebuffer.cc \
					common.cc \
					cpumonitor.cc \
					crc32.cc \
					dbus.cc \
					diskcache.cc \
					event.cc \
					filelock.cc \
					fileutils.cc \
					firewallsocketserver.cc \
					flags.cc \
					helpers.cc \
					httpbase.cc \
					httpclient.cc \
					httpcommon.cc \
					httprequest.cc \
					httpserver.cc \
					ifaddrs-android.cc \
					ipaddress.cc \
					latebindingsymboltable.cc \
					libdbusglibsymboltable.cc \
					linux.cc \
					linuxfdwalk.c \
					logging.cc \
					messagedigest.cc \
					messagehandler.cc \
					messagequeue.cc \
					multipart.cc \
					natserver.cc \
					natsocketfactory.cc \
					nattypes.cc \
					nethelpers.cc \
					network.cc \
					optionsfile.cc \
					openssladapter.cc \
					openssldigest.cc \
					opensslidentity.cc \
					opensslstreamadapter.cc \
					pathutils.cc \
					physicalsocketserver.cc \
					posix.cc \
					profiler.cc \
					proxydetect.cc \
					proxyinfo.cc \
					proxyserver.cc \
					ratelimiter.cc \
					ratetracker.cc  \
					sha1.cc \
					sharedexclusivelock.cc \
					signalthread.cc \
					socketadapters.cc \
					socketaddress.cc \
					socketaddresspair.cc \
					socketpool.cc \
					socketstream.cc \
					ssladapter.cc \
					sslfingerprint.cc \
					sslidentity.cc \
					sslsocketfactory.cc \
					sslstreamadapter.cc \
					sslstreamadapterhelper.cc \
					stream.cc \
					systeminfo.cc \
					task.cc \
					taskparent.cc \
					taskrunner.cc \
					testclient.cc \
					thread.cc \
					thread_checker_impl.cc \
					timing.cc \
					transformadapter.cc \
					unixfilesystem.cc \
					urlencode.cc \
					versionparsing.cc \
					virtualsocketserver.cc \
					worker.cc
					
					
include $(BUILD_STATIC_LIBRARY)