# 🤟 Hand Gesture to Text & Speech Converter

An IoT-based assistive communication system that translates hand gestures into readable text and synthesized speech in real time. The system combines **flex sensors**, an **MPU6050 motion sensor**, an **ESP32**, **Firebase Realtime Database**, and a responsive web application to bridge the communication gap for individuals with speech and hearing impairments.

---

## 📖 Overview

This project aims to provide an intuitive and low-cost communication solution by recognizing predefined hand gestures and converting them into meaningful words or complete sentences.

The glove uses flex sensors to detect finger bending and an MPU6050 accelerometer/gyroscope to detect hand orientation. The ESP32 processes these inputs, recognizes the gesture, and uploads the corresponding word or sentence to Firebase. A web application continuously listens for updates, displays the recognized text, and converts it into speech using the browser's Speech Synthesis API.

---

## ✨ Features

- 🤟 Real-time hand gesture recognition
- 📖 Gesture-to-text conversion
- 🔊 Automatic text-to-speech conversion
- 🌐 Wireless communication using Wi-Fi
- ☁ Firebase Realtime Database integration
- 📱 Responsive web interface
- 🔄 Dynamic Wi-Fi configuration using WiFiManager
- 📜 Sentence formation support
- 🚀 Low latency communication
- 🔧 Modular and scalable architecture

---

# 🏗 System Architecture

```
                 Hand Gesture
                      │
        ┌─────────────┴─────────────┐
        │                           │
   Flex Sensors                  MPU6050
        │                           │
        └─────────────┬─────────────┘
                      │
                  ESP32 Controller
                      │
                 Wi-Fi Connection
                      │
              Firebase Realtime DB
                      │
               Web Application
               │             │
          Display Text   Text-to-Speech
```

---

# 🛠 Hardware Components

- ESP32 Development Board 
- Flex Sensors
- MPU6050 Accelerometer + Gyroscope 
- Breadboard
- Jumper Wires 
- USB Cable 

# 💻 Software Stack
- Arduino IDE
- ESP32 Board Package
- Firebase Realtime Database
- HTML5
- CSS3
- JavaScript
- Firebase SDK
- WiFiManager Library
- MPU6050 Library
- Web Speech API

---

# ⚙ Working Principle

1. User performs a predefined hand gesture.
2. Flex sensors detect finger bending.
3. MPU6050 detects hand orientation.
4. ESP32 processes sensor values.
5. Gesture is mapped to a predefined word.
6. Stable gesture detection prevents false recognition.
7. Words are accumulated to form complete sentences.
8. The **SEND** gesture transmits the sentence to Firebase.
9. Web application receives the update instantly.
10. Text is displayed and spoken aloud using Text-to-Speech.

# 💬 Sentence Formation

Instead of immediately transmitting every recognized word, the ESP32 stores recognized words in a sentence buffer.

Example:

```
I
↓

NEED
↓

WATER
↓

SEND
```

Output:

```
I NEED WATER
```

The sentence is uploaded only after the **SEND** gesture is detected.

This reduces accidental transmissions and provides a more natural communication experience.

---

# 📡 Firebase Integration

The ESP32 writes recognized sentences to

```
/gesture/word
```

The web application listens continuously for updates and immediately displays and speaks the received sentence.

---

# 🔊 Text-to-Speech

Speech generation is implemented using the browser's built-in Speech Synthesis API.

Features:

- No external API required
- Low latency
- Works directly in modern browsers
- Supports multiple voices

# 🚀 Getting Started

### Clone Repository

```bash
git clone https://github.com/AP2605/Hand-Gesture-To-Text-and-Speech-Converter.git
```

---

### Upload ESP32 Code

- Install ESP32 Board Package
- Install required libraries
- Configure Firebase credentials
- Upload the sketch

---

### Configure Firebase

Create a Firebase Realtime Database and update:

```
API_KEY
DATABASE_URL
```

inside the ESP32 sketch and the web application.

---

### Launch Web Application

Open

```
index.html
```

using Live Server or any local web server.

---

# 📷 Demonstration

Example:

```
Gesture
↓

HELLO

↓

ESP32

↓

Firebase

↓

Website

↓

🔊 "Hello"
```

---

# 🌟 Future Improvements

- Machine Learning based gesture recognition
- Dynamic gesture training
- Larger gesture vocabulary
- Mobile application
- Multi-language speech synthesis
- User-specific calibration
- Cloud analytics
- Gesture prediction
- AI-powered sentence completion

---

# 🎯 Applications

- Assistive communication
- Healthcare
- Smart homes
- Human Computer Interaction
- Education
- Rehabilitation
- IoT communication systems

---

# 📈 Future Scope

The current implementation uses predefined gestures mapped to fixed words.

Future versions can integrate machine learning models for personalized gesture recognition, allowing users to create custom gestures while significantly increasing vocabulary size and improving recognition accuracy.

---

# 👨‍💻 Author

**Ayush Pathak**

B.Tech Computer Science & Engineering

VIT Chennai
---

# ⭐ If you found this project useful
Please consider giving this repository a **⭐ Star**.
