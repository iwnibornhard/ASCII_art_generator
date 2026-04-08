#include <iostream>
#include <random>

//function utilizing formula for generating chars in certain range.
//for e.g., if min=33 and max=34, we'll either get '!' (33) or '"' (34)
char randomGenerator(int min = 0, int max = 0) {
    return (rand() % (max - min + 1) + min);
}

int main() {
    //no need for complex PRNG algorithm/complex seed
    //using this to select what character will be used
    srand(time(nullptr));
    char s = randomGenerator(33, 34);
    std::cout << s;
    return 0;
}