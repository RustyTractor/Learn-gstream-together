# Rövid ismertető

 A lényege, hogy könnyen és gyorsan megoszthatunk RTSP streameket-

## Szükséges lépések a fordítás és futtatás előtt

 1. Gstreamre telepítése: https://gstreamer.freedesktop.org/documentation/installing/on-linux.html?gi-language=c

 2. Gstreamer RSTP server könyvtár telepítése:

    ```sudo apt-get install libgstrtspserver-1.0 gstreamer1.0-rtsp```

 3. Fejlesztői eszközök telepítése:
    
    ```sudo apt-get install git build-essential autoconf automake autopoint libtool pkg-config -y```

    ```sudo apt-get install gtk-doc-tools libglib2.0-dev libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev -y```

    ```sudo apt-get install checkinstall```

## Fordítás
    
```gcc rtsp-server-tutorial.c -o rtsps $(pkg-config --cflags --libs gstreamer-rtsp-server-1.0 gstreamer-1.0)```

## Futtatás

    A sikeres futtatáshoz három bemeneti praméterre lesz szükség, mégpedig a kívánt host, portsztámot és a megosztani kíván videó útvonalát kell megadni

   ```./rtsps 192.168.0.xxx 5600 /home/../../sample.mp4```
