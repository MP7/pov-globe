




if __name__=="__main__":
    bytes_read = open("smily.bmp","rb").read()
    for b in bytes_read:
        print str(b)
