FROM ubuntu:22.04
RUN apt-get update \
 && apt-get install git build-essential pkg-config -y \
 && apt-get install libgstreamer1.0-dev -y \
 && apt-get install libgstrtspserver-1.0 gstreamer1.0-rtsp -y
COPY rtsp-server.cpp .
COPY run-rtsp-server.sh .
WORKDIR /
RUN g++ rtsp-server.cpp -o rtsp-server $(pkg-config --cflags --libs gstreamer-rtsp-server-1.0 gstreamer-1.0)
CMD ["/bin/sh", "/run-rtsp-server.sh"]