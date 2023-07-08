#!/usr/bin/python3
# @Мартин.
import textwrap,argparse,sys,socket,os
version = "@Мартин. Night_of_19 Tool V1.0.0"
title='''
************************************************************************************
<免责声明>:本工具仅供学习实验使用,请勿用于非法用途,否则自行承担相应的法律责任
<Disclaimer>:This tool is only for learning and experiment. Do not use it for illegal purposes, or you will bear corresponding legal responsibilities
[PS:] Night_of_19 是一款内网近源渗透工具,你需要搭配Arduino使用,难度较大所以请认真阅读手册再使用工具
[PS:] Night_ Of_ 19 is an intranet near source penetration tool that you need to use with Arduino, which is quite challenging. Therefore, please read the manual carefully before using the tool
************************************************************************************'''
logo=f'''
 __    __  __            __          __                       ______           __     ______  
/  \  /  |/  |          /  |        /  |                     /      \        _/  |   /      \ 
$$  \ $$ |$$/   ______  $$ |____   _$$ |_           ______  /$$$$$$  |      / $$ |  /$$$$$$  |
$$$  \$$ |/  | /      \ $$      \ / $$   |         /      \ $$ |_ $$/       $$$$ |  $$ \__$$ |
$$$$  $$ |$$ |/$$$$$$  |$$$$$$$  |$$$$$$/         /$$$$$$  |$$   |            $$ |  $$    $$ |
$$ $$ $$ |$$ |$$ |  $$ |$$ |  $$ |  $$ | __       $$ |  $$ |$$$$/             $$ |   $$$$$$$ |
$$ |$$$$ |$$ |$$ \__$$ |$$ |  $$ |  $$ |/  |      $$ \__$$ |$$ |             _$$ |_ /  \__$$ |
$$ | $$$ |$$ |$$    $$ |$$ |  $$ |  $$  $$/       $$    $$/ $$ |            / $$   |$$    $$/ 
$$/   $$/ $$/  $$$$$$$ |$$/   $$/    $$$$/         $$$$$$/  $$/             $$$$$$/  $$$$$$/  
              /  \__$$ |                                                                      
              $$    $$/                           {version}                                          
               $$$$$$/                              {title}                                                                                              
'''


CONF = '''
[+] ---------------------------------------
| COM:{}\tBaudrate:{}\tBytesize:{}
| Parity:{}\tStopbits:{}\tTimeout:{}
| Rtscts:{}\tDsrdtr:{}\tXonxoff:{}
| WriteTimeout:{}\tInterCharTimeout:{}
 -------------------------------------------
'''

class Main():
    def __init__(self,args):
        self.COM = args.COM
        self.Baud = args.Baud

    def Server(self):
        try:
            ser = serial.Serial(self.COM, self.Baud, timeout=0.5)
        except:
            print("[!]COM Interface exception")
            return False
        else:
            print(CONF.format(ser.name,ser.baudrate,ser.bytesize,ser.parity,ser.stopbits,ser.timeout,ser.writeTimeout,\
                ser.xonxoff,ser.rtscts,ser.dsrdtr,ser.interCharTimeout))
            print("[+]Equipment monitoring")
            while True:
                try:
                    print(ser.readline().decode())
                except:
                    print("[-]Exit")
                    break


    def run(self):
        if self.COM:
            self.Server()
        else:
            print("[!]You must select a valid COM port!")


def main():
    print(logo)
    parser = argparse.ArgumentParser(
        formatter_class=argparse.RawTextHelpFormatter,
        epilog=textwrap.dedent('''
        Example:
            author-Github==>https://github.com/MartinxMax
        Basic usage:
            python3 {N19} -c (COM13) -b (Baud rate) #You must fill in the COM port, and then you can not fill in the baud rate, which is 9600 by default
            '''.format(N19=sys.argv[0]
                       )))
    parser.add_argument('-c', '--COM', default=None, help='COM Port')
    parser.add_argument('-b', '--Baud', type=int, default=9600, help='Baud rate')
    Main(parser.parse_args()).run()


if __name__ == '__main__':
    main()