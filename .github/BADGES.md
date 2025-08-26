# GitHub Actions Badges

## Available Badges

Add these badges to your README.md to show the CI/CD status:

### Build Status
```markdown
![CI/CD Pipeline](https://github.com/YOUR_USERNAME/cpp_features/workflows/CI/CD%20Pipeline/badge.svg)
```

### Security Status  
```markdown
![Security & Dependencies](https://github.com/YOUR_USERNAME/cpp_features/workflows/Security%20&%20Dependencies/badge.svg)
```

### Release Status
```markdown
![Release](https://github.com/YOUR_USERNAME/cpp_features/workflows/Release/badge.svg)
```

### Documentation
```markdown
![Deploy Documentation](https://github.com/YOUR_USERNAME/cpp_features/workflows/Deploy%20Documentation/badge.svg)
```

### Platform Support
```markdown
![Windows](https://img.shields.io/badge/Windows-MSVC%202022+-blue?logo=windows)
![Linux](https://img.shields.io/badge/Linux-GCC%2012%2B%20%7C%20Clang%2015%2B-green?logo=linux)
![macOS](https://img.shields.io/badge/macOS-Clang-orange?logo=apple)
```

### C++ Standards
```markdown
![C++11](https://img.shields.io/badge/C%2B%2B-11-blue)
![C++14](https://img.shields.io/badge/C%2B%2B-14-blue)
![C++17](https://img.shields.io/badge/C%2B%2B-17-blue)
![C++20](https://img.shields.io/badge/C%2B%2B-20-blue)
![C++23](https://img.shields.io/badge/C%2B%2B-23-blue)
![C++26](https://img.shields.io/badge/C%2B%2B-26%20(experimental)-orange)
```

### Build System
```markdown
![xmake](https://img.shields.io/badge/build-xmake-green?logo=cmake)
```

### Code Quality
```markdown
![Code Style](https://img.shields.io/badge/code%20style-Google-brightgreen)
![License](https://img.shields.io/github/license/YOUR_USERNAME/cpp_features)
```

### Latest Release
```markdown
![GitHub release (latest by date)](https://img.shields.io/github/v/release/YOUR_USERNAME/cpp_features)
![GitHub Release Date](https://img.shields.io/github/release-date/YOUR_USERNAME/cpp_features)
```

## Complete Badge Section for README

```markdown
# Modern C++ Features Showcase

![CI/CD Pipeline](https://github.com/YOUR_USERNAME/cpp_features/workflows/CI/CD%20Pipeline/badge.svg)
![Security & Dependencies](https://github.com/YOUR_USERNAME/cpp_features/workflows/Security%20&%20Dependencies/badge.svg)
![Release](https://github.com/YOUR_USERNAME/cpp_features/workflows/Release/badge.svg)
![GitHub release (latest by date)](https://img.shields.io/github/v/release/YOUR_USERNAME/cpp_features)

![C++11](https://img.shields.io/badge/C%2B%2B-11-blue)
![C++14](https://img.shields.io/badge/C%2B%2B-14-blue)
![C++17](https://img.shields.io/badge/C%2B%2B-17-blue)
![C++20](https://img.shields.io/badge/C%2B%2B-20-blue)
![C++23](https://img.shields.io/badge/C%2B%2B-23-blue)
![C++26](https://img.shields.io/badge/C%2B%2B-26%20(experimental)-orange)

![Windows](https://img.shields.io/badge/Windows-MSVC%202022+-blue?logo=windows)
![Linux](https://img.shields.io/badge/Linux-GCC%2012%2B%20%7C%20Clang%2015%2B-green?logo=linux)
![macOS](https://img.shields.io/badge/macOS-Clang-orange?logo=apple)

![xmake](https://img.shields.io/badge/build-xmake-green?logo=cmake)
![Code Style](https://img.shields.io/badge/code%20style-Google-brightgreen)
![License](https://img.shields.io/github/license/YOUR_USERNAME/cpp_features)
```

## Instructions

1. Replace `YOUR_USERNAME` with your actual GitHub username
2. Replace `cpp_features` with your repository name if different
3. Add the badge section to the top of your README.md
4. Commit and push to see the badges in action

## Custom Badge Colors

You can customize badge colors using:
- `brightgreen` for success/good status
- `green` for normal/ok status  
- `yellow` for warning status
- `orange` for caution status
- `red` for error/critical status
- `blue` for informational status
- `lightgrey` for neutral status

## Badge Update Frequency

Badges update automatically when:
- Workflows run (on push/PR)
- Releases are created
- Repository settings change