#include "../class/Response.hpp"
#include "../include/include.hpp"

//----- transcation -----------------------------------------------------------
int ft::safeRecv(int fd, char *buf, int size) {
  // std::cout << GRY << "Debug: safeRecv\n" << DFT;
  int recv_len;

  signal(SIGPIPE, SIG_IGN);
  if ((recv_len = recv(fd, buf, size, 0)) == -1) {
    std::cerr << RED << "Error: Transaction: recv() error\n" << DFT;
  }
  signal(SIGPIPE, SIG_DFL);
  return recv_len;
}

int ft::safeSend(int fd, Response &response) {
  // std::cout << GRY << "Debug: safeSend\n";
  int send_len;

  signal(SIGPIPE, SIG_IGN);
  if ((send_len = send(fd, response.getResponseMsg(),
                       response.getResponseMsgSize(), 0)) == -1) {
    std::cerr << RED << "Error: Transaction: send() error\n" << DFT;
  }
  signal(SIGPIPE, SIG_DFL);
  return send_len;
}

size_t ft::safeFread(char *buf, int size, int count, FILE *file_ptr) {
  // std::cout << GRY << "Debug: safeFread\n" << DFT;

  signal(SIGPIPE, SIG_IGN);
  size_t read_len = std::fread(buf, size, count, file_ptr);
  if (std::ferror(file_ptr)) {
    std::cerr << RED << "Error: Transaction: file fread() error\n" << DFT;
  }
  signal(SIGPIPE, SIG_DFL);
  return read_len;
}

size_t ft::safeFwrite(char *buf, int size, int count, FILE *file_ptr) {
  // std::cout << GRY << "Debug: safeFwrite\n" << DFT;

  signal(SIGPIPE, SIG_IGN);
  size_t write_len = std::fwrite(buf, size, count, file_ptr);
  if (std::ferror(file_ptr)) {
    std::cerr << RED << "Error: Transaction: file fwrite() error\n" << DFT;
  }
  signal(SIGPIPE, SIG_DFL);
  return write_len;
}

std::FILE *ft::safeFopen(const char *filename, const char *mode) {
  // std::cout << GRY << "Debug: safeFopen\n" << DFT;
  std::FILE *fp;

  // fopen 으로 읽으면 fp 의 stream 버퍼를 1024 로 설정한다.
  if ((fp = std::fopen(filename, mode)) == NULL) {
    std::cerr << RED << "Error: Transaction: file fopen() error\n" << DFT;
  }

  // 1024 로 설정된 fp 의 stream 을 F_STREAM_SIZE 크기로 설정한다.
  std::setvbuf(fp, 0, _IONBF, F_STREAM_SIZE);
  return fp;
}