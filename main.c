#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void error(char* msg) {
  perror(("\nError: %s\n", msg));
  exit(EXIT_FAILURE);
}

unsigned short csum(unsigned short *ptr, int nbytes) { // thank you AI 🤙
    register long sum;
    unsigned short oddbyte;
    register short answer;

    sum = 0;
    while (nbytes > 1) {
        sum += *ptr++;
        nbytes -= 2;
    }

    if (nbytes == 1) {
        oddbyte = 0;
        *((u_char *)&oddbyte) = *(u_char *)ptr;
        sum += oddbyte;
    }

    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);
    answer = (short)~sum;

    return answer;
}

int main(int argc, char* argv[]){
    int fd;
    char packet[sizeof(struct tcphdr)];
    memset(packet, 0, sizeof(struct tcphdr));

    struct tcphdr* tcpHeader;
    struct sockaddr_in addr;
    int one = 1;

    fd = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
    if(fd == -1) error("Erro ao criar socket!");


    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(argv[1]);


    //https://opensource.apple.com/source/xnu/xnu-344.34/bsd/netinet/tcp.h.auto.html
    // yes agree that "th_*" is a shit name, complain to apple
     tcpHeader = (struct tcphdr*)packet;
     //TODO try find best way to get the source port
     tcpHeader->th_sport = htons(12345);
     tcpHeader->th_dport = htons(atoi(argv[2])); // im not sure if can work in all cases because if uint16_t not signed int
     tcpHeader->th_seq = 0;
     tcpHeader->th_ack = 0;
     tcpHeader->th_off = 5; //32 bits;
     tcpHeader->th_flags = TH_SYN;
     tcpHeader->th_win = htons(5840); //this value is not correcly, i just get a sample in wireshark haha :D
     tcpHeader->th_sum = 0; // this will be calculate later
 
     //calculate the checksum
     tcpHeader->th_sum = csum((unsigned short*)packet, sizeof(struct tcphdr));

    int ipack = sendto(fd, packet,(sizeof(struct ip) + sizeof(struct tcphdr)), 0, (struct sockaddr*)&addr, sizeof(addr));

    if(ipack == -1){
        error("Erro ao enviar o pacote SYN!");
    }
    
    close(fd);
    return 0;
}
