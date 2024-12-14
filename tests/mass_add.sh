for i in {1..80}; do
    curl --request POST \
        --url http://127.0.0.1:8080/books \
        --header 'Content-Type: application/json' \
        --header 'User-Agent: insomnia/10.0.0' \
        --data "{
            \"id\": $i,
            \"title\": \"Book $i\",
            \"author\": \"Author $i\",
            \"publisher\": \"Publisher $i\",
            \"year\": $((2000 + i)),
            \"pages\": $((100 + i * 2)),
            \"edition\": \"${i}th Edition\",
            \"description\": \"Description for book $i\",
            \"status\": \"Available\"
        }"
done