# CPP-Webframework
A very very minimal micro web framework written in C++ (not usable in production, obv).

## Introduction and Motivation
It is a very minimalistic micro-web framework similar to [flask](https://github.com/pallets/flask) but in entirely in C++. It uses `fork()` to make child process to handle concurrent connections.

Motivation: Because it can be made.

## File Structure

```
cpp-webframework/
├─ LICENSE
├─ README.md
├─ TODO
├─ include/
│  ├─ constants.h
│  ├─ encode.h
│  ├─ inja/
│  │  └─ inja.hpp
│  ├─ logger.h
│  ├─ middleware.h
│  ├─ nlohmann/
│  │  ├─ json.hpp
│  │  └─ json_fwd.hpp
│  ├─ request.h
│  ├─ response.h
│  ├─ router.h
│  └─ server.h
├─ main.cpp
└─ src/
   ├─ logger.cpp
   ├─ middleware.cpp
   ├─ request.cpp
   ├─ response.cpp
   ├─ router.cpp
   └─ server.cpp
```

# Dependencies

It currently has mainly two dependencies:
- [nlohmann/json](https://github.com/nlohmann/json) - for interacting JSON data format
- [inja](https://github.com/pantor/inja) - for templating

Thank you [arthurafarias](https://github.com/arthurafarias/) for his [wonderful gist](https://gist.github.com/arthurafarias/56fec2cd49a32f374c02d1df2b6c350f) which helped in encoding/decoding URI components.

# Usage

Make a server object and define your routes in `main.cpp` like this:

```cpp
Server server;

// Basic route
server.route("GET", "/hello", [](Request& req, Response& res) {
    res.setContentType(MIME_JSON);
    json response = {
        {"message", "Hello, World!"},
        {"status", "success"}
    };
    res.json(response);
});
```

Accessing `https://localhost:8080/hello` will give :
```json
{"message":"Hello, World!","status":"success"}
```

Then compile:
```bash
g++ main.cpp src/*.cpp -o web
```

Then run the output binary:
```bash
./web
```

Currently this only supports static file serving and returning data via JSON (which makes it somewhat usable for making very basic APIs). It also supports serving html pages with contextual data with [inja](https://github.com/pantor/inja). 

# TODO
- Add redirect functionality
- Add support for file upload
- Add support for authentication methods (currently the authentication middleware doesn't work as expected)
- Choose a nice name for the repo

# License
The code is released under MIT License. See [LICENSE](./LICENSE).
