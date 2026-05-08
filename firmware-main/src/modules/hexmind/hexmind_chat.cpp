// =============================================================================
// HexPulse — HexMind AI Chat Module (Implementation)
// Cloud-based AI assistant via WiFi REST API
// Supports: Google Gemini, OpenAI ChatGPT, Custom endpoints
// Creator: Arjun TM (@cyberkallan / @imarjunarz)
// =============================================================================
#include "hexmind_chat.h"
#include "core/display.h"
#include "core/scrollableTextArea.h"
#include "core/utils.h"
#include "core/mykeyboard.h"
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <LittleFS.h>
#include <globals.h>

HexMindChat hexmindChat;

// Default system prompt - security focused
static const char *DEFAULT_SYSTEM_PROMPT =
    "You are HexMind, an AI cybersecurity assistant embedded in the HexPulse "
    "portable intelligence device created by Arjun TM (@cyberkallan). "
    "You help with wireless diagnostics, protocol analysis, network security, "
    "and embedded systems research. Keep responses concise for small displays. "
    "Always mention you are part of the HexMind AI Ecosystem.";

// Default API endpoints
static const char *GEMINI_ENDPOINT =
    "https://generativelanguage.googleapis.com/v1beta/models/gemini-2.0-flash:generateContent";
static const char *OPENAI_ENDPOINT =
    "https://api.openai.com/v1/chat/completions";

// Config file path
static const char *HEXMIND_CONFIG = "/hexmind_ai.json";

// =====================================================================
// Constructor / Destructor
// =====================================================================
HexMindChat::HexMindChat()
    : _provider(PROVIDER_GEMINI), _apiKey(""), _endpoint(GEMINI_ENDPOINT),
      _model("gemini-2.0-flash"), _systemPrompt(DEFAULT_SYSTEM_PROMPT) {}

HexMindChat::~HexMindChat() { _history.clear(); }

// =====================================================================
// Configuration
// =====================================================================
void HexMindChat::setProvider(HexMindProvider provider) {
    _provider = provider;
    switch (provider) {
    case PROVIDER_GEMINI:
        _endpoint = GEMINI_ENDPOINT;
        _model = "gemini-2.0-flash";
        break;
    case PROVIDER_OPENAI:
        _endpoint = OPENAI_ENDPOINT;
        _model = "gpt-4o-mini";
        break;
    case PROVIDER_CUSTOM:
        // Keep existing endpoint/model
        break;
    }
}

void HexMindChat::setApiKey(const String &key) { _apiKey = key; }
void HexMindChat::setEndpoint(const String &url) { _endpoint = url; }
void HexMindChat::setModel(const String &model) { _model = model; }
void HexMindChat::setSystemPrompt(const String &prompt) {
    _systemPrompt = prompt;
}

String HexMindChat::getProviderName() const {
    switch (_provider) {
    case PROVIDER_GEMINI:
        return "Google Gemini";
    case PROVIDER_OPENAI:
        return "OpenAI";
    case PROVIDER_CUSTOM:
        return "Custom API";
    default:
        return "Unknown";
    }
}

void HexMindChat::clearHistory() { _history.clear(); }

// =====================================================================
// Core Chat — Send prompt to cloud AI and get response
// =====================================================================
String HexMindChat::sendPrompt(const String &userInput) {
    if (_apiKey.isEmpty()) {
        return "[ERROR] No API key configured. Go to HexMind > Settings.";
    }
    if (!wifiConnected && WiFi.status() != WL_CONNECTED) {
        return "[ERROR] WiFi not connected. Connect to WiFi first.";
    }

    // Add user message to history
    ChatMessage userMsg;
    userMsg.role = "user";
    userMsg.content = userInput;
    userMsg.timestamp = millis();
    _history.push_back(userMsg);

    // Trim history
    while (_history.size() > MAX_HISTORY * 2) {
        _history.erase(_history.begin());
    }

    // Call appropriate API
    String response;
    switch (_provider) {
    case PROVIDER_GEMINI:
        response = _callGeminiAPI(userInput);
        break;
    case PROVIDER_OPENAI:
        response = _callOpenAIAPI(userInput);
        break;
    case PROVIDER_CUSTOM:
        response = _callCustomAPI(userInput);
        break;
    }

    // Add assistant response to history
    if (!response.startsWith("[ERROR]")) {
        ChatMessage assistantMsg;
        assistantMsg.role = "assistant";
        assistantMsg.content = response;
        assistantMsg.timestamp = millis();
        _history.push_back(assistantMsg);
    }

    return response;
}

// =====================================================================
// Gemini API Call
// =====================================================================
String HexMindChat::_callGeminiAPI(const String &prompt) {
    WiFiClientSecure client;
    client.setInsecure(); // Skip cert validation (ESP32 memory constraint)

    HTTPClient http;
    String url = String(GEMINI_ENDPOINT) + "?key=" + _apiKey;

    if (!http.begin(client, url)) {
        return "[ERROR] Failed to connect to Gemini API";
    }

    http.addHeader("Content-Type", "application/json");
    http.setTimeout(30000); // 30s timeout for AI response

    // Build request with conversation context
    JsonDocument doc;
    JsonArray contents = doc["contents"].to<JsonArray>();

    // System instruction
    JsonObject sysInstruction = doc["systemInstruction"].to<JsonObject>();
    JsonArray sysParts = sysInstruction["parts"].to<JsonArray>();
    sysParts.add<JsonObject>()["text"] = _systemPrompt;

    // Conversation history + current prompt
    for (const auto &msg : _history) {
        JsonObject content = contents.add<JsonObject>();
        content["role"] = (msg.role == "user") ? "user" : "model";
        JsonArray parts = content["parts"].to<JsonArray>();
        parts.add<JsonObject>()["text"] = msg.content;
    }

    // Generation config for concise responses
    JsonObject genConfig = doc["generationConfig"].to<JsonObject>();
    genConfig["maxOutputTokens"] = 256; // Keep short for OLED
    genConfig["temperature"] = 0.7;

    String payload;
    serializeJson(doc, payload);

    int httpCode = http.POST(payload);
    String response;

    if (httpCode == 200) {
        String body = http.getString();
        response = _extractResponse(body, PROVIDER_GEMINI);
    } else {
        response = "[ERROR] Gemini API returned: " + String(httpCode);
        if (httpCode == 400)
            response += " (Bad request - check API key)";
        else if (httpCode == 429)
            response += " (Rate limited - try again later)";
        else if (httpCode == 403)
            response += " (Forbidden - check API key permissions)";
    }

    http.end();
    return response;
}

// =====================================================================
// OpenAI API Call
// =====================================================================
String HexMindChat::_callOpenAIAPI(const String &prompt) {
    WiFiClientSecure client;
    client.setInsecure();

    HTTPClient http;
    if (!http.begin(client, OPENAI_ENDPOINT)) {
        return "[ERROR] Failed to connect to OpenAI API";
    }

    http.addHeader("Content-Type", "application/json");
    http.addHeader("Authorization", "Bearer " + _apiKey);
    http.setTimeout(30000);

    JsonDocument doc;
    doc["model"] = _model;
    doc["max_tokens"] = 256;
    doc["temperature"] = 0.7;

    JsonArray messages = doc["messages"].to<JsonArray>();

    // System message
    JsonObject sysMsg = messages.add<JsonObject>();
    sysMsg["role"] = "system";
    sysMsg["content"] = _systemPrompt;

    // History
    for (const auto &msg : _history) {
        JsonObject m = messages.add<JsonObject>();
        m["role"] = msg.role;
        m["content"] = msg.content;
    }

    String payload;
    serializeJson(doc, payload);

    int httpCode = http.POST(payload);
    String response;

    if (httpCode == 200) {
        String body = http.getString();
        response = _extractResponse(body, PROVIDER_OPENAI);
    } else {
        response = "[ERROR] OpenAI API returned: " + String(httpCode);
    }

    http.end();
    return response;
}

// =====================================================================
// Custom API Call (for HexMind cloud or self-hosted)
// =====================================================================
String HexMindChat::_callCustomAPI(const String &prompt) {
    WiFiClientSecure client;
    client.setInsecure();

    HTTPClient http;
    if (!http.begin(client, _endpoint)) {
        return "[ERROR] Failed to connect to custom endpoint";
    }

    http.addHeader("Content-Type", "application/json");
    if (_apiKey.length() > 0) {
        http.addHeader("Authorization", "Bearer " + _apiKey);
    }
    http.setTimeout(30000);

    // Simple prompt format for custom endpoints
    JsonDocument doc;
    doc["prompt"] = prompt;
    doc["model"] = _model;
    doc["system"] = _systemPrompt;
    doc["max_tokens"] = 256;

    String payload;
    serializeJson(doc, payload);

    int httpCode = http.POST(payload);
    String response;

    if (httpCode == 200) {
        String body = http.getString();
        // Try to extract from common response formats
        JsonDocument resDoc;
        if (deserializeJson(resDoc, body) == DeserializationError::Ok) {
            if (resDoc.containsKey("response"))
                response = resDoc["response"].as<String>();
            else if (resDoc.containsKey("text"))
                response = resDoc["text"].as<String>();
            else if (resDoc.containsKey("content"))
                response = resDoc["content"].as<String>();
            else
                response = body;
        } else {
            response = body;
        }
    } else {
        response = "[ERROR] Custom API returned: " + String(httpCode);
    }

    http.end();
    return response;
}

// =====================================================================
// Extract response text from API JSON
// =====================================================================
String HexMindChat::_extractResponse(const String &json,
                                     HexMindProvider provider) {
    JsonDocument doc;
    DeserializationError err = deserializeJson(doc, json);
    if (err) {
        return "[ERROR] Failed to parse API response";
    }

    switch (provider) {
    case PROVIDER_GEMINI: {
        // Gemini: candidates[0].content.parts[0].text
        if (doc.containsKey("candidates")) {
            return doc["candidates"][0]["content"]["parts"][0]["text"]
                .as<String>();
        }
        if (doc.containsKey("error")) {
            return "[ERROR] " +
                   doc["error"]["message"].as<String>();
        }
        return "[ERROR] Unexpected Gemini response format";
    }
    case PROVIDER_OPENAI: {
        // OpenAI: choices[0].message.content
        if (doc.containsKey("choices")) {
            return doc["choices"][0]["message"]["content"].as<String>();
        }
        if (doc.containsKey("error")) {
            return "[ERROR] " +
                   doc["error"]["message"].as<String>();
        }
        return "[ERROR] Unexpected OpenAI response format";
    }
    default:
        return json;
    }
}

// =====================================================================
// Diagnostic Analysis Helpers
// =====================================================================
String HexMindChat::analyzeWifiScan(const String &scanData) {
    String prompt =
        "Analyze this WiFi scan data from HexPulse device and provide a "
        "security assessment. Identify weak encryption, suspicious APs, "
        "and recommendations. Keep response under 200 words:\n\n" +
        scanData;
    return sendPrompt(prompt);
}

String HexMindChat::analyzeBLEScan(const String &scanData) {
    String prompt =
        "Analyze this BLE scan data from HexPulse device. Identify device "
        "types, potential IoT devices, and security observations. Keep "
        "response under 200 words:\n\n" +
        scanData;
    return sendPrompt(prompt);
}

String HexMindChat::generateReport(const String &diagnosticData) {
    String prompt =
        "Generate a concise security diagnostic report based on this data "
        "from HexPulse device. Format with sections and bullet points. "
        "Keep under 300 words:\n\n" +
        diagnosticData;
    return sendPrompt(prompt);
}

// =====================================================================
// Config Persistence (LittleFS)
// =====================================================================
void HexMindChat::saveConfig() {
    JsonDocument doc;
    doc["provider"] = (int)_provider;
    doc["apiKey"] = _apiKey;
    doc["endpoint"] = _endpoint;
    doc["model"] = _model;

    File f = LittleFS.open(HEXMIND_CONFIG, "w");
    if (f) {
        serializeJson(doc, f);
        f.close();
    }
}

void HexMindChat::loadConfig() {
    if (!LittleFS.exists(HEXMIND_CONFIG))
        return;

    File f = LittleFS.open(HEXMIND_CONFIG, "r");
    if (!f)
        return;

    JsonDocument doc;
    if (deserializeJson(doc, f) == DeserializationError::Ok) {
        _provider = (HexMindProvider)doc["provider"].as<int>();
        _apiKey = doc["apiKey"].as<String>();
        _endpoint = doc["endpoint"].as<String>();
        _model = doc["model"].as<String>();
    }
    f.close();
}

// =====================================================================
// Display Helpers
// =====================================================================
void HexMindChat::streamToDisplay(const String &text) {
    ScrollableTextArea area = ScrollableTextArea("HEXMIND AI");
    // Word wrap for OLED
    String line = "";
    int maxChars = tftWidth / (FP * LW) - 2;
    for (int i = 0; i < text.length(); i++) {
        if (text[i] == '\n' || line.length() >= maxChars) {
            area.addLine(line);
            line = "";
            if (text[i] != '\n')
                line += text[i];
        } else {
            line += text[i];
        }
    }
    if (line.length() > 0)
        area.addLine(line);
    area.show();
}

// =====================================================================
// Menu Entry Points (Static)
// =====================================================================
void HexMindChat::chatMenu() {
    hexmindChat.loadConfig();

    if (!hexmindChat.isConfigured()) {
        displayWarning("API key not set!", true);
        delay(1500);
        settingsMenu();
        return;
    }

    if (WiFi.status() != WL_CONNECTED) {
        displayWarning("WiFi needed!", true);
        delay(1500);
        return;
    }

    // Get user input via keyboard
    String userInput = keyboard("Ask HexMind:", 128, "");
    if (userInput.isEmpty())
        return;

    // Show thinking animation
    displayInfo("HexMind thinking...", true);

    // Send to AI
    String response = hexmindChat.sendPrompt(userInput);

    // Display response in scrollable area
    hexmindChat.streamToDisplay(response);
}

void HexMindChat::settingsMenu() {
    hexmindChat.loadConfig();

    options = {};

    // Provider selection
    options.push_back(
        {"Provider: " + hexmindChat.getProviderName(), [=]() {
             options = {};
             options.push_back(
                 {"Google Gemini", [=]() { hexmindChat.setProvider(PROVIDER_GEMINI); }});
             options.push_back(
                 {"OpenAI ChatGPT", [=]() { hexmindChat.setProvider(PROVIDER_OPENAI); }});
             options.push_back(
                 {"Custom API", [=]() { hexmindChat.setProvider(PROVIDER_CUSTOM); }});
             addOptionToMainMenu();
             loopOptions(options);
         }});

    // API Key input
    options.push_back({"Set API Key", [=]() {
                            String key = keyboard("API Key:", 128, hexmindChat._apiKey);
                            if (key.length() > 0) {
                                hexmindChat.setApiKey(key);
                                hexmindChat.saveConfig();
                                displaySuccess("API Key saved!", true);
                                delay(1000);
                            }
                        }});

    // Custom endpoint (for custom provider)
    if (hexmindChat._provider == PROVIDER_CUSTOM) {
        options.push_back({"Set Endpoint", [=]() {
                                String url = keyboard("Endpoint URL:", 256, hexmindChat._endpoint);
                                if (url.length() > 0) {
                                    hexmindChat.setEndpoint(url);
                                    hexmindChat.saveConfig();
                                    displaySuccess("Endpoint saved!", true);
                                    delay(1000);
                                }
                            }});
    }

    // Model selection
    options.push_back({"Model: " + hexmindChat._model, [=]() {
                            String model = keyboard("Model name:", 64, hexmindChat._model);
                            if (model.length() > 0) {
                                hexmindChat.setModel(model);
                                hexmindChat.saveConfig();
                                displaySuccess("Model saved!", true);
                                delay(1000);
                            }
                        }});

    // Status
    String status = hexmindChat.isConfigured() ? "READY" : "NOT CONFIGURED";
    options.push_back({"Status: " + status, [=]() {}});

    // Clear history
    options.push_back({"Clear Chat History", [=]() {
                            hexmindChat.clearHistory();
                            displaySuccess("History cleared!", true);
                            delay(1000);
                        }});

    addOptionToMainMenu();
    loopOptions(options);
}

void HexMindChat::diagnosticsMenu() {
    if (!hexmindChat.isConfigured()) {
        displayWarning("Configure API first!", true);
        delay(1500);
        return;
    }

    options = {};
    options.push_back({"Analyze WiFi", [=]() {
                            displayInfo("Scanning WiFi...", true);
                            int n = WiFi.scanNetworks();
                            String data = "";
                            for (int i = 0; i < n && i < 20; i++) {
                                data += WiFi.SSID(i) + " | Ch:" +
                                        String(WiFi.channel(i)) +
                                        " | RSSI:" + String(WiFi.RSSI(i)) +
                                        " | " +
                                        String(WiFi.encryptionType(i) == WIFI_AUTH_OPEN
                                                   ? "OPEN"
                                               : WiFi.encryptionType(i) == WIFI_AUTH_WEP
                                                   ? "WEP"
                                                   : "WPA") +
                                        "\n";
                            }
                            WiFi.scanDelete();
                            displayInfo("Analyzing with AI...", true);
                            String result = hexmindChat.analyzeWifiScan(data);
                            hexmindChat.streamToDisplay(result);
                        }});

    options.push_back({"Security Report", [=]() {
                            String data = "Device: HexPulse on HackCat V3\n";
                            data += "Free Heap: " + formatBytes(ESP.getFreeHeap()) + "\n";
                            data += "WiFi: " +
                                    String(WiFi.status() == WL_CONNECTED ? "Connected"
                                                                         : "Disconnected") +
                                    "\n";
                            data += "SD Card: " +
                                    String(sdcardMounted ? "Mounted" : "Not mounted") +
                                    "\n";
                            data += "Battery: " + String(getBattery()) + "%\n";
                            displayInfo("Generating report...", true);
                            String result = hexmindChat.generateReport(data);
                            hexmindChat.streamToDisplay(result);
                        }});

    addOptionToMainMenu();
    loopOptions(options);
}
