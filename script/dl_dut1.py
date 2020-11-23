import iers_tools as it

import re
import xml.etree.ElementTree as ET


server = "ftp.iers.org"
directory = "products/eop/bulletind/xml"
prefix = "ftp://" + server + "/" + directory + "/"
bulletinRe = r'bulletind-\d+.xml'
dataName = "dut1"

def parseBulletins(bulletins):
    data = dict()
    for bulletin in bulletins:
        bulletin = re.sub(' xmlns="[^"]+"', '', bulletin, count=1)
        dataNode = ET.fromstring(bulletin)[0]
        data[dataNode.find('startDate').text] = float(dataNode.find('DUT1').text)

    return data

def download():
    bulletinUrls = it.getBulletinUrls(server, directory, bulletinRe)
    bulletins = it.retrieveBulletins(bulletinUrls, prefix, bulletinRe)
    lsData = parseBulletins(bulletins)
    csvFile = open("../data/" + dataName + ".csv", "w")
    it.toCsv(lsData, csvFile)
    csvFile.close()