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

bool containsMP4File(const std::string& filePath) {
    std::regex pattern(R"(\.mp4$)");
    return std::regex_search(filePath, pattern);
}

int main(int argc, char *argv[])
{
  if (argc != 4)
  {
    g_error("Not enough arguments\n!");
  }

  std::string host(argv[1]);
  std::string port(argv[2]);
  std::string filePath(argv[3]);

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

  if(!containsMP4File(filePath))
  {
    g_printerr("Invalid file or filepath: The file must be in mp4 format");
    return -1;
  }


  std::string factoryStr = "filesrc location=" + filePath + " ! qtdemux ! queue ! h264parse ! rtph264pay config-interval=1 name=pay0 pt=96";

  GstRTSPServer *server;
  GMainLoop *loop;
  GstRTSPMediaFactory *factory;
  GstRTSPMountPoints *mounts;

  gst_init(&argc, &argv);

  server = gst_rtsp_server_new();
  loop = g_main_loop_new(NULL, FALSE);
  factory = gst_rtsp_media_factory_new();
  mounts = gst_rtsp_server_get_mount_points(server);

  gst_rtsp_server_set_address(server, argv[1]);
  gst_rtsp_server_set_service(server, argv[2]);
  gst_rtsp_mount_points_add_factory(mounts, "/test", factory);
  gst_rtsp_media_factory_set_launch(factory, (factoryStr.c_str()));
  g_object_unref(mounts);

  gst_rtsp_server_attach(server, NULL);

  g_print("A szerver fut!\n");
  g_main_loop_run(loop);
}