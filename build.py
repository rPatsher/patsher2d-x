from os import *
from resources import *


import logging
import traceback
def _build_() -> None:
    #! TODO : List array to define the c libs
    LIBS : list = [
        'thirdparty/ini/iniparser.c',
        'thirdparty/ini/iniparser.h',
        'thirdparty/ini/dictionary.c',
        'thirdparty/ini/dictionary.h'
    ]

    LIST = list
    print(LIBS, LIST)
    logging.warning(LIBS)

if __name__ == '__main__':
    _build_()




