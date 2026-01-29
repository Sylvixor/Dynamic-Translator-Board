from PyAccessPoint import pyaccesspoint
import time

access_point = pyaccesspoint.AccessPoint(wlan = 'wlp0s20f3')


if __name__ == '__main__':
    access_point.start()
    while(True):
        time.sleep(1)