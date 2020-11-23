import iers_tools as it

import re
import xml.etree.ElementTree as ET


server = "ftp.iers.org"
directory = "products/eop/bulletinc/xml"
prefix = "ftp://" + server + "/" + directory + "/"
bulletinRe = r'bulletinc-\d+.xml'
dataName = "leap_seconds"

def parseBulletins(bulletins):
    data = dict()
    for bulletin in bulletins:
        bulletin = re.sub(' xmlns="[^"]+"', '', bulletin, count=1)
        for UT in ET.fromstring(bulletin)[0].iterfind('UT'):
            data[UT.find('startDate').text] = int(UT.find('UTC_TAI').text)

    return data

def download():
    bulletinUrls = it.getBulletinUrls(server, directory, bulletinRe)
    bulletins = it.retrieveBulletins(bulletinUrls, prefix, bulletinRe)
    lsData = parseBulletins(bulletins)
    csvFile = open("../data/" + dataName + ".csv", "w")
    it.toCsv(lsData, csvFile)
    csvFile.close()