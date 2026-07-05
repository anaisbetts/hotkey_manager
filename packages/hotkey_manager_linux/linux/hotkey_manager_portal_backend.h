#ifndef FLUTTER_PLUGIN_HOTKEY_MANAGER_PORTAL_BACKEND_H_
#define FLUTTER_PLUGIN_HOTKEY_MANAGER_PORTAL_BACKEND_H_

#include <flutter_linux/flutter_linux.h>
#include <gio/gio.h>

#include <map>
#include <string>
#include <vector>

#include "hotkey_manager_linux_backend.h"

struct PortalHotkey {
  guint key_code;
  std::vector<std::string> modifiers;
};

class HotkeyManagerPortalBackend : public HotkeyManagerLinuxBackend {
 public:
  explicit HotkeyManagerPortalBackend(FlEventChannel* event_channel);
  ~HotkeyManagerPortalBackend() override;

  FlMethodResponse* Register(FlValue* args) override;
  FlMethodResponse* Unregister(FlValue* args) override;
  FlMethodResponse* UnregisterAll() override;
  gboolean RebindNow();
  void HandleCreateSessionResponse(guint32 response,
                                   GVariant* results,
                                   guint generation);
  void HandleBindShortcutsResponse(guint32 response, guint generation);
  void HandleShortcutSignal(const gchar* signal_name, GVariant* parameters);
  void AddRequestSubscription(guint subscription_id);
  void RemoveRequestSubscription(guint subscription_id);

 private:
  bool EnsurePortal(std::string* error_message);
  void ScheduleRebind();
  void CreateSession(guint generation);
  void BindShortcuts(guint generation);
  void CloseSession();
  void UnsubscribeRequestSignals();
  void SubscribeShortcutSignals();
  void UnsubscribeShortcutSignals();
  std::string TriggerForHotkey(const PortalHotkey& hotkey) const;

  FlEventChannel* event_channel_;
  GDBusConnection* connection_;
  GDBusProxy* portal_;
  std::map<std::string, PortalHotkey> hotkeys_;
  std::vector<guint> request_subscription_ids_;
  std::string session_handle_;
  guint activated_subscription_id_;
  guint deactivated_subscription_id_;
  guint rebind_source_id_;
  guint generation_;
  guint token_counter_;
};

#endif  // FLUTTER_PLUGIN_HOTKEY_MANAGER_PORTAL_BACKEND_H_
