import os
import re
import ftplib
import urllib.request
import time
import csv


def getCached(bulletinRe):
    if not os.path.exists("cache"):
        os.mkdir("cache")
    fileList = os.listdir("cache")
    return [re.search(bulletinRe, x).group(0) for x in fileList if re.search(bulletinRe, x)]

def getBulletinUrls(server, directory, bulletinRe):
    ftp = ftplib.FTP(server)
    ftp.login("anonymous", "ftplib-example-1")
    ftp.cwd(directory)
    fileList = []
    ftp.dir(fileList.append)

    filtered = []
    for line in fileList:
        m =  re.search(bulletinRe, line) 
        if m:
            filtered.append(m.group(0))

    ftp.quit()
    return filtered

def retrieveBulletins(bulletinUrls, prefix, bulletinRe):
    bulletins = []
    for cached in getCached(bulletinRe):
        bulletinUrls = [x for x in bulletinUrls if not re.search(cached, x)]
        bulletins.append(open("cache/" + cached, "r").read())

    for bulletin in bulletinUrls:
        urllib.request.urlretrieve(prefix + bulletin, "cache/" + bulletin)
        bulletins.append(open("cache/" + bulletin, "r").read())
        time.sleep(0.3)
    return bulletins

def toCsv(data, file):
    w = csv.writer(file)
    for key in sorted(data.keys()):
        w.writerow([key, data[key]])

