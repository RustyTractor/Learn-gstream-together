# Learn-gstream-together
Mindenféle finomság, ami Gstream-el kapcsolatos

## TODO
### [GStream alapok elsajátítása](https://gstreamer.freedesktop.org/documentation/tutorials/basic/hello-world.html?gi-language=c)
 - [x] Hello World!
 - [x] GStreamer concepts
 - [x] Dynamic pipelines
 - [ ] Time management
 - [ ] GUI toolkit integration
 - [ ] Media formats and Pad Capabilities
 - [ ] Multithreading and Pad Availability

## Hasznos linkek
 - [Stream video using Gstream server](https://pmungekar7.medium.com/stream-video-using-gstreamer-rtsp-server-ca498f4a54bd)
 - [GStream server](https://github.com/GStreamer/gst-rtsp-server)


## Gstream pipe a consoleból
### Egyszerű stream playbin-el: gst-launch-1.0 playbin uri=https://gstreamer.freedesktop.org/data/media/sintel_trailer-480p.webm

### RTSP bridge: gst-launch-1.0 rtspsrc location=rtsp://your_source_url ! rtph264depay ! h264parse ! avdec_h264 ! autovideosink
 - rtspsrc: Stream forrása
 - rtph264depay: Depays H.264 encoded payload.
 - h264parse: Parses the H.264 stream.
 - avdec_h264: Decodes the H.264 stream.
 - autovideosink: Automatically selects an appropriate video sink for displaying.


## Hasznons Pipeline-ok

### Webcamera video streamelése

 Amire szükség lesz az a v4l-utils nevezetű csomag:

 ```sudo apt install v4l-utils```

 Segítéségvel listázhatod az eszközön található "videó forrásokat":

 ```v4l2-ctl --list-devices```

 A parancs álatal listázott eszközök közül egyet behelyettesíthetsz a pipeline-ba

### Pipeline a kamera videó küldéséhez:

```gst-launch-1.0 v4l2src device=/dev/video0 ! videoconvert ! x264enc ! rtph264pay ! udpsink host=xxx.xxx.xxx.xxx port=xxxx```

### Pipeline a teszt videó küldéséhez:

```gst-launch-1.0 -v videotestsrc ! videoconvert ! x264enc ! rtph264pay ! udpsink host=127.0.0.1 port=5700```

### Pipeline videó fogadásához:

 ```gst-launch-1.0  udpsrc port=5600 caps = "application/x-rtp, media=(string)video, clock-rate=(int)90000, encoding-name=(string)H264, payload=(int)96" ! rtpjitterbuffer ! rtph264depay ! decodebin ! videoconvert ! autovideosink```

### RTSP Stream Forwardolása

 https://stackoverflow.com/questions/14430104/how-to-   forward-rtp-stream-with-gstreamer

 ```gst-launch-1.0 -v rtspsrc location=rtsp://192.168.0.94:5600/test ! udpsink host=127.0.0.1 port=5700```

### RTSP Stream lejátszása

 ```gst-launch-1.0 rtspsrc location=rtsp://127.0.0.1:5600/test latency=100 ! queue ! rtph264depay ! h264parse ! avdec_h264 ! videoconvert ! videoscale ! video/x-raw,width=640,height=480 ! autovideosink```

### Videó hosztolás UDP portra

```gst-launch-1.0 filesrc location=/sajat/fajl/utvonala.mp4 ! qtdemux ! video/x-h264 ! rtph264pay config-interval=1 ! udpsink host=192.168.0.xxx port=xxx```

### Videó forwardolása UDP portól-portra

```gst-launch-1.0  udpsrc port=xxxx ! udpsrc host=192.168.0.xxx port=xxxx```

### Videó fogadása és lejátszása UDP portról

```gst-launch-1.0  udpsrc port=5600 caps = "application/x-rtp, media=(string)video, clock-rate=(int)90000, encoding-name=(string)H264, payload=(int)96" ! rtpjitterbuffer ! rtph264depay ! decodebin ! videoconvert ! autovideosink```




  
