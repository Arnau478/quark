#!/usr/bin/env python3

import sys
import os
import struct

def create(file_name, dir_name):
    if not os.path.exists(dir_name):
        print(f"ERROR: {dir_name} does not exist")
        exit(1)
    
    out_fd = open(file_name, "wb+")

    def create_file(name, path):
        out_fd.write(bytes([0x01])) # file
        out_fd.write(bytes([len(name)])) # name length
        out_fd.write(name.encode("ascii")) # name
        fd = open(path, "rb")
        file_content = fd.read()
        fd.close()
        out_fd.write(struct.pack("I", len(file_content))) # file size
        out_fd.write(file_content) # file data

    def create_directory(name, path):
        out_fd.write(bytes([0x02])) # directory
        out_fd.write(bytes([len(name)])) # name length
        out_fd.write(name.encode("ascii")) # name
        child_nodes = os.listdir(path)
        out_fd.write(bytes([len(child_nodes)])) # child count
        for child in child_nodes:
            if(os.path.isdir(os.path.join(path, child))):
                create_directory(child, os.path.join(path, child))
            else:
                create_file(child, os.path.join(path, child))
    
    create_directory("", dir_name) # root directory has no name

    out_fd.close()
    

def main():
    if len(sys.argv) <= 1:
        print(f"Usage: {sys.argv[0]} <command>")
        print("Commands:")
        print("  create <file> <directory> | create a QROFS disk image file from a directory")
        print("  extract <file> <directory> | extract the QROFS disk image file contents into a directory")
    elif sys.argv[1] == "create":
        if len(sys.argv) != 4:
            print("Usage: create <file> <directory>")
        else:
            create(sys.argv[2], sys.argv[3])

if(__name__ == "__main__"):
    main()
