#!/bin/bash
# ===============================
# ՍԵՄԱՖՈՐՆԵՐԻ ԱՌԱՋԱԴՐԱՆՔՆԵՐ
# ===============================

# 1. Ստեղծել նոր սեմաֆորների համալիր՝ 4 սեմաֆորով
echo "1. Ստեղծում ենք նոր սեմաֆորների համալիր..."
SEM_ID=$(ipcmk -S 4 | awk '{print $NF}')
echo "Ստեղծվեց սեմաֆոր՝ ID=$SEM_ID"
echo

# 2. Արժեքների սահմանում (3,2,1,0)
echo "2. Սահմանում ենք սեմաֆորների սկզբնական արժեքները՝ 3,2,1,0"
for i in 0 1 2 3; do
  val=$((3 - i))
  ipcs -s | grep $SEM_ID >/dev/null 2>&1
  if [ $? -eq 0 ]; then
    ipcrm -s $SEM_ID
    SEM_ID=$(ipcmk -S 4 | awk '{print $NF}')
  fi
done

# Ստեղծում ենք նոր համալիր նորից
SEM_ID=$(ipcmk -S 4 | awk '{print $NF}')
for i in 0 1 2 3; do
  val=$((3 - i))
  semctl $SEM_ID $i SETVAL $val
done
echo "Սեմաֆորների արժեքները սահմանվեցին՝ 3,2,1,0"
echo

# 3. sem_good_init ծրագիր — տպել 2 սեմաֆորների արժեքներ
echo "3. Տպում ենք առաջին երկու սեմաֆորների արժեքները:"
for i in 0 1; do
  val=$(ipcs -s -i $SEM_ID | grep "semnum $i" | awk '{print $4}')
  echo "Սեմաֆոր $i արժեքը՝ $val"
done
echo

# 4. sem_op_undo օրինակ
echo "4. Օրինակ՝ SEM_UNDO flag-ով սեմաֆորների փոփոխություն"

cat > sem_op_undo.c <<'EOF'
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

int main() {
    key_t key = ftok(".", 'S');
    int semid = semget(key, 1, IPC_CREAT | 0666);
    if (semid == -1) { perror("semget"); return 1; }

    struct sembuf op = {0, -1, SEM_UNDO}; // նվազեցնել 1-ով SEM_UNDO-ով
    printf("Գործարկում ենք SEM_UNDO գործողությունը...\n");
    semop(semid, &op, 1);
    printf("Սպասում ենք 5 վայրկյան...\n");
    sleep(5);
    printf("Ծրագիրը ավարտվեց, undo կկատարվի ավտոմատ\n");
    return 0;
}
EOF

gcc sem_op_undo.c -o sem_op_undo
./sem_op_undo

echo
echo "Ամեն ինչ ավարտվեց։ Սեմաֆորների ցուցակը՝"
ipcs -s

echo "Ստեղծված սեմաֆորը կարող ես ջնջել՝ ipcrm -s $SEM_ID"

