import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Drawer {
    id: panel
    required property var controller
    edge: Qt.RightEdge
    modal: false
    dim: false
    readonly property var detail: controller.agentDetails
    readonly property var observation: controller.observationDetails
    function value(key) {
        const item = detail[key]
        return item === undefined || item === null ? "not exposed" : String(item)
    }
    function accounting() {
        const ledger = observation.ledger
        if (!ledger) return "No accounting yet."
        return "Founder input: " + ledger.founder_input
            + "\nPreset offspring input: " + ledger.preset_offspring_input
            + "\nFood input: " + ledger.food_input
            + "\nCompute spent: " + ledger.compute_spent
            + "\nMaintenance spent: " + ledger.maintenance_spent
            + "\nRemoved on death: " + ledger.death_removed
            + "\nSource live() net change: " + ledger.source_net_change
            + "\nTransferred internally: " + ledger.transferred
            + "\nAccounted live prana: " + ledger.accounted_live_prana
            + "\nActual live prana: " + ledger.live_prana
            + "\nBalance error: " + ledger.balance_error
    }
    background: Rectangle { color: "#241536"; border.color: "#B04CFF" }
    ScrollView {
        anchors.fill: parent
        anchors.margins: 18
        contentWidth: availableWidth
        ColumnLayout {
            width: parent.width
            spacing: 12
            RowLayout {
                Label { text: "AGENT INSPECTOR"; font.bold: true; Layout.fillWidth: true }
                Button { text: "Close"; onClicked: panel.close() }
            }
            Label {
                Layout.fillWidth: true; wrapMode: Text.WordWrap
                text: "Choose an agent here or click a white center in Living grid. Repeated clicks cycle overlapping agents. Step advances a world tick."
            }
            ComboBox {
                Layout.fillWidth: true
                model: panel.controller.agentChoices
                currentIndex: panel.controller.agentChoices.indexOf(panel.controller.selectedAgentId)
                displayText: panel.controller.selectedAgentId || "Choose an agent"
                enabled: panel.controller.busy
                Accessible.name: "Agent to inspect"
                onActivated: panel.controller.selectAgent(currentText)
            }
            Label {
                visible: !!panel.observation.organisms_truncated
                text: "Showing the first 1,024 live agents. Enter another ID below."
                wrapMode: Text.WordWrap; Layout.fillWidth: true
            }
            RowLayout {
                TextField { id: agentId; placeholderText: "Agent ID"; maximumLength: 256; Layout.fillWidth: true }
                Button { text: "Select"; enabled: panel.controller.busy; onClicked: panel.controller.selectAgent(agentId.text) }
            }
            Label {
                text: panel.controller.busy ? "Observed at tick " + panel.value("tick") : "Last observed state · simulation is not running"
                wrapMode: Text.WordWrap; Layout.fillWidth: true
            }
            Label {
                Layout.fillWidth: true; wrapMode: Text.WrapAnywhere; textFormat: Text.PlainText
                text: "ID: " + panel.value("id") + "\nStatus: " + panel.value("status")
                    + "\nPosition: " + panel.value("address") + "\nPrana: " + panel.value("prana")
                    + "\nLifecycle request: " + panel.value("lifecycle_request")
                    + "\nPending VM request: " + panel.value("pending_request")
                    + "\nInstruction position (zero-based): " + panel.value("instruction_position")
                    + "\nNext word: " + panel.value("next_word")
                    + "\nPrepaid compute credits: " + panel.value("compute_credits")
                    + "\nParent: " + (panel.detail.parent === null ? "founder" : panel.value("parent"))
                    + "\nGeneration: " + panel.value("generation")
                    + "\nLanguage: " + panel.value("language")
                    + "\nExecution: " + panel.value("execution_method")
                    + "\nEnergy policy: " + panel.value("energy_policy")
            }
            Label { text: "Raw genome · " + panel.value("word_count") + " words" }
            TextArea {
                Layout.fillWidth: true; readOnly: true; selectByMouse: true
                textFormat: TextEdit.PlainText; wrapMode: TextEdit.WrapAnywhere
                text: panel.detail.raw_genome || ""
            }
            Label { text: "Decoded program (→ next instruction)" }
            TextArea {
                Layout.fillWidth: true; readOnly: true; selectByMouse: true
                textFormat: TextEdit.PlainText; wrapMode: TextEdit.WrapAnywhere
                text: panel.detail.decoded_display || ""
            }
            Label { visible: !!panel.detail.truncated; text: "Genome display truncated; hashes identify the full genome."; wrapMode: Text.WordWrap; Layout.fillWidth: true }
            Label {
                Layout.fillWidth: true; wrapMode: Text.WrapAnywhere; textFormat: Text.PlainText
                text: "Raw-genome SHA-256: " + panel.value("genome_id")
                    + "\nDecoded-program SHA-256: " + panel.value("program_id")
                    + "\nAgent counters: " + (panel.detail.metrics ? JSON.stringify(panel.detail.metrics) : "not exposed by source live()")
            }
            Label { text: "WORLD PRANA LEDGER"; font.bold: true }
            Label { text: panel.accounting(); Layout.fillWidth: true; wrapMode: Text.WordWrap }
            Label { text: "CA food generation is outside this agent-prana ledger. Transfers do not change the total."; Layout.fillWidth: true; wrapMode: Text.WordWrap }
            Label {
                Layout.fillWidth: true; wrapMode: Text.WrapAnywhere; textFormat: Text.PlainText
                text: panel.observation.trace ? "Trace: " + panel.observation.trace.mode
                    + " · " + panel.observation.trace.events_written + "/" + panel.observation.trace.limit
                    + (panel.observation.trace.truncated ? " · limit reached" : "")
                    + (panel.observation.trace.error ? "\nRecording stopped: " + panel.observation.trace.error : "") : "Trace: off"
            }
        }
    }
}
