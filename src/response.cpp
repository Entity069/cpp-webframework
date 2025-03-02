#include "../include/response.h"
#include <sstream>

namespace MicroWeb {

Response::Response() : status_code(200), content_type(MIME_JSON) {
}

void Response::setStatus(int code) {
    status_code = code;
}

void Response::setBody(const std::string& b) {
    body = b;
}

void Response::setContentType(const std::string& type) {
    content_type = type;
}

void Response::addHeader(const std::string& key, const std::string& value) {
    headers[key] = value;
}

void Response::addCookie(const std::string& key, const std::string& value) {
    cookies[key] = value;
}

void Response::redirect(const std::string& location, int status_code) {
    if (status_code == HTTP_FOUND || status_code == HTTP_MOVED_PERMANENTLY) {
        status_code = HTTP_FOUND;
    }
    setStatus(status_code);
    addHeader("Location", location);
    text("Moved permanently. Redirecting to " + location);
}

void Response::json(const nlohmann::json& data) {
    setContentType(MIME_JSON);
    body = data.dump();
}

void Response::html(const std::string& html_content) {
    setContentType(MIME_HTML);
    body = html_content;
}

void Response::text(const std::string& text_content) {
    setContentType(MIME_PLAIN);
    body = text_content;
}

std::string Response::serialize() const {
    std::ostringstream response_stream;

    response_stream << "HTTP/2 " << status_code << " ";
    switch (status_code) {
        case HTTP_OK: response_stream << "OK"; break;
        case HTTP_MOVED_PERMANENTLY: response_stream << "Moved Permanently"; break;
        case HTTP_FOUND: response_stream << "Found"; break;
        case HTTP_BAD_REQUEST: response_stream << "Bad Request"; break;
        case HTTP_NOT_FOUND: response_stream << "Not Found"; break;
        case HTTP_INTERNAL_SERVER_ERROR: response_stream << "Internal Server Error"; break;
        default: response_stream << "Unknown Status"; break;
    }
    response_stream << "\r\n";

    // Headers
    response_stream << "Content-Type: " << content_type << "\r\n";
    response_stream << "Content-Length: " << body.length() << "\r\n";
    
    // Additional headers
    for (const auto& [key, value] : headers) {
        response_stream << key << ": " << value << "\r\n";
    }

    // cookies
    for (const auto& [key, value] : cookies) {
        response_stream << "Set-Cookie: " << key << "=" << value << "; Path=/\r\n";
    }

    // eoh
    response_stream << "\r\n";

    // body
    response_stream << body;

    return response_stream.str();
}

int Response::getStatusCode() const {
    return status_code;
}

std::string Response::getBody() const {
    return body;
}

Response::~Response() {
    headers.clear();
    cookies.clear();
}

} // namespace MicroWeb