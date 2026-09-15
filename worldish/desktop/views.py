"""Interchangeable Qt views: a real terminal screen and a snapshot grid."""
import copy
import math

import pyte
from PySide6.QtCore import Property, QRectF, Qt, Signal, Slot
from PySide6.QtGui import QColor, QFont, QFontMetricsF
from PySide6.QtQuick import QQuickPaintedItem


class TerminalScreen(pyte.Screen):
    """Support the alternate-screen mode used by ncurses/xterm."""
    def __init__(self, *args):
        self.saved_screen = None
        super().__init__(*args)

    def set_mode(self, *modes, **kwargs):
        if kwargs.get("private") and any(m in modes for m in (47, 1047, 1049)):
            if self.saved_screen is None:
                self.saved_screen = (copy.deepcopy(self.buffer), copy.deepcopy(self.cursor))
                self.erase_in_display(2)
                self.cursor_position()
        super().set_mode(*modes, **kwargs)

    def reset_mode(self, *modes, **kwargs):
        if kwargs.get("private") and any(m in modes for m in (47, 1047, 1049)):
            if self.saved_screen is not None:
                self.buffer, self.cursor = self.saved_screen
                self.saved_screen = None
                self.dirty.update(range(self.lines))
        super().reset_mode(*modes, **kwargs)


COLORS = {"black": "#100A19", "red": "#FF607D", "green": "#B6FF3B",
          "brown": "#FFE078", "yellow": "#FFE078", "blue": "#739DFF",
          "magenta": "#B04CFF", "cyan": "#65E6DD", "white": "#F1EAFE"}


class TerminalView(QQuickPaintedItem):
    resized = Signal(int, int)
    inputBytes = Signal(bytes)
    fontSizeChanged = Signal()

    def __init__(self, parent=None):
        super().__init__(parent)
        self.screen = TerminalScreen(80, 30)
        self.stream = pyte.ByteStream(self.screen)
        self._font_size = 14
        self.setClip(True)
        self.setAcceptedMouseButtons(Qt.MouseButton.LeftButton)
        self.widthChanged.connect(self._resize)
        self.heightChanged.connect(self._resize)
        self._font_metrics()

    def _font_metrics(self):
        self.font = QFont("monospace")
        self.font.setStyleHint(QFont.StyleHint.Monospace)
        self.font.setPixelSize(self._font_size)
        metrics = QFontMetricsF(self.font)
        self.cell_width = math.ceil(metrics.horizontalAdvance("M"))
        self.cell_height = math.ceil(metrics.height())
        self.ascent = metrics.ascent()

    def setFontSize(self, size):
        self._font_size = max(8, min(int(size), 32))
        self._font_metrics()
        self._resize()
        self.fontSizeChanged.emit()

    fontSize = Property(int, lambda self: self._font_size, setFontSize, notify=fontSizeChanged)

    def _resize(self):
        columns = max(2, min(400, int(self.width() / self.cell_width)))
        rows = max(2, min(200, int(self.height() / self.cell_height)))
        self.screen.resize(lines=rows, columns=columns)
        self.resized.emit(columns, rows)
        self.update()

    @Slot(bytes)
    def feed(self, data):
        self.stream.feed(data)
        self.update()

    @Slot()
    def reset(self):
        self.screen = TerminalScreen(self.screen.columns, self.screen.lines)
        self.stream = pyte.ByteStream(self.screen)
        self.update()

    def paint(self, painter):
        painter.fillRect(self.boundingRect(), QColor("#100A19"))
        for y in range(self.screen.lines):
            for x, cell in list(self.screen.buffer[y].items()):
                if x >= self.screen.columns:
                    continue
                foreground = self._color(cell.fg, "#F1EAFE")
                background = self._color(cell.bg, "#100A19")
                if cell.reverse:
                    foreground, background = background, foreground
                rect = QRectF(x * self.cell_width, y * self.cell_height, self.cell_width, self.cell_height)
                if background != QColor("#100A19"):
                    painter.fillRect(rect, background)
                if cell.data.strip():
                    font = QFont(self.font)
                    font.setBold(cell.bold)
                    font.setItalic(cell.italics)
                    font.setUnderline(cell.underscore)
                    painter.setFont(font)
                    painter.setPen(foreground)
                    painter.drawText(rect.x(), rect.y() + self.ascent, cell.data)
        if self.hasActiveFocus() and not self.screen.cursor.hidden:
            painter.setPen(QColor("#B6FF3B"))
            painter.drawRect(QRectF(self.screen.cursor.x * self.cell_width,
                                   self.screen.cursor.y * self.cell_height, self.cell_width, self.cell_height))

    @staticmethod
    def _color(value, default):
        return QColor(COLORS.get(value, "#" + value if len(value) == 6 else default))

    def mousePressEvent(self, event):
        self.forceActiveFocus()
        event.accept()
        self.update()

    def keyPressEvent(self, event):
        keys = {Qt.Key.Key_Up: b"\x1b[A", Qt.Key.Key_Down: b"\x1b[B", Qt.Key.Key_Right: b"\x1b[C",
                Qt.Key.Key_Left: b"\x1b[D", Qt.Key.Key_Return: b"\r", Qt.Key.Key_Enter: b"\r",
                Qt.Key.Key_Backspace: b"\x7f", Qt.Key.Key_Escape: b"\x1b"}
        if event.key() == Qt.Key.Key_C and event.modifiers() & Qt.KeyboardModifier.ControlModifier:
            self.inputBytes.emit(b"\x03")
        elif event.key() in keys:
            self.inputBytes.emit(keys[event.key()])
        elif event.text():
            self.inputBytes.emit(event.text().encode("utf-8"))
        else:
            event.ignore()
            return
        event.accept()


class GridView(QQuickPaintedItem):
    """Read-only world snapshots with selection of organism centers."""
    agentSelected = Signal(str)
    selectedAgentIdChanged = Signal()
    def __init__(self, parent=None):
        super().__init__(parent)
        self.frame = None
        self._selected_agent = ""
        self.setAcceptedMouseButtons(Qt.MouseButton.LeftButton)
        self.setClip(True)

    def setSelectedAgentId(self, value):
        if value != self._selected_agent:
            self._selected_agent = value
            self.selectedAgentIdChanged.emit()
            self.update()

    selectedAgentId = Property(str, lambda self: self._selected_agent,
                               setSelectedAgentId, notify=selectedAgentIdChanged)

    @Slot(float, float, result=str)
    def agentAt(self, x, y):
        if not self.frame:
            return ""
        width, height = self.frame["width"], self.frame["height"]
        scale = min(self.width() / width, self.height() / height)
        if scale <= 0:
            return ""
        dx, dy = (self.width() - width * scale) / 2, (self.height() - height * scale) / 2
        cell = [math.floor((x - dx) / scale), math.floor((y - dy) / scale)]
        candidates = [item["id"] for item in self.frame.get("organisms", [])
                      if item["position"] == cell]
        if not candidates:
            return ""
        # Repeated clicks cycle overlapping centers in snapshot order.
        index = candidates.index(self._selected_agent) + 1 if self._selected_agent in candidates else 0
        return candidates[index % len(candidates)]

    def mousePressEvent(self, event):
        agent_id = self.agentAt(event.position().x(), event.position().y())
        if agent_id:
            self.agentSelected.emit(agent_id)
        event.accept()

    @Slot(dict)
    def snapshot(self, frame):
        self.frame = frame
        self.update()

    @Slot()
    def reset(self):
        self.frame = None
        self.update()

    def paint(self, painter):
        painter.fillRect(self.boundingRect(), QColor("#100A19"))
        if not self.frame:
            return
        frame = self.frame
        width, height = frame["width"], frame["height"]
        scale = min(self.width() / width, self.height() / height)
        dx, dy = (self.width() - width * scale) / 2, (self.height() - height * scale) / 2
        painter.setPen(Qt.PenStyle.NoPen)
        painter.setBrush(QColor("#B6FF3B"))
        for index, alive in enumerate(frame["cells"]):
            if alive:
                painter.drawRect(QRectF(dx + index % width * scale, dy + index // width * scale, scale, scale))
        painter.setBrush(QColor("#B04CFF"))
        for x, y in frame["agents"]:
            if 0 <= x < width and 0 <= y < height:
                painter.drawRect(QRectF(dx + x * scale, dy + y * scale, scale, scale))

        painter.setBrush(QColor("#F1EAFE"))
        for item in frame.get("organisms", []):
            x, y = item["position"]
            painter.drawEllipse(QRectF(dx + (x + 0.35) * scale, dy + (y + 0.35) * scale,
                                      scale * 0.3, scale * 0.3))
        selected = frame.get("inspection", {})
        if selected.get("id") == self._selected_agent and selected.get("status") == "alive":
            x, y = selected["address"]
            painter.setBrush(Qt.BrushStyle.NoBrush)
            painter.setPen(QColor("#FFE078"))
            painter.drawRect(QRectF(dx + x * scale, dy + y * scale, scale, scale))
