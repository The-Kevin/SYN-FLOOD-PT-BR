#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void error(char* msg) {
  perror(("Error: %s\n", msg));
  exit(EXIT_FAILURE);
}

//ONLY APPLE
void defineTCPHeader(struct tcphdr* tcp, uint16_t port, unsigned short checksum){
    //https://opensource.apple.com/source/xnu/xnu-344.34/bsd/netinet/tcp.h.auto.html
    //
    //verify a best way to get source port from the kernel
    unsigned short sourcePort = 50689;
    tcp->th_ack = 0;
    tcp->th_sport = sourcePort;
    tcp->th_dport = port;
    tcp->th_flags = TH_SYN; 
    tcp->th_off = sizeof(struct tcphdr) / 4; // Tamanho do cabeçalho TCP em  32 bits
    tcp->th_seq = 0;
    tcp->th_sum = checksum;
    tcp->th_urp = 0;
    tcp->th_win = htons(65535); // this value was getted from wireshark sniff by empirically experience haha
}

int main(int argc, char* argv[]){

    int fd;
    struct sockaddr_in addr;
    struct tcphdr *tcpHeader;
    fd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
    if(fd == -1){
        error("Erro! Impossivel criar socket de conexao!");
    }


    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    addr.sin_port = htons(atoi(argv[2]));                                     
    defineTCPHeader(tcpHeader, atoi(argv[2]), 0);                                   

    int pack = sendto(fd, tcpHeader, sizeof(struct tcphdr), 0, (struct sockaddr*)&addr, sizeof(addr));

   if(pack == -1){
        error("Erro: Nao foi possivel enviar o SYN!");
   } 

   printf("Pacote SYN enviado com sucesso!");
    
    close(fd);

    
    return 0;
}
