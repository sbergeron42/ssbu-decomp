#!/bin/bash
# Worker notification: signal orchestrator + desktop toast
POOL="$1"
MSG="${2:-done}"
BUS_DIR="$(dirname "$0")/../.claude_bus"
mkdir -p "$BUS_DIR"
echo "$(date +%H:%M:%S) $MSG" > "$BUS_DIR/$POOL.done"

# Windows desktop toast notification
powershell.exe -Command "
  [Windows.UI.Notifications.ToastNotificationManager, Windows.UI.Notifications, ContentType = WindowsRuntime] | Out-Null
  [Windows.Data.Xml.Dom.XmlDocument, Windows.Data.Xml.Dom, ContentType = WindowsRuntime] | Out-Null
  \$xml = [Windows.Data.Xml.Dom.XmlDocument]::new()
  \$xml.LoadXml('<toast><visual><binding template=\"ToastText02\"><text id=\"1\">SSBU Decomp: $POOL done</text><text id=\"2\">$MSG — tell orchestrator to check</text></binding></visual></toast>')
  [Windows.UI.Notifications.ToastNotificationManager]::CreateToastNotifier('Claude Code').Show([Windows.UI.Notifications.ToastNotification]::new(\$xml))
" 2>/dev/null

echo "Notified orchestrator: $POOL is done ($MSG)"
