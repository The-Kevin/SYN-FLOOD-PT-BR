## SYN SENDER

Este projeto é de caráter didático e não deve ser utilizado para ataques sem a devida autorização prévia do mantenedor ou responsável do ambiente atacado.

## Descrição

Este software é utilizado para enviar um único pacote SYN por vez, partindo da sua máquina atual para o endereço IP especificado como primeiro argumento pela porta especificada no segundo argumento. Idealmente, deve ser utilizado juntamente com algum software de monitoramento de rede (recomendo o tcpdump ou Wireshark) para melhor visualização dos pacotes.

## Requerimentos

O software foi construído utilizando a [API apple](https://opensource.apple.com/), utilizando-se de estruturas xnu-334.34/bsd. Portanto, atualmente não é possível utilizar este software fora de um ambiente MacOS.

Permissões de superusuário.

## Como compilar o projeto

1. Certifique-se de ter o Clang compiler instalado no seu sistema.

2. No terminal, navegue até o diretório onde está localizado o arquivo `Makefile` e o arquivo `tcp_syn_sender.c`.

3. Execute o comando `make` no terminal:

    ```bash
    make
    ```

    Isso compilará o projeto e criará um executável chamado `tcp_syn_sender`.

## Uso

A execução é bastante simples, porém necessita de permissões de superusuário para sua execução, uma vez que pacotes TCP RAW não podem ser construídos sem a devida permissão do sistema operacional.

- O primeiro argumento será o IP (já resolvido) da máquina que irá receber os pacotes.
- O segundo argumento será a porta destino da máquina que irá receber os pacotes.

Um exemplo do comando completo para a execução seria `sudo ./tcp_syn_sender 127.0.0.1 80`.

## Futuro

Algumas melhorias estão sendo planejadas, como:
- O envio de múltiplos pacotes SYN em diferentes processos de execução.
- Melhor interface CLI para o usuário.
- Personalização do protocolo TCP no envio do pacote.
- Suporte a outras plataformas.

## Contribuição

A contribuição a este projeto é livre e espontânea. Qualquer pessoa pode abrir um pull request e contribuir. Sinta-se livre para me enviar feedbacks pelo e-mail kevin.almeida1111.ka@gmail.com :)

