#RTSP stream to HLS

 - ```gst-launch-1.0 rtspsrc location="rtsp://....." ! rtph264depay ! h264parse ! hlssink2 max-file=5```
 