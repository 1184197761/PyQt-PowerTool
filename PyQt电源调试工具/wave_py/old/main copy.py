from PyQt6.QtWidgets import QApplication, QMainWindow, QGridLayout
from PyQt6.QtCore import QTimer, QThread, pyqtSignal
# from ui_form import Ui_MainWin
from struct import unpack
from matplotlib.backends.backend_qt5agg import NavigationToolbar2QT
from serial.tools.list_ports import comports
from serial import Serial
from matplotlib.pyplot import rcParams
from matplotlib.backends.backend_qtagg import FigureCanvasQTAgg
from matplotlib.figure import Figure
from sys import exit, argv
from PyQt6 import uic

Form, Window = uic.loadUiType("MainWindow.ui")


class WaveChannel():

    def __init__(self):
        self.x = []
        self.y = []
        self.state = False


class RecvDataThread(QThread):
    trigger_recv = pyqtSignal(list)  # 创建一个接收到数据信号

    def __init__(self):
        super(RecvDataThread, self).__init__()

    def run(self):
        while True:
            self.trigger_recv.emit(list(self.serial.read_until(b'\xee')))


class DataDisplayThread(QThread):
    display_trigger = pyqtSignal(list)

    def __init__(self):
        super(DataDisplayThread, self).__init__()
        self.timer_display = QTimer(self)
        self.timer_display.timeout.connect(self.run)
        self.timer_display.start(100)

    def run(self):
        # clf()
        self.mplCanvas.axes.lines.clear()
        for channel in channels:
            if channel.state:  # 显示通道波形
                self.mplCanvas.axes.plot(channel.x, channel.y, 'k')
        self.mplCanvas.draw()


class MyMplCanvas(FigureCanvasQTAgg):

    def __init__(self):
        rcParams['font.family'] = ['SimHei']
        self.fig = Figure()
        self.axes = self.fig.add_subplot(111)
        FigureCanvasQTAgg.__init__(self, self.fig)


class MainWin(Form, Window):

    def __init__(self):
        super(MainWin, self).__init__()
        self.setupUi(self)
        self.setWindowTitle("Tai-Action 电源调试助手")
        self.gridLayout = QGridLayout(self.listView)
        self.mplCanvas = MyMplCanvas()
        self.navigTool = NavigationToolbar2QT(self.mplCanvas)
        self.gridLayout.addWidget(self.mplCanvas)
        self.gridLayout.addWidget(self.navigTool)
        self.mplCanvas.fig.suptitle("动态波形")
        self.mplCanvas.axes.set_ylabel('Y 轴')
        self.mplCanvas.axes.set_xlabel('X 轴')
        self.serial = Serial()
        self.recvedNum = 0
        self.sendedNum = 0
        self.textBrowser_recvNum.setText('0')
        self.textBrowser_sendNum.setText('0')
        self.dataDisplay = DataDisplayThread()
        self.dataDisplay.mplCanvas = self.mplCanvas
        self.channelX = 0
        self.event_connect()
        self.port_check()

    def reset_key(self):  # 复位键实现方法
        for channel in channels:  # 清除波形类所有成员的值
            channel.x = []
            channel.y = []
        self.mplCanvas.axes.remove()  # 清除所有图像
        self.mplCanvas.axes = self.mplCanvas.fig.add_subplot(111)
        self.mplCanvas.draw()

    def event_connect(self):
        self.pushButton_serialCheck.clicked.connect(self.port_check)  # 串口检测按钮
        self.pushButton_serialOpen.clicked.connect(self.port_open)  # 打开串口按钮
        self.timer_checkBox = QTimer()
        self.timer_checkBox.timeout.connect(self.channel_select)  # 定时检测通道
        self.pushButton_sendClear.clicked.connect(self.send_clear)  # 清除发送窗口
        self.pushButton_recvClear.clicked.connect(self.recv_clear)  # 清除接收窗口
        self.pushButton_reset.clicked.connect(self.reset_key)  # 复位信号按钮
        self.pushButton_serialClose.clicked.connect(self.port_close)  # 关闭串口按钮

    def channel_select(self):
        for index, channel in enumerate(channels):
            channel.state = getattr(self,
                                    "checkBox_CH%d" % (index + 1)).isChecked()

    def port_open(self):
        self.serial.port = self.comboBox_portName.currentText()
        self.serial.baudrate = int(self.comboBox_baudrate.currentText())
        self.serial.bytesize = int(self.comboBox_dataBit.currentText())
        self.serial.stopbits = int(self.comboBox_stopBit.currentText())
        self.serial.parity = self.comboBox_parity.currentText()
        self.serial.open()
        # self.serial.inter_byte_timeout = 0.001
        self.pushButton_serialOpen.setEnabled(False)
        self.pushButton_serialClose.setEnabled(True)
        self.timer_checkBox.start(10)  # 打开通道检测定时器，周期为10ms
        self.recvData = RecvDataThread()  # 实例化线程对象
        self.recvData.serial = self.serial  # 传递参数至线程
        self.recvData.start()  # 启动线程
        self.recvData.trigger_recv.connect(self.dataHandle)  # 线程信号槽函数
        self.dataDisplay.start()  # 启动线程

    def dataHandle(self, value):
        self.data_decode(value)  # 对接收到的数据进行解码
        if self.checkBox_HEXRecv.checkState():  # hex 显示
            recvText = ' '.join(['{:02X}'.format(date)
                                 for date in value]) + '\n'
            self.textBrowser_recv.insertPlainText(recvText)
        else:  # 字符串位转unicode字符
            self.textBrowser_recv.insertPlainText(value.decode('iso-8859-1'))
        self.recvedNum += len(value)  # 统计接收字符的数量
        self.textBrowser_recvNum.setText(str(self.recvedNum))
        textCursor = self.textBrowser_recv.textCursor()  # 获取到Text光标
        textCursor.movePosition(textCursor.MoveOperation.End)  # 滚动到底部
        self.textBrowser_recv.setTextCursor(textCursor)  # 设置光标到Text中去

    def port_close(self):  # 关闭串口
        self.recvData.terminate()
        if self.recvData.isFinished():
            del self.recvData
        self.serial.close()
        self.pushButton_serialOpen.setEnabled(True)
        self.pushButton_serialClose.setEnabled(False)
        self.recvedNum = 0  # 接收数据和发送数据数目清零
        self.sendedNum = 0

    def port_check(self):
        self.comboBox_portName.clear()
        for port in comports():
            self.comboBox_portName.addItem(port[0])

    def data_decode(self, data):  # 默认第一个参数是对象本身
        if data[0] != 0xAA or data[len(data) - 1] != 0xEE:  # 判断首尾
            print("指令格式错误！")
            return None
        self.channelX += 1
        for index in range(data[1]):
            i = 5 * index
            hexStr = ''.join(['{:02X}'.format(d) for d in data[3 + i:7 + i]])
            channels[data[2 + i]].y.append(unpack('!f', bytes.fromhex(hexStr)))
            channels[data[2 + i]].x.append(self.channelX)

    def send_clear(self):
        self.textBrowser_sendNum.setText('0')
        self.textEdit_Send.setText('')

    def recv_clear(self):
        self.textBrowser_recvNum.setText('0')
        self.textBrowser_recv.setText('')


if __name__ == "__main__":
    channels = [WaveChannel() for _ in range(4)]
    app = QApplication(argv)
    widget = MainWin()  # 生成动画
    widget.show()
    exit(app.exec())
