#!/usr/bin/python3

import os
import struct

def remove_bom(file_name):
    data = ""
    with open(i,"rb") as f:
        data = f.read()
        if(len(data) >= 3 and data[:3] == b'\xef\xbb\xbf'):
            data = data[3:]

    if(data != ""):
        with open(i,"wb") as f:
            f.write(data)

def update_tab_to_space(filename):
    data = ""
    with open(i,"r") as f:
        data = f.read()
        data = data.replace("\t","    ")

    with open(i,"w") as f:
        f.write(data)

def update_line_break(filename):
    data = ""
    with open(i,"r") as f:
        data = f.read()
        data = data.replace("\r\n","\n")

    with open(i,"w") as f:
        f.write(data)

path,_= os.path.split(os.path.abspath(__file__))
src_path = os.path.join(os.path.split(path)[0],"src")

file_l = []

for root, dirs, files in os.walk(src_path, topdown=False):
    for name in files:
        file_name = os.path.join(root, name)
        if(file_name.endswith(".cpp") or file_name.endswith(".h") or file_name.endswith(".hpp")):
            file_l.append(file_name)

for i in file_l:
    print(i)
    remove_bom(i)
    update_tab_to_space(i)
    update_line_break(i)
    print("="*80)
