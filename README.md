# Note

```
gst-launch-1.0 uridecodebin source::latency=200 source::protocols=4 uri=rtsp://admin:meditech123@192.168.100.90:554 ! nvvidconv ! videorate ! 'video/x-raw(memory:NVMM),format=NV12,width=1280,height=720,framerate=(fraction)30/1' ! nvv4l2h264enc insert-sps-pps=1 EnableTwopassCBR=1 control-rate=0 bitrate=2000000 vbv-size=125000 ratecontrol-enable=0 ! rtph264pay config-interval=1 pt=96 ! udpsink port=5002 host=127.0.0.1 sync=0

gst-launch-1.0 \
    udpsrc port=5002 caps="application/x-rtp, media=(string)video, clock-rate=(int)90000, encoding-name=(string)H264, payload=(int)96" ! queue ! \
    rtph264depay ! nvv4l2decoder ! nvvidconv ! xvimagesink sync=false async=true


gst-launch-1.0 uridecodebin source::latency=200 source::protocols=4 uri=rtsp://admin:meditech123@192.168.100.90:554/ ! \
    nvvidconv ! videorate ! \
    'video/x-raw, format=(string)I420,  width=(int)1280, height=(int)720, framerate=(fraction)30/1' ! \
    queue !  identity ! \
    shmsink wait-for-connection=0 socket-path=/tmp/tmpsock sync=true


gst-launch-1.0 shmsrc socket-path=/tmp/tmpsock do-timestamp=true is-live=true ! \
    video/x-raw, format=I420,  width=1280, height=720, framerate=30/1 ! \
    xvimagesink sync=false async=true
```