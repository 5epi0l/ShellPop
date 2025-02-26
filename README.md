<h1 align="center" id="title">ShellPop</h1>

<p align="center"><img src="https://i.imgur.com/z6MPqGL.png"></p>

<p id="description">ShellPop is a lightweight and versatile reverse shell generator and listener implemented in Python. Designed to simplify the process of generating reverse shells, ShellPop offers a straightforward and user-friendly interface for creating customized shells tailored to various scenarios.</p>

<p align="center"><img src="https://img.shields.io/badge/Python-3.6+-blue" alt="shields"><img src="https://img.shields.io/badge/v1.0.0-blue" alt="shields"><img src="https://img.shields.io/badge/Maintained%3F-yes-blue" alt="shields"><img src="https://img.shields.io/badge/Developed%20On-Manjaro-Red" alt="shields"></p>

<h2>🧐 Features</h2>

Here're some of the project's best features:

*   Ease of Use: With a minimalistic design, ShellPop prioritizes simplicity and ease of use. Generate reverse shells quickly and efficiently with just a few simple commands.
*   Multiple Shell Types: Supports Python, Netcat, Bash, PHP, Ruby, Perl, PowerShell, and Node.js reverse shells.
*   SSL/TLS Support: Includes encrypted variants for Python, Ruby, and Node.js shells for enhanced security.
*   Integrated Listener: Features an optional built-in Netcat listener for immediate connection testing.
*   Color-Coded Output: Intuitive color-coded interface for better readability and user experience.

<h2>🛠️ Installation Steps:</h2>

<p>1. Clone the Repository:</p>

```
git clone https://github.com/EF3X0S/ShellPop.git
```

<p>2. Navigate to the ShellPop Directory:</p>

```
cd ShellPop
```

<p>3. Provide Execution Permissions:</p>

```
chmod +x shellpop.py
```

<p>4. Run ShellPop:</p>

```
python3 shellpop.py
```

<h2>📋 Requirements</h2>

* Python 3.6 or higher
* Netcat (for listener functionality)

<h2>🍰 Contribution Guidelines:</h2>

Thank you for considering contributing to ShellPop! Contributions are welcomed and encouraged. Follow the existing coding style and conventions used in the project. If in doubt, refer to the existing codebase. If you encounter any issues or bugs, please open a GitHub issue and provide detailed information about the problem, including steps to reproduce.

<h2>💻 Built with</h2>

Technologies used in the project:

*   Python 3
*   Standard Python libraries (no external dependencies)

<h2>🔒 SSL/TLS Encrypted Shells</h2>

ShellPop supports SSL/TLS encrypted reverse shells for enhanced security. The following shells are available:
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


