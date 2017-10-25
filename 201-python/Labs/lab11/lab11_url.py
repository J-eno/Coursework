# File: lab11_math.py
# Author: Joel Okpara
# Date:
# Section: 4
# E-mail:
# Description:

import urllib.request


def main():
    url = urllib.request.urlopen("http://www.cnn.com")
    contents = url.read()
    print(contents)
    print(len(contents))


main()
