package com.examplefourthjuly.realtimeedgedetection;

public class NativeProcessor {

        static {
            System.loadLibrary("native-lib");
        }

    public static native byte[] processFrame(int[] pixels, int width, int height);
}


