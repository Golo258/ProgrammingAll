

class StringPlayground:
    
    
    """
        str.partition()
            dzieli stringa w przypadku wystąpienia separatora
            zwraca krotke
            (tekst_przed, separator, tekst_po) = str.partition("seperator")
    """
    def partition_usage():
        text = 'CONFIG_FILE_PATH  : \x1b[0;32m/home/user/config.ini\x1b[0m'
        print(text.partition(':')) # ('CONFIG_FILE_PATH  ', ':', ' \x1b[0;32m/home/user/config..ini\x1b[0m')
        

playground = StringPlayground()
playground.partition_usage()