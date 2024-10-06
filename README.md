# Web2Pdf

Web2Pdf is a simple command-line tool that parses a given webpage and converts it into a PDF document containing all the links present on that webpage. This project utilizes `libcurl` for fetching webpage data and `wkhtmltopdf` for converting HTML content to PDF format.

## Table of Contents

- [Features](#features)
- [Getting Started](#getting-started)
- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Usage](#usage)

## Features

- **Fetch Webpage**: Download and parse any given webpage.
- **Link Extraction**: Automatically extract all hyperlinks from the webpage.
- **PDF Generation**: Convert the extracted links into a well-formatted PDF document.

## Getting Started

### Prerequisites

Before you begin, ensure you have met the following requirements:

- **C++ Compiler**: Make sure G++ is installed on your system.
- **CMake**: Required for building the project.
- **libcurl**: A library for making HTTP requests.
- **wkhtmltopdf**: A tool to convert HTML to PDF.

### Installation

Follow these steps to set up the project on your local machine:

```bash
# Clone the repository
git clone https://github.com/thehashimq/web2pdf
# Navigate into the project directory
cd web2pdf
# Create a build directory and navigate into it
mkdir build && cd build
# Run CMake to configure the project
cmake ..
# Build the project
make
```

### Usage

To Convert a webpage to pdf , use the following command.

```bash
./build/web2pdf <URL>
```

Example:

```bash
./build/web2pdf https://example.com/

```
