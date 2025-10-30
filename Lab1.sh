gedit Lab1.sh
#!/bin/bash
# ============================================
# IPC Message Queue – 10 առաջադրանքների ավտոմատացում
# ============================================

echo "============================================"
echo " System V Message Queue – Փորձնական առաջադրանքներ"
echo "============================================"
echo

# Քայլ 1․ Ստեղծում ենք անհրաժեշտ C ֆայլերը
echo "[1/10] Ստեղծվում են .c ֆայլերը..."

# ---------- message_create.c ----------
cat << 'EOF' > message_create.c
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

int main() {
    key_t key;
    int msgid;

    // Ստեղծում ենք unique key
    key = ftok("progfile", 65);

    // Ստեղծում ենք message queue
    msgid = msgget(key, 0666 | IPC_CREAT);

    struct msg_buffer message;
    message.msg_type = 20;
    strcpy(message.msg_text, "test");

    msgsnd(msgid, &message, sizeof(message.msg_text), 0);

    printf("Message created and sent: type=%ld, text=%s\n", 
message.msg_type, message.msg_text);
    return 0;
}
EOF

# ---------- message_send.c ----------
cat << 'EOF' > message_send.c
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

int main() {
    key_t key;
    int msgid;

    key = ftok("progfile", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);

    struct msg_buffer message;
    message.msg_type = 1;
    strcpy(message.msg_text, "Hello from message_send!");

    msgsnd(msgid, &message, sizeof(message.msg_text), 0);

    printf("Message sent: %s\n", message.msg_text);
    return 0;
}
EOF

# ---------- message_receive.c ----------
cat << 'EOF' > message_receive.c
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>

struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

int main() {
    key_t key;
    int msgid;

    key = ftok("progfile", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);

    struct msg_buffer message;

    msgrcv(msgid, &message, sizeof(message.msg_text), 0, 0);

    printf("Received message: type=%ld, text=%s\n", message.msg_type, 
message.msg_text);
    return 0;
}
EOF

# ---------- message_rm.c ----------
cat << 'EOF' > message_rm.c
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    key_t key;
    int msgid;

    key = ftok("progfile", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);

    msgctl(msgid, IPC_RMID, NULL);
    printf("Message queue deleted successfully.\n");
    return 0;
}
EOF

# Քայլ 2․ Կոմպիլյացնենք բոլոր ֆայլերը
echo "[2/10] Կոմպիլյացվում են ծրագրերը..."
gcc message_create.c -o message_create
gcc message_send.c -o message_send
gcc message_receive.c -o message_receive
gcc message_rm.c -o message_rm

echo "[3/10] Ստեղծում ենք օգնական ֆայլ (progfile)..."
echo "dummy" > progfile

# Քայլ 4․ Գործարկում ենք message_create
echo
echo "▶ Քայլ 4․ message_create – նոր հաղորդագրություն ստեղծել"
./message_create

# Քայլ 5․ Ցուցադրել IPCS -q արդյունքը
echo
echo "▶ Քայլ 5․ ipcs -q – ցուցադրել գործող message queues"
ipcs -q

# Քայլ 6․ Գործարկել message_send ծրագիրը
echo
echo "▶ Քայլ 6․ message_send – ավելացնել նոր հաղորդագրություն"
./message_send

# Քայլ 7․ Կրկին ցուցադրել ipcs -q արդյունքը
echo
echo "▶ Քայլ 7․ ipcs -q (ստուգել փոփոխությունը)"
ipcs -q

# Քայլ 8․ Գործարկել message_receive (ընդունել հաղորդագրությունը)
echo
echo "▶ Քայլ 8․ message_receive – կարդալ հաղորդագրությունը"
./message_receive

# Քայլ 9․ Կրկին ստուգել հերթը
echo
echo "▶ Քայլ 9․ ipcs -q – ստուգել մնացյալ հերթը"
ipcs -q

# Քայլ 10․ Ջնջել հերթը
echo
echo "▶ Քայլ 10․ message_rm – ջնջել հաղորդագրությունների հերթը"
./message_rm

echo
echo "============================================"
echo " Բոլոր առաջադրանքները կատարվեցին հաջողությամբ ✅"
echo "============================================"
