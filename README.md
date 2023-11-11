# Learn-gstream-together
Mindenféle finomság, ami Gstream-el kapcsolatos

## TODO
### [GStream alapok elsajátítása](https://gstreamer.freedesktop.org/documentation/tutorials/basic/hello-world.html?gi-language=c)
 - [x] Hello World!
 - [x] GStreamer concepts
 - [ ] Dynamic pipelines
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
