
# 📸 Real-Time Edge Detection App (Android + JNI + OpenCV)

An Android app that captures live camera frames, sends them to C++ native code using JNI, and applies real-time **Canny edge detection** using OpenCV. The result is displayed as a grayscale edge-detected image on the screen.

---

## 🚀 Features

- 📷 Live camera preview using `TextureView`
- 🧠 Canny edge detection in real-time with OpenCV (in C++)
- 🔁 Frame-by-frame processing via JNI
- 📤 Native-C++ integration with Android NDK
- 🖼️ Processed frames displayed using `ImageView`

---

## 🛠️ Requirements

- Android Studio (Flamingo or newer)
- Android SDK 24+
- NDK (Native Development Kit)
- CMake 3.22+
- OpenCV Android SDK (pre-installed or bundled)
- A physical Android device or emulator

---

## 📂 Project Structure

```
RealTimeEdgeDetection/
├── app/
│   ├── src/
│   │   ├── main/
│   │   │   ├── java/com/examplefourthjuly/realtimeedgedetection/
│   │   │   │   ├── MainActivity.java
│   │   │   │   └── NativeProcessor.java
│   │   │   ├── cpp/
│   │   │   │   └── native-lib.cpp
│   │   │   ├── res/layout/
│   │   │   │   └── activity_main.xml
│   │   │   └── AndroidManifest.xml
├── CMakeLists.txt
└── README.md
```

---

## 🔧 Configuration

### `build.gradle` (app)

```groovy
android {
    ...
    defaultConfig {
        ...
        externalNativeBuild {
            cmake {
                cppFlags += ""
            }
        }
        ndk {
            abiFilters 'armeabi-v7a', 'arm64-v8a'
        }
    }

    externalNativeBuild {
        cmake {
            path "src/main/cpp/CMakeLists.txt"
        }
    }
}
```

### `CMakeLists.txt`

```cmake
cmake_minimum_required(VERSION 3.4.1)

add_library(native-lib SHARED native-lib.cpp)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

target_link_libraries(
    native-lib
    ${OpenCV_LIBS}
    log
    android
)
```

---

## 🧠 Native C++ Code (Canny Detection)

```cpp
extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_examplefourthjuly_realtimeedgedetection_NativeProcessor_processFrame(
    JNIEnv* env, jobject, jintArray pixels_, jint width, jint height) {

    jint* pixels = env->GetIntArrayElements(pixels_, nullptr);
    Mat rgba(height, width, CV_8UC4, pixels);
    Mat bgr;
    cvtColor(rgba, bgr, COLOR_RGBA2BGR);
    env->ReleaseIntArrayElements(pixels_, pixels, 0);

    Mat gray;
    cvtColor(bgr, gray, COLOR_BGR2GRAY);

    Mat edges;
    Canny(gray, edges, 100, 200);

    jbyteArray result = env->NewByteArray(edges.total());
    env->SetByteArrayRegion(result, 0, edges.total(), reinterpret_cast<jbyte*>(edges.data));
    return result;
}
```

---

## 🖼️ Layout (`activity_main.xml`)

```xml
<RelativeLayout ...>
    <TextureView
        android:id="@+id/textureView"
        android:layout_width="match_parent"
        android:layout_height="match_parent" />

    <ImageView
        android:id="@+id/edgeView"
        android:layout_width="match_parent"
        android:layout_height="match_parent"
        android:scaleType="fitXY" />
</RelativeLayout>
```

---

## 📸 How It Works

1. Camera preview is shown using `TextureView`.
2. Each frame update triggers `onSurfaceTextureUpdated()`.
3. The frame is sent to native C++ code via JNI.
4. OpenCV processes the frame and applies Canny edge detection.
5. Resulting byte array is converted back to a Bitmap.
6. The `ImageView` displays the edge-detected result.

---

## 🐞 Common Issues

- **`Cannot resolve symbol 'R'`** – Clean and rebuild the project (`Build > Clean Project`).
- **`UnsatisfiedLinkError`** – Check `System.loadLibrary("native-lib")` and ensure `.so` is built.
- **Edge image too small or blank** – Adjust Canny thresholds or make sure you're sending the correct pixel format.

---

## 📦 License

This project is open source and available for educational use.

---

## ✨ Credits

Created by Renu Ekka  
Uses [OpenCV](https://opencv.org/) for image processing.
