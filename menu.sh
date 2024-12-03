#!/bin/bash
# Ցույց տալ մենյու
show_menu() {
    echo "=========================="
    echo "        Գլխավոր Մենյու"
    echo "=========================="
    echo "1. Էկրանին տպել IPv4 և IPv6 հասցեները"
    echo "2. Ցույց տալ ցանցային ճանապարհը (traceroute)"
    echo "3. Ցույց տալ մուտքագրված hostname-ի IP հասցեն"
    echo "4. Գաղտնագրել տեքստը (Ցեզարի մեթոդով)"
    echo "5. Վերծանել տեքստը (Ցեզարի մեթոդով)"
    echo "6. Սեղմել ֆայլը կամ տեքստը"
    echo "7. Վերականգնել սեղմված ֆայլը կամ տեքստը"
    echo "8. Հաշվել ֆայլի արժեքը (checksum)"
    echo "9. Ելք"
    echo "=========================="
}

# Էկրանին տպել IP հասցեները
show_ip() {
    echo "IPv4 հասցեներ:"
    ifconfig | grep "inet " | awk '{print $2}'
    echo "IPv6 հասցեներ:"
    ifconfig | grep "inet6 " | awk '{print $2}'
}
# Ցանցային ճանապարհը (traceroute)
network_path() {
    read -p "Մուտքագրեք hostname կամ URL: " hostname
    traceroute "$hostname"
}
# Ցույց տալ hostname-ի IP հասցեն
hostname_to_ip() {
    read -p "Մուտքագրեք hostname կամ URL: " hostname
    ip=$(dig +short "$hostname")
    if [[ -z "$ip" ]]; then
        echo "Հնարավոր չէ գտնել IP հասցե։"
    else
        echo "IP հասցե: $ip"
    fi
}

# Ցեզարի գաղտնագրում
caesar_encrypt() {
    read -p "Մուտքագրեք տեքստը գաղտնագրման համար: " text
    read -p "Մուտքագրեք տեղաշարժի չափը (թիվ): " shift
    encrypted=""
    for ((i=0; i<${#text}; i++)); do
        char="${text:i:1}"
        if [[ "$char" =~ [a-zA-Z] ]]; then
            ascii=$(printf "%d" "'$char")
            base=$((ascii >= 97 ? 97 : 65))
            new_char=$(printf \\$(printf "%03o" $(( (ascii - base + shift) % 26 + base ))))
            encrypted+="$new_char"
        else
            encrypted+="$char"
        fi
    done
    echo "Գաղտնագրված տեքստը: $encrypted"
}

# Ցեզարի վերծանում
caesar_decrypt() {
    read -p "Մուտքագրեք տեքստը վերծանման համար: " text
    read -p "Մուտքագրեք տեղաշարժի չափը (թիվ): " shift
    shift=$(( -shift ))
    caesar_encrypt "$text" "$shift"
}

# Սեղմել ֆայլը կամ տեքստը
compress_file() {
    read -p "Մուտքագրեք ֆայլի անունը սեղմելու համար: " file
    if [[ -f "$file" ]]; then
        gzip "$file"
        echo "Ֆայլը սեղմվել է: $file.gz"
    else
        echo "Ֆայլը գոյություն չունի։"
    fi
}

# Վերականգնել սեղմված ֆայլը
decompress_file() {
    read -p "Մուտքագրեք սեղմված ֆայլի անունը: " file
    if [[ -f "$file" ]]; then
        gunzip "$file"
        echo "Ֆայլը վերականգնվել է։"
    else
        echo "Սեղմված ֆայլը գոյություն չունի։"
    fi
}
# Հաշվել ֆայլի արժեքը (checksum)
calculate_checksum() {
    read -p "Մուտքագրեք ֆայլի անունը: " file
    if [[ -f "$file" ]]; then
        checksum=$(shasum "$file" | awk '{print $1}')
        echo "Ֆայլի checksum արժեքը: $checksum"
    else
        echo "Ֆայլը գոյություն չունի։"
    fi
}

# Գլխավոր ծրագիր
while true; do
    show_menu
    read -p "Ընտրեք գործողությունը (1-9): " choice

    case $choice in
        1) show_ip ;;
        2) network_path ;;
        3) hostname_to_ip ;;
        4) caesar_encrypt ;;
        5) caesar_decrypt ;;
        6) compress_file ;;
        7) decompress_file ;;
        8) calculate_checksum ;;
        9) echo "Ելք..."; exit 0 ;;
        *) echo "Սխալ ընտրություն։ Խնդրում ենք փորձել կրկին։" ;;
    esac

    echo
    read -p "Սեղմեք Enter՝ շարունակելու համար..." dummy
done
