// =============================================================================
// HexPulse — HexMind AI Chat Module
// Cloud-based AI assistant for the HexPulse device
// Part of the HexMind AI Ecosystem by Arjun TM (@cyberkallan)
// =============================================================================
#ifndef __HEXMIND_CHAT_H__
#define __HEXMIND_CHAT_H__

#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>

// Supported AI providers
enum HexMindProvider {
    PROVIDER_GEMINI = 0,
    PROVIDER_OPENAI = 1,
    PROVIDER_CUSTOM = 2
};

// Chat message structure
struct ChatMessage {
    String role;    // "user" or "assistant"
    String content;
    unsigned long timestamp;
};

class HexMindChat {
public:
    HexMindChat();
    ~HexMindChat();

    // Configuration
    void setProvider(HexMindProvider provider);
    void setApiKey(const String &key);
    void setEndpoint(const String &url);
    void setModel(const String &model);
    void setSystemPrompt(const String &prompt);

    // Core chat
    String sendPrompt(const String &userInput);
    void streamToDisplay(const String &text);
    void clearHistory();

    // Diagnostic helpers
    String analyzeWifiScan(const String &scanData);
    String analyzeBLEScan(const String &scanData);
    String generateReport(const String &diagnosticData);

    // Config persistence
    void saveConfig();
    void loadConfig();

    // Status
    bool isConfigured() const { return _apiKey.length() > 0; }
    HexMindProvider getProvider() const { return _provider; }
    String getProviderName() const;
    int getHistorySize() const { return _history.size(); }

    // UI Entry point
    static void chatMenu();
    static void settingsMenu();
    static void diagnosticsMenu();

private:
    HexMindProvider _provider;
    String _apiKey;
    String _endpoint;
    String _model;
    String _systemPrompt;
    std::vector<ChatMessage> _history;
    static const int MAX_HISTORY = 5;

    // API helpers
    String _callGeminiAPI(const String &prompt);
    String _callOpenAIAPI(const String &prompt);
    String _callCustomAPI(const String &prompt);
    String _buildConversationContext();
    String _extractResponse(const String &json, HexMindProvider provider);

    // Display helpers
    void _displayTypingAnimation();
    void _displayResponse(const String &response);
    void _displayError(const String &error);
};

// Global instance
extern HexMindChat hexmindChat;

#endif // __HEXMIND_CHAT_H__
