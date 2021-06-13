import gmplot
import pandas as pd
import serial
import time
import serial.tools.list_ports
import sys
import requests


def convert_format(i):
    lat = float(i.split(',')[0][:2]) + float(i.split(',')[0][2:])/60
    long = float(i.split(',')[1][:3]) + float(i.split(',')[1][3:][:-1]) / 60
    return lat, long


def plot(d):
    serialPort = serial.Serial(
        port="COM3", baudrate=9600, bytesize=8, timeout=2, stopbits=serial.STOPBITS_ONE
    )
    while 1:
        # Wait until there is data waiting in the serial buffer
        if serialPort.in_waiting > 0:

            # Read data out of the buffer until a carraige return / new line is found
            serialString = serialPort.readline()

            # Print the contents of the serial data
            try:
                print(serialString.decode("Ascii"))
                i = serialString.decode("Ascii")
                if i[0] == '3':
                    lat, long = convert_format(i)
                    # lat, long = float(i.split(',')[0])/100, float(i.split(',')[1][:-1])/100
                    print(lat, long)
                    d2 = pd.DataFrame({'lat': [lat], 'long': [long]})
                    d = d.append(d2)
                    gmap3 = gmplot.GoogleMapPlotter(d.iloc[0, :][0],
                                                    d.iloc[0, :][1], 16)

                    gmap3.scatter(d.lat, d.long,
                                  size=20, marker=False)

                    gmap3.plot(d.lat, d.long,
                               'cornflowerblue', edge_width=2.5)

                    gmap3.draw("map3.html")

            except:
                pass


def get_available_ports():

    list = serial.tools.list_ports.comports()
    connected = []
    for element in list:
        connected.append(element.device)
    print("Connected COM ports: " + str(connected))

    """ Lists serial port names

        :raises EnvironmentError:
            On unsupported or unknown platforms
        :returns:
            A list of the serial ports available on the system
    """
    if sys.platform.startswith('win'):
    # !attention assumes pyserial 3.x
        ports = ['COM%s' % (i + 1) for i in range(256)]
    elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):
        # this excludes your current terminal "/dev/tty"
        ports = glob.glob('/dev/tty[A-Za-z]*')
    elif sys.platform.startswith('darwin'):
        ports = glob.glob('/dev/tty.*')
    else:
        raise EnvironmentError('Unsupported platform')

    result = []
    for port in ports:
        try:
            s = serial.Serial(port)
            s.close()
            result.append(port)
        except (OSError, serial.SerialException):
            pass
    print("Availible COM Ports: " + str(result))
    return result


def get_distance(lat1, lon1, lat2, lon2):
    R = 6373.0
    dlon = lon2 - lon1
    dlat = lat2 - lat1

    a = math.sin(dlat / 2)**2 + math.cos(lat1) * math.cos(lat2) * math.sin(dlon / 2)**2
    c = 2 * math.atan2(math.sqrt(a), math.sqrt(1 - a))
    distance = c*R
    return distance


def get_location():

    res = requests.get("https://ipinfo.io/")
    lat = res.text.split()[13]
    lat = lat[1:-2]
    lat = lat.split(',')
    lat = float(lat[0])
    long = res.text.split()[13]
    long = long[1:-2]
    long = long.split(',')
    long = float(long[1])

    return lat, long