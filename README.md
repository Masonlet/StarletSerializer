# StarletSerializer
A lightweight serialization library for **Starlet** projects to handle both data reading and writing, designed with OpenGL engines in mind.

## Features
- **Logging Utils**
    - `error` and `debug` for console logging

- **File I/O**
    - **Parser** - `loadFile`, `loadBinaryFile`, both with basic safety checks
    - **Writer** - `saveScene`, for serializing scenes and components

- **Parser Utils**
    - Whitespace & line skipping helpers: `skipWhitespace`, `skipToNextLine`, `trimEOL`
    - Typed parsers: `parseUINT`, `parseBool`, `parseFloat`, `parseVec2f`, `parseVec3`, `parseVec3`
    - Token parsing with `parseToken`
    - Error-safe macros `PARSE_OR` and `PARSE_STRING_OR`

## Using as a Dependency
```cmake
include(FetchContent)

FetchContent_Declare(StarletSerializer GIT_REPOSITORY https://github.com/Masonlet/StarletSerializer.git GIT_TAG main)
FetchContent_MakeAvailable(StarletSerializer)

target_link_libraries(YourAppName PRIVATE StarletSerializer)
```
