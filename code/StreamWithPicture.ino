#include <WebServer.h>
#include <WiFi.h>
#include <esp32cam.h>

const char* WIFI_SSID = "‎";  // Change this to your WiFi SSID
const char* WIFI_PASS = "12345678";  // Change this to your WiFi password

WebServer server(80);

static auto hiRes = esp32cam::Resolution::find(800, 600);
static auto loRes = esp32cam::Resolution::find(320, 240);

// Function to serve a single JPEG image
void serveJpg() {
    auto frame = esp32cam::capture();
    if (frame == nullptr) {
        Serial.println("❌ CAPTURE FAIL");
        server.send(503, "", "");
        return;
    }
    Serial.printf("✅ CAPTURE OK: %dx%d %d bytes\n", frame->getWidth(), frame->getHeight(), static_cast<int>(frame->size()));

    server.setContentLength(frame->size());
    server.send(200, "image/jpeg");
    WiFiClient client = server.client();
    frame->writeTo(client);
}

// Function to handle MJPEG streaming
void handleStream() {
    WiFiClient client = server.client();
    String header = "HTTP/1.1 200 OK\r\n"
                    "Content-Type: multipart/x-mixed-replace; boundary=frame\r\n\r\n";
    client.write(header.c_str(), header.length());

    while (client.connected()) {
        auto frame = esp32cam::capture();
        if (frame == nullptr) {
            Serial.println("❌ Frame Capture Failed");
            continue;
        }

        String frameHeader = "--frame\r\n"
                             "Content-Type: image/jpeg\r\n"
                             "Content-Length: " +
                             String(frame->size()) + "\r\n\r\n";

        client.write(frameHeader.c_str(), frameHeader.length());
        frame->writeTo(client);
        client.write("\r\n");
        delay(50);  // Adjust delay to control frame rate
    }
}

// Function to handle a single image capture (low resolution)
void handleJpgLo() {
    if (!esp32cam::Camera.changeResolution(loRes)) {
        Serial.println("❌ SET-LO-RES FAIL");
    }
    serveJpg();
}

void setup() {
    Serial.begin(115200);
    Serial.println();

    using namespace esp32cam;
    Config cfg;
    cfg.setPins(pins::AiThinker);
    cfg.setResolution(hiRes);
    cfg.setBufferCount(2);
    cfg.setJpeg(80);

    bool ok = Camera.begin(cfg);
    Serial.println(ok ? "✅ CAMERA OK" : "❌ CAMERA FAIL");

    WiFi.persistent(false);
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }

    Serial.print("📡 Stream available at: http://");
    Serial.println(WiFi.localIP());
    Serial.println("  /stream  (Live Video)");
    Serial.println("  /cam-lo.jpg  (Single Image)");

    server.on("/stream", handleStream);  // Live MJPEG stream
    server.on("/cam-lo.jpg", handleJpgLo);  // Single low-resolution image
    server.begin();
}

void loop() {
    server.handleClient();
}

