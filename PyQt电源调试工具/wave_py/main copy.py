from PyQt6.QtWidgets import (
    QApplication,
    QMainWindow,
    QGridLayout,
    QMessageBox,
    QPushButton,
    QDoubleSpinBox,
    QTimeEdit,
    QToolButton,
    QDialog,
)
from qdarktheme import setup_theme
from PyQt6.QtCore import QTimer, QThread, pyqtSignal, QTime
from struct import unpack
from serial.tools.list_ports import comports
from serial import Serial
from sys import exit, argv
from pyqtgraph import PlotWidget, setConfigOptions, InfiniteLine
from ui_MainWindow import Ui_MainWindow
from ui_ParamDialog import Ui_Dialog as Ui_ParamDialog
from ui_ChannelDialog import Ui_Dialog as Ui_ChannelDialog
from time import time


class WaveChannel(Ui_MainWindow):
    def __init__(self, color, name, id, symbol):
        self.name = name
        self.id = id
        self.y = []
        self.color = color
        self.gain = 1.0
        self.symbol = symbol


class RunParmeter:
    def __init__(self, id) -> None:
        self.name = ""
        self.id = 0
        self.min = 0.0
        self.max = 65536.0
        self.gain = 0.01


class RecvDataThread(QThread):
    trigger = pyqtSignal(list)  # 创建一个接收到数据信号

    def __init__(self):
        super(RecvDataThread, self).__init__()

    def run(self):
        while True:
            if serial.inWaiting():
                self.trigger.emit(list(serial.readall()))


class ChannelDialog(QDialog, Ui_ChannelDialog):
    def __init__(self):
        super().__init__()
        self.setupUi(self)


class ParamDialog(QDialog, Ui_ParamDialog):
    def __init__(self):
        super().__init__()
        self.setupUi(self)


class MainWin(QMainWindow, Ui_MainWindow):
    def __init__(self):
        super().__init__()
        self.setupUi(self)
        setConfigOptions(foreground="k", antialias=True)
        self.graphWidget = PlotWidget(background="w")
        self.graphWidget.showGrid(x=True, y=True)
        self.graphWidget.setLabel("left", "采样值")
        self.graphWidget.setLabel("bottom", "时间/s")
        # self.graphWidget.plot().getViewBox().invertX(True)
        self.gridLayout = QGridLayout(self.graphicsView)
        self.gridLayout.addWidget(self.graphWidget)
        self.channelX = []
        self.cursors = []
        self.add_cursor()
        self.graphWidget.addLegend()
        for channel in channels:
            channel.line = self.graphWidget.plot(
                name=channel.name,
                pen=channel.color,
                symbol=channel.symbol,
            )
        self.port_check()
        self.event_connect()

    def wave_display(self):
        self.graphWidget.addLegend()
        if self.channelX == [] or not self.waveFlag:
            return
        self.waveFlag = False
        self.graphWidget.setXRange(
            self.channelX[-1] - 1,
            self.channelX[-1],
        )
        for index, cursor in enumerate(self.cursors):
            cursor.setPos(self.channelX[-1] - 1 + index)
        for channel in channels:
            channel.line.setData(self.channelX, channel.y)
            getattr(self, "lineEdit_CH%s" % channel.id).setText(
                str(round(channel.y[-1], 2))
            )

    def reset_key(self):  # 复位键实现方法
        for channel in channels:  # 清除波形类所有成员的值
            channel.y.clear()
        self.channelX.clear()
        self.graphWidget.clear()  # 清除所有图像
        for channel in channels:
            channel.line = self.graphWidget.plot(
                name=channel.name,
                pen=channel.color,
                symbol=channel.symbol,
            )
        for cursor in self.cursors:
            self.graphWidget.addItem(cursor)

    def event_connect(self):
        self.pushButton_portCheck.clicked.connect(self.port_check)
        self.pushButton_portOpen.clicked.connect(self.port_open)  # 打开串口按钮
        self.timer = QTimer()
        self.timer.timeout.connect(self.wave_display)
        self.pushButton_reset.clicked.connect(self.reset_key)  # 复位信号按钮
        for child in self.groupBox_runContrl.findChildren(QPushButton):
            child.clicked.connect(self.port_write)
        for child in self.groupBox_readWriteData.findChildren(QDoubleSpinBox):
            child.wheelEvent = lambda e: e.ignore()
            child.editingFinished.connect(self.port_write)
        self.checkBox_autoStart.clicked.connect(self.port_write)
        for child in self.groupBox_powerSelect.findChildren(QTimeEdit):
            child.dateTimeChanged.connect(self.port_write)
        for child in self.groupBox_runContrl.findChildren(QPushButton):
            child.clicked.connect(self.port_write)
        self.pushButton_send.clicked.connect(self.data_send)
        for child in self.groupBox_wave.findChildren(QToolButton):
            child.clicked.connect(self.channel_dialog)
        for child in self.groupBox_readWriteData.findChildren(QPushButton):
            child.clicked.connect(self.param_dialog)

    def add_cursor(self):
        for index in range(2):
            line = InfiniteLine(
                movable=True,
                pen="k",
                label="游标" + str(index),
            )
            line.addMarker(">|<", 0)
            line.sigDragged.connect(self.cursor_measure)
            self.cursors.append(line)
            self.graphWidget.addItem(line)

    def cursor_measure(self):
        text1 = "游标0：" + str(self.cursors[0].pos()[0])
        text2 = "\n游标1：" + str(self.cursors[1].pos()[0])
        text3 = "\n间距：" + str((self.cursors[1].pos() - self.cursors[0].pos())[0])
        self.textEdit_recv.setText(text1 + text2 + text3)

    def channel_dialog(self):
        dialog = ChannelDialog()  # 生成动画
        dialog.lineEdit_name.setText(channels[int(self.sender().whatsThis())].name)
        dialog.doubleSpinBox_gain.setValue(
            channels[int(self.sender().whatsThis())].gain
        )
        dialog.show()
        dialog.exec()
        if dialog.lineEdit_name.text():
            self.sender().setText(dialog.lineEdit_name.text())
            channels[int(self.sender().whatsThis())].name = dialog.lineEdit_name.text()
        if dialog.doubleSpinBox_gain.value():
            channels[
                int(self.sender().whatsThis())
            ].gain = dialog.doubleSpinBox_gain.value()

    def param_dialog(self):
        dialog = ParamDialog()  # 生成动画
        dialog.lineEdit_name.setText(self.sender().text())
        dialog.doubleSpinBox_gain.setValue(
            parameter[int(self.sender().whatsThis())].gain
        )
        dialog.doubleSpinBox_max.setValue(parameter[int(self.sender().whatsThis())].max)
        dialog.doubleSpinBox_min.setValue(parameter[int(self.sender().whatsThis())].min)
        dialog.show()
        dialog.exec()
        if dialog.lineEdit_name.text():
            self.sender().setText(dialog.lineEdit_name.text())
        parameter[
            int(self.sender().whatsThis())
        ].gain = dialog.doubleSpinBox_gain.value()
        parameter[int(self.sender().whatsThis())].max = dialog.doubleSpinBox_max.value()
        parameter[int(self.sender().whatsThis())].min = dialog.doubleSpinBox_min.value()
        getattr(self, "doubleSpinBox_%d" % int(self.sender().whatsThis())).setMinimum(
            dialog.doubleSpinBox_min.value()
        )
        getattr(self, "doubleSpinBox_%d" % int(self.sender().whatsThis())).setMaximum(
            dialog.doubleSpinBox_max.value()
        )

    def port_check(self):
        self.comboBox_portSelect.clear()
        for port in comports():
            self.comboBox_portSelect.addItem(port[0])

    def port_open(self):
        if self.pushButton_portOpen.isChecked():
            serial.port = self.comboBox_portSelect.currentText()
            serial.baudrate = int(self.comboBox_baudrate.currentText())
            serial.bytesize = int(self.comboBox_dataBit.currentText())
            serial.stopbits = int(self.comboBox_stopBit.currentText())
            serial.parity = self.comboBox_parityBit.currentText()
            try:
                serial.open()
            except:
                QMessageBox.warning(self, "警告", "串口被占用！")
                self.pushButton_portOpen.setChecked(False)
                return
            self.pushButton_portOpen.setText("关闭串口")
            # self.pushButton_send.setEnabled(True)
            self.timer.start(100)
            self.recvData = RecvDataThread()  # 实例化线程对象
            self.recvData.trigger.connect(self.dataHandle)  # 线程信号槽函数
            self.recvData.start()  # 启动线程
        else:
            self.recvData.terminate()
            serial.close()
            self.recvData.exit()  # 启动线程
            self.timer.stop()
            self.pushButton_portOpen.setText("打开串口")

    def port_write(self):
        if not serial.isOpen():
            QMessageBox.warning(self, "警告", "串口未打开！")
            if self.sender() == self.checkBox_autoStart:
                self.checkBox_autoStart.toggle()
            return
        self.cmd = []
        addr = int(self.sender().whatsThis())
        dataH = 0
        dataL = 0
        match self.sender().parent().title():
            case "运行控制":
                self.cmd = [0xCC, addr, dataH, dataL, 0xEE]
            case "运行参数":
                data = int(
                    self.sender().value()
                    / parameter[int(self.sender().whatsThis())].gain
                )
                dataH = data >> 8 & 0xFF
                dataL = data & 0xFF
                self.cmd = [0xCC, addr, dataH, dataL, 0xEE]
            case "开关机选项":
                if addr == 22:
                    dataL = int(self.sender().isChecked())
                elif addr in range(23, 25):
                    dataH = self.sender().time().toPyTime().hour
                    dataL = self.sender().time().toPyTime().minute
                self.cmd = [0xCC, addr, dataH, dataL, 0xEE]
        serial.write(bytes(self.cmd))

    def dataHandle(self, rx):
        if len(rx) == 0:
            return
        if rx[0] == 0xAA and rx[-1] == 0xEE:  # 判断首尾
            # if rx[1] > 4:
            #     QMessageBox.warning(self, "警告", "最多支持4个通道！")
            #     return
            if len(self.channelX):
                self.channelX.append(time() - self.startTime)
            else:
                self.startTime = time()
                self.channelX.append(0)
            for index in range(4):
                i = 4 * index
                hexStr = "".join(["{:02X}".format(d) for d in rx[1 + i : 5 + i]])
                rawData = unpack("!f", bytes.fromhex(hexStr))[0]
                channels[index].y.append(rawData * channels[index].gain)
            self.waveFlag = True
        elif rx[0] == 0xBB and rx[-1] == 0xEE:
            for child in self.findChildren(QDoubleSpinBox):
                if child.hasFocus():
                    continue
                dataId = int(child.whatsThis())
                result = ((rx[1 + dataId * 2] << 8) + rx[2 + dataId * 2]) * parameter[
                    dataId
                ].gain
                child.setValue(min(child.maximum(), result))
            # for child in self.findChildren(QLineEdit):
            #     dataId = int(child.whatsThis())
            #     child.setText(
            #         str(((rx[1 + dataId * 2] << 8) + rx[2 + dataId * 2]) / 100)
            #     )
            self.checkBox_autoStart.setChecked(rx[2 + 22 * 2])
            self.timeEdit_start.setTime(QTime(rx[1 + 23 * 2], rx[2 + 23 * 2]))
            self.timeEdit_stop.setTime(QTime(rx[1 + 24 * 2], rx[2 + 24 * 2]))

        if rx[0] == 0xAA:
            return
        if self.checkBox_HEXRecv.isChecked():  # hex 显示
            recvText = " ".join(["{:02X}".format(v) for v in rx])
            self.textEdit_recv.insertPlainText("已接收👈：" + recvText + "\n")
        else:  # 字符串位转unicode字符
            self.textEdit_recv.insertPlainText(
                "已接收👈：" + bytes(rx).decode(errors="ignore") + "\n"
            )
        textCursor = self.textEdit_recv.textCursor()  # 获取到Text光标
        textCursor.movePosition(textCursor.MoveOperation.End)  # 滚动到底部
        self.textEdit_recv.setTextCursor(textCursor)  # 设置光标到Text中去

    def data_send(self):
        if not serial.isOpen():
            QMessageBox.warning(self, "警告", "串口未打开！")
        if serial.isOpen():
            sendText = self.plainTextEdit_send.toPlainText()
            if sendText != "":
                if self.checkBox_HEXSend.isChecked():
                    try:
                        serial.write(bytes.fromhex(sendText))
                    except:
                        QMessageBox.warning(self, "警告", "请输入十六进制数据！")
                        return
                else:
                    serial.write(sendText.encode())
                self.textEdit_recv.insertPlainText("已发送👉：" + sendText + "\n")


if __name__ == "__main__":
    channels = [
        WaveChannel("rgby"[index], "通道%d" % index, index, "+txo"[index])
        for index in range(4)
    ]
    serial = Serial(timeout=0.001)
    parameter = [RunParmeter(index) for index in range(256)]

    app = QApplication(argv)
    setup_theme("auto")
    widget = MainWin()  # 生成动画
    widget.show()
    exit(app.exec())
