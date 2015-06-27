rm ./ex17b
make ex17b
echo "==> Test create"
./ex17b /tmp/fake.db c 10
echo "==> Test set"
./ex17b /tmp/fake.db s 1 mohan mohan1@test.com
./ex17b /tmp/fake.db s 2 mohan2 mohan2@test.com
echo "==> Test list"
./ex17b /tmp/fake.db l
echo "==> Test get"
./ex17b /tmp/fake.db g 2
echo "==> Test get fail"
./ex17b /tmp/fake.db g 5
echo "==> Test delete"
./ex17b /tmp/fake.db d 1
./ex17b /tmp/fake.db g 1
./ex17b /tmp/fake.db g 2
