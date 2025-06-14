# ESP32-CAM Based Smart Lock System 🔐📸

An IoT-based smart door locking system that uses the ESP32-CAM to stream live video, capture images, and simulate a facial recognition-based unlocking mechanism.

> ⚠️ This is a half-functional prototype. Due to a hardware mismatch (wrong ESP32 module), face recognition could not be implemented on-device. However, the streaming, capture, SD card logging, and lock mechanism were successfully tested.

---

## 📷 What It Does

- Captures live video from the ESP32-CAM module.
- Takes still images on command.
- *Planned*: Saves images to an SD card.
- *Planned*: Controls a relay and servo motor to simulate door unlocking.
- *Planned*: On-device face recognition with access control.

---

## 🛠️ Hardware Used

- ESP32-CAM (Ai Thinker module, not sure)
- Servo Motor (SG90)
- Relay Module (5V)
- SD Card Module (SPI mode)
- Breadboard + Jumper Wires
- 5V Power Supply

---

## 🔌 Pin Connections (ESP32-CAM)

| Component   | Pin Connection  |
|-------------|-----------------|
| Servo       | GPIO13          |
| Relay       | GPIO12          |
| SD Card CS  | GPIO5           |
| SD Card MISO| GPIO2           |
| SD Card MOSI| GPIO15          |
| SD Card SCK | GPIO14          |

---

## 🧪 What Worked

- ✅ Live video stream from ESP32-CAM via browser.
- ✅ Capturing a stil image from stream.
 
## ❌ What Didn't Work

- ❌ Face recognition (due to incorrect ESP32 module without proper PSRAM support).
- ❌ On-device facial match and access logic.
- ❌ Servo and relay control.
- ❌ Capturing and storing images to SD card.


---

## 📁 Project Structure

- `code/` – Arduino sketches for streaming, locking, and SD card logging.
- `images/` – Add your real-life images here.
- `report/` – Final project report PDF.
- `notes/` – Known issues, debug logs, and what we learned.

---

## 📖 How to Use

---

## 💬 What We Learned

Even with partial success, this project taught us:
- How to work with ESP32-CAM hardware.
- Basics of IoT hardware interaction (camera, servo, relay).
- Debugging hardware-level issues.
- Importance of checking specs before building 😅.

---

## 👥 Authors

- **Aditya Chavan** – Project Lead, Programming, Documentation  
- **Vrundarank Parite** – Hardware Assembly, Testing, Co-Development  
- [@Aditya-Chavan](https://github.com/aditya8242)
- [@Vrundarank](https://github.com/Vrundarank)

---

## 📄 Report

See the full report in `/report/Final_Report.pdf`.

---

## ✅ Future Improvements

- Use correct ESP32-CAM board with PSRAM.
- Integrate OpenCV-based face matching via external processor (e.g., Raspberry Pi).
- Cloud-based image logging.
- Add Telegram/Email alerts on failed recognition attempts.

---

Thanks for checking out our project!

---
