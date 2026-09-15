import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
import Ouroborus 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 1120
    height: 740
    minimumWidth: 800
    minimumHeight: 560
    title: "Ouroborus"
    color: "#140D21"
    readonly property color purple: "#B04CFF"
    readonly property color green: "#B6FF3B"
    readonly property color ink: "#F1EAFE"
    palette.windowText: ink
    palette.text: ink
    palette.buttonText: ink
    palette.button: "#38234D"
    palette.base: "#140D21"
    palette.highlight: purple
    palette.highlightedText: "#140D21"
    font.pixelSize: 15

    component ActionButton: Button {
        id: control
        padding: 10
        background: Rectangle {
            radius: 8
            color: !control.enabled ? "#241536" : control.down ? "#704098" : control.highlighted ? window.green : control.hovered ? "#503266" : "#38234D"
            border.width: control.activeFocus ? 2 : 1
            border.color: control.activeFocus ? window.purple : "#49305F"
        }
        contentItem: Text {
            text: control.text
            font: control.font
            color: !control.enabled ? "#8C799D" : control.highlighted ? "#140D21" : window.ink
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }

    header: Rectangle {
        height: 66
        color: window.purple
        RowLayout {
            anchors.fill: parent
            anchors.margins: 20
            Label { text: "OUROBORUS"; color: "#140D21"; font.bold: true; font.letterSpacing: 3; font.pixelSize: 23 }
            Item { Layout.fillWidth: true }
            Label { text: "Artificial life playground"; color: "#140D21" }
        }
    }

    property bool closeWhenStopped: false
    function draft() {
        return {preset: preset.currentText.toLowerCase(), steps: steps.value, seed: seed.value,
                interval: pace.value, audio: audio.output, volume: volume.value,
                execution_method: preset.currentIndex === 4 ? method.currentText.toLowerCase() : "compiled",
                instructions_per_tick: preset.currentIndex === 4 ? allowance.value : 6,
                energy_policy: preset.currentIndex === 4 ? metabolism.currentText.toLowerCase() : "maintenance",
                instructions_per_prana: preset.currentIndex === 4 ? computeBatch.value : 6}
    }
    FileDialog {
        id: saveDialog
        title: "Save simulation settings"
        fileMode: FileDialog.SaveFile
        defaultSuffix: "json"
        nameFilters: ["Simulation settings (*.json)"]
        onAccepted: simulation.savePreset(selectedFile, window.draft())
    }
    FileDialog {
        id: loadDialog
        title: "Load simulation settings"
        nameFilters: ["Simulation settings (*.json)"]
        onAccepted: {
            const settings = simulation.loadPreset(selectedFile)
            if (settings.preset === undefined) return
            preset.currentIndex = ["alpha", "beta", "delta", "epsilon", "forager"].indexOf(settings.preset)
            steps.value = settings.steps
            seed.value = settings.seed
            pace.value = settings.interval
            audio.currentIndex = ["speakers", "off", "silent"].indexOf(settings.audio)
            volume.value = settings.volume
            method.currentIndex = ["compiled", "interpreted"].indexOf(settings.execution_method)
            allowance.value = settings.instructions_per_tick
            metabolism.currentIndex = ["maintenance", "compute"].indexOf(settings.energy_policy)
            computeBatch.value = settings.instructions_per_prana
        }
    }
    onClosing: function(close) {
        if (simulation.busy) {
            close.accepted = false
            closeWhenStopped = true
            simulation.stop()
        }
    }
    Connections {
        target: simulation
        function onCompleted() { if (window.closeWhenStopped) window.close() }
    }

    RowLayout {
        anchors.fill: parent
        spacing: 1
        Rectangle {
            Layout.preferredWidth: 280
            Layout.fillHeight: true
            color: "#241536"
            ScrollView {
                anchors.fill: parent
                anchors.margins: 18
                anchors.bottomMargin: 160
                contentWidth: availableWidth
                ColumnLayout {
                    width: parent.width
                    spacing: 12
                    Label { text: "YOUR WORLD"; color: window.green; font.bold: true; font.letterSpacing: 2 }
                    RowLayout {
                        ActionButton { text: "Load settings"; onClicked: loadDialog.open() }
                        ActionButton { text: "Save"; onClicked: saveDialog.open() }
                    }
                    Label { text: "Specificity" }
                    ComboBox {
                        id: preset
                        Layout.fillWidth: true
                        model: ["Alpha", "Beta", "Delta", "Epsilon", "Forager"]
                        Accessible.name: "Simulation specificity"
                        onActivated: { if (currentIndex !== 4) method.currentIndex = 0 }
                        ToolTip.visible: hovered
                        ToolTip.text: "World rules, initial population, and seed genome"
                    }
                    Label {
                        text: (preset.currentIndex === 0 || preset.currentIndex === 4) ? "World: 80 × 20 · 3 initial agents" : preset.currentIndex === 3 ? "World: 80 × 40 · no initial agents" : "World: 80 × 40 · 3 initial agents"
                        color: "#C8B6DB"; font.pixelSize: 12
                    }
                    Label { text: "Execution method" }
                    ComboBox {
                        id: method; model: ["Compiled", "Interpreted"]; Layout.fillWidth: true
                        enabled: preset.currentIndex === 4
                        Accessible.name: "Agent execution method"
                    }
                    ColumnLayout {
                        visible: preset.currentIndex === 4
                        Layout.fillWidth: true
                        Label { text: "Instructions per tick" }
                        SpinBox { id: allowance; from: 1; to: 4096; value: 6; editable: true; Layout.fillWidth: true }
                        Label { text: "Energy policy" }
                        ComboBox { id: metabolism; model: ["Maintenance", "Compute"]; Layout.fillWidth: true }
                        Label { text: "Instructions per prana"; visible: metabolism.currentIndex === 1 }
                        SpinBox { id: computeBatch; from: 1; to: 4096; value: 6; editable: true; Layout.fillWidth: true; visible: metabolism.currentIndex === 1 }
                    }
                    Label { text: "Iterations" }
                    SpinBox { id: steps; from: 1; to: 1000000; value: 4000; editable: true; Layout.fillWidth: true }
                    Label { text: "Random seed" }
                    RowLayout {
                        SpinBox { id: seed; from: 0; to: 2147483647; value: 42; editable: true; Layout.fillWidth: true }
                        ActionButton { text: "Roll"; Accessible.name: "Randomize seed"; onClicked: seed.value = Math.floor(Math.random() * 2147483647) }
                    }
                    Label { text: "Tick interval: " + pace.value.toFixed(2) + " s" }
                    Slider {
                        id: pace; from: 0.01; to: 5; value: 0.1; stepSize: 0.01; Layout.fillWidth: true
                        Accessible.name: "Tick interval"
                        onMoved: simulation.setPace(value)
                    }
                    Label { text: "Audio output" }
                    ComboBox {
                        id: audio; model: ["Speakers", "Off", "Silent test"]
                        Layout.fillWidth: true
                        property string output: ["speakers", "off", "silent"][currentIndex]
                    }
                    Label { text: "Volume: " + Math.round(volume.value * 100) + "%" }
                    Slider {
                        id: volume; from: 0; to: 1; value: 0.5; Layout.fillWidth: true
                        Accessible.name: "Audio volume"
                        onMoved: simulation.setVolume(value)
                    }
                    CheckBox { id: mute; text: "Mute"; onToggled: simulation.setMuted(checked) }
                    Label {
                        Layout.fillWidth: true; wrapMode: Text.WordWrap; color: "#C8B6DB"; font.pixelSize: 12
                        text: "Specificity, execution, energy, seed, iterations and output apply on the next run. Pace and volume also apply live."
                    }
                }
            }
            ColumnLayout {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.margins: 18
                spacing: 6
                    ActionButton {
                        objectName: "startButton"
                        text: "▶  Start simulation"; Layout.fillWidth: true; enabled: !simulation.busy
                        highlighted: true
                        onClicked: {
                            mute.checked = false
                            const settings = window.draft()
                            simulation.start(preset.currentText, steps.value, seed.value, pace.value, audio.output, volume.value,
                                             settings.execution_method, settings.instructions_per_tick,
                                             settings.energy_policy, settings.instructions_per_prana)
                        }
                    }
                    RowLayout {
                        ActionButton {
                            text: simulation.state === "paused" ? "▶ Resume" : "Ⅱ Pause"
                            enabled: simulation.state === "running" || simulation.state === "paused"
                            Layout.fillWidth: true
                            onClicked: simulation.command(simulation.state === "paused" ? "resume" : "pause")
                        }
                        ActionButton { text: "Step"; enabled: simulation.state === "paused"; onClicked: simulation.command("step") }
                    }
                    ActionButton {
                        text: "■  Stop"; Layout.fillWidth: true
                        enabled: simulation.busy && simulation.state !== "stopping"
                        onClicked: simulation.stop()
                    }
            }
        }
        ColumnLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.margins: 20
            spacing: 14
            RowLayout {
                ComboBox { id: view; objectName: "viewSelector"; model: ["Terminal", "Living grid"]; Accessible.name: "Simulation view" }
                Label { text: "Text size"; visible: view.currentIndex === 0 }
                SpinBox { from: 8; to: 24; value: 14; visible: view.currentIndex === 0; onValueModified: terminal.fontSize = value }
                Item { Layout.fillWidth: true }
                Label { text: simulation.state; color: window.green; font.bold: true }
            }
            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                radius: 12
                color: "#100A19"
                border.color: "#49305F"
                TerminalView {
                    id: terminal; objectName: "terminal"
                    anchors.fill: parent; anchors.margins: 10
                    visible: view.currentIndex === 0
                }
                GridView { objectName: "grid"; anchors.fill: parent; anchors.margins: 10; visible: view.currentIndex === 1 }
                Label {
                    anchors.centerIn: parent; text: "A world is waiting."; color: window.green; font.pixelSize: 28
                    visible: simulation.state === "idle"
                }
                BusyIndicator { anchors.centerIn: parent; running: simulation.state === "preparing"; visible: running }
            }
            Label { text: simulation.metrics; color: window.ink }
            Label { text: simulation.runSummary; color: "#C8B6DB"; visible: text.length > 0 }
            Label { text: simulation.audioStatus; color: "#C8B6DB" }
            RowLayout {
                Label { text: simulation.message; Layout.fillWidth: true; wrapMode: Text.WordWrap; color: "#C8B6DB" }
                ActionButton { text: "Run logs"; enabled: simulation.runPath.length > 0; onClicked: simulation.openLogs() }
            }
        }
    }
}
