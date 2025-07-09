# 🤝 Contributing to HackLab

Thanks for your interest in contributing to **HackLab**, a Bash-based terminal enumeration toolkit developed by [**Mohammad Al Shahin**](https://www.linkedin.com/in/mohammadalshahin). Your contributions — big or small — help improve this tool for the entire cybersecurity community.

---

## 📦 Getting Started

1. **Fork this repository**  
   Click the **Fork** button on the top-right of the GitHub repo page.

2. **Clone your fork**
   ```bash
   git clone https://github.com/malshahin/hacklab.git
   cd hacklab
   ```
3. **Create a new branch**
   ```bash
   git checkout -b your-feature-name
   ```
4. **Make your changes**
    - Add new features or modules
    - Fix bugs or errors
    - Improve user interaction or performance
    - Update packaging or documentation

5. **Test your changes**
    - Run the script: bash hacklab.sh
    - If you're working with .deb packaging, rebuild with:

         ```bash
         dpkg-deb --build --root-owner-group hacklab_1.0-1_all/
         ```
   
7. **Commit your changes**
   
   ```bash
   git add .
   git commit -m "Add: [feature/fix description]"
   ```

7. **Push your branch**
   
   ```bash
   git push origin your-feature-name
   ```
- Create a Pull Request
- Go to your fork on GitHub
- Click "Compare & pull request"
- Add a clear title and explain your changes


## 💡 What You Can Contribute
- 🛠️ Enumeration modules (e.g., new tools or techniques)
- 🐞 Bug fixes and compatibility improvements
- 📝 Better documentation or help messages
- 🌐 Localization or translation
- 🧪 Script refactoring or optimization
- 📦 Packaging updates or install automation


## 📌 Guidelines
- Write clean and readable Bash code
- Keep it modular — one function/module per task
- Use comments to explain non-obvious parts
- Don't include destructive commands (e.g., rm -rf)
- Make sure it works on major Linux distros

  
## 🛡 Code of Conduct
Please follow our [Code of Conduct](.github/CODE_OF_CONDUCT.md).

We expect all contributors to behave respectfully, collaboratively, and professionally.


## 🙌 Credits

This project is maintained by:

**Mohammad Al Shahin**  
📧 [ceo@m-alshahin.com](mailto:ceo@m-alshahin.com)  
🔗 [GitHub Profile](https://github.com/malshahin)

Thank you for helping make **HackLab** better for the cybersecurity and ethical hacking community! 🚀
