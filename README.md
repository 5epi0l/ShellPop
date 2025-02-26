<h1 align="center" id="title">ShellPop</h1>

<p align="center"><img src="https://i.imgur.com/z6MPqGL.png"></p>

<p id="description">ShellPop is a lightweight and versatile reverse shell generator and listener implemented entirely in C++. Designed to simplify the process of generating reverse shells ShellPop offers a straightforward and user-friendly interface for creating customized shells tailored to various scenarios.</p>

<p align="center"><img src="https://img.shields.io/badge/C%2B%2B-red" alt="shields"><img src="https://img.shields.io/badge/v1.0.0-blue" alt="shields"><img src="https://img.shields.io/badge/Maintained%3F-yes-blue" alt="shields"><img src="https://img.shields.io/badge/Developed%20On-Manjaro-Red" alt="shields"></p>



 
<h2>🧐 Features</h2>

Here're some of the project's best features:

*   Ease of Use: With a minimalistic design ShellPop prioritizes simplicity and ease of use. Generate reverse shells quickly and efficiently with just a few simple commands.
*   Flexibility: ShellPop supports a range of options allowing users to customize generated shells based on their specific requirements. Whether you need a Python Bash or other types of reverse shells ShellPop has you covered.
*   Listener Integration: ShellPop includes an optional feature to start an inbuilt listener using Netcat. After generating a reverse shell, users have the option to initiate the listener directly from the program.
   

<h2>🛠️ Installation Steps:</h2>

<p>1. Clone the Repository:</p>

```
git clone https://github.com/EF3X0S/ShellPop.git
```

<p>2. Navigate to the ShellPop Directory:</p>

```
cd ShellPop
```
<p>4. Compile the binary:</p>

```
g++ shellPop.cpp -o ShellPop

```

<p>3. Provide Execution Permissions:</p>

```
chmod +x ShellPop
```

<p>4. Run ShellPop:</p>

```
./ShellPop
```
<h1>↔️Alternative:</h1> 
<p>Download the latest binary from <a href="https://github.com/EF3X0S/ShellPop/releases/tag/v1.0.0">release</a></p>

<h2>🍰 Contribution Guidelines:</h2>

Thank you for considering contributing to ShellPop! Contributions are welcomed and encouraged. Follow the existing coding style and conventions used in the project. If in doubt refer to the existing codebase. If you encounter any issues or bugs please open a GitHub issue and provide detailed information about the problem including steps to reproduce.

  
  
<h2>💻 Built with</h2>

Technologies used in the project:

*   C++

<h2>🔒 SSL/TLS Encrypted Shells</h2>

ShellPop now supports SSL/TLS encrypted reverse shells for enhanced security. The following shells are available:
* Python SSL
* Ruby SSL
* Node.js SSL

To use SSL/TLS encrypted shells:

<p>1. Generate a self-signed certificate (one-time setup):</p>

```
openssl req -x509 -newkey rsa:4096 -keyout key.pem -out cert.pem -days 365 -nodes
```

<p>2. For Python/Ruby shells, start the listener with:</p>

```
openssl s_server -quiet -key key.pem -cert cert.pem -port <PORT>
```

<p>3. For Node.js shells, use socat as the listener:</p>

```
socat openssl-listen:<PORT>,cert=cert.pem,verify=0 stdout
```

<p>4. Generate and use your SSL shell from ShellPop as normal, selecting one of the SSL options from the menu.</p>


