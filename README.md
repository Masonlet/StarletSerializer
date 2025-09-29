# StarletParser
A lightweight parsing library for **Starlet** projects designed with OpenGL engines in mind.

## Features
- **Logging Utils**
    - `error` and `debug` for console logging

- **File Parsers**
    -`loadFile`, `loadBinaryFile`, both with basic safety checks

- **Parser Utils**
    - Whitespace & line skipping helpers: `skipWhitespace`, `skipToNextLine`, `trimEOL`
    - Typed parsers: `parseUINT`, `parseBool`, `parseFloat`, `parseVec2f`, `parseVec3`, `parseVec3`
    - Token parsing with `parseToken`
    - Error-safe macros `PARSE_OR` and `PARSE_STRING_OR`

## Using as a Dependency
```cmake
include(FetchContent)

FetchContent_Declare(StarletParsers GIT_REPOSITORY https://github.com/Masonlet/StarletParser.git GIT_TAG main)
FetchContent_MakeAvailable(StarletParser)

target_link_libraries(YourAppName PRIVATE StarletParser)
```
