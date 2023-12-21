#include <gst/gst.h>
#include <gst/rtsp-server/rtsp-server.h>
#include <iostream>
#include <string>
#include <regex>

bool isValidIPv4(const std::string& str) {
    std::regex pattern("^((25[0-5]|2[0-4][0-9]|[0-1]?[0-9][0-9]?)\\.){3}(25[0-5]|2[0-4][0-9]|[0-1]?[0-9][0-9]?)$");
    return std::regex_match(str, pattern);
}

bool isValidPortNumber(const std::string& str) {
    std::regex pattern("^5000$|^([5-5][0-9]{3})$|^6000$");
    return std::regex_match(str, pattern);
}


int main(int argc, char *argv[])
{
  if (argc != 4)
  {
    g_error("Not enough arguments\n!");
  }
  
  std::string srcPort(argv[1]);
  std::string host(argv[2]);
  std::string port(argv[3]);

  if(!isValidPortNumber(srcPort))
  {
    g_printerr("Invalid port number: Valid Range (5000 - 6000)!\n");
    return -1;
  }

  if(!isValidIPv4(host))
  {
    g_printerr("Invalid host address format!\n");
    return -1;
  }

  if(!isValidPortNumber(port))
  {
    g_printerr("Invalid port number: Valid Range (5000 - 6000)!\n");
    return -1;
  }

  std::string factoryStr = "udpsrc port=5600 caps=\"application/x-rtp,media=(string)video,encoding-name=(string)H264,clock-rate=(int)90000\" ! queue ! rtph264depay ! rtph264pay name=pay0 pt=96";

  GstRTSPServer *server;
  GMainLoop *loop;
  GstRTSPMediaFactory *factory;
  GstRTSPMountPoints *mounts;

  gst_init(&argc, &argv);

  server = gst_rtsp_server_new();
  loop = g_main_loop_new(NULL, FALSE);
  factory = gst_rtsp_media_factory_new();
  mounts = gst_rtsp_server_get_mount_points(server);

  gst_rtsp_server_set_address(server, argv[2]);
  gst_rtsp_server_set_service(server, argv[3]);
  gst_rtsp_mount_points_add_factory(mounts, "/stream", factory);
  gst_rtsp_media_factory_set_launch(factory, (factoryStr.c_str()));
  g_object_unref(mounts);

  gst_rtsp_server_attach(server, NULL);

  g_print("Stream fut!\n");
  g_main_loop_run(loop);
}