#include "./solution.h"

void test0(){
    vector<string> foods[1] = {{"kimchi", "miso", "sushi", "moussaka", "ramen", "bulgogi"}};
    vector<string> cuisines[1] = {{"korean", "japanese", "japanese", "greek", "japanese", "korean"}};
    vector<int> ratings[1] = {{9, 12, 8, 15, 14, 7}};
    string food[2] = {"sushi", "ramen"};
    int newRating[2] = {16, 16};
    string cuisine[4] = {"korean", "japanese", "japanese", "japanese"};
    FoodRatings *obj = new FoodRatings(foods[0], cuisines[0], ratings[0]);
    string res0 = obj->highestRated(cuisine[0]);
    string ans0 = "kimchi";
    compare_result("0-0", res0, ans0);
    string res1 = obj->highestRated(cuisine[1]);
    string ans1 = "ramen";
    compare_result("0-1", res1, ans1);
    obj->changeRating(food[0], newRating[0]);
    string res2 = obj->highestRated(cuisine[2]);
    string ans2 = "sushi";
    compare_result("0-2", res2, ans2);
    obj->changeRating(food[1], newRating[1]);
    string res3 = obj->highestRated(cuisine[3]);
    string ans3 = "ramen";
    compare_result("0-3", res3, ans3);
}

int main() {
    test0();
    return 0;
}
